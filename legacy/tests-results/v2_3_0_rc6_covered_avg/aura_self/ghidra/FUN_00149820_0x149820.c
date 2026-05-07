
void FUN_00149820(undefined8 *param_1)

{
  long lVar1;
  void *__ptr;
  long lVar2;
  long *__ptr_00;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr_00 = (long *)*param_1;
    if (__ptr_00 != (long *)0x0) {
      __ptr = (void *)*__ptr_00;
      if (__ptr != (void *)0x0) {
        if ((int)__ptr_00[1] != 0) {
          lVar2 = 0;
          do {
            lVar1 = lVar2 * 0x20;
            lVar2 = lVar2 + 1;
            free(*(void **)((long)__ptr + lVar1 + 0x10));
            __ptr = (void *)*__ptr_00;
          } while ((uint)lVar2 < *(uint *)(__ptr_00 + 1));
        }
        free(__ptr);
      }
      free(__ptr_00);
      *param_1 = 0;
    }
    return;
  }
  return;
}

