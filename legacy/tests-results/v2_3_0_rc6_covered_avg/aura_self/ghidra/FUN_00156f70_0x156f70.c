
undefined8 FUN_00156f70(long *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  long lVar8;
  uint *puVar9;
  undefined8 *puVar10;
  int *piVar11;
  undefined8 *puVar12;
  void *__ptr;
  long lVar13;
  uint *puVar14;
  undefined8 uVar15;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 1);
  if (uVar1 == 0) {
    return 0;
  }
  __ptr = (void *)0x0;
  uVar2 = *(uint *)(param_1 + 2);
  lVar13 = *param_1;
  if ((uVar2 - 1 < 0xfffffffe) && (__ptr = calloc((ulong)uVar2,4), __ptr != (void *)0x0)) {
    puVar10 = (undefined8 *)(lVar13 + 8);
    puVar12 = puVar10 + (ulong)uVar1 * 10;
    do {
      if (*(uint *)(puVar10 + 1) != 0) {
        piVar7 = (int *)*puVar10;
        piVar11 = piVar7 + (ulong)*(uint *)(puVar10 + 1) * 0x24;
        do {
          while( true ) {
            iVar3 = piVar7[0x12];
            if (iVar3 != 0) {
              uVar4 = piVar7[6];
              if (uVar4 < uVar2) {
                *(int *)((long)__ptr + (ulong)uVar4 * 4) =
                     *(int *)((long)__ptr + (ulong)uVar4 * 4) + 1;
              }
              if (iVar3 != 1) {
                uVar4 = piVar7[10];
                if (uVar4 < uVar2) {
                  *(int *)((long)__ptr + (ulong)uVar4 * 4) =
                       *(int *)((long)__ptr + (ulong)uVar4 * 4) + 1;
                }
                if ((iVar3 != 2) && (uVar4 = piVar7[0xe], uVar4 < uVar2)) {
                  *(int *)((long)__ptr + (ulong)uVar4 * 4) =
                       *(int *)((long)__ptr + (ulong)uVar4 * 4) + 1;
                }
              }
            }
            if ((*piVar7 != 0x1b) || (piVar7[0x18] == 0)) break;
            puVar9 = *(uint **)(piVar7 + 0x14);
            puVar14 = puVar9 + (ulong)(uint)piVar7[0x18] * 4;
            do {
              uVar4 = *puVar9;
              puVar9 = puVar9 + 4;
              if (uVar4 < uVar2) {
                *(int *)((long)__ptr + (ulong)uVar4 * 4) =
                     *(int *)((long)__ptr + (ulong)uVar4 * 4) + 1;
              }
            } while (puVar14 != puVar9);
            piVar7 = piVar7 + 0x24;
            if (piVar7 == piVar11) goto LAB_001570c8;
          }
          piVar7 = piVar7 + 0x24;
        } while (piVar7 != piVar11);
      }
LAB_001570c8:
      puVar10 = puVar10 + 10;
    } while (puVar10 != puVar12);
  }
  puVar14 = (uint *)(lVar13 + 0x10);
  uVar15 = 0;
  puVar9 = puVar14 + (ulong)uVar1 * 0x14;
LAB_001570f8:
  uVar1 = *puVar14;
  if (1 < uVar1) {
    uVar2 = uVar1 - 1;
    lVar8 = *(long *)(puVar14 + -2);
    lVar13 = lVar8 + (ulong)uVar2 * 0x90;
    if ((*(int *)(lVar8 + (ulong)uVar2 * 0x90) == 0x1a) && (uVar4 = uVar1 - 2, -1 < (int)uVar4)) {
      piVar7 = (int *)(lVar8 + (ulong)uVar4 * 0x90);
      uVar6 = uVar4;
      while (*piVar7 != 0x19) {
        uVar6 = uVar6 - 1;
        if ((*piVar7 - 0x16U < 3) || (piVar7 = piVar7 + -0x24, uVar6 == 0xffffffff))
        goto LAB_001570ec;
      }
      uVar5 = piVar7[2];
      if (((uVar5 != 0xffffffff) &&
          ((*(int *)(lVar13 + 0x48) != 0 && (uVar5 == *(uint *)(lVar13 + 0x18))))) &&
         ((__ptr == (void *)0x0 || (*(int *)((long)__ptr + (ulong)uVar5 * 4) == 1)))) {
        uVar5 = uVar6 + 1;
        if (uVar2 <= uVar5) goto LAB_001571d4;
        piVar11 = (int *)(lVar8 + (ulong)uVar5 * 0x90);
        goto LAB_001571b8;
      }
    }
  }
  goto LAB_001570ec;
  while ((int *)(lVar8 + 0x90 + ((ulong)((uVar1 - 3) - uVar6) + (ulong)uVar5) * 0x90) != piVar11) {
LAB_001571b8:
    iVar3 = *piVar11;
    piVar11 = piVar11 + 0x24;
    if (iVar3 - 0x16U < 4) goto LAB_001570ec;
  }
LAB_001571d4:
  iVar3 = piVar7[0x12];
  *(undefined4 *)(lVar13 + 100) = 0xffffffff;
  if (iVar3 != 0) {
    uVar15 = *(undefined8 *)(piVar7 + 8);
    *(undefined8 *)(lVar13 + 0x28) = *(undefined8 *)(piVar7 + 6);
    *(undefined8 *)(lVar13 + 0x30) = uVar15;
    if (*(int *)(lVar13 + 0x48) == 1) {
      *(undefined4 *)(lVar13 + 0x48) = 2;
    }
  }
  uVar15 = *(undefined8 *)(piVar7 + 0x14);
  *(undefined8 *)(lVar13 + 0x58) = *(undefined8 *)(piVar7 + 0x16);
  *(undefined8 *)(lVar13 + 0x50) = uVar15;
  *(int *)(lVar13 + 0x60) = piVar7[0x18];
  piVar7[0x14] = 0;
  piVar7[0x15] = 0;
  piVar7[0x16] = 0;
  piVar7[0x17] = 0;
  piVar7[0x18] = 0;
  if (uVar5 < uVar1) {
    memmove((void *)(lVar8 + (long)(int)uVar6 * 0x90),(void *)(lVar8 + (ulong)uVar5 * 0x90),
            ((ulong)(uVar4 - uVar6) + 1) * 0x90);
  }
  uVar15 = 1;
  *puVar14 = uVar2;
LAB_001570ec:
  puVar14 = puVar14 + 0x14;
  if (puVar9 == puVar14) {
    free(__ptr);
    return uVar15;
  }
  goto LAB_001570f8;
}

