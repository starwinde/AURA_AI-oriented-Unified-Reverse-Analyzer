
undefined8 FUN_001e8204(ulong param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0x100) {
    uVar1 = 8;
  }
  else if (param_1 < 0x10000) {
    uVar1 = 0x10;
  }
  else if (param_1 < 0x100000000) {
    uVar1 = 0x20;
  }
  else {
    uVar1 = 0x40;
  }
  return uVar1;
}

