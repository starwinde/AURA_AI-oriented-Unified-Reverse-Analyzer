
void FUN_0010ad30(uint param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  undefined8 uVar4;
  
  lVar2 = *(long *)PTR___stack_chk_guard_0013ffd0;
  piVar3 = __errno_location();
  iVar1 = *piVar3;
  uVar4 = FUN_00112640(0,param_3);
  error(0,iVar1,param_2,uVar4);
  if ((param_1 & 1) == 0) {
    if (DAT_00140f40 == 0) {
      DAT_00140f40 = 1;
    }
  }
  else {
    DAT_00140f40 = 2;
  }
  if (lVar2 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,lVar2 - *(long *)PTR___stack_chk_guard_0013ffd0)
  ;
}

