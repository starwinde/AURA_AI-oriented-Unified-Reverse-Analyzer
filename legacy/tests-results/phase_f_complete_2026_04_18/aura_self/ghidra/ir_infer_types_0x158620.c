
/* WARNING: Type propagation algorithm not settling */

undefined8 ir_infer_types(long *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char cVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  ulong uVar11;
  long lVar12;
  uint uVar13;
  long lVar14;
  int *piVar15;
  long *plVar16;
  ulong uVar17;
  long *plVar18;
  long *plVar19;
  ulong uVar20;
  ulong extraout_x8;
  ulong extraout_x8_00;
  ulong extraout_x8_01;
  uint *puVar21;
  uint *extraout_x9;
  uint *extraout_x9_00;
  uint *extraout_x9_01;
  ulong uVar22;
  ulong extraout_x10;
  ulong extraout_x10_00;
  ulong extraout_x10_01;
  uint *puVar23;
  int *piVar24;
  uint *extraout_x11;
  uint *extraout_x11_00;
  uint *extraout_x11_01;
  undefined1 *puVar25;
  undefined1 *extraout_x12;
  undefined1 *extraout_x12_00;
  undefined1 *extraout_x12_01;
  undefined8 uVar26;
  undefined8 extraout_x13;
  undefined8 extraout_x13_00;
  undefined8 extraout_x13_01;
  void *__ptr;
  void *extraout_x14;
  void *extraout_x14_00;
  void *extraout_x14_01;
  undefined8 uVar27;
  undefined8 extraout_x15;
  undefined8 extraout_x15_00;
  undefined8 extraout_x15_01;
  uint *puVar28;
  long *plVar29;
  uint uVar30;
  uint uVar31;
  ulong uVar32;
  ulong extraout_x18;
  ulong extraout_x18_00;
  ulong extraout_x18_01;
  uint uVar33;
  undefined4 *puVar34;
  long *plVar36;
  char cVar37;
  char cVar38;
  undefined4 *puVar35;
  
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  uVar33 = *(uint *)(param_1 + 1);
  if (uVar33 != 0) {
    uVar2 = *(uint *)(param_1 + 2);
    __ptr = (void *)0x0;
    if ((uVar2 != 0) && (__ptr = calloc((ulong)uVar2,1), __ptr == (void *)0x0)) {
      return 0xfffffffc;
    }
    uVar20 = 0x50;
    plVar18 = (long *)(*param_1 + 8);
    puVar25 = &CSWTCH_4;
    uVar22 = 10;
    uVar17 = 0x90;
    uVar27 = 5;
    uVar32 = 0x1000000d;
    plVar19 = plVar18 + (ulong)uVar33 * 10;
    do {
      uVar26 = 0;
      plVar29 = plVar18;
      do {
        if (*(uint *)(plVar29 + 1) != 0) {
          puVar21 = (uint *)*plVar29;
          puVar23 = (uint *)((long)puVar21 + (ulong)*(uint *)(plVar29 + 1) * (uVar17 & 0xffffffff));
          do {
            while (uVar33 = *puVar21, 0xe < uVar33) {
              if (uVar33 == 0x1b) {
                uVar33 = puVar21[0x18];
                if ((uVar33 != 0) && (*(long *)(puVar21 + 0x14) != 0)) {
                  puVar1 = (undefined4 *)(*(long *)(puVar21 + 0x14) + 4);
                  uVar11 = 6;
                  puVar34 = puVar1;
                  do {
                    puVar35 = puVar34 + 4;
                    uVar11 = type_wider(uVar11,*puVar34);
                    uVar20 = extraout_x8_01;
                    puVar21 = extraout_x9_01;
                    uVar22 = extraout_x10_01;
                    puVar23 = extraout_x11_01;
                    puVar25 = extraout_x12_01;
                    uVar26 = extraout_x13_01;
                    __ptr = extraout_x14_01;
                    uVar27 = extraout_x15_01;
                    uVar32 = extraout_x18_01;
                    puVar34 = puVar35;
                  } while (puVar35 != puVar1 + (ulong)uVar33 * 4);
                  goto LAB_001586d4;
                }
              }
              else if (uVar33 < 0x1c) {
                if (uVar33 - 0x11 < 4) goto LAB_00158aec;
              }
              else if ((uVar33 == 0x1c) && (2 < puVar21[0x12])) {
                uVar11 = type_wider(puVar21[0xb],puVar21[0xf]);
                uVar20 = extraout_x8;
                puVar21 = extraout_x9;
                uVar22 = extraout_x10;
                puVar23 = extraout_x11;
                puVar25 = extraout_x12;
                uVar26 = extraout_x13;
                __ptr = extraout_x14;
                uVar27 = extraout_x15;
                uVar32 = extraout_x18;
                goto LAB_001586d4;
              }
LAB_001586fc:
              puVar21 = puVar21 + 0x24;
              if (puVar21 == puVar23) goto LAB_00158708;
            }
            if (10 < uVar33) {
LAB_00158aec:
              uVar11 = 6;
LAB_001586d4:
              if (puVar21[3] != (uint)uVar11 && (puVar21[3] != 0 && puVar21[2] != 0xffffffff)) {
                uVar26 = 1;
                puVar21[3] = (uint)uVar11;
              }
              goto LAB_001586fc;
            }
            if (8 < uVar33) {
LAB_001586c8:
              if (puVar21[0x12] == 0) goto LAB_001586fc;
LAB_001586d0:
              uVar11 = (ulong)puVar21[7];
              goto LAB_001586d4;
            }
            if (uVar33 < 2) {
              if (uVar33 != 0) goto LAB_001586fc;
              goto LAB_001586c8;
            }
            if (1 < puVar21[0x12]) {
              uVar11 = type_wider(puVar21[7],puVar21[0xb]);
              uVar20 = extraout_x8_00;
              puVar21 = extraout_x9_00;
              uVar22 = extraout_x10_00;
              puVar23 = extraout_x11_00;
              puVar25 = extraout_x12_00;
              uVar26 = extraout_x13_00;
              __ptr = extraout_x14_00;
              uVar27 = extraout_x15_00;
              uVar32 = extraout_x18_00;
              goto LAB_001586d4;
            }
            if (puVar21[0x12] == 1) goto LAB_001586d0;
            puVar21 = puVar21 + 0x24;
          } while (puVar21 != puVar23);
        }
LAB_00158708:
        plVar29 = plVar29 + 10;
      } while (plVar29 != plVar19);
      uVar33 = 0;
      plVar29 = plVar18;
      do {
        if (*(uint *)(plVar29 + 1) != 0) {
          piVar15 = (int *)*plVar29;
          piVar24 = (int *)((long)piVar15 + (ulong)*(uint *)(plVar29 + 1) * (uVar17 & 0xffffffff));
          do {
            if ((((*piVar15 - 0x15U < 2) && (piVar15[0x12] != 0)) && (piVar15[6] != -1)) &&
               (*(uint *)(param_1 + 1) != 0)) {
              plVar16 = plVar18;
              do {
                if (*(uint *)(plVar16 + 1) != 0) {
                  lVar12 = *plVar16;
                  lVar14 = lVar12 + (ulong)*(uint *)(plVar16 + 1) * (uVar17 & 0xffffffff);
                  do {
                    if (piVar15[6] == *(int *)(lVar12 + 8)) {
                      if ((*(uint *)(lVar12 + 0xc) != 5) &&
                         ((*(uint *)(lVar12 + 0xc) & 0xfffffffb) == 0)) {
                        uVar33 = 1;
                        *(uint *)(lVar12 + 0xc) = (uint)uVar27;
                      }
                      goto LAB_001587b0;
                    }
                    lVar12 = lVar12 + 0x90;
                  } while (lVar12 != lVar14);
                }
                plVar16 = plVar16 + 10;
              } while (plVar16 !=
                       (long *)((long)plVar18 +
                               (ulong)*(uint *)(param_1 + 1) * (uVar20 & 0xffffffff)));
            }
LAB_001587b0:
            piVar15 = piVar15 + 0x24;
          } while (piVar15 != piVar24);
        }
        plVar29 = plVar29 + 10;
      } while (plVar29 != plVar19);
      uVar13 = 0;
      plVar29 = plVar18;
      do {
        if (*(uint *)(plVar29 + 1) != 0) {
          puVar21 = (uint *)*plVar29;
          puVar23 = (uint *)((long)puVar21 + (ulong)*(uint *)(plVar29 + 1) * (uVar17 & 0xffffffff));
          do {
            if (((puVar21[2] != 0xffffffff) && (puVar21[3] != 5)) && (puVar21[0x12] != 0)) {
              puVar28 = puVar21 + 6;
              uVar30 = 0;
              do {
                if (puVar28[1] == 5) {
LAB_00158a88:
                  if ((*puVar21 < 0x1d) && ((uVar32 >> ((ulong)*puVar21 & 0x3f) & 1) != 0)) {
                    puVar21[3] = (uint)uVar27;
                    uVar13 = 1;
                  }
                  break;
                }
                if ((*puVar28 != 0xffffffff) && (*(uint *)(param_1 + 1) != 0)) {
                  plVar16 = plVar18;
                  do {
                    if (*(uint *)(plVar16 + 1) != 0) {
                      lVar12 = *plVar16;
                      lVar14 = lVar12 + (ulong)*(uint *)(plVar16 + 1) * (uVar17 & 0xffffffff);
                      do {
                        if (*puVar28 == *(uint *)(lVar12 + 8)) {
                          if (*(int *)(lVar12 + 0xc) != 5) goto LAB_00158870;
                          puVar21[(ulong)uVar30 * 4 + 7] = 5;
                          goto LAB_00158a88;
                        }
                        lVar12 = lVar12 + 0x90;
                      } while (lVar12 != lVar14);
                    }
                    plVar16 = plVar16 + 10;
                  } while ((long *)((long)plVar18 +
                                   (ulong)*(uint *)(param_1 + 1) * (uVar20 & 0xffffffff)) != plVar16
                          );
                }
LAB_00158870:
                uVar30 = uVar30 + 1;
                puVar28 = puVar28 + 4;
              } while (uVar30 != 3 && uVar30 < puVar21[0x12]);
            }
            puVar21 = puVar21 + 0x24;
          } while (puVar23 != puVar21);
        }
        plVar29 = plVar29 + 10;
      } while (plVar29 != plVar19);
      uVar13 = (uint)uVar26 | uVar33 | uVar13;
      if (__ptr != (void *)0x0) {
        uVar33 = 0;
        plVar29 = plVar18;
        do {
          if (*(uint *)(plVar29 + 1) != 0) {
            piVar15 = (int *)*plVar29;
            piVar24 = (int *)((long)piVar15 + (ulong)*(uint *)(plVar29 + 1) * (uVar17 & 0xffffffff))
            ;
            do {
              if (((*piVar15 - 0x15U < 2) && (piVar15[0x12] != 0)) &&
                 (uVar30 = piVar15[6], uVar30 < uVar2)) {
                if (*piVar15 == 0x15) {
                  uVar10 = piVar15[3];
                  if (uVar10 < 0xd) goto LAB_00158900;
LAB_00158c20:
                  uVar10 = 8;
LAB_00158c24:
                  if (*(uint *)(param_1 + 1) != 0) {
                    plVar16 = plVar18;
                    do {
                      if (*(uint *)(plVar16 + 1) != 0) {
                        lVar12 = *plVar16;
                        lVar14 = lVar12 + (ulong)*(uint *)(plVar16 + 1) * (uVar17 & 0xffffffff);
                        do {
                          if (uVar30 == *(uint *)(lVar12 + 8)) {
                            if (*(char *)((long)__ptr + (ulong)uVar30) == '\0') {
                              if (*(byte *)(lVar12 + 0x88) == 0) {
                                uVar33 = 1;
                                *(char *)(lVar12 + 0x88) = (char)uVar10;
                              }
                              else if ((uVar10 & 0xff) != (uint)*(byte *)(lVar12 + 0x88)) {
                                uVar33 = 1;
                                *(undefined1 *)((long)__ptr + (ulong)uVar30) = 1;
                                *(undefined1 *)(lVar12 + 0x88) = 0;
                              }
                            }
                            goto LAB_00158910;
                          }
                          lVar12 = lVar12 + 0x90;
                        } while (lVar12 != lVar14);
                      }
                      plVar16 = plVar16 + 10;
                    } while (plVar16 !=
                             (long *)((long)plVar18 +
                                     (ulong)*(uint *)(param_1 + 1) * (uVar20 & 0xffffffff)));
                  }
                }
                else if (piVar15[0x12] != 1) {
                  uVar10 = piVar15[0xb];
                  if (0xc < uVar10) goto LAB_00158c20;
LAB_00158900:
                  uVar10 = *(uint *)(puVar25 + (ulong)uVar10 * 4);
                  if (uVar10 - 1 < 0xff) goto LAB_00158c24;
                }
              }
LAB_00158910:
              piVar15 = piVar15 + 0x24;
            } while (piVar15 != piVar24);
          }
          plVar29 = plVar29 + 10;
        } while (plVar29 != plVar19);
        uVar30 = *(uint *)(param_1 + 1);
        uVar13 = uVar13 | uVar33;
        if (uVar30 != 0) {
          uVar10 = 0;
          uVar33 = 0;
          plVar29 = (long *)(*param_1 + 8);
          plVar16 = plVar29;
          do {
            if (*(uint *)(plVar16 + 1) != 0) {
              puVar21 = (uint *)(*plVar16 + 0x18);
              puVar23 = (uint *)((long)puVar21 +
                                (ulong)*(uint *)(plVar16 + 1) * (uVar17 & 0xffffffff));
LAB_00158970:
              do {
                uVar5 = puVar21[-6];
                if ((((uVar5 == 0 || uVar5 == 2) || uVar5 == 3) &&
                    (uVar6 = puVar21[-4], uVar6 != 0xffffffff)) && (puVar21[-3] == 5)) {
                  cVar37 = '\0';
                  if (uVar6 < uVar2) {
                    cVar37 = *(char *)((long)__ptr + (ulong)uVar6);
                  }
                  uVar3 = puVar21[0xc];
                  if (uVar3 != 0) {
                    cVar38 = (char)puVar21[0x1c];
                    uVar31 = 0;
                    puVar28 = puVar21;
                    do {
                      uVar4 = *puVar28;
                      plVar36 = plVar29;
                      if (uVar4 < uVar2) {
                        do {
                          if (*(uint *)(plVar36 + 1) != 0) {
                            piVar15 = (int *)*plVar36;
                            piVar24 = (int *)((long)piVar15 +
                                             (ulong)*(uint *)(plVar36 + 1) * (uVar17 & 0xffffffff));
                            do {
                              if (uVar4 == piVar15[2]) {
                                if ((uVar5 != 0) && (piVar15[3] != 5)) {
                                  if (*piVar15 != 1) goto LAB_001589d0;
                                  lVar14 = *(long *)(piVar15 + 4);
                                  lVar12 = -lVar14;
                                  if (-1 < lVar14) {
                                    lVar12 = lVar14;
                                  }
                                  if (lVar12 < 0x1000) goto LAB_001589d0;
                                }
                                cVar8 = *(char *)((long)__ptr + (ulong)uVar4);
                                cVar7 = (char)piVar15[0x22];
                                if (cVar37 != '\0' && cVar8 == '\0') {
                                  *(undefined1 *)((long)__ptr + (ulong)uVar4) = 1;
                                  if (cVar7 == '\0') {
LAB_00158d48:
                                    if (cVar38 != '\0') {
                                      uVar10 = 1;
                                      *(char *)(piVar15 + 0x22) = cVar38;
                                    }
                                  }
                                  else {
                                    uVar10 = 1;
                                    *(undefined1 *)(piVar15 + 0x22) = 0;
LAB_00158bb8:
                                    if ((cVar7 != '\0' && cVar7 != cVar38) && cVar38 != '\0') {
                                      if (uVar6 < uVar2) {
LAB_00158d2c:
                                        *(undefined1 *)((long)__ptr + (ulong)uVar6) = 1;
                                      }
LAB_00158bd0:
                                      *(undefined1 *)(piVar15 + 0x22) = 0;
                                      uVar10 = 1;
                                      *(undefined1 *)((long)__ptr + (ulong)uVar4) = 1;
                                      *(undefined1 *)(puVar21 + 0x1c) = 0;
                                      cVar38 = '\0';
                                    }
                                  }
                                  goto LAB_001589d0;
                                }
                                if (cVar8 == '\0' || cVar37 != '\0') {
                                  if (cVar37 != '\0' || cVar38 != '\0') {
                                    if (cVar7 == '\0' && cVar8 == '\0') goto LAB_00158d48;
                                    goto LAB_00158bb8;
                                  }
                                  if (cVar7 == '\0') {
                                    cVar38 = '\0';
                                    if (cVar8 != '\0') {
                                      cVar38 = '\0';
                                    }
                                    goto LAB_001589d0;
                                  }
                                }
                                else {
                                  if (uVar2 <= uVar6) {
                                    if (cVar38 == '\0') goto joined_r0x00158cdc;
                                    if (cVar7 != '\0' && cVar7 != cVar38) goto LAB_00158bd0;
                                    goto LAB_001589d0;
                                  }
                                  uVar9 = puVar21[0x1c];
                                  *(undefined1 *)((long)__ptr + (ulong)uVar6) = 1;
                                  if ((char)uVar9 == '\0') {
                                    if (cVar38 != '\0') {
LAB_00158d20:
                                      if (cVar7 != '\0' && cVar7 != cVar38) goto LAB_00158d2c;
                                      goto LAB_001589d0;
                                    }
                                  }
                                  else {
                                    *(undefined1 *)(puVar21 + 0x1c) = 0;
                                    if (cVar38 != '\0') {
                                      uVar10 = 1;
                                      goto LAB_00158d20;
                                    }
                                    uVar10 = 1;
                                  }
joined_r0x00158cdc:
                                  if (cVar7 == '\0') {
                                    cVar38 = '\0';
                                    goto LAB_001589d0;
                                  }
                                }
                                uVar10 = 1;
                                *(char *)(puVar21 + 0x1c) = cVar7;
                                cVar38 = cVar7;
                                goto LAB_001589d0;
                              }
                              piVar15 = piVar15 + 0x24;
                            } while (piVar15 != piVar24);
                          }
                          plVar36 = plVar36 + 10;
                        } while (plVar36 !=
                                 (long *)((long)plVar29 + (ulong)uVar30 * (uVar20 & 0xffffffff)));
                      }
LAB_001589d0:
                      uVar31 = uVar31 + 1;
                      puVar28 = puVar28 + 4;
                    } while (uVar31 < uVar3 && uVar31 != 3);
                    puVar21 = puVar21 + 0x24;
                    if (puVar21 == puVar23) break;
                    goto LAB_00158970;
                  }
                }
                puVar21 = puVar21 + 0x24;
              } while (puVar21 != puVar23);
              uVar30 = *(uint *)(param_1 + 1);
            }
            uVar33 = uVar33 + 1;
            plVar16 = plVar16 + 10;
          } while (uVar33 < uVar30);
          uVar13 = uVar13 | uVar10;
        }
      }
    } while ((uVar13 != 0) && (uVar33 = (int)uVar22 - 1, uVar22 = (ulong)uVar33, uVar33 != 0));
    free(__ptr);
  }
  return 0;
}

