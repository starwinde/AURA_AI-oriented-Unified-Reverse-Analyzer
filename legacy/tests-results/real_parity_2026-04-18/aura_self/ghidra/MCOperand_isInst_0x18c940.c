
bool MCOperand_isInst(long param_1)

{
  return *(char *)(param_1 + 4) == '\x06';
}

