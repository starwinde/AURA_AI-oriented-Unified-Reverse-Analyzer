
char * FUN_001e5370(long param_1,uint param_2)

{
  if (0xf5 < param_2) {
    return (char *)0x0;
  }
  if (param_2 == 0x19) {
    if ((*(uint *)(param_1 + 4) >> 2 & 1) != 0) {
      return "eflags";
    }
    if ((*(uint *)(param_1 + 4) >> 3 & 1) != 0) {
      return "rflags";
    }
  }
  return *(char **)(&DAT_005f5968 + (ulong)param_2 * 0x10);
}

