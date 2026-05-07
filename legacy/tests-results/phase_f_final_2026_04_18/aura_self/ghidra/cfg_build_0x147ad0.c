
long * cfg_build(ulong *param_1,ulong param_2,long param_3)

{
  size_t sVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  ulong *__ptr;
  size_t sVar8;
  size_t sVar9;
  long *__ptr_00;
  void *pvVar10;
  void *pvVar11;
  ulong *__ptr_01;
  ulong *puVar12;
  char *pcVar13;
  ulong *puVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  uint uVar18;
  uint uVar19;
  undefined4 uVar20;
  uint uVar21;
  long lVar22;
  size_t sVar23;
  ulong uVar24;
  uint uVar25;
  ulong uVar26;
  undefined8 *puVar27;
  long lVar28;
  ulong uVar29;
  uint uVar30;
  ulong uVar31;
  ulong local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (ulong *)0x0 || param_2 == 0) {
    __ptr_00 = calloc(1,0x28);
    if (__ptr_00 != (long *)0x0) {
      __ptr_00[4] = param_3;
    }
  }
  else {
    __ptr = malloc(0x100);
    if (__ptr != (ulong *)0x0) {
      sVar23 = 1;
      puVar14 = param_1 + 0xc;
      uVar26 = 0;
      *__ptr = *param_1;
      uVar24 = 0x20;
      do {
        uVar26 = uVar26 + 1;
        uVar6 = branch_classify(puVar14 + -8);
        __ptr_01 = __ptr;
        uVar17 = uVar24;
        if (uVar6 != 0) {
          if (uVar26 < param_2) {
            uVar29 = puVar14[0x10];
            if (sVar23 != 0) {
              uVar16 = 0;
              do {
                if (uVar29 == __ptr[uVar16]) goto LAB_00147b8c;
                uVar16 = uVar16 + 1;
              } while (uVar16 != sVar23);
            }
            if (uVar24 <= sVar23) {
              uVar17 = uVar24 << 1;
              __ptr_01 = realloc(__ptr,uVar24 << 4);
              if (__ptr_01 == (ulong *)0x0) goto LAB_00147fdc;
            }
            __ptr_01[sVar23] = uVar29;
            sVar23 = sVar23 + 1;
          }
LAB_00147b8c:
          if (uVar6 < 9) {
            if (uVar6 < 7) {
              if ((uVar6 == 4) || ((uVar6 & 0xfffffffb) == 2)) {
                iVar7 = parse_one_target_token(puVar14,&local_70);
LAB_00147f10:
                uVar24 = local_70;
                if (iVar7 != 0) {
                  if (sVar23 != 0) {
                    uVar29 = 0;
                    do {
                      if (local_70 == __ptr_01[uVar29]) goto LAB_00147bb0;
                      uVar29 = uVar29 + 1;
                    } while (uVar29 != sVar23);
                  }
                  puVar12 = __ptr_01;
                  uVar29 = uVar17;
                  if (uVar17 <= sVar23) {
                    uVar29 = uVar17 << 1;
                    puVar12 = realloc(__ptr_01,uVar17 << 4);
                    __ptr = __ptr_01;
                    if (puVar12 == (ulong *)0x0) goto LAB_00147fdc;
                  }
                  puVar12[sVar23] = uVar24;
                  sVar23 = sVar23 + 1;
                  __ptr_01 = puVar12;
                  uVar17 = uVar29;
                }
              }
            }
            else {
              pcVar13 = strrchr((char *)puVar14,0x2c);
              if (pcVar13 != (char *)0x0) {
                iVar7 = parse_one_target_token(pcVar13 + 1,&local_70);
                goto LAB_00147f10;
              }
            }
          }
        }
LAB_00147bb0:
        puVar14 = puVar14 + 0x1c;
        __ptr = __ptr_01;
        uVar24 = uVar17;
      } while (uVar26 < param_2);
      qsort(__ptr_01,sVar23,8,addr_cmp);
      if (sVar23 == 0) {
        uVar26 = 0;
      }
      else {
        sVar8 = 0;
        uVar26 = 0;
        do {
          while( true ) {
            puVar14 = __ptr_01 + sVar8;
            lVar15 = 0;
            if ((uVar26 == 0) || (lVar15 = uVar26 * 8, __ptr_01[uVar26 - 1] != *puVar14)) break;
            do {
              sVar9 = sVar8;
              sVar1 = sVar9 + 1;
              if (sVar1 == sVar23) goto LAB_00147c50;
              sVar8 = sVar1;
            } while (__ptr_01[uVar26 - 1] == __ptr_01[sVar1]);
            sVar8 = sVar9 + 2;
            __ptr_01[uVar26] = __ptr_01[sVar1];
            uVar26 = uVar26 + 1;
            if (sVar8 == sVar23) goto LAB_00147c50;
          }
          sVar8 = sVar8 + 1;
          *(ulong *)((long)__ptr_01 + lVar15) = *puVar14;
          uVar26 = uVar26 + 1;
        } while (sVar8 != sVar23);
      }
LAB_00147c50:
      __ptr_00 = calloc(1,0x28);
      if (__ptr_00 != (long *)0x0) {
        *(undefined4 *)((long)__ptr_00 + 0x1c) = 0x20;
        *(undefined4 *)((long)__ptr_00 + 0xc) = 0x10;
        __ptr_00[4] = param_3;
        pvVar10 = malloc(0x200);
        *__ptr_00 = (long)pvVar10;
        pvVar11 = malloc(0x180);
        __ptr_00[2] = (long)pvVar11;
        if (pvVar10 != (void *)0x0 && pvVar11 != (void *)0x0) {
          uVar24 = 0;
          puVar27 = (undefined8 *)0x0;
          do {
            uVar16 = *param_1;
            uVar17 = 0;
            uVar29 = uVar26;
            while (uVar31 = uVar29, uVar17 < uVar31) {
              uVar29 = uVar17 + (uVar31 - uVar17 >> 1);
              if (uVar16 == __ptr_01[uVar29]) {
                if (puVar27 != (undefined8 *)0x0) {
                  puVar27[1] = uVar16;
                }
                uVar6 = *(uint *)(__ptr_00 + 1);
                uVar30 = *(uint *)((long)__ptr_00 + 0xc);
                pvVar11 = (void *)*__ptr_00;
                pvVar10 = pvVar11;
                if (uVar30 <= uVar6) {
                  pvVar10 = realloc(pvVar11,((ulong)uVar30 & 0x7fffffff) << 6);
                  if (pvVar10 == (void *)0x0) {
                    if (pvVar11 != (void *)0x0) {
                      lVar15 = 0;
                      if (uVar6 != 0) {
                        do {
                          lVar22 = lVar15 * 0x20;
                          lVar15 = lVar15 + 1;
                          free(*(void **)(*__ptr_00 + lVar22 + 0x10));
                        } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                      }
                      free((void *)*__ptr_00);
                    }
                    goto LAB_00147fcc;
                  }
                  *__ptr_00 = (long)pvVar10;
                  *(uint *)((long)__ptr_00 + 0xc) = uVar30 << 1;
                }
                puVar27 = (undefined8 *)((long)pvVar10 + (ulong)uVar6 * 0x20);
                *(uint *)(__ptr_00 + 1) = uVar6 + 1;
                pvVar11 = (void *)0x0;
                sVar23 = 0x700;
                uVar30 = 8;
                *puVar27 = 0;
                puVar27[1] = 0;
                puVar27[2] = 0;
                puVar27[3] = 0;
                *(ulong *)((long)pvVar10 + (ulong)uVar6 * 0x20) = *param_1;
                goto LAB_0014808c;
              }
              if (__ptr_01[uVar29] <= uVar16) {
                uVar17 = uVar29 + 1;
                uVar29 = uVar31;
              }
            }
            if (puVar27 != (undefined8 *)0x0) {
              uVar6 = *(uint *)(puVar27 + 3);
              uVar30 = *(uint *)((long)puVar27 + 0x1c);
              pvVar11 = (void *)puVar27[2];
              if (uVar6 < uVar30) {
LAB_00147d00:
                uVar29 = param_1[1];
                uVar17 = *param_1;
                uVar31 = param_1[3];
                uVar16 = param_1[2];
                puVar14 = (ulong *)((long)pvVar11 + (ulong)uVar6 * 0xe0);
                *(uint *)(puVar27 + 3) = uVar6 + 1;
                puVar14[1] = uVar29;
                *puVar14 = uVar17;
                puVar14[3] = uVar31;
                puVar14[2] = uVar16;
                uVar17 = param_1[4];
                uVar16 = param_1[7];
                uVar29 = param_1[6];
                puVar14[5] = param_1[5];
                puVar14[4] = uVar17;
                puVar14[7] = uVar16;
                puVar14[6] = uVar29;
                uVar17 = param_1[8];
                uVar16 = param_1[0xb];
                uVar29 = param_1[10];
                puVar14[9] = param_1[9];
                puVar14[8] = uVar17;
                puVar14[0xb] = uVar16;
                puVar14[10] = uVar29;
                uVar17 = param_1[0xc];
                uVar16 = param_1[0xf];
                uVar29 = param_1[0xe];
                puVar14[0xd] = param_1[0xd];
                puVar14[0xc] = uVar17;
                puVar14[0xf] = uVar16;
                puVar14[0xe] = uVar29;
                uVar17 = param_1[0x10];
                uVar16 = param_1[0x13];
                uVar29 = param_1[0x12];
                puVar14[0x11] = param_1[0x11];
                puVar14[0x10] = uVar17;
                puVar14[0x13] = uVar16;
                puVar14[0x12] = uVar29;
                uVar17 = param_1[0x14];
                uVar16 = param_1[0x17];
                uVar29 = param_1[0x16];
                puVar14[0x15] = param_1[0x15];
                puVar14[0x14] = uVar17;
                puVar14[0x17] = uVar16;
                puVar14[0x16] = uVar29;
                uVar17 = param_1[0x18];
                uVar16 = param_1[0x1b];
                uVar29 = param_1[0x1a];
                puVar14[0x19] = param_1[0x19];
                puVar14[0x18] = uVar17;
                puVar14[0x1b] = uVar16;
                puVar14[0x1a] = uVar29;
                iVar7 = branch_classify(param_1 + 4);
                if (iVar7 != 0) {
                  puVar27[1] = *param_1 + param_1[3];
                  goto LAB_00147d60;
                }
                goto LAB_00147d64;
              }
              if (uVar30 == 0) {
                sVar23 = 0x700;
                uVar30 = 8;
              }
              else {
                uVar30 = uVar30 << 1;
                sVar23 = (ulong)uVar30 * 0xe0;
              }
LAB_0014808c:
              pvVar11 = realloc(pvVar11,sVar23);
              if (pvVar11 != (void *)0x0) {
                uVar6 = *(uint *)(puVar27 + 3);
                puVar27[2] = pvVar11;
                *(uint *)((long)puVar27 + 0x1c) = uVar30;
                goto LAB_00147d00;
              }
              pvVar10 = (void *)*__ptr_00;
              if (pvVar10 != (void *)0x0) {
                lVar15 = 0;
                if ((int)__ptr_00[1] != 0) {
                  do {
                    lVar22 = lVar15 * 0x20;
                    lVar15 = lVar15 + 1;
                    free(*(void **)((long)pvVar10 + lVar22 + 0x10));
                    pvVar10 = (void *)*__ptr_00;
                  } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                }
                free(pvVar10);
              }
LAB_00147fcc:
              pvVar11 = (void *)__ptr_00[2];
              goto LAB_00147fd0;
            }
LAB_00147d60:
            puVar27 = (undefined8 *)0x0;
LAB_00147d64:
            uVar24 = uVar24 + 1;
            param_1 = param_1 + 0x1c;
          } while (uVar24 < param_2);
          if ((puVar27 != (undefined8 *)0x0) && (*(int *)(puVar27 + 3) != 0)) {
            lVar15 = (ulong)(*(int *)(puVar27 + 3) - 1) * 0xe0;
            puVar27[1] = *(long *)(puVar27[2] + lVar15) + *(long *)(puVar27[2] + lVar15 + 0x18);
          }
          free(__ptr_01);
          uVar6 = *(uint *)(__ptr_00 + 1);
          if (uVar6 != 0) {
            lVar15 = 0;
            uVar30 = 1;
LAB_00147e2c:
            lVar28 = *__ptr_00;
            lVar22 = lVar28 + lVar15 * 0x20;
            iVar7 = *(int *)(lVar22 + 0x18);
            if (iVar7 == 0) goto LAB_00147e18;
            uVar3 = (undefined4)lVar15;
            lVar22 = *(long *)(lVar22 + 0x10) + (ulong)(iVar7 - 1) * 0xe0;
            iVar7 = branch_classify(lVar22 + 0x20);
            if (iVar7 == 1) {
              uVar21 = *(uint *)(__ptr_00 + 3);
              pvVar10 = (void *)__ptr_00[2];
              if (*(uint *)((long)__ptr_00 + 0x1c) <= uVar21) {
                uVar18 = *(uint *)((long)__ptr_00 + 0x1c) << 1;
                pvVar10 = realloc(pvVar10,(ulong)uVar18 * 0xc);
                if (pvVar10 == (void *)0x0) {
                  if (lVar28 != 0) {
                    lVar15 = 0;
                    do {
                      lVar22 = lVar15 * 0x20;
                      lVar15 = lVar15 + 1;
                      free(*(void **)(*__ptr_00 + lVar22 + 0x10));
                    } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                    pvVar10 = (void *)*__ptr_00;
                    goto LAB_001483dc;
                  }
                  goto LAB_001483e0;
                }
                __ptr_00[2] = (long)pvVar10;
                *(uint *)((long)__ptr_00 + 0x1c) = uVar18;
              }
              *(uint *)(__ptr_00 + 3) = uVar21 + 1;
              *(undefined4 *)((long)pvVar10 + (ulong)uVar21 * 0xc) = uVar3;
              *(undefined8 *)((long)pvVar10 + (ulong)uVar21 * 0xc + 4) = 0x4ffffffff;
              goto LAB_00147e18;
            }
            if (iVar7 - 4U < 2) {
              if (((iVar7 == 4) &&
                  (iVar7 = parse_one_target_token(lVar22 + 0x60,&local_70), iVar7 != 0)) &&
                 (*(uint *)(__ptr_00 + 1) != 0)) {
                uVar26 = 0;
                do {
                  if (local_70 == *(ulong *)(*__ptr_00 + uVar26 * 0x20)) {
                    uVar6 = *(uint *)(__ptr_00 + 3);
                    uVar21 = *(uint *)((long)__ptr_00 + 0x1c);
                    uVar20 = (undefined4)uVar26;
                    pvVar10 = (void *)__ptr_00[2];
                    uVar4 = uVar20;
                    if (uVar6 < uVar21) goto LAB_00147ecc;
                    goto LAB_0014820c;
                  }
                  uVar26 = uVar26 + 1;
                } while (uVar26 != *(uint *)(__ptr_00 + 1));
              }
              uVar6 = *(uint *)(__ptr_00 + 3);
              uVar21 = *(uint *)((long)__ptr_00 + 0x1c);
              uVar20 = 0xffffffff;
              pvVar10 = (void *)__ptr_00[2];
              uVar4 = 0xffffffff;
              if (uVar21 <= uVar6) {
LAB_0014820c:
                uVar20 = uVar4;
                pvVar10 = realloc(pvVar10,(ulong)(uVar21 << 1) * 0xc);
                if (pvVar10 == (void *)0x0) {
                  pvVar10 = (void *)*__ptr_00;
                  if (pvVar10 == (void *)0x0) goto LAB_001483e0;
                  lVar15 = 0;
                  if ((int)__ptr_00[1] != 0) {
                    do {
                      lVar22 = lVar15 * 0x20;
                      lVar15 = lVar15 + 1;
                      free(*(void **)((long)pvVar10 + lVar22 + 0x10));
                      pvVar10 = (void *)*__ptr_00;
                    } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                  }
                  goto LAB_001483dc;
                }
                __ptr_00[2] = (long)pvVar10;
                *(uint *)((long)__ptr_00 + 0x1c) = uVar21 << 1;
              }
LAB_00147ecc:
              lVar22 = (ulong)uVar6 * 0xc;
              *(uint *)(__ptr_00 + 3) = uVar6 + 1;
              uVar6 = *(uint *)(__ptr_00 + 1);
              *(undefined4 *)((long)pvVar10 + lVar22) = uVar3;
              *(undefined4 *)((long)pvVar10 + lVar22 + 4) = uVar20;
              *(undefined4 *)((long)pvVar10 + lVar22 + 8) = 0;
              goto LAB_00147e18;
            }
            if (2 < iVar7 - 6U) {
              pvVar10 = (void *)__ptr_00[2];
              uVar21 = *(uint *)(__ptr_00 + 3);
              uVar18 = *(uint *)((long)__ptr_00 + 0x1c);
              if (iVar7 - 2U < 2) {
                if (uVar18 <= uVar21) {
                  uVar18 = uVar18 << 1;
                  pvVar10 = realloc(pvVar10,(ulong)uVar18 * 0xc);
                  if (pvVar10 == (void *)0x0) {
                    if (lVar28 != 0) {
                      lVar15 = 0;
                      do {
                        lVar22 = lVar15 * 0x20;
                        lVar15 = lVar15 + 1;
                        free(*(void **)(*__ptr_00 + lVar22 + 0x10));
                      } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                      pvVar10 = (void *)*__ptr_00;
                      goto LAB_001483dc;
                    }
                    goto LAB_001483e0;
                  }
                  __ptr_00[2] = (long)pvVar10;
                  *(uint *)((long)__ptr_00 + 0x1c) = uVar18;
                }
                uVar25 = uVar21 + 1;
                *(uint *)(__ptr_00 + 3) = uVar25;
                uVar19 = uVar30;
                if (uVar6 <= uVar30) {
                  uVar19 = 0xffffffff;
                }
                *(undefined4 *)((long)pvVar10 + (ulong)uVar21 * 0xc) = uVar3;
                *(undefined8 *)((long)pvVar10 + (ulong)uVar21 * 0xc + 4) = 0x3ffffffff;
                if (uVar18 <= uVar25) {
                  pvVar10 = realloc(pvVar10,(ulong)(uVar18 << 1) * 0xc);
                  if (pvVar10 == (void *)0x0) {
                    if (lVar28 != 0) {
                      lVar15 = 0;
                      do {
                        lVar22 = lVar15 * 0x20;
                        lVar15 = lVar15 + 1;
                        free(*(void **)(*__ptr_00 + lVar22 + 0x10));
                      } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                      pvVar10 = (void *)*__ptr_00;
                      goto LAB_001483dc;
                    }
                    goto LAB_001483e0;
                  }
                  __ptr_00[2] = (long)pvVar10;
                  *(uint *)((long)__ptr_00 + 0x1c) = uVar18 << 1;
                }
                lVar22 = (ulong)uVar25 * 0xc;
                *(uint *)(__ptr_00 + 3) = uVar21 + 2;
                *(undefined4 *)((long)pvVar10 + lVar22) = uVar3;
                *(uint *)((long)pvVar10 + lVar22 + 4) = uVar19;
                *(undefined4 *)((long)pvVar10 + lVar22 + 8) = 0;
                goto LAB_00147e18;
              }
              uVar25 = uVar30;
              if (uVar6 <= uVar30) {
                uVar25 = 0xffffffff;
              }
              if (uVar21 < uVar18) {
LAB_00147dfc:
                lVar22 = (ulong)uVar21 * 0xc;
                *(uint *)(__ptr_00 + 3) = uVar21 + 1;
                *(undefined4 *)((long)pvVar10 + lVar22) = uVar3;
                *(uint *)((long)pvVar10 + lVar22 + 4) = uVar25;
                *(undefined4 *)((long)pvVar10 + lVar22 + 8) = 0;
                goto LAB_00147e18;
              }
              pvVar10 = realloc(pvVar10,(ulong)(uVar18 << 1) * 0xc);
              if (pvVar10 != (void *)0x0) {
                __ptr_00[2] = (long)pvVar10;
                *(uint *)((long)__ptr_00 + 0x1c) = uVar18 << 1;
                goto LAB_00147dfc;
              }
              if (lVar28 == 0) goto LAB_001483e0;
              lVar15 = 0;
              do {
                lVar22 = lVar15 * 0x20;
                lVar15 = lVar15 + 1;
                free(*(void **)(*__ptr_00 + lVar22 + 0x10));
              } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
              pvVar10 = (void *)*__ptr_00;
LAB_001483dc:
              free(pvVar10);
LAB_001483e0:
              free((void *)__ptr_00[2]);
              free(__ptr_00);
              goto LAB_00147fe8;
            }
            pcVar13 = (char *)(lVar22 + 0x60);
            if (iVar7 - 7U < 2) {
              pcVar13 = strrchr(pcVar13,0x2c);
              if (pcVar13 != (char *)0x0) {
                pcVar13 = pcVar13 + 1;
                goto LAB_00148150;
              }
LAB_00148324:
              uVar21 = 0xffffffff;
LAB_00148198:
              uVar18 = uVar30;
              if (uVar6 <= uVar30) {
                uVar18 = 0xffffffff;
              }
            }
            else {
LAB_00148150:
              iVar7 = parse_one_target_token(pcVar13,&local_70);
              uVar6 = *(uint *)(__ptr_00 + 1);
              if (iVar7 == 0) goto LAB_00148324;
              if (uVar6 != 0) {
                uVar26 = 0;
                do {
                  if (local_70 == *(ulong *)(*__ptr_00 + uVar26 * 0x20)) {
                    uVar21 = (uint)uVar26;
                    goto LAB_00148198;
                  }
                  uVar26 = uVar26 + 1;
                } while (uVar26 != uVar6);
                goto LAB_00148324;
              }
              uVar21 = 0xffffffff;
              uVar18 = uVar21;
            }
            uVar25 = *(uint *)(__ptr_00 + 3);
            uVar19 = *(uint *)((long)__ptr_00 + 0x1c);
            pvVar10 = (void *)__ptr_00[2];
            if (uVar19 <= uVar25) {
              uVar19 = uVar19 << 1;
              pvVar10 = realloc(pvVar10,(ulong)uVar19 * 0xc);
              if (pvVar10 == (void *)0x0) {
                pvVar10 = (void *)*__ptr_00;
                if (pvVar10 == (void *)0x0) goto LAB_001483e0;
                lVar15 = 0;
                if (uVar6 != 0) {
                  do {
                    lVar22 = lVar15 * 0x20;
                    lVar15 = lVar15 + 1;
                    free(*(void **)((long)pvVar10 + lVar22 + 0x10));
                    pvVar10 = (void *)*__ptr_00;
                  } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                }
                goto LAB_001483dc;
              }
              __ptr_00[2] = (long)pvVar10;
              *(uint *)((long)__ptr_00 + 0x1c) = uVar19;
            }
            lVar22 = (ulong)uVar25 * 0xc;
            uVar2 = uVar25 + 1;
            *(uint *)(__ptr_00 + 3) = uVar2;
            *(undefined4 *)((long)pvVar10 + lVar22) = uVar3;
            *(uint *)((long)pvVar10 + lVar22 + 4) = uVar21;
            *(undefined4 *)((long)pvVar10 + lVar22 + 8) = 1;
            if (uVar19 <= uVar2) {
              pvVar10 = realloc(pvVar10,(ulong)(uVar19 << 1) * 0xc);
              if (pvVar10 == (void *)0x0) {
                pvVar10 = (void *)*__ptr_00;
                if (pvVar10 == (void *)0x0) goto LAB_001483e0;
                lVar15 = 0;
                if (uVar6 != 0) {
                  do {
                    lVar22 = lVar15 * 0x20;
                    lVar15 = lVar15 + 1;
                    free(*(void **)((long)pvVar10 + lVar22 + 0x10));
                    pvVar10 = (void *)*__ptr_00;
                  } while ((uint)lVar15 < *(uint *)(__ptr_00 + 1));
                }
                goto LAB_001483dc;
              }
              __ptr_00[2] = (long)pvVar10;
              *(uint *)((long)__ptr_00 + 0x1c) = uVar19 << 1;
            }
            lVar22 = (ulong)uVar2 * 0xc;
            uVar6 = *(uint *)(__ptr_00 + 1);
            *(uint *)(__ptr_00 + 3) = uVar25 + 2;
            *(undefined4 *)((long)pvVar10 + lVar22) = uVar3;
            *(uint *)((long)pvVar10 + lVar22 + 4) = uVar18;
            *(undefined4 *)((long)pvVar10 + lVar22 + 8) = 2;
            goto LAB_00147e18;
          }
          goto LAB_00147ff4;
        }
        free(pvVar10);
LAB_00147fd0:
        free(pvVar11);
        free(__ptr_00);
      }
LAB_00147fdc:
      free(__ptr);
    }
LAB_00147fe8:
    __ptr_00 = (long *)0x0;
  }
LAB_00147ff4:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return __ptr_00;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_00147e18:
  lVar15 = lVar15 + 1;
  bVar5 = uVar6 <= uVar30;
  uVar30 = uVar30 + 1;
  if (bVar5) goto LAB_00147ff4;
  goto LAB_00147e2c;
}

