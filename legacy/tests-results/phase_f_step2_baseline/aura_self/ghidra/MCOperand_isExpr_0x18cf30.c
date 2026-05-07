
bool MCOperand_isExpr(long param_1)

{
  return *(char *)(param_1 + 4) == '\x05';
}

