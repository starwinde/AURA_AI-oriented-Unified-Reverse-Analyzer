
void FUN_001907d0(void)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar1 = (**(code **)PTR_PTR_005ffed8)();
  if (lVar2 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1,PTR___stack_chk_guard_005ffe88,0,
                   lVar2 - *(long *)PTR___stack_chk_guard_005ffe88);
}

