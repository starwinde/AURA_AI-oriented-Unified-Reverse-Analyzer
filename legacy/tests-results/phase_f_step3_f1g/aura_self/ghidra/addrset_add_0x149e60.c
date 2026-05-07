
undefined8 addrset_add(undefined8 *param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  void *__ptr;
  
  uVar2 = *(uint *)(param_1 + 1);
  uVar1 = *(uint *)((long)param_1 + 0xc);
  __ptr = (void *)*param_1;
  if (uVar1 <= uVar2) {
    __ptr = realloc(__ptr,((ulong)uVar1 & 0x7fffffff) << 4);
    if (__ptr == (void *)0x0) {
      return 0;
    }
    uVar2 = *(uint *)(param_1 + 1);
    *param_1 = __ptr;
    *(uint *)((long)param_1 + 0xc) = uVar1 << 1;
  }
  *(uint *)(param_1 + 1) = uVar2 + 1;
  *(undefined8 *)((long)__ptr + (ulong)uVar2 * 8) = param_2;
  return 1;
}

