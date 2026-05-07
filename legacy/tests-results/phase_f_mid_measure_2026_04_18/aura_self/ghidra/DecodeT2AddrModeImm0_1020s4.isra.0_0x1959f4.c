
undefined8 DecodeT2AddrModeImm0_1020s4_isra_0(undefined8 param_1,uint param_2)

{
  if (param_2 >> 8 != 0xf) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 >> 8) * 2));
    MCOperand_CreateImm0(param_1,param_2 & 0xff);
    return 3;
  }
  MCOperand_CreateReg0(param_1,0xb);
  MCOperand_CreateImm0(param_1,param_2 & 0xff);
  return 1;
}

