
void switchD_001d2260::caseD_0(void)

{
  long in_stack_00000098;
  
  if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    printSVERegOp();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
}

