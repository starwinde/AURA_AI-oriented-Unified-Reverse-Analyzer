
undefined8 FUN_001dbf20(long *param_1,undefined1 *param_2,long param_3)

{
  if ((ulong)(param_3 - param_1[2]) < (ulong)param_1[1]) {
    *param_2 = *(undefined1 *)(*param_1 + (param_3 - param_1[2]));
    return 0;
  }
  return 0xffffffff;
}

