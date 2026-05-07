
void reloc_table_destroy(undefined8 *param_1)

{
  long lVar1;
  long lVar2;
  long *__ptr;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr = (long *)*param_1;
    if (__ptr != (long *)0x0) {
      if ((int)__ptr[1] != 0) {
        lVar2 = 0;
        do {
          lVar1 = lVar2 * 0x20;
          lVar2 = lVar2 + 1;
          free(*(void **)(*__ptr + lVar1 + 8));
        } while ((uint)lVar2 < *(uint *)(__ptr + 1));
      }
      free((void *)*__ptr);
      free(__ptr);
      *param_1 = 0;
    }
    return;
  }
  return;
}

