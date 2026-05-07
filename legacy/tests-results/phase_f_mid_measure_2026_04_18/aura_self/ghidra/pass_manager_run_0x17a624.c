
int pass_manager_run(long *param_1,long param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  int iVar4;
  code *pcVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  long lVar10;
  uint uVar11;
  int local_6c;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0 && param_2 != 0) && ((int)param_1[1] != 0)) {
    iVar1 = (int)param_1[2];
    if (iVar1 < 1) {
      iVar1 = 5;
    }
    iVar9 = 0;
    do {
      lVar10 = 0;
      uVar11 = 0;
      uVar7 = 0;
      do {
        lVar6 = *param_1;
        pcVar5 = *(code **)(lVar6 + lVar10 + 0x10);
        if ((pcVar5 == (code *)0x0) || (uVar3 = (*pcVar5)(param_2), uVar8 = uVar7, (uVar3 & 1) != 0)
           ) {
          local_6c = 0;
          uVar2 = (**(code **)(lVar6 + lVar10 + 8))(param_2,&local_6c);
          iVar4 = local_6c;
          if (local_6c != 0) goto LAB_0017a724;
          uVar8 = uVar2 & 0xff;
          if ((uVar2 & 1) == 0) {
            uVar8 = uVar7;
          }
        }
        uVar11 = uVar11 + 1;
        lVar10 = lVar10 + 0x18;
        uVar7 = uVar8;
      } while (uVar11 < *(uint *)(param_1 + 1));
    } while ((((uVar8 & 1) != 0) && (iVar9 = iVar9 + 1, iVar1 != iVar9)) &&
            (*(uint *)(param_1 + 1) != 0));
  }
  iVar4 = 0;
LAB_0017a724:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar4,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return iVar4;
}

