
undefined8 ARM_reg_name2(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x6f) {
    return *(undefined8 *)(reg_name_maps2 + (ulong)param_2 * 0x10 + 8);
  }
  return 0;
}

