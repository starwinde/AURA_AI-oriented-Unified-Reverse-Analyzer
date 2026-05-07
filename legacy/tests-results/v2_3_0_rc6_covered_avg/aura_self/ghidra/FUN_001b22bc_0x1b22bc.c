
void FUN_001b22bc(long param_1,int param_2,undefined8 param_3)

{
  undefined *puVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  
  uVar7 = FUN_0018ffd0();
  uVar8 = FUN_0018ffd0(param_1,param_2 + 1);
  uVar3 = FUN_001900a0();
  uVar3 = uVar3 & 0x100;
  iVar4 = FUN_00190080(uVar7);
  if (iVar4 == 0) {
    uVar5 = FUN_001900a0(uVar8);
    uVar5 = uVar5 & 0xff;
    puVar1 = &DAT_001fe648;
    if (uVar3 != 0) {
      puVar1 = &DAT_001faa60;
    }
    if (uVar5 < 10) {
      FUN_001903f0(param_3,"#%s%u",puVar1,uVar5);
    }
    else {
      FUN_001903f0(param_3,"#%s0x%x",puVar1,uVar5);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar9 + 0x80);
      lVar10 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar10 + 0x94) = 2;
      *(uint *)(lVar10 + 0x98) = uVar5;
      *(bool *)(lVar10 + 0xb0) = uVar3 != 0;
      *(byte *)(lVar9 + 0x80) = bVar2 + 1;
      return;
    }
  }
  else {
    puVar1 = &DAT_001fe648;
    if (uVar3 != 0) {
      puVar1 = &DAT_001faa60;
    }
    FUN_00190370(param_3,puVar1);
    lVar10 = *(long *)(param_1 + 800);
    FUN_00190080(uVar7);
    uVar8 = (**(code **)(lVar10 + 0x78))();
    FUN_00190370(param_3,uVar8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 0x80) * 0x30 + 0x94) = 1;
      uVar6 = FUN_00190080(uVar7);
      lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar9 + 0x80);
      lVar10 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar10 + 0x98) = uVar6;
      *(bool *)(lVar10 + 0xb0) = uVar3 != 0;
      *(undefined1 *)(lVar10 + 0xb1) = 1;
      *(byte *)(lVar9 + 0x80) = bVar2 + 1;
      return;
    }
  }
  return;
}

