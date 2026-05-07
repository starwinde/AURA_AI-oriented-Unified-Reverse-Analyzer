
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * sa_compute_postdom(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  size_t __size;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  long lVar9;
  long *__ptr;
  void *__s;
  uint *__ptr_00;
  int *piVar10;
  uint *__ptr_01;
  void *__ptr_02;
  void *__ptr_03;
  uint *puVar11;
  uint *puVar12;
  long lVar13;
  ulong uVar14;
  undefined8 *puVar15;
  long lVar16;
  undefined8 *puVar17;
  undefined8 *puVar18;
  uint uVar19;
  int iVar20;
  uint uVar21;
  uint *puVar22;
  long lVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  long lVar27;
  uint uVar28;
  ulong uVar29;
  long lVar30;
  long lVar31;
  long lVar32;
  long lVar33;
  long lVar34;
  long lVar35;
  long *plVar36;
  undefined8 uVar37;
  undefined8 uVar38;
  uint local_6c;
  
  lVar9 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (long *)0x0) {
    uVar2 = *(uint *)(param_1 + 1);
    if ((uVar2 != 0) && (__ptr = calloc(1,0x18), __ptr != (long *)0x0)) {
      __size = (ulong)uVar2 << 2;
      __s = malloc(__size);
      *__ptr = (long)__s;
      *(uint *)(__ptr + 1) = uVar2;
      if (__s == (void *)0x0) {
        plVar36 = (long *)0x0;
        free(__ptr);
        goto LAB_0017c88c;
      }
      memset(__s,0xff,__size);
      __ptr_00 = malloc(__size);
      if (__ptr_00 == (uint *)0x0) {
        free(__s);
        plVar36 = (long *)0x0;
        free(__ptr);
        goto LAB_0017c88c;
      }
      uVar29 = 0;
      uVar19 = 0;
      lVar31 = *param_1;
      plVar36 = (long *)(lVar31 + 8);
      do {
        if ((int)plVar36[5] == 0) {
LAB_0017c36c:
          __ptr_00[uVar29] = uVar19;
          uVar29 = (ulong)((int)uVar29 + 1);
        }
        else {
          uVar21 = *(uint *)(plVar36 + 1);
          if (0 < (int)uVar21) {
            piVar10 = (int *)(*plVar36 + (ulong)uVar21 * 0x88 + -0x88);
            do {
              if (*piVar10 == 0x1a) goto LAB_0017c36c;
              piVar10 = piVar10 + -0x22;
            } while (piVar10 !=
                     (int *)((ulong)uVar21 * 0x88 + (ulong)(uVar21 - 1) * -0x88 + *plVar36 + -0x110)
                    );
          }
        }
        uVar19 = uVar19 + 1;
        plVar36 = plVar36 + 10;
        uVar28 = (uint)uVar29;
        uVar21 = uVar19;
        if (uVar19 < uVar28) {
          uVar21 = uVar28;
        }
      } while (uVar21 < uVar2);
      if (uVar28 == 0) {
        uVar29 = 1;
        *__ptr_00 = uVar2 - 1;
      }
      __ptr_01 = malloc(__size);
      __ptr_02 = malloc(__size);
      __ptr_03 = calloc((ulong)uVar2,1);
      if ((__ptr_01 == (uint *)0x0 || __ptr_02 == (void *)0x0) || __ptr_03 == (void *)0x0) {
        free(__ptr_00);
        free(__ptr_01);
        free(__ptr_02);
        free(__ptr_03);
        free(__s);
        plVar36 = (long *)0x0;
        free(__ptr);
        goto LAB_0017c88c;
      }
      puVar1 = __ptr_00 + uVar29;
      bVar7 = false;
      local_6c = 0;
      puVar11 = __ptr_00;
      do {
        while (uVar19 = *puVar11, (*(byte *)((long)__ptr_03 + (ulong)uVar19) & 1) == 0) {
          lVar35 = lVar31 + (ulong)uVar19 * 0x50;
          *(undefined1 *)((long)__ptr_03 + (ulong)uVar19) = 1;
          uVar21 = *(uint *)(lVar35 + 0x20);
          if (uVar21 != 0) {
            lVar32 = *(long *)(lVar35 + 0x18);
            lVar24 = 0;
            do {
              uVar28 = *(uint *)(lVar32 + lVar24 * 4);
              if ((uVar28 < uVar2) && ((*(byte *)((long)__ptr_03 + (ulong)uVar28) & 1) == 0)) {
                lVar13 = lVar31 + (ulong)uVar28 * 0x50;
                *(undefined1 *)((long)__ptr_03 + (ulong)uVar28) = 1;
                uVar21 = *(uint *)(lVar13 + 0x20);
                if (uVar21 != 0) {
                  lVar34 = *(long *)(lVar13 + 0x18);
                  lVar30 = 0;
                  do {
                    uVar3 = *(uint *)(lVar34 + lVar30 * 4);
                    if ((uVar3 < uVar2) && ((*(byte *)((long)__ptr_03 + (ulong)uVar3) & 1) == 0)) {
                      *(undefined1 *)((long)__ptr_03 + (ulong)uVar3) = 1;
                      lVar26 = lVar31 + (ulong)uVar3 * 0x50;
                      uVar21 = *(uint *)(lVar26 + 0x20);
                      if (uVar21 != 0) {
                        lVar23 = *(long *)(lVar26 + 0x18);
                        lVar33 = 0;
                        do {
                          uVar4 = *(uint *)(lVar23 + lVar33 * 4);
                          if ((uVar4 < uVar2) &&
                             ((*(byte *)((long)__ptr_03 + (ulong)uVar4) & 1) == 0)) {
                            *(undefined1 *)((long)__ptr_03 + (ulong)uVar4) = 1;
                            lVar25 = lVar31 + (ulong)uVar4 * 0x50;
                            uVar21 = *(uint *)(lVar25 + 0x20);
                            if (uVar21 != 0) {
                              lVar16 = *(long *)(lVar25 + 0x18);
                              lVar27 = 0;
                              do {
                                uVar5 = *(uint *)(lVar16 + lVar27 * 4);
                                if ((uVar5 < uVar2) &&
                                   ((*(byte *)((long)__ptr_03 + (ulong)uVar5) & 1) == 0)) {
                                  rpo_reverse_dfs(param_1);
                                  uVar21 = *(uint *)(lVar25 + 0x20);
                                }
                                lVar27 = lVar27 + 1;
                              } while ((uint)lVar27 < uVar21);
                            }
                            __ptr_01[local_6c] = uVar4;
                            uVar21 = *(uint *)(lVar26 + 0x20);
                            local_6c = local_6c + 1;
                          }
                          lVar33 = lVar33 + 1;
                        } while ((uint)lVar33 < uVar21);
                      }
                      __ptr_01[local_6c] = uVar3;
                      uVar21 = *(uint *)(lVar13 + 0x20);
                      local_6c = local_6c + 1;
                    }
                    lVar30 = lVar30 + 1;
                  } while ((uint)lVar30 < uVar21);
                }
                __ptr_01[local_6c] = uVar28;
                uVar21 = *(uint *)(lVar35 + 0x20);
                local_6c = local_6c + 1;
              }
              lVar24 = lVar24 + 1;
            } while ((uint)lVar24 < uVar21);
          }
          puVar11 = puVar11 + 1;
          uVar21 = local_6c + 1;
          __ptr_01[local_6c] = uVar19;
          local_6c = uVar21;
          if (puVar11 == puVar1) goto LAB_0017c4f4;
        }
        puVar11 = puVar11 + 1;
      } while (puVar11 != puVar1);
LAB_0017c4f4:
      uVar14 = (ulong)local_6c;
      uVar29 = 0;
      bVar6 = bVar7;
      do {
        if ((*(byte *)((long)__ptr_03 + uVar29) & 1) == 0) {
          __ptr_01[uVar14] = (uint)uVar29;
          uVar14 = (ulong)((int)uVar14 + 1);
          bVar6 = true;
        }
        uVar29 = uVar29 + 1;
      } while (uVar2 != uVar29);
      if (bVar6) {
        local_6c = (uint)uVar14;
      }
      uVar29 = 0;
      if (local_6c >> 1 == 0) {
        memset(__ptr_02,0xff,__size);
        puVar11 = __ptr_00;
        if (local_6c != 0) goto LAB_0017c5a0;
      }
      else {
        do {
          uVar21 = (local_6c - 1) - (int)uVar29;
          uVar19 = __ptr_01[uVar29];
          __ptr_01[uVar29] = __ptr_01[uVar21];
          uVar29 = uVar29 + 1;
          __ptr_01[uVar21] = uVar19;
        } while (uVar29 != local_6c >> 1);
        memset(__ptr_02,0xff,__size);
LAB_0017c5a0:
        uVar29 = 0;
        do {
          *(int *)((long)__ptr_02 + (ulong)__ptr_01[uVar29] * 4) = (int)uVar29;
          uVar29 = uVar29 + 1;
          puVar11 = __ptr_00;
        } while (uVar29 != local_6c);
      }
      do {
        puVar12 = puVar11 + 1;
        *(uint *)((long)__s + (ulong)*puVar11 * 4) = *puVar11;
        puVar11 = puVar12;
      } while (puVar12 != puVar1);
      if (local_6c != 0) {
        iVar20 = 1;
        puVar11 = __ptr_01;
        bVar6 = bVar7;
LAB_0017c5f0:
        uVar19 = *puVar11;
        puVar12 = __ptr_00;
        do {
          if (*puVar12 == uVar19) goto joined_r0x0017c7dc;
          puVar12 = puVar12 + 1;
        } while (puVar12 != puVar1);
        lVar35 = lVar31 + (ulong)uVar19 * 0x50;
        uVar21 = *(uint *)(lVar35 + 0x30);
        if (uVar21 != 0) {
          puVar22 = *(uint **)(lVar35 + 0x28);
          uVar28 = 0xffffffff;
          puVar12 = puVar22 + uVar21;
LAB_0017c780:
          uVar21 = *puVar22;
          uVar3 = uVar28;
          if (((uVar21 < uVar2) && (uVar29 = (ulong)uVar21, *(int *)((long)__s + uVar29 * 4) != -1))
             && (uVar3 = uVar21, uVar28 != 0xffffffff)) {
            while (uVar3 = uVar28, uVar21 != uVar28) {
              while( true ) {
                uVar4 = *(uint *)((long)__ptr_02 + (ulong)uVar28 * 4);
                if (uVar4 <= *(uint *)((long)__ptr_02 + uVar29 * 4)) break;
                uVar3 = *(uint *)((long)__s + (ulong)uVar28 * 4);
                if (uVar3 == uVar28) goto LAB_0017c848;
                uVar28 = uVar3;
                if (uVar3 == 0xffffffff) goto LAB_0017c7a8;
              }
              while( true ) {
                uVar3 = uVar21;
                if (uVar21 == 0xffffffff) goto LAB_0017c7a8;
                uVar29 = (ulong)uVar21;
                if (*(uint *)((long)__ptr_02 + uVar29 * 4) <= uVar4) break;
                uVar3 = *(uint *)((long)__s + uVar29 * 4);
                bVar8 = uVar3 == uVar21;
                uVar21 = uVar3;
                if (bVar8) goto LAB_0017c848;
              }
            }
          }
          goto LAB_0017c7a8;
        }
        goto joined_r0x0017c7dc;
      }
      iVar20 = 1;
LAB_0017c854:
      *(undefined1 *)((long)__ptr + 0xc) = 0;
      *(int *)(__ptr + 2) = iVar20;
      goto LAB_0017c85c;
    }
  }
  plVar36 = (long *)0x0;
  goto LAB_0017c88c;
