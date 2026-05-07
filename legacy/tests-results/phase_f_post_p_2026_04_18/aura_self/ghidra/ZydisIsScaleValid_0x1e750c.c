
undefined8 ZydisIsScaleValid(byte param_1)

{
  undefined8 uVar1;
  
  if ((param_1 < 9) && ((0x117UL >> ((ulong)param_1 & 0x3f) & 1) != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

