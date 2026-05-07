
undefined8
FUN_001573c4(long param_1,uint param_2,int param_3,int *param_4,undefined8 *param_5,
            undefined4 *param_6,int *param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  long lVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined8 uVar8;
  int *piVar9;
  undefined8 *puVar10;
  int *piVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  int *piVar14;
  int iVar15;
  int iVar16;
  undefined8 *puVar17;
  
  if (param_2 == 0) {
    return 0;
  }
  puVar12 = (undefined8 *)(param_1 + 8);
  puVar13 = puVar12 + (ulong)param_2 * 10;
  puVar10 = puVar12;
  do {
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar7 = (int *)*puVar10;
      piVar11 = piVar7 + (ulong)*(uint *)(puVar10 + 1) * 0x24;
      do {
        if (piVar7[2] == param_3) {
          if (*piVar7 != 2) {
            return 0;
          }
          if (piVar7[0x12] != 2) {
            return 0;
          }
          iVar16 = piVar7[6];
          iVar1 = piVar7[10];
          puVar10 = puVar12;
          goto LAB_00157450;
        }
        piVar7 = piVar7 + 0x24;
      } while (piVar7 != piVar11);
    }
    puVar10 = puVar10 + 10;
    if (puVar10 == puVar13) {
      return 0;
    }
  } while( true );
LAB_00157450:
  do {
    puVar17 = puVar12;
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar11 = (int *)*puVar10;
      do {
        piVar14 = piVar11 + 0x24;
        if (iVar16 == piVar11[2]) goto LAB_00157488;
        piVar11 = piVar14;
      } while (piVar14 != (int *)*puVar10 + (ulong)*(uint *)(puVar10 + 1) * 0x24);
    }
    puVar10 = puVar10 + 10;
  } while (puVar10 != puVar13);
  piVar11 = (int *)0x0;
LAB_00157488:
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      piVar14 = (int *)*puVar17;
      do {
        piVar4 = piVar14 + 0x24;
        if (iVar1 == piVar14[2]) {
          iVar15 = *piVar14;
          if (iVar15 == 4) {
            if (piVar14[0x12] != 2) goto LAB_00157568;
            iVar15 = piVar14[6];
            puVar10 = puVar12;
            goto LAB_0015763c;
          }
          if (piVar11 != (int *)0x0) {
            iVar3 = *piVar11;
            if (iVar3 != 4) {
              if (iVar15 == 1) goto LAB_00157618;
              goto LAB_001574dc;
            }
            if (piVar11[0x12] == 2) goto LAB_00157584;
          }
          if (iVar15 == 1) goto LAB_00157618;
          goto LAB_001574e4;
        }
        piVar14 = piVar4;
      } while (piVar4 != (int *)*puVar17 + (ulong)*(uint *)(puVar17 + 1) * 0x24);
    }
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar13);
  if (piVar11 == (int *)0x0) goto LAB_001574e4;
  iVar3 = *piVar11;
  if (iVar3 == 4) {
    iVar15 = piVar11[0x12];
    piVar14 = (int *)0x0;
joined_r0x00157580:
    if (iVar15 == 2) {
LAB_00157584:
      iVar15 = piVar11[10];
      puVar10 = puVar12;
      do {
        if (*(uint *)(puVar10 + 1) != 0) {
          piVar4 = (int *)*puVar10;
          piVar9 = piVar4 + (ulong)*(uint *)(puVar10 + 1) * 0x24;
          while (iVar15 != piVar4[2]) {
            piVar4 = piVar4 + 0x24;
            if (piVar9 == piVar4) goto LAB_00157770;
          }
          if ((*piVar4 != 1) ||
             (lVar5 = *(long *)(piVar4 + 4), iVar3 = iVar1, iVar2 = piVar11[6], lVar5 < 1)) break;
LAB_001576c0:
          iVar15 = iVar2;
          iVar16 = iVar3;
          uVar6 = (undefined4)lVar5;
          goto LAB_00157504;
        }
LAB_00157770:
        puVar10 = puVar10 + 10;
      } while (puVar10 != puVar13);
      do {
        if (*(uint *)(puVar12 + 1) != 0) {
          piVar4 = (int *)*puVar12;
          piVar9 = piVar4 + (ulong)*(uint *)(puVar12 + 1) * 0x24;
          do {
            if (piVar11[6] == piVar4[2]) {
              if ((*piVar4 != 1) || (*(long *)(piVar4 + 4) < 1)) goto LAB_00157608;
              uVar6 = (undefined4)*(long *)(piVar4 + 4);
              iVar16 = iVar1;
              goto LAB_00157504;
            }
            piVar4 = piVar4 + 0x24;
          } while (piVar9 != piVar4);
        }
        puVar12 = puVar12 + 10;
      } while (puVar12 != puVar13);
LAB_00157608:
      if ((piVar14 == (int *)0x0) || (*piVar14 != 1)) goto LAB_001574e4;
LAB_00157618:
      uVar8 = *(undefined8 *)(piVar14 + 4);
      *param_4 = iVar16;
      goto LAB_00157620;
    }
    goto LAB_001574e4;
  }
  goto LAB_001574dc;
LAB_0015763c:
  do {
    puVar17 = puVar12;
    if (*(uint *)(puVar10 + 1) != 0) {
      piVar4 = (int *)*puVar10;
      piVar9 = piVar4 + (ulong)*(uint *)(puVar10 + 1) * 0x24;
      do {
        if (piVar14[10] == piVar4[2]) {
          if ((*piVar4 != 1) || (*(long *)(piVar4 + 4) < 1)) goto LAB_0015767c;
          uVar6 = (undefined4)*(long *)(piVar4 + 4);
          goto LAB_00157504;
        }
        piVar4 = piVar4 + 0x24;
      } while (piVar4 != piVar9);
    }
    puVar10 = puVar10 + 10;
  } while (puVar10 != puVar13);
LAB_0015767c:
  do {
    if (*(uint *)(puVar17 + 1) != 0) {
      piVar4 = (int *)*puVar17;
      piVar9 = piVar4 + (ulong)*(uint *)(puVar17 + 1) * 0x24;
      do {
        if (iVar15 == piVar4[2]) {
          if ((*piVar4 != 1) ||
             (lVar5 = *(long *)(piVar4 + 4), iVar3 = iVar16, iVar2 = piVar14[10], lVar5 < 1))
          goto LAB_00157568;
          goto LAB_001576c0;
        }
        piVar4 = piVar4 + 0x24;
      } while (piVar9 != piVar4);
    }
    puVar17 = puVar17 + 10;
  } while (puVar17 != puVar13);
LAB_00157568:
  if (piVar11 == (int *)0x0) goto LAB_001574e4;
  iVar3 = *piVar11;
  if (iVar3 == 4) {
    iVar15 = piVar11[0x12];
    goto joined_r0x00157580;
  }
LAB_001574dc:
  if (iVar3 == 1) {
    uVar8 = *(undefined8 *)(piVar11 + 4);
    *param_4 = iVar1;
LAB_00157620:
    *param_5 = uVar8;
    return 1;
  }
LAB_001574e4:
  if ((piVar7[7] != 5) || (piVar7[0xb] == 5)) {
    return 0;
  }
  uVar6 = 1;
  iVar15 = iVar1;
LAB_00157504:
  *param_4 = iVar16;
  *param_6 = uVar6;
  *param_7 = iVar15;
  return 2;
}

