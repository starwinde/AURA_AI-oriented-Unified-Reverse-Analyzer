
byte FUN_001109d0(byte *param_1,long *param_2,ulong *param_3,char *param_4)

{
  uint uVar1;
  long *plVar2;
  ushort uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  bool bVar30;
  bool bVar31;
  bool bVar32;
  int *piVar33;
  ushort **ppuVar34;
  char *pcVar35;
  ulong uVar36;
  int iVar37;
  int iVar38;
  byte bVar39;
  byte *pbVar40;
  ulong uVar41;
  ulong uVar42;
  byte bVar43;
  byte bVar44;
  long lStack_60;
  long local_58;
  
  plVar2 = &lStack_60;
  if (param_2 != (long *)0x0) {
    plVar2 = param_2;
  }
  local_58 = *(long *)PTR___stack_chk_guard_0013ffd0;
  piVar33 = __errno_location();
  *piVar33 = 0;
  uVar41 = (ulong)*param_1;
  ppuVar34 = __ctype_b_loc();
  uVar3 = (*ppuVar34)[uVar41];
  pbVar40 = param_1;
  while ((uVar3 >> 0xd & 1) != 0) {
    pbVar40 = pbVar40 + 1;
    uVar41 = (ulong)*pbVar40;
    uVar3 = (*ppuVar34)[uVar41];
  }
  if ((int)uVar41 != 0x2d) {
    uVar41 = __isoc23_strtoumax(param_1,plVar2,0);
    pbVar40 = (byte *)*plVar2;
    if (param_1 != pbVar40) {
      if (*piVar33 == 0) {
        bVar44 = 0;
      }
      else {
        bVar44 = 1;
        if (*piVar33 != 0x22) goto LAB_00110aec;
      }
      bVar39 = *pbVar40;
      bVar43 = bVar44;
      if (bVar39 != 0) {
        pcVar35 = strchr(param_4,(uint)bVar39);
        uVar42 = uVar41;
        if (pcVar35 != (char *)0x0) goto LAB_00110b14;
code_r0x00110b90:
        bVar43 = bVar44 | 2;
        *param_3 = uVar41;
        goto LAB_00110aa0;
      }
LAB_00110a98:
      *param_3 = uVar41;
      goto LAB_00110aa0;
    }
    bVar39 = *pbVar40;
    if (bVar39 != 0) {
      bVar44 = 0;
      uVar42 = 1;
      pcVar35 = strchr(param_4,(uint)bVar39);
      if (pcVar35 != (char *)0x0) {
LAB_00110b14:
        uVar1 = bVar39 - 0x45 & 0xff;
        if (((uVar1 < 0x30) && ((0x81440030b945U >> ((ulong)uVar1 & 0x3f) & 1) != 0)) &&
           (pcVar35 = strchr(param_4,0x30), pcVar35 != (char *)0x0)) {
          bVar43 = pbVar40[1];
          if (bVar43 == 0x44) {
            iVar37 = 2;
            uVar36 = 1000;
          }
          else if (bVar43 == 0x69) {
            uVar36 = 0x400;
            iVar37 = 3;
            if (pbVar40[2] != 0x42) {
              iVar37 = 1;
            }
          }
          else {
            uVar36 = 0x400;
            if (bVar43 == 0x42) {
              uVar36 = 1000;
            }
            iVar37 = 2;
            if (bVar43 != 0x42) {
              iVar37 = 1;
            }
          }
        }
        else {
          iVar37 = 1;
          uVar36 = 0x400;
        }
        uVar41 = uVar42;
        switch((uint)bVar39) {
        case 0x42:
          uVar41 = uVar42 << 10;
          if (uVar42 >> 0x36 != 0) {
            bVar44 = 1;
            uVar41 = 0xffffffffffffffff;
          }
          break;
        default:
          goto code_r0x00110b90;
        case 0x45:
          iVar38 = 6;
          bVar39 = 0;
          do {
            auVar13._8_8_ = 0;
            auVar13._0_8_ = uVar36;
            auVar26._8_8_ = 0;
            auVar26._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar13 * auVar26,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x47:
        case 0x67:
          auVar5._8_8_ = 0;
          auVar5._0_8_ = uVar36;
          auVar18._8_8_ = 0;
          auVar18._0_8_ = uVar42;
          uVar42 = uVar36 * uVar42;
          bVar31 = SUB168(auVar5 * auVar18,8) != 0;
          if (bVar31) {
            uVar42 = 0xffffffffffffffff;
          }
          auVar6._8_8_ = 0;
          auVar6._0_8_ = uVar36;
          auVar19._8_8_ = 0;
          auVar19._0_8_ = uVar42;
          uVar42 = uVar36 * uVar42;
          bVar32 = SUB168(auVar6 * auVar19,8) != 0;
          if (bVar32) {
            uVar42 = 0xffffffffffffffff;
          }
          auVar7._8_8_ = 0;
          auVar7._0_8_ = uVar36;
          auVar20._8_8_ = 0;
          auVar20._0_8_ = uVar42;
          uVar41 = uVar36 * uVar42;
          bVar30 = SUB168(auVar7 * auVar20,8) != 0;
          if (bVar30) {
            uVar41 = 0xffffffffffffffff;
          }
          bVar44 = bVar44 | (bVar30 || (bVar32 || bVar31));
          break;
        case 0x4b:
        case 0x6b:
          auVar4._8_8_ = 0;
          auVar4._0_8_ = uVar36;
          auVar17._8_8_ = 0;
          auVar17._0_8_ = uVar42;
          uVar41 = uVar36 * uVar42;
          if (SUB168(auVar4 * auVar17,8) != 0) {
            bVar44 = 1;
            uVar41 = 0xffffffffffffffff;
          }
          break;
        case 0x4d:
        case 0x6d:
          auVar8._8_8_ = 0;
          auVar8._0_8_ = uVar36;
          auVar21._8_8_ = 0;
          auVar21._0_8_ = uVar42;
          uVar42 = uVar36 * uVar42;
          bVar31 = SUB168(auVar8 * auVar21,8) != 0;
          if (bVar31) {
            uVar42 = 0xffffffffffffffff;
          }
          auVar9._8_8_ = 0;
          auVar9._0_8_ = uVar36;
          auVar22._8_8_ = 0;
          auVar22._0_8_ = uVar42;
          uVar41 = uVar36 * uVar42;
          bVar32 = SUB168(auVar9 * auVar22,8) != 0;
          if (bVar32) {
            uVar41 = 0xffffffffffffffff;
          }
          bVar44 = bVar44 | (bVar32 || bVar31);
          break;
        case 0x50:
          iVar38 = 5;
          bVar39 = 0;
          do {
            auVar14._8_8_ = 0;
            auVar14._0_8_ = uVar36;
            auVar27._8_8_ = 0;
            auVar27._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar14 * auVar27,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x51:
          iVar38 = 10;
          bVar39 = 0;
          do {
            auVar16._8_8_ = 0;
            auVar16._0_8_ = uVar36;
            auVar29._8_8_ = 0;
            auVar29._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar16 * auVar29,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x52:
          iVar38 = 9;
          bVar39 = 0;
          do {
            auVar15._8_8_ = 0;
            auVar15._0_8_ = uVar36;
            auVar28._8_8_ = 0;
            auVar28._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar15 * auVar28,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x54:
        case 0x74:
          iVar38 = 4;
          bVar39 = 0;
          do {
            auVar10._8_8_ = 0;
            auVar10._0_8_ = uVar36;
            auVar23._8_8_ = 0;
            auVar23._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar10 * auVar23,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x59:
          iVar38 = 8;
          bVar39 = 0;
          do {
            auVar11._8_8_ = 0;
            auVar11._0_8_ = uVar36;
            auVar24._8_8_ = 0;
            auVar24._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar11 * auVar24,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x5a:
          iVar38 = 7;
          bVar39 = 0;
          do {
            auVar12._8_8_ = 0;
            auVar12._0_8_ = uVar36;
            auVar25._8_8_ = 0;
            auVar25._0_8_ = uVar41;
            uVar41 = uVar36 * uVar41;
            if (SUB168(auVar12 * auVar25,8) != 0) {
              bVar39 = 1;
              uVar41 = 0xffffffffffffffff;
            }
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
          bVar44 = bVar44 | bVar39;
          break;
        case 0x62:
          uVar41 = uVar42 << 9;
          if (uVar42 >> 0x37 != 0) {
            bVar44 = 1;
            uVar41 = 0xffffffffffffffff;
          }
          break;
        case 99:
          break;
        case 0x77:
          uVar41 = uVar42 << 1;
          if ((long)uVar42 < 0) {
            bVar44 = 1;
            uVar41 = 0xffffffffffffffff;
          }
        }
        *plVar2 = (long)(pbVar40 + iVar37);
        bVar43 = bVar44 | 2;
        if (pbVar40[iVar37] == 0) {
          bVar43 = bVar44;
        }
        goto LAB_00110a98;
      }
    }
  }
LAB_00110aec:
  bVar43 = 4;
LAB_00110aa0:
  if (local_58 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return bVar43;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_58 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

