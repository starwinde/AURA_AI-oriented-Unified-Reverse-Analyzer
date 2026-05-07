
ulong FUN_00178d00(long *param_1,uint param_2)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  uint uVar4;
  
  if (param_1 == (long *)0x0) {
    return 0xffffffff;
  }
  uVar2 = 0xffffffff;
  if (param_2 < *(uint *)(param_1 + 2)) {
    lVar3 = *param_1;
    uVar4 = *(uint *)(lVar3 + (ulong)param_2 * 4);
    if (param_2 == uVar4) {
      return (ulong)param_2;
    }
    do {
      uVar1 = (ulong)param_2;
      param_2 = *(uint *)(lVar3 + (ulong)uVar4 * 4);
      uVar2 = (ulong)param_2;
      *(uint *)(lVar3 + uVar1 * 4) = param_2;
      uVar4 = *(uint *)(lVar3 + uVar2 * 4);
    } while (uVar4 != param_2);
  }
  return uVar2;
}