LAB_0017c848:
  uVar3 = 0xffffffff;
LAB_0017c7a8:
  uVar28 = uVar3;
  puVar22 = puVar22 + 1;
  if (puVar22 == puVar12) goto code_r0x0017c7b4;
  goto LAB_0017c780;
code_r0x0017c7b4:
  if ((uVar28 != 0xffffffff) && (*(uint *)((long)__s + (ulong)uVar19 * 4) != uVar28)) {
    *(uint *)((long)__s + (ulong)uVar19 * 4) = uVar28;
    bVar6 = true;
  }
joined_r0x0017c7dc:
  puVar11 = puVar11 + 1;
  if (puVar11 != __ptr_01 + local_6c) goto LAB_0017c5f0;
  if (!bVar6) goto LAB_0017c854;
  if (iVar20 != 20000) {
    iVar20 = iVar20 + 1;
    puVar11 = __ptr_01;
    bVar6 = bVar7;
    goto LAB_0017c5f0;
  }
  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                "[aura] sa_compute_postdom watchdog: function 0x%llx did not converge after %u iterations, aborting (block_count=%u)\n"
                ,param_1[3],20000,(ulong)uVar2);
  *(undefined1 *)((long)__ptr + 0xc) = 1;
  *(undefined4 *)(__ptr + 2) = 20000;
  puVar15 = (undefined8 *)*__ptr;
  if (uVar2 < 4) {
    uVar19 = 0;
LAB_0017c93c:
    uVar21 = uVar19 + 1;
    *(uint *)((long)puVar15 + (ulong)uVar19 * 4) = uVar19;
    if (uVar21 < uVar2) {
      uVar19 = uVar19 + 2;
      *(uint *)((long)puVar15 + (ulong)uVar21 * 4) = uVar21;
      if (uVar19 < uVar2) {
        *(uint *)((long)puVar15 + (ulong)uVar19 * 4) = uVar19;
      }
    }
  }
  else {
    puVar17 = puVar15;
    uVar37 = _DAT_0020b140;
    uVar38 = _UNK_0020b148;
    do {
      puVar18 = puVar17 + 2;
      puVar17[1] = uVar38;
      *puVar17 = uVar37;
      puVar17 = puVar18;
      uVar37 = CONCAT44((int)((ulong)uVar37 >> 0x20) + 4,(int)uVar37 + 4);
      uVar38 = CONCAT44((int)((ulong)uVar38 >> 0x20) + 4,(int)uVar38 + 4);
    } while (puVar18 != puVar15 + (ulong)(uVar2 >> 2) * 2);
    uVar19 = uVar2 & 0xfffffffc;
    if ((uVar2 & 3) != 0) goto LAB_0017c93c;
  }
LAB_0017c85c:
  free(__ptr_00);
  free(__ptr_01);
  free(__ptr_02);
  free(__ptr_03);
  plVar36 = __ptr;
LAB_0017c88c:
  if (lVar9 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar36;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar9 - *(long *)PTR___stack_chk_guard_005ffe88)
  ;
}

