
int ir_cond_simplify_part_0(long *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  int *piVar3;
  long lVar4;
  ulong uVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  undefined8 *puVar9;
  uint *puVar10;
  long lVar11;
  undefined8 *puVar12;
  uint uVar13;
  int iVar14;
  uint *puVar15;
  undefined8 *puVar16;
  int iVar17;
  int iVar18;
  
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  iVar14 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar12 = puVar1 + (ulong)*(uint *)(param_1 + 1) * 9;
  puVar16 = puVar1;
  do {
    if (*(uint *)(puVar16 + 1) != 0) {
      piVar6 = (int *)*puVar16;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar16 + 1) * 0x22;
      do {
        if ((*piVar6 == 0xc) && (piVar6[0x12] == 2)) {
          iVar17 = piVar6[10];
          if (iVar17 == -1) {
            iVar18 = piVar6[6];
            if ((iVar18 != -1) && (uVar13 = *(uint *)(param_1 + 1), uVar13 != 0)) {
LAB_00178d30:
              puVar9 = puVar1;
              do {
                if (*(uint *)(puVar9 + 1) != 0) {
                  piVar3 = (int *)*puVar9;
                  piVar8 = piVar3 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
                  do {
                    if ((*piVar3 == 1) && (piVar3[2] == iVar18)) {
                      if (*(long *)(piVar3 + 4) == 0) {
                        iVar14 = iVar14 + 1;
                        *piVar6 = 0;
                        piVar6[6] = iVar17;
                        piVar6[0x12] = 1;
                      }
                      goto LAB_00178a78;
                    }
                    piVar3 = piVar3 + 0x22;
                  } while (piVar3 != piVar8);
                }
                puVar9 = puVar9 + 9;
              } while (puVar9 != puVar1 + (ulong)uVar13 * 9);
            }
          }
          else {
            uVar13 = *(uint *)(param_1 + 1);
            if (uVar13 != 0) {
              puVar9 = puVar1;
              do {
                if (*(uint *)(puVar9 + 1) != 0) {
                  piVar3 = (int *)*puVar9;
                  piVar8 = piVar3 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
                  do {
                    if ((*piVar3 == 1) && (iVar17 == piVar3[2])) {
                      if (*(long *)(piVar3 + 4) != 0) goto LAB_00178d24;
                      iVar14 = iVar14 + 1;
                      *piVar6 = 0;
                      piVar6[0x12] = 1;
                      goto LAB_00178a78;
                    }
                    piVar3 = piVar3 + 0x22;
                  } while (piVar3 != piVar8);
                }
                puVar9 = puVar9 + 9;
              } while (puVar9 != puVar1 + (ulong)uVar13 * 9);
LAB_00178d24:
              iVar18 = piVar6[6];
              if (iVar18 != -1) goto LAB_00178d30;
            }
          }
        }
LAB_00178a78:
        piVar6 = piVar6 + 0x22;
      } while (piVar6 != piVar7);
    }
    puVar16 = puVar16 + 9;
  } while (puVar16 != puVar12);
  iVar17 = 0;
  puVar16 = puVar1;
  do {
    if (*(uint *)(puVar16 + 1) != 0) {
      piVar6 = (int *)*puVar16;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar16 + 1) * 0x22;
LAB_00178ac0:
      if ((((*piVar6 == 8) && (piVar6[0x12] == 2)) && (piVar6[10] != -1)) &&
         (*(uint *)(param_1 + 1) != 0)) {
        puVar9 = puVar1;
        do {
          if (*(uint *)(puVar9 + 1) != 0) {
            piVar3 = (int *)*puVar9;
            piVar8 = piVar3 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
            do {
              if ((*piVar3 == 1) && (piVar6[10] == piVar3[2])) {
                if ((*(long *)(piVar3 + 4) != 1) || (puVar9 = puVar1, piVar6[6] == -1))
                goto LAB_00178bb0;
                goto LAB_00178b48;
              }
              piVar3 = piVar3 + 0x22;
            } while (piVar8 != piVar3);
          }
          puVar9 = puVar9 + 9;
        } while (puVar9 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 9);
      }
      goto LAB_00178bb0;
    }
