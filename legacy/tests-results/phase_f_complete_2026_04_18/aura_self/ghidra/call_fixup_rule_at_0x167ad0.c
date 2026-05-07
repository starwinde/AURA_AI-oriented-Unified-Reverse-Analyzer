
undefined ** call_fixup_rule_at(uint param_1)

{
  undefined **ppuVar1;
  
  ppuVar1 = &s_builtin_rules + (ulong)param_1 * 2;
  if (0x1d < param_1) {
    ppuVar1 = (undefined **)0x0;
  }
  return ppuVar1;
}

