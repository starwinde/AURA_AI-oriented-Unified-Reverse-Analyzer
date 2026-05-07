
byte MCOperandInfo_isPredicate(long param_1)

{
  return *(byte *)(param_1 + 2) >> 1 & 1;
}

