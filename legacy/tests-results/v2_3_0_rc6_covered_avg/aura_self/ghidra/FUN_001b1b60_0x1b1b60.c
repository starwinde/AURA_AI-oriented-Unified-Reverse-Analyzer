
void FUN_001b1b60(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  FUN_0018ffd0();
  iVar2 = FUN_001900a0();
  FUN_00190370(param_3,", ");
  if (iVar2 == -0x80000000) {
    FUN_00190370(param_3,&DAT_001fdf78);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar4 + 0x80);
      *(undefined8 *)(lVar4 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
      *(byte *)(lVar4 + 0x80) = bVar1 + 1;
      return;
    }
  }
  else {
    FUN_00190614(param_3,iVar2);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar3 + 0x80);
      lVar4 = lVar3 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar4 + 0x94) = 2;
      *(int *)(lVar4 + 0x98) = iVar2;
      *(byte *)(lVar3 + 0x80) = bVar1 + 1;
    }
  }
  return;
}

