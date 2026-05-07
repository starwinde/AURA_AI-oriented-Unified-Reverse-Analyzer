
int FUN_00183008(undefined8 param_1,long param_2,long param_3)

{
  int iVar1;
  FILE *unaff_x22;
  
  if (param_3 - param_2 == 0) {
    iVar1 = fputc(10,unaff_x22);
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1,0,param_3 - param_2);
}

