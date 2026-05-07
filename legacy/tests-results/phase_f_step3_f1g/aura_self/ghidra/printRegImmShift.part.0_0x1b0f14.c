
void printRegImmShift_part_0(long param_1,undefined8 param_2,uint param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  char *pcVar6;
  
  SStream_concat0(param_2,", ");
  if (param_3 == 3) {
    pcVar6 = "lsr";
LAB_001b0f98:
    SStream_concat0(param_2,pcVar6);
    lVar4 = *(long *)(param_1 + 800);
    iVar1 = *(int *)(lVar4 + 0x60);
joined_r0x001b0fa8:
    if (iVar1 == 0) goto LAB_001b1008;
  }
  else {
    if (param_3 < 4) {
      if (param_3 == 1) {
        pcVar6 = "asr";
      }
      else {
        pcVar6 = "lsl";
        if (param_3 != 2) goto LAB_001b0fe8;
      }
      goto LAB_001b0f98;
    }
    if (param_3 == 4) {
      pcVar6 = "ror";
      goto LAB_001b0f98;
    }
    if (param_3 != 5) {
LAB_001b0fe8:
      SStream_concat0(param_2,&DAT_001fca88);
      lVar4 = *(long *)(param_1 + 800);
      iVar1 = *(int *)(lVar4 + 0x60);
      goto joined_r0x001b0fa8;
    }
    SStream_concat0(param_2,&DAT_001fc3b0);
    lVar4 = *(long *)(param_1 + 800);
    if (*(int *)(lVar4 + 0x60) == 0) {
      return;
    }
  }
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar2 = *(byte *)(lVar5 + 0x80);
  if ((*(byte *)(lVar4 + 0x6c) & 1) == 0) {
    uVar3 = bVar2 - 1;
    *(uint *)(lVar5 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar3 << 1) +
                      (long)(int)uVar3) * 0x10 + 0x8c) = param_3;
  }
  else {
    *(uint *)(lVar5 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x8c) = param_3;
  }
  if (param_3 == 5) {
    return;
  }
LAB_001b1008:
  SStream_concat0(param_2,&DAT_001fc9a8);
  if (param_4 == 0) {
    param_4 = 0x20;
  }
  SStream_concat(param_2,&DAT_001fc1b8,param_4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar2 = *(byte *)(lVar4 + 0x80);
  if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) {
    uVar3 = bVar2 - 1;
    *(int *)(lVar4 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar3 << 1) +
                     (long)(int)uVar3) * 0x10 + 0x90) = param_4;
    return;
  }
  *(int *)(lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x90) = param_4;
  return;
}

