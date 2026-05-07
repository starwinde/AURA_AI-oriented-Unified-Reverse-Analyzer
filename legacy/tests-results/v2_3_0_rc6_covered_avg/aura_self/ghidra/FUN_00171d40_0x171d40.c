
undefined8
FUN_00171d40(long param_1,long param_2,long param_3,undefined8 param_4,undefined8 param_5)

{
  undefined8 *__ptr;
  undefined8 uVar1;
  
  if (((param_2 != 0 && param_3 != 0) && param_1 != 0) &&
     (__ptr = calloc(1,0x10), __ptr != (undefined8 *)0x0)) {
    *__ptr = param_5;
    uVar1 = FUN_00171200(param_1,param_2,param_3,param_4,__ptr,1);
    free(__ptr);
    return uVar1;
  }
  return 0;
}

