
bool MCOperand_isReg(long param_1)

{
  return *(char *)(param_1 + 4) == '\x01';
}

