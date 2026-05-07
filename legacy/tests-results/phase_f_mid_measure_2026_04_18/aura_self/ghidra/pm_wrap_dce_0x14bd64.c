
undefined8 pm_wrap_dce(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  void *__ptr;
  int *piVar4;
  undefined8 *puVar5;
  uint *puVar6;
  uint uVar7;
  long lVar8;
  undefined8 uVar9;
  int *piVar10;
  uint uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  uint uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  
  uVar2 = *(uint *)(param_1 + 2);
  if ((0xfffffffd < uVar2 - 1) || (__ptr = calloc((ulong)uVar2,1), __ptr == (void *)0x0)) {
    return 0;
  }
  uVar11 = *(uint *)(param_1 + 1);
  if (uVar11 == 0) {
    uVar9 = 0;
  }
  else {
    lVar15 = *param_1;
    puVar5 = (undefined8 *)(lVar15 + 8);
    puVar12 = puVar5 + (ulong)uVar11 * 10;
    do {
      if (*(uint *)(puVar5 + 1) != 0) {
        piVar4 = (int *)*puVar5;
        piVar10 = piVar4 + (ulong)*(uint *)(puVar5 + 1) * 0x22;
        do {
          while( true ) {
            iVar3 = piVar4[0x12];
            if (iVar3 != 0) {
              if ((uint)piVar4[6] < uVar2) {
                *(undefined1 *)((long)__ptr + (ulong)(uint)piVar4[6]) = 1;
              }
              if (iVar3 != 1) {
                if ((uint)piVar4[10] < uVar2) {
                  *(undefined1 *)((long)__ptr + (ulong)(uint)piVar4[10]) = 1;
                }
                if ((iVar3 != 2) && ((uint)piVar4[0xe] < uVar2)) {
                  *(undefined1 *)((long)__ptr + (ulong)(uint)piVar4[0xe]) = 1;
                }
              }
            }
            if (*piVar4 == 0x1b) break;
            if ((*piVar4 - 0x16U < 5) && ((uint)piVar4[2] < uVar2)) {
              *(undefined1 *)((long)__ptr + (ulong)(uint)piVar4[2]) = 1;
            }
LAB_0014be10:
            piVar4 = piVar4 + 0x22;
            if (piVar10 == piVar4) goto LAB_0014bea8;
          }
          if (piVar4[0x18] == 0) goto LAB_0014be10;
          puVar6 = *(uint **)(piVar4 + 0x14);
          puVar1 = puVar6 + (ulong)(uint)piVar4[0x18] * 4;
          do {
            uVar16 = *puVar6;
            puVar6 = puVar6 + 4;
            if (uVar16 < uVar2) {
              *(undefined1 *)((long)__ptr + (ulong)uVar16) = 1;
            }
          } while (puVar6 != puVar1);
          piVar4 = piVar4 + 0x22;
        } while (piVar10 != piVar4);
      }
LAB_0014bea8:
      puVar5 = puVar5 + 10;
    } while (puVar5 != puVar12);
    lVar8 = 0;
    uVar9 = 0;
    uVar16 = 0;
    uVar7 = *(uint *)(lVar15 + 0x10);
    if (uVar7 == 0) goto LAB_0014bf7c;
    while( true ) {
      lVar14 = 0;
      uVar13 = 0;
      uVar11 = 0;
      do {
        piVar4 = (int *)(*(long *)(lVar15 + 8) + lVar14);
        puVar5 = (undefined8 *)(*(long *)(lVar15 + 8) + uVar13 * 0x88);
        if ((((uint)piVar4[2] < uVar2) && (*(char *)((long)__ptr + (ulong)(uint)piVar4[2]) == '\0'))
           && (5 < *piVar4 - 0x16U)) {
          free(*(void **)(piVar4 + 0x14));
          free(*(void **)(piVar4 + 0x16));
          uVar9 = 1;
          uVar7 = *(uint *)(lVar15 + 0x10);
        }
        else {
          if (uVar11 != (uint)uVar13) {
            uVar17 = *(undefined8 *)piVar4;
            uVar19 = *(undefined8 *)(piVar4 + 6);
            uVar18 = *(undefined8 *)(piVar4 + 4);
            puVar5[1] = *(undefined8 *)(piVar4 + 2);
            *puVar5 = uVar17;
            puVar5[3] = uVar19;
            puVar5[2] = uVar18;
            uVar17 = *(undefined8 *)(piVar4 + 8);
            uVar19 = *(undefined8 *)(piVar4 + 0xe);
            uVar18 = *(undefined8 *)(piVar4 + 0xc);
            puVar5[5] = *(undefined8 *)(piVar4 + 10);
            puVar5[4] = uVar17;
            puVar5[7] = uVar19;
            puVar5[6] = uVar18;
            uVar17 = *(undefined8 *)(piVar4 + 0x10);
            uVar19 = *(undefined8 *)(piVar4 + 0x16);
            uVar18 = *(undefined8 *)(piVar4 + 0x14);
            puVar5[9] = *(undefined8 *)(piVar4 + 0x12);
            puVar5[8] = uVar17;
            puVar5[0xb] = uVar19;
            puVar5[10] = uVar18;
            uVar17 = *(undefined8 *)(piVar4 + 0x18);
            uVar19 = *(undefined8 *)(piVar4 + 0x1e);
            uVar18 = *(undefined8 *)(piVar4 + 0x1c);
            puVar5[0xd] = *(undefined8 *)(piVar4 + 0x1a);
            puVar5[0xc] = uVar17;
            puVar5[0xf] = uVar19;
            puVar5[0xe] = uVar18;
            puVar5[0x10] = *(undefined8 *)(piVar4 + 0x20);
          }
          uVar13 = (ulong)((uint)uVar13 + 1);
        }
        uVar11 = uVar11 + 1;
        lVar14 = lVar14 + 0x88;
      } while (uVar11 < uVar7);
      uVar11 = *(uint *)(param_1 + 1);
      uVar16 = uVar16 + 1;
      *(int *)(lVar15 + 0x10) = (int)uVar13;
      if (uVar11 <= uVar16) break;
      while( true ) {
        lVar8 = lVar8 + 0x50;
        lVar15 = *param_1 + lVar8;
        uVar7 = *(uint *)(lVar15 + 0x10);
        if (uVar7 != 0) break;
LAB_0014bf7c:
        uVar16 = uVar16 + 1;
        *(undefined4 *)(lVar15 + 0x10) = 0;
        if (uVar11 <= uVar16) goto LAB_0014bfa0;
      }
    }
  }
LAB_0014bfa0:
  free(__ptr);
  return uVar9;
}

