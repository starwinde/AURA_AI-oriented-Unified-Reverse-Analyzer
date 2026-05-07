
undefined8 DecodeBranchImmInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  
  uVar4 = param_2 >> 0x1c & 0xf;
  uVar1 = (uint)param_2 & 0xffffff;
  iVar3 = (int)uVar4;
  if (iVar3 == 0xf) {
    MCInst_setOpcode(param_1,0x22c);
    MCOperand_CreateImm0
              (param_1,(long)((ulong)(((uint)(param_2 >> 0x18) & 1) << 1 | uVar1 << 2) << 0x26) >>
                       0x26);
  }
  else {
    MCOperand_CreateImm0(param_1,-(ulong)(uVar1 >> 0x17) & 0xfffffffffc000000 | (ulong)uVar1 << 2);
    iVar2 = MCInst_getOpcode(param_1);
    if (iVar2 == 0xc4f) {
      if (iVar3 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,uVar4);
    }
    else {
      MCOperand_CreateImm0(param_1,uVar4);
      if (iVar3 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return 3;
      }
    }
    MCOperand_CreateReg0(param_1,3);
  }
  return 3;
}

