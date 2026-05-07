
void printRegWithShiftExtend
               (long param_1,undefined8 param_2,undefined8 param_3,byte param_4,uint param_5,
               char param_6,char param_7)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  
  printOperand();
  if (param_7 == 's' || param_7 == 'd') {
    SStream_concat(param_3,&DAT_001ffc50,param_7);
  }
  if (param_4 == 0 && param_5 == 8) {
    if (param_6 != 'w') {
      return;
    }
    SStream_concat0(param_3,", ");
    SStream_concat(param_3,"%cxt%c",0x75,0x77);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar3 + (ulong)*(byte *)(lVar3 + 0x67) * 0x38 + 0x78) = 3;
    return;
  }
  SStream_concat0(param_3,", ");
  if ((param_6 == 'x' & (param_4 ^ 1)) == 0) {
    if ((param_4 & 1) == 0) {
      SStream_concat(param_3,"%cxt%c",0x75,param_6);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001cd000;
      if (param_6 == 'w') {
        lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar3 + (ulong)*(byte *)(lVar3 + 0x67) * 0x38 + 0x78) = 3;
      }
    }
    else {
      SStream_concat(param_3,"%cxt%c",0x73,param_6);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar1 = *(byte *)(lVar3 + 0x67);
        if (param_6 == 'x') {
          *(undefined4 *)(lVar3 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8 + 0x78) = 8;
        }
        else {
          *(undefined4 *)(lVar3 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8 + 0x78) = 7;
        }
      }
    }
    if (param_5 == 8) {
      return;
    }
  }
  else {
    SStream_concat0(param_3,&DAT_001fa830);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar3 + (ulong)*(byte *)(lVar3 + 0x67) * 0x38 + 0x70) = 1;
    }
  }
LAB_001cd000:
  iVar2 = 0x1f - (int)LZCOUNT(param_5 >> 3);
  SStream_concat(param_3,&DAT_001ffc70,iVar2);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  lVar3 = lVar3 + (ulong)*(byte *)(lVar3 + 0x67) * 0x38;
  *(undefined4 *)(lVar3 + 0x70) = 1;
  *(int *)(lVar3 + 0x74) = iVar2;
  return;
}

