
undefined8 DecodeDPRRegisterClass_isra_0(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x20) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)param_2 * 2));
    return 3;
  }
  return 0;
}

