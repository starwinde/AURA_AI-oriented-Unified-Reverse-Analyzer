/* AURA D-29A — argv one-shot mode entry.
 *
 * Frozen 5-stage flow + log emission contract — see
 * ~/.claude/plans/d29-decoder-design-plan-turn-lively-brooks.md
 * §"argv 인자 사양 Fixation Amendment" + §"Implementation 진입 전 검증 조건".
 *
 * Apache 2.0 (matches Ghidra upstream).
 */
#include "aura_argv_mode.hh"
#include "raw_arch.hh"
#include "loadimage.hh"
#include "marshal.hh"
#include "funcdata.hh"
#include "block.hh"
#include "libdecomp.hh"
#include "sleigh_arch.hh"     /* SleighArchitecture::scanForSleighDirectories */
#include "ghidra_process.hh"  /* ELEM_DOC */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

namespace ghidra {

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ostringstream;

/* Frozen exit codes (D-29A contract). */
enum AuraExit {
  AURA_EXIT_OK         = 0,
  AURA_EXIT_ARGV       = 1,
  AURA_EXIT_LOAD       = 2,
  AURA_EXIT_ADDR       = 3,
  AURA_EXIT_ARCH       = 4,
  AURA_EXIT_DECOMPILE  = 5,
  AURA_EXIT_IO         = 6,
};

/* Frozen 5-stage stderr log. AURA-side logger parses by prefix regex
 * `^\[(load|arch-init|address-map|decompile|xml-emit)\] (ok|fail):? (.*)$`. */
static void log_ok(const char *stage, const string &detail) {
  cerr << '[' << stage << "] ok " << detail << '\n';
  cerr.flush();
}
static void log_fail(const char *stage, const string &reason) {
  cerr << '[' << stage << "] fail: " << reason << '\n';
  cerr.flush();
}

struct Args {
  string binary_path;
  string addr_str;
  string arch_override;
  string sla_dir_override;
  string cspec_override;
  string pspec_override;
  string out_format;
  bool show_help;
  bool show_version;
  Args() : out_format("xml"), show_help(false), show_version(false) {}
};

static const char *USAGE =
    "aura-decompile - AURA-bridge mode for Ghidra decompiler\n"
    "\n"
    "Usage:\n"
    "  aura-decompile --decompile <path> --addr <hex> [options]\n"
    "  aura-decompile --help\n"
    "  aura-decompile --version\n"
    "  aura-decompile                 (legacy subprocess mode for Ghidra Java client)\n"
    "\n"
    "Required (argv mode):\n"
    "  --decompile <path>   Binary file to decompile (ELF; PE/Mach-O not yet supported)\n"
    "  --addr <hex>         Function entry address (hex, 0x prefix optional)\n"
    "\n"
    "Optional (argv mode):\n"
    "  --arch <name>        Force architecture: x86-64, aarch64 (default: auto from ELF)\n"
    "  --sla-dir <dir>      Directory containing .sla files (default: $AURA_GHIDRA_SLA_DIR)\n"
    "  --cspec <path>       Explicit cspec file (default: derived from --arch)\n"
    "  --pspec <path>       Explicit pspec file (default: derived from --arch)\n"
    "  --out-format <fmt>   Output format: xml (default: xml)\n"
    "\n"
    "Output:\n"
    "  stdout - XmlEncode XML document on success (exit 0); empty on failure\n"
    "  stderr - 5-stage diagnostic log + warnings (line-oriented)\n"
    "\n"
    "Exit codes:\n"
    "  0  decompile succeeded, XML on stdout\n"
    "  1  argv parse failure\n"
    "  2  binary load failure (path / format / permission / e_machine)\n"
    "  3  function address invalid (parse / not in code / not function entry)\n"
    "  4  Architecture build failure (.sla / cspec / pspec missing or invalid)\n"
    "  5  decompile exception (Ghidra LowlevelError / XmlError)\n"
    "  6  I/O error during stdout/stderr write\n";

static const char *VERSION_STRING =
    "aura-decompile 0.1.0 (ghidra 12.0.4)";

/* Parse argv into Args. Returns AURA_EXIT_OK on success or AURA_EXIT_ARGV.
 * Supports both "--flag value" and "--flag=value". Duplicate flags take
 * the last value (with stderr warning). Unknown flags fail. */
static int parse_args(int argc, char **argv, Args &out) {
  for (int i = 1; i < argc; ++i) {
    string flag = argv[i];
    string value;
    bool has_value = false;
    size_t eq = flag.find('=');
    if (eq != string::npos) {
      value = flag.substr(eq + 1);
      flag = flag.substr(0, eq);
      has_value = true;
    }
    /* Lambda would be cleanest but C++11 here — explicit local helper. */
    bool need_value =
        (flag == "--decompile" || flag == "--addr" ||
         flag == "--arch" || flag == "--sla-dir" ||
         flag == "--cspec" || flag == "--pspec" ||
         flag == "--out-format");
    if (need_value && !has_value) {
      if (i + 1 >= argc) {
        log_fail("argv", flag + " requires a value");
        return AURA_EXIT_ARGV;
      }
      value = argv[++i];
    }

    if (flag == "--help") {
      out.show_help = true;
    } else if (flag == "--version") {
      out.show_version = true;
    } else if (flag == "--decompile") {
      out.binary_path = value;
    } else if (flag == "--addr") {
      out.addr_str = value;
    } else if (flag == "--arch") {
      out.arch_override = value;
    } else if (flag == "--sla-dir") {
      out.sla_dir_override = value;
    } else if (flag == "--cspec") {
      out.cspec_override = value;
    } else if (flag == "--pspec") {
      out.pspec_override = value;
    } else if (flag == "--out-format") {
      out.out_format = value;
      if (out.out_format != "xml") {
        log_fail("argv",
                 "--out-format only supports 'xml' (D-29A scope), got '" +
                     out.out_format + "'");
        return AURA_EXIT_ARGV;
      }
    } else {
      log_fail("argv", "unknown flag: " + flag);
      return AURA_EXIT_ARGV;
    }
  }

  if (out.show_help || out.show_version) return AURA_EXIT_OK;
  if (out.binary_path.empty()) {
    log_fail("argv", "missing --decompile <path>");
    return AURA_EXIT_ARGV;
  }
  if (out.addr_str.empty()) {
    log_fail("argv", "missing --addr <hex>");
    return AURA_EXIT_ARGV;
  }
  return AURA_EXIT_OK;
}

/* Parse hex string (with optional 0x prefix) into uint64_t. */
static bool parse_addr_hex(const string &s, uint64_t &out) {
  if (s.empty()) return false;
  size_t pos = 0;
  if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) pos = 2;
  if (pos == s.size()) return false;
  uint64_t val = 0;
  for (; pos < s.size(); ++pos) {
    char c = s[pos];
    int d;
    if (c >= '0' && c <= '9') d = c - '0';
    else if (c >= 'a' && c <= 'f') d = 10 + (c - 'a');
    else if (c >= 'A' && c <= 'F') d = 10 + (c - 'A');
    else return false;
    if (val > (UINT64_MAX >> 4)) return false;
    val = (val << 4) | (uint64_t)d;
  }
  out = val;
  return true;
}

