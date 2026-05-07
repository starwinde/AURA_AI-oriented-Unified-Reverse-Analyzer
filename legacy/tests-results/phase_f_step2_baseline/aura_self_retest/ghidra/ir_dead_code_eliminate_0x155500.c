
uint ir_dead_code_eliminate(long *param_1)

{
  long *plVar1;
  undefined8 *puVar2;
  uint uVar3;
  char *__ptr;
  undefined4 *__ptr_00;
  char *pcVar4;
  void *__ptr_01;
  long *plVar6;
  void *pvVar7;
  uint uVar8;
  ulong uVar9;
  undefined8 *puVar10;
  uint *puVar11;
  int *piVar12;
  uint uVar13;
  uint *puVar14;
  uint uVar15;
  int *piVar16;
  int *piVar17;
  int *piVar18;
  long lVar19;
  ulong uVar20;
  int *piVar21;
  long lVar22;
  long *plVar23;
  ulong uVar25;
  long lVar26;
  long *plVar27;
  long lVar28;
  uint uVar29;
  long lVar30;
  uint uVar31;
  undefined8 uVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  uint local_84;
  int local_70 [2];
  long local_68;
  char *pcVar5;
  long *plVar24;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0) {
    local_84 = 0;
    goto LAB_00155540;
  }
  uVar29 = *(uint *)(param_1 + 1);
  uVar25 = (ulong)uVar29;
  local_84 = 0;
  if (uVar29 == 0) goto LAB_00155540;
  if ((uVar29 == 1) || (__ptr = calloc(uVar25,1), __ptr == (char *)0x0)) {
LAB_00155a44:
    local_84 = 0;
  }
  else {
    __ptr_00 = malloc(uVar25 << 2);
    if (__ptr_00 == (undefined4 *)0x0) {
LAB_00155a3c:
      free(__ptr);
      goto LAB_00155a44;
    }
    piVar18 = (int *)*param_1;
    uVar20 = 1;
    lVar22 = 0;
    *__ptr = '\x01';
    *__ptr_00 = 0;
    do {
      uVar13 = __ptr_00[lVar22];
      if (piVar18[(ulong)uVar13 * 0x12 + 0xc] != 0) {
        piVar16 = *(int **)(piVar18 + (ulong)uVar13 * 0x12 + 10);
        piVar17 = piVar16 + (uint)piVar18[(ulong)uVar13 * 0x12 + 0xc];
        do {
          uVar9 = 0;
          piVar21 = piVar18;
          do {
            if ((*piVar16 == *piVar21) && (__ptr[uVar9] == '\0')) {
              __ptr_00[uVar20] = (int)uVar9;
              uVar20 = (ulong)((int)uVar20 + 1);
              __ptr[uVar9] = '\x01';
              break;
            }
            uVar9 = uVar9 + 1;
            piVar21 = piVar21 + 0x12;
          } while (uVar25 != uVar9);
          piVar16 = piVar16 + 1;
        } while (piVar17 != piVar16);
      }
      if (piVar18[(ulong)uVar13 * 0x12 + 4] != 0) {
        piVar17 = *(int **)(piVar18 + (ulong)uVar13 * 0x12 + 2);
        piVar16 = piVar17 + (ulong)(uint)piVar18[(ulong)uVar13 * 0x12 + 4] * 0x22;
        do {
          while (iVar35 = *piVar17, 1 < iVar35 - 0x17U) {
            piVar17 = piVar17 + 0x22;
            if (piVar16 == piVar17) goto LAB_001556d4;
          }
          piVar21 = local_70;
          iVar36 = 0;
          local_70[0] = piVar17[0x19];
          local_70[1] = piVar17[0x1a];
          do {
            uVar9 = 0;
            piVar12 = piVar18;
            do {
              if ((*piVar12 == *piVar21) && (__ptr[uVar9] == '\0')) {
                __ptr_00[uVar20] = (int)uVar9;
                uVar20 = (ulong)((int)uVar20 + 1);
                __ptr[uVar9] = '\x01';
                break;
              }
              uVar9 = uVar9 + 1;
              piVar12 = piVar12 + 0x12;
            } while (uVar25 != uVar9);
            iVar36 = iVar36 + 1;
            piVar21 = piVar21 + 1;
          } while (iVar36 != (iVar35 == 0x17) + 1);
          piVar17 = piVar17 + 0x22;
        } while (piVar16 != piVar17);
      }
LAB_001556d4:
      lVar22 = lVar22 + 1;
    } while ((uint)lVar22 < (uint)uVar20);
    free(__ptr_00);
    if (uVar29 - 1 < 0xf) {
      uVar8 = 0;
      uVar13 = 1;
      uVar31 = (uint)(*__ptr == '\0');
LAB_00155760:
      if (__ptr[uVar13] == '\0') {
        uVar31 = uVar31 + 1;
      }
      if (uVar8 + 2 < uVar29) {
        if (__ptr[uVar8 + 2] == '\0') {
          uVar31 = uVar31 + 1;
        }
        if (uVar8 + 3 < uVar29) {
          if (__ptr[uVar8 + 3] == '\0') {
            uVar31 = uVar31 + 1;
          }
          if (uVar8 + 4 < uVar29) {
            if (__ptr[uVar8 + 4] == '\0') {
              uVar31 = uVar31 + 1;
            }
            if (uVar8 + 5 < uVar29) {
              if (__ptr[uVar8 + 5] == '\0') {
                uVar31 = uVar31 + 1;
              }
              if (uVar8 + 6 < uVar29) {
                if (__ptr[uVar8 + 6] == '\0') {
                  uVar31 = uVar31 + 1;
                }
                if (uVar8 + 7 < uVar29) {
                  if (__ptr[uVar8 + 7] == '\0') {
                    uVar31 = uVar31 + 1;
                  }
                  if (uVar8 + 8 < uVar29) {
                    if (__ptr[uVar8 + 8] == '\0') {
                      uVar31 = uVar31 + 1;
                    }
                    if (uVar8 + 9 < uVar29) {
                      if (__ptr[uVar8 + 9] == '\0') {
                        uVar31 = uVar31 + 1;
                      }
                      if (uVar8 + 10 < uVar29) {
                        if (__ptr[uVar8 + 10] == '\0') {
                          uVar31 = uVar31 + 1;
                        }
                        if (uVar8 + 0xb < uVar29) {
                          if (__ptr[uVar8 + 0xb] == '\0') {
                            uVar31 = uVar31 + 1;
                          }
                          if (uVar8 + 0xc < uVar29) {
                            if (__ptr[uVar8 + 0xc] == '\0') {
                              uVar31 = uVar31 + 1;
                            }
                            if (uVar8 + 0xd < uVar29) {
                              if (__ptr[uVar8 + 0xd] == '\0') {
                                uVar31 = uVar31 + 1;
                              }
                              if ((uVar8 + 0xe < uVar29) && (__ptr[uVar8 + 0xe] == '\0')) {
                                uVar31 = uVar31 + 1;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      iVar35 = 0;
      iVar36 = 0;
      iVar37 = 0;
      iVar38 = 0;
      pcVar5 = __ptr;
      do {
        pcVar4 = pcVar5 + 0x10;
        uVar33 = *(undefined8 *)(pcVar5 + 8);
        uVar32 = *(undefined8 *)pcVar5;
        iVar35 = iVar35 + ((((uint)(-((char)uVar32 == '\0') & 1) -
                            (int)(short)-((char)((ulong)uVar32 >> 0x20) == '\0')) -
                           (int)(short)-((char)uVar33 == '\0')) -
                          (int)(short)-((char)((ulong)uVar33 >> 0x20) == '\0'));
        iVar36 = iVar36 + ((((uint)(-((char)((ulong)uVar32 >> 8) == '\0') & 1) -
                            (int)(short)-((char)((ulong)uVar32 >> 0x28) == '\0')) -
                           (int)(short)-((char)((ulong)uVar33 >> 8) == '\0')) -
                          (int)(short)-((char)((ulong)uVar33 >> 0x28) == '\0'));
        iVar37 = iVar37 + ((((uint)(-((char)((ulong)uVar32 >> 0x10) == '\0') & 1) -
                            (int)(short)-((char)((ulong)uVar32 >> 0x30) == '\0')) -
                           (int)(short)-((char)((ulong)uVar33 >> 0x10) == '\0')) -
                          (int)(short)-((char)((ulong)uVar33 >> 0x30) == '\0'));
        iVar38 = iVar38 + ((((uint)(-((char)((ulong)uVar32 >> 0x18) == '\0') & 1) -
                            (int)(short)-((char)((ulong)uVar32 >> 0x38) == '\0')) -
                           (int)(short)-((char)((ulong)uVar33 >> 0x18) == '\0')) -
                          (int)(short)-((char)((ulong)uVar33 >> 0x38) == '\0'));
        pcVar5 = pcVar4;
      } while (__ptr + (ulong)(uVar29 >> 4) * 0x10 != pcVar4);
      uVar31 = iVar35 + iVar36 + iVar37 + iVar38;
      uVar8 = uVar29 & 0xfffffff0;
      if ((uVar29 & 0xf) != 0) {
        uVar13 = uVar8 + 1;
        if (__ptr[uVar8] == '\0') {
          uVar31 = uVar31 + 1;
        }
        if (uVar13 < uVar29) goto LAB_00155760;
      }
    }
    if (uVar31 == 0) goto LAB_00155a3c;
    lVar22 = 0;
    pcVar5 = __ptr;
    do {
      while (*pcVar5 != '\0') {
        pcVar5 = pcVar5 + 1;
        lVar22 = lVar22 + 0x48;
        if (__ptr + uVar25 == pcVar5) goto LAB_00155954;
      }
      lVar26 = 0;
      uVar29 = 0;
      lVar19 = *param_1 + lVar22;
      if (*(int *)(lVar19 + 0x10) != 0) {
        do {
          uVar29 = uVar29 + 1;
          free(*(void **)(*(long *)(lVar19 + 8) + lVar26 + 0x50));
          lVar28 = *(long *)(lVar19 + 8) + lVar26;
          lVar26 = lVar26 + 0x88;
          free(*(void **)(lVar28 + 0x58));
        } while (uVar29 < *(uint *)(lVar19 + 0x10));
      }
      pcVar5 = pcVar5 + 1;
      lVar22 = lVar22 + 0x48;
      free(*(void **)(lVar19 + 8));
      free(*(void **)(lVar19 + 0x18));
      free(*(void **)(lVar19 + 0x28));
      free(*(void **)(lVar19 + 0x38));
    } while (__ptr + uVar25 != pcVar5);
LAB_00155954:
    lVar22 = 0;
    uVar20 = 0;
    uVar29 = 0;
    do {
      if (__ptr[uVar20] != '\0') {
        if (uVar29 != (uint)uVar20) {
          puVar2 = (undefined8 *)(*param_1 + lVar22);
          puVar10 = (undefined8 *)(*param_1 + (ulong)uVar29 * 0x48);
          uVar32 = *puVar2;
          uVar34 = puVar2[3];
          uVar33 = puVar2[2];
          puVar10[1] = puVar2[1];
          *puVar10 = uVar32;
          puVar10[3] = uVar34;
          puVar10[2] = uVar33;
          uVar32 = puVar2[4];
          uVar34 = puVar2[7];
          uVar33 = puVar2[6];
          puVar10[5] = puVar2[5];
          puVar10[4] = uVar32;
          puVar10[7] = uVar34;
          puVar10[6] = uVar33;
          puVar10[8] = puVar2[8];
        }
        uVar29 = uVar29 + 1;
      }
      uVar20 = uVar20 + 1;
      lVar22 = lVar22 + 0x48;
    } while (uVar25 != uVar20);
    *(uint *)(param_1 + 1) = uVar29;
    if (uVar29 != 0) {
      piVar17 = (int *)*param_1;
      uVar13 = 0;
      piVar18 = piVar17 + 2;
LAB_001559d8:
      uVar8 = piVar18[6];
      if (uVar8 != 0) {
        lVar26 = *(long *)(piVar18 + 4);
        lVar22 = 0;
        uVar25 = 0;
        do {
          iVar35 = *(int *)(lVar26 + lVar22 * 4);
          if (uVar29 != 0) {
            piVar16 = piVar17;
            do {
              if (iVar35 == *piVar16) {
                *(int *)(lVar26 + uVar25 * 4) = iVar35;
                uVar25 = (ulong)((int)uVar25 + 1);
                uVar8 = piVar18[6];
                break;
              }
              piVar16 = piVar16 + 0x12;
            } while (piVar17 + (ulong)uVar29 * 0x12 != piVar16);
          }
          lVar22 = lVar22 + 1;
          if (uVar8 <= (uint)lVar22) goto LAB_00155e48;
          uVar29 = *(uint *)(param_1 + 1);
        } while( true );
      }
      goto LAB_001559c8;
    }
LAB_00155f3c:
    free(__ptr);
    local_84 = 1;
  }
  uVar29 = *(uint *)(param_1 + 2);
  if (0xfffffffd < uVar29 - 1) goto LAB_00155540;
  uVar25 = (ulong)uVar29;
  __ptr_01 = calloc(uVar25,8);
  if (__ptr_01 == (void *)0x0) goto LAB_00155540;
  uVar13 = *(uint *)(param_1 + 1);
  if (uVar13 == 0) {
    plVar6 = calloc(0,8);
    if (plVar6 != (long *)0x0) {
      pvVar7 = malloc(uVar25 << 2);
      if (pvVar7 != (void *)0x0) {
        free(pvVar7);
      }
      goto LAB_00155d34;
    }
  }
  else {
    lVar22 = *param_1;
    uVar8 = 0;
    plVar23 = (long *)(lVar22 + 8);
    plVar6 = plVar23;
    do {
      lVar26 = plVar6[1];
      if ((int)lVar26 != 0) {
        iVar35 = 0;
        puVar14 = (uint *)(*plVar6 + 8);
        do {
          if (*puVar14 < uVar29) {
            lVar19 = (ulong)*puVar14 * 8;
            *(uint *)((long)__ptr_01 + lVar19) = uVar8;
            *(int *)((long)__ptr_01 + lVar19 + 4) = iVar35;
          }
          iVar35 = iVar35 + 1;
          puVar14 = puVar14 + 0x22;
        } while (iVar35 != (int)lVar26);
      }
      uVar8 = uVar8 + 1;
      plVar6 = plVar6 + 9;
    } while (uVar8 != uVar13);
    plVar6 = calloc((ulong)uVar13,8);
    if (plVar6 != (long *)0x0) {
      puVar14 = (uint *)(lVar22 + 0x10);
      plVar24 = plVar6 + uVar13;
      plVar27 = plVar6;
      do {
        while (*puVar14 == 0) {
          plVar27 = plVar27 + 1;
          puVar14 = puVar14 + 0x12;
          if (plVar24 == plVar27) goto LAB_00155b4c;
        }
        pvVar7 = calloc((ulong)*puVar14,1);
        plVar1 = plVar27 + 1;
        *plVar27 = (long)pvVar7;
        puVar14 = puVar14 + 0x12;
        plVar27 = plVar1;
      } while (plVar24 != plVar1);
LAB_00155b4c:
      pvVar7 = malloc(uVar25 << 2);
      if (pvVar7 == (void *)0x0) {
        for (lVar22 = 0; (uint)lVar22 < uVar13; lVar22 = lVar22 + 1) {
          free((void *)plVar6[lVar22]);
        }
      }
      else {
        uVar25 = 0;
        plVar27 = plVar6;
        do {
          uVar8 = *(uint *)(plVar23 + 1);
          if (uVar8 != 0) {
            piVar18 = (int *)*plVar23;
            uVar20 = 0;
            do {
              if (*piVar18 - 0x16U < 5) {
                iVar35 = piVar18[0x12];
                *(undefined1 *)(*plVar27 + uVar20) = 1;
                if (iVar35 != 0) {
                  if ((uint)piVar18[6] < uVar29) {
                    *(int *)((long)pvVar7 + uVar25 * 4) = piVar18[6];
                    uVar25 = (ulong)((int)uVar25 + 1);
                  }
                  if (iVar35 != 1) {
                    if ((uint)piVar18[10] < uVar29) {
                      *(int *)((long)pvVar7 + uVar25 * 4) = piVar18[10];
                      uVar25 = (ulong)((int)uVar25 + 1);
                    }
                    if ((iVar35 != 2) && ((uint)piVar18[0xe] < uVar29)) {
                      *(int *)((long)pvVar7 + uVar25 * 4) = piVar18[0xe];
                      uVar25 = (ulong)((int)uVar25 + 1);
                    }
                  }
                }
              }
              uVar20 = uVar20 + 1;
              piVar18 = piVar18 + 0x22;
            } while (uVar8 != uVar20);
          }
          plVar27 = plVar27 + 1;
          plVar23 = plVar23 + 9;
        } while (plVar24 != plVar27);
        iVar35 = (int)uVar25;
        while (iVar35 != 0) {
          uVar15 = (uint)uVar25;
          uVar8 = uVar15 - 1;
          uVar31 = *(uint *)((long)pvVar7 + (ulong)(uVar15 - 1) * 4);
          if (uVar31 < uVar29) {
            lVar26 = (ulong)uVar31 * 8;
            uVar31 = *(uint *)((long)__ptr_01 + lVar26);
            if (uVar13 <= uVar31) goto LAB_00155c60;
            lVar19 = lVar22 + (ulong)uVar31 * 0x48;
            uVar3 = *(uint *)((long)__ptr_01 + lVar26 + 4);
            if ((*(uint *)(lVar19 + 0x10) <= uVar3) ||
               (*(char *)(plVar6[uVar31] + (ulong)uVar3) != '\0')) goto LAB_00155c60;
            lVar19 = *(long *)(lVar19 + 8);
            *(undefined1 *)(plVar6[uVar31] + (ulong)uVar3) = 1;
            lVar26 = lVar19 + (ulong)uVar3 * 0x88;
            iVar35 = *(int *)(lVar26 + 0x48);
            if (iVar35 == 0) {
LAB_00155dd0:
              uVar25 = (ulong)uVar8;
            }
            else {
              if (*(uint *)(lVar26 + 0x18) < uVar29) {
                *(uint *)((long)pvVar7 + (ulong)(uVar15 - 1) * 4) = *(uint *)(lVar26 + 0x18);
                uVar8 = uVar15;
              }
              uVar25 = (ulong)uVar8;
              if (iVar35 != 1) {
                if (*(uint *)(lVar26 + 0x28) < uVar29) {
                  *(uint *)((long)pvVar7 + (ulong)uVar8 * 4) = *(uint *)(lVar26 + 0x28);
                  uVar8 = uVar8 + 1;
                }
                uVar25 = (ulong)uVar8;
                if (iVar35 != 2) {
                  if (*(uint *)(lVar26 + 0x38) < uVar29) {
                    *(uint *)((long)pvVar7 + (ulong)uVar8 * 4) = *(uint *)(lVar26 + 0x38);
                    uVar8 = uVar8 + 1;
                  }
                  goto LAB_00155dd0;
                }
              }
            }
            if ((*(int *)(lVar19 + (ulong)uVar3 * 0x88) == 0x1b) && (*(uint *)(lVar26 + 0x60) != 0))
            {
              puVar11 = *(uint **)(lVar26 + 0x50);
              puVar14 = puVar11 + (ulong)*(uint *)(lVar26 + 0x60) * 4;
              do {
                if (*puVar11 < uVar29) {
                  *(uint *)((long)pvVar7 + uVar25 * 4) = *puVar11;
                  uVar25 = (ulong)((int)uVar25 + 1);
                }
                puVar11 = puVar11 + 4;
              } while (puVar14 != puVar11);
            }
          }
          else {
LAB_00155c60:
            uVar25 = (ulong)uVar8;
          }
          iVar35 = (int)uVar25;
        }
        free(pvVar7);
        lVar22 = 0;
        uVar29 = 0;
        do {
          lVar26 = *param_1 + lVar22 * 0x48;
          uVar8 = *(uint *)(lVar26 + 0x10);
          if (uVar8 == 0) {
            uVar31 = 0;
          }
          else {
            lVar30 = plVar6[lVar22];
            lVar28 = 0;
            lVar19 = 0;
            uVar31 = 0;
            do {
              if (*(char *)(lVar30 + lVar19) == '\0') {
                free(*(void **)(*(long *)(lVar26 + 8) + lVar28 + 0x50));
                free(*(void **)(*(long *)(lVar26 + 8) + lVar28 + 0x58));
                uVar8 = *(uint *)(lVar26 + 0x10);
                uVar29 = 1;
              }
              else {
                if (uVar31 != (uint)lVar19) {
                  puVar2 = (undefined8 *)(*(long *)(lVar26 + 8) + lVar28);
                  puVar10 = (undefined8 *)(*(long *)(lVar26 + 8) + (ulong)uVar31 * 0x88);
                  uVar32 = *puVar2;
                  uVar34 = puVar2[3];
                  uVar33 = puVar2[2];
                  puVar10[1] = puVar2[1];
                  *puVar10 = uVar32;
                  puVar10[3] = uVar34;
                  puVar10[2] = uVar33;
                  uVar32 = puVar2[4];
                  uVar34 = puVar2[7];
                  uVar33 = puVar2[6];
                  puVar10[5] = puVar2[5];
                  puVar10[4] = uVar32;
                  puVar10[7] = uVar34;
                  puVar10[6] = uVar33;
                  uVar32 = puVar2[8];
                  uVar34 = puVar2[0xb];
                  uVar33 = puVar2[10];
                  puVar10[9] = puVar2[9];
                  puVar10[8] = uVar32;
                  puVar10[0xb] = uVar34;
                  puVar10[10] = uVar33;
                  uVar32 = puVar2[0xc];
                  uVar34 = puVar2[0xf];
                  uVar33 = puVar2[0xe];
                  puVar10[0xd] = puVar2[0xd];
                  puVar10[0xc] = uVar32;
                  puVar10[0xf] = uVar34;
                  puVar10[0xe] = uVar33;
                  puVar10[0x10] = puVar2[0x10];
                }
                uVar31 = uVar31 + 1;
              }
              lVar19 = lVar19 + 1;
              lVar28 = lVar28 + 0x88;
            } while ((uint)lVar19 < uVar8);
            uVar13 = *(uint *)(param_1 + 1);
          }
          lVar22 = lVar22 + 1;
          *(uint *)(lVar26 + 0x10) = uVar31;
        } while ((uint)lVar22 < uVar13);
        local_84 = local_84 | uVar29;
        if (uVar13 != 0) {
          plVar23 = plVar6;
          do {
            plVar24 = plVar23 + 1;
            free((void *)*plVar23);
            plVar23 = plVar24;
          } while (plVar6 + uVar13 != plVar24);
        }
      }
LAB_00155d34:
      free(plVar6);
    }
  }
  free(__ptr_01);
LAB_00155540:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_84;
LAB_00155e48:
  uVar8 = piVar18[2];
  piVar18[6] = (int)uVar25;
  uVar29 = *(uint *)(param_1 + 1);
  if (uVar8 == 0) {
LAB_001559c8:
    uVar13 = uVar13 + 1;
    piVar18 = piVar18 + 0x12;
    if (uVar29 <= uVar13) goto LAB_00155f3c;
    goto LAB_001559d8;
  }
  piVar16 = *(int **)piVar18;
  uVar31 = 0;
  do {
    while ((*piVar16 != 0x1b || (uVar15 = piVar16[0x18], uVar15 == 0))) {
      uVar31 = uVar31 + 1;
      piVar16 = piVar16 + 0x22;
      if (uVar8 <= uVar31) goto LAB_00155f28;
    }
    piVar21 = *(int **)(piVar16 + 0x16);
    lVar22 = 0;
    uVar25 = 0;
    iVar36 = 0;
    uVar8 = 0;
    iVar35 = *piVar21;
    while (uVar29 != 0) {
      piVar12 = piVar17;
      do {
        if (iVar35 == *piVar12) {
          puVar10 = (undefined8 *)(*(long *)(piVar16 + 0x14) + lVar22 * 0x10);
          puVar2 = (undefined8 *)(*(long *)(piVar16 + 0x14) + uVar25 * 0x10);
          uVar32 = puVar10[1];
          *puVar2 = *puVar10;
          puVar2[1] = uVar32;
          piVar21[uVar25] = piVar21[lVar22];
          uVar25 = (ulong)((int)uVar25 + 1);
          uVar15 = piVar16[0x18];
          break;
        }
        piVar12 = piVar12 + 0x12;
      } while (piVar17 + (ulong)uVar29 * 0x12 != piVar12);
      iVar36 = (int)uVar25;
      uVar8 = uVar8 + 1;
      if (uVar15 <= uVar8) break;
      lVar22 = lVar22 + 1;
      iVar35 = piVar21[lVar22];
      uVar29 = *(uint *)(param_1 + 1);
    }
    piVar16[0x18] = iVar36;
    uVar31 = uVar31 + 1;
    piVar16 = piVar16 + 0x22;
    uVar8 = piVar18[2];
    uVar29 = *(uint *)(param_1 + 1);
  } while (uVar31 < uVar8);
LAB_00155f28:
  uVar13 = uVar13 + 1;
  piVar18 = piVar18 + 0x12;
  if (uVar29 <= uVar13) goto LAB_00155f3c;
  goto LAB_001559d8;
}

