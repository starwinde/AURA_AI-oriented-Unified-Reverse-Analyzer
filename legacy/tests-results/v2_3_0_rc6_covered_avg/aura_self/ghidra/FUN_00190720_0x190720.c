
ulong FUN_00190720(short *param_1)

{
  ulong uVar1;
  
  if (*param_1 != 0) {
    uVar1 = 0;
    do {
      uVar1 = (ulong)((int)uVar1 + 1);
    } while (param_1[uVar1] != 0);
    return uVar1;
  }
  return 0;
}

