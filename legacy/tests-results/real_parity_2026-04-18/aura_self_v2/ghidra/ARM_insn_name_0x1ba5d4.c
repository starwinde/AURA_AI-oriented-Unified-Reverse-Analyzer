
undefined8 ARM_insn_name(undefined8 param_1,uint param_2)

{
  if (param_2 < 0x1d8) {
    return *(undefined8 *)(insn_name_maps + (ulong)param_2 * 8);
  }
  return 0;
}

