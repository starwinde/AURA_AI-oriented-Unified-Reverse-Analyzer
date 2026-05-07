
undefined8 DecodeQADDInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  uVar5 = param_2 >> 0x1c & 0xf;
  uVar3 = (param_2 & 0xffffffff) >> 0xc & 0xf;
  iVar4 = (int)uVar5;
  if (iVar4 == 0xf) {
    uVar6 = DecodeCPSInstruction_isra_0();
    return uVar6;
  }
  if ((int)uVar3 == 0xf) {
    uVar6 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    uVar6 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
  }
  uVar1 = (uint)param_2 & 0xf;
  if (uVar1 == 0xf) {
    uVar6 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  uVar1 = (uint)((param_2 & 0xffffffff) >> 0x10) & 0xf;
  if (uVar1 == 0xf) {
    uVar6 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 == 0xc4f) {
    if (iVar4 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,uVar5);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar5);
    if (iVar4 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      return uVar6;
    }
  }
  MCOperand_CreateReg0(param_1,3);
  return uVar6;
}

