
uint MCOperandInfo_isTiedToOp(long param_1)

{
  return *(uint *)(param_1 + 4) & 1;
}

