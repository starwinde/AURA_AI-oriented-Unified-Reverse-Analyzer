
void FUN_00178dc0(undefined8 *param_1)

{
  undefined8 *__ptr;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr = (undefined8 *)*param_1;
    if (__ptr != (undefined8 *)0x0) {
      free((void *)*__ptr);
      free((void *)__ptr[1]);
      free((void *)__ptr[4]);
      free((void *)__ptr[5]);
      free(__ptr);
      *param_1 = 0;
    }
    return;
  }
  return;
}

