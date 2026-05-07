
void printShiftImmOperand_constprop_0(long param_1,undefined8 param_2)

{
  uint uVar1;
  long lVar2;
  undefined4 uVar3;
  uint uVar4;
  
  MCInst_getOperand(param_1,3);
  uVar1 = MCOperand_getImm();
  uVar4 = uVar1 & 0x1f;
  if ((uVar1 >> 5 & 1) == 0) {
    if (uVar4 == 0) {
      return;
    }
    if (uVar4 < 10) {
      SStream_concat(param_2,", lsl #%u",uVar4);
    }
    else {
      SStream_concat(param_2,", lsl #0x%x",uVar4);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar2 = *(long *)(param_1 + 0x310);
    uVar3 = 2;
    goto LAB_001b0320;
  }
  if (uVar4 == 0) {
    uVar4 = 0x20;
LAB_001b02f8:
    SStream_concat(param_2,", asr #0x%x",uVar4);
  }
  else {
    if (9 < uVar4) goto LAB_001b02f8;
    SStream_concat(param_2,", asr #%u",uVar4);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar2 = *(long *)(param_1 + 0x310);
  uVar3 = 1;
LAB_001b0320:
  uVar1 = *(byte *)(*(long *)(lVar2 + 0xf0) + 0x80) - 1;
  lVar2 = *(long *)(lVar2 + 0xf0) +
          ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) + (long)(int)uVar1) *
          0x10;
  *(undefined4 *)(lVar2 + 0x8c) = uVar3;
  *(uint *)(lVar2 + 0x90) = uVar4;
  return;
}

