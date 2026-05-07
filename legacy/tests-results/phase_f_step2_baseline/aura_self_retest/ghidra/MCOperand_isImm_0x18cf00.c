
bool MCOperand_isImm(long param_1)

{
  return *(char *)(param_1 + 4) == '\x02';
}

