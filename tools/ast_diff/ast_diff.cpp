// AURA Phase G — Hybrid scorer ast_diff binary.
//
// Parses two C source files (Ghidra reference + AURA decompile output)
// using libclang's C API, normalizes both ASTs (variable renaming,
// compound-condition flatten for F-1-C-3 visibility, cast-and-deref
// canonicalization for F-1-M visibility), then computes Jaccard
// similarity over branch conditions and member-access patterns.
//
// CLI:
//   ast_diff <ghidra_file> <aura_file>
//
// Output (stdout, JSON one line):
//   {"ast_branch_semantic": int, "ast_struct_semantic": int,
//    "ast_total": int, "ast_parse_ok": bool}
//
// Exit codes:
//   0 — both files parsed successfully
//   2 — at least one file failed to parse (JSON still emitted with
//       ast_parse_ok=false and zeroed scores)
//   3 — usage error
//
// Build: see tools/ast_diff/CMakeLists.txt
// Design: tests/benchmark/HYBRID_SCORER_DESIGN.md (Phase G-1)

#include <clang-c/Index.h>

#include <algorithm>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {

// ── Stub harness prepended to each source so libclang accepts decompile
//    output that lacks standard headers. Generic enough to cover most
//    Ghidra/AURA emit conventions; struct types are intentionally left
//    forward-declared (libclang KeepGoing mode tolerates incomplete-type
//    member access for our normalization purposes).
constexpr const char* STUB_HARNESS_PREFIX =
    "typedef unsigned char  uint8_t;\n"
    "typedef unsigned short uint16_t;\n"
    "typedef unsigned int   uint32_t;\n"
    "typedef unsigned long  uint64_t;\n"
    "typedef signed char    int8_t;\n"
    "typedef short          int16_t;\n"
    "typedef int            int32_t;\n"
    "typedef long           int64_t;\n"
    "typedef unsigned long  size_t;\n"
    "typedef long           ssize_t;\n"
    "typedef unsigned long  uintptr_t;\n"
    "typedef long           intptr_t;\n"
    "typedef int            FILE;\n"
    "typedef int            _Bool;\n"
    "typedef unsigned long  ulong;\n"
    "typedef unsigned int   uint;\n"
    "typedef unsigned char  byte;\n"
    "typedef unsigned short ushort;\n"
    "typedef unsigned long  undefined8;\n"
    "typedef unsigned int   undefined4;\n"
    "typedef unsigned short undefined2;\n"
    "typedef unsigned char  undefined1;\n"
    "typedef unsigned char  undefined;\n"
    // Ghidra-style generic struct so `s->f<N>` parses without explicit
    // member declaration. We treat any `MemberRefExpr` whose name starts
    // with 'f' or 'field' followed by digits as offset N.
    "struct __attribute__((aligned(8))) __aura_generic_s {\n"
    "    char _data[8192];\n"
    "};\n"
    "/* === decompile output begins === */\n";

constexpr int MAX_SUB_SCORE = 10;

