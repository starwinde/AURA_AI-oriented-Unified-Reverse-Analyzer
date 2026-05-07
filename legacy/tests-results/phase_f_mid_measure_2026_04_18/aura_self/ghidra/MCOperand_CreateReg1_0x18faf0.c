
long MCOperand_CreateReg1(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x308) = param_2;
  *(undefined4 *)(param_1 + 0x300) = 1;
  *(undefined1 *)(param_1 + 0x304) = 1;
  return param_1 + 0x300;
}

