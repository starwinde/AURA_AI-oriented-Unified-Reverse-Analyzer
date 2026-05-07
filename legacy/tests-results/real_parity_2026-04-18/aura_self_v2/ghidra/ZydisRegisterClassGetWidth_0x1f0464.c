
undefined2 ZydisRegisterClassGetWidth(int param_1,uint param_2)

{
  undefined2 uVar1;
  
  if (param_2 < 0x14) {
    if (param_1 == 0) {
      uVar1 = *(undefined2 *)(REG_CLASS_LOOKUP + (ulong)param_2 * 0xc + 10);
    }
    else {
      uVar1 = *(undefined2 *)(REG_CLASS_LOOKUP + (ulong)param_2 * 0xc + 8);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

