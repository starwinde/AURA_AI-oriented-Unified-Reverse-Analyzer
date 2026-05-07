
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * alias_analyze(long *param_1)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  undefined8 *__ptr;
  uint *__ptr_00;
  void *__ptr_01;
  uint *puVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint *puVar10;
  uint uVar11;
  long lVar12;
  int iVar13;
  uint uVar14;
  ulong uVar15;
  uint *puVar16;
  uint *puVar17;
  uint *puVar18;
  long lVar19;
  uint *puVar20;
  uint *puVar21;
  uint uVar22;
  ulong uVar23;
  undefined8 *puVar24;
  long lVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 *local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (uVar7 = *(uint *)(param_1 + 1), uVar7 != 0)) {
    uVar1 = *(uint *)(param_1 + 2);
    if ((uVar1 != 0) && (__ptr = calloc(1,0x20), local_60 = __ptr, __ptr != (undefined8 *)0x0)) {
      __ptr_00 = malloc((ulong)uVar1 << 2);
      *__ptr = __ptr_00;
      __ptr_01 = calloc((ulong)uVar1,4);
      __ptr[1] = __ptr_01;
      if (__ptr_01 == (void *)0x0 || __ptr_00 == (uint *)0x0) {
        free(__ptr_00);
        free(__ptr_01);
        puVar24 = (undefined8 *)0x0;
        free(__ptr);
        goto LAB_001786bc;
      }
      lVar25 = param_1[3];
      *(uint *)(__ptr + 2) = uVar1;
      __ptr[3] = lVar25;
      if (uVar1 - 1 < 3) {
        uVar4 = 0;
LAB_00178518:
        uVar11 = uVar4 + 1;
        __ptr_00[uVar4] = uVar4;
        if (uVar11 < uVar1) {
          uVar4 = uVar4 + 2;
          __ptr_00[uVar11] = uVar11;
          if (uVar4 < uVar1) {
            __ptr_00[uVar4] = uVar4;
          }
        }
      }
      else {
        puVar5 = __ptr_00;
        uVar26 = _DAT_0020b500;
        uVar27 = _UNK_0020b508;
        do {
          puVar9 = puVar5 + 4;
          *(undefined8 *)(puVar5 + 2) = uVar27;
          *(undefined8 *)puVar5 = uVar26;
          puVar5 = puVar9;
          uVar26 = CONCAT44((int)((ulong)uVar26 >> 0x20) + 4,(int)uVar26 + 4);
          uVar27 = CONCAT44((int)((ulong)uVar27 >> 0x20) + 4,(int)uVar27 + 4);
        } while (puVar9 != __ptr_00 + (ulong)(uVar1 >> 2) * 4);
        uVar4 = uVar1 & 0xfffffffc;
        if ((uVar1 & 3) != 0) goto LAB_00178518;
      }
      puVar5 = calloc(0x100,8);
      if (puVar5 == (uint *)0x0) {
        puVar24 = (undefined8 *)0x0;
        alias_result_destroy(&local_60);
      }
      else {
        uVar23 = 0;
        puVar9 = (uint *)(*param_1 + 0x10);
        puVar21 = puVar9 + (ulong)uVar7 * 0x14;
        do {
          uVar7 = *puVar9;
          if (uVar7 != 0) {
            puVar10 = *(uint **)(puVar9 + -2);
            uVar4 = 0;
            do {
              while( true ) {
                uVar11 = *puVar10;
                uVar14 = puVar10[2];
                uVar15 = (ulong)uVar14;
                uVar22 = (uint)uVar23;
                if (uVar11 == 0x16) {
                  if (((1 < puVar10[0x12]) && (uVar11 = puVar10[6], uVar11 < uVar1)) &&
                     (puVar10[10] < uVar1)) {
                    uVar14 = __ptr_00[uVar11];
                    lVar19 = (ulong)uVar11 * 4;
                    if (uVar11 != uVar14) {
                      do {
                        uVar11 = __ptr_00[uVar14];
                        *(uint *)((long)__ptr_00 + lVar19) = uVar11;
                        lVar19 = (ulong)uVar11 << 2;
                        uVar14 = __ptr_00[uVar11];
                      } while (uVar14 != uVar11);
                      uVar7 = *puVar9;
                    }
                    if (uVar22 < 0x100) {
                      uVar14 = puVar10[10];
                      puVar5[uVar23 * 2] = uVar11;
                      puVar5[uVar23 * 2 + 1] = uVar14;
                      uVar23 = (ulong)(uVar22 + 1);
                    }
                  }
                  goto LAB_001785b0;
                }
                if (0x16 < uVar11) break;
                if (3 < uVar11) {
                  if (((uVar11 != 0x15) || (uVar1 <= uVar14)) ||
                     ((puVar10[0x12] == 0 || (uVar11 = puVar10[6], uVar1 <= uVar11))))
                  goto LAB_001785b0;
                  uVar7 = __ptr_00[uVar11];
                  lVar19 = (ulong)uVar11 * 4;
                  if (uVar11 != uVar7) {
                    do {
                      uVar11 = __ptr_00[uVar7];
                      *(uint *)((long)__ptr_00 + lVar19) = uVar11;
                      lVar19 = (ulong)uVar11 << 2;
                      uVar7 = __ptr_00[uVar11];
                    } while (uVar7 != uVar11);
                  }
                  if (uVar22 != 0) {
                    puVar17 = __ptr_00 + uVar15;
                    puVar16 = puVar5;
                    do {
                      uVar7 = *puVar16;
                      lVar19 = (ulong)uVar7 * 4;
                      uVar22 = __ptr_00[uVar7];
                      if (uVar22 != uVar7) {
                        do {
                          uVar7 = __ptr_00[uVar22];
                          *(uint *)((long)__ptr_00 + lVar19) = uVar7;
                          lVar19 = (ulong)uVar7 << 2;
                          uVar22 = __ptr_00[uVar7];
                        } while (uVar22 != uVar7);
                      }
                      if (uVar11 == uVar7) {
                        uVar7 = puVar16[1];
                        uVar6 = (ulong)uVar7;
                        if (uVar7 < uVar1) {
                          uVar22 = *puVar17;
                          puVar18 = puVar17;
                          uVar8 = uVar14;
                          uVar3 = uVar15;
                          if (uVar14 != uVar22) {
                            do {
                              uVar8 = __ptr_00[uVar22];
                              *puVar18 = uVar8;
                              uVar22 = __ptr_00[uVar8];
                              puVar18 = __ptr_00 + uVar8;
                              uVar3 = (ulong)uVar8;
                            } while (uVar22 != uVar8);
                          }
                          uVar22 = __ptr_00[uVar6];
                          puVar20 = __ptr_00 + uVar6;
                          if (uVar7 != uVar22) {
                            do {
                              uVar7 = __ptr_00[uVar22];
                              uVar6 = (ulong)uVar7;
                              *puVar20 = uVar7;
                              uVar22 = __ptr_00[uVar7];
                              puVar20 = __ptr_00 + uVar6;
                            } while (uVar22 != uVar7);
                          }
                          if (uVar8 != uVar7) {
                            uVar22 = *(uint *)((long)__ptr_01 + uVar6 * 4);
                            uVar2 = *(uint *)((long)__ptr_01 + uVar3 * 4);
                            if (uVar2 < uVar22) {
                              *puVar18 = uVar7;
                            }
                            else if (uVar2 == uVar22) {
                              *puVar20 = uVar8;
                              *(uint *)((long)__ptr_01 + uVar3 * 4) = uVar2 + 1;
                            }
                            else {
                              *puVar20 = uVar8;
                            }
                          }
                        }
                      }
                      puVar16 = puVar16 + 2;
                    } while (puVar16 != puVar5 + uVar23 * 2);
                    uVar7 = *puVar9;
                    goto LAB_0017861c;
                  }
                  goto LAB_00178618;
                }
                if (uVar11 < 2) {
                  if (((uVar11 == 0) && (uVar14 < uVar1)) && (puVar10[0x12] != 0)) {
                    uVar11 = puVar10[6];
                    uVar6 = (ulong)uVar11;
                    if (uVar11 < uVar1) {
                      uVar7 = __ptr_00[uVar15];
                      puVar16 = __ptr_00 + uVar15;
                      if (uVar14 != uVar7) {
                        do {
                          uVar14 = __ptr_00[uVar7];
                          uVar15 = (ulong)uVar14;
                          *puVar16 = uVar14;
                          uVar7 = __ptr_00[uVar14];
                          puVar16 = __ptr_00 + uVar15;
                        } while (uVar7 != uVar14);
                      }
                      lVar12 = uVar15 * 4;
                      uVar7 = __ptr_00[uVar6];
                      lVar19 = uVar6 * 4;
                      puVar17 = __ptr_00 + uVar6;
                      if (uVar11 != uVar7) {
                        do {
                          uVar11 = __ptr_00[uVar7];
                          *puVar17 = uVar11;
                          lVar19 = (ulong)uVar11 * 4;
                          uVar7 = __ptr_00[uVar11];
                          puVar17 = __ptr_00 + uVar11;
                        } while (uVar7 != uVar11);
                      }
                      goto LAB_00178754;
                    }
                  }
                }
                else if ((uVar14 < uVar1) && (1 < puVar10[0x12])) {
                  uVar11 = puVar10[6];
                  uVar6 = (ulong)uVar11;
                  if ((uVar11 < uVar1) && (puVar10[7] - 4 < 2)) {
                    uVar7 = __ptr_00[uVar15];
                    puVar16 = __ptr_00 + uVar15;
                    if (uVar14 != uVar7) {
                      do {
                        uVar14 = __ptr_00[uVar7];
                        uVar15 = (ulong)uVar14;
                        *puVar16 = uVar14;
                        uVar7 = __ptr_00[uVar14];
                        puVar16 = __ptr_00 + uVar15;
                      } while (uVar7 != uVar14);
                    }
                    lVar12 = uVar15 * 4;
                    uVar7 = __ptr_00[uVar6];
                    lVar19 = uVar6 * 4;
                    puVar17 = __ptr_00 + uVar6;
                    if (uVar7 != uVar11) {
                      do {
                        uVar11 = __ptr_00[uVar7];
                        *puVar17 = uVar11;
                        lVar19 = (ulong)uVar11 * 4;
                        uVar7 = __ptr_00[uVar11];
                        puVar17 = __ptr_00 + uVar11;
                      } while (uVar7 != uVar11);
                    }
                  }
                  else {
                    uVar11 = puVar10[10];
                    uVar6 = (ulong)uVar11;
                    if ((uVar1 <= uVar11) || (1 < puVar10[0xb] - 4)) goto LAB_001785b0;
                    uVar7 = __ptr_00[uVar15];
                    puVar16 = __ptr_00 + uVar15;
                    if (uVar14 != uVar7) {
                      do {
                        uVar14 = __ptr_00[uVar7];
                        uVar15 = (ulong)uVar14;
                        *puVar16 = uVar14;
                        uVar7 = __ptr_00[uVar14];
                        puVar16 = __ptr_00 + uVar15;
                      } while (uVar7 != uVar14);
                    }
                    lVar12 = uVar15 * 4;
                    uVar7 = __ptr_00[uVar6];
                    lVar19 = uVar6 * 4;
                    puVar17 = __ptr_00 + uVar6;
                    if (uVar7 != uVar11) {
                      do {
                        uVar11 = __ptr_00[uVar7];
                        *puVar17 = uVar11;
                        lVar19 = (ulong)uVar11 * 4;
                        uVar7 = __ptr_00[uVar11];
                        puVar17 = __ptr_00 + uVar11;
                      } while (uVar7 != uVar11);
                    }
                  }
                  if (uVar14 == uVar11) goto LAB_00178618;
                  uVar7 = *(uint *)((long)__ptr_01 + lVar12);
                  if (uVar7 < *(uint *)((long)__ptr_01 + lVar19)) {
                    *puVar16 = uVar11;
                    uVar7 = *puVar9;
                  }
                  else {
                    if (uVar7 == *(uint *)((long)__ptr_01 + lVar19)) {
                      *puVar17 = uVar14;
                      *(uint *)((long)__ptr_01 + lVar12) = uVar7 + 1;
                      uVar7 = *puVar9;
                      goto LAB_0017861c;
                    }
                    *puVar17 = uVar14;
                    uVar7 = *puVar9;
                  }
                }
LAB_001785b0:
                uVar4 = uVar4 + 1;
                puVar10 = puVar10 + 0x22;
                if (uVar7 <= uVar4) goto LAB_00178630;
              }
              if (uVar11 == 0x1b) {
                if ((uVar14 < uVar1) && (uVar11 = puVar10[0x18], uVar11 != 0)) {
                  lVar12 = *(long *)(puVar10 + 0x14);
                  puVar16 = __ptr_00 + uVar15;
                  lVar19 = 0;
                  if (lVar12 != 0) {
LAB_001789c8:
                    do {
                      while( true ) {
                        uVar7 = *(uint *)(lVar12 + lVar19 * 0x10);
                        uVar6 = (ulong)uVar7;
                        if (uVar7 < uVar1) break;
LAB_001789d8:
                        lVar19 = lVar19 + 1;
                        if (uVar11 <= (uint)lVar19) {
                          uVar7 = *puVar9;
                          goto LAB_0017861c;
                        }
                      }
                      uVar11 = *puVar16;
                      puVar17 = puVar16;
                      uVar22 = uVar14;
                      uVar3 = uVar15;
                      if (uVar14 != uVar11) {
                        do {
                          uVar22 = __ptr_00[uVar11];
                          *puVar17 = uVar22;
                          uVar11 = __ptr_00[uVar22];
                          puVar17 = __ptr_00 + uVar22;
                          uVar3 = (ulong)uVar22;
                        } while (uVar11 != uVar22);
                      }
                      uVar11 = __ptr_00[uVar6];
                      puVar18 = __ptr_00 + uVar6;
                      if (uVar7 != uVar11) {
                        do {
                          uVar7 = __ptr_00[uVar11];
                          uVar6 = (ulong)uVar7;
                          *puVar18 = uVar7;
                          uVar11 = __ptr_00[uVar7];
                          puVar18 = __ptr_00 + uVar6;
                        } while (uVar11 != uVar7);
                      }
                      if (uVar22 == uVar7) {
                        uVar11 = puVar10[0x18];
                        goto LAB_001789d8;
                      }
                      uVar11 = *(uint *)((long)__ptr_01 + uVar6 * 4);
                      uVar8 = *(uint *)((long)__ptr_01 + uVar3 * 4);
                      if (uVar8 < uVar11) {
                        *puVar17 = uVar7;
                        lVar19 = lVar19 + 1;
                        uVar11 = puVar10[0x18];
                        if (uVar11 <= (uint)lVar19) goto LAB_00178618;
                        goto LAB_001789c8;
                      }
                      if (uVar8 == uVar11) {
                        *puVar18 = uVar22;
                        *(uint *)((long)__ptr_01 + uVar3 * 4) = uVar8 + 1;
                        lVar19 = lVar19 + 1;
                        uVar11 = puVar10[0x18];
                        if (uVar11 <= (uint)lVar19) {
                          uVar7 = *puVar9;
                          goto LAB_0017861c;
                        }
                        goto LAB_001789c8;
                      }
                      *puVar18 = uVar22;
                      lVar19 = lVar19 + 1;
                      uVar11 = puVar10[0x18];
                    } while ((uint)lVar19 < uVar11);
                    uVar7 = *puVar9;
                    goto LAB_0017861c;
                  }
                  do {
                    lVar19 = lVar19 + 1;
                  } while ((uint)lVar19 < uVar11);
                }
                goto LAB_001785b0;
              }
              if (((uVar11 != 0x1c) || (uVar1 <= uVar14)) || (uVar11 = puVar10[0x12], uVar11 < 2))
              goto LAB_001785b0;
              uVar7 = puVar10[10];
              uVar6 = (ulong)uVar7;
              if (uVar7 < uVar1) {
                uVar11 = __ptr_00[uVar14];
                puVar16 = __ptr_00 + uVar15;
                uVar22 = uVar14;
                uVar3 = uVar15;
                if (uVar14 != uVar11) {
                  do {
                    uVar22 = __ptr_00[uVar11];
                    *puVar16 = uVar22;
                    uVar11 = __ptr_00[uVar22];
                    puVar16 = __ptr_00 + uVar22;
                    uVar3 = (ulong)uVar22;
                  } while (uVar11 != uVar22);
                }
                uVar11 = __ptr_00[uVar6];
                puVar17 = __ptr_00 + uVar6;
                if (uVar7 != uVar11) {
                  do {
                    uVar7 = __ptr_00[uVar11];
                    uVar6 = (ulong)uVar7;
                    *puVar17 = uVar7;
                    uVar11 = __ptr_00[uVar7];
                    puVar17 = __ptr_00 + uVar6;
                  } while (uVar11 != uVar7);
                }
                if (uVar22 == uVar7) {
LAB_00178cb8:
                  uVar11 = puVar10[0x12];
                }
                else {
                  uVar11 = *(uint *)((long)__ptr_01 + uVar6 * 4);
                  uVar8 = *(uint *)((long)__ptr_01 + uVar3 * 4);
                  if (uVar8 < uVar11) {
                    *puVar16 = uVar7;
                    uVar11 = puVar10[0x12];
                  }
                  else {
                    if (uVar8 <= uVar11) {
                      *puVar17 = uVar22;
                      *(uint *)((long)__ptr_01 + uVar3 * 4) = uVar8 + 1;
                      goto LAB_00178cb8;
                    }
                    *puVar17 = uVar22;
                    uVar11 = puVar10[0x12];
                  }
                }
              }
              if (2 < uVar11) {
                uVar11 = puVar10[0xe];
                uVar6 = (ulong)uVar11;
                if (uVar11 < uVar1) {
                  uVar7 = __ptr_00[uVar15];
                  puVar16 = __ptr_00 + uVar15;
                  if (uVar14 != uVar7) {
                    do {
                      uVar14 = __ptr_00[uVar7];
                      uVar15 = (ulong)uVar14;
                      *puVar16 = uVar14;
                      uVar7 = __ptr_00[uVar14];
                      puVar16 = __ptr_00 + uVar15;
                    } while (uVar7 != uVar14);
                  }
                  lVar12 = uVar15 * 4;
                  uVar7 = __ptr_00[uVar6];
                  lVar19 = uVar6 * 4;
                  puVar17 = __ptr_00 + uVar6;
                  if (uVar11 != uVar7) {
                    do {
                      uVar11 = __ptr_00[uVar7];
                      *puVar17 = uVar11;
                      lVar19 = (ulong)uVar11 * 4;
                      uVar7 = __ptr_00[uVar11];
                      puVar17 = __ptr_00 + uVar11;
                    } while (uVar7 != uVar11);
                  }
LAB_00178754:
                  if (uVar14 != uVar11) {
                    uVar7 = *(uint *)((long)__ptr_01 + lVar12);
                    if (uVar7 < *(uint *)((long)__ptr_01 + lVar19)) {
                      *puVar16 = uVar11;
                      uVar7 = *puVar9;
                    }
                    else if (uVar7 == *(uint *)((long)__ptr_01 + lVar19)) {
                      *puVar17 = uVar14;
                      *(uint *)((long)__ptr_01 + lVar12) = uVar7 + 1;
                      uVar7 = *puVar9;
                    }
                    else {
                      *puVar17 = uVar14;
                      uVar7 = *puVar9;
                    }
                    goto LAB_001785b0;
                  }
                }
              }
LAB_00178618:
              uVar7 = *puVar9;
LAB_0017861c:
              uVar4 = uVar4 + 1;
              puVar10 = puVar10 + 0x22;
            } while (uVar4 < uVar7);
          }
LAB_00178630:
          puVar9 = puVar9 + 0x14;
        } while (puVar9 != puVar21);
        free(puVar5);
        uVar7 = 0;
        iVar13 = 0;
        puVar5 = __ptr_00;
        do {
          uVar4 = *puVar5;
          puVar9 = puVar5;
          if (uVar4 == uVar7) {
LAB_00178b10:
            iVar13 = iVar13 + 1;
          }
          else {
            do {
              uVar11 = __ptr_00[uVar4];
              *puVar9 = uVar11;
              puVar9 = __ptr_00 + uVar11;
              uVar4 = __ptr_00[uVar11];
            } while (uVar4 != uVar11);
            if (uVar4 == uVar7) goto LAB_00178b10;
          }
          uVar7 = uVar7 + 1;
          puVar5 = puVar5 + 1;
        } while (uVar1 != uVar7);
        *(int *)((long)__ptr + 0x14) = iVar13;
        aura_log(1,0,0,&DAT_001fc200,lVar25,(ulong)uVar1);
        puVar24 = __ptr;
      }
      goto LAB_001786bc;
    }
  }
  puVar24 = (undefined8 *)0x0;
LAB_001786bc:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return puVar24;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

