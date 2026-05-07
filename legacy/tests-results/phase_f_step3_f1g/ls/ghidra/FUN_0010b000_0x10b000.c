
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0010b000(size_t *param_1)

{
  int iVar1;
  __pid_t _Var2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  _union_1457 local_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 local_68;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if ((DAT_00140f84 & 1) == 0) {
    DAT_00140f84 = 1;
    _Var2 = tcgetpgrp(1);
    if (-1 < _Var2) {
      piVar4 = &DAT_00118470;
      sigemptyset((sigset_t *)&DAT_00140f90);
      piVar5 = piVar4;
      do {
        iVar1 = *piVar5;
        sigaction(iVar1,(sigaction *)0x0,(sigaction *)&local_f0);
        if (local_f0.sa_handler != (__sighandler_t)0x1) {
          sigaddset((sigset_t *)&DAT_00140f90,iVar1);
        }
        piVar5 = piVar5 + 1;
      } while (piVar5 != (int *)&DAT_001184a0);
      local_68 = 0x10000000;
      uStack_e0 = uRam0000000000140f98;
      local_e8 = _DAT_00140f90;
      uStack_d0 = uRam0000000000140fa8;
      uStack_d8 = _DAT_00140fa0;
      uStack_c0 = uRam0000000000140fb8;
      local_c8 = _DAT_00140fb0;
      uStack_b0 = uRam0000000000140fc8;
      uStack_b8 = _DAT_00140fc0;
      uStack_a0 = uRam0000000000140fd8;
      local_a8 = _DAT_00140fd0;
      uStack_90 = uRam0000000000140fe8;
      uStack_98 = _DAT_00140fe0;
      uStack_80 = uRam0000000000140ff8;
      local_88 = _DAT_00140ff0;
      uStack_70 = uRam0000000000141008;
      uStack_78 = _DAT_00141000;
      do {
        iVar1 = *piVar4;
        iVar3 = sigismember((sigset_t *)&DAT_00140f90,iVar1);
        if (iVar3 != 0) {
          local_f0 = (_union_1457)FUN_00105f50;
          if (iVar1 == 0x14) {
            local_f0 = (_union_1457)FUN_00105f80;
          }
          sigaction(iVar1,(sigaction *)&local_f0,(sigaction *)0x0);
        }
        piVar4 = piVar4 + 1;
      } while (piVar4 != (int *)&DAT_001184a0);
    }
    if (DAT_00140118 == 0) {
      FUN_0010b000(&DAT_001400f0);
      FUN_0010b000(&DAT_00140120);
      FUN_0010b000(&DAT_00140100);
    }
    else {
      FUN_0010b000(&DAT_00140110);
    }
  }
  if (local_58 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                     local_58 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  fwrite_unlocked((void *)param_1[1],*param_1,1,*(FILE **)PTR_stdout_0013ffc0);
  return;
}

