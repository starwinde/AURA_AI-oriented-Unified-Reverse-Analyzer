
undefined8 rc_get_var_name(uint param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (g_last_var_names != (long *)0x0) {
    if (*(uint *)(g_last_var_names + 1) <= param_1) {
      return 0;
    }
    uVar1 = *(undefined8 *)(*g_last_var_names + (ulong)param_1 * 8);
  }
  return uVar1;
}

