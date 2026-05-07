
undefined8 FUN_001db9a0(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x156) {
    return *(undefined8 *)(&DAT_005f0ef0 + (ulong)param_2 * 8);
  }
  return 0;
}

