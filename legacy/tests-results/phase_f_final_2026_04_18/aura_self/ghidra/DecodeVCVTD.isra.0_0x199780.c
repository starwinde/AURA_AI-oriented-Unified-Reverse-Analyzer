
ulong DecodeVCVTD_isra_0(undefined8 param_1,ulong param_2)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar3 = (uint)(param_2 >> 0x10);
  uVar2 = uVar3 & 0x38;
  uVar1 = uVar4 >> 5;
  if ((param_2 >> 0x10 & 0x38) != 0) {
    uVar2 = uVar3 & 0x20;
    if (((uVar3 & 0xffff) >> 5 & 1) != 0) {
      MCOperand_CreateReg0
                (param_1,*(undefined2 *)
                          (DPR + (ulong)((uint)(uVar4 >> 0xc) & 0xf |
                                        ((uint)param_2 & 0x400000) >> 0x12) * 2));
      MCOperand_CreateReg0
                (param_1,*(undefined2 *)
                          (DPR + (ulong)((uint)param_2 & 0xf | ((uint)uVar1 & 1) << 4) * 2));
      MCOperand_CreateImm0(param_1,0x40 - (uVar3 & 0x3f));
      return 3;
    }
LAB_001997b8:
    return (ulong)uVar2;
  }
  uVar3 = (uint)(uVar4 >> 8) & 0xf;
  if (uVar3 == 0xf) {
    if ((uVar1 & 1) != 0) goto LAB_001997b8;
    MCInst_setOpcode(param_1,0x71e);
  }
  else if (uVar3 == 0xe) {
    if ((uVar1 & 1) == 0) {
      MCInst_setOpcode(param_1,0x725);
    }
    else {
      MCInst_setOpcode(param_1,0x71d);
    }
  }
  else if ((uVar3 == 0xd) || (uVar3 == 0xc)) {
    if ((uVar1 & 1) == 0) {
      MCInst_setOpcode(param_1,0x71f);
    }
    else {
      MCInst_setOpcode(param_1,0x758);
    }
  }
  uVar1 = DecodeNEONModImmInstruction_isra_0(param_1,uVar4);
  return uVar1;
}

