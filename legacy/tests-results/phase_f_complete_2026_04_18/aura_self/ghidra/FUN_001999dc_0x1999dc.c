
undefined8 FUN_001999dc(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  
  uVar5 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar5 >> 10) & 3;
  uVar4 = (uint)param_2;
  if (uVar3 == 1) {
    uVar7 = uVar5 >> 6 & 3;
    if ((param_2 & 0x20) != 0) {
      uVar3 = 2;
    }
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 2;
  }
  else if (uVar3 == 2) {
    if ((uVar4 >> 5 & 1) != 0) {
      return 0;
    }
    if ((param_2 & 0x40) == 0) {
      uVar3 = 1;
    }
    uVar7 = uVar5 >> 7 & 1;
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 3;
  }
  else {
    if ((uVar5 >> 10 & 3) != 0) {
      return 0;
    }
    uVar7 = uVar5 >> 5 & 7;
    uVar3 = 1;
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 1;
  }
  uVar1 = uVar4 & 0xf;
  uVar2 = *(undefined2 *)(GPR + (uVar5 >> 0x10 & 0xf) * 2);
  if (uVar1 == 0xf) {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,iVar6);
  }
  else {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,iVar6);
    if (uVar1 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
  }
  uVar4 = (uint)(uVar5 >> 0xc) & 0xf | (uVar4 & 0x400000) >> 0x12;
  uVar3 = uVar4 + uVar3;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar4 * 2));
  if (0x1f < uVar3) {
    return 0;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar3 * 2));
  MCOperand_CreateImm0(param_1,uVar7);
  return 3;
}

