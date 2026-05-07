
void FUN_0014ae20(undefined8 *param_1)

{
  undefined8 *__ptr;
  undefined8 *puVar1;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr = (undefined8 *)*param_1;
    if (__ptr != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)*__ptr;
      if (puVar1 != (undefined8 *)0x0) {
        free((void *)*puVar1);
        free(puVar1);
      }
      puVar1 = (undefined8 *)__ptr[1];
      if (puVar1 != (undefined8 *)0x0) {
        free((void *)*puVar1);
        free(puVar1);
      }
      free(__ptr);
      *param_1 = 0;
    }
    return;
  }
  return;
}

