
bool cJSON_IsNull(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\x04';
  }
  return false;
}

