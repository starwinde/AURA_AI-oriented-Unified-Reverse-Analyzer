
void FUN_001d200c(undefined8 param_1,long param_2,long param_3)

{
  if (param_3 - param_2 == 0) {
    printShifter();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1,0,param_3 - param_2);
}

