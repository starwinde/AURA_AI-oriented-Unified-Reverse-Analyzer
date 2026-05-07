/* AURA D-29A — argv one-shot mode for aura-decompile.
 *
 * Vendored extension on top of upstream Ghidra ghidra_process.cc.
 * Frozen contract — see ~/.claude/plans/d29-decoder-design-plan-turn-lively-brooks.md
 * §"argv 인자 사양 Fixation Amendment".
 *
 * Apache 2.0 (matches Ghidra upstream).
 */
#ifndef __AURA_ARGV_MODE_HH__
#define __AURA_ARGV_MODE_HH__

namespace ghidra {

/* Entry point for AURA argv one-shot mode.
 *
 * Returns process exit code per the D-29A frozen contract:
 *   0 = OK, 1 = argv parse, 2 = load, 3 = addr, 4 = arch,
 *   5 = decompile, 6 = io.
 *
 * Caller (ghidra_process.cc:main()) has already verified that argv
 * contains a recognized AURA flag (--decompile / --help / --version)
 * and has performed AttributeId / ElementId / CapabilityPoint
 * initialization.
 */
int aura_argv_mode_entry(int argc, char **argv);

}  // namespace ghidra

#endif  /* __AURA_ARGV_MODE_HH__ */
