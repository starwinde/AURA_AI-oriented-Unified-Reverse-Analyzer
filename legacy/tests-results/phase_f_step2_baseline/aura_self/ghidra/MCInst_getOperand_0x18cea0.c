
long MCInst_getOperand(long param_1,ulong param_2)

{
  return param_1 + (param_2 & 0xffffffff) * 0x10 + 0x10;
}