/* Sniff ELF64 LE header — extract e_machine and compute the
 * adjustvma = (first PT_LOAD).p_vaddr - p_offset so RawLoadImage
 * (which reads file bytes at offset N) maps to vma adjustvma+N. */
static bool sniff_elf(const string &path, uint16_t &out_e_machine,
                      long &out_adjustvma, string &err) {
  std::ifstream f(path.c_str(), std::ios::binary);
  if (!f) { err = "cannot open file"; return false; }
  unsigned char ident[16];
  f.read((char *)ident, 16);
  if (!f || ident[0] != 0x7F || ident[1] != 'E' ||
      ident[2] != 'L' || ident[3] != 'F') {
    err = "not an ELF file (bad magic)";
    return false;
  }
  if (ident[4] != 2) { err = "only ELF64 supported (D-29A scope)"; return false; }
  if (ident[5] != 1) { err = "only little-endian supported (D-29A scope)"; return false; }

  /* ELF64 header layout (after 16-byte e_ident, hdr[] indices below):
   *   hdr[0..1]   e_type
   *   hdr[2..3]   e_machine
   *   hdr[4..7]   e_version
   *   hdr[8..15]  e_entry
   *   hdr[16..23] e_phoff
   *   hdr[24..31] e_shoff
   *   hdr[32..35] e_flags
   *   hdr[36..37] e_ehsize
   *   hdr[38..39] e_phentsize
   *   hdr[40..41] e_phnum
   *   hdr[42..43] e_shentsize
   *   hdr[44..45] e_shnum
   *   hdr[46..47] e_shstrndx
   */
  unsigned char hdr[64 - 16];
  f.read((char *)hdr, sizeof hdr);
  if (!f) { err = "ELF header truncated"; return false; }
  uint16_t e_machine = (uint16_t)hdr[2] | ((uint16_t)hdr[3] << 8);
  uint64_t e_phoff = 0;
  for (int i = 0; i < 8; ++i) e_phoff |= (uint64_t)hdr[16 + i] << (8 * i);
  uint16_t e_phentsize = (uint16_t)hdr[38] | ((uint16_t)hdr[39] << 8);
  uint16_t e_phnum     = (uint16_t)hdr[40] | ((uint16_t)hdr[41] << 8);

  if (e_phentsize < 56 || e_phentsize > 1024 || e_phnum == 0) {
    err = "implausible Phdr table layout";
    return false;
  }

  vector<unsigned char> ph(e_phentsize);
  for (uint16_t i = 0; i < e_phnum; ++i) {
    f.seekg((std::streamoff)(e_phoff + (uint64_t)i * e_phentsize));
    f.read((char *)ph.data(), e_phentsize);
    if (!f) { err = "Phdr table truncated"; return false; }
    /* ELF64 Phdr layout:
     *   ph[0..3]   p_type
     *   ph[4..7]   p_flags
     *   ph[8..15]  p_offset
     *   ph[16..23] p_vaddr
     *   ph[24..31] p_paddr
     *   ph[32..39] p_filesz
     *   ph[40..47] p_memsz
     *   ph[48..55] p_align
     */
    uint32_t p_type = (uint32_t)ph[0] | ((uint32_t)ph[1] << 8) |
                      ((uint32_t)ph[2] << 16) | ((uint32_t)ph[3] << 24);
    if (p_type != 1 /* PT_LOAD */) continue;
    uint64_t p_offset = 0, p_vaddr = 0;
    for (int j = 0; j < 8; ++j) p_offset |= (uint64_t)ph[8 + j]  << (8 * j);
    for (int j = 0; j < 8; ++j) p_vaddr  |= (uint64_t)ph[16 + j] << (8 * j);
    out_adjustvma = (long)((int64_t)p_vaddr - (int64_t)p_offset);
    out_e_machine = e_machine;
    return true;
  }
  err = "no PT_LOAD segment in ELF";
  return false;
}

