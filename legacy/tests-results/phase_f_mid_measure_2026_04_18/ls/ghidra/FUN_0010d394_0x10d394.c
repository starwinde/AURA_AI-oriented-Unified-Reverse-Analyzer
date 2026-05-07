
tm * FUN_0010d394(long param_1,time_t *param_2,tm *param_3)

{
  long lVar1;
  tm *ptVar2;
  ulong uVar3;
  
  if (param_1 == 0) {
    ptVar2 = gmtime_r(param_2,param_3);
    return ptVar2;
  }
  lVar1 = FUN_0010d1e4();
  if (lVar1 != 0) {
    ptVar2 = localtime_r(param_2,param_3);
    if ((ptVar2 == (tm *)0x0) || (uVar3 = FUN_0010d080(param_1,param_3), (uVar3 & 1) == 0)) {
      if (lVar1 != 1) {
        FUN_0010d304(lVar1);
      }
    }
    else if ((lVar1 == 1) || (uVar3 = FUN_0010d304(lVar1), (uVar3 & 1) != 0)) {
      return param_3;
    }
  }
  return (tm *)0x0;
}

