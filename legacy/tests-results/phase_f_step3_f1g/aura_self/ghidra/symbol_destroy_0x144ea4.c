
void symbol_destroy(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    free((void *)*param_1);
    *param_1 = 0;
    free((void *)param_1[1]);
    param_1[1] = 0;
    return;
  }
  return;
}

