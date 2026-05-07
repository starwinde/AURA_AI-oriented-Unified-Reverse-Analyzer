
void * aura_demangle(char *param_1)

{
  void *__ptr;
  int local_1c;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    local_1c = 0;
    __ptr = (void *)__cxa_demangle(param_1,0,0,&local_1c);
    if (local_1c == 0) goto LAB_0018601c;
    free(__ptr);
  }
  __ptr = (void *)0x0;
LAB_0018601c:
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return __ptr;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,__ptr,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

