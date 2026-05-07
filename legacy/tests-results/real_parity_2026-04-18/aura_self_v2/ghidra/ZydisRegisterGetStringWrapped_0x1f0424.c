
long ZydisRegisterGetStringWrapped(uint param_1)

{
  long lVar1;
  
  if (param_1 < 0x14b) {
    lVar1 = (long)&STR_REGISTERS + (ulong)param_1 * 9;
  }
  else {
    lVar1 = 0;
  }
  return lVar1;
}

