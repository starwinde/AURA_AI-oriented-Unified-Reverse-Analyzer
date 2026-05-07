
undefined2 FUN_001dbbb0(uint param_1)

{
  if (0x29f < param_1) {
    return 0;
  }
  return *(undefined2 *)(&DAT_002d53b0 + (ulong)(param_1 - 1) * 2);
}

