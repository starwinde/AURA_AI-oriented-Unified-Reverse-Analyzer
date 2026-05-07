
undefined2 FUN_001f2b94(int param_1,uint param_2)

{
  undefined2 uVar1;
  
  if (param_2 < 0x14) {
    if (param_1 == 0) {
      uVar1 = *(undefined2 *)(&DAT_0058d082 + (ulong)param_2 * 0xc);
    }
    else {
      uVar1 = *(undefined2 *)(&DAT_0058d080 + (ulong)param_2 * 0xc);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

