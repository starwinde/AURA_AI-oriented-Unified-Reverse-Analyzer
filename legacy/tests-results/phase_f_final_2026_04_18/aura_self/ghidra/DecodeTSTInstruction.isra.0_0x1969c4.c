
undefined4 DecodeTSTInstruction_isra_0(long param_1,ulong param_2)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  int iVar4;
  ulong uVar5;
  
  uVar2 = param_2 & 0xffffffff;
  uVar5 = param_2 >> 0x1c & 0xf;
  iVar4 = (int)uVar5;
  if (iVar4 != 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (uVar2 >> 0x10 & 0xf) * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)((uint)param_2 & 0xf) * 2));
    iVar1 = MCInst_getOpcode(param_1);
    if (iVar1 == 0xc4f) {
      if (iVar4 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,uVar5);
    }
    else {
      MCOperand_CreateImm0(param_1,uVar5);
      if (iVar4 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return 3;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return 3;
  }
  if ((((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) && ((int)(uVar2 >> 0x14) == 0xf11))
     && ((param_2 & 0xf0) == 0)) {
    uVar3 = 3;
    if ((param_2 & 0xffc0f) != 0) {
      uVar3 = 1;
    }
    MCInst_setOpcode(param_1,0x2f6,(uint)param_2 & 0xffc0f);
    MCOperand_CreateImm0(param_1,uVar2 >> 9 & 1);
    return uVar3;
  }
  return 0;
}

