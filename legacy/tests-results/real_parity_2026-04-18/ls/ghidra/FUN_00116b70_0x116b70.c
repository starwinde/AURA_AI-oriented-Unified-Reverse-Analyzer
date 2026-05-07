
undefined1  [16] FUN_00116b70(undefined1 param_1 [16],undefined1 param_2 [16])

{
  uint uVar1;
  undefined1 auVar2 [16];
  bool bVar3;
  byte bVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  ulong uVar25;
  ulong uVar26;
  ulong uVar27;
  undefined1 auVar28 [16];
  
  uVar23 = param_2._8_8_;
  uVar7 = param_2._0_8_;
  uVar12 = param_1._8_8_;
  uVar11 = param_1._0_8_;
  uVar13 = fpcr;
  uVar21 = uVar12 & 0xffffffffffff;
  uVar19 = uVar12 >> 0x30 & 0x7fff;
  iVar16 = (int)uVar19;
  uVar1 = param_1._12_4_;
  uVar18 = param_2._12_4_;
  if (iVar16 == 0) {
    if (uVar11 == 0 && uVar21 == 0) {
      uVar11 = 0;
      uVar10 = 4;
      lVar14 = 0;
      lVar24 = 1;
      bVar4 = false;
      uVar21 = 0;
      goto LAB_00116bd4;
    }
    if (uVar21 == 0) {
      uVar19 = LZCOUNT(uVar11) + 0x31;
      iVar16 = (int)uVar19;
      lVar14 = LZCOUNT(uVar11) + 0x40;
      if (uVar19 < 0x3d) goto LAB_00116f2c;
      uVar21 = uVar11 << ((ulong)(iVar16 - 0x3d) & 0x3f);
      uVar11 = 0;
    }
    else {
      lVar14 = LZCOUNT(uVar21);
      iVar16 = (int)lVar14 + -0xf;
LAB_00116f2c:
      uVar21 = uVar11 >> ((ulong)(0x3d - iVar16) & 0x3f) | uVar21 << ((ulong)(iVar16 + 3) & 0x3f);
      uVar11 = uVar11 << ((ulong)(iVar16 + 3) & 0x3f);
    }
    uVar10 = 0;
    lVar14 = -0x3fef - lVar14;
    lVar24 = 0;
    bVar4 = false;
LAB_00116bd4:
    uVar6 = uVar23 >> 0x30 & 0x7fff;
    uVar19 = uVar21;
    if ((int)uVar6 != 0) goto LAB_00116be8;
LAB_00116ea0:
    uVar19 = uVar23 & 0xffffffffffff;
    if (uVar7 == 0 && uVar19 == 0) {
      uVar10 = uVar10 | 1;
      lVar9 = 1;
      goto LAB_00116eb0;
    }
    if (uVar19 == 0) {
      uVar23 = LZCOUNT(uVar7) + 0x31;
      iVar16 = (int)uVar23;
      lVar9 = LZCOUNT(uVar7) + 0x40;
      if (uVar23 < 0x3d) goto LAB_00116fdc;
      uVar23 = uVar7 << ((ulong)(iVar16 - 0x3d) & 0x3f);
      uVar7 = 0;
    }
    else {
      lVar9 = LZCOUNT(uVar19);
      iVar16 = (int)lVar9 + -0xf;
LAB_00116fdc:
      uVar23 = uVar7 >> ((ulong)(0x3d - iVar16) & 0x3f) | uVar19 << ((ulong)(iVar16 + 3) & 0x3f);
      uVar7 = uVar7 << ((ulong)(iVar16 + 3) & 0x3f);
    }
    lVar14 = lVar9 + lVar14 + 0x3fef;
LAB_00116c10:
    uVar18 = (uVar1 ^ uVar18) >> 0x1f;
    uVar19 = (ulong)uVar18;
    if ((uVar10 - 1 < 0xc) && ((uint)(uVar10 - 1) < 0xc)) {
      uVar17 = uVar18;
      switch(uVar10) {
      case 4:
code_r0x00117108:
        uVar5 = 0;
        uVar21 = 0;
        uVar7 = 0;
        break;
      case 8:
code_r0x00117198:
LAB_0011719c:
        uVar5 = 0x7fff;
        uVar21 = 0;
        uVar7 = 0;
        uVar18 = uVar17;
        break;
      case 0xc:
code_r0x00117120:
        lVar9 = lVar24;
        uVar15 = uVar21;
        uVar7 = uVar11;
        uVar23 = uVar12;
LAB_0011712c:
        uVar19 = uVar23 >> 0x3f;
        uVar17 = (uint)(uVar23 >> 0x3f);
        uVar18 = uVar17;
        if (lVar9 != 1) {
          if (lVar9 == 0) goto code_r0x00116e0c;
          if (lVar9 != 2) goto LAB_00116fa8;
          goto LAB_0011719c;
        }
        uVar5 = 0;
        uVar21 = 0;
        uVar7 = 0;
      }
LAB_00116e48:
      uVar21 = uVar21 | (ulong)(uVar5 | uVar18 << 0xf) << 0x30;
      if (bVar4 == 0) {
        auVar28._8_8_ = uVar21;
        auVar28._0_8_ = uVar7;
        return auVar28;
      }
      goto LAB_00116f00;
    }
    if ((uVar23 < uVar21) || (uVar21 == uVar23 && uVar7 <= uVar11)) {
      uVar12 = uVar11 << 0x3f;
      uVar11 = uVar11 >> 1 | uVar21 << 0x3f;
      uVar21 = uVar21 >> 1;
    }
    else {
      lVar14 = lVar14 + -1;
      uVar12 = 0;
    }
    uVar20 = uVar23 >> 0x14 & 0xffffffff;
    uVar10 = uVar7 >> 0x34 | uVar23 << 0xc;
    uVar22 = uVar7 >> 0x34 | uVar23 << 0xc & 0xffffffff;
    uVar6 = uVar7 * 0x1000;
    uVar23 = 0;
    if (uVar20 != 0) {
      uVar23 = uVar21 / uVar20;
    }
    uVar8 = uVar22 * uVar23;
    uVar21 = uVar11 >> 0x20 | uVar21 - uVar23 * uVar20 << 0x20;
    uVar15 = uVar23;
    if (uVar21 <= uVar8 && uVar8 - uVar21 != 0) {
      bVar3 = CARRY8(uVar10,uVar21);
      uVar21 = uVar10 + uVar21;
      uVar15 = uVar23 - 1;
      if ((!bVar3 && uVar21 <= uVar8) && (bVar3 || uVar8 - uVar21 != 0)) {
        uVar15 = uVar23 - 2;
        uVar21 = uVar21 + uVar10;
      }
    }
    uVar23 = 0;
    if (uVar20 != 0) {
      uVar23 = (uVar21 - uVar8) / uVar20;
    }
    uVar26 = uVar22 * uVar23;
    uVar21 = uVar11 & 0xffffffff | (uVar21 - uVar8) - uVar23 * uVar20 << 0x20;
    uVar11 = uVar23;
    if (uVar21 <= uVar26 && uVar26 - uVar21 != 0) {
      bVar3 = CARRY8(uVar10,uVar21);
      uVar21 = uVar10 + uVar21;
      uVar11 = uVar23 - 1;
      if ((!bVar3 && uVar21 <= uVar26) && (bVar3 || uVar26 - uVar21 != 0)) {
        uVar11 = uVar23 - 2;
        uVar21 = uVar21 + uVar10;
      }
    }
    uVar27 = uVar11 | uVar15 << 0x20;
    uVar25 = uVar6 & 0xffffffff;
    uVar8 = uVar6 >> 0x20;
    uVar21 = uVar21 - uVar26;
    uVar15 = (uVar11 & 0xffffffff) * uVar25;
    uVar26 = (uVar27 >> 0x20) * uVar25;
    lVar9 = (uVar27 >> 0x20) * uVar8;
    uVar23 = uVar26 + uVar8 * (uVar11 & 0xffffffff) + (uVar15 >> 0x20);
    lVar24 = lVar9 + 0x100000000;
    if (uVar26 < uVar23 || uVar26 - uVar23 == 0) {
      lVar24 = lVar9;
    }
    uVar11 = (uVar15 & 0xffffffff) + (uVar23 << 0x20);
    uVar23 = lVar24 + (uVar23 >> 0x20);
    if ((uVar21 < uVar23) || (uVar15 = uVar27, uVar21 == uVar23 && uVar12 < uVar11)) {
      bVar3 = CARRY8(uVar12,uVar6);
      uVar12 = uVar12 + uVar6;
      uVar15 = uVar27 - 1;
      uVar21 = uVar21 + uVar10 + (ulong)bVar3;
      if (((uVar10 < uVar21) || (!bVar3 && uVar10 == uVar21)) &&
         ((uVar21 < uVar23 || (uVar23 == uVar21 && uVar12 < uVar11)))) {
        bVar3 = CARRY8(uVar6,uVar12);
        uVar12 = uVar6 + uVar12;
        uVar15 = uVar27 - 2;
        uVar21 = uVar21 + uVar10 + (ulong)bVar3;
      }
    }
    uVar21 = uVar21 - (uVar23 + (uVar12 < uVar11));
    if (uVar10 == uVar21) {
      lVar24 = lVar14 + 0x3fff;
      uVar7 = 0xffffffffffffffff;
      if (-0x3fff < lVar14) {
LAB_00117144:
        uVar21 = uVar13 & 0xc00000;
        bVar4 = bVar4 | 0x10;
        if (uVar21 == 0x400000) {
          if (uVar19 == 0) {
LAB_00117370:
            bVar3 = 0xfffffffffffffff7 < uVar7;
            uVar7 = uVar7 + 8;
            if (bVar3) {
              uVar15 = uVar15 + 1;
            }
          }
        }
        else if (uVar21 == 0x800000) {
          if (uVar19 != 0) goto LAB_00117370;
        }
        else if (((uVar21 == 0) && ((uVar7 & 0xf) != 4)) &&
                (bVar3 = 0xfffffffffffffffb < uVar7, uVar7 = uVar7 + 4, bVar3)) {
          uVar15 = uVar15 + 1;
        }
LAB_00116e24:
        if ((uVar15 >> 0x34 & 1) != 0) {
          uVar15 = uVar15 & 0xffefffffffffffff;
          lVar24 = lVar14 + 0x4000;
        }
        if (lVar24 < 0x7fff) {
          uVar5 = (uint)lVar24 & 0x7fff;
          uVar21 = uVar15 >> 3 & 0xffffffffffff;
          uVar7 = uVar7 >> 3 | uVar15 << 0x3d;
          goto LAB_00116e48;
        }
        uVar13 = uVar13 & 0xc00000;
        uVar5 = 0x7ffe;
        if (uVar13 == 0x400000) {
          bVar3 = uVar19 == 0;
          if (bVar3) {
            uVar5 = 0x7fff;
          }
          uVar21 = 0;
          if (!bVar3) {
            uVar21 = 0xffffffffffff;
          }
          uVar7 = -(ulong)!bVar3;
        }
        else if (uVar13 == 0x800000) {
          bVar3 = uVar19 == 0;
          if (!bVar3) {
            uVar5 = 0x7fff;
          }
          uVar21 = 0;
          if (bVar3) {
            uVar21 = 0xffffffffffff;
          }
          uVar7 = -(ulong)bVar3;
        }
        else if (uVar13 == 0) {
          uVar5 = 0x7fff;
          uVar21 = 0;
          uVar7 = 0;
        }
        else {
          uVar5 = 0x7ffe;
          uVar21 = 0xffffffffffff;
          uVar7 = 0xffffffffffffffff;
        }
        bVar4 = bVar4 | 0x14;
        goto LAB_00116ee8;
      }
      uVar21 = 1 - lVar24;
      if (0x74 < (long)uVar21) {
LAB_001173f0:
        bVar4 = bVar4 | 0x10;
        if ((uVar13 & 0xc00000) == 0x400000) {
          uVar7 = 1 - uVar19;
        }
        else {
          uVar7 = uVar19;
          if ((uVar13 & 0xc00000) != 0x800000) {
            uVar7 = 0;
          }
        }
        goto LAB_001172dc;
      }
    }
    else {
      uVar23 = 0;
      if (uVar20 != 0) {
        uVar23 = uVar21 / uVar20;
      }
      uVar27 = uVar22 * uVar23;
      uVar21 = uVar12 - uVar11 >> 0x20 | uVar21 - uVar23 * uVar20 << 0x20;
      uVar26 = uVar23;
      if (uVar21 <= uVar27 && uVar27 - uVar21 != 0) {
        bVar3 = CARRY8(uVar10,uVar21);
        uVar21 = uVar10 + uVar21;
        uVar26 = uVar23 - 1;
        if ((!bVar3 && uVar21 <= uVar27) && (bVar3 || uVar27 - uVar21 != 0)) {
          uVar26 = uVar23 - 2;
          uVar21 = uVar21 + uVar10;
        }
      }
      uVar23 = 0;
      if (uVar20 != 0) {
        uVar23 = (uVar21 - uVar27) / uVar20;
      }
      uVar22 = uVar22 * uVar23;
      uVar21 = uVar12 - uVar11 & 0xffffffff | (uVar21 - uVar27) - uVar23 * uVar20 << 0x20;
      uVar11 = uVar23;
      if (uVar21 <= uVar22 && uVar22 - uVar21 != 0) {
        bVar3 = CARRY8(uVar10,uVar21);
        uVar21 = uVar10 + uVar21;
        uVar11 = uVar23 - 1;
        if ((!bVar3 && uVar21 <= uVar22) && (bVar3 || uVar22 - uVar21 != 0)) {
          uVar11 = uVar23 - 2;
          uVar21 = uVar21 + uVar10;
        }
      }
      uVar12 = uVar11 | uVar26 << 0x20;
      uVar21 = uVar21 - uVar22;
      uVar20 = uVar25 * (uVar11 & 0xffffffff);
      uVar25 = (uVar12 >> 0x20) * uVar25;
      lVar9 = uVar8 * (uVar12 >> 0x20);
      uVar23 = uVar25 + uVar8 * (uVar11 & 0xffffffff) + (uVar20 >> 0x20);
      lVar24 = lVar9 + 0x100000000;
      if (uVar25 < uVar23 || uVar25 - uVar23 == 0) {
        lVar24 = lVar9;
      }
      uVar11 = (uVar20 & 0xffffffff) + (uVar23 << 0x20);
      uVar23 = lVar24 + (uVar23 >> 0x20);
      if ((uVar21 < uVar23) || (bVar3 = uVar11 != 0, bVar3 && uVar21 == uVar23)) {
        bVar3 = CARRY8(uVar10,uVar21);
        uVar21 = uVar10 + uVar21;
        if ((bVar3) || ((uVar23 <= uVar21 && (uVar21 != uVar23 || uVar11 <= uVar6)))) {
          bVar3 = uVar6 - uVar11 != 0;
          uVar12 = uVar12 - 1;
        }
        else {
          uVar12 = uVar12 - 2;
          if (uVar7 * 0x2000 <= uVar6 && uVar7 * -0x1000 != 0) {
            uVar10 = uVar10 + 1;
          }
          bVar3 = uVar11 != uVar7 * 0x2000;
          uVar21 = uVar21 + uVar10;
        }
      }
      uVar7 = (bVar3 || uVar21 != uVar23) | uVar12;
code_r0x00116e0c:
      lVar24 = lVar14 + 0x3fff;
      if (0 < lVar24) {
        if ((uVar7 & 7) != 0) goto LAB_00117144;
        goto LAB_00116e24;
      }
      uVar21 = 1 - lVar24;
      if (0x74 < (long)uVar21) {
        bVar3 = uVar7 != 0;
        uVar7 = 0;
        if (bVar3 || uVar15 != 0) goto LAB_001173f0;
LAB_001172dc:
        bVar4 = bVar4 | 8;
        uVar5 = 0;
        uVar21 = 0;
        goto LAB_00116ee8;
      }
    }
    iVar16 = (int)uVar21;
    if ((long)uVar21 < 0x40) {
      uVar23 = (ulong)(uVar7 << ((ulong)(0x40 - iVar16) & 0x3f) != 0);
      uVar11 = uVar15 << ((ulong)(0x40 - iVar16) & 0x3f) | uVar7 >> (uVar21 & 0x3f);
      uVar21 = uVar15 >> (uVar21 & 0x3f);
      uVar7 = uVar11 | uVar23;
      if ((uVar11 & 7) != 0 || uVar23 != 0) goto LAB_0011709c;
      if ((uVar21 >> 0x33 & 1) == 0) goto LAB_0011742c;
    }
    else {
      uVar23 = uVar7 | uVar15 << ((ulong)(0x80 - iVar16) & 0x3f);
      if (uVar21 == 0x40) {
        uVar23 = uVar7;
      }
      uVar15 = uVar15 >> ((ulong)(iVar16 - 0x40) & 0x3f);
      uVar7 = uVar23 != 0 | uVar15;
      uVar21 = 0;
      if ((ulong)(uVar23 != 0) == 0 && (uVar15 & 7) == 0) {
LAB_0011742c:
        uVar5 = 0;
        uVar7 = uVar7 >> 3 | uVar21 << 0x3d;
        uVar21 = uVar21 >> 3 & 0xffffffffffff;
        if (((uint)uVar13 >> 0xb & 1) == 0) goto LAB_00116e48;
        bVar4 = bVar4 | 8;
        goto LAB_00116ee8;
      }
      uVar21 = 0;
LAB_0011709c:
      uVar13 = uVar13 & 0xc00000;
      if (uVar13 == 0x400000) {
        if (uVar19 == 0) {
LAB_001174a0:
          bVar3 = 0xfffffffffffffff7 < uVar7;
          uVar7 = uVar7 + 8;
          if (bVar3) {
            uVar21 = uVar21 + 1;
          }
        }
      }
      else if (uVar13 == 0x800000) {
        if (uVar19 != 0) goto LAB_001174a0;
      }
      else if (((uVar13 == 0) && ((uVar7 & 0xf) != 4)) &&
              (bVar3 = 0xfffffffffffffffb < uVar7, uVar7 = uVar7 + 4, bVar3)) {
        uVar21 = uVar21 + 1;
      }
      if ((uVar21 >> 0x33 & 1) == 0) {
        bVar4 = bVar4 | 0x18;
        uVar7 = uVar7 >> 3 | uVar21 << 0x3d;
        uVar5 = 0;
        uVar21 = uVar21 >> 3 & 0xffffffffffff;
        goto LAB_00116ee8;
      }
    }
    bVar4 = bVar4 | 0x18;
    uVar5 = 1;
    uVar21 = 0;
    uVar7 = 0;
  }
  else {
    if (iVar16 != 0x7fff) {
      uVar21 = uVar11 >> 0x3d | uVar21 << 3 | 0x8000000000000;
      uVar11 = uVar11 << 3;
      uVar10 = 0;
      lVar14 = uVar19 - 0x3fff;
      lVar24 = 0;
      bVar4 = false;
      goto LAB_00116bd4;
    }
    if (uVar11 != 0 || uVar21 != 0) {
      bVar4 = uVar21 < 0x800000000000;
      uVar10 = 0xc;
      lVar14 = 0x7fff;
      lVar24 = 3;
      goto LAB_00116bd4;
    }
    uVar6 = uVar23 >> 0x30 & 0x7fff;
    uVar11 = 0;
    uVar10 = 8;
    lVar14 = 0x7fff;
    lVar24 = 2;
    bVar4 = false;
    uVar21 = 0;
    uVar19 = 0;
    if ((int)uVar6 == 0) goto LAB_00116ea0;
LAB_00116be8:
    uVar15 = uVar23 & 0xffffffffffff;
    uVar17 = uVar18 >> 0x1f;
    uVar21 = uVar19;
    if ((int)uVar6 != 0x7fff) {
      uVar23 = uVar7 >> 0x3d | uVar15 << 3 | 0x8000000000000;
      lVar14 = lVar14 - (uVar6 - 0x3fff);
      uVar7 = uVar7 << 3;
      goto LAB_00116c10;
    }
    lVar14 = lVar14 + -0x7fff;
    if (uVar7 != 0 || uVar15 != 0) {
      uVar18 = (uVar1 ^ uVar18) >> 0x1f;
      uVar23 = (uVar10 | 3) - 4;
      if (uVar15 < 0x800000000000) {
        bVar4 = true;
      }
      if (uVar23 < 0xc) {
        switch(uVar23 & 0xffffffff) {
        case 0:
        case 2:
          goto code_r0x00117108;
        case 1:
        case 6:
          goto code_r0x0011717c;
        default:
          goto code_r0x00116fa0;
        case 4:
        case 5:
          uVar21 = 0;
          uVar7 = 0;
          uVar5 = 0x7fff;
          break;
        case 8:
        case 9:
        case 10:
          goto code_r0x00117120;
        case 0xb:
          if (((uVar19 >> 0x2f & 1) == 0) || (uVar15 >> 0x2f != 0)) {
            uVar21 = uVar19 & 0xffffffffffff | 0x800000000000;
            uVar5 = 0x7fff;
            uVar7 = uVar11;
            uVar18 = uVar1 >> 0x1f;
          }
          else {
            uVar21 = uVar15 | 0x800000000000;
            uVar5 = 0x7fff;
            uVar18 = uVar17;
          }
        }
      }
      else {
code_r0x00116fa0:
LAB_00116fa8:
        uVar5 = 0x7fff;
        uVar21 = uVar15 & 0xffffffffffff | 0x800000000000;
        uVar18 = uVar17;
      }
      goto LAB_00116e48;
    }
    uVar10 = uVar10 | 2;
    lVar9 = 2;
LAB_00116eb0:
    uVar18 = (uVar1 ^ uVar18) >> 0x1f;
    if (uVar10 - 2 < 0xd) {
      uVar17 = uVar18;
      switch(uVar10 - 2 & 0xffffffff) {
      case 0:
      case 2:
      case 4:
        goto code_r0x00117108;
      case 1:
      case 5:
      case 9:
        uVar15 = 0;
        uVar7 = 0;
        goto LAB_0011712c;
      case 3:
      case 8:
code_r0x0011717c:
        uVar18 = 0;
        uVar21 = 0xffffffffffff;
        uVar7 = 0xffffffffffffffff;
        bVar4 = 1;
        uVar5 = 0x7fff;
        goto LAB_00116e48;
      case 6:
      case 7:
        goto code_r0x00117198;
      case 10:
      case 0xb:
      case 0xc:
        goto code_r0x00117120;
      default:
        break;
      }
    }
    bVar4 = bVar4 | 2;
    uVar5 = 0x7fff;
    uVar21 = 0;
    uVar7 = 0;
  }
LAB_00116ee8:
  uVar21 = uVar21 | (ulong)(uVar5 | uVar18 << 0xf) << 0x30;
LAB_00116f00:
  FUN_001180e0(bVar4);
  auVar2._8_8_ = uVar21;
  auVar2._0_8_ = uVar7;
  return auVar2;
}

