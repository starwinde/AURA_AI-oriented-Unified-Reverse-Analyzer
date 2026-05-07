
undefined8 * sa_compute_postdom(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  size_t __size;
  bool bVar6;
  bool bVar7;
  long lVar8;
  void *__s;
  uint *__ptr;
  int *piVar9;
  uint *__ptr_00;
  void *__ptr_01;
  void *__ptr_02;
  uint *puVar10;
  uint *puVar11;
  uint uVar12;
  long lVar13;
  uint uVar14;
  ulong uVar15;
  long *plVar16;
  uint *puVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  uint uVar22;
  ulong uVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  long lVar27;
  long lVar28;
  long lVar29;
  long lVar30;
  long lVar31;
  undefined8 *local_108;
  uint local_6c;
  
  lVar8 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (long *)0x0) {
    uVar2 = *(uint *)(param_1 + 1);
    if ((uVar2 != 0) && (local_108 = calloc(1,0x10), local_108 != (undefined8 *)0x0)) {
      __size = (ulong)uVar2 << 2;
      __s = malloc(__size);
      *local_108 = __s;
      *(uint *)(local_108 + 1) = uVar2;
      if (__s == (void *)0x0) {
        free(local_108);
        local_108 = (undefined8 *)0x0;
        goto LAB_0017a628;
      }
      memset(__s,0xff,__size);
      __ptr = malloc(__size);
      if (__ptr == (uint *)0x0) {
        free(__s);
        free(local_108);
        local_108 = (undefined8 *)0x0;
        goto LAB_0017a628;
      }
      uVar23 = 0;
      uVar14 = 0;
      lVar28 = *param_1;
      plVar16 = (long *)(lVar28 + 8);
      do {
        if ((int)plVar16[5] == 0) {
LAB_0017a340:
          __ptr[uVar23] = uVar14;
          uVar23 = (ulong)((int)uVar23 + 1);
        }
        else {
          uVar12 = *(uint *)(plVar16 + 1);
          if (0 < (int)uVar12) {
            piVar9 = (int *)(*plVar16 + (ulong)uVar12 * 0x88 + -0x88);
            do {
              if (*piVar9 == 0x1a) goto LAB_0017a340;
              piVar9 = piVar9 + -0x22;
            } while (piVar9 != (int *)((ulong)uVar12 * 0x88 + (ulong)(uVar12 - 1) * -0x88 +
                                      *plVar16 + -0x110));
          }
        }
        uVar14 = uVar14 + 1;
        plVar16 = plVar16 + 9;
        uVar22 = (uint)uVar23;
        uVar12 = uVar14;
        if (uVar14 < uVar22) {
          uVar12 = uVar22;
        }
      } while (uVar12 < uVar2);
      if (uVar22 == 0) {
        uVar23 = 1;
        *__ptr = uVar2 - 1;
      }
      __ptr_00 = malloc(__size);
      __ptr_01 = malloc(__size);
      __ptr_02 = calloc((ulong)uVar2,1);
      if ((__ptr_00 == (uint *)0x0 || __ptr_01 == (void *)0x0) || __ptr_02 == (void *)0x0) {
        free(__ptr);
        free(__ptr_00);
        free(__ptr_01);
        free(__ptr_02);
        free(__s);
        free(local_108);
        local_108 = (undefined8 *)0x0;
        goto LAB_0017a628;
      }
      puVar1 = __ptr + uVar23;
      local_6c = 0;
      puVar10 = __ptr;
      do {
        while (uVar14 = *puVar10, (*(byte *)((long)__ptr_02 + (ulong)uVar14) & 1) != 0) {
          puVar10 = puVar10 + 1;
          if (puVar10 == puVar1) goto LAB_0017a4d0;
        }
        lVar29 = lVar28 + (ulong)uVar14 * 0x48;
        *(undefined1 *)((long)__ptr_02 + (ulong)uVar14) = 1;
        uVar12 = *(uint *)(lVar29 + 0x20);
        if (uVar12 != 0) {
          lVar27 = *(long *)(lVar29 + 0x18);
          lVar20 = 0;
          do {
            uVar22 = *(uint *)(lVar27 + lVar20 * 4);
            if ((uVar22 < uVar2) && ((*(byte *)((long)__ptr_02 + (ulong)uVar22) & 1) == 0)) {
              lVar19 = lVar28 + (ulong)uVar22 * 0x48;
              *(undefined1 *)((long)__ptr_02 + (ulong)uVar22) = 1;
              uVar12 = *(uint *)(lVar19 + 0x20);
              if (uVar12 != 0) {
                lVar13 = *(long *)(lVar19 + 0x18);
                lVar30 = 0;
                do {
                  uVar3 = *(uint *)(lVar13 + lVar30 * 4);
                  if ((uVar3 < uVar2) && ((*(byte *)((long)__ptr_02 + (ulong)uVar3) & 1) == 0)) {
                    *(undefined1 *)((long)__ptr_02 + (ulong)uVar3) = 1;
                    lVar26 = lVar28 + (ulong)uVar3 * 0x48;
                    uVar12 = *(uint *)(lVar26 + 0x20);
                    if (uVar12 != 0) {
                      lVar31 = *(long *)(lVar26 + 0x18);
                      lVar21 = 0;
                      do {
                        uVar4 = *(uint *)(lVar31 + lVar21 * 4);
                        if ((uVar4 < uVar2) && ((*(byte *)((long)__ptr_02 + (ulong)uVar4) & 1) == 0)
                           ) {
                          *(undefined1 *)((long)__ptr_02 + (ulong)uVar4) = 1;
                          lVar25 = lVar28 + (ulong)uVar4 * 0x48;
                          uVar12 = *(uint *)(lVar25 + 0x20);
                          if (uVar12 != 0) {
                            lVar18 = *(long *)(lVar25 + 0x18);
                            lVar24 = 0;
                            do {
                              uVar5 = *(uint *)(lVar18 + lVar24 * 4);
                              if ((uVar5 < uVar2) &&
                                 ((*(byte *)((long)__ptr_02 + (ulong)uVar5) & 1) == 0)) {
                                rpo_reverse_dfs(param_1);
                                uVar12 = *(uint *)(lVar25 + 0x20);
                              }
                              lVar24 = lVar24 + 1;
                            } while ((uint)lVar24 < uVar12);
                          }
                          __ptr_00[local_6c] = uVar4;
                          uVar12 = *(uint *)(lVar26 + 0x20);
                          local_6c = local_6c + 1;
                        }
                        lVar21 = lVar21 + 1;
                      } while ((uint)lVar21 < uVar12);
                    }
                    __ptr_00[local_6c] = uVar3;
                    uVar12 = *(uint *)(lVar19 + 0x20);
                    local_6c = local_6c + 1;
                  }
                  lVar30 = lVar30 + 1;
                } while ((uint)lVar30 < uVar12);
              }
              __ptr_00[local_6c] = uVar22;
              uVar12 = *(uint *)(lVar29 + 0x20);
              local_6c = local_6c + 1;
            }
            lVar20 = lVar20 + 1;
          } while ((uint)lVar20 < uVar12);
        }
        puVar10 = puVar10 + 1;
        uVar12 = local_6c + 1;
        __ptr_00[local_6c] = uVar14;
        local_6c = uVar12;
      } while (puVar10 != puVar1);
LAB_0017a4d0:
      uVar15 = (ulong)local_6c;
      uVar23 = 0;
      bVar6 = false;
      do {
        if ((*(byte *)((long)__ptr_02 + uVar23) & 1) == 0) {
          __ptr_00[uVar15] = (uint)uVar23;
          uVar15 = (ulong)((int)uVar15 + 1);
          bVar6 = true;
        }
        uVar23 = uVar23 + 1;
      } while (uVar2 != uVar23);
      if (bVar6) {
        local_6c = (uint)uVar15;
      }
      uVar23 = 0;
      if (local_6c >> 1 == 0) {
        memset(__ptr_01,0xff,__size);
        puVar10 = __ptr;
        if (local_6c != 0) goto LAB_0017a578;
      }
      else {
        do {
          uVar12 = (local_6c - 1) - (int)uVar23;
          uVar14 = __ptr_00[uVar23];
          __ptr_00[uVar23] = __ptr_00[uVar12];
          uVar23 = uVar23 + 1;
          __ptr_00[uVar12] = uVar14;
        } while (uVar23 != local_6c >> 1);
        memset(__ptr_01,0xff,__size);
LAB_0017a578:
        uVar23 = 0;
        do {
          *(int *)((long)__ptr_01 + (ulong)__ptr_00[uVar23] * 4) = (int)uVar23;
          uVar23 = uVar23 + 1;
          puVar10 = __ptr;
        } while (uVar23 != local_6c);
      }
      do {
        puVar11 = puVar10 + 1;
        *(uint *)((long)__s + (ulong)*puVar10 * 4) = *puVar10;
        puVar10 = puVar11;
      } while (puVar11 != puVar1);
      if (local_6c != 0) {
LAB_0017a5b4:
        bVar6 = false;
        puVar10 = __ptr_00;
LAB_0017a5c0:
        uVar14 = *puVar10;
        puVar11 = __ptr;
        do {
          if (*puVar11 == uVar14) goto joined_r0x0017a804;
          puVar11 = puVar11 + 1;
        } while (puVar11 != puVar1);
        lVar29 = lVar28 + (ulong)uVar14 * 0x48;
        uVar12 = *(uint *)(lVar29 + 0x30);
        if (uVar12 != 0) {
          puVar17 = *(uint **)(lVar29 + 0x28);
          uVar22 = 0xffffffff;
          puVar11 = puVar17 + uVar12;
LAB_0017a7a8:
          uVar12 = *puVar17;
          uVar3 = uVar22;
          if (((uVar12 < uVar2) && (uVar23 = (ulong)uVar12, *(int *)((long)__s + uVar23 * 4) != -1))
             && (uVar3 = uVar12, uVar22 != 0xffffffff)) {
            while (uVar3 = uVar22, uVar12 != uVar22) {
              while( true ) {
                uVar4 = *(uint *)((long)__ptr_01 + (ulong)uVar22 * 4);
                if (uVar4 <= *(uint *)((long)__ptr_01 + uVar23 * 4)) break;
                uVar3 = *(uint *)((long)__s + (ulong)uVar22 * 4);
                if (uVar3 == uVar22) goto LAB_0017a870;
                uVar22 = uVar3;
                if (uVar3 == 0xffffffff) goto LAB_0017a7d0;
              }
              while( true ) {
                uVar3 = uVar12;
                if (uVar12 == 0xffffffff) goto LAB_0017a7d0;
                uVar23 = (ulong)uVar12;
                if (*(uint *)((long)__ptr_01 + uVar23 * 4) <= uVar4) break;
                uVar3 = *(uint *)((long)__s + uVar23 * 4);
                bVar7 = uVar3 == uVar12;
                uVar12 = uVar3;
                if (bVar7) goto LAB_0017a870;
              }
            }
          }
          goto LAB_0017a7d0;
        }
        goto joined_r0x0017a804;
      }
LAB_0017a5f4:
      free(__ptr);
      free(__ptr_00);
      free(__ptr_01);
      free(__ptr_02);
      goto LAB_0017a628;
    }
  }
  local_108 = (undefined8 *)0x0;
LAB_0017a628:
  if (lVar8 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     lVar8 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_108;
LAB_0017a870:
  uVar3 = 0xffffffff;
LAB_0017a7d0:
  uVar22 = uVar3;
  puVar17 = puVar17 + 1;
  if (puVar17 == puVar11) goto code_r0x0017a7dc;
  goto LAB_0017a7a8;
code_r0x0017a7dc:
  if ((uVar22 != 0xffffffff) && (*(uint *)((long)__s + (ulong)uVar14 * 4) != uVar22)) {
    *(uint *)((long)__s + (ulong)uVar14 * 4) = uVar22;
    bVar6 = true;
  }
joined_r0x0017a804:
  puVar10 = puVar10 + 1;
  if (puVar10 == __ptr_00 + local_6c) goto LAB_0017a5f0;
  goto LAB_0017a5c0;
LAB_0017a5f0:
  if (!bVar6) goto LAB_0017a5f4;
  goto LAB_0017a5b4;
}

