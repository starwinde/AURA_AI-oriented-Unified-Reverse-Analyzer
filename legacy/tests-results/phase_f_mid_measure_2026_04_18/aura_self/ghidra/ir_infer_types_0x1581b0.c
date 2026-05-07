
undefined8 ir_infer_types(long *param_1)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  int *piVar7;
  long *plVar8;
  uint *puVar9;
  undefined8 uVar10;
  uint *puVar11;
  int *piVar12;
  uint *puVar13;
  ulong uVar14;
  ulong extraout_x8;
  ulong extraout_x8_00;
  ulong extraout_x8_01;
  long *plVar15;
  long *extraout_x9;
  long *extraout_x9_00;
  long *extraout_x9_01;
  undefined8 uVar16;
  undefined8 extraout_x10;
  undefined8 extraout_x10_00;
  undefined8 extraout_x10_01;
  ulong uVar17;
  ulong extraout_x11;
  ulong extraout_x11_00;
  ulong extraout_x11_01;
  ulong uVar18;
  ulong extraout_x12;
  ulong extraout_x12_00;
  ulong extraout_x12_01;
  long *plVar19;
  long *extraout_x13;
  long *extraout_x13_00;
  long *extraout_x13_01;
  long *extraout_x14;
  long *extraout_x14_00;
  long *extraout_x14_01;
  ulong uVar20;
  ulong extraout_x15;
  ulong extraout_x15_00;
  ulong extraout_x15_01;
  uint uVar21;
  long *plVar22;
  undefined4 *puVar23;
  undefined4 *extraout_x18;
  
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  uVar20 = 0x50;
  uVar18 = 10;
  uVar14 = 0x88;
  uVar16 = 5;
  plVar19 = (long *)(*param_1 + 8);
  uVar17 = 0x1000000d;
  plVar15 = plVar19 + (ulong)*(uint *)(param_1 + 1) * 10;
  do {
    uVar10 = 0;
    plVar22 = plVar19;
    do {
      if (*(uint *)(plVar22 + 1) != 0) {
        puVar9 = (uint *)*plVar22;
        puVar11 = (uint *)((long)puVar9 + (ulong)*(uint *)(plVar22 + 1) * (uVar14 & 0xffffffff));
        do {
          while (uVar21 = *puVar9, 0xe < uVar21) {
            if (uVar21 == 0x1b) {
              if ((puVar9[0x18] != 0) && (*(long *)(puVar9 + 0x14) != 0)) {
                puVar23 = (undefined4 *)(*(long *)(puVar9 + 0x14) + 4);
                uVar4 = 6;
                puVar1 = puVar23 + (ulong)puVar9[0x18] * 4;
                do {
                  uVar4 = type_wider(uVar4,*puVar23);
                  uVar14 = extraout_x8_00;
                  plVar15 = extraout_x9_00;
                  uVar16 = extraout_x10_00;
                  uVar17 = extraout_x11_00;
                  uVar18 = extraout_x12_00;
                  plVar19 = extraout_x13_00;
                  param_1 = extraout_x14_00;
                  uVar20 = extraout_x15_00;
                  puVar23 = extraout_x18;
                } while (extraout_x18 != puVar1);
                goto LAB_0015823c;
              }
            }
            else if (uVar21 < 0x1c) {
              if (uVar21 - 0x11 < 4) goto LAB_00158504;
            }
            else if ((uVar21 == 0x1c) && (2 < puVar9[0x12])) {
              uVar4 = type_wider(puVar9[0xb],puVar9[0xf]);
              uVar14 = extraout_x8;
              plVar15 = extraout_x9;
              uVar16 = extraout_x10;
              uVar17 = extraout_x11;
              uVar18 = extraout_x12;
              plVar19 = extraout_x13;
              param_1 = extraout_x14;
              uVar20 = extraout_x15;
              goto LAB_0015823c;
            }
LAB_00158264:
            puVar9 = puVar9 + 0x22;
            if (puVar9 == puVar11) goto LAB_00158270;
          }
          if (10 < uVar21) {
LAB_00158504:
            uVar4 = 6;
LAB_0015823c:
            if (puVar9[3] != (uint)uVar4 && (puVar9[3] != 0 && puVar9[2] != 0xffffffff)) {
              uVar10 = 1;
              puVar9[3] = (uint)uVar4;
            }
            goto LAB_00158264;
          }
          if (8 < uVar21) {
LAB_00158230:
            if (puVar9[0x12] == 0) goto LAB_00158264;
LAB_00158238:
            uVar4 = (ulong)puVar9[7];
            goto LAB_0015823c;
          }
          if (uVar21 < 2) {
            if (uVar21 != 0) goto LAB_00158264;
            goto LAB_00158230;
          }
          if (1 < puVar9[0x12]) {
            uVar4 = type_wider(puVar9[7],puVar9[0xb]);
            uVar14 = extraout_x8_01;
            plVar15 = extraout_x9_01;
            uVar16 = extraout_x10_01;
            uVar17 = extraout_x11_01;
            uVar18 = extraout_x12_01;
            plVar19 = extraout_x13_01;
            param_1 = extraout_x14_01;
            uVar20 = extraout_x15_01;
            goto LAB_0015823c;
          }
          if (puVar9[0x12] == 1) goto LAB_00158238;
          puVar9 = puVar9 + 0x22;
        } while (puVar9 != puVar11);
      }
LAB_00158270:
      plVar22 = plVar22 + 10;
    } while (plVar22 != plVar15);
    bVar3 = false;
    plVar22 = plVar19;
    do {
      if (*(uint *)(plVar22 + 1) != 0) {
        piVar7 = (int *)*plVar22;
        piVar12 = (int *)((long)piVar7 + (ulong)*(uint *)(plVar22 + 1) * (uVar14 & 0xffffffff));
        do {
          if ((((*piVar7 - 0x15U < 2) && (piVar7[0x12] != 0)) && (piVar7[6] != -1)) &&
             (*(uint *)(param_1 + 1) != 0)) {
            plVar8 = plVar19;
            do {
              if (*(uint *)(plVar8 + 1) != 0) {
                lVar5 = *plVar8;
                lVar6 = lVar5 + (ulong)*(uint *)(plVar8 + 1) * (uVar14 & 0xffffffff);
                do {
                  if (piVar7[6] == *(int *)(lVar5 + 8)) {
                    if ((*(uint *)(lVar5 + 0xc) != 5) &&
                       ((*(uint *)(lVar5 + 0xc) & 0xfffffffb) == 0)) {
                      bVar3 = true;
                      *(uint *)(lVar5 + 0xc) = (uint)uVar16;
                    }
                    goto LAB_00158318;
                  }
                  lVar5 = lVar5 + 0x88;
                } while (lVar6 != lVar5);
              }
              plVar8 = plVar8 + 10;
            } while ((long *)((long)plVar19 + (ulong)*(uint *)(param_1 + 1) * (uVar20 & 0xffffffff))
                     != plVar8);
          }
LAB_00158318:
          piVar7 = piVar7 + 0x22;
        } while (piVar7 != piVar12);
      }
      plVar22 = plVar22 + 10;
    } while (plVar22 != plVar15);
    bVar2 = false;
    plVar22 = plVar19;
    do {
      if (*(uint *)(plVar22 + 1) != 0) {
        puVar9 = (uint *)*plVar22;
        puVar11 = (uint *)((long)puVar9 + (ulong)*(uint *)(plVar22 + 1) * (uVar14 & 0xffffffff));
        do {
          if (((puVar9[2] != 0xffffffff) && (puVar9[3] != 5)) && (puVar9[0x12] != 0)) {
            puVar13 = puVar9 + 6;
            uVar21 = 0;
            do {
              if (puVar13[1] == 5) {
LAB_0015846c:
                if ((*puVar9 < 0x1d) && ((uVar17 >> ((ulong)*puVar9 & 0x3f) & 1) != 0)) {
                  puVar9[3] = (uint)uVar16;
                  bVar2 = true;
                }
                break;
              }
              if ((*puVar13 != 0xffffffff) && (*(uint *)(param_1 + 1) != 0)) {
                plVar8 = plVar19;
                do {
                  if (*(uint *)(plVar8 + 1) != 0) {
                    lVar5 = *plVar8;
                    lVar6 = lVar5 + (ulong)*(uint *)(plVar8 + 1) * (uVar14 & 0xffffffff);
                    do {
                      if (*puVar13 == *(uint *)(lVar5 + 8)) {
                        if (*(int *)(lVar5 + 0xc) != 5) goto LAB_001583d8;
                        puVar9[(ulong)uVar21 * 4 + 7] = 5;
                        goto LAB_0015846c;
                      }
                      lVar5 = lVar5 + 0x88;
                    } while (lVar5 != lVar6);
                  }
                  plVar8 = plVar8 + 10;
                } while (plVar8 != (long *)((long)plVar19 +
                                           (ulong)*(uint *)(param_1 + 1) * (uVar20 & 0xffffffff)));
              }
LAB_001583d8:
              uVar21 = uVar21 + 1;
              puVar13 = puVar13 + 4;
            } while (uVar21 < puVar9[0x12] && uVar21 != 3);
          }
          puVar9 = puVar9 + 0x22;
        } while (puVar9 != puVar11);
      }
      plVar22 = plVar22 + 10;
    } while (plVar22 != plVar15);
    if ((((int)uVar10 == 0 && !bVar3) && !bVar2) ||
       (uVar21 = (int)uVar18 - 1, uVar18 = (ulong)uVar21, uVar21 == 0)) {
      return 0;
    }
  } while( true );
}

