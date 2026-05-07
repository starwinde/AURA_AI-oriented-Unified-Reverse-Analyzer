
void xref_print_to(long param_1,undefined8 param_2,FILE *param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *local_70;
  uint local_68;
  void *local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_58 - *(long *)PTR___stack_chk_guard_005ffe88,
                       PTR___stack_chk_guard_005ffe88,0);
    }
    return;
  }
  if (param_3 == (FILE *)0x0) {
    param_3 = *(FILE **)PTR_stdout_005fff40;
  }
  iVar2 = xref_to(param_1,param_2,&local_70);
  __fprintf_chk(param_3,2,"Xref To 0x%lx (%u references):\n",param_2,iVar2);
  if (local_68 != 0) {
    puVar4 = local_70;
    do {
      iVar1 = *(int *)(puVar4 + 2);
      puVar3 = &DAT_001fa550;
      if ((iVar1 != 1) && (puVar3 = &DAT_001fba18, iVar1 != 2)) {
        puVar3 = &DAT_001f9ec0;
        if (iVar1 != 0) {
          puVar3 = &DAT_001faad0;
        }
      }
      puVar5 = puVar4 + 3;
      __fprintf_chk(param_3,2,"  [%s] 0x%lx -> 0x%lx\n",puVar3,*puVar4,puVar4[1]);
      puVar4 = puVar5;
    } while (puVar5 != local_70 + (ulong)local_68 * 3);
  }
  if (iVar2 == 0) {
    fwrite("  (none)\n",1,9,param_3);
  }
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  free(local_60);
  return;
}

