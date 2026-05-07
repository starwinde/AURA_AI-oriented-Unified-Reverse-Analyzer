
void FUN_001b4834(long param_1,int param_2,undefined8 param_3,char param_4)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined *puVar11;
  long lVar12;
  
  FUN_0018ffd0();
  uVar6 = FUN_00190020();
  if ((uVar6 & 1) == 0) {
    FUN_001b1900(param_1,param_2,param_3);
    return;
  }
  uVar7 = FUN_0018ffd0(param_1,param_2);
  uVar8 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar9 = FUN_0018ffd0(param_1,param_2 + 2);
  uVar3 = FUN_001900a0();
  uVar3 = uVar3 & 0x100;
  FUN_00190370(param_3,&DAT_001fdf80);
  FUN_001b3500(param_1,1);
  lVar12 = *(long *)(param_1 + 800);
  FUN_00190080(uVar7);
  uVar10 = (**(code **)(lVar12 + 0x78))();
  FUN_00190370(param_3,uVar10);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar4 = FUN_00190080(uVar8);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar12 + 0x80);
    uVar5 = FUN_00190080(uVar7);
    *(undefined4 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x98) = uVar5;
    iVar4 = FUN_00190080(uVar8);
  }
  if (iVar4 != 0) {
    FUN_00190370(param_3,", ");
    puVar11 = &DAT_001fe648;
    if (uVar3 != 0) {
      puVar11 = &DAT_001faa60;
    }
    FUN_00190370(param_3,puVar11);
    lVar12 = *(long *)(param_1 + 800);
    FUN_00190080(uVar8);
    uVar7 = (**(code **)(lVar12 + 0x78))();
    FUN_00190370(param_3,uVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar12 + 0x80);
      uVar5 = FUN_00190080(uVar8);
      *(undefined4 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x9c) = uVar5;
      if (uVar3 != 0) {
        lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
        *(undefined4 *)(lVar12 + 0xa0) = 0xffffffff;
        *(undefined1 *)(lVar12 + 0xb0) = 1;
      }
    }
    goto LAB_001b4930;
  }
  bVar2 = FUN_001900a0(uVar9);
  uVar1 = (uint)bVar2;
  if (bVar2 == 0 && param_4 == '\0') {
    if (uVar3 != 0) {
      puVar11 = &DAT_001faa60;
LAB_001b4af8:
      FUN_001903f0(param_3,", #%s%u",puVar11,uVar1);
      goto LAB_001b4ab4;
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b4930;
    lVar12 = *(long *)(param_1 + 0x310);
  }
  else {
    if (uVar1 < 10) {
      puVar11 = &DAT_001faa60;
      if (uVar3 == 0) {
        puVar11 = &DAT_001fe648;
      }
      goto LAB_001b4af8;
    }
    puVar11 = &DAT_001fe648;
    if (uVar3 != 0) {
      puVar11 = &DAT_001faa60;
    }
    FUN_001903f0(param_3,&DAT_001fdf88,puVar11,uVar1);
LAB_001b4ab4:
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b4930;
    lVar12 = *(long *)(param_1 + 0x310);
    bVar2 = *(byte *)(*(long *)(lVar12 + 0xf0) + 0x80);
    if (uVar3 != 0) {
      lVar12 = *(long *)(lVar12 + 0xf0) + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(uint *)(lVar12 + 0xa4) = -uVar1;
      *(undefined1 *)(lVar12 + 0xb0) = 1;
      goto LAB_001b4930;
    }
  }
  *(uint *)(*(long *)(lVar12 + 0xf0) + (ulong)*(byte *)(*(long *)(lVar12 + 0xf0) + 0x80) * 0x30 +
           0xa4) = uVar1;
LAB_001b4930:
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar12 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar12 = *(long *)(lVar12 + 0xf0);
    *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
  }
  return;
}

