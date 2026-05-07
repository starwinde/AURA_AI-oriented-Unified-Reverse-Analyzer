
void FUN_0016d180(void *param_1)

{
  if (param_1 != (void *)0x0) {
    free(*(void **)((long)param_1 + 8));
    free(param_1);
    return;
  }
  return;
}

