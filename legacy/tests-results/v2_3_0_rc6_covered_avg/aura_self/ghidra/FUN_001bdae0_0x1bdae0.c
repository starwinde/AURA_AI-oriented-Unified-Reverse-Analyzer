
undefined8 FUN_001bdae0(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x6f) {
    return *(undefined8 *)(&DAT_005edd08 + (ulong)param_2 * 0x10);
  }
  return 0;
}

