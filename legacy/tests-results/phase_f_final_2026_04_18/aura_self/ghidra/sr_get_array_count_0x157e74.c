
undefined4 sr_get_array_count(long param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 0x18);
  }
  return 0;
}

