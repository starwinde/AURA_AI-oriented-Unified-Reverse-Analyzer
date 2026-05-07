
undefined1  [16] FUN_00117730(undefined1 param_1 [16],undefined1 param_2 [16])

{
  ulong uVar1;
  undefined1 auVar2 [16];
  bool bVar3;
  byte bVar4;
  uint uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uVar16;
  long lVar17;
  int iVar18;
  ulong uVar19;
  long lVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  ulong uVar24;
  ulong uVar25;
  ulong uVar26;
  ulong uVar27;
  undefined1 auVar28 [16];
  
  uVar21 = param_2._8_8_;
  uVar11 = param_2._0_8_;
  uVar6 = param_1._8_8_;
  uVar14 = param_1._0_8_;
  uVar15 = fpcr;
  uVar8 = uVar6 >> 0x3f;
  uVar12 = uVar6 & 0xffffffffffff;
  uVar6 = uVar6 >> 0x30 & 0x7fff;
  iVar18 = (int)uVar6;
  if (iVar18 == 0) {
    if (uVar14 == 0 && uVar12 == 0) {
      uVar12 = 0;
      uVar16 = 4;
      lVar9 = 0;
      lVar17 = 1;
      bVar4 = false;
      uVar6 = 0;
      goto LAB_00117794;
    }
    if (uVar12 == 0) {
      uVar6 = LZCOUNT(uVar14) + 0x31;
      iVar18 = (int)uVar6;
      lVar9 = LZCOUNT(uVar14) + 0x40;
      if (uVar6 < 0x3d) goto LAB_00117b00;
      uVar6 = 0;
      uVar12 = uVar14 << ((ulong)(iVar18 - 0x3d) & 0x3f);
    }
    else {
      lVar9 = LZCOUNT(uVar12);
      iVar18 = (int)lVar9 + -0xf;
LAB_00117b00:
      uVar12 = uVar14 >> ((ulong)(0x3d - iVar18) & 0x3f) | uVar12 << ((ulong)(iVar18 + 3) & 0x3f);
      uVar6 = uVar14 << ((ulong)(iVar18 + 3) & 0x3f);
    }
    uVar16 = 0;
    lVar9 = -0x3fef - lVar9;
    lVar17 = 0;
    bVar4 = false;
LAB_00117794:
    lVar7 = lVar9;
    uVar14 = uVar6;
    if ((uVar21 & 0x7fff000000000000) != 0) goto LAB_001177ac;
LAB_00117a28:
    uVar14 = uVar21 & 0xffffffffffff;
    if (uVar11 == 0 && uVar14 == 0) {
      uVar16 = uVar16 | 1;
      uVar10 = 0;
      uVar11 = 0;
      lVar20 = 1;
      goto LAB_001177d8;
    }
    if (uVar14 == 0) {
      uVar10 = LZCOUNT(uVar11) + 0x31;
      iVar18 = (int)uVar10;
      lVar7 = LZCOUNT(uVar11) + 0x40;
      if (uVar10 < 0x3d) goto LAB_00117a3c;
      uVar10 = uVar11 << ((ulong)(iVar18 - 0x3d) & 0x3f);
      uVar11 = 0;
    }
    else {
      lVar7 = LZCOUNT(uVar14);
      iVar18 = (int)lVar7 + -0xf;
LAB_00117a3c:
      uVar10 = uVar11 >> ((ulong)(0x3d - iVar18) & 0x3f) | uVar14 << ((ulong)(iVar18 + 3) & 0x3f);
      uVar11 = uVar11 << ((ulong)(iVar18 + 3) & 0x3f);
    }
    lVar7 = lVar9 - lVar7;
    lVar9 = lVar7 + -0x3fef;
    lVar20 = 0;
    lVar7 = lVar7 + -0x3fee;
    uVar22 = uVar12;
    uVar14 = uVar6;
    uVar23 = uVar8;
    if (uVar16 < 0xb) goto LAB_001177e4;
LAB_00117a7c:
    uVar11 = uVar6;
    uVar10 = uVar22;
    lVar9 = lVar7;
    uVar8 = uVar23;
    if (lVar17 == 2) {
      uVar5 = 0x7fff;
      uVar12 = 0;
      uVar14 = 0;
    }
    else if (lVar17 == 3) {
LAB_00117e98:
      uVar5 = 0x7fff;
      uVar12 = uVar10 & 0xffffffffffff | 0x800000000000;
      uVar14 = uVar11;
      uVar8 = uVar23;
    }
    else {
      uVar19 = uVar23;
      if (lVar17 != 1) goto LAB_00117980;
      uVar5 = 0;
      uVar12 = 0;
      uVar14 = 0;
    }
  }
  else {
    if (iVar18 != 0x7fff) {
      uVar12 = uVar14 >> 0x3d | uVar12 << 3 | 0x8000000000000;
      lVar9 = uVar6 - 0x3fff;
      uVar16 = 0;
      lVar17 = 0;
      bVar4 = false;
      uVar6 = uVar14 << 3;
      goto LAB_00117794;
    }
    if (uVar14 != 0 || uVar12 != 0) {
      uVar16 = 0xc;
      bVar4 = uVar12 < 0x800000000000;
      lVar9 = 0x7fff;
      lVar17 = 3;
      uVar6 = uVar14;
      goto LAB_00117794;
    }
    uVar12 = 0;
    uVar16 = 8;
    lVar9 = 0x7fff;
    lVar17 = 2;
    bVar4 = false;
    uVar6 = 0;
    uVar14 = 0;
    lVar7 = lVar9;
    if ((uVar21 & 0x7fff000000000000) == 0) goto LAB_00117a28;
LAB_001177ac:
    uVar5 = param_2._14_2_ & 0x7fff;
    uVar10 = uVar21 & 0xffffffffffff;
    uVar23 = uVar21 >> 0x3f;
    uVar6 = uVar14;
    if (uVar5 != 0x7fff) {
      uVar10 = uVar11 >> 0x3d | uVar10 << 3 | 0x8000000000000;
      lVar9 = ((ulong)uVar5 - 0x3fff) + lVar7;
      uVar11 = uVar11 << 3;
      lVar20 = 0;
LAB_001177d8:
      lVar7 = lVar9 + 1;
      uVar22 = uVar12;
      uVar14 = uVar6;
      uVar23 = uVar8;
      if (10 < uVar16) goto LAB_00117a7c;
LAB_001177e4:
      uVar19 = (ulong)((param_1._12_4_ ^ param_2._12_4_) >> 0x1f);
      if (2 < uVar16) goto LAB_001177f4;
      uVar22 = uVar10;
      uVar6 = uVar11;
      lVar17 = lVar20;
      uVar23 = uVar19;
      if (uVar16 - 1 < 2) goto LAB_00117a7c;
LAB_00117820:
      uVar16 = uVar11 & 0xffffffff;
      uVar22 = uVar14 >> 0x20;
      uVar11 = uVar11 >> 0x20;
      uVar14 = uVar14 & 0xffffffff;
      uVar21 = uVar10 & 0xffffffff;
      uVar10 = uVar10 >> 0x20;
      uVar24 = uVar22 * uVar16;
      uVar23 = uVar22 * uVar21;
      uVar27 = uVar12 >> 0x20;
      uVar12 = uVar12 & 0xffffffff;
      uVar8 = uVar24 + uVar11 * uVar14 + (uVar16 * uVar14 >> 0x20);
      uVar6 = uVar23 + uVar10 * uVar14 + (uVar14 * uVar21 >> 0x20);
      uVar26 = uVar27 * uVar16;
      uVar25 = uVar27 * uVar21;
      lVar17 = uVar22 * uVar11 + 0x100000000;
      if (uVar24 < uVar8 || uVar24 - uVar8 == 0) {
        lVar17 = uVar22 * uVar11;
      }
      uVar24 = (uVar14 * uVar21 & 0xffffffff) + (uVar6 << 0x20);
      uVar1 = uVar26 + uVar11 * uVar12 + (uVar16 * uVar12 >> 0x20);
      uVar13 = uVar25 + uVar10 * uVar12 + (uVar12 * uVar21 >> 0x20);
      lVar20 = uVar22 * uVar10 + 0x100000000;
      if (uVar23 < uVar6 || uVar23 - uVar6 == 0) {
        lVar20 = uVar22 * uVar10;
      }
      uVar6 = lVar20 + (uVar6 >> 0x20);
      lVar20 = uVar11 * uVar27 + 0x100000000;
      if (uVar26 < uVar1 || uVar26 - uVar1 == 0) {
        lVar20 = uVar11 * uVar27;
      }
      uVar11 = (uVar12 * uVar21 & 0xffffffff) + (uVar13 << 0x20);
      uVar21 = uVar24 + (uVar8 >> 0x20) + lVar17;
      lVar17 = uVar10 * uVar27 + 0x100000000;
      if (uVar25 < uVar13 || uVar25 - uVar13 == 0) {
        lVar17 = uVar10 * uVar27;
      }
      uVar10 = uVar11 + uVar6;
      uVar23 = (ulong)(uVar21 < uVar24);
      uVar22 = uVar10 + uVar23;
      uVar12 = (uVar16 * uVar12 & 0xffffffff) + (uVar1 << 0x20);
      uVar13 = uVar13 >> 0x20;
      if (CARRY8(uVar11,uVar6) || CARRY8(uVar10,uVar23)) {
        uVar13 = uVar13 + 1;
      }
      uVar11 = lVar20 + (uVar1 >> 0x20);
      uVar6 = uVar21 + uVar12;
      uVar10 = (ulong)CARRY8(uVar21,uVar12);
      uVar12 = uVar22 + uVar11;
      uVar21 = uVar12 + uVar10;
      if (CARRY8(uVar22,uVar11) || CARRY8(uVar12,uVar10)) {
        lVar17 = lVar17 + 1;
      }
      uVar12 = (ulong)((uVar16 * uVar14 & 0xffffffff) + (uVar8 << 0x20) != 0 ||
                      (uVar6 & 0x7ffffffffffff) != 0);
      uVar6 = uVar6 >> 0x33;
      uVar11 = uVar12 | uVar6 | uVar21 * 0x2000;
      uVar21 = uVar21 >> 0x33;
      uVar10 = uVar21 | (lVar17 + uVar13) * 0x2000;
      if ((lVar17 + uVar13 >> 0x27 & 1) != 0) {
        uVar11 = uVar12 | uVar6 & 1 | uVar11 >> 1 | uVar21 << 0x3f;
        uVar10 = uVar10 >> 1;
        lVar9 = lVar7;
      }
LAB_00117980:
      lVar17 = lVar9 + 0x3fff;
      uVar8 = uVar19;
      if (lVar17 < 1) {
        uVar12 = 1 - lVar17;
        if ((long)uVar12 < 0x75) {
          iVar18 = (int)uVar12;
          if ((long)uVar12 < 0x40) {
            uVar21 = (ulong)(uVar11 << ((ulong)(0x40 - iVar18) & 0x3f) != 0);
            uVar14 = uVar10 << ((ulong)(0x40 - iVar18) & 0x3f) | uVar11 >> (uVar12 & 0x3f);
            uVar6 = uVar10 >> (uVar12 & 0x3f);
            uVar11 = uVar14 | uVar21;
            if ((uVar14 & 7) != 0 || uVar21 != 0) goto LAB_00117c4c;
            if ((uVar6 >> 0x33 & 1) == 0) goto LAB_00117e40;
LAB_00117e00:
            bVar4 = bVar4 | 0x18;
            uVar11 = 1;
            uVar12 = 0;
            uVar14 = 0;
          }
          else {
            uVar14 = uVar11 | uVar10 << ((ulong)(0x80 - iVar18) & 0x3f);
            if (uVar12 == 0x40) {
              uVar14 = uVar11;
            }
            uVar10 = uVar10 >> ((ulong)(iVar18 - 0x40) & 0x3f);
            uVar11 = uVar14 != 0 | uVar10;
            uVar6 = 0;
            if ((ulong)(uVar14 != 0) == 0 && (uVar10 & 7) == 0) {
LAB_00117e40:
              uVar12 = uVar6 >> 3 & 0xffffffffffff;
              uVar14 = uVar11 >> 3 | uVar6 << 0x3d;
              uVar11 = 0;
              uVar5 = 0;
              if (((uint)uVar15 >> 0xb & 1) == 0) goto LAB_00117aa0;
              bVar4 = bVar4 | 8;
            }
            else {
              uVar6 = 0;
LAB_00117c4c:
              uVar15 = uVar15 & 0xc00000;
              if (uVar15 == 0x400000) {
                if (uVar19 == 0) {
LAB_00117eac:
                  bVar3 = 0xfffffffffffffff7 < uVar11;
                  uVar11 = uVar11 + 8;
                  if (bVar3) {
                    uVar6 = uVar6 + 1;
                  }
                }
              }
              else if (uVar15 == 0x800000) {
                if (uVar19 != 0) goto LAB_00117eac;
              }
              else if (((uVar15 == 0) && ((uVar11 & 0xf) != 4)) &&
                      (bVar3 = 0xfffffffffffffffb < uVar11, uVar11 = uVar11 + 4, bVar3)) {
                uVar6 = uVar6 + 1;
              }
              if ((uVar6 >> 0x33 & 1) != 0) goto LAB_00117e00;
              uVar12 = uVar6 >> 3 & 0xffffffffffff;
              uVar14 = uVar11 >> 3 | uVar6 << 0x3d;
              bVar4 = bVar4 | 0x18;
              uVar11 = 0;
            }
          }
        }
        else {
          uVar14 = 0;
          if (uVar11 != 0 || uVar10 != 0) {
            bVar4 = bVar4 | 0x10;
            uVar14 = 1 - uVar19;
            if (((uVar15 & 0xc00000) != 0x400000) &&
               (uVar14 = uVar19, (uVar15 & 0xc00000) != 0x800000)) {
              uVar14 = 0;
            }
          }
          bVar4 = bVar4 | 8;
          uVar12 = 0;
          uVar11 = 0;
        }
      }
      else {
        if ((uVar11 & 7) != 0) {
          uVar12 = uVar15 & 0xc00000;
          bVar4 = bVar4 | 0x10;
          if (uVar12 == 0x400000) {
            if (uVar19 == 0) {
LAB_00117e34:
              bVar3 = 0xfffffffffffffff7 < uVar11;
              uVar11 = uVar11 + 8;
              if (bVar3) {
                uVar10 = uVar10 + 1;
              }
            }
          }
          else if (uVar12 == 0x800000) {
            if (uVar19 != 0) goto LAB_00117e34;
          }
          else if (((uVar12 == 0) && ((uVar11 & 0xf) != 4)) &&
                  (bVar3 = 0xfffffffffffffffb < uVar11, uVar11 = uVar11 + 4, bVar3)) {
            uVar10 = uVar10 + 1;
          }
        }
        if ((uVar10 >> 0x34 & 1) != 0) {
          uVar10 = uVar10 & 0xffefffffffffffff;
          lVar17 = lVar9 + 0x4000;
        }
        if (lVar17 < 0x7fff) {
          uVar12 = uVar10 >> 3 & 0xffffffffffff;
          uVar5 = (uint)lVar17 & 0x7fff;
          uVar14 = uVar11 >> 3 | uVar10 << 0x3d;
          goto LAB_00117aa0;
        }
        uVar15 = uVar15 & 0xc00000;
        uVar5 = 0x7ffe;
        if (uVar15 == 0x400000) {
          bVar3 = uVar19 == 0;
          if (bVar3) {
            uVar5 = 0x7fff;
          }
          uVar11 = (ulong)uVar5;
          uVar12 = 0;
          if (!bVar3) {
            uVar12 = 0xffffffffffff;
          }
          uVar14 = -(ulong)!bVar3;
        }
        else if (uVar15 == 0x800000) {
          bVar3 = uVar19 == 0;
          if (!bVar3) {
            uVar5 = 0x7fff;
          }
          uVar11 = (ulong)uVar5;
          uVar12 = 0;
          if (bVar3) {
            uVar12 = 0xffffffffffff;
          }
          uVar14 = -(ulong)bVar3;
        }
        else if (uVar15 == 0) {
          uVar11 = 0x7fff;
          uVar12 = 0;
          uVar14 = 0;
        }
        else {
          uVar11 = 0x7ffe;
          uVar12 = 0xffffffffffff;
          uVar14 = 0xffffffffffffffff;
        }
        bVar4 = bVar4 | 0x14;
      }
      uVar12 = uVar12 | uVar11 << 0x30 | uVar19 << 0x3f;
      goto LAB_00117d08;
    }
    lVar9 = lVar7 + 0x7fff;
    if (uVar11 == 0 && uVar10 == 0) {
      uVar16 = uVar16 | 2;
      uVar10 = 0;
      uVar11 = 0;
      lVar20 = 2;
      goto LAB_001177d8;
    }
    uVar19 = (ulong)((param_1._12_4_ ^ param_2._12_4_) >> 0x1f);
    uVar16 = uVar16 | 3;
    lVar7 = lVar7 + 0x8000;
    if (uVar10 < 0x800000000000) {
      bVar4 = true;
    }
    lVar20 = 3;
    if (uVar16 < 0xb) {
LAB_001177f4:
      uVar16 = 1L << uVar16;
      uVar22 = uVar12;
      uVar6 = uVar14;
      uVar23 = uVar19;
      if ((uVar16 & 0x530) == 0) {
        if ((uVar16 & 0x240) != 0) {
          bVar4 = 1;
          uVar12 = 0xffffffffffff;
          uVar5 = 0x7fff;
          uVar14 = 0xffffffffffffffff;
          uVar8 = 0;
          goto LAB_00117aa0;
        }
        uVar22 = uVar10;
        uVar6 = uVar11;
        lVar17 = lVar20;
        uVar23 = uVar21 >> 0x3f;
        if ((uVar16 & 0x88) == 0) goto LAB_00117820;
      }
      goto LAB_00117a7c;
    }
    if (uVar16 != 0xf) goto LAB_00117e98;
    if (((uVar12 >> 0x2f & 1) == 0) || (uVar10 >> 0x2f != 0)) {
      uVar12 = uVar12 & 0xffffffffffff | 0x800000000000;
      uVar5 = 0x7fff;
    }
    else {
      uVar12 = uVar10 | 0x800000000000;
      uVar5 = 0x7fff;
      uVar14 = uVar11;
      uVar8 = uVar23;
    }
  }
LAB_00117aa0:
  uVar12 = uVar12 | (ulong)(uVar5 | (int)uVar8 << 0xf) << 0x30;
  if (bVar4 == 0) {
    auVar28._8_8_ = uVar12;
    auVar28._0_8_ = uVar14;
    return auVar28;
  }
LAB_00117d08:
  FUN_001180e0(bVar4);
  auVar2._8_8_ = uVar12;
  auVar2._0_8_ = uVar14;
  return auVar2;
}

