
bool FUN_001902c4(long param_1,ulong param_2)

{
  return *(char *)(param_1 + (param_2 & 0xffffffff) + 0x336) != -1;
}

