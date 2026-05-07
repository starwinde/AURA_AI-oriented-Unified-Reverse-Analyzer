
void FUN_001cd610(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  
  uVar4 = FUN_0018ffd0();
  uVar5 = FUN_00190030();
  if ((uVar5 & 1) != 0) {
    lVar6 = FUN_001900a0(uVar4);
    lVar6 = *(long *)(param_1 + 0x318) + lVar6 * 4;
    FUN_00190540(param_3,lVar6);
    lVar8 = *(long *)(param_1 + 800);
    if (*(int *)(lVar8 + 0x60) != 0) {
      uVar3 = FUN_0018ffb0(param_1);
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar8 = FUN_001dbcf0(lVar8,uVar3);
      lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar2 = *(char *)(lVar8 + (ulong)bVar1);
      bVar1 = *(byte *)(lVar7 + 0x67);
      if (cVar2 == -0x80) {
        cVar2 = '\0';
      }
      lVar8 = lVar7 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
      *(char *)(lVar8 + 0x98) = cVar2;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar8 + 0x7c) = 2;
      *(long *)(lVar8 + 0x88) = lVar6;
      *(byte *)(lVar7 + 0x67) = bVar1 + 1;
      return;
    }
  }
  return;
}

