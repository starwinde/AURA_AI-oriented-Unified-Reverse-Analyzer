
undefined2 X86_register_map(ushort param_1)

{
  if (0x114 < param_1) {
    return 0;
  }
  return *(undefined2 *)(reg_map + (ulong)param_1 * 4 + 2);
}

