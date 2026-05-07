
ulong FUN_0015ad14(long *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  uint *puVar8;
  
  uVar2 = *(uint *)(param_1 + 1);
  lVar5 = *param_1 + (ulong)param_2 * 0x50;
  uVar3 = *(uint *)(lVar5 + 0x20);
  if (uVar3 != 0) {
    puVar8 = *(uint **)(lVar5 + 0x18);
    puVar1 = puVar8 + uVar3;
    do {
      uVar3 = *puVar8;
      if ((param_2 != uVar3) && (uVar3 < uVar2)) {
        uVar7 = 0;
        uVar6 = (ulong)uVar3;
        while( true ) {
          uVar7 = uVar7 + 1;
          uVar4 = *(uint *)(*param_1 + uVar6 * 0x50 + 0x34);
          if ((uVar4 == (uint)uVar6) || (uVar2 < uVar7)) break;
          uVar6 = (ulong)uVar4;
          if (param_2 == uVar4) {
            return (ulong)uVar3;
          }
        }
      }
      puVar8 = puVar8 + 1;
    } while (puVar1 != puVar8);
  }
  return (ulong)uVar2;
}

