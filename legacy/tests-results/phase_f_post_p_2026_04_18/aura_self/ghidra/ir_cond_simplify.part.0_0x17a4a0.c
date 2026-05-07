
int ir_cond_simplify_part_0(long *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  int *piVar3;
  ulong uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  undefined8 *puVar8;
  uint *puVar9;
  int *piVar10;
  ulong uVar11;
  undefined8 *puVar12;
  uint uVar13;
  undefined8 *puVar14;
  int iVar15;
  uint *puVar16;
  undefined8 *puVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  iVar15 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar12 = puVar1 + (ulong)*(uint *)(param_1 + 1) * 10;
  puVar17 = puVar1;
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      piVar6 = (int *)*puVar17;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
      do {
        if ((*piVar6 == 0xc) && (piVar6[0x12] == 2)) {
          iVar18 = piVar6[10];
          if (iVar18 == -1) {
            iVar19 = piVar6[6];
            if ((iVar19 != -1) && (uVar13 = *(uint *)(param_1 + 1), uVar13 != 0)) {
LAB_0017ab64:
              puVar8 = puVar1;
              do {
                if (*(uint *)(puVar8 + 1) != 0) {
                  piVar3 = (int *)*puVar8;
                  piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
                  do {
                    if ((*piVar3 == 1) && (piVar3[2] == iVar19)) {
                      if (*(long *)(piVar3 + 4) == 0) {
                        iVar15 = iVar15 + 1;
                        *piVar6 = 0;
                        piVar6[6] = iVar18;
                        piVar6[0x12] = 1;
                      }
                      goto LAB_0017a558;
                    }
                    piVar3 = piVar3 + 0x22;
                  } while (piVar3 != piVar5);
                }
                puVar8 = puVar8 + 10;
              } while (puVar8 != puVar1 + (ulong)uVar13 * 10);
            }
          }
          else {
            uVar13 = *(uint *)(param_1 + 1);
            if (uVar13 != 0) {
              puVar8 = puVar1;
              do {
                if (*(uint *)(puVar8 + 1) != 0) {
                  piVar3 = (int *)*puVar8;
                  piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
                  do {
                    if ((*piVar3 == 1) && (iVar18 == piVar3[2])) {
                      if (*(long *)(piVar3 + 4) != 0) goto LAB_0017ab58;
                      iVar15 = iVar15 + 1;
                      *piVar6 = 0;
                      piVar6[0x12] = 1;
                      goto LAB_0017a558;
                    }
                    piVar3 = piVar3 + 0x22;
                  } while (piVar3 != piVar5);
                }
                puVar8 = puVar8 + 10;
              } while (puVar8 != puVar1 + (ulong)uVar13 * 10);
LAB_0017ab58:
              iVar19 = piVar6[6];
              if (iVar19 != -1) goto LAB_0017ab64;
            }
          }
        }
LAB_0017a558:
        piVar6 = piVar6 + 0x22;
      } while (piVar6 != piVar7);
    }
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar12);
  iVar18 = 0;
  puVar17 = puVar1;
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      piVar6 = (int *)*puVar17;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
LAB_0017a5a0:
      if ((((*piVar6 == 8) && (piVar6[0x12] == 2)) && (piVar6[10] != -1)) &&
         (*(uint *)(param_1 + 1) != 0)) {
        puVar8 = puVar1;
        do {
          if (*(uint *)(puVar8 + 1) != 0) {
            piVar3 = (int *)*puVar8;
            piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
            do {
              if ((*piVar3 == 1) && (piVar6[10] == piVar3[2])) {
                if ((*(long *)(piVar3 + 4) != 1) || (puVar8 = puVar1, piVar6[6] == -1))
                goto LAB_0017a690;
                goto LAB_0017a628;
              }
              piVar3 = piVar3 + 0x22;
            } while (piVar3 != piVar5);
          }
          puVar8 = puVar8 + 10;
        } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
      }
      goto LAB_0017a690;
    }
LAB_0017a69c:
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar12);
  iVar19 = 0;
  puVar17 = puVar1;
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      puVar9 = (uint *)*puVar17;
      puVar16 = puVar9 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
