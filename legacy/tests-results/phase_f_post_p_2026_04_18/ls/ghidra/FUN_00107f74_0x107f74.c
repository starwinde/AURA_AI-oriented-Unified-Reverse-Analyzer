
void FUN_00107f74(undefined8 param_1)

{
  int iVar1;
  long local_20;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_0013ffd0;
  iVar1 = FUN_001109d0(param_1,0,&local_20,"",0);
  if (iVar1 == 0) {
    if (local_20 < 0) {
      local_20 = 0;
    }
  }
  else {
    local_20 = -(ulong)(iVar1 != 1);
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(local_20,PTR___stack_chk_guard_0013ffd0,0,
                     local_18 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return;
}

