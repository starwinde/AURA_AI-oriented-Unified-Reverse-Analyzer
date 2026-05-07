
int patch_apply(long *param_1,ulong param_2,long param_3)

{
  int iVar1;
  ulong uVar2;
  undefined1 auStack_50 [16];
  size_t local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0 || param_3 == 0) {
    iVar1 = -4;
    goto LAB_00165d74;
  }
  if (((ulong)param_1[2] <= param_2) && (uVar2 = param_2 - param_1[2], uVar2 < (ulong)param_1[1])) {
    iVar1 = patch_encode(param_3,param_2,auStack_50);
    if (iVar1 != 0) goto LAB_00165d74;
    if (local_40 + uVar2 <= (ulong)param_1[1]) {
      memcpy((void *)(*param_1 + uVar2),auStack_50,local_40);
      goto LAB_00165d74;
    }
  }
  iVar1 = -6;
LAB_00165d74:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

