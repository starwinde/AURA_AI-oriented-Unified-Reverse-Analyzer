
undefined4 sa_postdom_dominates(long *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  uVar4 = param_2;
  if (param_2 < param_3) {
    uVar4 = param_3;
  }
  if (uVar4 < *(uint *)(param_1 + 1)) {
    if (param_2 == param_3) {
      return 1;
    }
    uVar3 = *(uint *)(*param_1 + (ulong)param_3 * 4);
    uVar4 = 0;
    if (uVar3 == 0xffffffff || param_3 == uVar3) {
      return 0;
    }
    do {
      uVar4 = uVar4 + 1;
      if (*(uint *)(param_1 + 1) < uVar4) {
        return 0;
      }
      if (param_2 == uVar3) {
        return 1;
      }
      uVar1 = *(uint *)(*param_1 + (ulong)uVar3 * 4);
      bVar2 = uVar1 != uVar3;
      uVar3 = uVar1;
    } while (bVar2 && uVar1 != 0xffffffff);
  }
  return 0;
}

