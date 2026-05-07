
undefined8
candidateset_add(undefined8 *param_1,undefined8 param_2,undefined1 param_3,undefined1 param_4,
                undefined2 param_5)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  size_t __size;
  void *__ptr;
  int iVar4;
  
  if (param_1 == (undefined8 *)0x0) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 1);
  uVar2 = *(uint *)((long)param_1 + 0xc);
  __ptr = (void *)*param_1;
  if (uVar2 <= uVar1) {
    if (uVar2 == 0) {
      __size = 0x400;
      iVar4 = 0x40;
    }
    else {
      iVar4 = uVar2 << 1;
      __size = ((ulong)uVar2 & 0x7fffffff) << 5;
    }
    __ptr = realloc(__ptr,__size);
    if (__ptr == (void *)0x0) {
      return 0;
    }
    uVar1 = *(uint *)(param_1 + 1);
    *param_1 = __ptr;
    *(int *)((long)param_1 + 0xc) = iVar4;
  }
  lVar3 = (ulong)uVar1 * 0x10;
  *(uint *)(param_1 + 1) = uVar1 + 1;
  *(undefined8 *)((long)__ptr + lVar3) = param_2;
  *(undefined1 *)((long)__ptr + lVar3 + 8) = param_3;
  *(undefined1 *)((long)__ptr + lVar3 + 9) = param_4;
  *(undefined2 *)((long)__ptr + lVar3 + 10) = param_5;
  return 1;
}

