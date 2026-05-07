
ulong DecodeT2LdStPre_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar1 = (param_2 >> 9 & 1) << 8 | (int)uVar2 << 9 | param_2 & 0xff;
  uVar3 = (ulong)(param_2 >> 0xc) & 0xf;
  if ((int)uVar2 != 0xf) {
    if ((param_2 >> 0x14 & 1) == 0) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar2 * 2));
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
      uVar1 = DecodeT2AddrModeImm8_isra_0(param_1,uVar1);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar2 * 2));
      uVar1 = DecodeT2AddrModeImm8_isra_0(param_1,uVar1);
    }
    if (3 < uVar1) {
      return 0;
    }
    if ((uVar1 & 1) == 0) {
      return 0;
    }
    return (ulong)*(uint *)(CSWTCH_1083 + (ulong)uVar1 * 4);
  }
  uVar1 = MCInst_getOpcode();
  if (uVar1 < 0xb30) {
    if (0xb2d < uVar1) {
      if ((int)uVar3 == 0xf) {
        MCInst_setOpcode(param_1,0xb72);
      }
      else {
        MCInst_setOpcode(param_1,0xb32);
      }
      goto LAB_001967c0;
    }
    if (uVar1 < 0xb1b) {
      if (0xb18 < uVar1) {
        MCInst_setOpcode(param_1,0xb1d);
        goto LAB_001967c0;
      }
    }
    else if (uVar1 - 0xb27 < 2) {
      MCInst_setOpcode(param_1,0xb2b);
      goto LAB_001967c0;
    }
  }
  else if (uVar1 < 0xb37) {
    if (0xb34 < uVar1) {
      MCInst_setOpcode(param_1,0xb39);
      goto LAB_001967c0;
    }
  }
  else if (uVar1 - 0xb3c < 2) {
    MCInst_setOpcode(param_1,0xb40);
LAB_001967c0:
    uVar2 = DecodeT2LoadLabel_isra_0(param_1,param_2);
    return uVar2;
  }
  return 0;
}

