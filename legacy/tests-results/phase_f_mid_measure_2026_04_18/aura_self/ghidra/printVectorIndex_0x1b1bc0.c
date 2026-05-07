
void printVectorIndex(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  
  MCInst_getOperand();
  uVar2 = MCOperand_getImm();
  if (uVar2 < 10) {
    SStream_concat(param_3,&DAT_001fd980,uVar2);
  }
  else {
    SStream_concat(param_3,"[0x%x]",uVar2);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar1 = *(byte *)(lVar3 + 0x80) - 1;
    *(uint *)(lVar3 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                      (long)(int)uVar1) * 0x10 + 0x88) = uVar2;
  }
  return;
}

