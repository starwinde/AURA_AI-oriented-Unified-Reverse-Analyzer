
void FUN_0015a3f4(void)

{
  long lVar1;
  long *__ptr;
  long lVar2;
  
  __ptr = DAT_006005f0;
  if (DAT_006005f0 != (long *)0x0) {
    if ((int)DAT_006005f0[1] != 0) {
      lVar2 = 0;
      do {
        lVar1 = lVar2 * 8;
        lVar2 = lVar2 + 1;
        free(*(void **)(*__ptr + lVar1));
      } while ((uint)lVar2 < *(uint *)(__ptr + 1));
    }
    free((void *)*__ptr);
    free(__ptr);
    DAT_006005f0 = (long *)0x0;
  }
  return;
}

