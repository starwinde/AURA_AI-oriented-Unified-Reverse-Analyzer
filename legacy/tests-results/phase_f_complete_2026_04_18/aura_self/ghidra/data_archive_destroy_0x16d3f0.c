
void data_archive_destroy(undefined8 *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  long lVar3;
  void *__ptr;
  long lVar4;
  long *__ptr_00;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  __ptr_00 = (long *)*param_1;
  if (__ptr_00 != (long *)0x0) {
    uVar2 = *(uint *)(__ptr_00 + 1);
    __ptr = (void *)*__ptr_00;
    if (uVar2 != 0) {
      lVar4 = 0;
      do {
        while( true ) {
          lVar3 = lVar4 * 0x20;
          puVar1 = (undefined8 *)((long)__ptr + lVar3);
          if (puVar1 == (undefined8 *)0x0) break;
          lVar4 = lVar4 + 1;
          free(*(void **)((long)__ptr + lVar3));
          free((void *)puVar1[1]);
          free((void *)puVar1[2]);
          uVar2 = *(uint *)(__ptr_00 + 1);
          __ptr = (void *)*__ptr_00;
          *puVar1 = 0;
          puVar1[1] = 0;
          puVar1[2] = 0;
          if (uVar2 <= (uint)lVar4) goto LAB_0016d46c;
        }
        lVar4 = lVar4 + 1;
      } while ((uint)lVar4 < uVar2);
    }
LAB_0016d46c:
    free(__ptr);
    free((void *)__ptr_00[2]);
    free(__ptr_00);
    *param_1 = 0;
  }
  return;
}

