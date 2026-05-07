
undefined8 DecodeQPRRegisterClass_part_0(undefined8 param_1,ulong param_2)

{
  MCOperand_CreateReg0(param_1,*(undefined2 *)(QPR + (param_2 >> 1 & 0x7fffffff) * 2));
  return 3;
}

