
ulong DecodeT2LoadShift_isra_0(undefined8 param_1,ulong param_2)

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
    if (uVar3 == 0xb3a) {
      MCInst_setOpcode(param_1,0xb39);
    }
    else if (uVar3 < 0xb3b) {
      if (uVar3 == 0xb2c) {
        MCInst_setOpcode(param_1,0xb2b);
      }
      else if (uVar3 == 0xb33) {
        MCInst_setOpcode(param_1,0xb32);
      }
      else {
        if (uVar3 != 0xb1e) {
          return 0;
        }
        MCInst_setOpcode(param_1,0xb1d);
      }
    }
    else if (uVar3 == 0xb6f) {
      MCInst_setOpcode(param_1,0xb6e);
    }
    else if (uVar3 == 0xb73) {
      MCInst_setOpcode(param_1,0xb72);
    }
    else {
      if (uVar3 != 0xb41) {
        return 0;
      }
      MCInst_setOpcode(param_1,0xb40);
    }
    uVar4 = DecodeT2LoadLabel_isra_0(param_1,uVar4);
    return uVar4;
  }
  if (uVar1 == 0xf) {
    iVar2 = MCInst_getOpcode();
    if (iVar2 == 0xb33) {
      MCInst_setOpcode(param_1,0xb73);
    }
    else {
      if (iVar2 == 0xb3a) {
        return 0;
      }
      if (iVar2 == 0xb2c) {
        MCInst_setOpcode(param_1,0xb6b);
      }
    }
  }
  iVar2 = MCInst_getOpcode(param_1);
  if ((8 < iVar2 - 0xb6bU) || ((0x111UL >> ((ulong)(iVar2 - 0xb6bU) & 0x3f) & 1) == 0)) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  uVar3 = DecodeT2AddrModeSOReg_isra_0
                    (param_1,(uint)(uVar4 >> 4) & 3 | ((uint)param_2 & 0xf) << 2 | uVar3 << 6);
  if ((uVar3 < 4) && ((uVar3 & 1) != 0)) {
    return (ulong)*(uint *)(CSWTCH_1083 + (ulong)uVar3 * 4);
  }
  return 0;
}

