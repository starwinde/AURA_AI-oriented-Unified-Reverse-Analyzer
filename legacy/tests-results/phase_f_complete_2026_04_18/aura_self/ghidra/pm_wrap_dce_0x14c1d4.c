
undefined8 pm_wrap_dce(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  void *__ptr;
  int *piVar5;
  undefined8 *puVar6;
  uint *puVar7;
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
    puVar6 = (undefined8 *)(lVar15 + 8);
    puVar12 = puVar6 + (ulong)uVar11 * 10;
    do {
      if (*(uint *)(puVar6 + 1) != 0) {
        piVar5 = (int *)*puVar6;
        piVar10 = piVar5 + (ulong)*(uint *)(puVar6 + 1) * 0x24;
        do {
          while( true ) {
            iVar3 = piVar5[0x12];
            if (iVar3 != 0) {
              if ((uint)piVar5[6] < uVar2) {
                *(undefined1 *)((long)__ptr + (ulong)(uint)piVar5[6]) = 1;
              }
              if (iVar3 != 1) {
                if ((uint)piVar5[10] < uVar2) {
                  *(undefined1 *)((long)__ptr + (ulong)(uint)piVar5[10]) = 1;
                }
                if ((iVar3 != 2) && ((uint)piVar5[0xe] < uVar2)) {
                  *(undefined1 *)((long)__ptr + (ulong)(uint)piVar5[0xe]) = 1;
                }
              }
            }
            if (*piVar5 == 0x1b) break;
            if ((*piVar5 - 0x16U < 5) && ((uint)piVar5[2] < uVar2)) {
              *(undefined1 *)((long)__ptr + (ulong)(uint)piVar5[2]) = 1;
            }
LAB_0014c280:
            piVar5 = piVar5 + 0x24;
            if (piVar10 == piVar5) goto LAB_0014c318;
          }
          if (piVar5[0x18] == 0) goto LAB_0014c280;
          puVar7 = *(uint **)(piVar5 + 0x14);
          puVar1 = puVar7 + (ulong)(uint)piVar5[0x18] * 4;
          do {
            uVar16 = *puVar7;
            puVar7 = puVar7 + 4;
            if (uVar16 < uVar2) {
              *(undefined1 *)((long)__ptr + (ulong)uVar16) = 1;
            }
          } while (puVar7 != puVar1);
          piVar5 = piVar5 + 0x24;
        } while (piVar10 != piVar5);
      }
LAB_0014c318:
      puVar6 = puVar6 + 10;
    } while (puVar6 != puVar12);
    lVar8 = 0;
    uVar9 = 0;
    uVar16 = 0;
    uVar4 = *(uint *)(lVar15 + 0x10);
    if (uVar4 == 0) goto LAB_0014c3ec;
    while( true ) {
      lVar14 = 0;
      uVar13 = 0;
      uVar11 = 0;
      do {
        piVar5 = (int *)(*(long *)(lVar15 + 8) + lVar14);
        puVar6 = (undefined8 *)(*(long *)(lVar15 + 8) + uVar13 * 0x90);
        if ((((uint)piVar5[2] < uVar2) && (*(char *)((long)__ptr + (ulong)(uint)piVar5[2]) == '\0'))
           && (5 < *piVar5 - 0x16U)) {
          free(*(void **)(piVar5 + 0x14));
          free(*(void **)(piVar5 + 0x16));
          uVar9 = 1;
          uVar4 = *(uint *)(lVar15 + 0x10);
        }
        else {
          if (uVar11 != (uint)uVar13) {
            uVar17 = *(undefined8 *)piVar5;
            uVar19 = *(undefined8 *)(piVar5 + 6);
            uVar18 = *(undefined8 *)(piVar5 + 4);
            puVar6[1] = *(undefined8 *)(piVar5 + 2);
            *puVar6 = uVar17;
            puVar6[3] = uVar19;
            puVar6[2] = uVar18;
            uVar17 = *(undefined8 *)(piVar5 + 8);
            uVar19 = *(undefined8 *)(piVar5 + 0xe);
            uVar18 = *(undefined8 *)(piVar5 + 0xc);
            puVar6[5] = *(undefined8 *)(piVar5 + 10);
            puVar6[4] = uVar17;
            puVar6[7] = uVar19;
            puVar6[6] = uVar18;
            uVar17 = *(undefined8 *)(piVar5 + 0x10);
            uVar19 = *(undefined8 *)(piVar5 + 0x16);
            uVar18 = *(undefined8 *)(piVar5 + 0x14);
            puVar6[9] = *(undefined8 *)(piVar5 + 0x12);
            puVar6[8] = uVar17;
            puVar6[0xb] = uVar19;
            puVar6[10] = uVar18;
            uVar17 = *(undefined8 *)(piVar5 + 0x18);
            uVar19 = *(undefined8 *)(piVar5 + 0x1e);
            uVar18 = *(undefined8 *)(piVar5 + 0x1c);
            puVar6[0xd] = *(undefined8 *)(piVar5 + 0x1a);
            puVar6[0xc] = uVar17;
            puVar6[0xf] = uVar19;
            puVar6[0xe] = uVar18;
            uVar17 = *(undefined8 *)(piVar5 + 0x20);
            puVar6[0x11] = *(undefined8 *)(piVar5 + 0x22);
            puVar6[0x10] = uVar17;
          }
          uVar13 = (ulong)((uint)uVar13 + 1);
        }
        uVar11 = uVar11 + 1;
        lVar14 = lVar14 + 0x90;
      } while (uVar11 < uVar4);
      uVar11 = *(uint *)(param_1 + 1);
      uVar16 = uVar16 + 1;
      *(int *)(lVar15 + 0x10) = (int)uVar13;
      if (uVar11 <= uVar16) break;
      while( true ) {
        lVar8 = lVar8 + 0x50;
        lVar15 = *param_1 + lVar8;
        uVar4 = *(uint *)(lVar15 + 0x10);
        if (uVar4 != 0) break;
LAB_0014c3ec:
        uVar16 = uVar16 + 1;
        *(undefined4 *)(lVar15 + 0x10) = 0;
        if (uVar11 <= uVar16) goto LAB_0014c410;
      }
    }
  }
LAB_0014c410:
  free(__ptr);
  return uVar9;
}