/* Map ELF e_machine to D-29A-supported (arch_name, target_id). */
static bool e_machine_to_target(uint16_t e_machine, string &out_arch,
                                string &out_target_id) {
  switch (e_machine) {
    case 62:   /* EM_X86_64 */
      out_arch = "x86-64";
      out_target_id = "x86:LE:64:default";
      return true;
    case 183:  /* EM_AARCH64 */
      out_arch = "aarch64";
      out_target_id = "AARCH64:LE:64:v8A";
      return true;
    default:
      return false;
  }
}

static bool arch_to_target(const string &arch, string &out_target_id) {
  if (arch == "x86-64" || arch == "x86_64") {
    out_target_id = "x86:LE:64:default";
    return true;
  }
  if (arch == "aarch64" || arch == "AARCH64") {
    out_target_id = "AARCH64:LE:64:v8A";
    return true;
  }
  return false;
}

/* Compute extra spec-search paths for SleighArchitecture (specpaths).
 *
 * Each path in the returned list is added verbatim (NOT recursively
 * scanned) — caller passes them to startDecompilerLibrary(extrapaths).
 * That contract differs from scanForSleighDirectories which assumes
 * upstream Ghidra's "Ghidra/Processors/<arch>/data/" hierarchy, which
 * the vendored AURA layout (`processors/<arch>/languages/`) does not
 * follow.
 *
 * Includes:
 *   - .sla output dir (--sla-dir / $AURA_GHIDRA_SLA_DIR / built-in fallback)
 *   - per-arch language dirs from $AURA_GHIDRA_PROCESSORS_DIR
 *     (currently x86 + AARCH64 — extend as more arches enter scope)
 */
