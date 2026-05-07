
undefined4 sr_get_struct_total_size(long *param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 != (long *)0x0) {
    uVar1 = 0;
    if (param_2 < *(uint *)(param_1 + 1)) {
      uVar1 = *(undefined4 *)(*param_1 + (ulong)param_2 * 0x60 + 0x18);
    }
    return uVar1;
  }
  return 0;
}

