
long ZydisRegisterGetId(uint param_1)

{
  long lVar1;
  
  if (param_1 < 0x14b) {
    lVar1 = (long)(char)REG_LOOKUP[(ulong)param_1 * 0xc + 4];
  }
  else {
    lVar1 = 0xffffffff;
  }
  return lVar1;
}

