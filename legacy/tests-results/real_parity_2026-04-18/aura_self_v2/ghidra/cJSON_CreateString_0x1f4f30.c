
undefined8 * cJSON_CreateString(char *param_1)

{
  undefined8 *puVar1;
  size_t sVar2;
  void *__dest;
  
  puVar1 = (undefined8 *)(*(code *)global_hooks)(0x40);
  if (puVar1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *(undefined4 *)(puVar1 + 3) = 0x10;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    if (param_1 != (char *)0x0) {
      sVar2 = strlen(param_1);
      __dest = (void *)(*(code *)global_hooks)(sVar2 + 1);
      if (__dest != (void *)0x0) {
        memcpy(__dest,param_1,sVar2 + 1);
        puVar1[4] = __dest;
        return puVar1;
      }
      puVar1[4] = 0;
    }
    cJSON_Delete(puVar1);
  }
  return (undefined8 *)0x0;
}

