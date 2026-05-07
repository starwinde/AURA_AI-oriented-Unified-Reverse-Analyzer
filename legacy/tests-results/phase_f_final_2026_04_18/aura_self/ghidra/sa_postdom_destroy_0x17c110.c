
void sa_postdom_destroy(long *param_1)

{
  if (param_1 != (long *)0x0) {
    if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
      free(*(void **)*param_1);
      free((void *)*param_1);
      *param_1 = 0;
    }
    return;
  }
  return;
}

