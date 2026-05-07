
undefined8 FUN_0015485c(long *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  bool bVar6;
  uint uVar7;
  void *__ptr;
  void *__ptr_00;
  undefined8 *__ptr_01;
  void *pvVar8;
  long lVar9;
  long lVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  int iVar14;
  size_t sVar15;
  uint *puVar16;
  ulong uVar17;
  int iVar18;
  uint uVar19;
  long *plVar20;
  long extraout_x8;
  long extraout_x8_00;
  long lVar21;
  long extraout_x10;
  long lVar22;
  ulong uVar23;
  undefined4 *puVar24;
  undefined8 *puVar25;
  ulong uVar27;
  undefined8 uVar28;
  uint uVar29;
  long lVar30;
  uint uVar31;
  ulong uVar32;
  undefined1 auVar33 [16];
  long *plStack_20;
  long lStack_8;
  undefined8 *puVar26;
  
  if (((param_1 != (long *)0x0) && (uVar29 = *(uint *)(param_1 + 1), uVar29 != 0)) &&
     (uVar2 = *(uint *)(param_1 + 2), uVar2 - 1 < 0xfffffffe)) {
    uVar23 = (ulong)uVar2;
    __ptr = calloc(uVar23,0x10);
    if (__ptr != (void *)0x0) {
      __ptr_00 = calloc(uVar23,8);
      if (__ptr_00 != (void *)0x0) {
        uVar19 = 0;
        plVar20 = (long *)(*param_1 + 8);
        do {
          lVar9 = plVar20[1];
          if ((int)lVar9 != 0) {
            iVar14 = 0;
            puVar13 = (uint *)(*plVar20 + 8);
            do {
              uVar31 = *puVar13;
              puVar13 = puVar13 + 0x22;
              if (uVar31 < uVar2) {
                lVar30 = (ulong)uVar31 * 8;
                *(uint *)((long)__ptr_00 + lVar30) = uVar19;
                *(int *)((long)__ptr_00 + lVar30 + 4) = iVar14;
              }
              iVar14 = iVar14 + 1;
            } while (iVar14 != (int)lVar9);
          }
          uVar19 = uVar19 + 1;
          plVar20 = plVar20 + 9;
        } while (uVar29 != uVar19);
      }
      __ptr_01 = calloc(uVar23,0x10);
      if (__ptr_01 == (undefined8 *)0x0) {
        free(__ptr);
        free(__ptr_00);
      }
      else {
        lStack_8 = 0;
        do {
          lVar9 = *param_1 + lStack_8 * 0x48;
          if (*(int *)(lVar9 + 0x10) != 0) {
            lVar30 = 0;
            uVar29 = 0;
            do {
              uVar19 = 0;
              piVar1 = (int *)(*(long *)(lVar9 + 8) + lVar30);
              puVar13 = (uint *)(piVar1 + 6);
              uVar31 = piVar1[0x12];
              uVar7 = piVar1[2];
              if (uVar31 != 0) {
                do {
                  uVar3 = *puVar13;
                  uVar23 = (ulong)uVar3;
                  uVar5 = uVar7;
                  if (uVar7 < uVar3) {
                    uVar5 = uVar3;
                  }
                  if (uVar5 < uVar2) {
                    lVar10 = uVar23 * 0x10;
                    puVar11 = (uint *)__ptr_01[uVar23 * 2];
                    uVar5 = *(uint *)(__ptr_01 + uVar23 * 2 + 1);
                    if (uVar5 == 0) {
                      iVar14 = 1;
                      puVar12 = puVar11;
                      if (*(int *)((long)__ptr_01 + lVar10 + 0xc) == 0) {
                        lVar22 = 0;
                        iVar14 = 1;
LAB_00154c78:
                        sVar15 = 0x10;
                        iVar18 = 4;
                        goto LAB_00154ba0;
                      }
                    }
                    else {
                      lVar22 = (ulong)uVar5 * 4;
                      puVar12 = puVar11 + uVar5;
                      puVar16 = puVar11;
                      do {
                        uVar3 = *puVar16;
                        puVar16 = puVar16 + 1;
                        if (uVar7 == uVar3) goto LAB_001549b8;
                      } while (puVar12 != puVar16);
                      uVar31 = *(uint *)((long)__ptr_01 + lVar10 + 0xc);
                      iVar14 = uVar5 + 1;
                      if (uVar31 <= uVar5) {
                        if (uVar31 == 0) goto LAB_00154c78;
                        iVar18 = uVar31 << 1;
                        sVar15 = ((ulong)uVar31 & 0x7fffffff) << 3;
LAB_00154ba0:
                        *(int *)((long)__ptr_01 + lVar10 + 0xc) = iVar18;
                        pvVar8 = realloc(puVar11,sVar15);
                        __ptr_01[uVar23 * 2] = pvVar8;
                        puVar12 = (uint *)((long)pvVar8 + lVar22);
                      }
                    }
                    *puVar12 = uVar7;
                    *(int *)(__ptr_01 + uVar23 * 2 + 1) = iVar14;
                    uVar31 = piVar1[0x12];
                  }
LAB_001549b8:
                  uVar19 = uVar19 + 1;
                  puVar13 = puVar13 + 4;
                } while (uVar19 < uVar31);
              }
              if ((*piVar1 == 0x1b) && (uVar19 = piVar1[0x18], uVar19 != 0)) {
                lVar10 = 0;
                do {
                  uVar5 = *(uint *)(*(long *)(piVar1 + 0x14) + lVar10 * 0x10);
                  uVar23 = (ulong)uVar5;
                  uVar31 = uVar7;
                  if (uVar7 < uVar5) {
                    uVar31 = uVar5;
                  }
                  if (uVar31 < uVar2) {
                    lVar22 = uVar23 * 0x10;
                    puVar13 = (uint *)__ptr_01[uVar23 * 2];
                    uVar31 = *(uint *)(__ptr_01 + uVar23 * 2 + 1);
                    if (uVar31 == 0) {
                      iVar14 = 1;
                      puVar11 = puVar13;
                      if (*(int *)((long)__ptr_01 + lVar22 + 0xc) == 0) {
                        lVar21 = 0;
                        iVar14 = 1;
LAB_00154cd0:
                        sVar15 = 0x10;
                        iVar18 = 4;
                        goto LAB_00154c90;
                      }
                    }
                    else {
                      lVar21 = (ulong)uVar31 * 4;
                      puVar11 = puVar13 + uVar31;
                      puVar12 = puVar13;
                      do {
                        uVar5 = *puVar12;
                        puVar12 = puVar12 + 1;
                        if (uVar7 == uVar5) goto LAB_00154bdc;
                      } while (puVar11 != puVar12);
                      uVar19 = *(uint *)((long)__ptr_01 + lVar22 + 0xc);
                      iVar14 = uVar31 + 1;
                      if (uVar19 <= uVar31) {
                        if (uVar19 == 0) goto LAB_00154cd0;
                        iVar18 = uVar19 << 1;
                        sVar15 = ((ulong)uVar19 & 0x7fffffff) << 3;
LAB_00154c90:
                        *(int *)((long)__ptr_01 + lVar22 + 0xc) = iVar18;
                        pvVar8 = realloc(puVar13,sVar15);
                        __ptr_01[uVar23 * 2] = pvVar8;
                        puVar11 = (uint *)((long)pvVar8 + lVar21);
                      }
                    }
                    *puVar11 = uVar7;
                    *(int *)(__ptr_01 + uVar23 * 2 + 1) = iVar14;
                    uVar19 = piVar1[0x18];
                  }
LAB_00154bdc:
                  lVar10 = lVar10 + 1;
                } while ((uint)lVar10 < uVar19);
              }
              uVar29 = uVar29 + 1;
              lVar30 = lVar30 + 0x88;
            } while (uVar29 < *(uint *)(lVar9 + 0x10));
            uVar29 = *(uint *)(param_1 + 1);
          }
          lStack_8 = lStack_8 + 1;
        } while ((uint)lStack_8 < uVar29);
        if (__ptr_00 != (void *)0x0) {
          uVar19 = uVar2;
          if (uVar2 < 0x100) {
            uVar19 = 0x100;
          }
          uVar31 = uVar2;
          if (uVar2 < 0x100) {
            uVar31 = 0x100;
          }
          uVar23 = (ulong)uVar31;
          pvVar8 = malloc((ulong)uVar19 << 2);
          if (uVar29 != 0) {
            uVar19 = 0;
            lVar9 = *param_1;
            plStack_20 = (long *)(lVar9 + 8);
            plVar20 = plStack_20 + (ulong)uVar29 * 9;
            do {
              if (*(uint *)(plStack_20 + 1) != 0) {
                lVar30 = *plStack_20;
                lVar10 = lVar30 + (ulong)*(uint *)(plStack_20 + 1) * 0x88;
LAB_00154a98:
                do {
                  if (*(uint *)(lVar30 + 8) < uVar2) {
                    auVar33 = evaluate_instr((ulong)*(uint *)(lVar30 + 8) << 4,lVar30,__ptr,uVar2);
                    if ((*(int *)((long)__ptr + extraout_x8) != auVar33._0_4_) ||
                       ((*(int *)((long)__ptr + extraout_x8) == 1 &&
                        (*(long *)((long)__ptr + extraout_x8 + 8) != auVar33._8_8_)))) {
                      *(long *)((long)__ptr + extraout_x8) = auVar33._0_8_;
                      *(long *)((long)__ptr + extraout_x8 + 8) = auVar33._8_8_;
                      iVar14 = *(int *)((long)__ptr_01 + extraout_x8 + 8);
                      if (iVar14 != 0) {
                        puVar24 = *(undefined4 **)((long)__ptr_01 + extraout_x8);
                        uVar31 = uVar19 + iVar14;
                        do {
                          uVar4 = *puVar24;
                          uVar7 = (uint)uVar23;
                          if (uVar7 <= uVar19) {
                            sVar15 = 0x40;
                            if (uVar7 == 0) {
                              uVar23 = 0x10;
                            }
                            else {
                              uVar23 = (ulong)(uVar7 << 1);
                              sVar15 = uVar23 << 2;
                            }
                            pvVar8 = realloc(pvVar8,sVar15);
                          }
                          uVar7 = uVar19 + 1;
                          *(undefined4 *)((long)pvVar8 + (ulong)uVar19 * 4) = uVar4;
                          puVar24 = puVar24 + 1;
                          uVar19 = uVar7;
                        } while (uVar7 != uVar31);
                        lVar30 = lVar30 + 0x88;
                        uVar19 = uVar31;
                        if (lVar10 == lVar30) break;
                        goto LAB_00154a98;
                      }
                    }
                  }
                  lVar30 = lVar30 + 0x88;
                } while (lVar10 != lVar30);
              }
              plStack_20 = plStack_20 + 9;
            } while (plVar20 != plStack_20);
            if (uVar19 != 0) {
              uVar27 = (ulong)(uVar19 - 1);
              uVar31 = *(uint *)((long)pvVar8 + uVar27 * 4);
              if (uVar2 << 2 != 0) {
                uVar32 = (ulong)(uVar19 - 1);
                iVar14 = 1;
                do {
                  uVar19 = (uint)uVar32;
                  if (uVar31 < uVar2) {
                    lVar30 = (ulong)uVar31 * 8;
                    uVar5 = *(uint *)((long)__ptr_00 + lVar30);
                    uVar7 = *(uint *)((long)__ptr_00 + lVar30 + 4);
                    if (((uVar5 < uVar29) &&
                        (lVar30 = lVar9 + (ulong)uVar5 * 0x48, uVar7 < *(uint *)(lVar30 + 0x10))) &&
                       (lVar30 = *(long *)(lVar30 + 8) + (ulong)uVar7 * 0x88,
                       *(uint *)(lVar30 + 8) == uVar31)) {
                      auVar33 = evaluate_instr((ulong)uVar31 << 4,lVar30,__ptr,uVar2);
                      lVar10 = auVar33._8_8_;
                      uVar31 = *(uint *)((long)__ptr + extraout_x8_00);
                      uVar17 = auVar33._0_8_ & 0xffffffff;
                      lVar22 = *(long *)(extraout_x10 + 8);
                      uVar7 = auVar33._0_4_;
                      lVar30 = lVar10;
                      if (uVar31 < uVar7) {
                        if (uVar7 == 1 && uVar31 == 1) {
                          uVar17 = 2;
                          lVar30 = 0;
                          if (lVar22 == lVar10) goto LAB_00154dbc;
                        }
                      }
                      else if (uVar7 == 1) {
                        if (uVar31 == 1 && lVar22 != lVar10) {
                          uVar17 = 2;
                          lVar30 = 0;
                        }
                        else if (uVar31 == 1 && lVar22 == lVar10) goto LAB_00154dbc;
                      }
                      else if (uVar31 == uVar7) goto LAB_00154dbc;
                      *(ulong *)((long)__ptr + extraout_x8_00) =
                           auVar33._0_8_ & 0xffffffff00000000 | uVar17;
                      *(long *)(extraout_x10 + 8) = lVar30;
                      iVar18 = *(int *)((long)__ptr_01 + extraout_x8_00 + 8);
                      if (iVar18 != 0) {
                        puVar24 = *(undefined4 **)((long)__ptr_01 + extraout_x8_00);
                        uVar19 = uVar19 + iVar18;
                        do {
                          uVar4 = *puVar24;
                          uVar31 = (uint)uVar23;
                          if (uVar31 <= (uint)uVar32) {
                            sVar15 = 0x40;
                            if (uVar31 == 0) {
                              uVar23 = 0x10;
                            }
                            else {
                              uVar23 = (ulong)(uVar31 << 1);
                              sVar15 = uVar23 << 2;
                            }
                            pvVar8 = realloc(pvVar8,sVar15);
                          }
                          uVar31 = (uint)uVar32 + 1;
                          *(undefined4 *)((long)pvVar8 + uVar27 * 4) = uVar4;
                          puVar24 = puVar24 + 1;
                          uVar32 = (ulong)uVar31;
                          uVar27 = (ulong)uVar31;
                        } while (uVar31 != uVar19);
                      }
                    }
                  }
LAB_00154dbc:
                  if (uVar19 == 0) break;
                  uVar27 = (ulong)(uVar19 - 1);
                  uVar31 = *(uint *)((long)pvVar8 + uVar27 * 4);
                  bVar6 = uVar2 << 2 != iVar14;
                  uVar32 = uVar27;
                  iVar14 = iVar14 + 1;
                } while (bVar6);
              }
            }
            lVar30 = 0;
            uVar28 = 0;
            do {
              lVar9 = lVar9 + lVar30 * 0x48;
              uVar19 = *(uint *)(lVar9 + 0x10);
              if (uVar19 != 0) {
                lVar10 = 0;
                uVar29 = 0;
                do {
                  while( true ) {
                    piVar1 = (int *)(*(long *)(lVar9 + 8) + lVar10);
                    if (((uint)piVar1[2] < uVar2) &&
                       (lVar22 = (ulong)(uint)piVar1[2] * 0x10, *(int *)((long)__ptr + lVar22) == 1)
                       ) break;
LAB_00154e1c:
                    uVar29 = uVar29 + 1;
                    lVar10 = lVar10 + 0x88;
                    if (uVar19 <= uVar29) goto LAB_00154e98;
                  }
                  iVar14 = *piVar1;
                  if ((iVar14 == 1) || (iVar14 - 0x16U < 5)) goto LAB_00154e1c;
                  if (iVar14 == 0x1b) {
                    free(*(void **)(piVar1 + 0x14));
                    free(*(void **)(piVar1 + 0x16));
                    piVar1[0x14] = 0;
                    piVar1[0x15] = 0;
                    piVar1[0x16] = 0;
                    piVar1[0x17] = 0;
                    uVar19 = *(uint *)(lVar9 + 0x10);
                    piVar1[0x18] = 0;
                  }
                  uVar28 = *(undefined8 *)((long)__ptr + lVar22 + 8);
                  uVar29 = uVar29 + 1;
                  *piVar1 = 1;
                  lVar10 = lVar10 + 0x88;
                  *(undefined8 *)(piVar1 + 4) = uVar28;
                  uVar28 = 1;
                  piVar1[0x12] = 0;
                } while (uVar29 < uVar19);
LAB_00154e98:
                uVar29 = *(uint *)(param_1 + 1);
              }
              lVar30 = lVar30 + 1;
              if (uVar29 <= (uint)lVar30) goto LAB_00154ec8;
              lVar9 = *param_1;
            } while( true );
          }
          uVar28 = 0;
LAB_00154ec8:
          free(pvVar8);
          free(__ptr);
          free(__ptr_00);
          puVar25 = __ptr_01;
          do {
            puVar26 = puVar25 + 2;
            free((void *)*puVar25);
            puVar25 = puVar26;
          } while (puVar26 != __ptr_01 + (ulong)uVar2 * 2);
          free(__ptr_01);
          return uVar28;
        }
        free(__ptr);
        puVar25 = __ptr_01;
        do {
          puVar26 = puVar25 + 2;
          free((void *)*puVar25);
          puVar25 = puVar26;
        } while (puVar26 != __ptr_01 + (ulong)uVar2 * 2);
        free(__ptr_01);
      }
    }
  }
  return 0;
}

