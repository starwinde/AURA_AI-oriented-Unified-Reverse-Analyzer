
undefined8 DecodeThumbAddSPReg_isra_0(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = MCInst_getOpcode();
  if (iVar2 == 0xc3d) {
    uVar1 = *(undefined2 *)(GPR + (ulong)(param_2 & 7 | ((param_2 & 0xffff) >> 7 & 1) << 3) * 2);
    MCOperand_CreateReg0(param_1,uVar1);
    MCOperand_CreateReg0(param_1,0xc);
    MCOperand_CreateReg0(param_1,uVar1);
    return 3;
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 != 0xc41) {
    return 3;
  }
  MCOperand_CreateReg0(param_1,0xc);
  MCOperand_CreateReg0(param_1,0xc);
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + ((ulong)((param_2 & 0xffff) >> 3) & 0xf) * 2));
  return 3;
}

