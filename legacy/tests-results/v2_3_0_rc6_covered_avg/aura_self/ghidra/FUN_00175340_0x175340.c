
long FUN_00175340(long *param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  long lVar5;
  
  if ((param_1 != (long *)0x0) && (lVar5 = *param_1, lVar5 != 0)) {
    uVar4 = *(uint *)(param_1 + 1);
    if (uVar4 != 0) {
      uVar2 = 0;
      do {
        uVar1 = uVar2 + (uVar4 - uVar2 >> 1);
        uVar3 = *(ulong *)(lVar5 + (ulong)uVar1 * 0x20);
        if (uVar3 < param_2) {
          uVar2 = uVar1 + 1;
        }
        else {
          uVar4 = uVar1;
          if (uVar3 <= param_2) {
            return lVar5 + (ulong)uVar1 * 0x20;
          }
        }
      } while (uVar2 < uVar4);
    }
  }
  return 0;
}

