
void param_id_analyze(long param_1,long param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_3 != 0 && param_2 != 0) && param_1 != 0) {
    param_id_run_part_0();
  }
  if (lVar1 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0,PTR___stack_chk_guard_005ffe88,0,
                   lVar1 - *(long *)PTR___stack_chk_guard_005ffe88);
}

