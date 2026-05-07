
ulong FUN_0019b07c(undefined8 param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  
  uVar7 = param_2 >> 6 & 3;
  uVar8 = param_2 >> 0x10 & 0xf;
  uVar4 = (uint)(param_2 >> 0xc) & 0xf | ((uint)param_2 & 0x400000) >> 0x12;
  iVar1 = ((uint)(param_2 >> 5) & 1) + 1;
  uVar2 = (uint)param_2 & 0xf;
  uVar5 = param_2 >> 4 & 1;
  iVar6 = (int)uVar7;
  if (iVar6 == 3) {
    uVar7 = 0x10;
    if ((int)uVar5 == 0) {
      return uVar5;
    }
  }
  else {
    uVar7 = (ulong)(uint)(((int)uVar5 << uVar7) << 2);
    if (iVar6 == 2) {
      uVar7 = uVar5 << 3;
    }
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar4 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(uVar4 + iVar1) & 0x1f) * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(iVar1 * 2 + uVar4) & 0x1f) * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(iVar1 * 3 + uVar4) & 0x1f) * 2));
  if (uVar2 == 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar8 * 2));
    MCOperand_CreateImm0(param_1,uVar7);
  }
  else {
    uVar3 = *(undefined2 *)(GPR + uVar8 * 2);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateReg0(param_1,uVar3);
    MCOperand_CreateImm0(param_1,uVar7);
    if (uVar2 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
  }
  return 3;
}

