
void FUN_00170ef4(long *param_1,long param_2,FILE *param_3)

{
  undefined8 *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long local_80;
  uint local_78;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0) {
LAB_00171068:
    lVar6 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar6 == 0) {
      return;
    }
  }
  else {
    if (param_3 == (FILE *)0x0) {
      param_3 = *(FILE **)PTR_stdout_005fff40;
    }
    __fprintf_chk(param_3,2,"=== Strings (%u found) ===\n\n",(int)param_1[1],0);
    if ((int)param_1[1] != 0) {
      lVar6 = 0;
      do {
        lVar8 = *param_1;
        lVar10 = lVar6 * 0x20;
        lVar9 = lVar8 + lVar10;
        puVar2 = &DAT_001faac0;
        if (*(undefined **)(lVar9 + 0x18) != (undefined *)0x0) {
          puVar2 = *(undefined **)(lVar9 + 0x18);
        }
        puVar3 = &DAT_001fe648;
        if (0x50 < *(uint *)(lVar9 + 0x10)) {
          puVar3 = &DAT_001fc840;
        }
        __fprintf_chk(param_3,2,"  0x%lx  [%s]  \"%.80s%s\"\n",*(undefined8 *)(lVar8 + lVar10),
                      puVar2,*(undefined8 *)(lVar9 + 8),puVar3);
        if (param_2 != 0) {
          iVar4 = FUN_001704d0(param_2,*(undefined8 *)(lVar8 + lVar10),&local_80);
          if ((iVar4 != 0) && (local_78 != 0)) {
            lVar9 = 0;
            uVar7 = 0;
            do {
              uVar7 = uVar7 + 1;
              uVar5 = FUN_001708a0(*(undefined4 *)(local_80 + lVar9 + 0x10));
              puVar1 = (undefined8 *)(local_80 + lVar9);
              lVar9 = lVar9 + 0x18;
              __fprintf_chk(param_3,2,"    <- [%s] 0x%lx\n",uVar5,*puVar1);
            } while (uVar7 < local_78);
          }
          FUN_00170860(&local_80);
        }
        lVar6 = lVar6 + 1;
      } while ((uint)lVar6 < *(uint *)(param_1 + 1));
      if (*(uint *)(param_1 + 1) != 0) goto LAB_00171068;
    }
    lVar6 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar6 == 0) {
      fwrite("  (no strings found)\n",1,0x15,param_3);
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar6);
}

