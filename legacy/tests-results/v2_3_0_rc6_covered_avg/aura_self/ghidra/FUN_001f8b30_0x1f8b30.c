
bool FUN_001f8b30(long param_1)

{
  if (param_1 != 0) {
    return (*(uint *)(param_1 + 0x18) & 3) != 0;
  }
  return false;
}

