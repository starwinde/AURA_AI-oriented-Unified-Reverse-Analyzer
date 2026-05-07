
undefined4 DecodeThumbTableBranch_isra_0(long param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar1 = (uint)param_2 & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar3 = 3;
  if ((int)uVar2 == 0xc) {
    uVar3 = 1;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar2 * 2));
  if (uVar1 == 0xd) {
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) == 0) {
      MCOperand_CreateReg0(param_1,0xc);
      return 1;
    }
  }
  else if (uVar1 == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
    return 1;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  return uVar3;
}

