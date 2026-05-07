
bool cJSON_IsString(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\x10';
  }
  return false;
}

