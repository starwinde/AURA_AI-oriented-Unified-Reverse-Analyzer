
void FUN_001b3dd0(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  
  uVar4 = FUN_0018ffd0();
  uVar5 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar6 = FUN_0018ffd0(param_1,param_2 + 2);
  FUN_00190370(param_3,&DAT_001fdf80);
  FUN_001b3500(param_1,1);
  lVar8 = *(long *)(param_1 + 800);
  FUN_00190080(uVar4);
  uVar7 = (**(code **)(lVar8 + 0x78))();
  FUN_00190370(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar3 = FUN_00190080(uVar4);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
  }
  FUN_00190370(param_3,", ");
  lVar8 = *(long *)(param_1 + 800);
  FUN_00190080(uVar5);
  uVar4 = (**(code **)(lVar8 + 0x78))();
  FUN_00190370(param_3,uVar4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar3 = FUN_00190080(uVar5);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar3;
  }
  iVar2 = FUN_001900a0(uVar6);
  if (iVar2 != 0) {
    FUN_00190370(param_3,", lsl ");
    FUN_001903f0(param_3,&DAT_001fdd78,iVar2);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30;
      *(undefined4 *)(lVar8 + 0x8c) = 2;
      *(int *)(lVar8 + 0x90) = iVar2;
    }
  }
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar8 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar8 = *(long *)(lVar8 + 0xf0);
    *(char *)(lVar8 + 0x80) = *(char *)(lVar8 + 0x80) + '\x01';
  }
  return;
}

