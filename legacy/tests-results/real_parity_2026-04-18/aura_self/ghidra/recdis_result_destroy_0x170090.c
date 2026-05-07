
void recdis_result_destroy(long *param_1)

{
  uint uVar1;
  long *plVar2;
  void *__ptr;
  long lVar3;
  uint uVar4;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  plVar2 = (long *)*param_1;
  if (plVar2 != (long *)0x0) {
    __ptr = (void *)*plVar2;
    if ((int)plVar2[1] != 0) {
      uVar4 = 0;
      lVar3 = 0;
      do {
        uVar4 = uVar4 + 1;
        free(*(void **)((long)__ptr + lVar3 + 8));
        __ptr = *(void **)*param_1;
        uVar1 = *(uint *)((long *)*param_1 + 1);
        *(undefined8 *)((long)__ptr + lVar3 + 8) = 0;
        lVar3 = lVar3 + 0x18;
      } while (uVar4 < uVar1);
    }
    free(__ptr);
    free((void *)*param_1);
    *param_1 = 0;
  }
  return;
}

