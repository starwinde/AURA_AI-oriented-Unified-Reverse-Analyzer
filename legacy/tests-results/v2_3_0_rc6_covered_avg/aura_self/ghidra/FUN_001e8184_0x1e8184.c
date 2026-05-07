
undefined8 FUN_001e8184(long param_1)

{
  undefined8 uVar1;
  
  if ((param_1 < -0x80) || (0x7f < param_1)) {
    if ((param_1 < -0x8000) || (0x7fff < param_1)) {
      if ((param_1 < -0x80000000) || (0x7fffffff < param_1)) {
        uVar1 = 0x40;
      }
      else {
        uVar1 = 0x20;
      }
    }
    else {
      uVar1 = 0x10;
    }
  }
  else {
    uVar1 = 8;
  }
  return uVar1;
}

