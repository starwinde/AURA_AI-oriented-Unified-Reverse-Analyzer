
undefined4 cs_errno(long param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 0x50);
  }
  return 4;
}

