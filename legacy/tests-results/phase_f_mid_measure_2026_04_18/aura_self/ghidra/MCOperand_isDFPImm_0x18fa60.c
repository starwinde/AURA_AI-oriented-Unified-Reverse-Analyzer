
bool MCOperand_isDFPImm(long param_1)

{
  return *(char *)(param_1 + 4) == '\x04';
}

