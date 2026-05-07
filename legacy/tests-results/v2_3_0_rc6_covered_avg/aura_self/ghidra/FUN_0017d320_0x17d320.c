
uint FUN_0017d320(long *param_1,long param_2,uint param_3)

{
  uint uVar1;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return 0xffffffff;
  }
  uVar1 = 0xffffffff;
  if (param_3 < *(uint *)(param_1 + 1)) {
    uVar1 = *(uint *)(*param_1 + (ulong)param_3 * 4);
    if (param_3 == uVar1 || uVar1 == 0xffffffff) {
      return 0xffffffff;
    }
    if (*(uint *)(param_2 + 8) <= uVar1) {
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

