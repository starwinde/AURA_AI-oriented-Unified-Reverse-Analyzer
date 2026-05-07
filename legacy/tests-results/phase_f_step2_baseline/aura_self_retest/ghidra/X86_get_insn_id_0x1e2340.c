
void X86_get_insn_id(long param_1,uint *param_2,uint param_3)

{
  ulong uVar1;
  int iVar2;
  undefined1 uVar3;
  byte bVar4;
  uint uVar5;
  undefined8 *puVar6;
  short *psVar7;
  short *psVar8;
  short *psVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  byte bVar14;
  uint uVar15;
  long lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  ulong uVar13;
  
  uVar5 = 0x3b22;
  if (0x3b22 < param_3 - 0x92) {
    return;
  }
  uVar12 = 0x3b22;
  uVar11 = 0x1e23;
  uVar15 = 0;
  while( true ) {
    uVar12 = uVar12 >> 1;
    uVar13 = (ulong)uVar12;
    if (param_3 == uVar11) break;
    if (param_3 < uVar11) {
      uVar5 = uVar12 - 1;
      if (uVar5 < uVar15) {
        return;
      }
    }
    else {
      uVar15 = uVar12 + 1;
      if (uVar5 < uVar15) {
        return;
      }
    }
    uVar12 = uVar15 + uVar5;
    uVar11 = (uint)*(ushort *)(insns + (ulong)(uVar12 >> 1) * 0x50);
  }
  iVar2 = *(int *)(param_1 + 0x60);
  *param_2 = (uint)*(ushort *)(insns + uVar13 * 0x50 + 2);
  if (iVar2 == 0) {
    return;
  }
  puVar6 = *(undefined8 **)(param_2 + 0x3c);
  lVar16 = uVar13 * 0x50;
  uVar17 = *(undefined8 *)(insns + lVar16 + 0xe);
  *puVar6 = *(undefined8 *)(insns + lVar16 + 6);
  puVar6[1] = uVar17;
  puVar6[2] = *(undefined8 *)(insns + lVar16 + 0x16);
  uVar3 = count_positive();
  psVar7 = *(short **)(param_2 + 0x3c);
  *(undefined1 *)(psVar7 + 0x14) = uVar3;
  if (param_3 == 0x922) {
    if (*(int *)(param_1 + 4) == 8) goto LAB_001e2458;
    uVar5 = 2;
    psVar7[0x15] = 0x13;
    psVar7[0x16] = 0x18;
    *(undefined1 *)(psVar7 + 0x29) = 2;
  }
  else if ((param_3 == 0x923) && (*(int *)(param_1 + 4) != 8)) {
    uVar5 = 3;
    psVar7[0x15] = 0x13;
    psVar7[0x16] = 0x16;
    psVar7[0x17] = 0x18;
    *(undefined1 *)(psVar7 + 0x29) = 3;
  }
  else {
LAB_001e2458:
    uVar17 = *(undefined8 *)(insns + lVar16 + 0x1e);
    uVar19 = *(undefined8 *)(insns + lVar16 + 0x36);
    uVar18 = *(undefined8 *)(insns + lVar16 + 0x2e);
    *(undefined8 *)(psVar7 + 0x19) = *(undefined8 *)(insns + lVar16 + 0x26);
    *(undefined8 *)(psVar7 + 0x15) = uVar17;
    *(undefined8 *)(psVar7 + 0x21) = uVar19;
    *(undefined8 *)(psVar7 + 0x1d) = uVar18;
    *(undefined8 *)(psVar7 + 0x25) = *(undefined8 *)(insns + lVar16 + 0x3e);
    bVar4 = count_positive();
    uVar5 = (uint)bVar4;
    psVar7 = *(short **)(param_2 + 0x3c);
    *(byte *)(psVar7 + 0x29) = bVar4;
  }
  uVar15 = *param_2;
  if (0x1eb < uVar15) {
    if (uVar15 == 0x279) {
      sVar10 = 0x2f;
      if ((*(int *)(param_1 + 4) != 2) && (sVar10 = 0x1e, *(int *)(param_1 + 4) != 4)) {
        sVar10 = 0x2c;
      }
      *psVar7 = sVar10;
      *(undefined1 *)(psVar7 + 0x14) = 1;
      psVar7[0x15] = sVar10;
      *(undefined1 *)(psVar7 + 0x29) = 1;
    }
    else if ((uVar15 - 0x28d < 0x3b) &&
            ((0x78000000000000dU >> ((ulong)(uVar15 - 0x28d) & 0x3f) & 1) != 0)) {
      if (*(int *)(param_1 + 4) == 2) {
        if (*(byte *)(psVar7 + 0x14) != 0) {
          psVar8 = psVar7;
          do {
            if (*psVar8 == 0x17) {
              *psVar8 = 0xe;
              break;
            }
            psVar8 = psVar8 + 1;
          } while (psVar8 != psVar7 + (uint)*(byte *)(psVar7 + 0x14));
        }
        if (uVar5 != 0) {
          psVar9 = psVar7 + 0x15;
          psVar8 = psVar9 + uVar5;
          do {
            if (*psVar9 == 0x17) {
              *psVar9 = 0xe;
              break;
            }
            psVar9 = psVar9 + 1;
          } while (psVar8 != psVar9);
        }
      }
      else if (*(int *)(param_1 + 4) == 8) {
        if (*(byte *)(psVar7 + 0x14) != 0) {
          psVar8 = psVar7;
          do {
            if (*psVar8 == 0x17) {
              *psVar8 = 0x27;
              break;
            }
            psVar8 = psVar8 + 1;
          } while (psVar8 != psVar7 + (uint)*(byte *)(psVar7 + 0x14));
        }
        if (uVar5 != 0) {
          psVar9 = psVar7 + 0x15;
          psVar8 = psVar9 + uVar5;
          do {
            if (*psVar9 == 0x17) {
              *psVar9 = 0x27;
              break;
            }
            psVar9 = psVar9 + 1;
          } while (psVar9 != psVar8);
        }
      }
    }
    goto LAB_001e2650;
  }
  if (uVar15 < 0x1e5) {
    if (0x15b < uVar15) {
      if (2 < uVar15 - 0x15c) goto LAB_001e2650;
      iVar2 = *(int *)(param_1 + 4);
      if (iVar2 == 4) {
        sVar10 = 0x16;
LAB_001e2620:
        *psVar7 = sVar10;
        *(undefined1 *)(psVar7 + 0x14) = 1;
        psVar7[0x15] = sVar10;
        *(undefined1 *)(psVar7 + 0x29) = 1;
      }
      else {
        if (iVar2 == 8) {
          sVar10 = 0x26;
          goto LAB_001e2620;
        }
        sVar10 = 0xc;
        if (iVar2 == 2) goto LAB_001e2620;
      }
      if (uVar15 != 0x15c) {
        psVar7[1] = 0x19;
        *(undefined1 *)(psVar7 + 0x14) = 2;
      }
      goto LAB_001e2650;
    }
    if (0x157 < uVar15) {
      if (*(int *)(param_1 + 4) == 2) {
        if (*(byte *)(psVar7 + 0x14) != 0) {
          psVar8 = psVar7;
          do {
            if (*psVar8 == 0x1d) {
              *psVar8 = 0x2d;
              break;
            }
            psVar8 = psVar8 + 1;
          } while (psVar8 != psVar7 + (uint)*(byte *)(psVar7 + 0x14));
        }
        if (uVar5 != 0) {
          psVar9 = psVar7 + 0x15;
          psVar8 = psVar9 + uVar5;
          do {
            if (*psVar9 == 0x1d) goto LAB_001e28c4;
            psVar9 = psVar9 + 1;
          } while (psVar9 != psVar8);
        }
      }
      else if (*(int *)(param_1 + 4) == 8) {
        if (*(byte *)(psVar7 + 0x14) != 0) {
          psVar8 = psVar7;
          do {
            if (*psVar8 == 0x1d) {
              *psVar8 = 0x2b;
              break;
            }
            psVar8 = psVar8 + 1;
          } while (psVar8 != psVar7 + (uint)*(byte *)(psVar7 + 0x14));
        }
        if (uVar5 != 0) {
          psVar9 = psVar7 + 0x15;
          psVar8 = psVar9 + uVar5;
          do {
            if (*psVar9 == 0x1d) goto LAB_001e2518;
            psVar9 = psVar9 + 1;
          } while (psVar9 != psVar8);
        }
      }
      goto LAB_001e2650;
    }
    if (uVar15 < 0x6f) {
      if (uVar15 < 0x6c) goto LAB_001e2650;
    }
    else if (uVar15 != 0x70) goto LAB_001e2650;
  }
  else if ((0x53UL >> ((ulong)(uVar15 - 0x1e5) & 0x3f) & 1) == 0) goto LAB_001e2650;
  if (*(int *)(param_1 + 4) != 2) {
    if (*(int *)(param_1 + 4) != 8) goto LAB_001e2650;
    bVar4 = *(byte *)(psVar7 + 0x14);
    if (bVar4 == 0) {
      if (uVar5 == 0) goto LAB_001e2650;
LAB_001e27c0:
      psVar8 = psVar7 + 0x15;
      uVar15 = 0;
      do {
        uVar12 = uVar15 + 1;
        uVar15 = uVar12 & 0xff;
        if (*psVar8 == 0x17) {
          *psVar8 = 0x27;
          break;
        }
        psVar8 = psVar8 + 1;
      } while ((uVar12 & 0xff) < uVar5);
      if (bVar4 != 0) goto LAB_001e27f8;
    }
    else {
      psVar8 = psVar7;
      do {
        if (*psVar8 == 0x17) {
          *psVar8 = 0x27;
          break;
        }
        psVar8 = psVar8 + 1;
      } while (psVar8 != psVar7 + (uint)bVar4);
      if (uVar5 != 0) goto LAB_001e27c0;
LAB_001e27f8:
      bVar14 = 0;
      psVar8 = psVar7;
      do {
        bVar14 = bVar14 + 1;
        if (*psVar8 == 0x1d) {
          *psVar8 = 0x2b;
          break;
        }
        psVar8 = psVar8 + 1;
      } while (bVar14 < bVar4);
      if (uVar5 == 0) goto LAB_001e2650;
    }
    psVar9 = psVar7 + 0x15;
    psVar8 = psVar9 + uVar5;
    do {
      if (*psVar9 == 0x1d) goto LAB_001e2518;
      psVar9 = psVar9 + 1;
    } while (psVar9 != psVar8);
    goto LAB_001e2650;
  }
  bVar4 = *(byte *)(psVar7 + 0x14);
  if (bVar4 == 0) {
    if (uVar5 == 0) goto LAB_001e2650;
LAB_001e2974:
    psVar8 = psVar7 + 0x15;
    uVar15 = 0;
    do {
      uVar12 = uVar15 + 1;
      uVar15 = uVar12 & 0xff;
      if (*psVar8 == 0x17) {
        *psVar8 = 0xe;
        break;
      }
      psVar8 = psVar8 + 1;
    } while ((uVar12 & 0xff) < uVar5);
    if (bVar4 != 0) goto LAB_001e29ac;
  }
  else {
    psVar8 = psVar7;
    do {
      if (*psVar8 == 0x17) {
        *psVar8 = 0xe;
        break;
      }
      psVar8 = psVar8 + 1;
    } while (psVar8 != psVar7 + (uint)bVar4);
    if (uVar5 != 0) goto LAB_001e2974;
LAB_001e29ac:
    bVar14 = 0;
    psVar8 = psVar7;
    do {
      bVar14 = bVar14 + 1;
      if (*psVar8 == 0x1d) {
        *psVar8 = 0x2d;
        break;
      }
      psVar8 = psVar8 + 1;
    } while (bVar14 < bVar4);
    if (uVar5 == 0) goto LAB_001e2650;
  }
  psVar9 = psVar7 + 0x15;
  psVar8 = psVar9 + uVar5;
  do {
    if (*psVar9 == 0x1d) goto LAB_001e28c4;
    psVar9 = psVar9 + 1;
  } while (psVar8 != psVar9);
LAB_001e2650:
  *(undefined8 *)((long)psVar7 + 0x53) = *(undefined8 *)(insns + lVar16 + 0x46);
  bVar4 = count_positive8(lVar16 + 0x443b1e);
  lVar16 = *(long *)(param_2 + 0x3c);
  bVar14 = insns[uVar13 * 0x50 + 0x4e];
  *(byte *)(lVar16 + 0x5b) = bVar4;
  if (((bVar14 & 1) != 0) || ((insns[uVar13 * 0x50 + 0x4f] & 1) != 0)) {
    uVar1 = (ulong)bVar4;
    bVar4 = bVar4 + 1;
    *(undefined1 *)(lVar16 + uVar1 + 0x53) = 1;
    *(byte *)(lVar16 + 0x5b) = bVar4;
  }
  uVar5 = *(ushort *)(insns + uVar13 * 0x50) - 0x753 & 0xffff;
  if (((uVar5 < 5) && ((0x15UL >> ((ulong)uVar5 & 0x3f) & 1) != 0)) &&
     (*(long *)(lVar16 + 0xb0) == -0x4e)) {
    *(undefined1 *)(lVar16 + (ulong)bVar4 + 0x53) = 4;
    *(byte *)(lVar16 + 0x5b) = bVar4 + 1;
    return;
  }
  return;
LAB_001e2518:
  *psVar9 = 0x2b;
  goto LAB_001e2650;
LAB_001e28c4:
  *psVar9 = 0x2d;
  goto LAB_001e2650;
}

