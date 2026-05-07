
uint FUN_001e7414(long *param_1,uint param_2,uint param_3)

{
  ushort *puVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  long lVar6;
  
  lVar6 = *param_1 + (ulong)param_2 * 0x18;
  lVar5 = (ulong)*(uint *)(lVar6 + 4) * 2;
  lVar2 = param_1[6] + lVar5;
  if (lVar2 != 0) {
    uVar3 = (uint)*(ushort *)(param_1[6] + lVar5);
    if (uVar3 == 0) {
      return 0;
    }
    uVar3 = uVar3 + param_2;
    lVar5 = 0;
    do {
      puVar1 = (ushort *)(param_1[8] + (ulong)*(uint *)(lVar6 + 0xc) * 2 + lVar5);
      lVar5 = lVar5 + 2;
      if (*puVar1 == param_3) {
        return uVar3 & 0xffff;
      }
      uVar4 = (uint)*(ushort *)(lVar2 + lVar5);
      uVar3 = uVar4 + (uVar3 & 0xffff);
    } while (uVar4 != 0);
  }
  return 0;
}

