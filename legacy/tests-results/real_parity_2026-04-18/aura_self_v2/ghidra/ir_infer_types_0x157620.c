
undefined8 ir_infer_types(long *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  uint *puVar6;
  undefined8 *puVar7;
  uint uVar8;
  undefined8 uVar9;
  ulong uVar10;
  ulong extraout_x8;
  ulong extraout_x8_00;
  ulong extraout_x8_01;
  ulong uVar11;
  ulong extraout_x9;
  ulong extraout_x9_00;
  ulong extraout_x9_01;
  undefined8 *puVar12;
  undefined8 *extraout_x10;
  undefined8 *extraout_x10_00;
  undefined8 *extraout_x10_01;
  undefined8 uVar13;
  undefined8 extraout_x11;
  undefined8 extraout_x11_00;
  undefined8 extraout_x11_01;
  undefined8 *puVar14;
  undefined8 *extraout_x12;
  undefined8 *extraout_x12_00;
  undefined8 *extraout_x12_01;
  ulong uVar15;
  ulong extraout_x13;
  ulong extraout_x13_00;
  ulong extraout_x13_01;
  long *extraout_x14;
  long *extraout_x14_00;
  long *extraout_x14_01;
  ulong uVar16;
  ulong extraout_x15;
  ulong extraout_x15_00;
  ulong extraout_x15_01;
  undefined4 *puVar17;
  undefined4 *extraout_x18;
  uint *puVar18;
  undefined8 *puVar19;
  
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  uVar16 = 0x48;
  uVar15 = 10;
  uVar10 = 0x88;
  uVar11 = 0x1000000d;
  uVar13 = 5;
  puVar12 = (undefined8 *)(*param_1 + 8) + (ulong)*(uint *)(param_1 + 1) * 9;
  puVar7 = (undefined8 *)(*param_1 + 8);
  do {
    uVar9 = 0;
    puVar14 = puVar7;
    puVar19 = puVar7;
    do {
      if (*(uint *)(puVar19 + 1) != 0) {
        puVar6 = (uint *)*puVar19;
        puVar18 = (uint *)((long)puVar6 + (ulong)*(uint *)(puVar19 + 1) * (uVar10 & 0xffffffff));
        do {
          while (uVar8 = *puVar6, 0xe < uVar8) {
            if (uVar8 == 0x1b) {
              if ((puVar6[0x18] != 0) && (*(long *)(puVar6 + 0x14) != 0)) {
                puVar17 = (undefined4 *)(*(long *)(puVar6 + 0x14) + 4);
                uVar4 = 6;
                puVar1 = puVar17 + (ulong)puVar6[0x18] * 4;
                do {
                  uVar4 = type_wider(uVar4,*puVar17);
                  uVar10 = extraout_x8_01;
                  uVar11 = extraout_x9_01;
                  puVar12 = extraout_x10_01;
                  uVar13 = extraout_x11_01;
                  puVar14 = extraout_x12_01;
                  uVar15 = extraout_x13_01;
                  param_1 = extraout_x14_01;
                  uVar16 = extraout_x15_01;
                  puVar17 = extraout_x18;
                } while (puVar1 != extraout_x18);
                goto LAB_001576b4;
              }
            }
            else if (uVar8 < 0x1c) {
              if (uVar8 - 0x11 < 4) goto LAB_00157804;
            }
            else if ((uVar8 == 0x1c) && (2 < puVar6[0x12])) {
              uVar4 = type_wider(puVar6[0xb],puVar6[0xf]);
              uVar10 = extraout_x8;
              uVar11 = extraout_x9;
              puVar12 = extraout_x10;
              uVar13 = extraout_x11;
              puVar14 = extraout_x12;
              uVar15 = extraout_x13;
              param_1 = extraout_x14;
              uVar16 = extraout_x15;
              goto LAB_001576b4;
            }
LAB_001576dc:
            puVar6 = puVar6 + 0x22;
            if (puVar6 == puVar18) goto LAB_001576e8;
          }
          if (10 < uVar8) {
LAB_00157804:
            uVar4 = 6;
LAB_001576b4:
            if (puVar6[3] != (uint)uVar4 && (puVar6[3] != 0 && puVar6[2] != 0xffffffff)) {
              uVar9 = 1;
              puVar6[3] = (uint)uVar4;
            }
            goto LAB_001576dc;
          }
          if (8 < uVar8) {
LAB_001576a8:
            if (puVar6[0x12] == 0) goto LAB_001576dc;
LAB_001576b0:
            uVar4 = (ulong)puVar6[7];
            goto LAB_001576b4;
          }
          if (uVar8 < 2) {
            if (uVar8 != 0) goto LAB_001576dc;
            goto LAB_001576a8;
          }
          if (1 < puVar6[0x12]) {
            uVar4 = type_wider(puVar6[7],puVar6[0xb]);
            uVar10 = extraout_x8_00;
            uVar11 = extraout_x9_00;
            puVar12 = extraout_x10_00;
            uVar13 = extraout_x11_00;
            puVar14 = extraout_x12_00;
            uVar15 = extraout_x13_00;
            param_1 = extraout_x14_00;
            uVar16 = extraout_x15_00;
            goto LAB_001576b4;
          }
          if (puVar6[0x12] == 1) goto LAB_001576b0;
          puVar6 = puVar6 + 0x22;
        } while (puVar6 != puVar18);
      }
LAB_001576e8:
      uVar8 = (uint)uVar9;
      puVar19 = puVar19 + 9;
    } while (puVar19 != puVar12);
    uVar2 = *(uint *)(param_1 + 1);
    if (uVar2 != 0) {
      uVar5 = 0;
      do {
        if (*(uint *)(puVar7 + 1) != 0) {
          puVar6 = (uint *)*puVar7;
          puVar18 = (uint *)((long)puVar6 + (ulong)*(uint *)(puVar7 + 1) * (uVar10 & 0xffffffff));
          do {
            if (((((puVar6[2] != 0xffffffff) && (puVar6[3] != 5)) &&
                 (uVar3 = puVar6[0x12], uVar3 != 0)) &&
                ((puVar6[7] == 5 ||
                 ((uVar3 != 1 && ((puVar6[0xb] == 5 || ((uVar3 != 2 && (puVar6[0xf] == 5))))))))))
               && ((*puVar6 < 0x1d && ((uVar11 >> ((ulong)*puVar6 & 0x3f) & 1) != 0)))) {
              uVar5 = 1;
              puVar6[3] = (uint)uVar13;
            }
            puVar6 = puVar6 + 0x22;
          } while (puVar6 != puVar18);
        }
        puVar7 = puVar7 + 9;
      } while (puVar7 != (undefined8 *)((long)puVar14 + (ulong)uVar2 * (uVar16 & 0xffffffff)));
      uVar8 = uVar8 | uVar5;
    }
    if ((uVar8 == 0) ||
       (uVar8 = (int)uVar15 - 1, uVar15 = (ulong)uVar8, puVar7 = puVar14, uVar8 == 0)) {
      return 0;
    }
  } while( true );
}

