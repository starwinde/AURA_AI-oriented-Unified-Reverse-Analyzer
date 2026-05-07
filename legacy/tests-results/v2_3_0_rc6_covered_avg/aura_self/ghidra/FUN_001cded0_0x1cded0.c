
void FUN_001cded0(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  
  uVar6 = FUN_0018ffd0();
  uVar7 = FUN_00190030();
  if ((uVar7 & 1) == 0) {
    return;
  }
  uVar3 = FUN_001900a0(uVar6);
  FUN_0018ffd0(param_1,param_2 + 1);
  uVar4 = FUN_001900a0();
  FUN_00190614(param_3,(ulong)(uVar3 & 0xfff));
  lVar9 = *(long *)(param_1 + 800);
  if (*(int *)(lVar9 + 0x60) != 0) {
    uVar5 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar9 = FUN_001dbcf0(lVar9,uVar5);
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    cVar2 = *(char *)(lVar9 + (ulong)bVar1);
    bVar1 = *(byte *)(lVar8 + 0x67);
    if (cVar2 == -0x80) {
      cVar2 = '\0';
    }
    lVar9 = lVar8 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
    *(char *)(lVar9 + 0x98) = cVar2;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar9 + 0x7c) = 2;
    *(ulong *)(lVar9 + 0x88) = (ulong)(uVar3 & 0xfff);
    *(byte *)(lVar8 + 0x67) = bVar1 + 1;
  }
  if ((uVar4 & 0x3f) != 0) {
    FUN_001cdbe4(param_1,param_2 + 1,param_3);
    return;
  }
  return;
}

