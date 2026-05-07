
uint FUN_001bdd50(undefined8 param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 - 0x229U < 10) {
    return (uint)(-0x21eL >> ((ulong)(param_2 - 0x229U) & 0x3f)) & 1 ^ 1;
  }
  if ((param_2 != 0xad3) && (param_2 != 0xada)) {
    uVar1 = (uint)(-0xe2aL >> ((ulong)(param_2 - 0xc46U) & 0x3f)) & 1 ^ 1;
    if (0xb < param_2 - 0xc46U) {
      uVar1 = 0;
    }
    return uVar1;
  }
  return 1;
}

