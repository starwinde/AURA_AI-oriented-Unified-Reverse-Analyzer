
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ir_reg_coalesce_part_0(long *param_1)

{
  long lVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 *__ptr;
  void *__ptr_00;
  undefined8 *puVar7;
  long *plVar8;
  void *pvVar9;
  void *__ptr_01;
  void *__ptr_02;
  void *__ptr_03;
  void *__ptr_04;
  ulong uVar10;
  char *pcVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  ulong uVar15;
  uint *puVar16;
  uint uVar17;
  int *piVar18;
  uint *puVar19;
  undefined8 *puVar20;
  uint uVar21;
  uint *puVar22;
  uint uVar23;
  uint *puVar24;
  int *piVar25;
  int *piVar26;
  uint *puVar27;
  uint *puVar28;
  undefined8 *puVar29;
  ulong __nmemb;
  int iVar30;
  int iVar31;
  long lVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  undefined8 uVar35;
  char local_88 [32];
  long local_68;
  
  uVar13 = *(uint *)(param_1 + 2);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar3 = 0;
  if (uVar13 == 0) goto LAB_00159098;
  uVar12 = *(uint *)(param_1 + 1);
  lVar32 = *param_1;
  iVar3 = count_active_vars_isra_0(lVar32,uVar12,uVar13);
  __ptr = malloc((ulong)uVar13 << 2);
  g_parent = __ptr;
  __ptr_00 = calloc((ulong)uVar13,4);
  g_rank = __ptr_00;
  if (uVar13 - 1 < 3) {
    uVar4 = 0;
LAB_00159168:
    uVar17 = uVar4 + 1;
    *(uint *)((long)__ptr + (ulong)uVar4 * 4) = uVar4;
    if (uVar17 < uVar13) {
      uVar4 = uVar4 + 2;
      *(uint *)((long)__ptr + (ulong)uVar17 * 4) = uVar17;
      if (uVar4 < uVar13) {
        *(uint *)((long)__ptr + (ulong)uVar4 * 4) = uVar4;
      }
    }
  }
  else {
    puVar7 = __ptr;
    uVar33 = _DAT_0020b140;
    uVar34 = _UNK_0020b148;
    do {
      puVar20 = puVar7 + 2;
      puVar7[1] = uVar34;
      *puVar7 = uVar33;
      puVar7 = puVar20;
      uVar33 = CONCAT44((int)((ulong)uVar33 >> 0x20) + 4,(int)uVar33 + 4);
      uVar34 = CONCAT44((int)((ulong)uVar34 >> 0x20) + 4,(int)uVar34 + 4);
    } while (puVar20 != __ptr + (ulong)(uVar13 >> 2) * 2);
    uVar4 = uVar13 & 0xfffffffc;
    if ((uVar13 & 3) != 0) goto LAB_00159168;
  }
  if (uVar12 != 0) {
    puVar19 = (uint *)(lVar32 + 0x10);
    puVar24 = puVar19 + (ulong)uVar12 * 0x14;
    puVar22 = puVar19;
    do {
      uVar12 = *puVar22;
      if (uVar12 != 0) {
        piVar14 = *(int **)(puVar22 + -2);
        uVar4 = 0;
        do {
          while ((*piVar14 != 0 || (piVar14[0x12] == 0))) {
LAB_001591bc:
            uVar4 = uVar4 + 1;
            piVar14 = piVar14 + 0x22;
            if (uVar12 <= uVar4) goto LAB_001592f0;
          }
          uVar21 = piVar14[2];
          uVar17 = piVar14[6];
          if (uVar21 == 0xffffffff || uVar17 == 0xffffffff) goto LAB_001591bc;
          uVar5 = uVar21;
          if (uVar21 < uVar17) {
            uVar5 = uVar17;
          }
          if (uVar13 <= uVar5 || uVar21 == uVar17) goto LAB_001591bc;
          uVar5 = *(uint *)((long)__ptr + (ulong)uVar17 * 4);
          puVar28 = (uint *)((long)__ptr + (ulong)uVar17 * 4);
          puVar16 = puVar28;
          uVar12 = uVar17;
          if (uVar17 != uVar5) {
            do {
              uVar12 = *(uint *)((long)__ptr + (ulong)uVar5 * 4);
              *puVar16 = uVar12;
              uVar5 = *(uint *)((long)__ptr + (ulong)uVar12 * 4);
              puVar16 = (uint *)((long)__ptr + (ulong)uVar12 * 4);
            } while (uVar5 != uVar12);
          }
          uVar23 = *(uint *)((long)__ptr + (ulong)uVar21 * 4);
          puVar16 = (uint *)((long)__ptr + (ulong)uVar21 * 4);
          puVar27 = puVar16;
          uVar5 = uVar21;
          if (uVar21 != uVar23) {
            do {
              uVar5 = *(uint *)((long)__ptr + (ulong)uVar23 * 4);
              *puVar27 = uVar5;
              uVar23 = *(uint *)((long)__ptr + (ulong)uVar5 * 4);
              puVar27 = (uint *)((long)__ptr + (ulong)uVar5 * 4);
            } while (uVar23 != uVar5);
          }
          if (uVar12 == uVar5) {
LAB_001592dc:
            uVar12 = *puVar22;
          }
          else {
            uVar12 = *puVar28;
            if (uVar17 != uVar12) {
              do {
                uVar17 = *(uint *)((long)__ptr + (ulong)uVar12 * 4);
                *puVar28 = uVar17;
                puVar28 = (uint *)((long)__ptr + (ulong)uVar17 * 4);
                uVar12 = *(uint *)((long)__ptr + (ulong)uVar17 * 4);
              } while (uVar12 != uVar17);
            }
            uVar12 = *puVar16;
            if (uVar21 != uVar12) {
              do {
                uVar21 = *(uint *)((long)__ptr + (ulong)uVar12 * 4);
                *puVar16 = uVar21;
                puVar16 = (uint *)((long)__ptr + (ulong)uVar21 * 4);
                uVar12 = *(uint *)((long)__ptr + (ulong)uVar21 * 4);
              } while (uVar12 != uVar21);
            }
            if (uVar17 == uVar21) goto LAB_001592dc;
            uVar12 = uVar21;
            if (uVar17 < uVar21) {
              uVar12 = uVar17;
            }
            if (uVar17 < uVar21) {
              uVar17 = uVar21;
            }
            iVar6 = *(int *)((long)__ptr_00 + (ulong)uVar12 * 4);
            iVar2 = *(int *)((long)__ptr_00 + (ulong)uVar17 * 4);
            *(uint *)((long)__ptr + (ulong)uVar17 * 4) = uVar12;
            if (iVar6 != iVar2) goto LAB_001592dc;
            *(int *)((long)__ptr_00 + (ulong)uVar12 * 4) = iVar6 + 1;
            uVar12 = *puVar22;
          }
          uVar4 = uVar4 + 1;
          piVar14 = piVar14 + 0x22;
        } while (uVar4 < uVar12);
      }
LAB_001592f0:
      puVar22 = puVar22 + 0x14;
      puVar28 = puVar19;
    } while (puVar22 != puVar24);
    do {
      if (*puVar28 != 0) {
        uVar12 = 0;
        puVar22 = (uint *)(*(long *)(puVar28 + -2) + 0x18);
        do {
          uVar4 = puVar22[-4];
          if (uVar4 < uVar13) {
            uVar17 = *(uint *)((long)__ptr + (ulong)uVar4 * 4);
            lVar1 = (ulong)uVar4 * 4;
            if (uVar17 != uVar4) {
              do {
                uVar4 = *(uint *)((long)__ptr + (ulong)uVar17 * 4);
                *(uint *)((long)__ptr + lVar1) = uVar4;
                lVar1 = (ulong)uVar4 << 2;
                uVar17 = *(uint *)((long)__ptr + (ulong)uVar4 * 4);
              } while (uVar17 != uVar4);
              if (uVar17 != puVar22[-4]) {
                puVar22[-4] = uVar17;
              }
            }
          }
          uVar17 = puVar22[0xc];
          uVar4 = 0;
          puVar16 = puVar22;
          if (uVar17 != 0) {
            do {
              uVar21 = *puVar16;
              if (uVar21 < uVar13) {
                uVar5 = *(uint *)((long)__ptr + (ulong)uVar21 * 4);
                lVar1 = (ulong)uVar21 * 4;
                if (uVar21 != uVar5) {
                  do {
                    uVar17 = *(uint *)((long)__ptr + (ulong)uVar5 * 4);
                    *(uint *)((long)__ptr + lVar1) = uVar17;
                    lVar1 = (ulong)uVar17 << 2;
                    uVar5 = *(uint *)((long)__ptr + (ulong)uVar17 * 4);
                  } while (uVar5 != uVar17);
                  uVar17 = puVar22[0xc];
                  if (uVar5 != *puVar16) {
                    *puVar16 = uVar5;
                  }
                }
              }
              uVar4 = uVar4 + 1;
              puVar16 = puVar16 + 4;
            } while (uVar4 != 3 && uVar4 < uVar17);
          }
          if (((puVar22[-6] == 0x1b) &&
              (puVar16 = *(uint **)(puVar22 + 0xe), puVar16 != (uint *)0x0)) &&
             (uVar4 = puVar22[0x12], uVar4 != 0)) {
            uVar17 = 0;
            do {
              uVar21 = *puVar16;
              if (uVar21 < uVar13) {
                uVar5 = *(uint *)((long)__ptr + (ulong)uVar21 * 4);
                lVar1 = (ulong)uVar21 * 4;
                if (uVar21 != uVar5) {
                  do {
                    uVar4 = *(uint *)((long)__ptr + (ulong)uVar5 * 4);
                    *(uint *)((long)__ptr + lVar1) = uVar4;
                    lVar1 = (ulong)uVar4 << 2;
                    uVar5 = *(uint *)((long)__ptr + (ulong)uVar4 * 4);
                  } while (uVar5 != uVar4);
                  if (uVar5 != *puVar16) {
                    *puVar16 = uVar5;
                  }
                  uVar4 = puVar22[0x12];
                }
              }
              uVar17 = uVar17 + 1;
              puVar16 = puVar16 + 4;
            } while (uVar17 < uVar4);
          }
          uVar12 = uVar12 + 1;
          puVar22 = puVar22 + 0x22;
        } while (uVar12 < *puVar28);
      }
      puVar28 = puVar28 + 0x14;
    } while (puVar28 != puVar24);
    do {
      while (uVar13 = *puVar19, uVar13 == 0) {
        puVar22 = puVar19 + 0x14;
        *puVar19 = 0;
        puVar19 = puVar22;
        if (puVar22 == puVar24) goto LAB_00159414;
      }
      piVar26 = *(int **)(puVar19 + -2);
      uVar12 = 0;
      uVar4 = 0;
      piVar14 = piVar26;
      do {
        if (((*piVar14 != 0) || (piVar14[0x12] == 0)) || (piVar14[2] != piVar14[6])) {
          if (uVar4 != uVar12) {
            uVar33 = *(undefined8 *)piVar14;
            uVar35 = *(undefined8 *)(piVar14 + 6);
            uVar34 = *(undefined8 *)(piVar14 + 4);
            piVar18 = piVar26 + (ulong)uVar12 * 0x22;
            *(undefined8 *)(piVar18 + 2) = *(undefined8 *)(piVar14 + 2);
            *(undefined8 *)piVar18 = uVar33;
            *(undefined8 *)(piVar18 + 6) = uVar35;
            *(undefined8 *)(piVar18 + 4) = uVar34;
            uVar33 = *(undefined8 *)(piVar14 + 8);
            uVar35 = *(undefined8 *)(piVar14 + 0xe);
            uVar34 = *(undefined8 *)(piVar14 + 0xc);
            *(undefined8 *)(piVar18 + 10) = *(undefined8 *)(piVar14 + 10);
            *(undefined8 *)(piVar18 + 8) = uVar33;
            *(undefined8 *)(piVar18 + 0xe) = uVar35;
            *(undefined8 *)(piVar18 + 0xc) = uVar34;
            uVar33 = *(undefined8 *)(piVar14 + 0x10);
            uVar35 = *(undefined8 *)(piVar14 + 0x16);
            uVar34 = *(undefined8 *)(piVar14 + 0x14);
            *(undefined8 *)(piVar18 + 0x12) = *(undefined8 *)(piVar14 + 0x12);
            *(undefined8 *)(piVar18 + 0x10) = uVar33;
            *(undefined8 *)(piVar18 + 0x16) = uVar35;
            *(undefined8 *)(piVar18 + 0x14) = uVar34;
            uVar33 = *(undefined8 *)(piVar14 + 0x18);
            uVar35 = *(undefined8 *)(piVar14 + 0x1e);
            uVar34 = *(undefined8 *)(piVar14 + 0x1c);
            *(undefined8 *)(piVar18 + 0x1a) = *(undefined8 *)(piVar14 + 0x1a);
            *(undefined8 *)(piVar18 + 0x18) = uVar33;
            *(undefined8 *)(piVar18 + 0x1e) = uVar35;
            *(undefined8 *)(piVar18 + 0x1c) = uVar34;
            *(undefined8 *)(piVar18 + 0x20) = *(undefined8 *)(piVar14 + 0x20);
          }
          uVar12 = uVar12 + 1;
        }
        uVar4 = uVar4 + 1;
        piVar14 = piVar14 + 0x22;
      } while (uVar4 != uVar13);
      puVar22 = puVar19 + 0x14;
      *puVar19 = uVar12;
      puVar19 = puVar22;
    } while (puVar22 != puVar24);
  }
LAB_00159414:
  plVar8 = g_last_var_names;
  if (g_last_var_names != (long *)0x0) {
    lVar32 = 0;
    if ((int)g_last_var_names[1] != 0) {
      do {
        lVar1 = lVar32 * 8;
        lVar32 = lVar32 + 1;
        free(*(void **)(*plVar8 + lVar1));
      } while ((uint)lVar32 < *(uint *)(plVar8 + 1));
    }
    free((void *)*plVar8);
    free(plVar8);
    lVar32 = *param_1;
    g_last_var_names = (long *)0x0;
  }
  uVar13 = *(uint *)(param_1 + 1);
  uVar12 = *(uint *)(param_1 + 2);
  plVar8 = calloc(1,0x10);
  if (plVar8 == (long *)0x0) {
LAB_00159b48:
    plVar8 = (long *)0x0;
  }
  else {
    __nmemb = (ulong)uVar12;
    pvVar9 = calloc(__nmemb,8);
    *plVar8 = (long)pvVar9;
    *(uint *)(plVar8 + 1) = uVar12;
    pvVar9 = calloc(__nmemb,1);
    __ptr_01 = calloc(__nmemb,1);
    __ptr_02 = calloc(__nmemb,1);
    __ptr_03 = calloc(__nmemb,1);
    __ptr_04 = calloc(__nmemb,1);
    if ((pvVar9 == (void *)0x0 || __ptr_01 == (void *)0x0) ||
       ((__ptr_02 == (void *)0x0 || __ptr_03 == (void *)0x0) || __ptr_04 == (void *)0x0)) {
      free(pvVar9);
      free(__ptr_01);
      lVar32 = 0;
      free(__ptr_02);
      free(__ptr_03);
      free(__ptr_04);
      if (uVar12 != 0) {
        do {
          lVar1 = lVar32 * 8;
          lVar32 = lVar32 + 1;
          free(*(void **)(*plVar8 + lVar1));
        } while ((uint)lVar32 < *(uint *)(plVar8 + 1));
      }
      free((void *)*plVar8);
      free(plVar8);
      goto LAB_00159b48;
    }
    if (uVar13 != 0) {
      puVar7 = (undefined8 *)(lVar32 + (ulong)uVar13 * 0x50 + 8);
      puVar20 = (undefined8 *)(lVar32 + 8);
      do {
        if (*(uint *)(puVar20 + 1) != 0) {
          piVar14 = (int *)*puVar20;
          piVar26 = piVar14 + (ulong)*(uint *)(puVar20 + 1) * 0x22;
          do {
            while( true ) {
              uVar13 = piVar14[2];
              uVar15 = (ulong)uVar13;
              if (uVar13 < uVar12) break;
LAB_00159574:
              piVar14 = piVar14 + 0x22;
              if (piVar14 == piVar26) goto LAB_001595c0;
            }
            iVar6 = *piVar14;
            iVar2 = piVar14[3];
            if (iVar6 != 1) {
              if (iVar2 == 5) {
                *(undefined1 *)((long)__ptr_01 + uVar15) = 1;
              }
              else if (iVar2 == 6) {
                *(undefined1 *)((long)__ptr_02 + uVar15) = 1;
              }
              if (iVar6 == 0x19) {
                *(undefined1 *)((long)__ptr_03 + uVar15) = 1;
              }
              else if ((iVar6 - 2U < 2) && (piVar14[0x12] == 2)) {
                uVar10 = 0;
                uVar13 = piVar14[6];
                do {
                  if (uVar13 < uVar12) {
                    puVar29 = (undefined8 *)(lVar32 + 8);
                    do {
                      if (*(uint *)(puVar29 + 1) != 0) {
                        piVar18 = (int *)*puVar29;
                        piVar25 = piVar18 + (ulong)*(uint *)(puVar29 + 1) * 0x22;
                        do {
                          while (((uVar13 != piVar18[2] || (*piVar18 != 1)) ||
                                 ((*(long *)(piVar18 + 4) + 1U & 0xfffffffffffffffd) != 0))) {
LAB_00159834:
                            piVar18 = piVar18 + 0x22;
                            if (piVar18 == piVar25) goto LAB_00159888;
                          }
                          uVar4 = piVar14[((uVar10 ^ 1) + 1) * 4 + 2];
                          *(undefined1 *)((long)__ptr_04 + uVar15) = 1;
                          if (uVar12 <= uVar4) goto LAB_00159834;
                          piVar18 = piVar18 + 0x22;
                          *(undefined1 *)((long)__ptr_04 + (ulong)uVar4) = 1;
                        } while (piVar18 != piVar25);
                      }
LAB_00159888:
                      puVar29 = puVar29 + 10;
                    } while (puVar29 != puVar7);
                  }
                  if (uVar10 != 0) break;
                  uVar10 = 1;
                  uVar13 = piVar14[10];
                } while( true );
              }
              goto LAB_00159574;
            }
            *(undefined1 *)((long)pvVar9 + uVar15) = 1;
            if (iVar2 == 5) {
              *(undefined1 *)((long)__ptr_01 + (ulong)uVar13) = 1;
              goto LAB_00159574;
            }
            if (iVar2 != 6) goto LAB_00159574;
            piVar14 = piVar14 + 0x22;
            *(undefined1 *)((long)__ptr_02 + (ulong)uVar13) = 1;
          } while (piVar14 != piVar26);
        }
LAB_001595c0:
        puVar20 = puVar20 + 10;
      } while (puVar20 != puVar7);
    }
    if (uVar12 != 0) {
      uVar15 = 0;
      iVar6 = 0;
      iVar2 = 0;
      iVar30 = 0;
      do {
        uVar13 = *(uint *)((long)__ptr + uVar15 * 4);
        uVar12 = (uint)uVar15;
        uVar10 = uVar15;
        iVar31 = iVar30;
        if (uVar13 == uVar12) {
LAB_001598e4:
          if ((*(char *)((long)pvVar9 + uVar15) == '\0') ||
             (*(char *)((long)__ptr_01 + uVar15) != '\0')) {
            uVar13 = *(uint *)(plVar8 + 1);
            if (uVar12 < uVar13) {
              lVar32 = *plVar8;
              if (*(long *)(lVar32 + uVar15 * 8) == 0) {
                if (*(char *)((long)__ptr_04 + uVar15) == '\0' || 4 < iVar30) goto LAB_00159920;
                iVar31 = iVar30 + 1;
                pcVar11 = strdup((&loop_names_0)[iVar30]);
                *(char **)(lVar32 + uVar15 * 8) = pcVar11;
              }
            }
            else if (*(char *)((long)__ptr_04 + uVar15) == '\0' || 4 < iVar30) {
LAB_00159920:
              if (*(char *)((long)__ptr_03 + uVar15) == '\0') {
                if (*(char *)((long)__ptr_01 + uVar15) == '\0') {
                  if (*(char *)((long)__ptr_02 + uVar15) != '\0' && uVar12 < uVar13) {
                    free(*(void **)(*plVar8 + uVar15 * 8));
                    lVar32 = *plVar8;
                    pcVar11 = strdup("cond");
                    *(char **)(lVar32 + uVar15 * 8) = pcVar11;
                  }
                }
                else {
                  if (iVar2 == 0) {
                    builtin_strncpy(local_88,"ptr",4);
                  }
                  else {
                    __snprintf_chk(local_88,0x10,2,0x10,"ptr_%d",iVar2);
                    uVar13 = *(uint *)(plVar8 + 1);
                  }
                  if (uVar12 < uVar13) {
                    free(*(void **)(*plVar8 + uVar15 * 8));
                    lVar32 = *plVar8;
                    pcVar11 = strdup(local_88);
                    *(char **)(lVar32 + uVar15 * 8) = pcVar11;
                  }
                  iVar2 = iVar2 + 1;
                  __ptr = g_parent;
                }
              }
              else {
                if (iVar6 == 0) {
                  local_88[0] = s_result_001f94a8[0];
                  local_88[1] = s_result_001f94a8[1];
                  local_88[2] = s_result_001f94a8[2];
                  local_88[3] = s_result_001f94a8[3];
                  local_88[4] = s_result_001f94a8[4];
                  local_88[5] = s_result_001f94a8[5];
                  local_88[6] = s_result_001f94a8[6];
                }
                else {
                  __snprintf_chk(local_88,0x20,2,0x20,"result_%d",iVar6);
                  uVar13 = *(uint *)(plVar8 + 1);
                }
                if (uVar12 < uVar13) {
                  free(*(void **)(*plVar8 + uVar15 * 8));
                  lVar32 = *plVar8;
                  pcVar11 = strdup(local_88);
                  *(char **)(lVar32 + uVar15 * 8) = pcVar11;
                }
                iVar6 = iVar6 + 1;
                __ptr = g_parent;
              }
            }
            else {
              iVar31 = iVar30 + 1;
            }
          }
        }
        else {
          do {
            uVar4 = *(uint *)((long)__ptr + (ulong)uVar13 * 4);
            *(uint *)((long)__ptr + uVar10 * 4) = uVar4;
            uVar10 = (ulong)uVar4;
            uVar13 = *(uint *)((long)__ptr + (ulong)uVar4 * 4);
          } while (uVar13 != uVar4);
          if (uVar13 == uVar12) goto LAB_001598e4;
        }
        uVar15 = uVar15 + 1;
        __ptr_00 = g_rank;
        iVar30 = iVar31;
      } while (uVar15 != __nmemb);
    }
    free(pvVar9);
    free(__ptr_01);
    free(__ptr_02);
    free(__ptr_03);
    free(__ptr_04);
  }
  g_last_var_names = plVar8;
  iVar6 = count_active_vars_isra_0(*param_1,(int)param_1[1],(int)param_1[2]);
  free(__ptr);
  free(__ptr_00);
  g_parent = (undefined8 *)0x0;
  iVar3 = iVar3 - iVar6;
  g_rank = (void *)0x0;
LAB_00159098:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar3,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

