
void FUN_001b2c50(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  
  uVar4 = FUN_0018ffd0();
  uVar5 = FUN_0018ffd0(param_1,param_2 + 1);
  lVar9 = *(long *)(param_1 + 800);
  FUN_00190080(uVar4);
  uVar6 = (**(code **)(lVar9 + 0x78))();
  FUN_00190370(param_3,uVar6);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30 + 0x94) = 1;
    uVar3 = FUN_00190080(uVar4);
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    lVar9 = lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar9 + 0x98) = uVar3;
    *(undefined1 *)(lVar9 + 0xb1) = 1;
    *(byte *)(lVar8 + 0x80) = bVar1 + 1;
  }
  uVar2 = FUN_001900a0(uVar5);
  uVar7 = FUN_001900a0(uVar5);
  if (((uVar2 & 7) != 0) && ((uVar7 >> 3 & 0x1fffffff) != 0 || (uVar2 & 7) != 2)) {
    FUN_001b2a84(param_1,param_3,uVar2 & 7);
    return;
  }
  return;
}

