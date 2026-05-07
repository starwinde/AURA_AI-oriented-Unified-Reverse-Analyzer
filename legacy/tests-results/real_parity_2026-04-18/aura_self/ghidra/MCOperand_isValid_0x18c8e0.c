
bool MCOperand_isValid(long param_1)

{
  return *(char *)(param_1 + 4) != '\0';
}

