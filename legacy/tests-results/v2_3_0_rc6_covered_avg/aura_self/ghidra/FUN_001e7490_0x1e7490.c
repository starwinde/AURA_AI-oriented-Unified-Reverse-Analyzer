
long FUN_001e7490(long param_1,uint param_2)

{
  if (param_2 < *(uint *)(param_1 + 0x20)) {
    return *(long *)(param_1 + 0x18) + (ulong)param_2 * 0x18;
  }
  return 0;
}