LAB_0017a6d0:
      if (((puVar9[0x12] == 2) && (puVar9[6] != 0xffffffff)) && (*(uint *)(param_1 + 1) != 0)) {
        puVar8 = puVar1;
        do {
          if (*(uint *)(puVar8 + 1) != 0) {
            piVar6 = (int *)*puVar8;
            piVar7 = piVar6 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
            do {
              if ((*piVar6 == 1) && (puVar9[6] == piVar6[2])) {
                puVar8 = puVar1;
                if (puVar9[10] != 0xffffffff) goto LAB_0017a740;
                goto LAB_0017a7c8;
              }
              piVar6 = piVar6 + 0x22;
            } while (piVar7 != piVar6);
          }
          puVar8 = puVar8 + 10;
        } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 10 != puVar8);
      }
      goto LAB_0017a7c8;
    }
LAB_0017a7d4:
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar12);
  iVar19 = iVar18 + iVar15 + iVar19;
  iVar15 = 0;
  puVar17 = puVar1;
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      piVar6 = (int *)*puVar17;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
      do {
        iVar18 = *piVar6;
        if ((((iVar18 - 0xbU < 2) && (piVar6[0x12] == 2)) && (piVar6[10] != -1)) &&
           (*(uint *)(param_1 + 1) != 0)) {
          puVar14 = puVar1 + (ulong)*(uint *)(param_1 + 1) * 10;
          puVar8 = puVar1;
          do {
            if (*(uint *)(puVar8 + 1) != 0) {
              piVar3 = (int *)*puVar8;
              piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
              do {
                if ((*piVar3 == 1) && (piVar6[10] == piVar3[2])) goto LAB_0017a888;
                piVar3 = piVar3 + 0x22;
              } while (piVar3 != piVar5);
            }
            puVar8 = puVar8 + 10;
          } while (puVar8 != puVar14);
        }
        piVar6 = piVar6 + 0x22;
      } while (piVar6 != piVar7);
    }
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar12);
  iVar15 = 0;
  puVar17 = puVar1;
  while (*(uint *)(puVar17 + 1) == 0) {
LAB_0017ab0c:
    puVar17 = puVar17 + 10;
    if (puVar17 == puVar12) {
      return iVar19 + iVar15;
    }
  }
  piVar6 = (int *)*puVar17;
  piVar7 = piVar6 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
LAB_0017aa40:
  iVar18 = *piVar6;
  if ((((iVar18 == 0x14 || iVar18 == 0xf) && (piVar6[0x12] == 2)) && (piVar6[10] != -1)) &&
     (*(uint *)(param_1 + 1) != 0)) {
    puVar8 = puVar1;
    do {
      if (*(uint *)(puVar8 + 1) != 0) {
        piVar3 = (int *)*puVar8;
        piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
        do {
          if ((*piVar3 == 1) && (piVar6[10] == piVar3[2])) {
            if (*(long *)(piVar3 + 4) != 0) goto joined_r0x0017ab34;
            puVar8 = puVar1;
            if (piVar6[6] == -1) goto LAB_0017abec;
            goto LAB_0017aac8;
          }
          piVar3 = piVar3 + 0x22;
        } while (piVar3 != piVar5);
      }
      puVar8 = puVar8 + 10;
    } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
  }
  goto joined_r0x0017ab34;
LAB_0017a628:
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar3 = (int *)*puVar8;
      piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
      do {
        if (piVar6[6] == piVar3[2]) {
          uVar13 = *piVar3 - 0xb;
          if ((uVar13 < 10) && (*piVar3 != *(int *)(&CSWTCH_24 + (ulong)uVar13 * 4))) {
            *piVar6 = *(int *)(&CSWTCH_24 + (ulong)uVar13 * 4);
            iVar18 = iVar18 + 1;
            uVar2 = *(undefined8 *)(piVar3 + 8);
            *(undefined8 *)(piVar6 + 6) = *(undefined8 *)(piVar3 + 6);
            *(undefined8 *)(piVar6 + 8) = uVar2;
            uVar2 = *(undefined8 *)(piVar3 + 0xc);
            *(undefined8 *)(piVar6 + 10) = *(undefined8 *)(piVar3 + 10);
            *(undefined8 *)(piVar6 + 0xc) = uVar2;
            piVar6[0x12] = 2;
          }
          goto LAB_0017a690;
        }
        piVar3 = piVar3 + 0x22;
      } while (piVar3 != piVar5);
    }
    puVar8 = puVar8 + 10;
  } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
LAB_0017a690:
  piVar6 = piVar6 + 0x22;
  if (piVar6 == piVar7) goto LAB_0017a69c;
  goto LAB_0017a5a0;
