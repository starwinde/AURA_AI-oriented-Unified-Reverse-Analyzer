
undefined8 FUN_00198fcc(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar1 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar4 = (ulong)uVar1;
  iVar2 = MCInst_getOpcode();
  if (iVar2 - 0x5b2U < 0x12) {
    uVar3 = 1L << ((ulong)(iVar2 - 0x5b2U) & 0x3f);
    if ((uVar3 & 0x38e38) != 0) {
      if (0x1d < uVar1) {
        return 0;
      }
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPairSpc + uVar4 * 2));
      goto LAB_0019905c;
    }
    if ((uVar3 & 0x71c7) != 0) {
      if (uVar1 == 0x1f) {
        return 0;
      }
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPair + uVar4 * 2));
      goto LAB_0019905c;
    }
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + uVar4 * 2));
LAB_0019905c:
  uVar4 = (ulong)(param_2 >> 0x10) & 0xf;
  iVar2 = ((param_2 >> 4 & 1) << ((ulong)(param_2 >> 6) & 3)) << 1;
  if ((param_2 & 0xf) == 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    MCOperand_CreateImm0(param_1,iVar2);
  }
  else {
    MCOperand_CreateImm0(param_1,0);
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    MCOperand_CreateImm0(param_1,iVar2);
    if ((param_2 & 0xd) != 0xd) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 & 0xf) * 2));
    }
  }
  return 3;
}

