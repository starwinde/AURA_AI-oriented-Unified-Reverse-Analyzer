
void _printOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  uVar2 = MCInst_getOperand();
  uVar3 = MCOperand_isReg();
  if ((uVar3 & 1) != 0) {
    iVar1 = MCOperand_getReg(uVar2);
    SStream_concat0(param_3,&AsmStrs_0 + *(ushort *)(RegAsmOffset_1 + (ulong)(iVar1 - 1) * 2));
    return;
  }
  uVar3 = MCOperand_isImm(uVar2);
  if ((uVar3 & 1) == 0) {
    return;
  }
  uVar2 = MCOperand_getImm(uVar2);
  printImm_isra_0(*(undefined1 *)(param_1 + 6),*(long *)(param_1 + 800),param_3,uVar2,
                  *(int *)(*(long *)(param_1 + 800) + 100) != 0);
  return;
}

