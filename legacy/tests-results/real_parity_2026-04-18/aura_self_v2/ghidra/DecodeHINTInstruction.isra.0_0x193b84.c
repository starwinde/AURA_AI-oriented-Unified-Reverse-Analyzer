
undefined8 DecodeHINTInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  
  uVar3 = param_2 >> 0x1c & 0xf;
  MCOperand_CreateImm0(param_1,param_2 & 0xff);
  iVar2 = (int)uVar3;
  if (iVar2 == 0xf) {
    return 0;
  }
  iVar1 = MCInst_getOpcode(param_1);
  if (iVar1 == 0xc4f) {
    if (iVar2 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,uVar3);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar3);
    if (iVar2 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      return 3;
    }
  }
  MCOperand_CreateReg0(param_1,3);
  if (((uint)param_2 & 0xff) != 0x10) {
    return 3;
  }
  return 1;
}

