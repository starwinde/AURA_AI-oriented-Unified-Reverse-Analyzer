
bool FUN_001f8ad0(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\0';
  }
  return false;
}

