
undefined1  [16] FUN_001f4c30(double param_1,long param_2)

{
  int iVar1;
  undefined1 auVar2 [16];
  
  if (param_2 != 0) {
    iVar1 = 0x7fffffff;
    if ((param_1 < 2147483647.0) && (iVar1 = -0x80000000, -2147483648.0 < param_1)) {
      iVar1 = (int)param_1;
    }
    *(int *)(param_2 + 0x28) = iVar1;
    *(double *)(param_2 + 0x30) = param_1;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = param_1;
    return auVar2;
  }
  return ZEXT816(0x7ff8000000000000);
}