static vector<string> compute_specpaths(const Args &a) {
  vector<string> paths;
  if (!a.sla_dir_override.empty()) {
    paths.push_back(a.sla_dir_override);
  } else if (const char *env = getenv("AURA_GHIDRA_SLA_DIR")) {
    paths.push_back(env);
  }
  if (const char *env = getenv("AURA_GHIDRA_PROCESSORS_DIR")) {
    string base = env;
    paths.push_back(base + "/x86/languages");
    paths.push_back(base + "/AARCH64/languages");
  }
  return paths;
}

int aura_argv_mode_entry(int argc, char **argv) {
  Args a;
  int parse_rc = parse_args(argc, argv, a);
  if (parse_rc != AURA_EXIT_OK) return parse_rc;

  if (a.show_help) {
    cout << USAGE << std::flush;
    return AURA_EXIT_OK;
  }
  if (a.show_version) {
    cout << VERSION_STRING << '\n' << std::flush;
    return AURA_EXIT_OK;
  }

  /* Stage 1: load — verify path + ELF magic + e_machine. */
  uint16_t e_machine = 0;
  long adjustvma = 0;
  {
    string err;
    if (!sniff_elf(a.binary_path, e_machine, adjustvma, err)) {
      log_fail("load", err + " (path=" + a.binary_path + ")");
      return AURA_EXIT_LOAD;
    }
    ostringstream s;
    s << "path=" << a.binary_path << " e_machine=" << e_machine;
    log_ok("load", s.str());
  }

  /* Stage 2: arch-init — pick target id + library init + Architecture init. */
  string arch_name, target_id;
  if (!a.arch_override.empty()) {
    arch_name = a.arch_override;
    if (!arch_to_target(arch_name, target_id)) {
      log_fail("arch-init", "unsupported --arch value: " + arch_name);
      return AURA_EXIT_ARCH;
    }
  } else if (!e_machine_to_target(e_machine, arch_name, target_id)) {
    /* e_machine unrecognized — categorize as load failure (we did parse
     * the ELF header, but e_machine is not in D-29A scope). */
    ostringstream s;
    s << "unsupported e_machine: " << e_machine;
    log_fail("load", s.str());
    return AURA_EXIT_LOAD;
  }

  vector<string> extrapaths = compute_specpaths(a);
  startDecompilerLibrary(extrapaths);

  Architecture *conf = (Architecture *)0;
  try {
    conf = new RawBinaryArchitecture(a.binary_path, target_id, &cerr);
    DocumentStorage store;
    conf->init(store);
    if (adjustvma != 0 && conf->loader != (LoadImage *)0) {
      conf->loader->adjustVma(adjustvma);
    }
  } catch (LowlevelError &e) {
    if (conf) delete conf;
    log_fail("arch-init", e.explain);
    return AURA_EXIT_ARCH;
  } catch (DecoderError &e) {
    if (conf) delete conf;
    log_fail("arch-init", e.explain);
    return AURA_EXIT_ARCH;
  }
  {
    ostringstream s;
    s << "arch=" << arch_name << " target=" << target_id
      << " adjustvma=0x" << std::hex << adjustvma;
    log_ok("arch-init", s.str());
  }

  /* Stage 3: address-map — parse addr + create function symbol. */
  uint64_t addr_value = 0;
  if (!parse_addr_hex(a.addr_str, addr_value)) {
    delete conf;
    log_fail("address-map",
             "addr parse failed (addr=" + a.addr_str + ")");
    return AURA_EXIT_ADDR;
  }
  Funcdata *fd = (Funcdata *)0;
  try {
    Address addr(conf->getDefaultCodeSpace(), addr_value);
    string name;
    conf->nameFunction(addr, name);
    string basename;
    Scope *scope = conf->symboltab->findCreateScopeFromSymbolName(
        name, "::", basename, (Scope *)0);
    fd = scope->addFunction(addr, name)->getFunction();
  } catch (LowlevelError &e) {
    delete conf;
    log_fail("address-map", e.explain);
    return AURA_EXIT_ADDR;
  }
  if (fd == (Funcdata *)0) {
    delete conf;
    ostringstream s;
    s << "no function created at addr=0x" << std::hex << addr_value;
    log_fail("address-map", s.str());
    return AURA_EXIT_ADDR;
  }
  {
    ostringstream s;
    s << "addr=0x" << std::hex << addr_value << " name=" << fd->getName();
    log_ok("address-map", s.str());
  }

  /* Stage 4: decompile — run actions. */
  try {
    conf->allacts.getCurrent()->reset(*fd);
    conf->allacts.getCurrent()->perform(*fd);
  } catch (LowlevelError &e) {
    delete conf;
    log_fail("decompile", e.explain);
    return AURA_EXIT_DECOMPILE;
  } catch (DecoderError &e) {
    delete conf;
    log_fail("decompile", e.explain);
    return AURA_EXIT_DECOMPILE;
  }
  /* Verification condition 1: at least one BB. */
  int bb_count = fd->getBasicBlocks().getSize();
  if (bb_count == 0) {
    delete conf;
    log_fail("decompile", "no basic blocks produced");
    return AURA_EXIT_DECOMPILE;
  }
  {
    ostringstream s;
    s << "bb_count=" << bb_count;
    log_ok("decompile", s.str());
  }

  /* Stage 5: xml-emit — write XmlEncode (doFormat=false) to stdout.
   * No envelope, no burst marker, no progress text on stdout.
   * savetree=true emits the full syntax tree (basic blocks + p-code
   * ops), required by D-29B HIR mapping. D-29A turn #3 verification
   * checks the produced structure satisfies the user checklist
   * (function boundary / BB structure / pcode op / call expression /
   * varnode / highsymbol). */
  std::streampos before = cout.tellp();
  try {
    XmlEncode encoder(cout, false);
    encoder.openElement(ELEM_DOC);
    fd->encode(encoder, 0, true);
    encoder.closeElement(ELEM_DOC);
    cout.flush();
  } catch (LowlevelError &e) {
    delete conf;
    log_fail("xml-emit", e.explain);
    return AURA_EXIT_IO;
  } catch (DecoderError &e) {
    delete conf;
    log_fail("xml-emit", e.explain);
    return AURA_EXIT_IO;
  }
  if (!cout) {
    delete conf;
    log_fail("xml-emit", "stdout write failed");
    return AURA_EXIT_IO;
  }
  {
    std::streampos after = cout.tellp();
    ostringstream s;
    s << "bytes=" << (long long)(after - before);
    log_ok("xml-emit", s.str());
  }

  delete conf;
  return AURA_EXIT_OK;
}

}  /* namespace ghidra */
