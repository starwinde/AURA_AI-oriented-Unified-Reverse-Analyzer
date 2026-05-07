
undefined8 pm_wrap_const_fold(long *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  ulong uVar5;
  int *piVar6;
  ulong uVar7;
  uint *puVar8;
  undefined8 *puVar9;
  ulong uVar10;
  int *piVar11;
  uint *puVar12;
  undefined8 *puVar13;
  undefined8 uVar14;
  
  uVar2 = *(uint *)(param_1 + 1);
  if (uVar2 == 0) {
    return 0;
  }
  uVar14 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar13 = puVar1;
  while (*(uint *)(puVar13 + 1) == 0) {
LAB_0014cc34:
    puVar13 = puVar13 + 10;
    if (puVar1 + (ulong)uVar2 * 10 == puVar13) {
      return uVar14;
    }
  }
  puVar8 = (uint *)*puVar13;
  puVar12 = puVar8 + (ulong)*(uint *)(puVar13 + 1) * 0x24;
LAB_0014cb40:
  if ((puVar8[0x12] == 2) && (uVar3 = *puVar8, uVar3 - 2 < 9)) {
    if (*(uint *)(param_1 + 1) != 0) {
      puVar9 = puVar1;
      do {
        if (*(uint *)(puVar9 + 1) != 0) {
          piVar6 = (int *)*puVar9;
          piVar4 = piVar6 + (ulong)*(uint *)(puVar9 + 1) * 0x24;
          do {
            if ((*piVar6 == 1) && (puVar8[6] == piVar6[2])) {
              puVar9 = puVar1;
              goto LAB_0014cbb0;
            }
            piVar6 = piVar6 + 0x24;
          } while (piVar4 != piVar6);
        }
        puVar9 = puVar9 + 10;
      } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 10 != puVar9);
    }
  }
  goto LAB_0014cc28;
LAB_0014cbb0:
  do {
    if (*(uint *)(puVar9 + 1) != 0) {
      piVar4 = (int *)*puVar9;
      piVar11 = piVar4 + (ulong)*(uint *)(puVar9 + 1) * 0x24;
      do {
        if ((*piVar4 == 1) && (puVar8[10] == piVar4[2])) {
          uVar10 = *(ulong *)(piVar4 + 4);
          uVar7 = *(ulong *)(piVar6 + 4);
          if (uVar3 == 7) {
            uVar5 = uVar7 | uVar10;
          }
          else if (uVar3 < 8) {
            if (uVar3 == 4) {
              uVar5 = uVar7 * uVar10;
            }
            else if (uVar3 < 5) {
              if (uVar3 != 2) {
                uVar10 = -uVar10;
              }
              uVar5 = uVar7 + uVar10;
            }
            else {
              uVar5 = uVar7 & uVar10;
              if (uVar3 != 6) goto LAB_0014cc28;
            }
          }
          else {
            uVar5 = uVar7 << (uVar10 & 0x3f);
            if (uVar3 != 9) {
              uVar5 = uVar7 >> (uVar10 & 0x3f);
              if (uVar3 != 10) {
                uVar5 = uVar7 ^ uVar10;
              }
            }
          }
          uVar14 = 1;
          *puVar8 = 1;
          *(ulong *)(puVar8 + 4) = uVar5;
          puVar8[0x12] = 0;
          goto LAB_0014cc28;
        }
        piVar4 = piVar4 + 0x24;
      } while (piVar11 != piVar4);
    }
    puVar9 = puVar9 + 10;
  } while (puVar1 + (ulong)*(uint *)(param_1 + 1) * 10 != puVar9);
LAB_0014cc28:
  puVar8 = puVar8 + 0x24;
  if (puVar12 == puVar8) goto LAB_0014cc34;
  goto LAB_0014cb40;
}

