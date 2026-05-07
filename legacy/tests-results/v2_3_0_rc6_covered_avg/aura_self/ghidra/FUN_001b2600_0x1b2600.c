
void FUN_001b2600(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  
  FUN_0018ffd0();
  uVar2 = FUN_00190080();
  lVar5 = *(long *)(param_1 + 800);
  FUN_001e7414(*(undefined8 *)(param_1 + 0x3b0),uVar2,9);
  uVar4 = (**(code **)(lVar5 + 0x78))();
  FUN_00190370(param_3,uVar4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    uVar4 = *(undefined8 *)(param_1 + 0x3b0);
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar5 + (ulong)*(byte *)(lVar5 + 0x80) * 0x30 + 0x94) = 1;
    uVar3 = FUN_001e7414(uVar4,uVar2,9);
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    *(undefined4 *)(lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
    *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  }
  FUN_00190370(param_3,", ");
  lVar5 = *(long *)(param_1 + 800);
  FUN_001e7414(*(undefined8 *)(param_1 + 0x3b0),uVar2,10);
  uVar4 = (**(code **)(lVar5 + 0x78))();
  FUN_00190370(param_3,uVar4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  uVar4 = *(undefined8 *)(param_1 + 0x3b0);
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(undefined4 *)(lVar5 + (ulong)*(byte *)(lVar5 + 0x80) * 0x30 + 0x94) = 1;
  uVar2 = FUN_001e7414(uVar4,uVar2,10);
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar1 = *(byte *)(lVar5 + 0x80);
  *(undefined4 *)(lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar2;
  *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  return;
}

