
undefined8 ZydisRegisterGetString(uint param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0x14b) {
    uVar1 = *(undefined8 *)((long)&STR_REGISTERS + (ulong)param_1 * 9);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

