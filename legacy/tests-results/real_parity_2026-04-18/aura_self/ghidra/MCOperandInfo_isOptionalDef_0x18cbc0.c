
byte MCOperandInfo_isOptionalDef(long param_1)

{
  return *(byte *)(param_1 + 2) >> 2 & 1;
}

