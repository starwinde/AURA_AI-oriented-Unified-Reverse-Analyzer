
void * FUN_001f4c84(long param_1,char *param_2)

{
  size_t sVar1;
  size_t sVar2;
  void *__dest;
  char *__s;
  
  if (((param_1 != 0) && ((*(ulong *)(param_1 + 0x18) & 0x110) == 0x10)) &&
     (__s = *(char **)(param_1 + 0x20), __s != (char *)0x0 && param_2 != (char *)0x0)) {
    sVar1 = strlen(param_2);
    sVar2 = strlen(__s);
    if (sVar2 < sVar1) {
      __dest = (void *)(*(code *)PTR_malloc_00600598)(sVar1 + 1);
      if (__dest != (void *)0x0) {
        memcpy(__dest,param_2,sVar1 + 1);
        if (*(long *)(param_1 + 0x20) != 0) {
          (*(code *)PTR_free_006005a0)();
        }
        *(void **)(param_1 + 0x20) = __dest;
        return __dest;
      }
    }
    else if ((param_2 + sVar1 < __s) || (__s + sVar2 < param_2)) {
      memcpy(__s,param_2,sVar1 + 1);
      return *(void **)(param_1 + 0x20);
    }
  }
  return (void *)0x0;
}

