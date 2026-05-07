
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * cJSON_malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)global_hooks)();
  return pvVar1;
}

