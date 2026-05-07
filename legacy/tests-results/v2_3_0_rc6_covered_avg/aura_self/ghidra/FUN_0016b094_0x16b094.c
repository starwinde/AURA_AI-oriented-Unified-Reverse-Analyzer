
void FUN_0016b094(long *param_1)

{
  long lVar1;
  long lVar2;
  
  if (param_1 != (long *)0x0) {
    if ((int)param_1[1] != 0) {
      lVar2 = 0;
      do {
        lVar1 = lVar2 * 0x20;
        lVar2 = lVar2 + 1;
        free(*(void **)(*param_1 + lVar1 + 0x18));
      } while ((uint)lVar2 < *(uint *)(param_1 + 1));
    }
    free((void *)*param_1);
    free(param_1);
    return;
  }
  return;
}

