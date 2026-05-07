
ulong DecodeSwap_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  int iVar8;
  ulong uVar9;
  uint uVar10;
  
  uVar4 = (param_2 & 0xffffffff) >> 0xc & 0xf;
  uVar6 = (param_2 & 0xffffffff) >> 0x10 & 0xf;
  uVar9 = param_2 >> 0x1c & 0xf;
  iVar8 = (int)uVar9;
  if (iVar8 == 0xf) {
    uVar4 = DecodeCPSInstruction_isra_0();
    return uVar4;
  }
  uVar3 = (uint)uVar4;
  uVar5 = (uint)uVar6;
  uVar1 = (uint)param_2 & 0xf;
  uVar10 = 1;
  uVar7 = uVar10;
  if (uVar3 != uVar5 && uVar1 != uVar5) {
    uVar7 = 3;
  }
  if (uVar3 == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    uVar10 = uVar7;
  }
  if (uVar1 == 0xf) {
    uVar10 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  if (uVar5 == 0xf) {
    uVar10 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar6 * 2));
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 == 0xc4f) {
    if (iVar8 == 0xe) {
      uVar10 = 0;
      goto LAB_0019ace0;
    }
    MCOperand_CreateImm0(param_1,uVar9);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar9);
    if (iVar8 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      goto LAB_0019ace0;
    }
  }
  MCOperand_CreateReg0(param_1,3);
LAB_0019ace0:
  return (ulong)uVar10;
}

