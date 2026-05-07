
undefined2 FUN_001f27b0(int param_1,uint param_2)

{
  undefined2 uVar1;
  
  if (param_2 < 0x14b) {
    if (param_1 == 0) {
      uVar1 = *(undefined2 *)(&DAT_0058c0f8 + (ulong)param_2 * 0xc);
    }
    else {
      uVar1 = *(undefined2 *)(&DAT_0058c0f6 + (ulong)param_2 * 0xc);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

