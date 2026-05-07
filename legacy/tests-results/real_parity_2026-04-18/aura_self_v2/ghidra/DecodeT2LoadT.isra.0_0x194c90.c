
ulong DecodeT2LoadT_isra_0(long param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar2 = (uint)(uVar4 >> 0x10) & 0xf;
  if (uVar2 == 0xf) {
    uVar2 = MCInst_getOpcode();
    if (uVar2 == 0xb2d) {
      MCInst_setOpcode(param_1,0xb32);
    }
    else if (uVar2 < 0xb2e) {
      if (uVar2 == 0xb18) {
        MCInst_setOpcode(param_1,0xb1d);
      }
      else {
        if (uVar2 != 0xb26) {
          return 0;
        }
        MCInst_setOpcode(param_1,0xb2b);
      }
    }
    else if (uVar2 == 0xb34) {
      MCInst_setOpcode(param_1,0xb39);
    }
    else {
      if (uVar2 != 0xb3b) {
        return 0;
      }
      MCInst_setOpcode(param_1,0xb40);
    }
    uVar4 = DecodeT2LoadLabel_isra_0(param_1,uVar4);
    return uVar4;
  }
  uVar4 = uVar4 >> 0xc & 0xf;
  iVar1 = (int)uVar4;
  if (iVar1 == 0xd) {
    uVar3 = 3;
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 3;
    if (iVar1 == 0xf) {
      uVar3 = 1;
    }
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
  uVar3 = *(uint *)(CSWTCH_1083 + (ulong)uVar3 * 4);
  uVar4 = DecodeT2AddrModeImm8_isra_0(param_1,(uint)param_2 & 0xff | uVar2 << 9);
  if ((int)uVar4 != 1) {
    if ((int)uVar4 != 3) {
      return 0;
    }
    return (ulong)uVar3;
  }
  return uVar4;
}

