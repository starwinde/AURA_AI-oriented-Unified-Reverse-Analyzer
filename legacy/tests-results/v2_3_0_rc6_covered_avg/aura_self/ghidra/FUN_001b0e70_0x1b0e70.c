
void FUN_001b0e70(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  
  uVar4 = FUN_0018ffd0();
  iVar2 = FUN_00190080();
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x335) = 1;
    FUN_00190370(param_3,&DAT_001fd610);
    return;
  }
  FUN_00190370(param_3,", ");
  lVar7 = *(long *)(param_1 + 800);
  FUN_00190080(uVar4);
  uVar5 = (**(code **)(lVar7 + 0x78))();
  FUN_00190370(param_3,uVar5);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(undefined4 *)(lVar7 + (ulong)*(byte *)(lVar7 + 0x80) * 0x30 + 0x94) = 1;
  uVar3 = FUN_00190080(uVar4);
  lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar1 = *(byte *)(lVar6 + 0x80);
  lVar7 = lVar6 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
  *(undefined4 *)(lVar7 + 0x98) = uVar3;
  *(undefined1 *)(lVar7 + 0xb1) = 1;
  *(byte *)(lVar6 + 0x80) = bVar1 + 1;
  return;
}

