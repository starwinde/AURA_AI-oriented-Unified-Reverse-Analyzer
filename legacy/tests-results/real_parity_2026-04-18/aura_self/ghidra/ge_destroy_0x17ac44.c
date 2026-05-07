
void ge_destroy(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      free((void *)*param_1);
      *param_1 = 0;
    }
    return;
  }
  return;
}

