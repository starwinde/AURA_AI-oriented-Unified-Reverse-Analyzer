
int ir_expr_reassoc(long *param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  void *__ptr;
  uint *puVar6;
  ulong uVar7;
  int *piVar8;
  int *piVar9;
  long lVar10;
  uint *puVar11;
  long *plVar12;
  uint *puVar13;
  long *plVar14;
  long *plVar15;
  long *plVar16;
  int *piVar17;
  ulong uVar18;
  ulong uVar19;
  int iVar20;
  int iVar21;
  long lVar22;
  
  if (((param_1 != (long *)0x0) && (uVar2 = *(uint *)(param_1 + 1), uVar2 != 0)) &&
     (uVar3 = *(uint *)(param_1 + 2), uVar3 != 0)) {
    lVar22 = *param_1;
    __ptr = calloc((ulong)uVar3,0x10);
    if (__ptr != (void *)0x0) {
      plVar14 = (long *)(lVar22 + 8);
      plVar15 = plVar14 + (ulong)uVar2 * 10;
      plVar12 = plVar14;
      do {
        if (*(uint *)(plVar12 + 1) != 0) {
          lVar22 = *plVar12;
          lVar10 = lVar22 + (ulong)*(uint *)(plVar12 + 1) * 0x88;
          do {
            if (*(uint *)(lVar22 + 8) < uVar3) {
              *(long *)((long)__ptr + (ulong)*(uint *)(lVar22 + 8) * 0x10) = lVar22;
            }
            lVar22 = lVar22 + 0x88;
          } while (lVar22 != lVar10);
        }
        plVar12 = plVar12 + 10;
        plVar16 = plVar14;
      } while (plVar12 != plVar15);
      do {
        if (*(uint *)(plVar16 + 1) != 0) {
          puVar6 = (uint *)(*plVar16 + 0x18);
          puVar13 = puVar6 + (ulong)*(uint *)(plVar16 + 1) * 0x22;
          do {
            uVar2 = puVar6[0xc];
            if (uVar2 != 0) {
              uVar4 = *puVar6;
              if (uVar4 < uVar3) {
                *(int *)((long)__ptr + (ulong)uVar4 * 0x10 + 8) =
                     *(int *)((long)__ptr + (ulong)uVar4 * 0x10 + 8) + 1;
              }
              if (uVar2 != 1) {
                uVar4 = puVar6[4];
                if (uVar4 < uVar3) {
                  *(int *)((long)__ptr + (ulong)uVar4 * 0x10 + 8) =
                       *(int *)((long)__ptr + (ulong)uVar4 * 0x10 + 8) + 1;
                }
                if ((uVar2 != 2) && (uVar2 = puVar6[8], uVar2 < uVar3)) {
                  *(int *)((long)__ptr + (ulong)uVar2 * 0x10 + 8) =
                       *(int *)((long)__ptr + (ulong)uVar2 * 0x10 + 8) + 1;
                }
              }
            }
            puVar6 = puVar6 + 0x22;
          } while (puVar13 != puVar6);
        }
        plVar16 = plVar16 + 10;
      } while (plVar16 != plVar15);
      iVar21 = 0;
      plVar12 = plVar14;
      do {
        if (*(uint *)(plVar12 + 1) != 0) {
          puVar6 = (uint *)*plVar12;
          puVar13 = puVar6 + (ulong)*(uint *)(plVar12 + 1) * 0x22;
LAB_00159d0c:
          do {
            if (((1 < puVar6[0x12]) && (*puVar6 < 0xd)) &&
               ((0x19d4UL >> ((ulong)*puVar6 & 0x3f) & 1) != 0)) {
              uVar2 = puVar6[6];
              uVar4 = puVar6[10];
              uVar7 = (ulong)uVar4;
              if (uVar2 < uVar3) {
                piVar8 = *(int **)((long)__ptr + (ulong)uVar2 * 0x10);
                if ((piVar8 != (int *)0x0) && (*piVar8 == 1)) {
                  if ((uVar4 < uVar3) &&
                     (piVar8 = *(int **)((long)__ptr + uVar7 * 0x10), piVar8 != (int *)0x0)) {
                    if (*piVar8 == 1) goto LAB_00159d00;
                    uVar1 = *(undefined8 *)(puVar6 + 0xc);
                    *(undefined8 *)(puVar6 + 0xc) = *(undefined8 *)(puVar6 + 8);
                    *(undefined8 *)(puVar6 + 6) = *(undefined8 *)(puVar6 + 10);
                    *(undefined8 *)(puVar6 + 8) = uVar1;
                    puVar6[10] = uVar2;
                    puVar6[0xb] = puVar6[7];
                  }
                  else {
LAB_00159d60:
                    uVar1 = *(undefined8 *)(puVar6 + 0xc);
                    *(undefined8 *)(puVar6 + 0xc) = *(undefined8 *)(puVar6 + 8);
                    *(undefined8 *)(puVar6 + 6) = *(undefined8 *)(puVar6 + 10);
                    *(undefined8 *)(puVar6 + 8) = uVar1;
                    puVar6[10] = uVar2;
                    puVar6[0xb] = puVar6[7];
                  }
LAB_00159d7c:
                  iVar21 = iVar21 + 1;
                  puVar6 = puVar6 + 0x22;
                  if (puVar13 == puVar6) break;
                  goto LAB_00159d0c;
                }
                if (((uVar3 <= uVar4) ||
                    (piVar8 = *(int **)((long)__ptr + uVar7 * 0x10), piVar8 == (int *)0x0)) ||
                   (*piVar8 != 1)) goto LAB_00159edc;
              }
              else if (uVar4 < uVar3) {
                piVar8 = *(int **)((long)__ptr + uVar7 * 0x10);
                if ((piVar8 == (int *)0x0) || (*piVar8 != 1)) goto LAB_00159d60;
              }
              else {
LAB_00159edc:
                if (uVar4 < uVar2) {
                  uVar1 = *(undefined8 *)(puVar6 + 0xc);
                  *(undefined8 *)(puVar6 + 0xc) = *(undefined8 *)(puVar6 + 8);
                  *(undefined8 *)(puVar6 + 6) = *(undefined8 *)(puVar6 + 10);
                  *(undefined8 *)(puVar6 + 8) = uVar1;
                  puVar6[10] = uVar2;
                  puVar6[0xb] = puVar6[7];
                  goto LAB_00159d7c;
                }
              }
            }
LAB_00159d00:
            puVar6 = puVar6 + 0x22;
          } while (puVar13 != puVar6);
        }
        plVar12 = plVar12 + 10;
        if (plVar12 == plVar15) {
          uVar2 = *(uint *)(param_1 + 1);
          uVar3 = *(uint *)(param_1 + 2);
          if (uVar2 != 0) {
            iVar20 = 0;
            plVar12 = plVar14;
            do {
              if (*(uint *)(plVar12 + 1) != 0) {
                puVar6 = (uint *)*plVar12;
                puVar13 = puVar6 + (ulong)*(uint *)(plVar12 + 1) * 0x22;
                do {
                  if (1 < puVar6[0x12]) {
                    uVar4 = *puVar6;
                    if (((uVar4 < 9) && ((0x1d4UL >> ((ulong)uVar4 & 0x3f) & 1) != 0)) &&
                       ((puVar6[10] < uVar3 &&
                        (piVar8 = *(int **)((long)__ptr + (ulong)puVar6[10] * 0x10),
                        piVar8 != (int *)0x0)))) {
                      uVar5 = puVar6[6];
                      if ((*piVar8 == 1 && uVar5 <= uVar3) && (*piVar8 != 1 || uVar3 != uVar5)) {
                        puVar11 = *(uint **)((long)__ptr + (ulong)uVar5 * 0x10);
                        if (((((puVar11 != (uint *)0x0) && (uVar4 == *puVar11)) &&
                             (1 < puVar11[0x12])) &&
                            ((*(int *)((long)__ptr + (ulong)uVar5 * 0x10 + 8) == 1 &&
                             (puVar11[10] < uVar3)))) &&
                           ((piVar17 = *(int **)((long)__ptr + (ulong)puVar11[10] * 0x10),
                            piVar17 != (int *)0x0 && (*piVar17 == 1)))) {
                          uVar19 = *(ulong *)(piVar8 + 4);
                          uVar7 = *(ulong *)(piVar17 + 4);
                          if (uVar4 == 6) {
                            uVar18 = uVar7 & uVar19;
                          }
                          else if (uVar4 < 7) {
                            if (uVar4 == 2) {
                              uVar18 = uVar7 + uVar19;
                            }
                            else {
                              uVar18 = uVar7 * uVar19;
                              if (uVar4 != 4) {
                                uVar18 = uVar7;
                              }
                            }
                          }
                          else {
                            uVar18 = uVar7 | uVar19;
                            if (uVar4 != 7) {
                              uVar18 = uVar7 ^ uVar19;
                            }
                          }
                          iVar20 = iVar20 + 1;
                          *(undefined8 *)(puVar6 + 6) = *(undefined8 *)(puVar11 + 6);
                          *(ulong *)(piVar8 + 4) = uVar18;
                        }
                      }
                    }
                  }
                  puVar6 = puVar6 + 0x22;
                } while (puVar6 != puVar13);
              }
              plVar12 = plVar12 + 10;
            } while (plVar14 + (ulong)uVar2 * 10 != plVar12);
            iVar21 = iVar21 + iVar20;
            uVar2 = *(uint *)(param_1 + 2);
            if (*(uint *)(param_1 + 1) != 0) {
              iVar20 = 0;
              plVar12 = plVar14 + (ulong)*(uint *)(param_1 + 1) * 10;
              do {
                if (*(uint *)(plVar14 + 1) != 0) {
                  piVar8 = (int *)*plVar14;
                  piVar17 = piVar8 + (ulong)*(uint *)(plVar14 + 1) * 0x22;
                  do {
                    if (((*piVar8 == 3) && (1 < (uint)piVar8[0x12])) &&
                       (((uint)piVar8[10] < uVar2 &&
                        (((piVar9 = *(int **)((long)__ptr + (ulong)(uint)piVar8[10] * 0x10),
                          piVar9 != (int *)0x0 && (*piVar9 == 1)) &&
                         (lVar22 = *(long *)(piVar9 + 4), lVar22 < 0)))))) {
                      *piVar8 = 2;
                      iVar20 = iVar20 + 1;
                      *(long *)(piVar9 + 4) = -lVar22;
                    }
                    piVar8 = piVar8 + 0x22;
                  } while (piVar17 != piVar8);
                }
                plVar14 = plVar14 + 10;
              } while (plVar12 != plVar14);
              iVar21 = iVar21 + iVar20;
            }
          }
          free(__ptr);
          return iVar21;
        }
      } while( true );
    }
  }
  return 0;
}

