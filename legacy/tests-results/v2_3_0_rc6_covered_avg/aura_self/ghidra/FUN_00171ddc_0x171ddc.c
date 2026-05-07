
undefined8
FUN_00171ddc(long param_1,long param_2,long param_3,undefined8 param_4,long param_5,size_t param_6)

{
  long lVar1;
  void *__ptr;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  
  if (((param_1 != 0 && param_2 != 0) && ((param_3 != 0 && param_5 != 0) && param_6 != 0)) &&
     (__ptr = calloc(param_6,0x10), __ptr != (void *)0x0)) {
    uVar4 = 0;
    do {
      lVar3 = uVar4 * 0x10;
      lVar1 = uVar4 * 8;
      uVar4 = uVar4 + 1;
      *(undefined8 *)((long)__ptr + lVar3) = *(undefined8 *)(param_5 + lVar1);
    } while (uVar4 < param_6);
    uVar2 = FUN_00171200(param_1,param_2,param_3,param_4,__ptr,param_6);
    free(__ptr);
    return uVar2;
  }
  return 0;
}

