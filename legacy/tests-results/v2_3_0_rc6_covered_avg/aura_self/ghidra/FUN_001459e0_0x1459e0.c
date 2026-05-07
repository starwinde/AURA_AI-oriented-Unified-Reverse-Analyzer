
long FUN_001459e0(long param_1)

{
  int iVar1;
  long lVar2;
  long local_30;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != 0) {
    local_30 = FUN_00144c60(param_1,PTR___stack_chk_guard_005ffe88,0);
    if (local_30 != 0) {
      lVar2 = FUN_00144d80(&local_30);
      if (lVar2 == 0) {
        lVar2 = 0;
        FUN_00144bf0(local_30);
        goto LAB_00145a2c;
      }
      iVar1 = FUN_00145274();
      if (iVar1 == 0) goto LAB_00145a2c;
      FUN_00144de4(lVar2);
    }
  }
  lVar2 = 0;
LAB_00145a2c:
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return lVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
}

