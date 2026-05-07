
void FUN_001f4320(long *param_1)

{
  if (param_1 == (long *)0x0) {
    PTR_malloc_00600598 = PTR_malloc_005fff68;
    PTR_free_006005a0 = PTR_free_005ffeb0;
    PTR_realloc_006005a8 = PTR_realloc_005ffec8;
    return;
  }
  PTR_malloc_00600598 = (undefined *)*param_1;
  PTR_free_006005a0 = (undefined *)param_1[1];
  if (PTR_malloc_00600598 == (undefined *)0x0) {
    PTR_malloc_00600598 = PTR_malloc_005fff68;
    if (PTR_free_006005a0 == (undefined *)0x0) goto LAB_001f436c;
  }
  else {
    if (PTR_free_006005a0 == (undefined *)0x0) {
LAB_001f436c:
      if (PTR_malloc_00600598 == PTR_malloc_005fff68) {
        PTR_free_006005a0 = PTR_free_005ffeb0;
        PTR_realloc_006005a8 = PTR_realloc_005ffec8;
        return;
      }
      PTR_free_006005a0 = PTR_free_005ffeb0;
      PTR_realloc_006005a8 = (undefined *)0x0;
      return;
    }
    if (PTR_malloc_00600598 != PTR_malloc_005fff68) {
      PTR_realloc_006005a8 = (undefined *)0x0;
      return;
    }
  }
  PTR_realloc_006005a8 = (undefined *)0x0;
  if (PTR_free_006005a0 == PTR_free_005ffeb0) {
    PTR_realloc_006005a8 = PTR_realloc_005ffec8;
    return;
  }
  return;
}

