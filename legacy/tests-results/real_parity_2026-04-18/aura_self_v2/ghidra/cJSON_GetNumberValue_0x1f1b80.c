
undefined1  [16] cJSON_GetNumberValue(long param_1)

{
  undefined1 auVar1 [16];
  
  if ((param_1 != 0) && (*(char *)(param_1 + 0x18) == '\b')) {
    auVar1._0_8_ = *(ulong *)(param_1 + 0x30);
    auVar1._8_8_ = 0;
    return auVar1;
  }
  return ZEXT816(0x7ff8000000000000);
}