LAB_00178bbc:
    puVar16 = puVar16 + 9;
  } while (puVar16 != puVar12);
  iVar18 = 0;
  puVar16 = puVar1;
  while (*(uint *)(puVar16 + 1) == 0) {
LAB_00178ce4:
    puVar16 = puVar16 + 9;
    if (puVar16 == puVar12) {
      return iVar14 + iVar17 + iVar18;
    }
  }
  puVar10 = (uint *)*puVar16;
  puVar15 = puVar10 + (ulong)*(uint *)(puVar16 + 1) * 0x22;
LAB_00178bf0:
  if (((puVar10[0x12] == 2) && (puVar10[6] != 0xffffffff)) && (*(uint *)(param_1 + 1) != 0)) {
    puVar9 = puVar1;
    do {
      if (*(uint *)(puVar9 + 1) != 0) {
        piVar6 = (int *)*puVar9;
        piVar7 = piVar6 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
        do {
          if ((*piVar6 == 1) && (puVar10[6] == piVar6[2])) {
            puVar9 = puVar1;
            if (puVar10[10] == 0xffffffff) goto LAB_00178cd8;
            goto LAB_00178c60;
          }
          piVar6 = piVar6 + 0x22;
        } while (piVar7 != piVar6);
      }
      puVar9 = puVar9 + 9;
    } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 9 != puVar9);
  }
  goto LAB_00178cd8;
LAB_00178b48:
  do {
    if (*(uint *)(puVar9 + 1) != 0) {
      piVar3 = (int *)*puVar9;
      piVar8 = piVar3 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
      do {
        if (piVar6[6] == piVar3[2]) {
          uVar13 = *piVar3 - 0xb;
          if ((uVar13 < 10) && (*piVar3 != *(int *)(&CSWTCH_14 + (ulong)uVar13 * 4))) {
            *piVar6 = *(int *)(&CSWTCH_14 + (ulong)uVar13 * 4);
            iVar17 = iVar17 + 1;
            uVar2 = *(undefined8 *)(piVar3 + 8);
            *(undefined8 *)(piVar6 + 6) = *(undefined8 *)(piVar3 + 6);
            *(undefined8 *)(piVar6 + 8) = uVar2;
            uVar2 = *(undefined8 *)(piVar3 + 0xc);
            *(undefined8 *)(piVar6 + 10) = *(undefined8 *)(piVar3 + 10);
            *(undefined8 *)(piVar6 + 0xc) = uVar2;
            piVar6[0x12] = 2;
          }
          goto LAB_00178bb0;
        }
        piVar3 = piVar3 + 0x22;
      } while (piVar8 != piVar3);
    }
    puVar9 = puVar9 + 9;
  } while (puVar9 != puVar1 + (ulong)*(uint *)(param_1 + 1) * 9);
LAB_00178bb0:
  piVar6 = piVar6 + 0x22;
  if (piVar6 == piVar7) goto LAB_00178bbc;
  goto LAB_00178ac0;
LAB_00178c60:
  do {
    if (*(uint *)(puVar9 + 1) != 0) {
      piVar7 = (int *)*puVar9;
      piVar3 = piVar7 + (ulong)*(uint *)(puVar9 + 1) * 0x22;
      do {
        if ((*piVar7 == 1) && (puVar10[10] == piVar7[2])) {
          uVar13 = *puVar10;
          lVar11 = *(long *)(piVar6 + 4);
          lVar4 = *(long *)(piVar7 + 4);
          if (uVar13 == 0xd) {
            uVar5 = (ulong)(lVar11 < lVar4);
          }
          else if (uVar13 < 0xe) {
            if (uVar13 == 0xb) {
              uVar5 = (ulong)(lVar11 == lVar4);
            }
            else {
              uVar5 = (ulong)(lVar11 != lVar4);
              if (uVar13 != 0xc) goto LAB_00178cd8;
            }
          }
          else {
            uVar5 = (ulong)(lVar11 <= lVar4);
            if (uVar13 != 0xe) goto LAB_00178cd8;
          }
          iVar18 = iVar18 + 1;
          *puVar10 = 1;
          *(ulong *)(puVar10 + 4) = uVar5;
          puVar10[0x12] = 0;
          goto LAB_00178cd8;
        }
        piVar7 = piVar7 + 0x22;
      } while (piVar3 != piVar7);
    }
    puVar9 = puVar9 + 9;
  } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 9 != puVar9);
LAB_00178cd8:
  puVar10 = puVar10 + 0x22;
  if (puVar15 == puVar10) goto LAB_00178ce4;
  goto LAB_00178bf0;
}

