
undefined8 DecodeVLD3DupInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar4 = (uint)(param_2 >> 0xc) & 0xf | ((uint)param_2 & 0x400000) >> 0x12;
  uVar2 = (uint)param_2 & 0xf;
  uVar5 = param_2 >> 0x10 & 0xf;
  iVar1 = ((uint)(param_2 >> 5) & 1) + 1;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar4 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(uVar4 + iVar1) & 0x1f) * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(uVar4 + iVar1 * 2) & 0x1f) * 2));
  if (uVar2 == 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
    MCOperand_CreateImm0(param_1,0);
  }
  else {
    uVar3 = *(undefined2 *)(GPR + uVar5 * 2);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateImm0(param_1,0);
    if (uVar2 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
  }
  return 3;
}

