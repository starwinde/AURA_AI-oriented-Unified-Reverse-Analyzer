
void arm64_op_addFP(float param_1,long param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  
  if (*(int *)(*(long *)(param_2 + 800) + 0x60) != 0) {
    lVar3 = *(long *)(*(long *)(param_2 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar3 + 0x67);
    lVar1 = lVar3 + ((ulong)bVar2 * 8 - (ulong)bVar2) * 8;
    *(undefined4 *)(lVar1 + 0x7c) = 4;
    *(double *)(lVar1 + 0x88) = (double)param_1;
    *(byte *)(lVar3 + 0x67) = bVar2 + 1;
  }
  return;
}

