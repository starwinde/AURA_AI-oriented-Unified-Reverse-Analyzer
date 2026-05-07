
undefined8 FUN_0010b970(undefined8 *param_1)

{
  void *pvVar1;
  int *piVar2;
  size_t __size;
  undefined8 *__ptr;
  ulong uVar3;
  
  uVar3 = param_1[1];
  __ptr = (undefined8 *)*param_1;
  __size = uVar3 * 2;
  if (__ptr == param_1 + 2) {
    pvVar1 = malloc(__size);
    if (pvVar1 != (void *)0x0) {
      __memcpy_chk(pvVar1,__ptr,uVar3,__size);
LAB_0010b9c0:
      *param_1 = pvVar1;
      param_1[1] = __size;
      return 1;
    }
  }
  else {
    if (__size < uVar3) {
      piVar2 = __errno_location();
      *piVar2 = 0xc;
    }
    else {
      pvVar1 = realloc(__ptr,__size);
      if (pvVar1 != (void *)0x0) goto LAB_0010b9c0;
      __ptr = (undefined8 *)*param_1;
    }
    free(__ptr);
    *param_1 = param_1 + 2;
    param_1[1] = 0x400;
  }
  return 0;
}

