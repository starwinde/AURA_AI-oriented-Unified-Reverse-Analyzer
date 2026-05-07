
undefined1  [16] evaluate_instr(uint *param_1,long param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  uint *puVar11;
  long lVar12;
  long lVar13;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  
  uVar3 = *param_1;
  if (uVar3 < 0xf) {
    if (1 < uVar3) {
      if (1 < param_1[0x12]) {
        uVar4 = param_1[6];
        uVar5 = param_1[10];
        uVar2 = uVar4;
        if (uVar4 < uVar5) {
          uVar2 = uVar5;
        }
        if (uVar2 < param_3) {
          iVar6 = *(int *)(param_2 + (ulong)uVar4 * 0x10);
          iVar7 = *(int *)(param_2 + (ulong)uVar5 * 0x10);
          if (iVar6 != 2 && iVar7 != 2) {
            uVar8 = *(ulong *)(param_2 + (ulong)uVar4 * 0x10 + 8);
            uVar10 = *(ulong *)(param_2 + (ulong)uVar5 * 0x10 + 8);
            if (iVar7 == 0 || iVar6 == 0) {
              return ZEXT816(0);
            }
            switch(uVar3) {
            case 3:
              uVar9 = uVar8 - uVar10;
              break;
            case 4:
              uVar9 = uVar8 * uVar10;
              break;
            case 5:
              if (uVar10 == 0) goto LAB_00154c9c;
              uVar9 = 0;
              if (uVar10 != 0) {
                uVar9 = (long)uVar8 / (long)uVar10;
              }
              break;
            case 6:
              uVar9 = uVar8 & uVar10;
              break;
            case 7:
              uVar9 = uVar8 | uVar10;
              break;
            case 8:
              uVar9 = uVar8 ^ uVar10;
              break;
            case 9:
              uVar9 = uVar8 << (uVar10 & 0x3f);
              break;
            case 10:
              uVar9 = uVar8 >> (uVar10 & 0x3f);
              break;
            case 0xb:
              uVar9 = (ulong)(uVar8 == uVar10);
              break;
            case 0xc:
              uVar9 = (ulong)(uVar8 != uVar10);
              break;
            case 0xd:
              uVar9 = (ulong)((long)uVar8 < (long)uVar10);
              break;
            case 0xe:
              uVar9 = (ulong)((long)uVar8 <= (long)uVar10);
              break;
            default:
              uVar9 = uVar8 + uVar10;
            }
            auVar17._8_8_ = uVar9;
            auVar17._0_8_ = 1;
            return auVar17;
          }
        }
      }
      goto LAB_00154c9c;
    }
    if (uVar3 != 0) {
      auVar14._8_8_ = *(undefined8 *)(param_1 + 4);
      auVar14._0_8_ = 1;
      return auVar14;
    }
    if (param_1[0x12] == 0) goto LAB_00154c9c;
    uVar3 = param_1[6];
  }
  else {
    if (uVar3 == 0x1b) {
      uVar3 = param_1[0x18];
      uVar8 = (ulong)uVar3;
      lVar12 = 0;
      if (uVar3 != 0) {
        puVar11 = *(uint **)(param_1 + 0x14);
        lVar12 = 0;
        puVar1 = puVar11 + (ulong)uVar3 * 4;
        uVar8 = 0;
        do {
          if (*puVar11 < param_3) {
            lVar13 = (ulong)*puVar11 * 0x10;
            uVar3 = *(uint *)(param_2 + lVar13);
            lVar13 = *(long *)(param_2 + lVar13 + 8);
            if ((int)uVar8 == 0) {
              uVar8 = (ulong)uVar3;
              lVar12 = lVar13;
            }
            else if (uVar3 != 0) {
              if (((int)uVar8 != 2 && uVar3 != 2) && (lVar12 == lVar13)) goto LAB_00154d98;
              lVar12 = 0;
              uVar8 = 2;
              break;
            }
            if ((int)uVar8 == 2) break;
          }
LAB_00154d98:
          puVar11 = puVar11 + 4;
        } while (puVar11 != puVar1);
      }
      auVar15._8_8_ = lVar12;
      auVar15._0_8_ = uVar8;
      return auVar15;
    }
    if ((((uVar3 != 0x1c) || (param_1[0x12] < 3)) || (param_3 <= param_1[6])) ||
       (lVar12 = (ulong)param_1[6] * 0x10, *(int *)(param_2 + lVar12) != 1)) goto LAB_00154c9c;
    if (*(long *)(param_2 + lVar12 + 8) == 0) {
      uVar3 = param_1[0xe];
    }
    else {
      uVar3 = param_1[10];
    }
  }
  if (uVar3 < param_3) {
    auVar16._0_8_ = *(undefined8 *)(param_2 + (ulong)uVar3 * 0x10);
    auVar16._8_8_ = *(undefined8 *)(param_2 + (ulong)uVar3 * 0x10 + 8);
    return auVar16;
  }
LAB_00154c9c:
  return ZEXT816(2);
}

