
undefined4 arm32_reloc_type(int param_1)

{
  if (param_1 - 2U < 0x16) {
    return *(undefined4 *)(CSWTCH_39 + (ulong)(param_1 - 2U) * 4);
  }
  return 0;
}

