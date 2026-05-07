
void printImm8OptLsl64(undefined8 param_1,int param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  
  MCInst_getOperand();
  iVar1 = MCOperand_getImm();
  MCInst_getOperand(param_1,param_2 + 1);
  uVar2 = MCOperand_getImm();
  if (iVar1 != 0) {
    printUInt64Bang(param_3,iVar1 << (ulong)(uVar2 & 0x1f));
    return;
  }
  if ((uVar2 & 0x3f) == 0) {
    printUInt64Bang(param_3,0 << (ulong)(uVar2 & 0x1f));
    return;
  }
  printUInt32Bang(param_3,0);
  printShifter(param_1,param_2 + 1,param_3);
  return;
}

