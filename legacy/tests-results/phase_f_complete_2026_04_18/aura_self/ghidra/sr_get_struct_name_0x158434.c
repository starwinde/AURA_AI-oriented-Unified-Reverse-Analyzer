
long sr_get_struct_name(long *param_1,uint param_2)

{
  if ((param_1 != (long *)0x0) && (param_2 < *(uint *)(param_1 + 1))) {
    return *param_1 + (ulong)param_2 * 0x60 + 0x1c;
  }
  return 0;
}

