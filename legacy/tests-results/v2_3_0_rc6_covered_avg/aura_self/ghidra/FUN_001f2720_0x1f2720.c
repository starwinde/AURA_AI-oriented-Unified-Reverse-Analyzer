
long FUN_001f2720(uint param_1)

{
  long lVar1;
  
  if (param_1 < 0x14b) {
    lVar1 = (long)(char)(&DAT_0058c0f4)[(ulong)param_1 * 0xc];
  }
  else {
    lVar1 = 0xffffffff;
  }
  return lVar1;
}