LAB_0017a740:
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar7 = (int *)*puVar8;
      piVar3 = piVar7 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
      do {
        if ((*piVar7 == 1) && (puVar9[10] == piVar7[2])) {
          uVar13 = *puVar9;
          uVar11 = *(ulong *)(piVar6 + 4);
          uVar4 = *(ulong *)(piVar7 + 4);
          if (uVar13 == 0x10) {
            uVar4 = (ulong)(uVar11 <= uVar4);
          }
          else if (uVar13 < 0x11) {
            if (uVar13 == 0xd) {
              uVar4 = (ulong)((long)uVar11 < (long)uVar4);
            }
            else if (uVar13 < 0xe) {
              if (uVar13 == 0xb) {
                uVar4 = (ulong)(uVar11 == uVar4);
              }
              else {
                uVar4 = (ulong)(uVar11 != uVar4);
                if (uVar13 != 0xc) goto LAB_0017a7c8;
              }
            }
            else if (uVar13 == 0xe) {
              uVar4 = (ulong)((long)uVar11 <= (long)uVar4);
            }
            else {
              uVar4 = (ulong)(uVar11 < uVar4);
            }
          }
          else if (uVar13 == 0x13) {
            uVar4 = (ulong)(uVar4 < uVar11);
          }
          else if (uVar13 < 0x14) {
            if (uVar13 == 0x11) {
              uVar4 = (ulong)((long)uVar4 < (long)uVar11);
            }
            else {
              uVar4 = (ulong)((long)uVar4 <= (long)uVar11);
            }
          }
          else {
            uVar4 = (ulong)(uVar4 <= uVar11);
            if (uVar13 != 0x14) goto LAB_0017a7c8;
          }
          iVar19 = iVar19 + 1;
          *puVar9 = 1;
          *(ulong *)(puVar9 + 4) = uVar4;
          puVar9[0x12] = 0;
          goto LAB_0017a7c8;
        }
        piVar7 = piVar7 + 0x22;
      } while (piVar7 != piVar3);
    }
    puVar8 = puVar8 + 10;
  } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 10 != puVar8);
LAB_0017a7c8:
  puVar9 = puVar9 + 0x22;
  if (puVar16 == puVar9) goto LAB_0017a7d4;
  goto LAB_0017a6d0;
LAB_0017a888:
  iVar20 = 2;
  if ((*(ulong *)(piVar3 + 4) < 2) && (puVar8 = puVar1, piVar6[6] != -1)) {
    do {
      if (*(uint *)(puVar8 + 1) != 0) {
        piVar5 = (int *)*puVar8;
        piVar10 = piVar5 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
        do {
          if (piVar6[6] == piVar5[2]) {
            uVar13 = *piVar5 - 0xb;
            if (9 < uVar13) goto LAB_0017a920;
            if ((uint)(iVar18 == 0xb) == ((uint)*(ulong *)(piVar3 + 4) & 1)) {
              *piVar6 = 0;
              iVar20 = 1;
              piVar6[6] = piVar5[2];
            }
            else {
              if (*piVar5 == *(int *)(&CSWTCH_24 + (ulong)uVar13 * 4)) goto LAB_0017a920;
              *piVar6 = *(int *)(&CSWTCH_24 + (ulong)uVar13 * 4);
              uVar2 = *(undefined8 *)(piVar5 + 8);
              *(undefined8 *)(piVar6 + 6) = *(undefined8 *)(piVar5 + 6);
              *(undefined8 *)(piVar6 + 8) = uVar2;
              uVar2 = *(undefined8 *)(piVar5 + 0xc);
              *(undefined8 *)(piVar6 + 10) = *(undefined8 *)(piVar5 + 10);
              *(undefined8 *)(piVar6 + 0xc) = uVar2;
            }
            iVar15 = iVar15 + 1;
            piVar6[0x12] = iVar20;
            goto LAB_0017a920;
          }
          piVar5 = piVar5 + 0x22;
        } while (piVar5 != piVar10);
      }
      puVar8 = puVar8 + 10;
    } while (puVar8 != puVar14);
  }
