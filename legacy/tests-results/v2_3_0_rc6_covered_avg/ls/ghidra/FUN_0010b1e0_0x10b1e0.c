
void FUN_0010b1e0(void)

{
  undefined *puVar1;
  int __sig;
  sigset_t sStack_d8;
  long local_58;
  
  puVar1 = PTR_stdout_0013ffc0;
  local_58 = *(long *)PTR___stack_chk_guard_0013ffd0;
  while ((DAT_001402b0 != 0 || (DAT_001402b4 != 0))) {
    if ((DAT_00140f84 & 1) != 0) {
      FUN_0010b000(&DAT_001400f0);
      FUN_0010b000(&DAT_00140100);
    }
    fflush_unlocked(*(FILE **)puVar1);
    sigprocmask(0,(sigset_t *)&DAT_00140f90,&sStack_d8);
    __sig = DAT_001402b0;
    if (DAT_001402b4 == 0) {
      signal(DAT_001402b0,(__sighandler_t)0x0);
    }
    else {
      DAT_001402b4 = DAT_001402b4 + -1;
      __sig = 0x13;
    }
    raise(__sig);
    sigprocmask(2,&sStack_d8,(sigset_t *)0x0);
  }
  if (local_58 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_58 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

