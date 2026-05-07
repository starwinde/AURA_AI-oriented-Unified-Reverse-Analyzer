
void FUN_00178844(undefined8 *param_1)

{
  long lVar1;
  long lVar2;
  void *__ptr;
  uint uVar3;
  
  if (param_1 != (undefined8 *)0x0) {
    __ptr = (void *)*param_1;
    if (__ptr != (void *)0x0) {
      if (*(int *)((long)__ptr + 0x20) != 0) {
        lVar2 = 0;
        uVar3 = 0;
        do {
          uVar3 = uVar3 + 1;
          free(*(void **)(*(long *)((long)__ptr + 0x18) + lVar2 + 0x10));
          lVar1 = *(long *)((long)__ptr + 0x18) + lVar2;
          lVar2 = lVar2 + 0x30;
          free(*(void **)(lVar1 + 0x18));
        } while (uVar3 < *(uint *)((long)__ptr + 0x20));
      }
      free(*(void **)((long)__ptr + 0x18));
      free(__ptr);
      *param_1 = 0;
    }
    return;
  }
  return;
}

