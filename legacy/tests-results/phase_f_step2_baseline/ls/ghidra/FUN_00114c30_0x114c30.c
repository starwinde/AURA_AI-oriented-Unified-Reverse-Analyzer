
undefined8 *
FUN_00114c30(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *__ptr;
  ulong uVar1;
  size_t __nmemb;
  void *pvVar2;
  int *piVar3;
  
  __ptr = malloc(0x50);
  if (__ptr != (undefined8 *)0x0) {
    __ptr[5] = &DAT_001184a0;
    uVar1 = FUN_0010bb04();
    if ((uVar1 & 1) == 0) {
      piVar3 = __errno_location();
      *piVar3 = 0x16;
    }
    else {
      __nmemb = FUN_00114b40(0x3f4ccccd,param_1,0);
      __ptr[2] = __nmemb;
      if (__nmemb != 0) {
        pvVar2 = calloc(__nmemb,0x10);
        *__ptr = pvVar2;
        if (pvVar2 != (void *)0x0) {
          __ptr[1] = (void *)((long)pvVar2 + __nmemb * 0x10);
          __ptr[3] = 0;
          __ptr[4] = 0;
          __ptr[6] = param_2;
          __ptr[7] = param_3;
          __ptr[8] = param_4;
          __ptr[9] = 0;
          return __ptr;
        }
      }
    }
    free(__ptr);
  }
  return (undefined8 *)0x0;
}

