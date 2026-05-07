
undefined8 FUN_0010b8d0(undefined8 *param_1)

{
  void *pvVar1;
  int *piVar2;
  ulong uVar3;
  ulong __size;
  
  uVar3 = param_1[1];
  __size = uVar3 << 1;
  if ((undefined8 *)*param_1 != param_1 + 2) {
    free((undefined8 *)*param_1);
    uVar3 = param_1[1];
  }
  if (__size < uVar3) {
    piVar2 = __errno_location();
    *piVar2 = 0xc;
  }
  else {
    pvVar1 = malloc(__size);
    if (pvVar1 != (void *)0x0) {
      *param_1 = pvVar1;
      param_1[1] = __size;
      return 1;
    }
  }
  *param_1 = param_1 + 2;
  param_1[1] = 0x400;
  return 0;
}

