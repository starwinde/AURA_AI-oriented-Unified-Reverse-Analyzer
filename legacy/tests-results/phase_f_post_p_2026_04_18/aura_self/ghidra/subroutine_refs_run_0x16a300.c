
void subroutine_refs_run(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                        undefined8 *param_5,undefined8 *param_6)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined8 *__ptr;
  void *pvVar4;
  long lVar5;
  undefined8 *puVar6;
  char *pcVar7;
  undefined8 uVar8;
  int *piVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  ulong uVar12;
  uint uVar13;
  long lVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  long *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_5 == (undefined8 *)0x0) {
LAB_0016a5a0:
    uVar8 = 2;
    goto LAB_0016a52c;
  }
  *param_5 = 0;
  if (param_6 == (undefined8 *)0x0) {
    local_70 = (long *)xref_build(param_2,param_3);
    if (local_70 == (long *)0x0) goto LAB_0016a5a0;
  }
  else {
    *param_6 = 0;
    local_70 = (long *)xref_build(param_2,param_3);
    if (local_70 == (long *)0x0) {
      pcVar7 = strdup("subroutine_refs: xref_build failed (OOM)");
      *param_6 = pcVar7;
      goto LAB_0016a5a0;
    }
  }
  uVar2 = *(uint *)(local_70 + 1);
  if (uVar2 != 0) {
    puVar11 = (undefined8 *)*local_70;
    if (uVar2 - 1 < 4) {
      uVar3 = 0;
      uVar13 = 0;
LAB_0016a3d4:
      if (*(int *)(puVar11 + (ulong)uVar3 * 3 + 2) == 0) {
        uVar13 = uVar13 + 1;
      }
      if (uVar3 + 1 < uVar2) {
        if (*(int *)(puVar11 + (ulong)(uVar3 + 1) * 3 + 2) == 0) {
          uVar13 = uVar13 + 1;
        }
        if (uVar3 + 2 < uVar2) {
          if (*(int *)(puVar11 + (ulong)(uVar3 + 2) * 3 + 2) == 0) {
            uVar13 = uVar13 + 1;
          }
          if ((uVar3 + 3 < uVar2) && (*(int *)(puVar11 + (ulong)(uVar3 + 3) * 3 + 2) == 0)) {
            uVar13 = uVar13 + 1;
          }
        }
      }
    }
    else {
      iVar15 = 0;
      iVar16 = 0;
      iVar17 = 0;
      iVar18 = 0;
      piVar9 = (int *)(puVar11 + 2);
      do {
        piVar1 = piVar9 + 0x18;
        iVar15 = iVar15 + (uint)(*piVar9 == 0);
        iVar16 = iVar16 + (uint)(piVar9[6] == 0);
        iVar17 = iVar17 + (uint)(piVar9[0xc] == 0);
        iVar18 = iVar18 + (uint)(piVar9[0x12] == 0);
        piVar9 = piVar1;
      } while (piVar1 != (int *)((long)(puVar11 + 2) + (ulong)(uVar2 >> 2) * 0x18 * 4));
      uVar13 = iVar15 + iVar16 + iVar17 + iVar18;
      uVar3 = uVar2 & 0xfffffffc;
      if ((uVar2 & 3) != 0) goto LAB_0016a3d4;
    }
    if (uVar13 != 0) {
      __ptr = malloc(0x10);
      if (__ptr == (undefined8 *)0x0) {
        xref_table_destroy(&local_70);
        if (param_6 != (undefined8 *)0x0) {
          pcVar7 = strdup("subroutine_refs: result alloc failed");
          *param_6 = pcVar7;
        }
        uVar8 = 2;
      }
      else {
        pvVar4 = calloc((ulong)uVar13,0x18);
        *__ptr = pvVar4;
        if (pvVar4 == (void *)0x0) {
          free(__ptr);
          xref_table_destroy(&local_70);
          if (param_6 != (undefined8 *)0x0) {
            pcVar7 = strdup("subroutine_refs: refs alloc failed");
            *param_6 = pcVar7;
          }
          uVar8 = 2;
        }
        else {
          uVar3 = 0;
          uVar12 = 0;
          do {
            if (*(int *)(puVar11 + 2) == 0) {
              lVar14 = puVar11[1];
              uVar8 = *puVar11;
              lVar5 = uVar12 * 0x18;
              puVar6 = (undefined8 *)((long)pvVar4 + lVar5);
              puVar6[1] = lVar14;
              *puVar6 = uVar8;
              if (param_1 == 0) {
LAB_0016a554:
                pcVar7 = (char *)0x0;
              }
              else {
                puVar6 = *(undefined8 **)(param_1 + 0x28);
                pcVar7 = (char *)0x0;
                if (puVar6 != (undefined8 *)0x0) {
                  if (*(uint *)(param_1 + 0x30) != 0) {
                    puVar10 = puVar6 + (ulong)*(uint *)(param_1 + 0x30) * 5;
                    do {
                      if (puVar6[2] == lVar14) {
                        pcVar7 = (char *)puVar6[1];
                        if ((pcVar7 == (char *)0x0) &&
                           (pcVar7 = (char *)*puVar6, pcVar7 == (char *)0x0)) {
                          pcVar7 = (char *)0x0;
                        }
                        else {
                          pcVar7 = strdup(pcVar7);
                        }
                        goto LAB_0016a4e8;
                      }
                      puVar6 = puVar6 + 5;
                    } while (puVar6 != puVar10);
                  }
                  goto LAB_0016a554;
                }
              }
LAB_0016a4e8:
              uVar12 = (ulong)((int)uVar12 + 1);
              *(char **)((long)pvVar4 + lVar5 + 0x10) = pcVar7;
            }
            uVar3 = uVar3 + 1;
            puVar11 = puVar11 + 3;
          } while (uVar3 < uVar2 && (uint)uVar12 < uVar13);
          *(uint *)(__ptr + 1) = (uint)uVar12;
          xref_table_destroy(&local_70);
          uVar8 = 0;
          *param_5 = __ptr;
        }
      }
      goto LAB_0016a52c;
    }
  }
  xref_table_destroy(&local_70);
  uVar8 = 1;
LAB_0016a52c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar8,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

