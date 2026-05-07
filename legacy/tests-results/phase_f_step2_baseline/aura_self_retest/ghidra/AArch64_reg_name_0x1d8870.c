
undefined8 AArch64_reg_name(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x156) {
    return *(undefined8 *)(&reg_name_maps + (ulong)param_2 * 8);
  }
  return 0;
}

