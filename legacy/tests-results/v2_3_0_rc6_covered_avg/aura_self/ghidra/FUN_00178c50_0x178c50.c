
bool FUN_00178c50(long *param_1,uint param_2,uint param_3)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  if (param_1 == (long *)0x0) {
    return false;
  }
  if (param_2 == param_3) {
    return (bool)2;
  }
  uVar3 = param_2;
  if (param_2 < param_3) {
    uVar3 = param_3;
  }
  if (uVar3 < *(uint *)(param_1 + 2)) {
    lVar2 = *param_1;
    uVar3 = *(uint *)(lVar2 + (ulong)param_2 * 4);
    if (param_2 != uVar3) {
      do {
        uVar1 = (ulong)param_2;
        param_2 = *(uint *)(lVar2 + (ulong)uVar3 * 4);
        *(uint *)(lVar2 + uVar1 * 4) = param_2;
        uVar3 = *(uint *)(lVar2 + (ulong)param_2 * 4);
      } while (uVar3 != param_2);
    }
    uVar3 = *(uint *)(lVar2 + (ulong)param_3 * 4);
    if (param_3 != uVar3) {
      do {
        uVar1 = (ulong)param_3;
        param_3 = *(uint *)(lVar2 + (ulong)uVar3 * 4);
        *(uint *)(lVar2 + uVar1 * 4) = param_3;
        uVar3 = *(uint *)(lVar2 + (ulong)param_3 * 4);
      } while (uVar3 != param_3);
    }
    return param_3 == param_2;
  }
  return false;
}

