
undefined8 DecodeTBLInstruction_isra_0(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(undefined2 *)(DPR + (ulong)(param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) * 2);
  MCOperand_CreateReg0(param_1,uVar1);
  if ((param_2 >> 6 & 1) != 0) {
    MCOperand_CreateReg0(param_1,uVar1);
  }
  uVar2 = param_2 >> 0x10 & 0xf | (param_2 & 0x80) >> 3;
  iVar3 = MCInst_getOpcode(param_1);
  if ((iVar3 == 0xa70) || (iVar3 == 0xa76)) {
    if (uVar2 == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPair + (ulong)uVar2 * 2));
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar2 * 2));
  }
  MCOperand_CreateReg0
            (param_1,*(undefined2 *)(DPR + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
  return 3;
}

