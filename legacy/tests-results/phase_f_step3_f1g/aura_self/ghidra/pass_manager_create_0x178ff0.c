
undefined8 * pass_manager_create(void)

{
  undefined8 uVar1;
  undefined8 *__ptr;
  void *pvVar2;
  
  __ptr = calloc(1,0x18);
  if (__ptr != (undefined8 *)0x0) {
    pvVar2 = calloc(8,0x18);
    *__ptr = pvVar2;
    uVar1 = DAT_0020a9c8;
    if (pvVar2 != (void *)0x0) {
      *(undefined4 *)(__ptr + 2) = 5;
      __ptr[1] = uVar1;
      return __ptr;
    }
    free(__ptr);
  }
  return (undefined8 *)0x0;
}

