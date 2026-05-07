
void arm64_op_addImm(long param_1,int param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar3 + 0x67);
    lVar1 = lVar3 + ((ulong)bVar2 * 8 - (ulong)bVar2) * 8;
    *(undefined4 *)(lVar1 + 0x7c) = 2;
    *(long *)(lVar1 + 0x88) = (long)param_2;
    *(byte *)(lVar3 + 0x67) = bVar2 + 1;
  }
  return;
}

