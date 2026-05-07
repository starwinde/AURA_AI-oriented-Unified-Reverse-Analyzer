# Modern Decompiler Design Research — AURA Decompiler Improvements

**Date:** 2026-04-04  
**Purpose:** Identify practical improvements to AURA's decompiler architecture based on modern open-source decompilers.

---

## Executive Summary

Modern decompilers (Binary Ninja, Ghidra, RetDec) share a **layered IL approach** with systematic optimization passes. The most impactful improvements for AURA are:

1. **IL hierarchy** (Lifted → Low → Medium → High) with clear transformations at each stage
2. **Modular optimization passes** applied iteratively, not monolithically
3. **Copy propagation + constant folding** as high-ROI first passes
4. **Semantic-preserving control flow structuring** (iterative, region-based)
5. **Constraint-based type inference** over pure heuristics

---

## 1. BNIL Architecture: IL Hierarchy (Binary Ninja)

### Design Pattern

Binary Ninja uses **4-level IL hierarchy** with increasing abstraction:

| Level | Purpose | Key Transformations |
|-------|---------|---------------------|
| **Lifted IL** | Instruction semantics translation | x86 → unified representation |
| **LLIL** (Low Level) | Detailed, unified semantics | Memory ops, register tracking |
| **MLIL** (Medium Level) | Variables, types, SSA form | Stack elimination, function params inferred, CFG structured |
| **HLIL** (High Level) | Control flow statements + AST | Dead code elimination, variable folding, simplified expressions |

### Why This Matters for AURA

- **Current AURA**: Single IL-like representation (CFG → decompiled output)
- **Problem**: Mixing concerns (CFG analysis, type inference, optimization, generation) in one pass
- **Benefit**: Each level is independently testable/optimizable

### AURA Application

Introduce **3-tier IL**:
1. **Level 1 (Core IL)**: CFG + basic block structure, operand tracking
2. **Level 2 (Medium IL)**: SSA form, variable identification, control flow recovery
3. **Level 3 (High IL)**: Simplified expressions, dead code eliminated, output-ready

