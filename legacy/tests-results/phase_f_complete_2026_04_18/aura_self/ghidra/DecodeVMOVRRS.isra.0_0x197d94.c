
undefined8 DecodeVMOVRRS_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar1 = param_2 >> 5 & 1 | (param_2 & 0xf) << 1;
  if (((int)uVar4 == 0xf || uVar2 == 0xf) || uVar1 == 0x1f) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
    if (uVar1 + 1 == 0x20) {
      return 0;
    }
    uVar5 = 1;
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    uVar5 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
  }
  param_2 = param_2 >> 0x1c;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(HPR + (ulong)(uVar1 + 1) * 2));
  if (param_2 != 0xf) {
    iVar3 = MCInst_getOpcode(param_1);
    if (iVar3 == 0xc4f) {
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

