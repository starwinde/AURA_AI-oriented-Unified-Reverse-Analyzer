
void disasm_destroy(long *param_1)

{
  if (param_1 == (long *)0x0) {
    return;
  }
  if (*param_1 == 0) {
    free(param_1);
    return;
  }
  cs_close();
  free(param_1);
  return;
}

