
void FUN_001129a0(undefined8 param_1)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR___stack_chk_guard_0013ffd0;
  uVar1 = FUN_00112640(0,param_1);
  if (lVar2 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1,PTR___stack_chk_guard_0013ffd0,0,
                   lVar2 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

