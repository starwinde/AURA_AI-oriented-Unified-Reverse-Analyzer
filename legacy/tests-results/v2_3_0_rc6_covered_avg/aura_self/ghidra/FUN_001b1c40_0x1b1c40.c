
void FUN_001b1c40(long param_1,int param_2,undefined8 param_3,char param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined *puVar9;
  uint uVar10;
  uint uVar11;
  long lVar12;
  
  uVar4 = FUN_0018ffd0();
  uVar5 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar2 = FUN_001900a0();
  uVar6 = FUN_00190020(uVar4);
  if ((uVar6 & 1) == 0) {
    FUN_001b1900(param_1,param_2,param_3);
    return;
  }
  FUN_00190370(param_3,&DAT_001fdf80);
  lVar12 = *(long *)(param_1 + 800);
  FUN_00190080(uVar4);
  uVar7 = (**(code **)(lVar12 + 0x78))();
  FUN_00190370(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    bVar1 = FUN_001900a0(uVar5);
    uVar10 = (uint)bVar1;
    if (bVar1 != 0 || param_4 != '\0') goto LAB_001b1ce8;
LAB_001b1d98:
    if ((uVar2 & 0x100) == 0) goto LAB_001b1d50;
    uVar11 = 0;
    puVar9 = &DAT_001faa60;
LAB_001b1da8:
    FUN_001903f0(param_3,", #%s%u",puVar9,uVar11);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
    *(undefined4 *)(lVar12 + 0x94) = 3;
    uVar3 = FUN_00190080(uVar4);
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + 0x98) = uVar3;
    uVar4 = DAT_0020c578;
    lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30;
    *(undefined4 *)(lVar8 + 0x9c) = 0;
    *(undefined1 *)(lVar8 + 0xb1) = 1;
    *(undefined8 *)(lVar8 + 0xa0) = uVar4;
    bVar1 = FUN_001900a0(uVar5);
    uVar10 = (uint)bVar1;
    if (bVar1 == 0 && param_4 == '\0') goto LAB_001b1d98;
LAB_001b1ce8:
    uVar11 = uVar10 << 2;
    if (uVar11 < 10) {
      puVar9 = &DAT_001fe648;
      if ((uVar2 & 0x100) != 0) {
        puVar9 = &DAT_001faa60;
      }
      goto LAB_001b1da8;
    }
    puVar9 = &DAT_001fe648;
    if ((uVar2 & 0x100) != 0) {
      puVar9 = &DAT_001faa60;
    }
    FUN_001903f0(param_3,&DAT_001fdf88,puVar9,uVar11);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar12 + 0x80);
    if ((uVar2 & 0x100) == 0) {
      *(uint *)(lVar12 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0xa4) = uVar11;
    }
    else {
      *(uint *)(lVar12 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0xa4) = uVar10 * -4;
    }
  }
LAB_001b1d50:
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
  }
  return;
}

