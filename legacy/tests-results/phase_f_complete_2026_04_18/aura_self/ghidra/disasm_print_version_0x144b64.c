
void disasm_print_version(void)

{
  int iVar1;
  undefined4 local_20;
  undefined4 uStack_1c;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar1 = cs_version(&local_20,&uStack_1c,PTR___stack_chk_guard_005ffe88,0);
  if (iVar1 == 0) {
    __printf_chk(2,"Capstone version unknown (error: %u)\n",0);
  }
  else {
    __printf_chk(2,"Capstone v%d.%d\n",local_20,uStack_1c);
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

