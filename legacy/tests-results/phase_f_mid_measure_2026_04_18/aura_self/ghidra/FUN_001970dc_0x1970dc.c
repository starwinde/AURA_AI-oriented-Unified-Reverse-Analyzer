
undefined4 FUN_001970dc(long param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  undefined4 uVar5;
  
  uVar4 = param_2 >> 6 & 0x3ffffff;
  uVar3 = param_2 >> 2 & 0xf;
  iVar1 = MCInst_getOpcode();
  if (((0x13 < iVar1 - 0xbebU) || ((0x82001UL >> ((ulong)(iVar1 - 0xbebU) & 0x3f) & 1) == 0)) ||
     (uVar5 = 0, (int)uVar4 != 0xf)) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    iVar1 = (int)uVar3;
    if (iVar1 == 0xd) {
      uVar2 = 3;
      if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 3;
      if (iVar1 == 0xf) {
        uVar2 = 1;
      }
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
    uVar5 = *(undefined4 *)(CSWTCH_1083 + (ulong)uVar2 * 4);
    MCOperand_CreateImm0(param_1,(uint)param_2 & 3);
  }
  return uVar5;
}

