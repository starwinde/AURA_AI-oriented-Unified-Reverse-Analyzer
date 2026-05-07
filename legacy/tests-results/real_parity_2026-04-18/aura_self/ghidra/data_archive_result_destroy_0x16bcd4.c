
void data_archive_result_destroy(long *param_1)

{
  if (param_1 != (long *)0x0) {
    if (*param_1 != 0) {
      free(*(void **)(*param_1 + 8));
      free((void *)*param_1);
      *param_1 = 0;
    }
    return;
  }
  return;
}

