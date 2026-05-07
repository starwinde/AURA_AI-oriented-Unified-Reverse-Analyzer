
undefined4 dead_store_pass_run(long *param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  undefined4 uVar4;
  long local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == (long *)0x0) || ((int)param_1[1] == 0)) ||
     (local_50 = alias_analyze(param_1,(int)param_1[1],0), local_50 == 0)) {
    uVar4 = 0;
  }
  else {
    if ((int)param_1[1] == 0) {
      uVar4 = 0;
    }
    else {
      lVar3 = 0;
      uVar4 = 0;
      uVar2 = 0;
      do {
        uVar2 = uVar2 + 1;
        iVar1 = eliminate_dead_stores_in_block(*param_1 + lVar3,local_50);
        lVar3 = lVar3 + 0x50;
        if (0 < iVar1) {
          uVar4 = 1;
        }
      } while (uVar2 < *(uint *)(param_1 + 1));
    }
    alias_result_destroy(&local_50);
  }
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar4;
}

