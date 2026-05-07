
void FUN_001b2d64(long param_1,int param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long lVar7;
  ulong uVar8;
  
  uVar5 = FUN_0018ffd0();
  uVar6 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar3 = FUN_00190080(uVar5);
  uVar5 = (**(code **)(*(long *)(param_1 + 800) + 0x78))();
  FUN_00190370(param_3,uVar5);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar7 + 0x80);
    lVar1 = lVar7 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 1;
    *(undefined4 *)(lVar1 + 0x98) = uVar3;
    *(undefined1 *)(lVar1 + 0xb1) = 1;
    *(byte *)(lVar7 + 0x80) = bVar2 + 1;
  }
  uVar4 = FUN_001900a0(uVar6);
  uVar8 = FUN_001900a0(uVar6);
  if (((uVar4 & 7) != 0) && ((uVar8 >> 3 & 0x1fffffff) != 0 || (uVar4 & 7) != 2)) {
    FUN_001b2a84(param_1,param_3,uVar4 & 7);
    return;
  }
  return;
}

