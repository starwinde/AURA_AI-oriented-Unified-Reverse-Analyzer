
undefined8 alias_get_base_offset(long param_1,uint param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  if (param_1 != 0) {
    uVar1 = 0;
    if ((param_2 < *(uint *)(param_1 + 0x10)) &&
       (*(char *)(*(long *)(param_1 + 0x28) + (ulong)param_2) != '\0')) {
      if (param_3 != (undefined8 *)0x0) {
        *param_3 = *(undefined8 *)(*(long *)(param_1 + 0x20) + (ulong)param_2 * 8);
      }
      uVar1 = 1;
    }
    return uVar1;
  }
  return 0;
}

