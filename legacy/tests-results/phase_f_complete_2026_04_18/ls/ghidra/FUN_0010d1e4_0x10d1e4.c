
void * FUN_0010d1e4(long param_1)

{
  int iVar1;
  char *__s2;
  undefined8 *__ptr;
  int *piVar2;
  void *pvVar3;
  
  __s2 = getenv("TZ");
  if (__s2 == (char *)0x0) {
    if (*(char *)(param_1 + 8) == '\0') {
      return (void *)0x1;
    }
  }
  else {
    if (*(char *)(param_1 + 8) == '\0') {
      __ptr = (undefined8 *)FUN_00107ec0();
      if (__ptr == (void *)0x0) {
        return (void *)0x0;
      }
      iVar1 = unsetenv("TZ");
      goto joined_r0x0010d28c;
    }
    iVar1 = strcmp((char *)(param_1 + 9),__s2);
    if (iVar1 == 0) {
      return (void *)0x1;
    }
  }
  __ptr = (undefined8 *)FUN_00107ec0(__s2);
  if (__ptr == (void *)0x0) {
    return (void *)0x0;
  }
  iVar1 = setenv("TZ",(char *)(param_1 + 9),1);
joined_r0x0010d28c:
  if (iVar1 != 0) {
    piVar2 = __errno_location();
    iVar1 = *piVar2;
    if (__ptr != (void *)0x1) {
      do {
        pvVar3 = (void *)*__ptr;
        free(__ptr);
        __ptr = pvVar3;
      } while (pvVar3 != (void *)0x0);
    }
    *piVar2 = iVar1;
    return (void *)0x0;
  }
  tzset();
  return __ptr;
}

