
void sr_result_destroy(undefined8 *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *__ptr;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  __ptr = (long *)*param_1;
  if (__ptr != (long *)0x0) {
    if ((int)__ptr[1] != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        uVar2 = uVar2 + 1;
        lVar1 = *__ptr + lVar3;
        lVar3 = lVar3 + 0x60;
        free(*(void **)(lVar1 + 8));
      } while (uVar2 < *(uint *)(__ptr + 1));
    }
    free((void *)*__ptr);
    free((void *)__ptr[2]);
    free(__ptr);
    *param_1 = 0;
  }
  return;
}

