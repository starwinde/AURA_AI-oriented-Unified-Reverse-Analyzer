
void op_addReg(long param_1,int param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar3 = *(long *)(param_1 + 800);
  if (*(int *)(lVar3 + 0x60) != 0) {
    lVar5 = *(long *)(lVar3 + 0xa0);
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0xa0);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0xa8) = 1;
    *(int *)(lVar1 + 0xb0) = param_2;
    *(undefined1 *)(lVar1 + 200) = *(undefined1 *)(lVar5 + param_2);
    *(byte *)(lVar4 + 0xa0) = bVar2 + 1;
  }
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(*(long *)(lVar3 + 0xa0) + (long)param_2);
  }
  return;
}