// ── Read file contents into a string (returns empty on failure) ────
std::string read_file(const char* path) {
    std::ifstream ifs(path);
    if (!ifs) return {};
    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

// ── Convert CXString to std::string (and dispose) ──────────────────
std::string cxstr(CXString s) {
    const char* c = clang_getCString(s);
    std::string r = c ? c : "";
    clang_disposeString(s);
    return r;
}

// ── Normalized tree node ───────────────────────────────────────────
// A canonical, language-agnostic representation of an expression /
// statement subtree used for Jaccard hashing. Variable names are
// already renamed (vN / pN / aN) so identical structure across
// rename schemes hashes equally.
struct Node {
    enum Kind : uint16_t {
        K_Unknown = 0,
        K_IntLit, K_StrLit, K_FloatLit,
        K_DeclRef,        // value = renamed ID ("v0", "p0", "g_foo")
        K_BinOp,          // value = operator string ("==", "+", "&&", ...)
        K_UnaryOp,        // value = operator ("*", "&", "-", "!", ...)
        K_Cast,            // value = (best-effort) target type name; child = expr
        K_MemberAccess,   // value = "<base_id>:<offset_int>"; no children
        K_Call,           // value = function name (renamed or literal)
        K_Cond,            // value = ""; children: cond, then-tag, else-tag
        K_Compound,       // children = sequence
        K_If, K_While, K_For, K_DoWhile, K_Switch,
        K_ParenExpr,      // pass-through
    };
    Kind kind = K_Unknown;
    std::string value;
    std::vector<Node> children;

    // Recursive structural hash (no var-name dependency beyond renamed
    // form already baked into `value`).
    uint64_t hash() const {
        uint64_t h = 1469598103934665603ULL;  // FNV-1a basis
        auto mix = [&](uint64_t v) {
            h ^= v;
            h *= 1099511628211ULL;
        };
        mix(static_cast<uint64_t>(kind));
        for (char c : value) mix(static_cast<uint8_t>(c));
        mix(0xDEADBEEF);  // separator
        for (const auto& ch : children) mix(ch.hash());
        return h;
    }

    bool operator==(const Node& o) const {
        return hash() == o.hash();
    }
};

struct NodeHash { size_t operator()(const Node& n) const { return n.hash(); } };

// ── Visitor / parse context ────────────────────────────────────────
struct VisitorContext {
    // Per-VarDecl renaming. Key = clang_hashCursor of the canonical
    // decl (we walk to canonical via clang_getCursorReferenced for
    // DeclRefExpr lookup).
    std::unordered_map<unsigned, std::string> rename;
    int next_var = 0;
    int next_param = 0;
    // Set of compound-condition flatten substitutions: when an
    // `if (X) ...` is preceded by `X = expr;`, IfStmt's condition for
    // hashing purposes is `expr` rather than the DeclRefExpr to X.
    std::unordered_map<unsigned, Node> if_cond_override;
    // Outputs:
    std::vector<Node> branch_conditions;
    std::vector<Node> member_accesses;
    // Tracking for source-text operator extraction:
    CXTranslationUnit tu = nullptr;
    const std::string* source = nullptr;  // wrapped source, byte-indexed
};

// Get byte offset of cursor's start/end in the source buffer.
unsigned cursor_off_start(CXCursor c) {
    CXSourceLocation loc = clang_getRangeStart(clang_getCursorExtent(c));
    unsigned off = 0;
    clang_getFileLocation(loc, nullptr, nullptr, nullptr, &off);
    return off;
}
unsigned cursor_off_end(CXCursor c) {
    CXSourceLocation loc = clang_getRangeEnd(clang_getCursorExtent(c));
    unsigned off = 0;
    clang_getFileLocation(loc, nullptr, nullptr, nullptr, &off);
    return off;
}

// Forward decls
Node build_node(CXCursor c, VisitorContext& ctx);

// ── Helper: collect immediate children into vector ────────────────
struct ChildCollector { std::vector<CXCursor> kids; };
static CXChildVisitResult kid_visitor_fwd(CXCursor c, CXCursor /*parent*/,
                                          CXClientData data) {
    static_cast<ChildCollector*>(data)->kids.push_back(c);
    return CXChildVisit_Continue;
}
std::vector<CXCursor> children_of(CXCursor c) {
    ChildCollector cc;
    clang_visitChildren(c, kid_visitor_fwd, &cc);
    return cc.kids;
}

// ── Recover a BinaryOperator / UnaryOperator's operator string by
//    inspecting source text directly. libclang's C API doesn't expose
//    the opcode enum, so we use position-based extraction:
//    - BinaryOperator: scan source between LHS-end and RHS-start for
//      the operator token (skip whitespace, compare against known op
//      table preferring longest match).
//    - UnaryOperator: scan from cursor-start; first non-whitespace
//      operator-character sequence.
static const std::vector<std::string> kBinOps = {
    "<<=", ">>=",
    "==", "!=", "<=", ">=", "&&", "||", "<<", ">>",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",
    "->",
    "=", "<", ">", "+", "-", "*", "/", "%", "&", "|", "^", ".", ",",
};
static const std::vector<std::string> kUnaryOps = {
    "++", "--",
    "*", "&", "-", "+", "!", "~",
};

bool starts_with(const std::string& s, size_t pos, const std::string& p) {
    if (pos + p.size() > s.size()) return false;
    return std::memcmp(s.data() + pos, p.data(), p.size()) == 0;
}

std::string match_op(const std::string& src, size_t pos,
                     const std::vector<std::string>& ops) {
    for (const auto& op : ops) {
        if (starts_with(src, pos, op)) return op;
    }
    return {};
}

std::string operator_for(CXCursor cursor, VisitorContext& ctx) {
    if (!ctx.source) return "?";
    const std::string& src = *ctx.source;
    CXCursorKind k = clang_getCursorKind(cursor);
    if (k == CXCursor_BinaryOperator) {
        auto kids = children_of(cursor);
        if (kids.size() < 2) return "?";
        unsigned lhs_end = cursor_off_end(kids[0]);
        unsigned rhs_start = cursor_off_start(kids[1]);
        if (lhs_end >= rhs_start || rhs_start > src.size()) return "?";
        for (size_t i = lhs_end; i < rhs_start; ++i) {
            if (std::isspace(static_cast<unsigned char>(src[i]))) continue;
            std::string op = match_op(src, i, kBinOps);
            if (!op.empty()) return op;
        }
        return "?";
    }
    if (k == CXCursor_UnaryOperator) {
        unsigned start = cursor_off_start(cursor);
        if (start >= src.size()) return "?";
        // Postfix ++/-- could occur after operand; check first char
        // first (prefix).
        for (size_t i = start; i < src.size(); ++i) {
            if (std::isspace(static_cast<unsigned char>(src[i]))) continue;
            std::string op = match_op(src, i, kUnaryOps);
            if (!op.empty()) return op;
            break;  // first non-whitespace must be the prefix op
        }
        // Try postfix on the END of the cursor range.
        unsigned end = cursor_off_end(cursor);
        if (end >= 2 && end <= src.size()) {
            std::string suffix2 = src.substr(end - 2, 2);
            if (suffix2 == "++" || suffix2 == "--") return suffix2;
        }
        return "?";
    }
    return "?";
}

// ── Canonical name for a referenced decl (rename lookup) ────────────
std::string renamed_name(CXCursor decl_cursor, VisitorContext& ctx) {
    unsigned h = clang_hashCursor(decl_cursor);
    auto it = ctx.rename.find(h);
    if (it != ctx.rename.end()) return it->second;
    // Globals / built-ins: keep original spelling so cross-side
    // references match.
    return cxstr(clang_getCursorSpelling(decl_cursor));
}

// ── Parse a positive integer prefix following a leading 'f' or
//    'field' from a member name, e.g. "f8" → 8, "field_0x18" → 24.
//    Returns -1 if no recognizable offset.
int member_name_to_offset(const std::string& name) {
    // Try Ghidra patterns: "fN", "f_N", "field_N", "field_0xN"
    auto try_parse = [](const char* p) -> int {
        if (!*p) return -1;
        char* end = nullptr;
        long v = std::strtol(p, &end, 0);
        if (end == p) return -1;
        if (v < 0) return -1;
        return static_cast<int>(v);
    };
    if (name.size() < 2) return -1;
    if (name[0] == 'f') {
        if (name.size() >= 2 && std::isdigit(static_cast<unsigned char>(name[1])))
            return try_parse(name.c_str() + 1);
        if (name.compare(0, 2, "f_") == 0)
            return try_parse(name.c_str() + 2);
        if (name.compare(0, 6, "field_") == 0)
            return try_parse(name.c_str() + 6);
    }
    return -1;
}

// kid_visitor alias for the rest of the file
constexpr auto kid_visitor = kid_visitor_fwd;

// ── Detect cast-and-deref offset pattern:
//      *(T*)((U*)base + N)        or   *(T*)(base + N)
//    Returns true and fills (base_cursor, offset_bytes) if recognized;
//    false otherwise.
bool detect_cast_deref_offset(CXCursor unary_op, VisitorContext& ctx,
                              std::string& base_id, int& offset_bytes) {
    // unary_op should be UnaryOperator with op '*' (deref).
    if (clang_getCursorKind(unary_op) != CXCursor_UnaryOperator) return false;
    if (operator_for(unary_op, ctx) != "*") return false;

    auto kids = children_of(unary_op);
    if (kids.empty()) return false;
    // Walk through cast and paren chains.
    CXCursor cur = kids.front();
    auto unwrap = [&](CXCursor c) -> CXCursor {
        for (;;) {
            CXCursorKind k = clang_getCursorKind(c);
            if (k == CXCursor_CStyleCastExpr || k == CXCursor_ParenExpr ||
                k == CXCursor_UnexposedExpr) {
                auto sub = children_of(c);
                if (sub.empty()) return c;
                // Pick last non-typeref child.
                CXCursor pick = clang_getNullCursor();
                for (auto it = sub.rbegin(); it != sub.rend(); ++it) {
                    if (clang_getCursorKind(*it) != CXCursor_TypeRef) {
                        pick = *it;
                        break;
                    }
                }
                if (clang_Cursor_isNull(pick)) return c;
                c = pick;
                continue;
            }
            break;
        }
        return c;
    };
    cur = unwrap(cur);
    if (clang_getCursorKind(cur) != CXCursor_BinaryOperator) return false;
    if (operator_for(cur, ctx) != "+") return false;

    auto bin_kids = children_of(cur);
    if (bin_kids.size() < 2) return false;
    CXCursor lhs = unwrap(bin_kids[0]);
    CXCursor rhs = unwrap(bin_kids[1]);

    // Identify integer literal side and base side.
    CXCursor lit = clang_getNullCursor(), base = clang_getNullCursor();
    if (clang_getCursorKind(rhs) == CXCursor_IntegerLiteral) {
        lit = rhs; base = lhs;
    } else if (clang_getCursorKind(lhs) == CXCursor_IntegerLiteral) {
        lit = lhs; base = rhs;
    } else {
        return false;
    }

    // Extract integer literal value via tokens.
    if (!ctx.tu) return false;
    CXToken* toks = nullptr; unsigned nt = 0;
    clang_tokenize(ctx.tu, clang_getCursorExtent(lit), &toks, &nt);
    long lit_val = 0;
    if (nt > 0) {
        std::string ts = cxstr(clang_getTokenSpelling(ctx.tu, toks[0]));
        char* end = nullptr;
        lit_val = std::strtol(ts.c_str(), &end, 0);
        if (end == ts.c_str()) lit_val = -1;
    }
    if (toks) clang_disposeTokens(ctx.tu, toks, nt);
    if (lit_val < 0) return false;

    // Extract base name.
    if (clang_getCursorKind(base) == CXCursor_DeclRefExpr) {
        CXCursor ref = clang_getCursorReferenced(base);
        if (clang_Cursor_isNull(ref)) {
            base_id = cxstr(clang_getCursorSpelling(base));
        } else {
            base_id = renamed_name(ref, ctx);
        }
    } else {
        base_id = "anon";
    }
    offset_bytes = static_cast<int>(lit_val);
    return true;
}

// ── Build a Node from a cursor (recursive). Generic structural copy. ──
Node build_node(CXCursor c, VisitorContext& ctx) {
    Node n;
    CXCursorKind k = clang_getCursorKind(c);
    switch (k) {
        case CXCursor_IntegerLiteral: {
            n.kind = Node::K_IntLit;
            CXToken* toks = nullptr; unsigned nt = 0;
            if (ctx.tu) {
                clang_tokenize(ctx.tu, clang_getCursorExtent(c), &toks, &nt);
                if (nt > 0) {
                    n.value = cxstr(clang_getTokenSpelling(ctx.tu, toks[0]));
                }
                if (toks) clang_disposeTokens(ctx.tu, toks, nt);
            }
            return n;
        }
        case CXCursor_StringLiteral:
            n.kind = Node::K_StrLit;
            n.value = "<str>";
            return n;
        case CXCursor_FloatingLiteral:
            n.kind = Node::K_FloatLit;
            return n;
        case CXCursor_DeclRefExpr: {
            n.kind = Node::K_DeclRef;
            CXCursor ref = clang_getCursorReferenced(c);
            n.value = clang_Cursor_isNull(ref)
                ? cxstr(clang_getCursorSpelling(c))
                : renamed_name(ref, ctx);
            return n;
        }
        case CXCursor_BinaryOperator: {
            n.kind = Node::K_BinOp;
            n.value = operator_for(c, ctx);
            for (auto kid : children_of(c)) n.children.push_back(build_node(kid, ctx));
            return n;
        }
        case CXCursor_UnaryOperator: {
            // M canonicalization: cast-and-deref → MemberAccess
            std::string base_id; int off;
            if (detect_cast_deref_offset(c, ctx, base_id, off)) {
                n.kind = Node::K_MemberAccess;
                n.value = base_id + ":" + std::to_string(off);
                return n;
            }
            n.kind = Node::K_UnaryOp;
            n.value = operator_for(c, ctx);
            for (auto kid : children_of(c)) n.children.push_back(build_node(kid, ctx));
            return n;
        }
        case CXCursor_MemberRefExpr: {
            n.kind = Node::K_MemberAccess;
            std::string mname = cxstr(clang_getCursorSpelling(c));
            int off = member_name_to_offset(mname);
            std::string base_id = "anon";
            // Walk through wrapping nodes to find the underlying base.
            std::function<CXCursor(CXCursor)> unwrap =
                [&](CXCursor cc) -> CXCursor {
                while (true) {
                    CXCursorKind kk = clang_getCursorKind(cc);
                    if (kk == CXCursor_ParenExpr ||
                        kk == CXCursor_UnexposedExpr ||
                        kk == CXCursor_CStyleCastExpr) {
                        auto sub = children_of(cc);
                        CXCursor pick = clang_getNullCursor();
                        for (auto it = sub.rbegin(); it != sub.rend(); ++it) {
                            if (clang_getCursorKind(*it) != CXCursor_TypeRef) {
                                pick = *it; break;
                            }
                        }
                        if (clang_Cursor_isNull(pick)) return cc;
                        cc = pick;
                        continue;
                    }
                    break;
                }
                return cc;
            };
            auto kids = children_of(c);
            if (!kids.empty()) {
                CXCursor base = unwrap(kids.front());
                if (clang_getCursorKind(base) == CXCursor_DeclRefExpr) {
                    CXCursor ref = clang_getCursorReferenced(base);
                    base_id = clang_Cursor_isNull(ref)
                        ? cxstr(clang_getCursorSpelling(base))
                        : renamed_name(ref, ctx);
                }
            }
            n.value = base_id + ":" + (off >= 0 ? std::to_string(off) : mname);
            return n;
        }
        case CXCursor_CStyleCastExpr:
        case CXCursor_ParenExpr:
        case CXCursor_UnexposedExpr: {
            // Pass through to first non-typeref child for hashing.
            for (auto kid : children_of(c)) {
                CXCursorKind kk = clang_getCursorKind(kid);
                if (kk == CXCursor_TypeRef) continue;
                return build_node(kid, ctx);
            }
            n.kind = Node::K_ParenExpr;
            return n;
        }
        case CXCursor_CallExpr: {
            n.kind = Node::K_Call;
            CXCursor ref = clang_getCursorReferenced(c);
            n.value = clang_Cursor_isNull(ref)
                ? cxstr(clang_getCursorSpelling(c))
                : cxstr(clang_getCursorSpelling(ref));
            for (auto kid : children_of(c)) {
                if (clang_getCursorKind(kid) == CXCursor_FirstExpr)
                    continue;  // skip callee ref
                n.children.push_back(build_node(kid, ctx));
            }
            return n;
        }
        default:
            n.kind = Node::K_Unknown;
            for (auto kid : children_of(c))
                n.children.push_back(build_node(kid, ctx));
            return n;
    }
}

// ── Detect compound-condition flatten pattern in a CompoundStmt.
//    Handles two forms:
//      1) Assignment then if:    `X = expr; if (X) { ... }`
//         AST: BinaryOperator(=, DeclRef(X), expr) → IfStmt(DeclRef(X), ...)
//      2) Decl-init then if:    `T X = expr; if (X) { ... }`
//         AST: DeclStmt(VarDecl(X, init=expr))    → IfStmt(DeclRef(X), ...)
//    Records an override so the IfStmt's branch_condition uses `expr`'s
//    normalized form rather than DeclRef(X).
void apply_c3_flatten(CXCursor compound, VisitorContext& ctx) {
    auto kids = children_of(compound);

    auto unwrap = [](CXCursor c) {
        while (clang_getCursorKind(c) == CXCursor_ParenExpr ||
               clang_getCursorKind(c) == CXCursor_UnexposedExpr) {
            ChildCollector cc;
            clang_visitChildren(c, kid_visitor, &cc);
            if (cc.kids.empty()) break;
            c = cc.kids.front();
        }
        return c;
    };

    // Helper: extract (decl_cursor, init_expr) from a candidate stmt.
    // Returns true if stmt assigns/initializes a variable to some expr.
    auto extract_assign_or_init =
        [&](CXCursor stmt, CXCursor& out_decl, CXCursor& out_expr) -> bool {
        CXCursorKind k = clang_getCursorKind(stmt);
        if (k == CXCursor_BinaryOperator && operator_for(stmt, ctx) == "=") {
            auto kk = children_of(stmt);
            if (kk.size() < 2) return false;
            CXCursor lhs = kk[0];
            if (clang_getCursorKind(lhs) != CXCursor_DeclRefExpr) return false;
            CXCursor ref = clang_getCursorReferenced(lhs);
            if (clang_Cursor_isNull(ref)) return false;
            out_decl = ref;
            out_expr = kk[1];
            return true;
        }
        if (k == CXCursor_DeclStmt) {
            auto kk = children_of(stmt);
            if (kk.empty()) return false;
            CXCursor vdec = kk.front();
            if (clang_getCursorKind(vdec) != CXCursor_VarDecl) return false;
            // VarDecl's initializer is its first non-typeref child.
            auto vk = children_of(vdec);
            for (auto vc : vk) {
                CXCursorKind vck = clang_getCursorKind(vc);
                if (vck == CXCursor_TypeRef || vck == CXCursor_NamespaceRef)
                    continue;
                out_decl = vdec;
                out_expr = vc;
                return true;
            }
            return false;
        }
        return false;
    };

    for (size_t i = 0; i + 1 < kids.size(); ++i) {
        CXCursor a = kids[i];
        CXCursor b = kids[i + 1];
        if (clang_getCursorKind(b) != CXCursor_IfStmt) continue;

        CXCursor decl = clang_getNullCursor();
        CXCursor init_expr = clang_getNullCursor();
        if (!extract_assign_or_init(a, decl, init_expr)) continue;

        // Find IfStmt's condition (first child).
        auto b_kids = children_of(b);
        if (b_kids.empty()) continue;
        CXCursor cond = unwrap(b_kids[0]);
        if (clang_getCursorKind(cond) != CXCursor_DeclRefExpr) continue;
        CXCursor cond_ref = clang_getCursorReferenced(cond);
        if (clang_Cursor_isNull(cond_ref)) continue;
        if (clang_hashCursor(decl) != clang_hashCursor(cond_ref))
            continue;

        // Pattern matches — override the IfStmt's effective condition.
        Node replacement = build_node(unwrap(init_expr), ctx);
        ctx.if_cond_override[clang_hashCursor(b)] = std::move(replacement);
    }

    // Recurse into nested compound stmts.
    for (auto k : kids) {
        if (clang_getCursorKind(k) == CXCursor_CompoundStmt) {
            apply_c3_flatten(k, ctx);
        } else {
            auto sub = children_of(k);
            for (auto s : sub) {
                if (clang_getCursorKind(s) == CXCursor_CompoundStmt) {
                    apply_c3_flatten(s, ctx);
                }
            }
        }
    }
}

// ── First-pass visitor: assign rename slots to VarDecl/ParmDecl in
//    DFS pre-order. ──────────────────────────────────────────────────
CXChildVisitResult rename_visitor(CXCursor c, CXCursor /*parent*/,
                                  CXClientData data) {
    auto* ctx = static_cast<VisitorContext*>(data);
    CXCursorKind k = clang_getCursorKind(c);
    if (k == CXCursor_VarDecl) {
        unsigned h = clang_hashCursor(c);
        if (ctx->rename.find(h) == ctx->rename.end()) {
            ctx->rename[h] = "v" + std::to_string(ctx->next_var++);
        }
    } else if (k == CXCursor_ParmDecl) {
        unsigned h = clang_hashCursor(c);
        if (ctx->rename.find(h) == ctx->rename.end()) {
            ctx->rename[h] = "p" + std::to_string(ctx->next_param++);
        }
    }
    return CXChildVisit_Recurse;
}

// ── Second-pass visitor: collect branch conditions + member accesses ──
CXChildVisitResult collect_visitor(CXCursor c, CXCursor /*parent*/,
                                   CXClientData data) {
    auto* ctx = static_cast<VisitorContext*>(data);
    CXCursorKind k = clang_getCursorKind(c);

    // Branch conditions for IfStmt / WhileStmt / ForStmt / DoStmt /
    // SwitchStmt. Apply C-3 flatten override if present.
    auto add_branch_cond = [&](CXCursor stmt, int cond_idx) {
        auto kids = children_of(stmt);
        if (cond_idx < 0 || static_cast<size_t>(cond_idx) >= kids.size()) return;
        unsigned h = clang_hashCursor(stmt);
        auto it = ctx->if_cond_override.find(h);
        if (it != ctx->if_cond_override.end()) {
            ctx->branch_conditions.push_back(it->second);
        } else {
            ctx->branch_conditions.push_back(build_node(kids[cond_idx], *ctx));
        }
    };
    switch (k) {
        case CXCursor_IfStmt:    add_branch_cond(c, 0); break;
        case CXCursor_WhileStmt: add_branch_cond(c, 0); break;
        case CXCursor_DoStmt: {
            // do-while: condition is last child
            auto kids = children_of(c);
            if (!kids.empty())
                ctx->branch_conditions.push_back(build_node(kids.back(), *ctx));
            break;
        }
        case CXCursor_ForStmt: {
            // for(init;cond;inc)body — children order varies; condition
            // is the second child if 4 children present.
            auto kids = children_of(c);
            if (kids.size() >= 3)
                ctx->branch_conditions.push_back(build_node(kids[1], *ctx));
            break;
        }
        case CXCursor_SwitchStmt:
            add_branch_cond(c, 0);
            break;
        case CXCursor_MemberRefExpr: {
            Node mn = build_node(c, *ctx);
            if (mn.kind == Node::K_MemberAccess) {
                ctx->member_accesses.push_back(std::move(mn));
            }
            break;
        }
        case CXCursor_UnaryOperator: {
            std::string base_id; int off;
            if (detect_cast_deref_offset(c, *ctx, base_id, off)) {
                Node mn;
                mn.kind = Node::K_MemberAccess;
                mn.value = base_id + ":" + std::to_string(off);
                ctx->member_accesses.push_back(std::move(mn));
            }
            break;
        }
        default: break;
    }
    return CXChildVisit_Recurse;
}

// ── Public: parse + normalize ──────────────────────────────────────
struct ParseResult {
    bool ok = false;
    std::vector<Node> branch_conditions;
    std::vector<Node> member_accesses;
};

ParseResult parse_and_normalize(const std::string& src) {
    ParseResult result;
    std::string wrapped = std::string(STUB_HARNESS_PREFIX) + src;

    CXIndex idx = clang_createIndex(0, 0);
    const char* fname = "input.c";
    CXUnsavedFile unsaved{fname, wrapped.c_str(), wrapped.size()};
    const char* args[] = {"-std=c11", "-w"};

    CXTranslationUnit tu = nullptr;
    CXErrorCode err = clang_parseTranslationUnit2(
        idx, fname, args, 2, &unsaved, 1,
        CXTranslationUnit_KeepGoing |
        CXTranslationUnit_DetailedPreprocessingRecord,
        &tu);
    if (err != CXError_Success || !tu) {
        clang_disposeIndex(idx);
        return result;
    }

    // Even with KeepGoing, count fatal diagnostics; if too many,
    // declare parse failed.
    unsigned ndiag = clang_getNumDiagnostics(tu);
    int fatal = 0;
    for (unsigned i = 0; i < ndiag; ++i) {
        CXDiagnostic d = clang_getDiagnostic(tu, i);
        if (clang_getDiagnosticSeverity(d) == CXDiagnostic_Fatal) ++fatal;
        clang_disposeDiagnostic(d);
    }
    // For our purposes, only fatal diagnostics are disqualifying.
    // Errors (e.g., incomplete struct member access) are tolerated
    // because they still produce usable AST cursors.
    bool ok = (fatal == 0);

    VisitorContext ctx;
    ctx.tu = tu;
    ctx.source = &wrapped;
    CXCursor root = clang_getTranslationUnitCursor(tu);

    // Pass 1: rename
    clang_visitChildren(root, rename_visitor, &ctx);
    // Pass 2: C-3 flatten — find compound stmts and detect pattern
    auto find_compounds = [&](CXCursor r) {
        struct CC { std::vector<CXCursor> stmts; };
        CC cc;
        clang_visitChildren(r, [](CXCursor c, CXCursor, CXClientData d) {
            if (clang_getCursorKind(c) == CXCursor_CompoundStmt) {
                static_cast<CC*>(d)->stmts.push_back(c);
            }
            return CXChildVisit_Recurse;
        }, &cc);
        return cc.stmts;
    };
    for (auto cs : find_compounds(root)) {
        apply_c3_flatten(cs, ctx);
    }
    // Pass 3: collect
    clang_visitChildren(root, collect_visitor, &ctx);

    result.ok = ok;
    result.branch_conditions = std::move(ctx.branch_conditions);
    result.member_accesses = std::move(ctx.member_accesses);

    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(idx);
    return result;
}

// ── Jaccard score (max scaled to MAX_SUB_SCORE) ────────────────────
int jaccard_score(const std::vector<Node>& a, const std::vector<Node>& b) {
    if (a.empty() && b.empty()) return MAX_SUB_SCORE;
    if (a.empty() || b.empty()) return 0;
    std::unordered_set<uint64_t> set_a, set_b, intersection, unioned;
    for (const auto& n : a) set_a.insert(n.hash());
    for (const auto& n : b) set_b.insert(n.hash());
    for (auto h : set_a) {
        unioned.insert(h);
        if (set_b.count(h)) intersection.insert(h);
    }
    for (auto h : set_b) unioned.insert(h);
    if (unioned.empty()) return 0;
    double j = static_cast<double>(intersection.size()) /
               static_cast<double>(unioned.size());
    int score = static_cast<int>(j * MAX_SUB_SCORE + 0.5);
    if (score < 0) score = 0;
    if (score > MAX_SUB_SCORE) score = MAX_SUB_SCORE;
    return score;
}

}  // anonymous namespace

int main(int argc, char** argv) {
    if (argc < 3) {
        std::fprintf(stderr, "Usage: %s <ghidra_file> <aura_file>\n", argv[0]);
        return 3;
    }
    std::string g_src = read_file(argv[1]);
    std::string a_src = read_file(argv[2]);

    auto g = parse_and_normalize(g_src);
    auto a = parse_and_normalize(a_src);

    bool ok = g.ok && a.ok;
    int branch = ok ? jaccard_score(g.branch_conditions, a.branch_conditions) : 0;
    int strct  = ok ? jaccard_score(g.member_accesses, a.member_accesses)   : 0;

    std::printf("{\"ast_branch_semantic\": %d, \"ast_struct_semantic\": %d, "
                "\"ast_total\": %d, \"ast_parse_ok\": %s}\n",
                branch, strct, branch + strct, ok ? "true" : "false");
    return ok ? 0 : 2;
}
