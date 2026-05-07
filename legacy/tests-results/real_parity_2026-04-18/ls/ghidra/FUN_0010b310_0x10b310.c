
void FUN_0010b310(undefined8 param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  lVar3 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (param_3 == -1) {
    uVar1 = dcgettext(0,"invalid argument %s for %s",5,PTR___stack_chk_guard_0013ffd0,0);
  }
  else {
    uVar1 = dcgettext(0,"ambiguous argument %s for %s",5,PTR___stack_chk_guard_0013ffd0,0);
  }
  uVar2 = FUN_00112640(0,param_2);
  FUN_00112640(1,param_1,&DAT_00140088);
  if (lVar3 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    error(0,0,uVar1,uVar2);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(lVar3 - *(long *)PTR___stack_chk_guard_0013ffd0,PTR___stack_chk_guard_0013ffd0,0)
  ;
}

