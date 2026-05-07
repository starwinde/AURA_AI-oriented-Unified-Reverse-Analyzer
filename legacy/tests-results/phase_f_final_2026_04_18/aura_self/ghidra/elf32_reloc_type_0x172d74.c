
undefined4 elf32_reloc_type(int param_1)

{
  if (param_1 - 1U < 8) {
    return *(undefined4 *)(CSWTCH_36 + (ulong)(param_1 - 1U) * 4);
  }
  return 0;
}

