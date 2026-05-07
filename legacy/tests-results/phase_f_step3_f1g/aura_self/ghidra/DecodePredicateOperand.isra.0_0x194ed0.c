
undefined8 DecodePredicateOperand_isra_0(undefined8 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0xf) {
    return 0;
  }
  iVar1 = MCInst_getOpcode();
  if (iVar1 == 0xc4f) {
    if (param_2 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,param_2);
  }
  else {
    MCOperand_CreateImm0(param_1,param_2);
    if (param_2 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      return 3;
    }
  }
  MCOperand_CreateReg0(param_1,3);
  return 3;
}

