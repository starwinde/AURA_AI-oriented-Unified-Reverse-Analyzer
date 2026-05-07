
ulong FUN_0019688c(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar4 >> 0x10) & 0xf;
  uVar1 = (uint)(uVar4 >> 0xc) & 0xf;
  if (uVar3 == 0xf) {
    uVar3 = MCInst_getOpcode();
    if (uVar3 == 0xb38) {
      MCInst_setOpcode(param_1,0xb39);
    }
    else if (uVar3 < 0xb39) {
      if (uVar3 == 0xb2a) {
        MCInst_setOpcode(param_1,0xb2b);
      }
      else if (uVar3 == 0xb31) {
        MCInst_setOpcode(param_1,0xb32);
      }
      else {
        if (uVar3 != 0xb1c) {
          return 0;
        }
        MCInst_setOpcode(param_1,0xb1d);
      }
    }
    else if (uVar3 == 0xb6d) {
      MCInst_setOpcode(param_1,0xb6e);
    }
    else if (uVar3 == 0xb71) {
      MCInst_setOpcode(param_1,0xb72);
    }
    else {
      if (uVar3 != 0xb3f) {
        return 0;
      }
      MCInst_setOpcode(param_1,0xb40);
    }
    uVar4 = DecodeT2LoadLabel_isra_0(param_1,uVar4);
    return uVar4;
  }
  if (uVar1 == 0xf) {
    iVar2 = MCInst_getOpcode();
    if (iVar2 == 0xb31) {
      MCInst_setOpcode(param_1,0xb71);
    }
    else {
      if (iVar2 == 0xb38) {
        return 0;
      }
      if ((iVar2 == 0xb2a) && ((uVar4 >> 9 & 1) == 0)) {
        MCInst_setOpcode(param_1,0xb6a);
      }
    }
  }
  iVar2 = MCInst_getOpcode(param_1);
  if ((7 < iVar2 - 0xb6aU) || ((0x89UL >> ((ulong)(iVar2 - 0xb6aU) & 0x3f) & 1) == 0)) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  uVar3 = DecodeT2AddrModeImm8_isra_0
                    (param_1,uVar3 << 9 | ((uint)(uVar4 >> 9) & 1) << 8 | (uint)param_2 & 0xff);
  if ((uVar3 < 4) && ((uVar3 & 1) != 0)) {
    return (ulong)*(uint *)(CSWTCH_1083 + (ulong)uVar3 * 4);
  }
  return 0;
}

