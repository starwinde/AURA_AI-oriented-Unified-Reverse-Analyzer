
undefined4 FUN_001f2768(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x14b) {
    uVar1 = *(undefined4 *)(&DAT_0058c0f0 + (ulong)param_1 * 0xc);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

