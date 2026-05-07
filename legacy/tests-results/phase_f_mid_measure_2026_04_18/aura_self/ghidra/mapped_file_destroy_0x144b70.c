
void mapped_file_destroy(int *param_1)

{
  if (param_1 == (int *)0x0) {
    return;
  }
  if ((long)*(void **)(param_1 + 2) - 1U < 0xfffffffffffffffe) {
    munmap(*(void **)(param_1 + 2),*(size_t *)(param_1 + 4));
  }
  if (*param_1 < 0) {
    free(*(void **)(param_1 + 6));
    free(param_1);
    return;
  }
  close(*param_1);
  free(*(void **)(param_1 + 6));
  free(param_1);
  return;
}

