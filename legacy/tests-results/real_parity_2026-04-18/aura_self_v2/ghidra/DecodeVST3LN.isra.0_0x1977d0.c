
undefined8 DecodeVST3LN_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar5 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar5 >> 10) & 3;
  uVar4 = (uint)param_2;
  if (uVar3 == 1) {
    if ((uVar4 >> 4 & 1) != 0) {
      return 0;
    }
    uVar6 = uVar5 >> 6 & 3;
    if ((param_2 & 0x20) != 0) {
      uVar3 = 2;
    }
  }
  else if (uVar3 == 2) {
    if ((param_2 & 0x30) != 0) {
      return 0;
    }
    uVar6 = uVar5 >> 7 & 1;
    if ((param_2 & 0x40) == 0) {
      uVar3 = 1;
    }
  }
  else {
    if ((uVar5 >> 10 & 3) != 0) {
      return 0;
    }
    uVar6 = uVar5 >> 5 & 7;
    uVar3 = 1;
    if ((uVar4 >> 4 & 1) != 0) {
      return 0;
    }
  }
  uVar1 = uVar4 & 0xf;
  uVar2 = *(undefined2 *)(GPR + (uVar5 >> 0x10 & 0xf) * 2);
  if (uVar1 == 0xf) {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,0);
  }
  else {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,0);
    if (uVar1 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
  }
  uVar1 = (uint)(uVar5 >> 0xc) & 0xf | (uVar4 & 0x400000) >> 0x12;
  uVar4 = uVar1 + uVar3;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar1 * 2));
  if (uVar4 < 0x20) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar4 * 2));
    if (uVar3 + uVar4 < 0x20) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)(uVar3 + uVar4) * 2));
      MCOperand_CreateImm0(param_1,uVar6);
      return 3;
    }
  }
  return 0;
}

