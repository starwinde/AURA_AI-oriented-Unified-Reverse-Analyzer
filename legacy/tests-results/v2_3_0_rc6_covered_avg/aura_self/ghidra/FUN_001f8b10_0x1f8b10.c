
bool FUN_001f8b10(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\x02';
  }
  return false;
}

