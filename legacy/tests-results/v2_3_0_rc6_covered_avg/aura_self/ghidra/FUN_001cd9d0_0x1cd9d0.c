
void FUN_001cd9d0(long param_1,undefined8 param_2,ulong param_3)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  int iVar7;
  long lVar8;
  
  uVar4 = FUN_0018ffd0(param_1,2);
  uVar5 = FUN_00190030();
  if ((uVar5 & 1) != 0) {
    lVar6 = FUN_001900a0(uVar4);
    lVar6 = (param_3 & 0xffffffff) * lVar6;
    FUN_001904e0(param_2,lVar6);
    lVar8 = *(long *)(param_1 + 800);
    if (*(int *)(lVar8 + 0x60) != 0) {
      iVar7 = (int)lVar6;
      if ((*(byte *)(lVar8 + 0x6c) & 1) != 0) {
        lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(int *)(lVar6 + (ulong)*(byte *)(lVar6 + 0x67) * 0x38 + 0x90) = iVar7;
        return;
      }
      uVar3 = FUN_0018ffb0(param_1);
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar6 = FUN_001dbcf0(lVar8,uVar3);
      lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar2 = *(char *)(lVar6 + (ulong)bVar1);
      bVar1 = *(byte *)(lVar8 + 0x67);
      if (cVar2 == -0x80) {
        cVar2 = '\0';
      }
      lVar6 = lVar8 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
      *(char *)(lVar6 + 0x98) = cVar2;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar6 + 0x7c) = 2;
      *(long *)(lVar6 + 0x88) = (long)iVar7;
      *(byte *)(lVar8 + 0x67) = bVar1 + 1;
    }
  }
  return;
}

