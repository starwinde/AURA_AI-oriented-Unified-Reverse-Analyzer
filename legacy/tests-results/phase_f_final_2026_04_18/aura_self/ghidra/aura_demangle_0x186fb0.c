
void aura_demangle(char *param_1)

{
  void *__ptr;
  int local_1c;
  undefined8 local_18;
  
  local_18 = *(undefined8 *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    local_1c = 0;
    __ptr = (void *)__cxa_demangle(param_1,0,0,&local_1c);
    if (local_1c == 0) goto LAB_00186ffc;
    free(__ptr);
  }
  __ptr = (void *)0x0;
LAB_00186ffc:
  e843419_004b_0000028f_58(PTR___stack_chk_guard_005ffe88,__ptr);
  return;
}

