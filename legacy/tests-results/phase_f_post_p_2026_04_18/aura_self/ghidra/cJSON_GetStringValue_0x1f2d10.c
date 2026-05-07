
undefined8 cJSON_GetStringValue(long param_1)

{
  undefined8 uVar1;
  
  if (param_1 != 0) {
    uVar1 = 0;
    if (*(char *)(param_1 + 0x18) == '\x10') {
      uVar1 = *(undefined8 *)(param_1 + 0x20);
    }
    return uVar1;
  }
  return 0;
}

