
int eliminate_double_negation(long *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined8 *puVar10;
  int *piVar11;
  undefined8 *puVar12;
  uint uVar13;
  
  uVar2 = *(uint *)(param_1 + 1);
  if (uVar2 == 0) {
    return 0;
  }
  iVar5 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar12 = puVar1;
  while (*(uint *)(puVar12 + 1) == 0) {
LAB_00179f54:
    puVar12 = puVar12 + 10;
    if (puVar12 == puVar1 + (ulong)uVar2 * 10) {
      return iVar5;
    }
  }
  piVar8 = (int *)*puVar12;
  piVar11 = piVar8 + (ulong)*(uint *)(puVar12 + 1) * 0x22;
LAB_00179ec8:
  if (piVar8[0x12] == 2) {
    if (*piVar8 == 3) {
      if ((piVar8[6] != -1) && (uVar3 = *(uint *)(param_1 + 1), uVar3 != 0)) {
        puVar10 = puVar1;
        do {
          if (*(uint *)(puVar10 + 1) != 0) {
            piVar6 = (int *)*puVar10;
            piVar7 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
            do {
              if ((*piVar6 == 1) && (piVar8[6] == piVar6[2])) {
                if ((*(long *)(piVar6 + 4) != 0) || (puVar10 = puVar1, piVar8[10] == -1))
                goto LAB_00179f48;
                goto LAB_00179fe0;
              }
              piVar6 = piVar6 + 0x22;
            } while (piVar6 != piVar7);
          }
          puVar10 = puVar10 + 10;
        } while (puVar10 != puVar1 + (ulong)uVar3 * 10);
      }
    }
    else if (((*piVar8 == 8) && (piVar8[10] != -1)) && (uVar3 = *(uint *)(param_1 + 1), uVar3 != 0))
    {
      puVar10 = puVar1;
      do {
        if (*(uint *)(puVar10 + 1) != 0) {
          piVar6 = (int *)*puVar10;
          piVar7 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
          do {
            if ((*piVar6 == 1) && (piVar8[10] == piVar6[2])) {
              if ((*(long *)(piVar6 + 4) != -1) || (puVar10 = puVar1, piVar8[6] == -1))
              goto LAB_00179f48;
              goto LAB_0017a0c4;
            }
            piVar6 = piVar6 + 0x22;
          } while (piVar7 != piVar6);
        }
        puVar10 = puVar10 + 10;
      } while (puVar1 + (ulong)uVar3 * 10 != puVar10);
    }
  }
  goto LAB_00179f48;
  while (puVar10 = puVar10 + 10, puVar10 != puVar1 + (ulong)uVar3 * 10) {
LAB_00179fe0:
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar6 = (int *)*puVar10;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if (piVar8[10] == piVar6[2]) {
          if (((*piVar6 != 3) || (piVar6[0x12] != 2)) || (piVar6[6] == -1)) goto LAB_00179f48;
          uVar13 = 0;
          puVar10 = puVar1;
          goto LAB_0017a03c;
        }
        piVar6 = piVar6 + 0x22;
      } while (piVar6 != piVar7);
    }
  }
  goto LAB_00179f48;
LAB_0017a03c:
  do {
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar7 = (int *)*puVar10;
      piVar9 = piVar7 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if ((*piVar7 == 1) && (piVar6[6] == piVar7[2])) {
          if (*(long *)(piVar7 + 4) == 0) {
            iVar4 = piVar6[10];
            iVar5 = iVar5 + 1;
            *piVar8 = 0;
            piVar8[6] = iVar4;
            piVar8[0x12] = 1;
          }
          goto LAB_00179f48;
        }
        piVar7 = piVar7 + 0x22;
      } while (piVar7 != piVar9);
    }
    uVar13 = uVar13 + 1;
    puVar10 = puVar10 + 10;
  } while (uVar13 < uVar3);
  goto LAB_00179f48;
  while (puVar10 = puVar10 + 10, puVar1 + (ulong)uVar3 * 10 != puVar10) {
LAB_0017a0c4:
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar6 = (int *)*puVar10;
      piVar7 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if (piVar8[6] == piVar6[2]) {
          if (((*piVar6 != 8) || (piVar6[0x12] != 2)) || (piVar6[10] == -1)) goto LAB_00179f48;
          uVar13 = 0;
          puVar10 = puVar1;
          goto LAB_0017a120;
        }
        piVar6 = piVar6 + 0x22;
      } while (piVar7 != piVar6);
    }
  }
  goto LAB_00179f48;
LAB_0017a120:
  do {
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar7 = (int *)*puVar10;
      piVar9 = piVar7 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
      do {
        if ((*piVar7 == 1) && (piVar6[10] == piVar7[2])) {
          if (*(long *)(piVar7 + 4) == -1) {
            iVar4 = piVar6[6];
            iVar5 = iVar5 + 1;
            *piVar8 = 0;
            piVar8[6] = iVar4;
            piVar8[0x12] = 1;
          }
          goto LAB_00179f48;
        }
        piVar7 = piVar7 + 0x22;
      } while (piVar9 != piVar7);
    }
    uVar13 = uVar13 + 1;
    puVar10 = puVar10 + 10;
  } while (uVar13 < uVar3);
LAB_00179f48:
  piVar8 = piVar8 + 0x22;
  if (piVar8 == piVar11) goto LAB_00179f54;
  goto LAB_00179ec8;
}

