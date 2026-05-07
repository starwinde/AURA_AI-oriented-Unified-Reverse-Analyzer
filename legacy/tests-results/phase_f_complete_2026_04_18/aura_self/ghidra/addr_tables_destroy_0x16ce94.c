
void addr_tables_destroy(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    free((void *)*param_1);
    free(param_1);
    return;
  }
  return;
}

