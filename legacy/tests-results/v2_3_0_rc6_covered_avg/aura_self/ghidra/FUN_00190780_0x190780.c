
void FUN_00190780(char *param_1)

{
  size_t sVar1;
  void *__dest;
  
  sVar1 = strlen(param_1);
  __dest = (void *)(**(code **)PTR_PTR_005ffed0)(sVar1 + 1);
  if (__dest != (void *)0x0) {
    memmove(__dest,param_1,sVar1 + 1);
    return;
  }
  return;
}

