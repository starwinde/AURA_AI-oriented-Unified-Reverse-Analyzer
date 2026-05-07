
undefined8 FUN_0019854c(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  int iVar5;
  ulong uVar6;
  undefined8 uVar7;
  
  uVar4 = param_2 & 0xffffffff;
  uVar6 = param_2 >> 0x1c & 0xf;
  uVar3 = uVar4 >> 0x10 & 0xf;
  iVar5 = (int)uVar6;
  if (iVar5 == 0xf) {
    uVar7 = DecodeCPSInstruction_isra_0();
    return uVar7;
  }
  if ((int)uVar3 == 0xf) {
    uVar7 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    uVar7 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
  }
  uVar1 = (uint)param_2 & 0xf;
  if (uVar1 == 0xf) {
    uVar7 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  uVar1 = (uint)(uVar4 >> 8) & 0xf;
  if (uVar1 == 0xf) {
    uVar7 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  uVar1 = (uint)(uVar4 >> 0xc) & 0xf;
  if (uVar1 == 0xf) {
    uVar7 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 == 0xc4f) {
    if (iVar5 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,uVar6);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar6);
    if (iVar5 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      return uVar7;
    }
  }
  MCOperand_CreateReg0(param_1,3);
  return uVar7;
}

