
void rc_cleanup(void)

{
  long lVar1;
  long *__ptr;
  long lVar2;
  
  __ptr = g_last_var_names;
  if (g_last_var_names != (long *)0x0) {
    if ((int)g_last_var_names[1] != 0) {
      lVar2 = 0;
      do {
        lVar1 = lVar2 * 8;
        lVar2 = lVar2 + 1;
        free(*(void **)(*__ptr + lVar1));
      } while ((uint)lVar2 < *(uint *)(__ptr + 1));
    }
    free((void *)*__ptr);
    free(__ptr);
    g_last_var_names = (long *)0x0;
  }
  return;
}

