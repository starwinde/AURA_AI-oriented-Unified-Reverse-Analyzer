
/* WARNING: Type propagation algorithm not settling */

ulong FUN_00111270(undefined1 *param_1,ulong param_2,char *param_3,uint param_4,uint param_5,
                  long param_6,char *param_7,char *param_8)

{
  uint uVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  size_t sVar6;
  ushort **ppuVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  byte bVar11;
  char cVar12;
  uint uVar13;
  uint uVar14;
  ulong uVar15;
  byte *pbVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  ulong uVar20;
  uint uVar21;
  uint uVar22;
  ulong uVar23;
  uint uVar24;
  ulong uVar25;
  uint uVar26;
  uint uVar27;
  ulong __n;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  char *local_d0;
  uint local_c8;
  uint local_b8;
  ulong local_a8;
  char *local_88;
  wint_t local_74;
  mbstate_t local_70;
  long local_68;
  
  uVar24 = param_5 >> 1;
  uVar23 = 0xffffffffffffffff;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  local_b8 = param_5;
  local_88 = param_8;
LAB_001112d8:
  sVar6 = __ctype_get_mb_cur_max();
  uVar14 = uVar24 & 1;
  local_d0 = (char *)0x0;
  local_c8 = 0;
  local_a8 = 0;
  uVar30 = 0;
  uVar28 = 0;
  __n = 0;
  uVar18 = 1;
  bVar3 = param_4 == 4;
  uVar29 = uVar14;
  bVar4 = false;
joined_r0x00111348:
  if (bVar3) {
    if (uVar14 != 0) goto LAB_00112194;
    uVar30 = 1;
LAB_001119a0:
    if (param_2 != 0) {
      *param_1 = 0x27;
    }
    uVar20 = 1;
    uVar29 = 0;
    param_4 = 2;
    local_d0 = "\'";
    __n = uVar20;
  }
  else if (param_4 < 4 || bVar4) {
    if (param_4 == 2) {
      if (uVar29 == 0) goto LAB_001119a0;
      __n = 1;
      uVar20 = 0;
      local_d0 = "\'";
    }
    else {
      if (param_4 == 3) {
        uVar30 = 1;
      }
      else if (param_4 == 0) {
        uVar29 = 0;
        uVar20 = 0;
        goto LAB_00111370;
      }
LAB_00112194:
      uVar29 = 1;
      __n = 1;
      uVar20 = 0;
      param_4 = 2;
      local_d0 = "\'";
    }
  }
  else if (param_4 == 7) {
    uVar29 = 0;
    uVar30 = 1;
    uVar20 = 0;
  }
  else if (param_4 < 8) {
    if (param_4 == 5) {
      if (uVar29 == 0) {
        if (param_2 != 0) {
          *param_1 = 0x22;
        }
        __n = 1;
        uVar20 = 1;
        local_d0 = "\"";
        uVar30 = 1;
      }
      else {
        __n = 1;
        uVar20 = 0;
        local_d0 = "\"";
        uVar30 = uVar29;
      }
    }
    else {
      uVar29 = 1;
      __n = 1;
      uVar20 = 0;
      param_4 = 5;
      local_d0 = "\"";
      uVar30 = 1;
    }
  }
  else {
    if (2 < param_4 - 8) {
                    /* WARNING: Subroutine does not return */
      abort();
    }
    if (param_4 != 10) {
      param_7 = (char *)dcgettext(0,&DAT_0011cbf0,5);
      if (param_7 == "`") {
        param_7 = (char *)FUN_0010ce80(&DAT_0011cbf0,param_4);
      }
      local_88 = (char *)dcgettext(0,&DAT_0011bc58,5);
      if (local_88 == "\'") {
        local_88 = (char *)FUN_0010ce80(&DAT_0011bc58,param_4);
      }
    }
    uVar20 = 0;
    if (uVar29 == 0) {
      cVar12 = *param_7;
      while (cVar12 != '\0') {
        if (uVar20 < param_2) {
          param_1[uVar20] = cVar12;
        }
        uVar20 = uVar20 + 1;
        cVar12 = param_7[uVar20];
      }
    }
    local_d0 = local_88;
    uVar30 = 1;
    __n = strlen(local_88);
  }
LAB_00111370:
  uVar25 = 0;
LAB_00111390:
  bVar3 = uVar25 == uVar23;
  if (uVar23 == 0xffffffffffffffff) {
    bVar3 = param_3[uVar25] == '\0';
  }
  bVar3 = !bVar3;
  uVar21 = (uint)bVar3;
  uVar14 = (uint)bVar3;
  uVar22 = (uint)bVar3;
  uVar19 = uVar30;
  if (uVar22 == 0) goto LAB_00111934;
  pbVar16 = (byte *)(param_3 + uVar25);
  uVar1 = uVar30 & param_4 != 2;
  uVar27 = uVar1 & __n != 0;
  uVar26 = uVar27;
  uVar17 = uVar28;
  if ((uVar1 & __n != 0) == 0) {
    bVar11 = param_3[uVar25];
    uVar15 = (ulong)bVar11;
    switch(uVar15) {
    case 0:
      if (uVar30 != 0) goto code_r0x00111be8;
      uVar26 = 0;
      uVar21 = uVar30;
      if ((local_b8 & 1) == 0) goto code_r0x00111420;
      uVar25 = uVar25 + 1;
      goto LAB_00111390;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
      goto code_r0x0011153c;
    case 7:
      bVar11 = 0x61;
      uVar17 = (uint)(param_4 == 2);
      break;
    case 8:
      bVar11 = 0x62;
      uVar17 = (uint)(param_4 == 2);
      break;
    case 9:
      bVar11 = 0x74;
      goto LAB_00111400;
    case 10:
      bVar11 = 0x6e;
      goto LAB_00111400;
    case 0xb:
      bVar11 = 0x76;
      uVar17 = (uint)(param_4 == 2);
      break;
    case 0xc:
      bVar11 = 0x66;
      uVar17 = (uint)(param_4 == 2);
      break;
    case 0xd:
      bVar11 = 0x72;
LAB_00111400:
      uVar17 = (uint)(param_4 == 2);
      uVar14 = (uint)(param_4 == 2);
      uVar26 = uVar29 & uVar14;
      if ((uVar29 & uVar14) != 0) goto LAB_001118e0;
      break;
    case 0x20:
LAB_001118d0:
      uVar21 = uVar22;
      if (uVar29 == 0 || param_4 != 2) goto code_r0x00111420;
      goto LAB_001118e0;
    case 0x21:
    case 0x22:
    case 0x24:
    case 0x26:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
code_r0x001116f0:
LAB_001116f4:
      uVar21 = uVar27;
      if (uVar29 == 0 || param_4 != 2) goto code_r0x00111420;
      goto LAB_001118e0;
    case 0x23:
code_r0x001118b4:
LAB_001118b8:
      uVar26 = uVar27;
      if (uVar25 == 0) goto LAB_001118d0;
      uVar21 = 0;
    case 0x25:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
      goto code_r0x00111420;
    case 0x27:
      local_c8 = uVar22;
      if (param_4 != 2) goto code_r0x00111420;
      if (uVar29 == 0) {
        uVar15 = 0;
        uVar8 = param_2;
        if (param_2 == 0 || local_a8 != 0) {
          if (uVar20 < param_2) {
            param_1[uVar20] = 0x27;
          }
          if (uVar20 + 1 < param_2) {
            param_1[uVar20 + 1] = 0x5c;
          }
          uVar15 = param_2;
          uVar8 = local_a8;
          if (uVar20 + 2 < param_2) {
            param_1[uVar20 + 2] = 0x27;
          }
        }
        uVar20 = uVar20 + 3;
        param_2 = uVar15;
        uVar14 = uVar29;
        local_a8 = uVar8;
        uVar28 = uVar29;
        goto LAB_001114dc;
      }
      goto LAB_001118f8;
    case 0x3f:
      if (param_4 != 2) goto code_r0x0011171c;
      uVar14 = uVar29;
      uVar21 = uVar29;
      if (uVar29 == 0) goto LAB_001114dc;
      goto LAB_001118f8;
    default:
      uVar14 = (uint)bVar11;
      if (0x7a < uVar14) {
        if (uVar14 == 0x7d) {
LAB_001118a0:
          if (uVar23 == 0xffffffffffffffff) {
            if (param_3[1] != '\0') {
              uVar26 = uVar27;
              uVar21 = 0;
              goto code_r0x00111420;
            }
          }
          else if (uVar23 != 1) goto LAB_00111bdc;
          goto code_r0x001118b4;
        }
        if (uVar14 < 0x7e) {
          if (uVar14 != 0x7b) {
            uVar15 = 0x7c;
            goto LAB_001116f4;
          }
          goto LAB_001118a0;
        }
        if (uVar14 == 0x7e) goto LAB_001118b8;
        goto joined_r0x00111e3c;
      }
      if (uVar14 == 0x40) goto code_r0x0011153c;
      uVar8 = 1L << ((ulong)(uVar14 - 0x41) & 0x3f);
      if ((uVar8 & 0x3ffffff53ffffff) != 0) goto code_r0x00111420;
      if ((uVar8 & 0xa4000000) != 0) goto code_r0x001116f0;
      if (param_4 != 2) goto LAB_00111dcc;
      if (uVar29 == 0) {
        uVar25 = uVar25 + 1;
        bVar11 = 0x5c;
        uVar21 = uVar29;
        goto LAB_001114ec;
      }
      goto LAB_001118f8;
    }
joined_r0x00111864:
    uVar21 = uVar30;
    if (uVar30 == 0) goto code_r0x00111420;
    uVar21 = 0;
    goto joined_r0x00111804;
  }
  if (1 < __n && uVar23 == 0xffffffffffffffff) {
    uVar23 = strlen(param_3);
  }
  uVar8 = uVar20;
  if ((uVar23 < __n + uVar25) || (iVar5 = memcmp(pbVar16,local_d0,__n), iVar5 != 0)) {
    bVar11 = *pbVar16;
    uVar15 = (ulong)bVar11;
    uVar13 = (uint)bVar11;
    switch(uVar13) {
    case 0:
code_r0x00111be8:
      if (uVar29 == 0) {
        uVar26 = (uint)(param_4 == 2) & (uVar28 ^ 1);
        if (((uint)(param_4 == 2) & (uVar28 ^ 1)) != 0) {
          if (uVar20 < param_2) {
            param_1[uVar20] = 0x27;
          }
          if (uVar20 + 1 < param_2) {
            param_1[uVar20 + 1] = 0x24;
          }
          if (uVar20 + 2 < param_2) {
            param_1[uVar20 + 2] = 0x27;
          }
          uVar14 = uVar26;
          uVar28 = uVar26;
          if (uVar20 + 3 < param_2) {
            bVar11 = 0x30;
            param_1[uVar20 + 3] = 0x5c;
            uVar20 = uVar20 + 4;
            uVar21 = uVar29;
          }
          else {
            bVar11 = 0x30;
            uVar20 = uVar20 + 4;
            uVar21 = uVar29;
          }
          goto LAB_001114dc;
        }
        goto LAB_00111af8;
      }
      if (param_4 == 2) {
        param_4 = 4;
      }
      goto LAB_00111904;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
      goto code_r0x00111534;
    case 7:
      uVar17 = 0;
      uVar21 = 0;
      bVar11 = 0x61;
      break;
    case 8:
      uVar17 = 0;
      uVar21 = 0;
      bVar11 = 0x62;
      break;
    case 9:
      bVar11 = 0x74;
      goto joined_r0x00111ca8;
    case 10:
      bVar11 = 0x6e;
joined_r0x00111ca8:
      uVar17 = 0;
      uVar26 = 0;
      goto joined_r0x00111864;
    case 0xb:
      uVar17 = 0;
      uVar21 = 0;
      bVar11 = 0x76;
      break;
    case 0xc:
      uVar17 = 0;
      uVar21 = 0;
      bVar11 = 0x66;
      break;
    case 0xd:
      uVar17 = 0;
      bVar11 = 0x72;
      uVar26 = 0;
      goto joined_r0x00111864;
    case 0x20:
    case 0x25:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
      uVar26 = 0;
      uVar21 = uVar27;
      goto code_r0x00111420;
    case 0x21:
    case 0x22:
    case 0x24:
    case 0x26:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
code_r0x00111bd8:
      uVar27 = 0;
LAB_00111bdc:
      uVar26 = uVar27;
      uVar21 = 0;
      goto code_r0x00111420;
    case 0x23:
      uVar27 = 0;
      goto LAB_001118b8;
    case 0x27:
      uVar26 = 0;
      local_c8 = uVar27;
      uVar21 = uVar27;
      goto code_r0x00111420;
    case 0x3f:
      uVar27 = 0;
      goto code_r0x0011171c;
    default:
      if (0x7a < bVar11) {
        if (uVar13 == 0x7d) {
          uVar27 = 0;
        }
        else {
          if (0x7d < uVar13) {
            uVar26 = 0;
            if (uVar13 == 0x7e) goto LAB_00112328;
            goto code_r0x00111534;
          }
          uVar27 = 0;
          if (uVar13 != 0x7b) goto LAB_00111fc8;
        }
        goto LAB_001118a0;
      }
      if (uVar13 == 0x40) {
code_r0x00111534:
        uVar27 = 0;
code_r0x0011153c:
joined_r0x00111e3c:
        uVar14 = uVar30;
        if (sVar6 != 1) {
          local_70.__count = 0;
          local_70.__value = (_union_27)0x0;
          if (uVar23 == 0xffffffffffffffff) {
            uVar23 = strlen(param_3);
          }
          uVar8 = 0;
          do {
            uVar10 = uVar25 + uVar8;
            lVar9 = FUN_00110350(&local_74,param_3 + uVar10,uVar23 - uVar10,&local_70);
            if (lVar9 == 0) break;
            if (lVar9 == -1) {
              uVar21 = 0;
              goto LAB_00111f8c;
            }
            if (lVar9 == -2) goto joined_r0x001124d8;
            if (lVar9 != -3) {
              if (uVar29 != 0 && param_4 == 2) {
                if (lVar9 == 1) {
                  uVar8 = uVar8 + 1;
                  goto LAB_00111f2c;
                }
                pbVar16 = (byte *)(param_3 + uVar10 + 1);
                do {
                  uVar22 = *pbVar16 - 0x5b & 0xff;
                  if ((uVar22 < 0x22) && ((0x20000002bU >> ((ulong)uVar22 & 0x3f) & 1) != 0)) {
                    param_4 = 2;
                    goto LAB_001118f8;
                  }
                  pbVar16 = pbVar16 + 1;
                } while ((byte *)(param_3 + uVar10 + lVar9) != pbVar16);
              }
              uVar8 = uVar8 + lVar9;
            }
LAB_00111f2c:
            iVar5 = iswprint(local_74);
            if (iVar5 == 0) {
              uVar21 = 0;
            }
            iVar5 = mbsinit(&local_70);
          } while (iVar5 == 0);
          uVar14 = uVar30 & (uVar21 ^ 1);
          goto LAB_00111f8c;
        }
        ppuVar7 = __ctype_b_loc();
        bVar3 = ((*ppuVar7)[uVar15] & 0x4000) == 0;
        uVar21 = (uint)!bVar3;
        uVar14 = uVar30 & bVar3;
        uVar8 = 1;
        goto joined_r0x00111f94;
      }
      uVar10 = 1L << ((ulong)(uVar13 - 0x41) & 0x3f);
      if ((uVar10 & 0x3ffffff53ffffff) != 0) {
        uVar26 = 0;
        goto LAB_00112164;
      }
      if ((uVar10 & 0xa4000000) != 0) goto code_r0x00111bd8;
LAB_00111dcc:
      uVar26 = 0;
      if ((uVar30 & uVar29) == 0) goto LAB_00112008;
      if (__n != 0) {
        uVar25 = uVar25 + 1;
        uVar21 = 0;
        bVar11 = 0x5c;
        goto LAB_001114ec;
      }
      goto LAB_00111904;
    }
    goto joined_r0x00111804;
  }
  if (uVar29 != 0) goto LAB_00111904;
  bVar11 = *pbVar16;
  uVar15 = (ulong)bVar11;
  uVar17 = 0;
  switch(uVar15) {
  case 0:
LAB_00111af8:
    uVar8 = uVar20 + 1;
    if (uVar20 < param_2) {
      param_1[uVar20] = 0x5c;
    }
    if (uVar1 != 0) {
      if ((uVar25 + 1 < uVar23) && ((byte)(param_3[uVar25 + 1] - 0x30U) < 10)) {
        if (uVar8 < param_2) {
          param_1[uVar8] = 0x30;
        }
        if (uVar20 + 2 < param_2) {
          param_1[uVar20 + 2] = 0x30;
        }
        uVar8 = uVar20 + 3;
      }
      uVar15 = 0x30;
      uVar21 = 0;
      goto LAB_00111430;
    }
    uVar14 = (uint)bVar3;
    bVar11 = 0x30;
    uVar21 = 0;
    uVar20 = uVar8;
    bVar2 = 0x30;
    if (uVar26 == 0) goto LAB_001114dc;
    goto LAB_00111448;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
    goto code_r0x0011153c;
  case 7:
    bVar11 = 0x61;
    uVar21 = uVar29;
    break;
  case 8:
    uVar17 = 0;
    bVar11 = 0x62;
    uVar21 = 0;
    break;
  case 9:
    bVar11 = 0x74;
    goto joined_r0x00111864;
  case 10:
    bVar11 = 0x6e;
    goto joined_r0x00111864;
  case 0xb:
    uVar17 = 0;
    bVar11 = 0x76;
    uVar21 = 0;
    break;
  case 0xc:
    uVar17 = 0;
    bVar11 = 0x66;
    uVar21 = 0;
    break;
  case 0xd:
    bVar11 = 0x72;
    goto joined_r0x00111864;
  case 0x20:
  case 0x25:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
  case 0x3a:
    uVar21 = uVar27;
    goto code_r0x00111420;
  case 0x21:
  case 0x22:
  case 0x24:
  case 0x26:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x3b:
  case 0x3c:
  case 0x3d:
  case 0x3e:
    uVar21 = uVar29;
    goto code_r0x00111420;
  case 0x23:
    goto code_r0x001118b4;
  case 0x27:
    local_c8 = uVar27;
    uVar21 = uVar27;
    goto code_r0x00111420;
  case 0x3f:
code_r0x0011171c:
    uVar26 = uVar27;
    if ((((param_4 == 5) && ((local_b8 >> 2 & 1) != 0)) && (uVar8 = uVar25 + 2, uVar8 < uVar23)) &&
       (pbVar16[1] == 0x3f)) {
      bVar11 = param_3[uVar8];
      uVar15 = 0x3f;
      if (0x3e < bVar11) goto LAB_00111bdc;
      uVar10 = 0x7000a38200000000 >> ((ulong)bVar11 & 0x3f);
      uVar21 = (uint)uVar10 & 1;
      if ((uVar10 & 1) == 0) goto code_r0x00111420;
      if (uVar29 != 0) goto LAB_00111904;
      if (uVar20 < param_2) {
        param_1[uVar20] = 0x3f;
      }
      if (uVar20 + 1 < param_2) {
        param_1[uVar20 + 1] = 0x22;
      }
      if (uVar20 + 2 < param_2) {
        param_1[uVar20 + 2] = 0x22;
      }
      if (uVar20 + 3 < param_2) {
        param_1[uVar20 + 3] = 0x3f;
      }
      uVar20 = uVar20 + 4;
      uVar15 = (ulong)bVar11;
      uVar25 = uVar8;
      uVar21 = uVar29;
    }
    else {
      uVar15 = 0x3f;
      uVar21 = 0;
    }
    goto code_r0x00111420;
  default:
    uVar14 = (uint)bVar11;
    if (0x7a < bVar11) {
      if (bVar11 == 0x7d) goto LAB_001118a0;
      if (bVar11 < 0x7e) {
        if (uVar14 == 0x7b) goto LAB_001118a0;
LAB_00111fc8:
        uVar15 = 0x7c;
        uVar26 = uVar27;
        uVar21 = 0;
      }
      else {
        if (uVar14 != 0x7e) goto code_r0x0011153c;
LAB_00112328:
        if (uVar25 != 0) {
          uVar21 = 0;
          uVar14 = 0;
          uVar15 = 0x7e;
          goto LAB_00111430;
        }
        uVar15 = 0x7e;
        uVar21 = uVar27;
      }
      goto code_r0x00111420;
    }
    if (uVar14 == 0x40) goto code_r0x0011153c;
    uVar10 = 1L << ((ulong)(uVar14 - 0x41) & 0x3f);
    if ((uVar10 & 0x3ffffff53ffffff) != 0) {
LAB_00112164:
      uVar14 = 0;
      uVar21 = uVar27;
      goto LAB_00111430;
    }
    if ((uVar10 & 0xa4000000) != 0) goto LAB_00111bdc;
LAB_00112008:
    uVar21 = uVar30;
    if (uVar30 == 0) goto code_r0x00111420;
    uVar21 = 0;
    bVar11 = 0x5c;
    goto LAB_001114a8;
  }
  goto LAB_00111458;
LAB_001125d8:
  param_4 = 5;
  param_2 = local_a8;
  goto LAB_001112d8;
joined_r0x001124d8:
  while ((uVar10 < uVar23 && (param_3[uVar10] != '\0'))) {
    uVar8 = uVar8 + 1;
    uVar10 = uVar25 + uVar8;
  }
  uVar21 = 0;
LAB_00111f8c:
  if (uVar8 < 2) {
joined_r0x00111f94:
    uVar26 = uVar27;
    if (uVar14 != 0) {
      uVar21 = 0;
      uVar14 = uVar30;
      goto LAB_001115ac;
    }
code_r0x00111420:
    bVar11 = (byte)uVar15;
    uVar14 = uVar1 | uVar29;
    uVar8 = uVar20;
    if (uVar1 != 0 || uVar29 != 0) {
      uVar14 = 0;
LAB_00111430:
      bVar11 = (byte)uVar15;
      if ((param_6 == 0) ||
         (bVar2 = bVar11,
         (*(uint *)(param_6 + (uVar15 >> 5) * 4) >> (ulong)((uint)uVar15 & 0x1f) & 1) == 0))
      goto LAB_00111444;
LAB_00111448:
      bVar11 = bVar2;
      uVar17 = (uint)(param_4 == 2);
      uVar20 = uVar8;
joined_r0x00111804:
      if (uVar29 != 0) {
        uVar19 = uVar30 & uVar17;
        goto LAB_001118f8;
      }
LAB_00111458:
      uVar17 = uVar17 & (uVar28 ^ 1);
      if (uVar17 != 0) {
        if (uVar20 < param_2) {
          param_1[uVar20] = 0x27;
        }
        if (uVar20 + 1 < param_2) {
          param_1[uVar20 + 1] = 0x24;
        }
        if (uVar20 + 2 < param_2) {
          param_1[uVar20 + 2] = 0x27;
        }
        uVar20 = uVar20 + 3;
        uVar28 = uVar17;
      }
LAB_001114a8:
      if (uVar20 < param_2) {
        param_1[uVar20] = 0x5c;
      }
      uVar20 = uVar20 + 1;
      uVar25 = uVar25 + 1;
      goto LAB_001114c0;
    }
LAB_00111444:
    uVar20 = uVar8;
    bVar2 = bVar11;
    if (uVar26 != 0) goto LAB_00111448;
LAB_001114dc:
    uVar25 = uVar25 + 1;
    uVar17 = uVar28 & (uVar14 ^ 1);
  }
  else {
LAB_001115ac:
    uVar8 = uVar25 + uVar8;
    uVar19 = 0;
    if (uVar14 == 0) goto LAB_00111690;
    while( true ) {
      uVar19 = (uint)(param_4 == 2);
      uVar22 = (uint)(param_4 == 2);
      if (uVar29 != 0) goto LAB_001118f8;
      if ((uVar22 & (uVar28 ^ 1)) != 0) {
        if (uVar20 < param_2) {
          param_1[uVar20] = 0x27;
        }
        if (uVar20 + 1 < param_2) {
          param_1[uVar20 + 1] = 0x24;
        }
        if (uVar20 + 2 < param_2) {
          param_1[uVar20 + 2] = 0x27;
        }
        uVar20 = uVar20 + 3;
        uVar28 = uVar22 & (uVar28 ^ 1);
      }
      if (uVar20 < param_2) {
        param_1[uVar20] = 0x5c;
      }
      if (uVar20 + 1 < param_2) {
        param_1[uVar20 + 1] = (char)(uVar15 >> 6) + '0';
      }
      if (uVar20 + 2 < param_2) {
        param_1[uVar20 + 2] = ((byte)(uVar15 >> 3) & 7) + 0x30;
      }
      uVar25 = uVar25 + 1;
      uVar19 = ((uint)uVar15 & 7) + 0x30;
      bVar11 = (byte)uVar19;
      uVar15 = (ulong)uVar19;
      uVar20 = uVar20 + 3;
      uVar19 = uVar14;
      uVar17 = uVar29;
      if (uVar8 <= uVar25) break;
      while( true ) {
        if (uVar20 < param_2) {
          param_1[uVar20] = (char)uVar15;
        }
        uVar15 = (ulong)(byte)param_3[uVar25];
        uVar20 = uVar20 + 1;
        if (uVar14 != 0) break;
LAB_00111690:
        bVar11 = (byte)uVar15;
        uVar17 = uVar28 & (uVar19 ^ 1);
        if (uVar27 != 0) {
          if (uVar20 < param_2) {
            param_1[uVar20] = 0x5c;
          }
          uVar20 = uVar20 + 1;
        }
        uVar25 = uVar25 + 1;
        if (uVar8 <= uVar25) goto LAB_001114ec;
        if (uVar17 == 0) {
          uVar27 = 0;
        }
        else {
          if (uVar20 < param_2) {
            param_1[uVar20] = 0x27;
          }
          if (uVar20 + 1 < param_2) {
            param_1[uVar20 + 1] = 0x27;
          }
          uVar20 = uVar20 + 2;
          uVar27 = uVar14;
          uVar28 = uVar14;
        }
      }
    }
  }
LAB_001114ec:
  if (uVar17 != 0) {
    if (uVar20 < param_2) {
      param_1[uVar20] = 0x27;
    }
    if (uVar20 + 1 < param_2) {
      param_1[uVar20 + 1] = 0x27;
    }
    uVar20 = uVar20 + 2;
    uVar28 = 0;
  }
LAB_001114c0:
  if (uVar20 < param_2) {
    param_1[uVar20] = bVar11;
  }
  uVar20 = uVar20 + 1;
  if (uVar21 == 0) {
    uVar18 = uVar21;
  }
  goto LAB_00111390;
LAB_00111934:
  if (uVar20 != 0 || param_4 != 2) {
    uVar14 = uVar29 ^ 1;
    if (param_4 != 2 || (uVar29 ^ 1) == 0) goto LAB_001120b0;
  }
  else if (uVar29 != 0) {
LAB_001118e0:
    param_4 = 2;
LAB_001118f8:
    if (uVar19 != 0) {
      param_4 = 4;
    }
LAB_00111904:
    param_6 = 0;
    local_b8 = local_b8 & 0xfffffffd;
    uVar24 = 0;
    goto LAB_001112d8;
  }
  if (local_c8 == 0) {
    uVar14 = 1;
  }
  else {
    if (uVar18 != 0) goto LAB_001125d8;
    bVar4 = param_2 == 0;
    uVar14 = local_c8;
    if (bVar4 && local_a8 != 0) {
      bVar3 = param_4 == 4;
      uVar14 = 0;
      uVar29 = uVar18;
      param_2 = local_a8;
      local_c8 = (uint)(bVar4 && local_a8 != 0);
      bVar4 = bVar3;
      goto joined_r0x00111348;
    }
  }
LAB_001120b0:
  uVar23 = uVar20;
  if ((local_d0 != (char *)0x0 && uVar14 != 0) && (cVar12 = *local_d0, cVar12 != '\0')) {
    do {
      if (uVar23 < param_2) {
        param_1[uVar23] = cVar12;
      }
      uVar23 = uVar23 + 1;
      cVar12 = local_d0[uVar23 - uVar20];
    } while (cVar12 != '\0');
  }
  if (uVar23 < param_2) {
    param_1[uVar23] = 0;
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                     local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return uVar23;
}

