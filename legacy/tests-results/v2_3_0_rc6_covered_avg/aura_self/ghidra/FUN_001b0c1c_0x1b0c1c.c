
void FUN_001b0c1c(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  
  uVar5 = FUN_0018ffd0();
  uVar6 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar7 = FUN_0018ffd0(param_1,param_2 + 2);
  lVar9 = *(long *)(param_1 + 800);
  FUN_00190080(uVar5);
  uVar8 = (**(code **)(lVar9 + 0x78))();
  FUN_00190370(param_3,uVar8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30 + 0x94) = 1;
    uVar4 = FUN_00190080(uVar5);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar9 = lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30;
    *(undefined4 *)(lVar9 + 0x98) = uVar4;
    *(undefined1 *)(lVar9 + 0xb1) = 1;
    uVar3 = FUN_001900a0(uVar7);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar9 + 0x80);
    *(uint *)(lVar9 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x8c) = (uVar3 & 7) + 5;
    *(byte *)(lVar9 + 0x80) = bVar1 + 1;
  }
  uVar2 = FUN_001900a0(uVar7);
  uVar3 = uVar2 & 7;
  FUN_00190370(param_3,", ");
  if (uVar3 == 3) {
    FUN_00190370(param_3,&DAT_001fa828);
    goto LAB_001b0d10;
  }
  if ((uVar2 >> 2 & 1) == 0) {
    if (uVar3 == 1) {
      FUN_00190370(param_3,&DAT_001fa830);
      goto LAB_001b0d10;
    }
    if (uVar3 == 2) {
      FUN_00190370(param_3,&DAT_001fa820);
      goto LAB_001b0d10;
    }
  }
  else {
    if (uVar3 == 4) {
      FUN_00190370(param_3,"ror");
      goto LAB_001b0d10;
    }
    if (uVar3 == 5) {
      FUN_00190370(param_3,&DAT_001fdf70);
      return;
    }
  }
  FUN_00190370(param_3,&DAT_001fe648);
LAB_001b0d10:
  FUN_00190370(param_3,&DAT_001fe568);
  lVar9 = *(long *)(param_1 + 800);
  FUN_00190080(uVar6);
  uVar5 = (**(code **)(lVar9 + 0x78))();
  FUN_00190370(param_3,uVar5);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar1 = *(byte *)(lVar9 + 0x80);
  uVar4 = FUN_00190080(uVar6);
  uVar3 = bVar1 - 1;
  *(undefined4 *)
   (lVar9 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar3 << 1) + (long)(int)uVar3)
            * 0x10 + 0x90) = uVar4;
  return;
}

