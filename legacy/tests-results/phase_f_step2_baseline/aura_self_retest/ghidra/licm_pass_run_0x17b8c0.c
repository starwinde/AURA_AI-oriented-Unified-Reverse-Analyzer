
bool licm_pass_run(long *param_1,undefined4 *param_2)

{
  uint *puVar1;
  undefined8 *puVar2;
  bool bVar3;
  long *plVar4;
  ulong uVar5;
  void *__ptr;
  int *piVar6;
  uint *puVar7;
  size_t __size;
  undefined8 *puVar8;
  uint uVar9;
  int *piVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  long lVar20;
  long lVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  int local_90;
  long local_88;
  uint local_7c;
  long *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = 0xfffffffc;
    }
    bVar3 = false;
  }
  else {
    plVar4 = (long *)loop_detect(param_1,0);
    local_70 = plVar4;
    if (plVar4 == (long *)0x0) {
      bVar3 = false;
    }
    else {
      uVar17 = *(uint *)(plVar4 + 1);
      if (uVar17 == 0) {
        bVar3 = false;
      }
      else {
        puVar19 = (uint *)*plVar4;
        local_90 = 0;
        local_88 = 0;
        local_7c = 0;
        if (puVar19 != (uint *)0x0) goto LAB_0017b950;
LAB_0017b928:
        local_7c = local_7c + 1;
        if (local_7c < uVar17) {
          while( true ) {
            local_88 = local_88 + 0x60;
            puVar19 = (uint *)(*plVar4 + local_88);
LAB_0017b950:
            if (((puVar19[4] == 0) || (*(uint *)(param_1 + 1) <= *puVar19)) ||
               (lVar21 = *param_1 + (ulong)*puVar19 * 0x48, *(int *)(lVar21 + 0x20) == 0))
            goto LAB_0017b928;
            lVar20 = 0;
            uVar17 = 0xffffffff;
            do {
              uVar9 = *(uint *)(*(long *)(lVar21 + 0x18) + lVar20 * 4);
              uVar5 = loop_contains_block(puVar19,uVar9);
              if (((uVar5 & 1) == 0) && (bVar3 = uVar17 != 0xffffffff, uVar17 = uVar9, bVar3))
              goto LAB_0017bd18;
              lVar20 = lVar20 + 1;
            } while ((uint)lVar20 < *(uint *)(lVar21 + 0x20));
            if (*(uint *)(param_1 + 1) <= uVar17) break;
            uVar9 = puVar19[4];
            iVar16 = 0;
            lVar21 = *param_1 + (ulong)uVar17 * 0x48;
            do {
              if (uVar9 == 0) break;
              lVar20 = 0;
              bVar3 = false;
LAB_0017b9f4:
              do {
                uVar17 = *(uint *)(*(long *)(puVar19 + 2) + lVar20 * 4);
                if (uVar17 < *(uint *)(param_1 + 1)) {
                  lVar13 = *param_1 + (ulong)uVar17 * 0x48;
                  uVar17 = *(uint *)(lVar13 + 0x10);
                  if (uVar17 != 0) {
                    uVar5 = 0;
                    do {
                      while( true ) {
                        lVar12 = uVar5 * 0x88;
                        uVar18 = (uint)uVar5;
                        uVar9 = uVar18 + 1;
                        puVar2 = (undefined8 *)(*(long *)(lVar13 + 8) + lVar12);
                        uVar15 = *(uint *)(*(long *)(lVar13 + 8) + lVar12);
                        if (0x14 < uVar15) break;
                        if (uVar15 != 1) goto LAB_0017ba60;
LAB_0017ba30:
                        uVar5 = (ulong)uVar9;
                        if (uVar17 <= uVar9) goto LAB_0017bba0;
                      }
                      if (uVar15 != 0x1c) goto LAB_0017ba30;
LAB_0017ba60:
                      if (*(uint *)(puVar2 + 9) != 0) {
                        puVar8 = puVar2;
                        do {
                          if (*(int *)(puVar8 + 3) != -1) {
                            puVar7 = *(uint **)(puVar19 + 2);
                            if (puVar19[4] != 0) {
                              puVar1 = puVar7 + puVar19[4];
                              do {
                                if (*puVar7 < *(uint *)(param_1 + 1)) {
                                  lVar14 = *param_1 + (ulong)*puVar7 * 0x48;
                                  uVar15 = *(uint *)(lVar14 + 0x10);
                                  if (uVar15 != 0) {
                                    piVar6 = (int *)(*(long *)(lVar14 + 8) + 8);
                                    piVar10 = piVar6 + (ulong)uVar15 * 0x22;
                                    do {
                                      if (*(int *)(puVar8 + 3) == *piVar6) goto LAB_0017ba30;
                                      piVar6 = piVar6 + 0x22;
                                    } while (piVar6 != piVar10);
                                  }
                                }
                                puVar7 = puVar7 + 1;
                              } while (puVar7 != puVar1);
                            }
                          }
                          puVar8 = puVar8 + 2;
                        } while (puVar8 != puVar2 + (ulong)*(uint *)(puVar2 + 9) * 2);
                      }
                      uVar17 = *(uint *)(lVar21 + 0x10);
                      uVar15 = *(uint *)(lVar21 + 0x14);
                      __ptr = *(void **)(lVar21 + 8);
                      if (uVar17 == 0) {
LAB_0017bc84:
                        uVar11 = uVar17;
                        if (uVar17 < uVar15) {
                          puVar8 = (undefined8 *)((long)__ptr + (ulong)uVar17 * 0x88);
                        }
                        else {
LAB_0017baf0:
                          if (uVar15 == 0) {
                            __size = 0x220;
                            uVar15 = 4;
                          }
                          else {
                            uVar15 = uVar15 << 1;
                            __size = (ulong)uVar15 * 0x88;
                          }
                          __ptr = realloc(__ptr,__size);
                          if (__ptr == (void *)0x0) {
                            uVar17 = *(uint *)(lVar13 + 0x10);
                            goto LAB_0017ba30;
                          }
                          uVar17 = *(uint *)(lVar21 + 0x10);
                          *(void **)(lVar21 + 8) = __ptr;
                          lVar14 = (ulong)uVar11 * 0x88;
                          *(uint *)(lVar21 + 0x14) = uVar15;
                          puVar8 = (undefined8 *)((long)__ptr + lVar14);
                          if (uVar11 < uVar17) goto LAB_0017bcd4;
                        }
                      }
                      else {
                        uVar11 = uVar17 - 1;
                        lVar14 = (ulong)uVar11 * 0x88;
                        puVar8 = (undefined8 *)((long)__ptr + lVar14);
                        if (1 < *(int *)((long)__ptr + lVar14) - 0x17U &&
                            *(int *)((long)__ptr + lVar14) != 0x1a) goto LAB_0017bc84;
                        if (uVar15 <= uVar17) goto LAB_0017baf0;
LAB_0017bcd4:
                        memmove((void *)((long)__ptr + (ulong)(uVar11 + 1) * 0x88),puVar8,
                                (ulong)(uVar17 - uVar11) * 0x88);
                        puVar8 = (undefined8 *)(*(long *)(lVar21 + 8) + lVar14);
                        uVar17 = *(uint *)(lVar21 + 0x10);
                      }
                      uVar22 = *puVar2;
                      uVar24 = puVar2[3];
                      uVar23 = puVar2[2];
                      puVar8[1] = puVar2[1];
                      *puVar8 = uVar22;
                      puVar8[3] = uVar24;
                      puVar8[2] = uVar23;
                      uVar22 = puVar2[4];
                      uVar24 = puVar2[7];
                      uVar23 = puVar2[6];
                      puVar8[5] = puVar2[5];
                      puVar8[4] = uVar22;
                      puVar8[7] = uVar24;
                      puVar8[6] = uVar23;
                      uVar22 = puVar2[8];
                      uVar24 = puVar2[0xb];
                      uVar23 = puVar2[10];
                      puVar8[9] = puVar2[9];
                      puVar8[8] = uVar22;
                      puVar8[0xb] = uVar24;
                      puVar8[10] = uVar23;
                      uVar22 = puVar2[0xc];
                      uVar24 = puVar2[0xf];
                      uVar23 = puVar2[0xe];
                      puVar8[0xd] = puVar2[0xd];
                      puVar8[0xc] = uVar22;
                      puVar8[0xf] = uVar24;
                      puVar8[0xe] = uVar23;
                      puVar8[0x10] = puVar2[0x10];
                      *(uint *)(lVar21 + 0x10) = uVar17 + 1;
                      uVar17 = *(uint *)(lVar13 + 0x10);
                      if (uVar9 < uVar17) {
                        memmove((void *)(*(long *)(lVar13 + 8) + lVar12),
                                (void *)(*(long *)(lVar13 + 8) + (ulong)uVar9 * 0x88),
                                (ulong)((uVar17 - 1) - uVar18) * 0x88);
                        uVar17 = *(uint *)(lVar13 + 0x10);
                      }
                      uVar17 = uVar17 - 1;
                      *(uint *)(lVar13 + 0x10) = uVar17;
                      iVar16 = iVar16 + 1;
                      bVar3 = true;
                    } while (uVar18 < uVar17);
LAB_0017bba0:
                    uVar9 = puVar19[4];
                    lVar20 = lVar20 + 1;
                    if (uVar9 <= (uint)lVar20) break;
                    goto LAB_0017b9f4;
                  }
                }
                lVar20 = lVar20 + 1;
              } while ((uint)lVar20 < uVar9);
            } while (bVar3);
            local_90 = local_90 + iVar16;
            uVar17 = *(uint *)(local_70 + 1);
            local_7c = local_7c + 1;
            plVar4 = local_70;
            if (uVar17 <= local_7c) goto LAB_0017bbe8;
          }
LAB_0017bd18:
          uVar17 = *(uint *)(local_70 + 1);
          plVar4 = local_70;
          goto LAB_0017b928;
        }
LAB_0017bbe8:
        bVar3 = local_90 != 0;
      }
      loop_info_destroy(&local_70);
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = 0;
      }
    }
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return bVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

