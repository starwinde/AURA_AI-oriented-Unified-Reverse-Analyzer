
uint FUN_00190310(byte *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(long *)(param_1 + 8) + (ulong)param_2 * 8 + 4);
  if (param_2 < *param_1) {
    uVar1 = uVar2 >> (ulong)((param_3 + 1) * 4 & 0x1f) & 0xf;
    if ((1 << (ulong)(param_3 & 0x1f) & uVar2) == 0) {
      uVar1 = 0xffffffff;
    }
    return uVar1;
  }
  return 0xffffffff;
}

