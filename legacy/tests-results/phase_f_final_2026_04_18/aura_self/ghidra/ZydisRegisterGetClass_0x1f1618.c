
undefined4 ZydisRegisterGetClass(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x14b) {
    uVar1 = *(undefined4 *)(REG_LOOKUP + (ulong)param_1 * 0xc);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

