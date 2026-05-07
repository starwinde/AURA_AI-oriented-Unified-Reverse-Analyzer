
undefined8 FUN_001f3c94(long param_1,long *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  byte *pbVar11;
  long lVar12;
  ulong uVar13;
  byte *pbVar14;
  byte *pbVar15;
  
  lVar12 = *param_2;
  lVar8 = param_2[2];
  uVar10 = lVar8 + 1;
  pbVar15 = (byte *)(lVar12 + uVar10);
  if (*(char *)(lVar12 + lVar8) == '\"') {
    uVar13 = param_2[1];
    lVar9 = 0;
    pbVar14 = pbVar15;
    while (uVar10 < uVar13) {
      if (*pbVar14 == 0x22) {
        if ((uVar10 < uVar13) &&
           (pbVar4 = (byte *)(*(code *)param_2[4])(pbVar14 + (-lVar9 - (lVar12 + lVar8)) + 1),
           pbVar2 = pbVar4, pbVar4 != (byte *)0x0)) goto joined_r0x001f3d68;
        break;
      }
      if (*pbVar14 == 0x5c) {
        pbVar14 = pbVar14 + 1;
        lVar9 = lVar9 + 1;
        if (uVar13 <= (ulong)((long)pbVar14 - lVar12)) break;
      }
      pbVar14 = pbVar14 + 1;
      uVar10 = (long)pbVar14 - lVar12;
    }
  }
  if (pbVar15 != (byte *)0x0) {
LAB_001f3ce4:
    param_2[2] = (long)pbVar15 - *param_2;
  }
  return 0;
joined_r0x001f3d68:
  if (pbVar14 <= pbVar15) {
    *pbVar2 = 0;
    lVar8 = *param_2;
    *(undefined4 *)(param_1 + 0x18) = 0x10;
    *(byte **)(param_1 + 0x20) = pbVar4;
    param_2[2] = (long)(pbVar14 + (1 - lVar8));
    return 1;
  }
  bVar5 = *pbVar15;
  if (bVar5 == 0x5c) {
    bVar5 = pbVar15[1];
    if (bVar5 == 0x6e) {
      pbVar11 = pbVar2 + 1;
      pbVar15 = pbVar15 + 2;
      bVar5 = 10;
    }
    else {
      uVar6 = (uint)bVar5;
      if (bVar5 < 0x6f) {
        if (bVar5 == 0x62) {
          pbVar11 = pbVar2 + 1;
          pbVar15 = pbVar15 + 2;
          bVar5 = 8;
        }
        else if (uVar6 < 99) {
          uVar6 = uVar6 - 0x22 & 0xff;
          if ((0x3a < uVar6) || ((0x400000000002001U >> ((ulong)uVar6 & 0x3f) & 1) == 0))
          goto LAB_001f3e38;
          pbVar11 = pbVar2 + 1;
          pbVar15 = pbVar15 + 2;
        }
        else {
          if (bVar5 != 0x66) goto LAB_001f3e38;
          pbVar11 = pbVar2 + 1;
          pbVar15 = pbVar15 + 2;
          bVar5 = 0xc;
        }
      }
      else if (bVar5 == 0x74) {
        pbVar11 = pbVar2 + 1;
        pbVar15 = pbVar15 + 2;
        bVar5 = 9;
      }
      else if (bVar5 == 0x75) {
        if ((long)pbVar14 - (long)pbVar15 < 6) goto LAB_001f3e38;
        bVar5 = pbVar15[2];
        uVar6 = bVar5 - 0x30;
        if ((uVar6 & 0xff) < 10) {
LAB_001f3ee8:
          bVar5 = pbVar15[3];
          iVar3 = uVar6 * 0x10;
          uVar6 = bVar5 - 0x30;
          if ((uVar6 & 0xff) < 10) {
            iVar3 = uVar6 + iVar3;
          }
          else {
            uVar6 = (uint)bVar5;
            if ((bVar5 - 0x41 & 0xff) < 6) {
              iVar3 = (uVar6 - 0x37) + iVar3;
            }
            else {
              if (5 < (uVar6 - 0x61 & 0xff)) goto LAB_001f41e0;
              iVar3 = (uVar6 - 0x57) + iVar3;
            }
          }
          bVar5 = pbVar15[4];
          iVar3 = iVar3 * 0x10;
          uVar6 = bVar5 - 0x30;
          if ((uVar6 & 0xff) < 10) {
            iVar3 = uVar6 + iVar3;
          }
          else {
            uVar6 = (uint)bVar5;
            if ((bVar5 - 0x41 & 0xff) < 6) {
              iVar3 = (uVar6 - 0x37) + iVar3;
            }
            else {
              if (5 < (uVar6 - 0x61 & 0xff)) goto LAB_001f41e0;
              iVar3 = (uVar6 - 0x57) + iVar3;
            }
          }
          bVar5 = pbVar15[5];
          iVar3 = iVar3 * 0x10;
          uVar6 = bVar5 - 0x30;
          if ((uVar6 & 0xff) < 10) {
            uVar6 = uVar6 + iVar3;
          }
          else {
            uVar6 = (uint)bVar5;
            if ((bVar5 - 0x41 & 0xff) < 6) {
              uVar6 = (uVar6 - 0x37) + iVar3;
            }
            else {
              if (5 < (uVar6 - 0x61 & 0xff)) goto LAB_001f41e0;
              uVar6 = (uVar6 - 0x57) + iVar3;
            }
          }
          if (0x3ff < uVar6 - 0xdc00) {
            if (0x3ff < uVar6 - 0xd800) {
              if (uVar6 < 0x80) goto LAB_001f41e4;
              if (0x7ff < uVar6) {
                lVar12 = 6;
                bVar5 = 0xe0;
                uVar7 = 2;
                lVar8 = 3;
                goto LAB_001f4118;
              }
              lVar8 = 2;
              bVar5 = (byte)(uVar6 >> 6) | 0xc0;
              lVar12 = 6;
              pbVar2[1] = (byte)uVar6 & 0x3f | 0x80;
LAB_001f4158:
              pbVar11 = pbVar2 + lVar8;
              goto LAB_001f415c;
            }
            if (((5 < (long)pbVar14 - (long)(pbVar15 + 6)) && (pbVar15[6] == 0x5c)) &&
               (pbVar15[7] == 0x75)) {
              bVar5 = pbVar15[8];
              uVar7 = bVar5 - 0x30;
              if (9 < (uVar7 & 0xff)) {
                uVar7 = (uint)bVar5;
                if ((bVar5 - 0x41 & 0xff) < 6) {
                  uVar7 = uVar7 - 0x37;
                }
                else {
                  if (5 < (uVar7 - 0x61 & 0xff)) goto LAB_001f3e38;
                  uVar7 = uVar7 - 0x57;
                }
              }
              bVar5 = pbVar15[9];
              iVar3 = uVar7 * 0x10;
              uVar7 = bVar5 - 0x30;
              if ((uVar7 & 0xff) < 10) {
                iVar3 = uVar7 + iVar3;
              }
              else {
                uVar7 = (uint)bVar5;
                if ((bVar5 - 0x41 & 0xff) < 6) {
                  iVar3 = (uVar7 - 0x37) + iVar3;
                }
                else {
                  if (5 < (uVar7 - 0x61 & 0xff)) goto LAB_001f3e38;
                  iVar3 = (uVar7 - 0x57) + iVar3;
                }
              }
              bVar5 = pbVar15[10];
              iVar3 = iVar3 * 0x10;
              uVar7 = bVar5 - 0x30;
              if ((uVar7 & 0xff) < 10) {
                iVar3 = uVar7 + iVar3;
              }
              else {
                uVar7 = (uint)bVar5;
                if ((bVar5 - 0x41 & 0xff) < 6) {
                  iVar3 = (uVar7 - 0x37) + iVar3;
                }
                else {
                  if (5 < (uVar7 - 0x61 & 0xff)) goto LAB_001f3e38;
                  iVar3 = (uVar7 - 0x57) + iVar3;
                }
              }
              bVar5 = pbVar15[0xb];
              iVar3 = iVar3 * 0x10;
              uVar7 = bVar5 - 0x30;
              if ((uVar7 & 0xff) < 10) {
                uVar7 = uVar7 + iVar3;
              }
              else {
                uVar7 = (uint)bVar5;
                if ((bVar5 - 0x41 & 0xff) < 6) {
                  uVar7 = (uVar7 - 0x37) + iVar3;
                }
                else {
                  if (5 < (uVar7 - 0x61 & 0xff)) goto LAB_001f3e38;
                  uVar7 = (uVar7 - 0x57) + iVar3;
                }
              }
              if (uVar7 - 0xdc00 < 0x400) {
                lVar12 = 0xc;
                uVar6 = ((uVar6 & 0x3ff) << 10 | uVar7 & 0x3ff) + 0x10000;
                bVar5 = 0xf0;
                uVar7 = 3;
                lVar8 = 4;
LAB_001f4118:
                pbVar2[uVar7] = (byte)uVar6 & 0x3f | 0x80;
                pbVar2[(ulong)(uVar7 - 1) & 0xff] = (byte)(uVar6 >> 6) & 0x3f | 0x80;
                bVar1 = (byte)(uVar6 >> 0xc);
                if (uVar7 == 2) {
                  bVar5 = bVar5 | bVar1;
                }
                else {
                  bVar5 = bVar5 | (byte)(uVar6 >> 0x12);
                  pbVar2[1] = bVar1 & 0x3f | 0x80;
                }
                goto LAB_001f4158;
              }
            }
          }
LAB_001f3e38:
          (*(code *)param_2[5])(pbVar4);
          goto LAB_001f3ce4;
        }
        uVar6 = (uint)bVar5;
        if ((bVar5 - 0x41 & 0xff) < 6) {
          uVar6 = uVar6 - 0x37;
          goto LAB_001f3ee8;
        }
        if ((uVar6 - 0x61 & 0xff) < 6) {
          uVar6 = uVar6 - 0x57;
          goto LAB_001f3ee8;
        }
LAB_001f41e0:
        uVar6 = 0;
LAB_001f41e4:
        bVar5 = (byte)uVar6;
        pbVar11 = pbVar2 + 1;
        lVar12 = 6;
LAB_001f415c:
        pbVar15 = pbVar15 + lVar12;
      }
      else {
        if (uVar6 != 0x72) goto LAB_001f3e38;
        pbVar11 = pbVar2 + 1;
        pbVar15 = pbVar15 + 2;
        bVar5 = 0xd;
      }
    }
  }
  else {
    pbVar15 = pbVar15 + 1;
    pbVar11 = pbVar2 + 1;
  }
  *pbVar2 = bVar5;
  pbVar2 = pbVar11;
  goto joined_r0x001f3d68;
}

