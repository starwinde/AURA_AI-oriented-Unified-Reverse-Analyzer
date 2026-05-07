
undefined2 AArch64_map_vregister(uint param_1)

{
  if (0x29f < param_1) {
    return 0;
  }
  return *(undefined2 *)(&RegAsmOffsetvreg_0 + (ulong)(param_1 - 1) * 2);
}

