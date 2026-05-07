
int FUN_001f11a4(long param_1,long param_2,long param_3)

{
  int iVar1;
  undefined1 auStack_58 [64];
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    iVar1 = -0x7feffffc;
  }
  else {
    iVar1 = FUN_001f0af4(param_1,0);
    if (-1 < iVar1) {
      iVar1 = FUN_001f106c(param_1,param_2,param_3,auStack_58);
    }
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar1,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

