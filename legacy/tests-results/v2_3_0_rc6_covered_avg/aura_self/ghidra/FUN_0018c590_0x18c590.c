
bool FUN_0018c590(uint param_1)

{
  if (param_1 < 0x12) {
    return (1 << (ulong)(param_1 & 0x1f) & 0xbU) != 0;
  }
  return false;
}

