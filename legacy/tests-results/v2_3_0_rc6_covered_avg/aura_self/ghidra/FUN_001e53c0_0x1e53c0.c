
undefined8 FUN_001e53c0(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x5f4) {
    return *(undefined8 *)(&DAT_005f6be0 + (ulong)param_2 * 8);
  }
  return 0;
}

