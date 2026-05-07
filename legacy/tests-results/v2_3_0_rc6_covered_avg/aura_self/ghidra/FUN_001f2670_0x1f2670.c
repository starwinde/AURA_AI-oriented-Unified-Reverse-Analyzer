
int FUN_001f2670(uint param_1,byte param_2)

{
  int iVar1;
  
  if (((param_1 == 0) || (param_1 == 0xb)) || (param_1 == 0xc)) {
    iVar1 = 0;
  }
  else if (param_1 < 0x14) {
    if ((uint)(*(int *)(&DAT_0058d07c + (ulong)param_1 * 0xc) -
              *(int *)(&DAT_0058d078 + (ulong)param_1 * 0xc)) < (uint)param_2) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(&DAT_0058d078 + (ulong)param_1 * 0xc) + (uint)param_2;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

