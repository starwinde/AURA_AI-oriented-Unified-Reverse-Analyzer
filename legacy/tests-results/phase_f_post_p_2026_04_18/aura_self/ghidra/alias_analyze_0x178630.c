
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * alias_analyze(long *param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  undefined8 *__ptr;
  undefined8 *puVar8;
  void *__ptr_00;
  void *__ptr_01;
  void *__ptr_02;
  undefined8 *puVar9;
  undefined8 *puVar10;
  uint *puVar11;
  int *piVar12;
  long lVar13;
  int *piVar14;
  uint uVar15;
  uint *puVar16;
  uint *puVar17;
  uint *puVar18;
  uint uVar19;
  ulong uVar20;
  long lVar21;
  uint uVar22;
  uint *puVar23;
  long lVar24;
  uint *puVar25;
  long lVar26;
  uint *puVar27;
  uint uVar28;
  uint uVar29;
  long lVar30;
  int iVar31;
  uint *puVar32;
  ulong uVar33;
  uint uVar34;
  long lVar35;
  undefined8 uVar36;
  undefined8 uVar37;
  undefined8 *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (uVar34 = *(uint *)(param_1 + 1), uVar34 != 0)) {
    uVar2 = *(uint *)(param_1 + 2);
    if ((uVar2 != 0) && (__ptr = calloc(1,0x30), local_70 = __ptr, __ptr != (undefined8 *)0x0)) {
      uVar33 = (ulong)uVar2;
      puVar8 = malloc((ulong)uVar2 << 2);
      *__ptr = puVar8;
      __ptr_00 = calloc(uVar33,4);
      __ptr[1] = __ptr_00;
      __ptr_01 = calloc(uVar33,8);
      __ptr[4] = __ptr_01;
      __ptr_02 = calloc(uVar33,1);
      __ptr[5] = __ptr_02;
      if ((__ptr_00 == (void *)0x0 || puVar8 == (undefined8 *)0x0) ||
          (__ptr_02 == (void *)0x0 || __ptr_01 == (void *)0x0)) {
        free(puVar8);
        free(__ptr_00);
        free(__ptr_01);
        free(__ptr_02);
        puVar8 = (undefined8 *)0x0;
        free(__ptr);
        goto LAB_00178a68;
      }
      lVar13 = param_1[3];
      *(uint *)(__ptr + 2) = uVar2;
      __ptr[3] = lVar13;
      if (uVar2 - 1 < 3) {
        uVar7 = 0;
LAB_00178758:
        uVar28 = uVar7 + 1;
        *(uint *)((long)puVar8 + (ulong)uVar7 * 4) = uVar7;
        if (uVar28 < uVar2) {
          uVar7 = uVar7 + 2;
          *(uint *)((long)puVar8 + (ulong)uVar28 * 4) = uVar28;
          if (uVar7 < uVar2) {
            *(uint *)((long)puVar8 + (ulong)uVar7 * 4) = uVar7;
          }
        }
      }
      else {
        puVar9 = puVar8;
        uVar36 = _DAT_0020b140;
        uVar37 = _UNK_0020b148;
        do {
          puVar10 = puVar9 + 2;
          puVar9[1] = uVar37;
          *puVar9 = uVar36;
          puVar9 = puVar10;
          uVar36 = CONCAT44((int)((ulong)uVar36 >> 0x20) + 4,(int)uVar36 + 4);
          uVar37 = CONCAT44((int)((ulong)uVar37 >> 0x20) + 4,(int)uVar37 + 4);
        } while (puVar10 != puVar8 + (ulong)(uVar2 >> 2) * 2);
        uVar7 = uVar2 & 0xfffffffc;
        if ((uVar2 & 3) != 0) goto LAB_00178758;
      }
      puVar11 = calloc(0x100,8);
      if (puVar11 == (uint *)0x0) {
        puVar8 = (undefined8 *)0x0;
        alias_result_destroy(&local_70);
      }
      else {
        uVar33 = 0;
        puVar16 = (uint *)(*param_1 + 0x10);
        puVar18 = puVar16 + (ulong)uVar34 * 0x14;
        do {
          uVar7 = *puVar16;
          if (uVar7 != 0) {
            puVar17 = *(uint **)(puVar16 + -2);
            uVar28 = 0;
            do {
              while( true ) {
                uVar22 = *puVar17;
                uVar19 = puVar17[2];
                uVar20 = (ulong)uVar19;
                uVar29 = (uint)uVar33;
                if (uVar22 != 0x16) break;
                if (((1 < puVar17[0x12]) && (uVar22 = puVar17[6], uVar22 < uVar2)) &&
                   (puVar17[10] < uVar2)) {
                  uVar19 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                  lVar13 = (ulong)uVar22 * 4;
                  if (uVar22 != uVar19) {
                    do {
                      uVar22 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                      *(uint *)((long)puVar8 + lVar13) = uVar22;
                      lVar13 = (ulong)uVar22 << 2;
                      uVar19 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                    } while (uVar19 != uVar22);
                    uVar7 = *puVar16;
                  }
                  if (uVar29 < 0x100) {
                    uVar19 = puVar17[10];
                    puVar11[uVar33 * 2] = uVar22;
                    puVar11[uVar33 * 2 + 1] = uVar19;
                    uVar33 = (ulong)(uVar29 + 1);
                  }
                }
LAB_001787f0:
                uVar28 = uVar28 + 1;
                puVar17 = puVar17 + 0x22;
                if (uVar7 <= uVar28) goto LAB_00178870;
              }
              if (0x16 < uVar22) {
                if (uVar22 == 0x1b) {
                  if ((uVar19 < uVar2) && (uVar22 = puVar17[0x18], uVar22 != 0)) {
                    lVar30 = *(long *)(puVar17 + 0x14);
                    puVar25 = (uint *)((long)puVar8 + uVar20 * 4);
                    lVar13 = 0;
                    if (lVar30 != 0) {
LAB_00178c98:
                      do {
                        while( true ) {
                          uVar7 = *(uint *)(lVar30 + lVar13 * 0x10);
                          if (uVar7 < uVar2) break;
LAB_00178ca8:
                          lVar13 = lVar13 + 1;
                          if (uVar22 <= (uint)lVar13) {
                            uVar7 = *puVar16;
                            goto LAB_0017885c;
                          }
                        }
                        uVar22 = *puVar25;
                        lVar21 = uVar20 * 4;
                        puVar23 = puVar25;
                        uVar29 = uVar19;
                        if (uVar19 != uVar22) {
                          do {
                            uVar29 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                            *puVar23 = uVar29;
                            uVar22 = *(uint *)((long)puVar8 + (ulong)uVar29 * 4);
                            puVar23 = (uint *)((long)puVar8 + (ulong)uVar29 * 4);
                            lVar21 = (ulong)uVar29 * 4;
                          } while (uVar22 != uVar29);
                        }
                        uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        lVar24 = (ulong)uVar7 * 4;
                        puVar27 = (uint *)((long)puVar8 + lVar24);
                        if (uVar7 != uVar22) {
                          do {
                            uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                            *puVar27 = uVar7;
                            lVar24 = (ulong)uVar7 * 4;
                            uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                            puVar27 = (uint *)((long)puVar8 + lVar24);
                          } while (uVar22 != uVar7);
                        }
                        if (uVar29 == uVar7) {
                          uVar22 = puVar17[0x18];
                          goto LAB_00178ca8;
                        }
                        uVar22 = *(uint *)((long)__ptr_00 + lVar21);
                        if (*(uint *)((long)__ptr_00 + lVar24) <= uVar22) {
                          if (uVar22 == *(uint *)((long)__ptr_00 + lVar24)) {
                            *puVar27 = uVar29;
                            *(uint *)((long)__ptr_00 + lVar21) = uVar22 + 1;
                            lVar13 = lVar13 + 1;
                            uVar22 = puVar17[0x18];
                            if (uVar22 <= (uint)lVar13) {
                              uVar7 = *puVar16;
                              goto LAB_0017885c;
                            }
                          }
                          else {
                            *puVar27 = uVar29;
                            lVar13 = lVar13 + 1;
                            uVar22 = puVar17[0x18];
                            if (uVar22 <= (uint)lVar13) {
                              uVar7 = *puVar16;
                              goto LAB_0017885c;
                            }
                          }
                          goto LAB_00178c98;
                        }
                        *puVar23 = uVar7;
                        lVar13 = lVar13 + 1;
                        uVar22 = puVar17[0x18];
                      } while ((uint)lVar13 < uVar22);
                      goto LAB_00178858;
                    }
                    do {
                      lVar13 = lVar13 + 1;
                    } while ((uint)lVar13 < uVar22);
                  }
                }
                else if (((uVar22 == 0x1c) && (uVar19 < uVar2)) &&
                        (uVar22 = puVar17[0x12], 1 < uVar22)) {
                  uVar7 = puVar17[10];
                  if (uVar7 < uVar2) {
                    uVar22 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                    lVar13 = uVar20 * 4;
                    puVar25 = (uint *)((long)puVar8 + lVar13);
                    uVar29 = uVar19;
                    if (uVar19 != uVar22) {
                      do {
                        uVar29 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                        *puVar25 = uVar29;
                        lVar13 = (ulong)uVar29 * 4;
                        uVar22 = *(uint *)((long)puVar8 + (ulong)uVar29 * 4);
                        puVar25 = (uint *)((long)puVar8 + lVar13);
                      } while (uVar22 != uVar29);
                    }
                    uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                    lVar30 = (ulong)uVar7 * 4;
                    puVar23 = (uint *)((long)puVar8 + lVar30);
                    if (uVar7 != uVar22) {
                      do {
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                        *puVar23 = uVar7;
                        lVar30 = (ulong)uVar7 * 4;
                        uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        puVar23 = (uint *)((long)puVar8 + lVar30);
                      } while (uVar22 != uVar7);
                    }
                    if (uVar29 == uVar7) {
LAB_001792d0:
                      uVar22 = puVar17[0x12];
                    }
                    else {
                      uVar22 = *(uint *)((long)__ptr_00 + lVar13);
                      if (uVar22 < *(uint *)((long)__ptr_00 + lVar30)) {
                        *puVar25 = uVar7;
                        uVar22 = puVar17[0x12];
                      }
                      else {
                        if (uVar22 <= *(uint *)((long)__ptr_00 + lVar30)) {
                          *puVar23 = uVar29;
                          *(uint *)((long)__ptr_00 + lVar13) = uVar22 + 1;
                          goto LAB_001792d0;
                        }
                        *puVar23 = uVar29;
                        uVar22 = puVar17[0x12];
                      }
                    }
                  }
                  if (2 < uVar22) {
                    uVar22 = puVar17[0xe];
                    if (uVar22 < uVar2) {
                      uVar7 = *(uint *)((long)puVar8 + uVar20 * 4);
                      lVar13 = uVar20 * 4;
                      puVar25 = (uint *)((long)puVar8 + lVar13);
                      if (uVar19 != uVar7) {
                        do {
                          uVar19 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                          *puVar25 = uVar19;
                          lVar13 = (ulong)uVar19 * 4;
                          uVar7 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                          puVar25 = (uint *)((long)puVar8 + lVar13);
                        } while (uVar7 != uVar19);
                      }
                      uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                      lVar30 = (ulong)uVar22 * 4;
                      puVar23 = (uint *)((long)puVar8 + lVar30);
                      if (uVar22 != uVar7) {
                        do {
                          uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                          *puVar23 = uVar22;
                          lVar30 = (ulong)uVar22 * 4;
                          uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                          puVar23 = (uint *)((long)puVar8 + lVar30);
                        } while (uVar7 != uVar22);
                      }
                      goto LAB_00178afc;
                    }
                  }
LAB_00178858:
                  uVar7 = *puVar16;
                  goto LAB_0017885c;
                }
                goto LAB_001787f0;
              }
              if (uVar22 < 4) {
                if (uVar22 < 2) {
                  if (((uVar22 == 0) && (uVar19 < uVar2)) && (puVar17[0x12] != 0)) {
                    uVar22 = puVar17[6];
                    if (uVar22 < uVar2) {
                      uVar7 = *(uint *)((long)puVar8 + uVar20 * 4);
                      lVar13 = uVar20 * 4;
                      puVar25 = (uint *)((long)puVar8 + lVar13);
                      if (uVar19 != uVar7) {
                        do {
                          uVar19 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                          *puVar25 = uVar19;
                          lVar13 = (ulong)uVar19 * 4;
                          uVar7 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                          puVar25 = (uint *)((long)puVar8 + lVar13);
                        } while (uVar7 != uVar19);
                      }
                      uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                      lVar30 = (ulong)uVar22 * 4;
                      puVar23 = (uint *)((long)puVar8 + lVar30);
                      if (uVar22 != uVar7) {
                        do {
                          uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                          *puVar23 = uVar22;
                          lVar30 = (ulong)uVar22 * 4;
                          uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                          puVar23 = (uint *)((long)puVar8 + lVar30);
                        } while (uVar7 != uVar22);
                      }
                      goto LAB_00178afc;
                    }
                  }
                }
                else if ((uVar19 < uVar2) && (1 < puVar17[0x12])) {
                  uVar22 = puVar17[6];
                  if ((uVar22 < uVar2) && (puVar17[7] - 4 < 2)) {
                    uVar7 = *(uint *)((long)puVar8 + uVar20 * 4);
                    lVar13 = uVar20 * 4;
                    puVar25 = (uint *)((long)puVar8 + lVar13);
                    if (uVar19 != uVar7) {
                      do {
                        uVar19 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        *puVar25 = uVar19;
                        lVar13 = (ulong)uVar19 * 4;
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                        puVar25 = (uint *)((long)puVar8 + lVar13);
                      } while (uVar7 != uVar19);
                    }
                    uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                    lVar30 = (ulong)uVar22 * 4;
                    puVar23 = (uint *)((long)puVar8 + lVar30);
                    if (uVar22 != uVar7) {
                      do {
                        uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        *puVar23 = uVar22;
                        lVar30 = (ulong)uVar22 * 4;
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                        puVar23 = (uint *)((long)puVar8 + lVar30);
                      } while (uVar7 != uVar22);
                    }
                  }
                  else {
                    uVar22 = puVar17[10];
                    if ((uVar2 <= uVar22) || (1 < puVar17[0xb] - 4)) goto LAB_001787f0;
                    uVar7 = *(uint *)((long)puVar8 + uVar20 * 4);
                    lVar13 = uVar20 * 4;
                    puVar25 = (uint *)((long)puVar8 + lVar13);
                    if (uVar19 != uVar7) {
                      do {
                        uVar19 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        *puVar25 = uVar19;
                        lVar13 = (ulong)uVar19 * 4;
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar19 * 4);
                        puVar25 = (uint *)((long)puVar8 + lVar13);
                      } while (uVar7 != uVar19);
                    }
                    uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                    lVar30 = (ulong)uVar22 * 4;
                    puVar23 = (uint *)((long)puVar8 + lVar30);
                    if (uVar7 != uVar22) {
                      do {
                        uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        *puVar23 = uVar22;
                        lVar30 = (ulong)uVar22 * 4;
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                        puVar23 = (uint *)((long)puVar8 + lVar30);
                      } while (uVar7 != uVar22);
                    }
                  }
LAB_00178afc:
                  if (uVar19 == uVar22) goto LAB_00178858;
                  uVar7 = *(uint *)((long)__ptr_00 + lVar13);
                  if (uVar7 < *(uint *)((long)__ptr_00 + lVar30)) {
                    *puVar25 = uVar22;
                    uVar7 = *puVar16;
                  }
                  else {
                    if (uVar7 == *(uint *)((long)__ptr_00 + lVar30)) {
                      *puVar23 = uVar19;
                      *(uint *)((long)__ptr_00 + lVar13) = uVar7 + 1;
                      uVar7 = *puVar16;
                      goto LAB_0017885c;
                    }
                    *puVar23 = uVar19;
                    uVar7 = *puVar16;
                  }
                }
                goto LAB_001787f0;
              }
              if (((uVar22 != 0x15) || (uVar2 <= uVar19)) ||
                 ((puVar17[0x12] == 0 || (uVar22 = puVar17[6], uVar2 <= uVar22))))
              goto LAB_001787f0;
              uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
              lVar13 = (ulong)uVar22 * 4;
              if (uVar22 != uVar7) {
                do {
                  uVar22 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                  *(uint *)((long)puVar8 + lVar13) = uVar22;
                  lVar13 = (ulong)uVar22 << 2;
                  uVar7 = *(uint *)((long)puVar8 + (ulong)uVar22 * 4);
                } while (uVar7 != uVar22);
              }
              if (uVar29 == 0) goto LAB_00178858;
              puVar23 = (uint *)((long)puVar8 + uVar20 * 4);
              puVar25 = puVar11;
              do {
                uVar7 = *puVar25;
                lVar13 = (ulong)uVar7 * 4;
                uVar29 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                if (uVar7 != uVar29) {
                  do {
                    uVar7 = *(uint *)((long)puVar8 + (ulong)uVar29 * 4);
                    *(uint *)((long)puVar8 + lVar13) = uVar7;
                    lVar13 = (ulong)uVar7 << 2;
                    uVar29 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                  } while (uVar29 != uVar7);
                }
                if (uVar22 == uVar7) {
                  uVar7 = puVar25[1];
                  if (uVar7 < uVar2) {
                    uVar29 = *puVar23;
                    lVar13 = uVar20 * 4;
                    puVar27 = puVar23;
                    uVar15 = uVar19;
                    if (uVar19 != uVar29) {
                      do {
                        uVar15 = *(uint *)((long)puVar8 + (ulong)uVar29 * 4);
                        *puVar27 = uVar15;
                        uVar29 = *(uint *)((long)puVar8 + (ulong)uVar15 * 4);
                        puVar27 = (uint *)((long)puVar8 + (ulong)uVar15 * 4);
                        lVar13 = (ulong)uVar15 * 4;
                      } while (uVar29 != uVar15);
                    }
                    uVar29 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                    lVar30 = (ulong)uVar7 * 4;
                    puVar32 = (uint *)((long)puVar8 + lVar30);
                    if (uVar7 != uVar29) {
                      do {
                        uVar7 = *(uint *)((long)puVar8 + (ulong)uVar29 * 4);
                        *puVar32 = uVar7;
                        lVar30 = (ulong)uVar7 * 4;
                        uVar29 = *(uint *)((long)puVar8 + (ulong)uVar7 * 4);
                        puVar32 = (uint *)((long)puVar8 + lVar30);
                      } while (uVar29 != uVar7);
                    }
                    if (uVar15 != uVar7) {
                      uVar29 = *(uint *)((long)__ptr_00 + lVar13);
                      if (uVar29 < *(uint *)((long)__ptr_00 + lVar30)) {
                        *puVar27 = uVar7;
                      }
                      else if (uVar29 == *(uint *)((long)__ptr_00 + lVar30)) {
                        *puVar32 = uVar15;
                        *(uint *)((long)__ptr_00 + lVar13) = uVar29 + 1;
                      }
                      else {
                        *puVar32 = uVar15;
                      }
                    }
                  }
                }
                puVar25 = puVar25 + 2;
              } while (puVar25 != puVar11 + uVar33 * 2);
              uVar7 = *puVar16;
LAB_0017885c:
              uVar28 = uVar28 + 1;
              puVar17 = puVar17 + 0x22;
            } while (uVar28 < uVar7);
          }
LAB_00178870:
          puVar16 = puVar16 + 0x14;
        } while (puVar16 != puVar18);
        free(puVar11);
        iVar31 = 8;
        do {
          lVar13 = 0;
          bVar4 = false;
          uVar7 = 0;
          do {
            lVar30 = *param_1 + lVar13;
            uVar28 = *(uint *)(lVar30 + 0x10);
            if (uVar28 != 0) {
              lVar21 = 0;
              uVar34 = 0;
              do {
                while( true ) {
                  uVar22 = *(uint *)(__ptr + 2);
                  puVar11 = (uint *)(*(long *)(lVar30 + 8) + lVar21);
                  uVar19 = puVar11[2];
                  uVar33 = (ulong)uVar19;
                  if (uVar19 < uVar22) break;
LAB_001788e8:
                  uVar34 = uVar34 + 1;
                  lVar21 = lVar21 + 0x88;
                  if (uVar28 <= uVar34) goto LAB_001789c0;
                }
                lVar24 = __ptr[5];
                uVar20 = (ulong)uVar19;
                if (*(char *)(lVar24 + uVar33) != '\0') goto LAB_001788e8;
                uVar29 = *puVar11;
                if (uVar29 < 4) {
                  if (uVar29 < 2) {
                    if (uVar29 == 0) {
                      if (((puVar11[0x12] != 0) && (uVar19 = puVar11[6], uVar19 < uVar22)) &&
                         (*(char *)(lVar24 + (ulong)uVar19) != '\0')) {
                        bVar4 = true;
                        *(undefined8 *)(__ptr[4] + uVar20 * 8) =
                             *(undefined8 *)(__ptr[4] + (ulong)uVar19 * 8);
                        *(undefined1 *)(lVar24 + uVar33) = 1;
                        uVar28 = *(uint *)(lVar30 + 0x10);
                      }
                    }
                    else if (puVar11[3] == 5) {
                      bVar4 = true;
                      *(undefined8 *)(__ptr[4] + uVar20 * 8) = 0;
                      *(undefined1 *)(lVar24 + uVar33) = 1;
                      uVar28 = *(uint *)(lVar30 + 0x10);
                    }
                  }
                  else if (1 < puVar11[0x12]) {
                    uVar15 = puVar11[6];
                    uVar3 = puVar11[10];
                    bVar1 = false;
                    if (uVar15 < uVar22) {
                      bVar1 = *(char *)(lVar24 + (ulong)uVar15) != '\0';
                      if (uVar3 < uVar22) {
                        if (*(char *)(lVar24 + (ulong)uVar3) == '\0') {
                          uVar22 = *(uint *)(param_1 + 1);
                          bVar6 = 0;
                        }
                        else {
LAB_00178f9c:
                          uVar22 = *(uint *)(param_1 + 1);
                          bVar6 = 1;
                        }
                        if (uVar22 != 0) {
LAB_00178e28:
                          lVar26 = *param_1;
                          puVar8 = (undefined8 *)(lVar26 + 8);
                          puVar9 = puVar8 + (ulong)uVar22 * 10;
                          do {
                            if (*(uint *)(puVar8 + 1) != 0) {
                              piVar14 = (int *)*puVar8;
                              piVar12 = piVar14 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
                              do {
                                if (uVar15 == piVar14[2]) {
                                  if (*piVar14 != 1) goto LAB_00178f30;
                                  lVar35 = *(long *)(piVar14 + 4);
                                  bVar5 = 1;
                                  goto joined_r0x00178f3c;
                                }
                                piVar14 = piVar14 + 0x22;
                              } while (piVar14 != piVar12);
                            }
                            puVar8 = puVar8 + 10;
                          } while (puVar8 != puVar9);
LAB_00178f30:
                          lVar35 = 0;
                          bVar5 = 0;
joined_r0x00178f3c:
                          if (uVar3 != 0xffffffff) goto LAB_00178e78;
                          goto LAB_00178f40;
                        }
                      }
                      else {
LAB_00178fb8:
                        uVar22 = *(uint *)(param_1 + 1);
                        if (uVar22 != 0) {
                          bVar6 = 0;
                          goto LAB_00178e28;
                        }
                      }
                    }
                    else {
                      if (uVar3 < uVar22) {
                        if (*(char *)(lVar24 + (ulong)uVar3) == '\0') {
                          if (uVar15 != 0xffffffff) {
                            uVar22 = *(uint *)(param_1 + 1);
                            bVar6 = 0;
                            if (uVar22 == 0) goto LAB_001788e8;
                            goto LAB_00178e28;
                          }
                          goto LAB_001790d4;
                        }
                        if (uVar15 != 0xffffffff) goto LAB_00178f9c;
                        bVar6 = 1;
                      }
                      else {
                        if (uVar15 != 0xffffffff) goto LAB_00178fb8;
                        if (uVar3 == 0xffffffff) goto LAB_001788e8;
LAB_001790d4:
                        bVar6 = 0;
                      }
                      uVar22 = *(uint *)(param_1 + 1);
                      if (uVar22 != 0) {
                        lVar26 = *param_1;
                        bVar5 = 0;
                        lVar35 = 0;
LAB_00178e78:
                        puVar8 = (undefined8 *)(lVar26 + 8);
                        puVar9 = puVar8 + (ulong)uVar22 * 10;
                        do {
                          if (*(uint *)(puVar8 + 1) != 0) {
                            piVar14 = (int *)*puVar8;
                            piVar12 = piVar14 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
                            do {
                              if (uVar3 == piVar14[2]) {
                                if ((*piVar14 != 1) || (!bVar1)) goto LAB_00178f40;
                                lVar35 = -*(long *)(piVar14 + 4);
                                if (uVar29 == 2) {
                                  lVar35 = *(long *)(piVar14 + 4);
                                }
                                *(long *)(__ptr[4] + uVar20 * 8) =
                                     *(long *)(__ptr[4] + (ulong)uVar15 * 8) + lVar35;
                                *(undefined1 *)(lVar24 + (ulong)uVar19) = 1;
                                uVar28 = *(uint *)(lVar30 + 0x10);
                                bVar4 = true;
                                goto LAB_001788e8;
                              }
                              piVar14 = piVar14 + 0x22;
                            } while (piVar14 != piVar12);
                          }
                          puVar8 = puVar8 + 10;
                        } while (puVar8 != puVar9);
LAB_00178f40:
                        if ((uVar29 == 2) && ((bool)(bVar6 & bVar5))) {
                          *(long *)(__ptr[4] + uVar20 * 8) =
                               *(long *)(__ptr[4] + (ulong)uVar3 * 8) + lVar35;
                          *(undefined1 *)(lVar24 + uVar33) = 1;
                          uVar28 = *(uint *)(lVar30 + 0x10);
                          bVar4 = true;
                        }
                      }
                    }
                  }
                  goto LAB_001788e8;
                }
                if (((uVar29 != 0x1b) || (uVar29 = puVar11[0x18], uVar29 == 0)) ||
                   (*(long *)(puVar11 + 0x14) == 0)) goto LAB_001788e8;
                uVar33 = 0;
                lVar35 = 0;
                do {
                  while( true ) {
                    uVar15 = *(uint *)(*(long *)(puVar11 + 0x14) + uVar33 * 0x10);
                    if ((uVar22 <= uVar15) || (*(char *)(lVar24 + (ulong)uVar15) == '\0'))
                    goto LAB_001788e8;
                    lVar26 = __ptr[4];
                    if (uVar33 != 0) break;
                    uVar33 = 1;
                    lVar35 = *(long *)(lVar26 + (ulong)uVar15 * 8);
                    if ((ulong)uVar29 == 1) goto LAB_001789a0;
                  }
                  if (*(long *)(lVar26 + (ulong)uVar15 * 8) != lVar35) goto LAB_001788e8;
                  uVar33 = uVar33 + 1;
                } while (uVar33 != uVar29);
LAB_001789a0:
                *(long *)(lVar26 + uVar20 * 8) = lVar35;
                uVar34 = uVar34 + 1;
                *(undefined1 *)(lVar24 + (ulong)uVar19) = 1;
                lVar21 = lVar21 + 0x88;
                bVar4 = true;
                uVar28 = *(uint *)(lVar30 + 0x10);
              } while (uVar34 < uVar28);
LAB_001789c0:
              uVar34 = *(uint *)(param_1 + 1);
            }
            uVar7 = uVar7 + 1;
            lVar13 = lVar13 + 0x50;
          } while (uVar7 < uVar34);
        } while (((bVar4) && (iVar31 = iVar31 + -1, iVar31 != 0)) && (uVar34 != 0));
        puVar16 = (uint *)*__ptr;
        uVar34 = 0;
        iVar31 = 0;
        puVar11 = puVar16;
        do {
          uVar7 = *puVar11;
          puVar18 = puVar11;
          if (uVar7 == uVar34) {
LAB_00179080:
            iVar31 = iVar31 + 1;
          }
          else {
            do {
              uVar28 = puVar16[uVar7];
              *puVar18 = uVar28;
              puVar18 = puVar16 + uVar28;
              uVar7 = puVar16[uVar28];
            } while (uVar7 != uVar28);
            if (uVar7 == uVar34) goto LAB_00179080;
          }
          uVar34 = uVar34 + 1;
          puVar11 = puVar11 + 1;
        } while (uVar2 != uVar34);
        lVar13 = param_1[3];
        *(int *)((long)__ptr + 0x14) = iVar31;
        aura_log(1,0,0,&DAT_001fbe40,lVar13,(ulong)uVar2);
        puVar8 = __ptr;
      }
      goto LAB_00178a68;
    }
  }
  puVar8 = (undefined8 *)0x0;
LAB_00178a68:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return puVar8;
}

