
undefined8 FUN_0018700c(undefined8 param_1,undefined8 param_2,long param_3,long param_4)

{
  if (param_4 - param_3 == 0) {
    return param_2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1,param_2,0,param_4 - param_3);
}

