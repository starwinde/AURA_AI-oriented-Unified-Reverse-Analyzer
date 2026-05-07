
int * FUN_00144c60(char *param_1)

{
  int iVar1;
  int *__ptr;
  void *pvVar2;
  char *pcVar3;
  int *piVar4;
  size_t local_88;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (char *)0x0) && (__ptr = calloc(1,0x20), __ptr != (int *)0x0)) {
    iVar1 = open(param_1,0);
    *__ptr = iVar1;
    if (iVar1 < 0) {
      piVar4 = (int *)0x0;
      free(__ptr);
      goto LAB_00144d0c;
    }
    iVar1 = fstat(iVar1,(stat *)&stack0xffffffffffffff48);
    if ((iVar1 == 0) && (0 < (long)local_88)) {
      *(size_t *)(__ptr + 4) = local_88;
      pvVar2 = mmap((void *)0x0,local_88,1,2,*__ptr,0);
      *(void **)(__ptr + 2) = pvVar2;
      if (pvVar2 != (void *)0xffffffffffffffff) {
        pcVar3 = strdup(param_1);
        *(char **)(__ptr + 6) = pcVar3;
        piVar4 = __ptr;
        if (pcVar3 == (char *)0x0) {
          piVar4 = (int *)0x0;
          FUN_00144bf0(__ptr);
        }
        goto LAB_00144d0c;
      }
    }
    close(*__ptr);
    free(__ptr);
  }
  piVar4 = (int *)0x0;
LAB_00144d0c:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return piVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

