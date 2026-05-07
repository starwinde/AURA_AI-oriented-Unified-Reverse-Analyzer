
void printRotImmOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  
  MCInst_getOperand();
  iVar2 = MCOperand_getImm();
  if (iVar2 != 0) {
    SStream_concat0(param_3,", ror #");
    if (iVar2 == 2) {
      SStream_concat0(param_3,&DAT_001fac68);
    }
    else if (iVar2 == 3) {
      SStream_concat0(param_3,&DAT_001fb6a0);
    }
    else {
      SStream_concat0(param_3,"8");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar1 = *(byte *)(lVar3 + 0x80) - 1;
      lVar3 = lVar3 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                      (long)(int)uVar1) * 0x10;
      *(undefined4 *)(lVar3 + 0x8c) = 4;
      *(int *)(lVar3 + 0x90) = iVar2 << 3;
      return;
    }
  }
  return;
}

