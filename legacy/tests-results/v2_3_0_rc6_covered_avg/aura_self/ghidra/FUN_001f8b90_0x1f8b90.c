
bool FUN_001f8b90(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\x10';
  }
  return false;
}

