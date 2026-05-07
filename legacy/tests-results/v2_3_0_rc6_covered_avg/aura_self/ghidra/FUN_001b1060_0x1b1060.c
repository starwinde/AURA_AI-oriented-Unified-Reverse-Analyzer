
void FUN_001b1060(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  
  FUN_0018ffd0();
  iVar3 = FUN_001900a0();
  FUN_001906d0(param_3,iVar3 + 1);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(int *)(lVar1 + 0x98) = iVar3 + 1;
    *(byte *)(lVar4 + 0x80) = bVar2 + 1;
  }
  return;
}

