
long FUN_001f2b54(uint param_1)

{
  long lVar1;
  
  if (param_1 < 0x14b) {
    lVar1 = (long)&PTR_DAT_005feca0 + (ulong)param_1 * 9;
  }
  else {
    lVar1 = 0;
  }
  return lVar1;
}

