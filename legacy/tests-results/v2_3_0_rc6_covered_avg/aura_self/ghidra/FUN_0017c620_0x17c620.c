
void FUN_0017c620(undefined8 *param_1)

{
  long lVar1;
  long lVar2;
  long *__ptr;
  uint uVar3;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr = (long *)*param_1;
    if (__ptr != (long *)0x0) {
      if ((int)__ptr[1] != 0) {
        lVar2 = 0;
        uVar3 = 0;
        do {
          uVar3 = uVar3 + 1;
          free(*(void **)(*__ptr + lVar2 + 8));
          lVar1 = *__ptr + lVar2;
          lVar2 = lVar2 + 0x60;
          free(*(void **)(lVar1 + 0x50));
        } while (uVar3 < *(uint *)(__ptr + 1));
      }
      free((void *)*__ptr);
      free((void *)__ptr[2]);
      free(__ptr);
      *param_1 = 0;
    }
    return;
  }
  return;
}

