
undefined8 FUN_001987ac(undefined8 param_1,ulong param_2)

{
  ulong uVar1;
  uint uVar2;
  undefined8 uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar2 = (uint)(param_2 >> 0x10);
  uVar1 = uVar4 >> 5;
  if ((param_2 >> 0x10 & 0x38) != 0) {
    if ((((uVar2 & 0xffff) >> 5 & 1) != 0) && ((uVar4 >> 0xc & 1) == 0)) {
      MCOperand_CreateReg0
                (param_1,*(undefined2 *)
                          (QPR + (ulong)(((uint)(uVar4 >> 0xc) & 0xf |
                                         ((uint)param_2 & 0x400000) >> 0x12) >> 1) * 2));
      if ((param_2 & 1) == 0) {
        MCOperand_CreateReg0
                  (param_1,*(undefined2 *)
                            (QPR + (ulong)(((uint)param_2 & 0xf | ((uint)uVar1 & 1) << 4) >> 1) * 2)
                  );
        MCOperand_CreateImm0(param_1,0x40 - (uVar2 & 0x3f));
        return 3;
      }
    }
    return 0;
  }
  uVar2 = (uint)(uVar4 >> 8) & 0xf;
  if (uVar2 == 0xf) {
    if ((uVar1 & 1) != 0) {
      return 0;
    }
    MCInst_setOpcode(param_1,0x721);
  }
  else if (uVar2 == 0xe) {
    if ((uVar1 & 1) == 0) {
      MCInst_setOpcode(param_1,0x71c);
    }
    else {
      MCInst_setOpcode(param_1,0x720);
    }
  }
  else if ((uVar2 == 0xd) || (uVar2 == 0xc)) {
    if ((uVar1 & 1) == 0) {
      MCInst_setOpcode(param_1,0x723);
    }
    else {
      MCInst_setOpcode(param_1,0x75a);
    }
  }
  uVar3 = DecodeNEONModImmInstruction_isra_0(param_1,uVar4);
  return uVar3;
}

