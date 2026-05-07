
undefined1 * lookupExactFPImmByEnum(ushort param_1)

{
  if (param_1 < 4) {
    return ExactFPImmsList + (ulong)*(uint *)(Index_0 + (ulong)param_1 * 8 + 4) * 0x18;
  }
  return (undefined1 *)0x0;
}

