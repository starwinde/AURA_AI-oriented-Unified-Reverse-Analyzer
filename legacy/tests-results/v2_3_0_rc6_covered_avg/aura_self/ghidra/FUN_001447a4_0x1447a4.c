
void FUN_001447a4(long *param_1)

{
  if (param_1 == (long *)0x0) {
    return;
  }
  if (*param_1 == 0) {
    free(param_1);
    return;
  }
  FUN_0018c810();
  free(param_1);
  return;
}

