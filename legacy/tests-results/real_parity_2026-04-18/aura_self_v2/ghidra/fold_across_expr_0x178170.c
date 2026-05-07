
int fold_across_expr(long *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined8 *puVar10;
  int *piVar11;
  int *piVar12;
  int *piVar13;
  undefined8 *puVar14;
  uint uVar15;
  
  uVar2 = *(uint *)(param_1 + 1);
  if (uVar2 == 0) {
    return 0;
  }
  iVar5 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar14 = puVar1;
  while (*(uint *)(puVar14 + 1) == 0) {
LAB_00178324:
    puVar14 = puVar14 + 9;
    if (puVar14 == puVar1 + (ulong)uVar2 * 9) {
      return iVar5;
    }
  }
  piVar9 = (int *)*puVar14;
  piVar12 = piVar9 + (ulong)*(uint *)(puVar14 + 1) * 0x22;
LAB_001781a8:
  do {
    if ((((piVar9[0x12] != 2) || (1 < *piVar9 - 2U)) || (iVar3 = piVar9[10], iVar3 == -1)) ||
       (uVar4 = *(uint *)(param_1 + 1), uVar4 == 0)) goto joined_r0x00178364;
    puVar10 = puVar1;
    do {
      if (*(uint *)(puVar10 + 1) != 0) {
        piVar6 = (int *)*puVar10;
        piVar7 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
        do {
          if ((*piVar6 == 1) && (iVar3 == piVar6[2])) {
            puVar10 = puVar1;
            if (piVar9[6] == -1) goto joined_r0x00178364;
            goto LAB_00178228;
          }
          piVar6 = piVar6 + 0x22;
        } while (piVar6 != piVar7);
      }
      puVar10 = puVar10 + 9;
    } while (puVar10 != puVar1 + (ulong)uVar4 * 9);
    piVar9 = piVar9 + 0x22;
  } while (piVar9 != piVar12);
  goto LAB_00178324;
  while (puVar10 = puVar10 + 9, puVar10 != puVar1 + (ulong)uVar4 * 9) {
LAB_00178228:
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar7 = (int *)*puVar10;
      piVar8 = piVar7 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if (piVar9[6] == piVar7[2]) {
          if (((piVar7[0x12] != 2) || (*piVar9 != *piVar7)) || (piVar7[10] == -1))
          goto joined_r0x00178364;
          uVar15 = 0;
          puVar10 = puVar1;
          goto LAB_00178280;
        }
        piVar7 = piVar7 + 0x22;
      } while (piVar7 != piVar8);
    }
  }
  goto joined_r0x00178364;
  while( true ) {
    uVar15 = uVar15 + 1;
    puVar10 = puVar10 + 9;
    if (uVar4 <= uVar15) break;
LAB_00178280:
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar8 = (int *)*puVar10;
      piVar11 = piVar8 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if ((*piVar8 == 1) && (piVar7[10] == piVar8[2])) {
          uVar15 = 0;
          puVar10 = puVar1;
          goto LAB_001782c0;
        }
        piVar8 = piVar8 + 0x22;
      } while (piVar11 != piVar8);
    }
  }
  goto joined_r0x00178364;
LAB_001782c0:
  do {
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar11 = (int *)*puVar10;
      piVar13 = piVar11 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if (iVar3 == piVar11[2]) {
          if (*piVar11 == 1) {
            iVar5 = iVar5 + 1;
            iVar3 = piVar7[6];
            *(long *)(piVar11 + 4) = *(long *)(piVar6 + 4) + *(long *)(piVar8 + 4);
            piVar9[6] = iVar3;
          }
          goto joined_r0x00178364;
        }
        piVar11 = piVar11 + 0x22;
      } while (piVar13 != piVar11);
    }
    uVar15 = uVar15 + 1;
    puVar10 = puVar10 + 9;
  } while (uVar15 < uVar4);
joined_r0x00178364:
  piVar9 = piVar9 + 0x22;
  if (piVar9 == piVar12) goto LAB_00178324;
  goto LAB_001781a8;
}

