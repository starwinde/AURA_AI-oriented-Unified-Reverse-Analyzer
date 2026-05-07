
undefined8 DecodeVLD2LN_isra_0(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  
  uVar7 = param_2 & 0xffffffff;
  uVar5 = (uint)(uVar7 >> 10) & 3;
  uVar6 = (uint)param_2;
  if (uVar5 == 1) {
    uVar9 = uVar7 >> 6 & 3;
    if ((param_2 & 0x20) != 0) {
      uVar5 = 2;
    }
    iVar8 = ((uint)(uVar7 >> 4) & 1) << 2;
  }
  else if (uVar5 == 2) {
    if ((uVar6 >> 5 & 1) != 0) {
      return 0;
    }
    if ((param_2 & 0x40) == 0) {
      uVar5 = 1;
    }
    uVar9 = uVar7 >> 7 & 1;
    iVar8 = ((uint)(uVar7 >> 4) & 1) << 3;
  }
  else {
    if ((uVar7 >> 10 & 3) != 0) {
      return 0;
    }
    uVar9 = uVar7 >> 5 & 7;
    uVar5 = 1;
    iVar8 = ((uint)(uVar7 >> 4) & 1) << 1;
  }
  uVar4 = (uint)(uVar7 >> 0xc) & 0xf | (uVar6 & 0x400000) >> 0x12;
  uVar5 = uVar4 + uVar5;
  uVar1 = *(undefined2 *)(DPR + (ulong)uVar4 * 2);
  MCOperand_CreateReg0(param_1,uVar1);
  if (0x1f < uVar5) {
    return 0;
  }
  uVar2 = *(undefined2 *)(DPR + (ulong)uVar5 * 2);
  uVar7 = uVar7 >> 0x10 & 0xf;
  uVar6 = uVar6 & 0xf;
  MCOperand_CreateReg0(param_1,uVar2);
  if (uVar6 == 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar7 * 2));
    MCOperand_CreateImm0(param_1,iVar8);
  }
  else {
    uVar3 = *(undefined2 *)(GPR + uVar7 * 2);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateImm0(param_1,iVar8);
    if (uVar6 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar6 * 2));
    }
  }
  MCOperand_CreateReg0(param_1,uVar1);
  MCOperand_CreateReg0(param_1,uVar2);
  MCOperand_CreateImm0(param_1,uVar9);
  return 3;
}

