
bool MCOperand_isFPImm(long param_1)

{
  return *(char *)(param_1 + 4) == '\x03';
}

