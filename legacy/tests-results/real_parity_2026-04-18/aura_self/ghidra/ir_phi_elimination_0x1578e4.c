
int ir_phi_elimination(long *param_1)

{
  uint uVar1;
  long *plVar2;
  undefined8 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  int *piVar9;
  long lVar10;
  undefined8 *puVar11;
  int *piVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  size_t sVar16;
  uint uVar17;
  uint uVar18;
  int *piVar19;
  long *plVar20;
  int *piVar21;
  long lVar22;
  int *piVar23;
  ulong uVar24;
  int *piVar25;
  undefined4 *puVar26;
  uint uVar27;
  undefined8 uVar28;
  int iVar29;
  int iVar31;
  undefined8 uVar30;
  int iVar32;
  int iVar34;
  undefined8 uVar33;
  int *local_18;
  
  if ((param_1 == (long *)0x0) || (uVar18 = *(uint *)(param_1 + 1), uVar18 == 0)) {
    return 0;
  }
  local_18 = (int *)*param_1;
  plVar20 = (long *)(local_18 + 2);
  plVar2 = plVar20 + (ulong)uVar18 * 9;
  uVar5 = 0;
  do {
    uVar27 = *(uint *)(plVar20 + 1);
    if (uVar27 != 0) {
      piVar21 = (int *)*plVar20;
      if (uVar27 - 1 < 4) {
        uVar17 = 0;
      }
      else {
        iVar29 = 0;
        iVar31 = 0;
        iVar32 = 0;
        iVar34 = 0;
        piVar12 = piVar21;
        do {
          piVar23 = piVar12 + 0x88;
          iVar29 = iVar29 + (uint)(*piVar12 == 0x1b);
          iVar31 = iVar31 + (uint)(piVar12[0x22] == 0x1b);
          iVar32 = iVar32 + (uint)(piVar12[0x44] == 0x1b);
          iVar34 = iVar34 + (uint)(piVar12[0x66] == 0x1b);
          piVar12 = piVar23;
        } while (piVar21 + (ulong)(uVar27 >> 2) * 0x88 != piVar23);
        uVar17 = uVar27 & 0xfffffffc;
        uVar5 = uVar5 + iVar29 + iVar31 + iVar32 + iVar34;
        if ((uVar27 & 3) == 0) goto LAB_00157a04;
      }
      if (piVar21[(ulong)uVar17 * 0x22] == 0x1b) {
        uVar5 = uVar5 + 1;
      }
      if (uVar17 + 1 < uVar27) {
        if (piVar21[(ulong)(uVar17 + 1) * 0x22] == 0x1b) {
          uVar5 = uVar5 + 1;
        }
        if (uVar17 + 2 < uVar27) {
          if (piVar21[(ulong)(uVar17 + 2) * 0x22] == 0x1b) {
            uVar5 = uVar5 + 1;
          }
          if ((uVar17 + 3 < uVar27) && (piVar21[(ulong)(uVar17 + 3) * 0x22] == 0x1b)) {
            uVar5 = uVar5 + 1;
          }
        }
      }
    }
LAB_00157a04:
    plVar20 = plVar20 + 9;
  } while (plVar20 != plVar2);
  if (uVar5 == 0) {
    return 0;
  }
  piVar21 = calloc((ulong)uVar5,0x28);
  if (piVar21 == (int *)0x0) {
    return 0;
  }
  uVar24 = 0;
  piVar12 = local_18;
  do {
    uVar5 = piVar12[4];
    if (uVar5 != 0) {
      piVar23 = *(int **)(piVar12 + 2);
      uVar27 = 0;
      do {
        while (*piVar23 != 0x1b) {
LAB_00157a74:
          uVar27 = uVar27 + 1;
          piVar23 = piVar23 + 0x22;
          if (uVar5 <= uVar27) goto LAB_00157b58;
        }
        uVar17 = piVar23[0x18];
        if ((uVar17 == 0) ||
           (puVar26 = *(undefined4 **)(piVar23 + 0x14), puVar26 == (undefined4 *)0x0))
        goto LAB_00157a74;
        iVar29 = piVar23[2];
        iVar31 = piVar23[3];
        sVar16 = (ulong)uVar17 << 2;
        uVar1 = (int)uVar24 + 1;
        piVar21[uVar24 * 10] = *piVar12;
        piVar21[uVar24 * 10 + 1] = iVar29;
        piVar21[uVar24 * 10 + 2] = iVar31;
        piVar21[uVar24 * 10 + 3] = uVar17;
        pvVar6 = malloc(sVar16);
        *(void **)(piVar21 + uVar24 * 10 + 4) = pvVar6;
        pvVar7 = malloc(sVar16);
        *(void **)(piVar21 + uVar24 * 10 + 6) = pvVar7;
        pvVar8 = malloc(sVar16);
        *(void **)(piVar21 + uVar24 * 10 + 8) = pvVar8;
        if ((pvVar6 == (void *)0x0 || pvVar7 == (void *)0x0) || pvVar8 == (void *)0x0) {
          uVar24 = 0;
          do {
            uVar18 = (int)uVar24 + 1;
            free(*(void **)(piVar21 + uVar24 * 10 + 4));
            free(*(void **)(piVar21 + uVar24 * 10 + 6));
            free(*(void **)(piVar21 + uVar24 * 10 + 8));
            uVar24 = (ulong)uVar18;
          } while (uVar18 <= uVar1);
          free(piVar21);
          return 0;
        }
        lVar22 = *(long *)(piVar23 + 0x16);
        lVar13 = 0;
        if (lVar22 == 0) {
          lVar13 = 0;
          do {
            *(undefined4 *)((long)pvVar6 + lVar13 * 4) = 0;
            *(undefined4 *)((long)pvVar7 + lVar13 * 4) = *puVar26;
            *(undefined4 *)((long)pvVar8 + lVar13 * 4) = puVar26[1];
            lVar13 = lVar13 + 1;
            puVar26 = puVar26 + 4;
          } while ((uint)lVar13 < (uint)piVar23[0x18]);
          uVar5 = piVar12[4];
        }
        else {
          do {
            *(undefined4 *)((long)pvVar6 + lVar13 * 4) = *(undefined4 *)(lVar22 + lVar13 * 4);
            *(undefined4 *)((long)pvVar7 + lVar13 * 4) = *puVar26;
            *(undefined4 *)((long)pvVar8 + lVar13 * 4) = puVar26[1];
            lVar13 = lVar13 + 1;
            puVar26 = puVar26 + 4;
          } while ((uint)lVar13 < (uint)piVar23[0x18]);
          uVar5 = piVar12[4];
        }
        uVar27 = uVar27 + 1;
        piVar23 = piVar23 + 0x22;
        uVar24 = (ulong)uVar1;
      } while (uVar27 < uVar5);
    }
LAB_00157b58:
    piVar12 = piVar12 + 0x12;
  } while (local_18 + (ulong)uVar18 * 0x12 != piVar12);
  if ((int)uVar24 == 0) {
LAB_00157f58:
    lVar13 = 0;
    uVar18 = 0;
    iVar29 = 0;
    uVar5 = local_18[4];
    if (uVar5 == 0) goto LAB_00158014;
    while( true ) {
      lVar22 = 0;
      uVar27 = 0;
      uVar15 = 0;
      do {
        lVar10 = *(long *)(local_18 + 2);
        puVar3 = (undefined8 *)(lVar10 + lVar22);
        puVar11 = (undefined8 *)(lVar10 + uVar15 * 0x88);
        if (*(int *)(lVar10 + lVar22) == 0x1b) {
          iVar29 = iVar29 + 1;
          free((void *)puVar3[10]);
          free((void *)puVar3[0xb]);
          uVar5 = local_18[4];
        }
        else {
          if ((uint)uVar15 != uVar27) {
            uVar28 = *puVar3;
            uVar33 = puVar3[3];
            uVar30 = puVar3[2];
            puVar11[1] = puVar3[1];
            *puVar11 = uVar28;
            puVar11[3] = uVar33;
            puVar11[2] = uVar30;
            uVar28 = puVar3[4];
            uVar33 = puVar3[7];
            uVar30 = puVar3[6];
            puVar11[5] = puVar3[5];
            puVar11[4] = uVar28;
            puVar11[7] = uVar33;
            puVar11[6] = uVar30;
            uVar28 = puVar3[8];
            uVar33 = puVar3[0xb];
            uVar30 = puVar3[10];
            puVar11[9] = puVar3[9];
            puVar11[8] = uVar28;
            puVar11[0xb] = uVar33;
            puVar11[10] = uVar30;
            uVar28 = puVar3[0xc];
            uVar33 = puVar3[0xf];
            uVar30 = puVar3[0xe];
            puVar11[0xd] = puVar3[0xd];
            puVar11[0xc] = uVar28;
            puVar11[0xf] = uVar33;
            puVar11[0xe] = uVar30;
            puVar11[0x10] = puVar3[0x10];
          }
          uVar15 = (ulong)((uint)uVar15 + 1);
        }
        uVar27 = uVar27 + 1;
        lVar22 = lVar22 + 0x88;
      } while (uVar27 < uVar5);
      uVar18 = uVar18 + 1;
      uVar5 = *(uint *)(param_1 + 1);
      local_18[4] = (int)uVar15;
      if (uVar5 <= uVar18) break;
      while( true ) {
        lVar13 = lVar13 + 0x48;
        local_18 = (int *)(*param_1 + lVar13);
        uVar5 = local_18[4];
        if (uVar5 != 0) break;
LAB_00158014:
        uVar18 = uVar18 + 1;
        uVar5 = *(uint *)(param_1 + 1);
        local_18[4] = 0;
        if (uVar5 <= uVar18) goto LAB_00158034;
      }
    }
LAB_00158034:
    if ((int)uVar24 == 0) goto LAB_00158068;
  }
  else {
    piVar12 = piVar21;
    do {
      uVar5 = piVar12[3];
      if (uVar5 != 0) {
        lVar22 = *(long *)(piVar12 + 6);
        lVar13 = 0;
LAB_00157ba0:
        iVar29 = *(int *)(lVar22 + lVar13);
        if (((iVar29 != -1) && (piVar12[1] != iVar29)) && (uVar18 != 0)) {
          piVar25 = (int *)*param_1;
          piVar19 = piVar25 + (ulong)uVar18 * 0x12;
          piVar23 = piVar25;
          do {
            if (*piVar12 == *piVar23) {
              if (piVar23[4] != 0) {
                piVar9 = *(int **)(piVar23 + 2);
                piVar23 = piVar9 + (ulong)(uint)piVar23[4] * 0x22;
                goto LAB_00157c10;
              }
              break;
            }
            piVar23 = piVar23 + 0x12;
          } while (piVar19 != piVar23);
        }
        goto LAB_00157d80;
      }
LAB_00157d8c:
      piVar12 = piVar12 + 10;
    } while (piVar21 + uVar24 * 10 != piVar12);
    piVar12 = piVar21 + 1;
    piVar23 = piVar12 + uVar24 * 10;
    do {
      uVar5 = piVar12[2];
      if (uVar5 != 0) {
        lVar22 = *(long *)(piVar12 + 5);
        lVar13 = 0;
LAB_00157dc0:
        iVar29 = *(int *)(lVar22 + lVar13);
        if (((iVar29 != -1) && (iVar31 = *piVar12, iVar31 != iVar29)) && (uVar18 != 0)) {
          piVar25 = (int *)*param_1;
          piVar19 = piVar25 + (ulong)uVar18 * 0x12;
          do {
            if (*(int *)(*(long *)(piVar12 + 3) + lVar13) == *piVar25) {
              uVar18 = piVar25[4];
              pvVar6 = *(void **)(piVar25 + 2);
              uVar15 = (ulong)uVar18;
              goto LAB_00157e20;
            }
            piVar25 = piVar25 + 0x12;
          } while (piVar19 != piVar25);
        }
        goto LAB_00157f2c;
      }
LAB_00157f38:
      piVar12 = piVar12 + 10;
    } while (piVar23 != piVar12);
    if (uVar18 != 0) {
      local_18 = (int *)*param_1;
      goto LAB_00157f58;
    }
    iVar29 = 0;
  }
  piVar12 = piVar21 + 4;
  do {
    piVar23 = piVar12 + 10;
    free(*(void **)piVar12);
    free(*(void **)(piVar12 + 2));
    free(*(void **)(piVar12 + 4));
    piVar12 = piVar23;
  } while (piVar21 + 4 + uVar24 * 10 != piVar23);
LAB_00158068:
  free(piVar21);
  return iVar29;
  while (piVar9 = piVar9 + 0x22, piVar23 != piVar9) {
LAB_00157c10:
    if ((*piVar9 == 0x1b) && (iVar29 == piVar9[2])) {
      lVar14 = *(long *)(piVar12 + 4);
      lVar10 = *(long *)(piVar12 + 8);
      iVar31 = (int)param_1[2];
      *(int *)(param_1 + 2) = iVar31 + 1;
      uVar4 = *(undefined4 *)(lVar10 + lVar13);
      goto LAB_00157c58;
    }
  }
  goto LAB_00157d80;
  while (piVar25 = piVar25 + 0x12, piVar19 != piVar25) {
LAB_00157c58:
    if (*(int *)(lVar14 + lVar13) == *piVar25) {
      uVar18 = piVar25[4];
      pvVar6 = *(void **)(piVar25 + 2);
      uVar15 = (ulong)uVar18;
      goto LAB_00157c70;
    }
  }
  goto LAB_00157d70;
  while( true ) {
    uVar17 = (int)uVar15 - 1;
    uVar15 = (ulong)uVar17;
    iVar32 = *(int *)((long)pvVar6 + uVar15 * 0x88);
    if (iVar32 - 0x17U < 2 || iVar32 == 0x1a) break;
LAB_00157c70:
    if ((int)uVar15 == 0) {
      uVar27 = piVar25[5];
      uVar17 = uVar18;
      if (uVar27 <= uVar18) goto LAB_00157ca0;
      lVar10 = (ulong)uVar18 * 0x88;
      goto LAB_00157d40;
    }
  }
  uVar27 = piVar25[5];
  if (uVar27 <= uVar18) {
LAB_00157ca0:
    if (uVar27 == 0) {
      sVar16 = 0x220;
      uVar27 = 4;
    }
    else {
      uVar27 = uVar27 << 1;
      sVar16 = (ulong)uVar27 * 0x88;
    }
    pvVar6 = realloc(pvVar6,sVar16);
    if (pvVar6 == (void *)0x0) goto LAB_00157d70;
    uVar18 = piVar25[4];
    *(void **)(piVar25 + 2) = pvVar6;
    piVar25[5] = uVar27;
  }
  lVar10 = (ulong)uVar17 * 0x88;
  if (uVar17 < uVar18) {
    memmove((void *)((long)pvVar6 + (ulong)(uVar17 + 1) * 0x88),(void *)((long)pvVar6 + lVar10),
            (ulong)(uVar18 - uVar17) * 0x88);
    pvVar6 = *(void **)(piVar25 + 2);
    uVar18 = piVar25[4];
  }
LAB_00157d40:
  puVar3 = (undefined8 *)((long)pvVar6 + lVar10);
  piVar25[4] = uVar18 + 1;
  puVar3[1] = 0;
  *puVar3 = 0;
  puVar3[3] = 0;
  puVar3[2] = 0;
  puVar3[9] = 0;
  puVar3[8] = 0;
  puVar3[0xb] = 0;
  puVar3[10] = 0;
  *(int *)(puVar3 + 1) = iVar31;
  *(undefined4 *)((long)puVar3 + 0xc) = uVar4;
  *(int *)(puVar3 + 3) = iVar29;
  *(undefined4 *)((long)puVar3 + 0x1c) = uVar4;
  *(undefined4 *)(puVar3 + 9) = 1;
  puVar3[0x10] = 0;
  puVar3[5] = 0;
  puVar3[4] = 0;
  puVar3[7] = 0;
  puVar3[6] = 0;
  puVar3[0xd] = 0;
  puVar3[0xc] = 0;
  puVar3[0xf] = 0;
  puVar3[0xe] = 0;
LAB_00157d70:
  *(int *)(lVar22 + lVar13) = iVar31;
  uVar18 = *(uint *)(param_1 + 1);
LAB_00157d80:
  lVar13 = lVar13 + 4;
  if ((ulong)uVar5 << 2 == lVar13) goto LAB_00157d8c;
  goto LAB_00157ba0;
  while( true ) {
    uVar17 = (int)uVar15 - 1;
    uVar15 = (ulong)uVar17;
    iVar32 = *(int *)((long)pvVar6 + uVar15 * 0x88);
    if (iVar32 - 0x17U < 2 || iVar32 == 0x1a) break;
LAB_00157e20:
    if ((int)uVar15 == 0) {
      iVar32 = piVar12[1];
      uVar27 = piVar25[5];
      uVar4 = *(undefined4 *)(*(long *)(piVar12 + 7) + lVar13);
      uVar17 = uVar18;
      if (uVar27 <= uVar18) goto LAB_00157e64;
      lVar10 = (ulong)uVar18 * 0x88;
      goto LAB_00157ee0;
    }
  }
  iVar32 = piVar12[1];
  uVar27 = piVar25[5];
  uVar4 = *(undefined4 *)(*(long *)(piVar12 + 7) + lVar13);
  if (uVar27 <= uVar18) {
LAB_00157e64:
    if (uVar27 == 0) {
      sVar16 = 0x220;
      uVar27 = 4;
    }
    else {
      uVar27 = uVar27 << 1;
      sVar16 = (ulong)uVar27 * 0x88;
    }
    pvVar6 = realloc(pvVar6,sVar16);
    if (pvVar6 == (void *)0x0) {
      uVar18 = *(uint *)(param_1 + 1);
      goto LAB_00157f2c;
    }
    uVar18 = piVar25[4];
    *(void **)(piVar25 + 2) = pvVar6;
    piVar25[5] = uVar27;
  }
  lVar10 = (ulong)uVar17 * 0x88;
  if (uVar17 < uVar18) {
    memmove((void *)((long)pvVar6 + (ulong)(uVar17 + 1) * 0x88),(void *)((long)pvVar6 + lVar10),
            (ulong)(uVar18 - uVar17) * 0x88);
    pvVar6 = *(void **)(piVar25 + 2);
    uVar18 = piVar25[4];
  }
LAB_00157ee0:
  puVar3 = (undefined8 *)((long)pvVar6 + lVar10);
  piVar25[4] = uVar18 + 1;
  puVar3[0x10] = 0;
  puVar3[1] = 0;
  *puVar3 = 0;
  puVar3[3] = 0;
  puVar3[2] = 0;
  puVar3[5] = 0;
  puVar3[4] = 0;
  puVar3[7] = 0;
  puVar3[6] = 0;
  puVar3[9] = 0;
  puVar3[8] = 0;
  puVar3[0xb] = 0;
  puVar3[10] = 0;
  puVar3[0xd] = 0;
  puVar3[0xc] = 0;
  puVar3[0xf] = 0;
  puVar3[0xe] = 0;
  uVar18 = *(uint *)(param_1 + 1);
  *(int *)((long)puVar3 + 0xc) = iVar32;
  *(int *)(puVar3 + 1) = iVar31;
  *(int *)(puVar3 + 3) = iVar29;
  *(undefined4 *)((long)puVar3 + 0x1c) = uVar4;
  *(undefined4 *)(puVar3 + 9) = 1;
LAB_00157f2c:
  lVar13 = lVar13 + 4;
  if ((ulong)uVar5 << 2 == lVar13) goto LAB_00157f38;
  goto LAB_00157dc0;
}

