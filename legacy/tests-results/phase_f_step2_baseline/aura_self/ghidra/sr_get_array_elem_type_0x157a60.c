
undefined4 sr_get_array_elem_type(long param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = 4;
    if (param_2 < *(uint *)(param_1 + 0x18)) {
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)param_2 * 0x10 + 8);
    }
    return uVar1;
  }
  return 4;
}

