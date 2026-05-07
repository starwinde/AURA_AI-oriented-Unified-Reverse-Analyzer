
void extern_resolver_destroy(long *param_1)

{
  long lVar1;
  long lVar2;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if ((int)param_1[1] != 0) {
    lVar1 = 0;
    do {
      lVar2 = lVar1 * 0x20;
      lVar1 = lVar1 + 1;
      free(*(void **)(*param_1 + lVar2));
      free(*(void **)(*param_1 + lVar2 + 0x18));
    } while ((uint)lVar1 < *(uint *)(param_1 + 1));
  }
  free((void *)*param_1);
  if ((int)param_1[3] != 0) {
    lVar1 = 0;
    do {
      lVar2 = lVar1 * 8;
      lVar1 = lVar1 + 1;
      free(*(void **)(param_1[2] + lVar2));
    } while ((uint)lVar1 < *(uint *)(param_1 + 3));
  }
  free((void *)param_1[2]);
  free(param_1);
  return;
}

