
undefined4 FUN_001970ac(long param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar1 = *(uint *)(*(long *)(param_1 + 800) + 4);
  uVar3 = (param_2 & 0xffffffff) >> 0xc & 0xf;
  if (((uVar1 >> 6 & 1) == 0) && ((uVar1 >> 4 & 1) != 0)) {
    uVar5 = 3;
    if (((uint)(param_2 >> 0xc) & 0xd) == 0xd) {
      uVar5 = 1;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
  }
  else if ((int)uVar3 == 0xf) {
    uVar5 = 1;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    uVar5 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
  }
  if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 4 & 1) == 0) {
    uVar3 = (param_2 & 0xffffffff) >> 0x1c;
    iVar4 = (int)uVar3;
    if (iVar4 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_1);
    if (iVar2 == 0xc4f) {
      if (iVar4 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,uVar3);
    }
    else {
      MCOperand_CreateImm0(param_1,uVar3);
      if (iVar4 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return uVar5;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return uVar5;
  }
  MCOperand_CreateImm0(param_1,0xe);
  MCOperand_CreateReg0(param_1,0);
  return uVar5;
}

