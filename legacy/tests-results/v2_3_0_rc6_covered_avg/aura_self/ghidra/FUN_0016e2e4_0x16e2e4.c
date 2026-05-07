
void FUN_0016e2e4(undefined8 param_1,long param_2,long param_3,undefined8 param_4,long *param_5)

{
  undefined8 uVar1;
  long local_30;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar1 = 1;
  if (param_2 != 0 && param_3 != 0) {
    local_30 = 0;
    uVar1 = FUN_0016dca0(param_2,param_3,&local_30);
    if (((int)uVar1 == 0) && (local_30 != 0)) {
      *param_5 = local_30;
    }
  }
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1,PTR___stack_chk_guard_005ffe88,0,
                   local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
}