Reference: [BNIL Overview](https://docs.binary.ninja/dev/bnil-overview.html), [BNIL MLIL](https://docs.binary.ninja/dev/bnil-mlil.html), [BNIL HLIL](https://docs.binary.ninja/dev/bnil-overview.html)

---

## 2. Ghidra P-code: Architecture-Independent Semantic Foundation

### Design Pattern

Ghidra uses **P-code** (Register Transfer Language) as the universal IR, with **SLEIGH** describing machine instruction semantics:

- **P-code**: Unified intermediate language (independent of ISA)
- **SLEIGH**: Specification language that lifts x86/ARM/MIPS → P-code
- **Decompiler**: Operates only on P-code, not raw instructions

### Advantages

1. **Retargetability**: Change processor → change SLEIGH spec, keep decompiler unchanged
2. **Semantic correctness**: ISA semantics captured formally in SLEIGH, not ad-hoc in C code
3. **Decoupling**: Disassembly + lifting vs. analysis are independent concerns

### Why This Matters for AURA

- **Current AURA**: Capstone for disasm + hand-coded semantic lifting in C++
- **Problem**: Semantic lifting scattered across `disasm/` module, hard to verify correctness
- **Opportunity**: Formalize lifting rules (even simple DSL) separately from analysis

### AURA Application

Not full SLEIGH (overkill for MVP), but:
- **Centralized instruction semantics**: Create a spec table mapping `x86 opcode → operand patterns → effect on registers/memory`
- **Semantic lifting wrapper**: Instead of inline Capstone calls, standardize how instructions are converted to IL
- **Example**: `mov eax, [rsp+8]` → explicit `Store(eax, Load(rsp+8))` operation

Reference: [SLEIGH Documentation](https://github.com/NationalSecurityAgency/ghidra/blob/master/Ghidra/Features/Decompiler/src/main/doc/sleigh.xml), [P-code Injection Guide](https://swarm.ptsecurity.com/guide-to-p-code-injection/)

---

## 3. RetDec: LLVM IR as Optimization Pipeline

### Design Pattern

RetDec uses **LLVM IR as a common optimization ground**:

1. **Binary → LLVM IR** (bin2llvmir): Lift machine code to LLVM
2. **Optimize LLVM IR** (multiple passes): Copy propagation, constant folding, DCE, etc.
3. **LLVM IR → Custom BIR** (llvmir2bll): Lift to backend IR
4. **BIR → C**: Final code generation

**Key insight**: Optimization happens at LLVM IR level, which enables cross-architecture reuse.

### Optimization Pass Strategy

RetDec's optimizer calls in order:
- `doInitialization()` — Setup
- `doOptimization()` — Apply passes
- `doFinalization()` — Cleanup

Passes include: **dead code elimination, constant detection, value protection** (preventing LLVM from over-optimizing domain-specific patterns).

### Why This Matters for AURA

- **Current AURA**: Ad-hoc optimizations in `decompiler/` mixed with analysis
- **Problem**: No reusable, composable optimization framework
- **Benefit**: Systematic passes can be applied per-function, per-CFG, enabling tuning

### AURA Application

Create **lightweight optimization pass framework**:

```cpp
struct OptPass {
    virtual void run(CFG& cfg) = 0;
};

class OptimizerPipeline {
    std::vector<std::unique_ptr<OptPass>> passes;
public:
    void addPass(std::unique_ptr<OptPass> p) { passes.push_back(std::move(p)); }
    void run(CFG& cfg) {
        for (auto& p : passes) p->run(cfg);
    }
};

// Usage: pipeline.addPass(make_unique<CopyPropagationPass>());
//        pipeline.addPass(make_unique<ConstantFoldingPass>());
//        pipeline.addPass(make_unique<DeadCodeEliminationPass>());
//        pipeline.run(cfg);
```

Reference: [RetDec GitHub](https://github.com/avast/retdec), [RetDec Optimization Passes](https://decompy.github.io/DecomPy/docs/html/Documentation/4_DecompilerInformation/1_HowDecompilersWork/2_OptimizationPassesInRetdec.html)

---

## 4. High-ROI Optimization Passes (Compiler Design)

### Standard Compiler Optimizations Applicable to Decompilation

| Pass | Impact | Difficulty | AURA Readiness |
|------|--------|------------|-----------------|
| **Copy Propagation** | High | Low | **Easy** — replaces `var_x = var_y; use(var_x)` → `use(var_y)` |
| **Constant Folding** | High | Low | **Easy** — `x = 5 + 3` → `x = 8` |
| **Common Subexpr Elim (CSE)** | Medium | Medium | **Possible** — requires expression hashing |
| **Dead Code Elimination (DCE)** | High | Medium | **Done** — AURA already does liveness analysis |
| **Strength Reduction** | Low | High | Skip for MVP |
| **Inline Expansion** | Medium | High | Post-MVP (function inlining) |

### Dead Code Elimination (Already in AURA)

AURA's liveness analysis already identifies unreachable code and dead assignments. **Next step**: Combine with copy propagation to remove intermediate variables.

Example:
```c
// Before
int x = y + z;
int result = x * 2;
// After (copy propagation + DCE)
int result = (y + z) * 2;
```

### Copy Propagation (High ROI, Easy to Add)

**Problem**: Decompilers produce intermediate variables that obscure intent.  
**Solution**: When `var_x = var_y` (no use of var_x between def and use of var_y), replace all uses of var_x with var_y.

**Algorithm**:
1. For each assignment `x = y`:
   - If x is not live at that point and y is available, mark x for removal
   - Replace uses of x with y downstream
2. Repeat until fixed point

### Constant Folding

**Problem**: `(a ^ 0) + (b >> 0)` should simplify to `a + b`.  
**Solution**: Track constant values, fold binary ops at compile-time.

**Implementation**:
```cpp
Value foldBinaryOp(BinOp op, Value lhs, Value rhs) {
    if (!lhs.isConstant() || !rhs.isConstant()) return op(lhs, rhs);
    switch (op) {
        case Add: return Value(lhs.const_val + rhs.const_val);
        case Mul: return lhs.const_val == 0 ? Value(0) : ...
        // ... etc
    }
}
```

### Conditional Simplification

**Problem**: `if (x != 0)` where x is always non-zero becomes unreachable else branch.  
**Solution**: Track data flow to detect impossible branches.

Reference: [Machine Independent Code Optimization](https://www.geeksforgeeks.org/machine-independent-code-optimization-in-compiler-design/), [Common Subexpression Elimination](https://www.geeksforgeeks.org/compiler-design/common-subexpression-elimination-code-optimization-technique-in-compiler-design/), [Dead Code Elimination](https://en.wikipedia.org/wiki/Dead-code-elimination)

---

## 5. Control Flow Structuring: Semantic-Preserving Structural Analysis

### Two Modern Approaches

#### A. Structural Analysis (Semantic-Preserving, CMU 2013)

**Paper**: "Native x86 Decompilation Using Semantics-Preserving Structural Analysis and Iterative Control-Flow Structuring" (Schwartz et al., USENIX Security 2013)

**Idea**: Iteratively identify and eliminate structured regions (loops, conditionals) from the CFG, transforming them into high-level constructs while preserving semantics.

**Algorithm**:
1. Find **interval** (maximal single-entry, single-exit subgraph)
2. Classify interval as loop, if-then, if-then-else, etc.
3. Replace interval with single node (abstraction)
4. Repeat until CFG is single node

**Advantages**:
- **Preserves semantics** throughout transformation
- **Handles complex nesting** well
- **Produces readable output** without gotos

**Limitations**:
- Requires multiple iterations (expensive)
- Sensitive to irreducible CFGs (rare in compiler output, but exist)

#### B. Pattern-Based Structuring (DREAM, NDSS 2015)

**Paper**: "No More Gotos: Decompilation Using Pattern-Independent Control-Flow Structuring"

**Idea**: Instead of schema (known compiler patterns), use pattern-independent algorithm to eliminate gotos and recover structures.

**Advantages**:
- Handles obfuscated binaries with unusual CFG patterns
- Doesn't rely on pattern database

**Trade-off**: Slower, more complex implementation

### Why This Matters for AURA

- **Current AURA**: Simple DFS-based control flow recovery (Task 5.4), likely produces gotos
- **Problem**: Gotos obscure intent, hard to read
- **Opportunity**: Implement iterative structural analysis post-CFG recovery

### AURA Application (Post-Phase 5)

1. **Phase 5**: Current CFG recovery + goto output ✓
2. **Phase 6+**: Add structural analysis pass:
   - Identify intervals (dominance-based)
   - Classify as loop/if/switch
   - Emit while/for/if instead of gotos

Example:
```cpp
// CFG with gotos (Phase 5 output)
Label_0x1000:
    cmp eax, 0
    jne Label_0x2000
    // ... code
    jmp Label_0x3000
Label_0x2000:
    // ... code
Label_0x3000:
    ret

// Structured output (Phase 6)
if (eax == 0) {
    // ... code from Label_0x1000
}
// ... code from Label_0x2000
return;
```

Reference: [Native x86 Decompilation (CMU/USENIX)](https://users.ece.cmu.edu/~dbrumley/pdf/Schwartz%20et%20al._2013_Native%20x86%20Decompilation%20using%20Semantics-Preserving%20Structural%20Analysis%20and%20Iterative%20Control-Flow%20Structuring.pdf), [No More Gotos (DREAM/NDSS)](https://net.cs.uni-bonn.de/fileadmin/ag/martini/Staff/yakdan/dream_ndss2015.pdf)

---

## 6. Type Inference: Constraint-Based vs. Heuristic

### TIE: Constraint-Based Type Reconstruction (CMU)

**Paper**: "TIE: Principled Reverse Engineering of Types in Binary Programs"

**Idea**: Collect type constraints from variable usage, solve via unification.

**Algorithm**:
1. Assign each variable/term a type variable τ
2. For each operation, generate constraint:
   - `x / y` → constraint: `typeof(x)` and `typeof(y)` must be integer, `typeof(result)` is integer
   - `x[i]` → constraint: `typeof(x)` is pointer
   - `x & y` → constraint: both must be bitvector
3. Solve constraints via unification (similar to ML type inference)

**Advantages**:
- **Sound**: Constraints guarantee type safety
- **Conservative**: Only infers types supported by evidence
- **Precise**: Better than ad-hoc heuristics

**Example**:
```c
// Binary: mov eax, [rsp+8]
//         add eax, ebx
//         mov [eax], ecx
// Constraints generated:
// - eax is loaded from memory → could be int, struct, pointer
// - eax is used in add → int or bitvector
// - eax is dereferenced (mov [eax]) → pointer
// - Resolution: eax is pointer-to-int or pointer-to-struct
```

### Current AURA Approach (Heuristic)

AURA likely uses:
- Size heuristics (1 byte = char, 4 bytes = int, 8 bytes = pointer)
- Usage heuristics (dereferenced → pointer, arithmetic → int)

**Gap**: No formal constraint solving; hard to handle ambiguous cases.

### AURA Application

**Phase 6+**: Add lightweight constraint collection:

```cpp
class TypeConstraintCollector {
    std::vector<TypeConstraint> constraints;
public:
    void visitLoad(const Expr& addr) {
        // addr must be pointer-like
        constraints.push_back(TypeConstraint::MustBePointer(addr));
    }
    void visitAdd(const Expr& lhs, const Expr& rhs, const Expr& result) {
        // All three must be numeric
        constraints.push_back(TypeConstraint::IsNumeric(lhs));
        constraints.push_back(TypeConstraint::IsNumeric(rhs));
        constraints.push_back(TypeConstraint::IsNumeric(result));
    }
    // ... more visit methods
    
    std::map<Variable, Type> solveConstraints();
};
```

Then solve via simple unification (not full ML-style, but better than pure heuristics).

Reference: [TIE Paper](https://www.ndss-symposium.org/wp-content/uploads/2017/09/lee.pdf), [Type Inference for Decompiled Code](https://www.binarly.io/blog/type-inference-for-decompiled-code-from-hidden-semantics-to-structured-insights)

---

## 7. Implementation Roadmap for AURA

### Phase 5 (Current): Foundation

- [x] CFG recovery
- [ ] Basic control flow output (gotos acceptable)
- [ ] Function call graph

### Phase 6 (Recommended): Optimization Framework

1. **IL Hierarchy**: Introduce Level 2 IL (SSA + structured variables)
2. **Optimization Passes**:
   - Copy propagation
   - Constant folding
   - Conditional simplification
   - Dead code elimination (refinement)
3. **Control Flow Structuring**: Replace gotos with if/while/for

### Phase 7+: Advanced Type & Analysis

4. **Type Inference**: Constraint-based collection + solving
5. **Semantic Lifting**: Formalize instruction semantics (optional, post-MVP)

---

## 8. Key Takeaways

| Insight | AURA Implication | Effort |
|---------|-----------------|--------|
| **IL hierarchy** | Separate concerns into 3 levels | Medium (refactor) |
| **Optimization passes** | Create pluggable pass framework | Low (new module) |
| **Copy propagation** | Eliminates intermediate variables | Low (algorithm) |
| **Structural analysis** | Removes gotos post-CFG | Medium (new pass) |
| **Constraint typing** | Better type inference than heuristics | Medium (new solver) |

### Immediate Next Steps (Phase 6)

1. **Copy Propagation Pass**: Implement, test on sample binaries
2. **Constant Folding Pass**: Extend to bitwise, comparison ops
3. **Optimization Pipeline**: Wire passes together in fixed order
4. **Metrics**: Measure output readability (variable count, expression complexity)

---

## References

- [Binary Ninja BNIL Overview](https://docs.binary.ninja/dev/bnil-overview.html)
- [Binary Ninja MLIL](https://docs.binary.ninja/dev/bnil-mlil.html)
- [Ghidra SLEIGH Documentation](https://github.com/NationalSecurityAgency/ghidra/blob/master/Ghidra/Features/Decompiler/src/main/doc/sleigh.xml)
- [RetDec GitHub](https://github.com/avast/retdec)
- [RetDec Optimization Passes](https://decompy.github.io/DecomPy/docs/html/Documentation/4_DecompilerInformation/1_HowDecompilersWork/2_OptimizationPassesInRetdec.html)
- [CMU Phoenix: Native x86 Decompilation (USENIX 2013)](https://users.ece.cmu.edu/~dbrumley/pdf/Schwartz%20et%20al._2013_Native%20x86%20Decompilation%20using%20Semantics-Preserving%20Structural%20Analysis%20and%20Iterative%20Control-Flow%20Structuring.pdf)
- [DREAM: No More Gotos (NDSS 2015)](https://net.cs.uni-bonn.de/fileadmin/ag/martini/Staff/yakdan/dream_ndss2015.pdf)
- [TIE: Type Inference (CMU/NDSS 2016)](https://www.ndss-symposium.org/wp-content/uploads/2017/09/lee.pdf)
- [Compiler Optimization Techniques (GeeksforGeeks)](https://www.geeksforgeeks.org/machine-independent-code-optimization-in-compiler-design/)
- [Type Inference for Decompiled Code (Binarly)](https://www.binarly.io/blog/type-inference-for-decompiled-code-from-hidden-semantics-to-structured-insights)
