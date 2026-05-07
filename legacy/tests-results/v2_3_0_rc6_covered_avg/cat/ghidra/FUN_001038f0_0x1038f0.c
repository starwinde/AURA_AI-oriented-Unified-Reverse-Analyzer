
/* WARNING: Type propagation algorithm not settling */

ulong FUN_001038f0(undefined1 *param_1,ulong param_2,char *param_3,uint param_4,uint param_5,
                  long param_6,char *param_7,char *param_8)

{
  byte *pbVar1;
  uint uVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  size_t sVar9;
  ushort **ppuVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  byte bVar15;
  char cVar16;
  uint uVar17;
  ulong uVar18;
  uint uVar19;
  long lVar20;
  byte *pbVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  ulong __n;
  ulong uVar25;
  wint_t *pwVar26;
  uint uVar27;
  ulong uVar28;
  uint uVar29;
  ulong uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  byte *local_f0;
  char *local_e0;
  uint local_d8;
  uint local_c8;
  ulong local_b8;
  wint_t local_74;
  mbstate_t local_70;
  long local_68;
  
  uVar27 = param_5 >> 1;
  uVar30 = 0xffffffffffffffff;
  local_68 = *(long *)PTR___stack_chk_guard_0011ffe0;
  local_c8 = param_5;
LAB_00103958:
  sVar9 = __ctype_get_mb_cur_max();
  uVar32 = uVar27 & 1;
  local_e0 = (char *)0x0;
  local_d8 = 0;
  local_b8 = 0;
  uVar24 = 1;
  uVar22 = 0;
  uVar23 = 0;
  __n = 0;
  bVar4 = param_4 == 4;
  uVar31 = uVar32;
  bVar5 = false;
joined_r0x001039bc:
  if (bVar4) {
    if (uVar32 != 0) goto LAB_00104a44;
    uVar23 = 1;
LAB_0010400c:
    if (param_2 != 0) {
      *param_1 = 0x27;
    }
    __n = 1;
    uVar31 = 0;
    param_4 = 2;
    local_e0 = "\'";
    uVar25 = __n;
  }
  else if (param_4 < 4 || bVar5) {
    if (param_4 == 2) {
      if (uVar31 == 0) goto LAB_0010400c;
      __n = 1;
      uVar25 = 0;
      local_e0 = "\'";
    }
    else {
      if (param_4 == 3) {
        uVar23 = 1;
      }
      else if (param_4 == 0) {
        uVar31 = 0;
        uVar25 = 0;
        goto LAB_001039e0;
      }
LAB_00104a44:
      uVar31 = 1;
      __n = 1;
      uVar25 = 0;
      param_4 = 2;
      local_e0 = "\'";
    }
  }
  else if (param_4 == 7) {
    uVar31 = 0;
    uVar23 = 1;
    uVar25 = 0;
  }
  else if (param_4 < 8) {
    if (param_4 == 5) {
      if (uVar31 == 0) {
        if (param_2 != 0) {
          *param_1 = 0x22;
        }
        __n = 1;
        uVar25 = 1;
        local_e0 = "\"";
        uVar23 = 1;
      }
      else {
        __n = 1;
        uVar25 = 0;
        local_e0 = "\"";
        uVar23 = uVar31;
      }
    }
    else {
      uVar31 = 1;
      __n = 1;
      uVar25 = 0;
      param_4 = 5;
      local_e0 = "\"";
      uVar23 = 1;
    }
  }
  else {
    if (2 < param_4 - 8) {
                    /* WARNING: Subroutine does not return */
      abort();
    }
    if (param_4 != 10) {
      param_7 = (char *)dcgettext(0,&DAT_001054d8,5);
      if (param_7 == "`") {
        param_7 = (char *)FUN_00102ff0(&DAT_001054d8,param_4);
      }
      param_8 = (char *)dcgettext(0,&DAT_00105200,5);
      if (param_8 == "\'") {
        param_8 = (char *)FUN_00102ff0(&DAT_00105200,param_4);
      }
    }
    uVar25 = 0;
    if (uVar31 == 0) {
      cVar16 = *param_7;
      while (cVar16 != '\0') {
        if (uVar25 < param_2) {
          param_1[uVar25] = cVar16;
        }
        uVar25 = uVar25 + 1;
        cVar16 = param_7[uVar25];
      }
    }
    __n = strlen(param_8);
    uVar23 = 1;
    local_e0 = param_8;
  }
LAB_001039e0:
  uVar28 = 0;
LAB_001039f8:
  bVar4 = uVar28 == uVar30;
  if (uVar30 == 0xffffffffffffffff) {
    bVar4 = param_3[uVar28] == '\0';
  }
  bVar4 = !bVar4;
  uVar32 = (uint)bVar4;
  uVar33 = (uint)bVar4;
  uVar19 = uVar23;
  if (uVar33 == 0) goto LAB_00103fa8;
  pbVar1 = (byte *)(param_3 + uVar28);
  uVar2 = uVar23 & param_4 != 2;
  uVar6 = uVar2 & __n != 0;
  uVar34 = (uint)bVar4;
  uVar7 = uVar22;
  uVar29 = uVar6;
  if ((uVar2 & __n != 0) == 0) {
    bVar15 = param_3[uVar28];
    uVar18 = (ulong)bVar15;
    uVar17 = uVar31;
    switch(uVar18) {
    case 0:
      if (uVar23 != 0) goto code_r0x00104278;
      uVar29 = 0;
      uVar32 = uVar23;
      if ((local_c8 & 1) == 0) goto code_r0x00103a88;
      uVar28 = uVar28 + 1;
      goto LAB_001039f8;
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
      goto code_r0x00103ba4;
    case 7:
      bVar15 = 0x61;
      uVar7 = (uint)(param_4 == 2);
      break;
    case 8:
      bVar15 = 0x62;
      uVar7 = (uint)(param_4 == 2);
      break;
    case 9:
      bVar15 = 0x74;
      goto LAB_00103a68;
    case 10:
      bVar15 = 0x6e;
      goto LAB_00103a68;
    case 0xb:
      bVar15 = 0x76;
      uVar7 = (uint)(param_4 == 2);
      break;
    case 0xc:
      bVar15 = 0x66;
      uVar7 = (uint)(param_4 == 2);
      break;
    case 0xd:
      bVar15 = 0x72;
LAB_00103a68:
      uVar7 = (uint)(param_4 == 2);
      uVar32 = (uint)(param_4 == 2);
      uVar29 = uVar31 & uVar32;
      if ((uVar31 & uVar32) != 0) goto LAB_00103f58;
      break;
    case 0x20:
LAB_00103f48:
      uVar32 = uVar34;
      if (uVar31 == 0 || param_4 != 2) goto code_r0x00103a88;
      goto LAB_00103f58;
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
code_r0x00103d68:
LAB_00103d6c:
      uVar32 = uVar6;
      if (uVar31 == 0 || param_4 != 2) goto code_r0x00103a88;
      goto LAB_00103f58;
    case 0x23:
code_r0x00103f2c:
LAB_00103f30:
      uVar29 = uVar6;
      if (uVar28 == 0) goto LAB_00103f48;
      uVar32 = 0;
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
      goto code_r0x00103a88;
    case 0x27:
      local_d8 = uVar33;
      if (param_4 != 2) goto code_r0x00103a88;
      if (uVar31 == 0) {
        uVar18 = 0;
        uVar11 = param_2;
        if (param_2 == 0 || local_b8 != 0) {
          if (uVar25 < param_2) {
            param_1[uVar25] = 0x27;
          }
          if (uVar25 + 1 < param_2) {
            param_1[uVar25 + 1] = 0x5c;
          }
          uVar18 = param_2;
          uVar11 = local_b8;
          if (uVar25 + 2 < param_2) {
            param_1[uVar25 + 2] = 0x27;
          }
        }
        uVar25 = uVar25 + 3;
        param_2 = uVar18;
        local_d8 = uVar34;
        local_b8 = uVar11;
        uVar22 = uVar31;
        goto LAB_00103b44;
      }
      goto LAB_00103f6c;
    case 0x3f:
      if (param_4 != 2) goto code_r0x00103d94;
      uVar32 = uVar31;
      if (uVar31 == 0) goto LAB_00103b44;
      goto LAB_00103f6c;
    default:
      uVar17 = (uint)bVar15;
      if (0x7a < uVar17) {
        if (uVar17 == 0x7d) {
LAB_00103f18:
          if (uVar30 == 0xffffffffffffffff) {
            if (param_3[1] != '\0') {
              uVar29 = uVar6;
              uVar32 = 0;
              goto code_r0x00103a88;
            }
          }
          else if (uVar30 != 1) goto LAB_0010426c;
          goto code_r0x00103f2c;
        }
        if (uVar17 < 0x7e) {
          if (uVar17 != 0x7b) {
            uVar18 = 0x7c;
            goto LAB_00103d6c;
          }
          goto LAB_00103f18;
        }
        if (uVar17 == 0x7e) goto LAB_00103f30;
        goto joined_r0x001044cc;
      }
      if (uVar17 == 0x40) goto code_r0x00103ba4;
      uVar11 = 1L << ((ulong)(uVar17 - 0x41) & 0x3f);
      if ((uVar11 & 0x3ffffff53ffffff) != 0) goto code_r0x00103a88;
      if ((uVar11 & 0xa4000000) != 0) goto code_r0x00103d68;
      if (param_4 != 2) goto LAB_0010445c;
      if (uVar31 == 0) {
        uVar28 = uVar28 + 1;
        bVar15 = 0x5c;
        uVar32 = uVar31;
        goto LAB_00103b54;
      }
      goto LAB_00103f6c;
    }
joined_r0x00103edc:
    uVar32 = uVar23;
    if (uVar23 == 0) goto code_r0x00103a88;
    uVar32 = 0;
    goto joined_r0x00103e7c;
  }
  if (1 < __n && uVar30 == 0xffffffffffffffff) {
    uVar30 = strlen(param_3);
  }
  uVar11 = uVar25;
  if ((uVar30 < __n + uVar28) || (iVar8 = memcmp(pbVar1,local_e0,__n), iVar8 != 0)) {
    bVar15 = *pbVar1;
    uVar18 = (ulong)bVar15;
    uVar17 = (uint)bVar15;
    switch(uVar17) {
    case 0:
code_r0x00104278:
      if (uVar31 == 0) {
        uVar6 = (uint)(param_4 == 2) & (uVar22 ^ 1);
        if (((uint)(param_4 == 2) & (uVar22 ^ 1)) != 0) {
          if (uVar25 < param_2) {
            param_1[uVar25] = 0x27;
          }
          if (uVar25 + 1 < param_2) {
            param_1[uVar25 + 1] = 0x24;
          }
          if (uVar25 + 2 < param_2) {
            param_1[uVar25 + 2] = 0x27;
          }
          uVar17 = uVar6;
          uVar22 = uVar6;
          if (uVar25 + 3 < param_2) {
            bVar15 = 0x30;
            param_1[uVar25 + 3] = 0x5c;
            uVar25 = uVar25 + 4;
            uVar32 = uVar31;
          }
          else {
            bVar15 = 0x30;
            uVar25 = uVar25 + 4;
            uVar32 = uVar31;
          }
          goto LAB_00103b44;
        }
        goto LAB_00104188;
      }
      if (param_4 == 2) {
        param_4 = 4;
      }
      goto LAB_00103f78;
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
      goto code_r0x00103b9c;
    case 7:
      uVar7 = 0;
      uVar32 = 0;
      bVar15 = 0x61;
      break;
    case 8:
      uVar7 = 0;
      uVar32 = 0;
      bVar15 = 0x62;
      break;
    case 9:
      bVar15 = 0x74;
      goto joined_r0x00104338;
    case 10:
      bVar15 = 0x6e;
joined_r0x00104338:
      uVar7 = 0;
      uVar29 = 0;
      goto joined_r0x00103edc;
    case 0xb:
      uVar7 = 0;
      uVar32 = 0;
      bVar15 = 0x76;
      break;
    case 0xc:
      uVar7 = 0;
      uVar32 = 0;
      bVar15 = 0x66;
      break;
    case 0xd:
      uVar7 = 0;
      bVar15 = 0x72;
      uVar29 = 0;
      goto joined_r0x00103edc;
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
      uVar29 = 0;
      uVar32 = uVar6;
      goto code_r0x00103a88;
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
code_r0x00104268:
      uVar6 = 0;
LAB_0010426c:
      uVar29 = uVar6;
      uVar32 = 0;
      goto code_r0x00103a88;
    case 0x23:
      uVar6 = 0;
      goto LAB_00103f30;
    case 0x27:
      local_d8 = uVar6;
      uVar29 = 0;
      uVar32 = uVar6;
      goto code_r0x00103a88;
    case 0x3f:
      uVar6 = 0;
      goto code_r0x00103d94;
    default:
      if (0x7a < bVar15) {
        if (uVar17 == 0x7d) {
          uVar6 = 0;
        }
        else {
          if (0x7d < uVar17) {
            uVar29 = 0;
            if (uVar17 == 0x7e) goto LAB_00104ac0;
            goto code_r0x00103b9c;
          }
          uVar6 = 0;
          if (uVar17 != 0x7b) goto LAB_00104694;
        }
        goto LAB_00103f18;
      }
      if (uVar17 == 0x40) {
code_r0x00103b9c:
        uVar6 = 0;
code_r0x00103ba4:
joined_r0x001044cc:
        uVar34 = uVar23;
        if (sVar9 != 1) {
          local_70.__count = 0;
          local_70.__value = (_union_27)0x0;
          if (uVar30 == 0xffffffffffffffff) {
            uVar30 = strlen(param_3);
          }
          uVar11 = 0;
          local_f0 = (byte *)0x105580;
LAB_0010458c:
          uVar13 = uVar28 + uVar11;
          pbVar1 = (byte *)(param_3 + uVar13);
          if (pbVar1 == (byte *)0x0) {
            pwVar26 = (wint_t *)0x0;
            lVar20 = 1;
            pbVar21 = local_f0;
            uVar7 = uVar33;
          }
          else {
            lVar20 = uVar30 - uVar13;
            pwVar26 = &local_74;
            pbVar21 = pbVar1;
            uVar7 = (uint)(lVar20 != 0);
          }
          uVar12 = mbrtoc32(pwVar26,pbVar21,lVar20,&local_70);
          if (uVar7 == 0 || uVar12 < 0xfffffffffffffffe) {
            if (uVar12 == 0) goto LAB_00104618;
            if (uVar12 == 0xffffffffffffffff) {
              uVar32 = 0;
              goto LAB_00104658;
            }
            if (uVar12 == 0xfffffffffffffffe) goto joined_r0x001047a8;
            if (uVar12 != 0xfffffffffffffffd) {
              if (uVar31 != 0 && param_4 == 2) {
                if (uVar12 == 1) goto LAB_001048d8;
                pbVar21 = (byte *)(param_3 + uVar13 + 1);
                do {
                  uVar7 = *pbVar21 - 0x5b & 0xff;
                  if ((uVar7 < 0x22) && ((0x20000002bU >> ((ulong)uVar7 & 0x3f) & 1) != 0)) {
                    param_4 = 2;
                    goto LAB_00103f6c;
                  }
                  pbVar21 = pbVar21 + 1;
                } while (pbVar1 + uVar12 != pbVar21);
              }
LAB_001045f8:
              uVar11 = uVar11 + uVar12;
            }
LAB_001045fc:
            iVar8 = iswprint(local_74);
            if (iVar8 == 0) {
              uVar32 = 0;
            }
            iVar8 = mbsinit(&local_70);
            if (iVar8 != 0) goto LAB_00104618;
            goto LAB_0010458c;
          }
          uVar14 = FUN_00103810();
          if ((uVar14 & 1) == 0) {
            if (pwVar26 != (wint_t *)0x0) {
              uVar12 = 1;
              *pwVar26 = (uint)*pbVar21;
              if (uVar31 == 0 || param_4 != 2) goto LAB_001045f8;
            }
LAB_001048d8:
            uVar11 = uVar11 + 1;
            goto LAB_001045fc;
          }
          if (uVar12 != 0xffffffffffffffff) {
joined_r0x001047a8:
            while ((uVar13 < uVar30 && (param_3[uVar13] != '\0'))) {
              uVar11 = uVar11 + 1;
              uVar13 = uVar28 + uVar11;
            }
          }
          uVar32 = 0;
          goto LAB_00104658;
        }
        ppuVar10 = __ctype_b_loc();
        bVar4 = ((*ppuVar10)[uVar18] & 0x4000) == 0;
        uVar32 = (uint)!bVar4;
        uVar34 = uVar23 & bVar4;
        uVar11 = 1;
        goto joined_r0x00104660;
      }
      uVar13 = 1L << ((ulong)(uVar17 - 0x41) & 0x3f);
      if ((uVar13 & 0x3ffffff53ffffff) != 0) {
        uVar29 = 0;
        goto LAB_001048e4;
      }
      if ((uVar13 & 0xa4000000) != 0) goto code_r0x00104268;
LAB_0010445c:
      uVar29 = 0;
      if ((uVar23 & uVar31) == 0) goto LAB_001046d4;
      if (__n != 0) {
        uVar28 = uVar28 + 1;
        uVar32 = 0;
        bVar15 = 0x5c;
        goto LAB_00103b54;
      }
      goto LAB_00103f78;
    }
    goto joined_r0x00103e7c;
  }
  if (uVar31 != 0) goto LAB_00103f78;
  bVar15 = *pbVar1;
  uVar18 = (ulong)bVar15;
  uVar7 = 0;
  switch(uVar18) {
  case 0:
LAB_00104188:
    uVar11 = uVar25 + 1;
    if (uVar25 < param_2) {
      param_1[uVar25] = 0x5c;
    }
    if (uVar2 != 0) {
      if ((uVar28 + 1 < uVar30) && ((byte)(param_3[uVar28 + 1] - 0x30U) < 10)) {
        if (uVar11 < param_2) {
          param_1[uVar11] = 0x30;
        }
        if (uVar25 + 2 < param_2) {
          param_1[uVar25 + 2] = 0x30;
        }
        uVar11 = uVar25 + 3;
      }
      uVar18 = 0x30;
      uVar32 = 0;
      uVar29 = uVar6;
      goto LAB_00103a98;
    }
    bVar15 = 0x30;
    uVar32 = 0;
    uVar25 = uVar11;
    uVar17 = uVar34;
    bVar3 = 0x30;
    if (uVar6 == 0) goto LAB_00103b44;
    goto LAB_00103ab0;
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
    goto code_r0x00103ba4;
  case 7:
    bVar15 = 0x61;
    uVar32 = uVar31;
    break;
  case 8:
    uVar7 = 0;
    bVar15 = 0x62;
    uVar32 = 0;
    break;
  case 9:
    bVar15 = 0x74;
    goto joined_r0x00103edc;
  case 10:
    bVar15 = 0x6e;
    goto joined_r0x00103edc;
  case 0xb:
    uVar7 = 0;
    bVar15 = 0x76;
    uVar32 = 0;
    break;
  case 0xc:
    uVar7 = 0;
    bVar15 = 0x66;
    uVar32 = 0;
    break;
  case 0xd:
    bVar15 = 0x72;
    goto joined_r0x00103edc;
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
    uVar32 = uVar6;
    goto code_r0x00103a88;
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
    uVar32 = uVar31;
    goto code_r0x00103a88;
  case 0x23:
    goto code_r0x00103f2c;
  case 0x27:
    local_d8 = uVar6;
    uVar32 = uVar6;
    goto code_r0x00103a88;
  case 0x3f:
code_r0x00103d94:
    uVar29 = uVar6;
    if ((((param_4 == 5) && ((local_c8 >> 2 & 1) != 0)) && (uVar11 = uVar28 + 2, uVar11 < uVar30))
       && (pbVar1[1] == 0x3f)) {
      bVar15 = param_3[uVar11];
      uVar18 = 0x3f;
      if (0x3e < bVar15) goto LAB_0010426c;
      uVar13 = 0x7000a38200000000 >> ((ulong)bVar15 & 0x3f);
      uVar32 = (uint)uVar13 & 1;
      if ((uVar13 & 1) == 0) goto code_r0x00103a88;
      if (uVar31 != 0) goto LAB_00103f78;
      if (uVar25 < param_2) {
        param_1[uVar25] = 0x3f;
      }
      if (uVar25 + 1 < param_2) {
        param_1[uVar25 + 1] = 0x22;
      }
      if (uVar25 + 2 < param_2) {
        param_1[uVar25 + 2] = 0x22;
      }
      if (uVar25 + 3 < param_2) {
        param_1[uVar25 + 3] = 0x3f;
      }
      uVar25 = uVar25 + 4;
      uVar18 = (ulong)bVar15;
      uVar28 = uVar11;
      uVar32 = uVar31;
    }
    else {
      uVar18 = 0x3f;
      uVar32 = 0;
    }
    goto code_r0x00103a88;
  default:
    uVar7 = (uint)bVar15;
    if (0x7a < bVar15) {
      if (bVar15 == 0x7d) goto LAB_00103f18;
      if (bVar15 < 0x7e) {
        if (uVar7 == 0x7b) goto LAB_00103f18;
LAB_00104694:
        uVar18 = 0x7c;
        uVar29 = uVar6;
        uVar32 = 0;
      }
      else {
        if (uVar7 != 0x7e) goto code_r0x00103ba4;
LAB_00104ac0:
        if (uVar28 != 0) {
          uVar32 = 0;
          uVar34 = 0;
          uVar18 = 0x7e;
          goto LAB_00103a98;
        }
        uVar18 = 0x7e;
        uVar32 = uVar6;
      }
      goto code_r0x00103a88;
    }
    if (uVar7 == 0x40) goto code_r0x00103ba4;
    uVar13 = 1L << ((ulong)(uVar7 - 0x41) & 0x3f);
    if ((uVar13 & 0x3ffffff53ffffff) != 0) {
LAB_001048e4:
      uVar34 = 0;
      uVar32 = uVar6;
      goto LAB_00103a98;
    }
    if ((uVar13 & 0xa4000000) != 0) goto LAB_0010426c;
LAB_001046d4:
    uVar32 = uVar23;
    if (uVar23 == 0) goto code_r0x00103a88;
    uVar32 = 0;
    bVar15 = 0x5c;
    goto LAB_00103b10;
  }
  goto LAB_00103ac0;
LAB_00104ce0:
  param_4 = 5;
  param_2 = local_b8;
  goto LAB_00103958;
LAB_00104618:
  uVar34 = uVar23 & (uVar32 ^ 1);
LAB_00104658:
  if (uVar11 < 2) {
joined_r0x00104660:
    uVar29 = uVar6;
    if (uVar34 != 0) {
      uVar32 = 0;
      uVar34 = uVar23;
      goto LAB_00103c24;
    }
code_r0x00103a88:
    bVar15 = (byte)uVar18;
    uVar34 = uVar2 | uVar31;
    uVar11 = uVar25;
    if (uVar2 != 0 || uVar31 != 0) {
      uVar34 = 0;
LAB_00103a98:
      bVar15 = (byte)uVar18;
      if ((param_6 == 0) ||
         (bVar3 = bVar15,
         (*(uint *)(param_6 + (uVar18 >> 5) * 4) >> (ulong)((uint)uVar18 & 0x1f) & 1) == 0))
      goto LAB_00103aac;
LAB_00103ab0:
      bVar15 = bVar3;
      uVar7 = (uint)(param_4 == 2);
      uVar25 = uVar11;
joined_r0x00103e7c:
      if (uVar31 != 0) {
        uVar19 = uVar23 & uVar7;
        goto LAB_00103f6c;
      }
LAB_00103ac0:
      uVar7 = uVar7 & (uVar22 ^ 1);
      if (uVar7 != 0) {
        if (uVar25 < param_2) {
          param_1[uVar25] = 0x27;
        }
        if (uVar25 + 1 < param_2) {
          param_1[uVar25 + 1] = 0x24;
        }
        if (uVar25 + 2 < param_2) {
          param_1[uVar25 + 2] = 0x27;
        }
        uVar25 = uVar25 + 3;
        uVar22 = uVar7;
      }
LAB_00103b10:
      if (uVar25 < param_2) {
        param_1[uVar25] = 0x5c;
      }
      uVar25 = uVar25 + 1;
      uVar28 = uVar28 + 1;
      goto LAB_00103b28;
    }
LAB_00103aac:
    uVar25 = uVar11;
    uVar17 = uVar34;
    bVar3 = bVar15;
    if (uVar29 != 0) goto LAB_00103ab0;
LAB_00103b44:
    uVar28 = uVar28 + 1;
    uVar7 = uVar22 & (uVar17 ^ 1);
  }
  else {
LAB_00103c24:
    uVar11 = uVar28 + uVar11;
    uVar19 = 0;
    if (uVar34 == 0) goto LAB_00103d08;
    while( true ) {
      uVar19 = (uint)(param_4 == 2);
      uVar33 = (uint)(param_4 == 2);
      if (uVar31 != 0) goto LAB_00103f6c;
      if ((uVar33 & (uVar22 ^ 1)) != 0) {
        if (uVar25 < param_2) {
          param_1[uVar25] = 0x27;
        }
        if (uVar25 + 1 < param_2) {
          param_1[uVar25 + 1] = 0x24;
        }
        if (uVar25 + 2 < param_2) {
          param_1[uVar25 + 2] = 0x27;
        }
        uVar25 = uVar25 + 3;
        uVar22 = uVar33 & (uVar22 ^ 1);
      }
      if (uVar25 < param_2) {
        param_1[uVar25] = 0x5c;
      }
      if (uVar25 + 1 < param_2) {
        param_1[uVar25 + 1] = (char)(uVar18 >> 6) + '0';
      }
      if (uVar25 + 2 < param_2) {
        param_1[uVar25 + 2] = ((byte)(uVar18 >> 3) & 7) + 0x30;
      }
      uVar28 = uVar28 + 1;
      uVar19 = ((uint)uVar18 & 7) + 0x30;
      bVar15 = (byte)uVar19;
      uVar18 = (ulong)uVar19;
      uVar25 = uVar25 + 3;
      uVar7 = uVar31;
      uVar19 = uVar34;
      if (uVar11 <= uVar28) break;
      while( true ) {
        if (uVar25 < param_2) {
          param_1[uVar25] = (char)uVar18;
        }
        uVar18 = (ulong)(byte)param_3[uVar28];
        uVar25 = uVar25 + 1;
        if (uVar34 != 0) break;
LAB_00103d08:
        bVar15 = (byte)uVar18;
        uVar7 = uVar22 & (uVar19 ^ 1);
        if (uVar6 != 0) {
          if (uVar25 < param_2) {
            param_1[uVar25] = 0x5c;
          }
          uVar25 = uVar25 + 1;
        }
        uVar28 = uVar28 + 1;
        if (uVar11 <= uVar28) goto LAB_00103b54;
        if (uVar7 == 0) {
          uVar6 = 0;
        }
        else {
          if (uVar25 < param_2) {
            param_1[uVar25] = 0x27;
          }
          if (uVar25 + 1 < param_2) {
            param_1[uVar25 + 1] = 0x27;
          }
          uVar25 = uVar25 + 2;
          uVar22 = uVar34;
          uVar6 = uVar34;
        }
      }
    }
  }
LAB_00103b54:
  if (uVar7 != 0) {
    if (uVar25 < param_2) {
      param_1[uVar25] = 0x27;
    }
    if (uVar25 + 1 < param_2) {
      param_1[uVar25 + 1] = 0x27;
    }
    uVar25 = uVar25 + 2;
    uVar22 = 0;
  }
LAB_00103b28:
  if (uVar25 < param_2) {
    param_1[uVar25] = bVar15;
  }
  uVar25 = uVar25 + 1;
  if (uVar32 == 0) {
    uVar24 = uVar32;
  }
  goto LAB_001039f8;
LAB_00103fa8:
  if (uVar25 != 0 || param_4 != 2) {
    uVar32 = uVar31 ^ 1;
    if (param_4 != 2 || (uVar31 ^ 1) == 0) goto LAB_00104804;
  }
  else if (uVar31 != 0) {
LAB_00103f58:
    param_4 = 2;
LAB_00103f6c:
    if (uVar19 != 0) {
      param_4 = 4;
    }
LAB_00103f78:
    param_6 = 0;
    local_c8 = local_c8 & 0xfffffffd;
    uVar27 = 0;
    goto LAB_00103958;
  }
  if (local_d8 == 0) {
    uVar32 = 1;
  }
  else {
    if (uVar24 != 0) goto LAB_00104ce0;
    bVar5 = param_2 == 0;
    uVar32 = local_d8;
    if (bVar5 && local_b8 != 0) {
      bVar4 = param_4 == 4;
      uVar32 = 0;
      uVar31 = uVar24;
      param_2 = local_b8;
      local_d8 = (uint)(bVar5 && local_b8 != 0);
      bVar5 = bVar4;
      goto joined_r0x001039bc;
    }
  }
LAB_00104804:
  uVar30 = uVar25;
  if ((local_e0 != (char *)0x0 && uVar32 != 0) && (cVar16 = *local_e0, cVar16 != '\0')) {
    do {
      if (uVar30 < param_2) {
        param_1[uVar30] = cVar16;
      }
      uVar30 = uVar30 + 1;
      cVar16 = local_e0[uVar30 - uVar25];
    } while (cVar16 != '\0');
  }
  if (uVar30 < param_2) {
    param_1[uVar30] = 0;
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_0011ffe0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_0011ffe0,0,
                     local_68 - *(long *)PTR___stack_chk_guard_0011ffe0);
  }
  return uVar30;
}

