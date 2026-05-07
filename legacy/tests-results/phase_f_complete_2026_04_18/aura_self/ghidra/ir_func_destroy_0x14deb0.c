
void ir_func_destroy(undefined8 *param_1)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  long *__ptr;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  __ptr = (long *)*param_1;
  if (__ptr != (long *)0x0) {
    if ((int)__ptr[1] != 0) {
      lVar6 = 0;
      uVar5 = 0;
      do {
        lVar1 = *__ptr + lVar6;
        if (*(int *)(lVar1 + 0x10) != 0) {
          lVar4 = 0;
          uVar3 = 0;
          do {
            uVar3 = uVar3 + 1;
            lVar2 = *(long *)(lVar1 + 8) + lVar4;
            lVar4 = lVar4 + 0x90;
            free(*(void **)(lVar2 + 0x50));
            free(*(void **)(lVar2 + 0x58));
          } while (uVar3 < *(uint *)(lVar1 + 0x10));
        }
        uVar5 = uVar5 + 1;
        lVar6 = lVar6 + 0x50;
        free(*(void **)(lVar1 + 8));
        free(*(void **)(lVar1 + 0x18));
        free(*(void **)(lVar1 + 0x28));
        free(*(void **)(lVar1 + 0x38));
      } while (uVar5 < *(uint *)(__ptr + 1));
    }
    free((void *)*__ptr);
    free(__ptr);
    *param_1 = 0;
  }
  return;
}