LAB_0017a920:
  do {
    piVar6 = piVar6 + 0x22;
    puVar8 = puVar17;
    if (piVar6 == piVar7) goto LAB_0017a9c0;
    while (((iVar18 = *piVar6, iVar18 - 0xbU < 2 && (piVar6[0x12] == 2)) &&
           ((piVar6[10] != -1 && (*(uint *)(param_1 + 1) != 0))))) {
      puVar14 = puVar1 + (ulong)*(uint *)(param_1 + 1) * 10;
      puVar8 = puVar1;
      do {
        if (*(uint *)(puVar8 + 1) != 0) {
          piVar3 = (int *)*puVar8;
          piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
          do {
            while (*piVar3 == 1) {
              if (piVar6[10] == piVar3[2]) goto LAB_0017a888;
              piVar3 = piVar3 + 0x22;
              if (piVar3 == piVar5) goto LAB_0017a9a8;
            }
            piVar3 = piVar3 + 0x22;
          } while (piVar3 != piVar5);
        }
LAB_0017a9a8:
        puVar8 = puVar8 + 10;
      } while (puVar8 != puVar14);
      piVar6 = piVar6 + 0x22;
      puVar8 = puVar17;
      if (piVar6 == piVar7) {
LAB_0017a9c0:
        do {
          puVar17 = puVar8 + 10;
          if (puVar17 == puVar12) {
            iVar18 = 0;
            puVar17 = puVar1;
            goto LAB_0017ad10;
          }
          puVar9 = (uint *)(puVar8 + 0xb);
          puVar8 = puVar17;
        } while (*puVar9 == 0);
        piVar6 = (int *)*puVar17;
        piVar7 = piVar6 + (ulong)*puVar9 * 0x22;
      }
    }
  } while( true );
LAB_0017ad10:
  if (*(uint *)(puVar17 + 1) != 0) {
    piVar6 = (int *)*puVar17;
    piVar7 = piVar6 + (ulong)*(uint *)(puVar17 + 1) * 0x22;
LAB_0017ad20:
    iVar20 = *piVar6;
    if ((((iVar20 == 0x14 || iVar20 == 0xf) && (piVar6[0x12] == 2)) && (piVar6[10] != -1)) &&
       (*(uint *)(param_1 + 1) != 0)) {
      puVar8 = puVar1;
      do {
        if (*(uint *)(puVar8 + 1) != 0) {
          piVar3 = (int *)*puVar8;
          piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
          do {
            if ((*piVar3 == 1) && (piVar6[10] == piVar3[2])) {
              if (*(long *)(piVar3 + 4) != 0) goto LAB_0017ade0;
              puVar8 = puVar1;
              if (piVar6[6] != -1) goto LAB_0017ada8;
              goto LAB_0017ae20;
            }
            piVar3 = piVar3 + 0x22;
          } while (piVar3 != piVar5);
        }
        puVar8 = puVar8 + 10;
      } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
    }
    goto LAB_0017ade0;
  }
LAB_0017adec:
  puVar17 = puVar17 + 10;
  if (puVar17 == puVar12) {
    return iVar19 + iVar15 + iVar18;
  }
  goto LAB_0017ad10;
LAB_0017ada8:
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar3 = (int *)*puVar8;
      piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
      do {
        if ((*piVar3 == 1) && (piVar6[6] == piVar3[2])) goto LAB_0017ade0;
        piVar3 = piVar3 + 0x22;
      } while (piVar3 != piVar5);
    }
    puVar8 = puVar8 + 10;
  } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
LAB_0017ae20:
  iVar18 = iVar18 + 1;
  *piVar6 = 1;
  *(ulong *)(piVar6 + 4) = (ulong)(iVar20 == 0x14);
  piVar6[0x12] = 0;
LAB_0017ade0:
  piVar6 = piVar6 + 0x22;
  if (piVar6 == piVar7) goto LAB_0017adec;
  goto LAB_0017ad20;
LAB_0017aac8:
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar3 = (int *)*puVar8;
      piVar5 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
      do {
        if ((*piVar3 == 1) && (piVar6[6] == piVar3[2])) goto joined_r0x0017ab34;
        piVar3 = piVar3 + 0x22;
      } while (piVar3 != piVar5);
    }
    puVar8 = puVar8 + 10;
  } while (puVar8 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 10);
LAB_0017abec:
  *piVar6 = 1;
  *(ulong *)(piVar6 + 4) = (ulong)(iVar18 == 0x14);
  iVar15 = iVar15 + 1;
  piVar6[0x12] = 0;
joined_r0x0017ab34:
  piVar6 = piVar6 + 0x22;
  if (piVar6 == piVar7) goto LAB_0017ab0c;
  goto LAB_0017aa40;
}

