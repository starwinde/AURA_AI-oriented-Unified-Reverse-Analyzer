
undefined8 DecodeVMOVSRR_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar3 = param_2 >> 0xc & 0xf;
  uVar1 = param_2 >> 5 & 1 | (param_2 & 0xf) << 1;
  if (uVar3 == 0xf || uVar2 == 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
    if (uVar1 == 0x1f) {
      return 0;
    }
    uVar5 = 1;
  }
  else {
    if (uVar1 == 0x1f) {
      MCOperand_CreateReg0(param_1,0x6e);
      return 0;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
    uVar5 = 3;
  }
  param_2 = param_2 >> 0x1c;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)(uVar1 + 1) * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar3 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
  if (param_2 != 0xf) {
    iVar4 = MCInst_getOpcode(param_1);
    if (iVar4 == 0xc4f) {
      if (param_2 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,param_2);
    }
    else {
      MCOperand_CreateImm0(param_1,param_2);
      if (param_2 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return uVar5;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return uVar5;
  }
  return 0;
}

