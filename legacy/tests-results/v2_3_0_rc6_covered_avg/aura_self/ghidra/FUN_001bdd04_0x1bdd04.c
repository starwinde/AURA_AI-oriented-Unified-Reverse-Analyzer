
undefined8 FUN_001bdd04(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x1d8) {
    return *(undefined8 *)(&DAT_005eeae0 + (ulong)param_2 * 8);
  }
  return 0;
}

