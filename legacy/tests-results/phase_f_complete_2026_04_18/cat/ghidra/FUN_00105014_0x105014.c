
void FUN_00105014(void)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR___stack_chk_guard_0011ffe0;
  uVar1 = FUN_00104d70();
  if (lVar2 - *(long *)PTR___stack_chk_guard_0011ffe0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1,PTR___stack_chk_guard_0011ffe0,0,
                   lVar2 - *(long *)PTR___stack_chk_guard_0011ffe0);
}

