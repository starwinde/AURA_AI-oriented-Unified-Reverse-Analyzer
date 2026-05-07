
bool cJSON_IsNumber(long param_1)

{
  if (param_1 != 0) {
    return *(char *)(param_1 + 0x18) == '\b';
  }
  return false;
}

