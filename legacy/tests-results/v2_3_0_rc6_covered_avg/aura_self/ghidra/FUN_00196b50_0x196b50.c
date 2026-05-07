
undefined8 FUN_00196b50(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x20) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)param_2 * 2));
    return 3;
  }
  return 0;
}

