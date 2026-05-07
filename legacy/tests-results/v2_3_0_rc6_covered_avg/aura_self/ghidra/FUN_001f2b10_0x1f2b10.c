
undefined8 FUN_001f2b10(uint param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0x14b) {
    uVar1 = *(undefined8 *)((long)&PTR_DAT_005feca0 + (ulong)param_1 * 9);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

