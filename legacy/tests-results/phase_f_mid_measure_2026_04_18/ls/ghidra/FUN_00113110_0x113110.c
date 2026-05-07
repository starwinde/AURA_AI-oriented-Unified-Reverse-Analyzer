
/* WARNING: Restarted to delay deadcode elimination for space: stack */

long FUN_00113110(byte *param_1,long param_2,byte *param_3,tm *param_4,uint param_5,uint param_6,
                 int param_7,long param_8,int param_9)

{
  char *__s;
  int iVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  __int32_t **pp_Var9;
  time_t tVar10;
  ulong uVar11;
  undefined1 uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ulong uVar17;
  long lVar18;
  byte *pbVar19;
  bool bVar20;
  long lVar21;
  char *pcVar22;
  ulong uVar23;
  char *pcVar24;
  uint uVar25;
  uint uVar26;
  int iVar27;
  undefined1 *puVar28;
  byte *pbVar29;
  uint uVar30;
  byte bVar31;
  ulong uVar32;
  size_t sVar33;
  size_t sVar34;
  uint uVar35;
  byte *pbVar36;
  long lVar37;
  undefined4 uVar38;
  tm local_4f0;
  tm local_4b0;
  undefined2 local_470;
  undefined1 local_46e;
  undefined1 local_46d [4];
  char acStack_469 [23];
  char local_452 [754];
  undefined8 local_160;
  long local_68;
  
  local_160 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  piVar8 = __errno_location();
  iVar1 = *piVar8;
  uVar35 = param_4->tm_hour;
  __s = "";
  if (param_4->tm_zone != (char *)0x0) {
    __s = param_4->tm_zone;
  }
  if ((int)uVar35 < 0xd) {
    if (uVar35 == 0) {
      uVar35 = 0xc;
    }
  }
  else {
    uVar35 = uVar35 - 0xc;
  }
  bVar31 = *param_3;
  lVar37 = 0;
joined_r0x001131ac:
  if (bVar31 != 0) {
    pbVar29 = param_3;
    if (bVar31 != 0x25) {
      iVar16 = param_7;
      if (param_7 < 0) {
        iVar16 = 0;
      }
      uVar23 = (ulong)iVar16;
      uVar17 = uVar23;
      if (uVar23 == 0) {
        uVar17 = 1;
      }
      if ((ulong)(param_2 - lVar37) <= uVar17) goto LAB_00113230;
      if (param_1 != (byte *)0x0) {
        if (1 < param_7) {
          memset(param_1,0x20,uVar23 - 1);
          param_1 = param_1 + (uVar23 - 1);
        }
        *param_1 = *param_3;
        param_1 = param_1 + 1;
      }
      lVar21 = lVar37 + uVar17;
      goto LAB_001131f8;
    }
    uVar26 = 0;
    uVar30 = param_5 & 0xff;
    uVar13 = 0;
LAB_001132d0:
    uVar25 = uVar13;
    pbVar29 = pbVar29 + 1;
    uVar13 = (uint)*pbVar29;
    uVar15 = *pbVar29 - 0x23 & 0xff;
    if (uVar15 < 0x3d) {
LAB_001132e4:
      uVar17 = 1L << ((ulong)uVar15 & 0x3f);
      if ((uVar17 & 0x1000000000002500) == 0) {
        if (uVar15 != 0x3b) {
          uVar14 = (uint)uVar17 & 1;
          if ((uVar17 & 1) != 0) goto code_r0x00113300;
          if (uVar13 - 0x30 < 10) {
            param_7 = 0;
            do {
              iVar16 = (int)((long)param_7 * 10);
              if (((int)((ulong)((long)param_7 * 10) >> 0x20) != iVar16 >> 0x1f) ||
                 (param_7 = iVar16 + (*pbVar29 - 0x30), SCARRY4(iVar16,*pbVar29 - 0x30))) {
                param_7 = 0x7fffffff;
              }
              pbVar29 = pbVar29 + 1;
              uVar13 = (uint)*pbVar29;
            } while (*pbVar29 - 0x30 < 10);
          }
          if ((uVar13 != 0x45) && (uVar13 != 0x4f)) goto LAB_00113318;
          pbVar29 = pbVar29 + 1;
          uVar14 = (uint)*pbVar29;
          uVar15 = uVar13;
          goto LAB_0011331c;
        }
        uVar30 = 1;
        uVar13 = uVar25;
      }
      goto LAB_001132d0;
    }
LAB_00113318:
    uVar15 = 0;
    uVar14 = uVar13;
LAB_0011331c:
    uVar12 = (undefined1)uVar14;
    pbVar36 = pbVar29;
    lVar21 = lVar37;
    uVar13 = uVar35;
    switch(uVar14) {
    case 0:
      pbVar36 = pbVar29 + -1;
      break;
    case 0x25:
      pbVar36 = pbVar29 + -1;
      if (pbVar29 + -1 != param_3) break;
      pbVar36 = param_1;
      if ((uVar25 == 0x2d) || (param_7 < 0)) {
        if (1 < (ulong)(param_2 - lVar37)) {
          uVar17 = 1;
          if (param_1 == (byte *)0x0) {
            lVar21 = lVar37 + 1;
            goto LAB_001131f8;
          }
          goto LAB_00114770;
        }
      }
      else {
        uVar23 = (ulong)param_7;
        uVar17 = uVar23;
        if (uVar23 == 0) {
          uVar17 = 1;
        }
        if (uVar17 < (ulong)(param_2 - lVar37)) {
          if (param_1 == (byte *)0x0) goto LAB_00113908;
          if (uVar23 < 2) {
            uVar17 = 1;
          }
          else {
            sVar33 = uVar23 - 1;
            if (uVar25 == 0x30 || uVar25 == 0x2b) {
              memset(param_1,0x30,sVar33);
            }
            else {
              memset(param_1,0x20,sVar33);
            }
            pbVar36 = param_1 + sVar33;
          }
LAB_00114770:
          lVar21 = lVar37 + uVar17;
          param_1 = pbVar36 + 1;
          *pbVar36 = *pbVar29;
          goto LAB_001131f8;
        }
      }
      goto LAB_00113230;
    case 0x3a:
      bVar31 = pbVar29[1];
      pbVar19 = pbVar29 + 1;
      uVar17 = 1;
      if (bVar31 == 0x3a) {
        do {
          uVar17 = uVar17 + 1;
          bVar31 = pbVar29[uVar17];
        } while (bVar31 == 0x3a);
        pbVar19 = pbVar29 + uVar17;
      }
      if (bVar31 == 0x7a) goto LAB_00113b40;
      break;
    case 0x41:
    case 0x61:
      if (uVar15 != 0) break;
      if (uVar26 == 0) {
        puVar28 = &local_46e;
      }
      else {
        puVar28 = &local_46e;
        uVar30 = uVar26;
        uVar26 = 0;
      }
      goto LAB_001134e8;
    case 0x42:
      if (uVar15 != 0x45) {
        uVar13 = uVar26;
        if (uVar26 != 0) {
          uVar30 = uVar26;
          uVar13 = 0;
        }
        goto LAB_001134d8;
      }
      break;
    case 0x43:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_year;
        uVar26 = (uint)(iVar27 < -0x76c);
        iVar16 = -99;
        if (0x76b < iVar27 + 0x76cU) {
          iVar16 = 0;
        }
        uVar7 = (uint)(-0x76d < iVar27);
        uVar13 = (iVar16 + iVar27) / 100 + 0x13;
        if (uVar25 == 0) {
          uVar25 = param_6;
        }
        if (uVar25 == 0x2b) {
          iVar16 = 2;
          uVar14 = 99;
LAB_00114380:
          uVar25 = 0x2b;
          uVar7 = uVar26 ^ 1;
          bVar4 = uVar14 < uVar13 || iVar16 < param_7;
          uVar14 = 0;
        }
        else {
          bVar4 = false;
          iVar16 = 2;
          uVar14 = 0;
        }
        goto LAB_00113c00;
      }
      goto LAB_00113920;
    case 0x44:
      if (uVar15 == 0) {
        iVar16 = -1;
        pcVar24 = "%m/%d/%y";
        goto LAB_00113d28;
      }
      break;
    case 0x46:
      if (uVar15 != 0) break;
      if (uVar25 != 0 || -1 < param_7) {
        iVar16 = param_7 + -6;
        if (iVar16 < 0) {
          iVar16 = 0;
        }
        pcVar24 = "%Y-%m-%d";
        goto LAB_00113d28;
      }
      pcVar24 = "%Y-%m-%d";
      uVar23 = FUN_00113110(0,0xffffffffffffffff,"%Y-%m-%d",param_4,uVar30,0x2b,4,param_8,param_9);
      uVar32 = param_2 - lVar37;
      iVar16 = 4;
      uVar25 = 0x2b;
      goto LAB_0011455c;
    case 0x47:
    case 0x56:
    case 0x67:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_year;
        iVar6 = param_4->tm_wday;
        iVar2 = param_4->tm_yday;
        iVar16 = -100;
        if (iVar27 < 0) {
          iVar16 = 300;
        }
        uVar26 = iVar27 + iVar16;
        iVar16 = (iVar2 - ((iVar2 - iVar6) + 0x17e) % 7) + 3;
        if (iVar16 < 0) {
          uVar26 = uVar26 - 1;
          iVar16 = 0x16d;
          if (((uVar26 & 3) == 0) &&
             (iVar16 = 0x16e,
             (uVar26 * -0x3d70a3d7 + 0x51eb850 >> 2 | uVar26 * 0x40000000) < 0x28f5c29)) {
            iVar16 = ((int)uVar26 % 400 == 0) + 0x16d;
          }
          uVar7 = 0xffffffff;
          iVar6 = ((iVar2 + iVar16) - (((iVar2 + iVar16) - iVar6) + 0x17e) % 7) + 3;
        }
        else {
          iVar5 = 0x16d;
          if (((uVar26 & 3) == 0) &&
             (iVar5 = 0x16e,
             (uVar26 * -0x3d70a3d7 + 0x51eb850 >> 2 | iVar27 * 0x40000000) < 0x28f5c29)) {
            iVar5 = ((int)uVar26 % 400 == 0) + 0x16d;
          }
          iVar2 = ((iVar2 - iVar5) - (((iVar2 - iVar5) - iVar6) + 0x17e) % 7) + 3;
          iVar6 = iVar2;
          if (-1 >= iVar2) {
            iVar6 = iVar16;
          }
          uVar7 = (uint)(-1 < iVar2);
        }
        if (uVar14 == 0x47) {
          uVar13 = iVar27 + 0x76c + uVar7;
          uVar26 = (uint)(iVar27 < (int)(-0x76c - uVar7));
          uVar7 = (uint)((int)(-0x76c - uVar7) <= iVar27);
          if (uVar25 == 0) {
            uVar25 = param_6;
          }
          if (uVar25 == 0x2b) {
LAB_00114970:
            iVar16 = 4;
            uVar14 = 9999;
            goto LAB_00114380;
          }
          bVar4 = false;
          iVar16 = 4;
          uVar14 = 0;
          goto LAB_00113c00;
        }
        if (uVar14 == 0x67) {
          uVar13 = (int)(iVar27 % 100 + uVar7) % 100;
          if ((int)uVar13 < 0) {
            if (iVar27 < (int)(-0x76c - uVar7)) {
              uVar13 = -uVar13;
            }
            else {
              uVar13 = uVar13 + 100;
            }
          }
          goto joined_r0x00113740;
        }
        iVar16 = 2;
        uVar13 = iVar6 / 7 + 1;
        goto LAB_00113ce8;
      }
      break;
    case 0x48:
      if (uVar15 != 0x45) {
        uVar13 = param_4->tm_hour;
        iVar16 = 2;
        goto LAB_00113ce8;
      }
      break;
    case 0x49:
      if (uVar15 != 0x45) {
        iVar16 = 2;
        goto LAB_00113ce8;
      }
      break;
    case 0x4d:
      if (uVar15 != 0x45) {
        iVar16 = 2;
        uVar13 = param_4->tm_min;
        goto LAB_00113ce8;
      }
      break;
    case 0x4e:
      if (uVar15 != 0x45) {
        iVar16 = 9;
        iVar27 = param_9;
        if (param_7 < 1) {
          param_7 = 9;
        }
        do {
          if (iVar16 <= param_7) {
            if (iVar16 == 1) {
              uVar17 = 1;
              goto LAB_00113f1c;
            }
            if (iVar27 % 10 != 0) goto code_r0x00113f14;
          }
          iVar16 = iVar16 + -1;
          iVar27 = iVar27 / 10;
        } while( true );
      }
      break;
    case 0x50:
      uVar13 = 1;
      goto LAB_00114320;
    case 0x52:
      iVar16 = -1;
      pcVar24 = "%H:%M";
      goto LAB_00113d28;
    case 0x53:
      if (uVar15 != 0x45) {
        iVar16 = 2;
        uVar13 = param_4->tm_sec;
        goto LAB_00113ce8;
      }
      break;
    case 0x54:
      iVar16 = -1;
      pcVar24 = "%H:%M:%S";
LAB_00113d28:
      uVar23 = FUN_00113110(0,0xffffffffffffffff,pcVar24,param_4,uVar30,uVar25,iVar16,param_8,
                            param_9);
      uVar32 = param_2 - lVar37;
      if ((uVar25 == 0x2d) || (param_7 < 0)) {
LAB_0011455c:
        if (uVar32 <= uVar23) goto LAB_00113230;
        uVar17 = uVar23;
        if (param_1 != (byte *)0x0) goto LAB_00113df4;
        lVar21 = lVar37 + uVar23;
      }
      else {
        uVar11 = (ulong)param_7;
        uVar17 = uVar23;
        if (uVar23 < uVar11) {
          uVar17 = uVar11;
        }
        if (uVar32 <= uVar17) goto LAB_00113230;
        if (param_1 != (byte *)0x0) {
          if (uVar23 < uVar11) {
            sVar33 = uVar11 - uVar23;
            if (uVar25 == 0x30 || uVar25 == 0x2b) {
              memset(param_1,0x30,sVar33);
            }
            else {
              memset(param_1,0x20,sVar33);
            }
            param_1 = param_1 + sVar33;
          }
LAB_00113df4:
          FUN_00113110(param_1,uVar32,pcVar24,param_4,uVar30,uVar25,iVar16,param_8,param_9);
          param_1 = param_1 + uVar23;
        }
LAB_00113e24:
        lVar21 = lVar37 + uVar17;
      }
      goto LAB_001131f8;
    case 0x55:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_yday - param_4->tm_wday;
LAB_00114110:
        iVar16 = 2;
        uVar13 = (iVar27 + 7) / 7;
        goto LAB_00113ce8;
      }
      break;
    case 0x57:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_yday - (param_4->tm_wday + 6) % 7;
        goto LAB_00114110;
      }
      break;
    case 0x58:
    case 99:
    case 0x78:
      if (uVar15 != 0x4f) goto code_r0x001134d4;
      break;
    case 0x59:
      if (uVar15 == 0x45) goto LAB_00113920;
      if (uVar15 == 0x4f) break;
      uVar13 = param_4->tm_year + 0x76c;
      uVar26 = (uint)(param_4->tm_year < -0x76c);
      if (uVar25 == 0) {
        uVar25 = param_6;
      }
      if (uVar25 == 0x2b) goto LAB_00114970;
      uVar14 = 0;
      bVar4 = false;
      iVar16 = 4;
      goto LAB_001137e8;
    case 0x5a:
      if (uVar26 != 0) {
        uVar30 = 0;
      }
      sVar33 = strlen(__s);
      uVar17 = sVar33;
      if ((uVar25 == 0x2d) || (param_7 < 0)) {
        if (sVar33 < (ulong)(param_2 - lVar37)) {
          if (param_1 == (byte *)0x0) {
            lVar21 = lVar37 + sVar33;
            goto LAB_001131f8;
          }
LAB_001142b0:
          if (uVar26 == 0) {
            if ((uVar30 & 1) == 0) {
              memcpy(param_1,__s,sVar33);
            }
            else {
              lVar21 = sVar33 - 1;
              if (sVar33 != 0) {
                pp_Var9 = __ctype_toupper_loc();
                do {
                  param_1[lVar21] = (byte)(*pp_Var9)[(byte)__s[lVar21]];
                  lVar21 = lVar21 + -1;
                } while (lVar21 != -1);
              }
            }
          }
          else {
            lVar21 = sVar33 - 1;
            if (sVar33 != 0) {
              pp_Var9 = __ctype_tolower_loc();
              do {
                param_1[lVar21] = (byte)(*pp_Var9)[(byte)__s[lVar21]];
                lVar21 = lVar21 + -1;
              } while (lVar21 != -1);
            }
          }
          param_1 = param_1 + sVar33;
          lVar21 = lVar37 + uVar17;
          goto LAB_001131f8;
        }
        goto LAB_00113230;
      }
      uVar23 = (ulong)param_7;
      if (sVar33 < uVar23) {
        uVar17 = uVar23;
      }
      if ((ulong)(param_2 - lVar37) <= uVar17) goto LAB_00113230;
      if (param_1 != (byte *)0x0) {
        if (sVar33 < uVar23) {
          sVar34 = uVar23 - sVar33;
          if (uVar25 == 0x30 || uVar25 == 0x2b) {
            memset(param_1,0x30,sVar34);
            param_1 = param_1 + sVar34;
          }
          else {
            memset(param_1,0x20,sVar34);
            param_1 = param_1 + sVar34;
          }
        }
        goto LAB_001142b0;
      }
      goto LAB_00113e24;
    case 0x62:
    case 0x68:
      if (uVar26 != 0) {
        uVar30 = uVar26;
      }
      if (uVar15 != 0x45) goto code_r0x001134d4;
      break;
    case 100:
      if (uVar15 != 0x45) {
        iVar16 = 2;
        uVar13 = param_4->tm_mday;
        goto LAB_00113ce8;
      }
      break;
    case 0x65:
      if (uVar15 != 0x45) {
        uVar13 = param_4->tm_mday;
LAB_00113cdc:
        iVar16 = 2;
        if (uVar25 == 0) {
          uVar25 = 0x5f;
        }
        goto LAB_00113ce8;
      }
      break;
    case 0x6a:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_yday;
        uVar14 = 0;
        bVar4 = false;
        iVar16 = 3;
        uVar13 = iVar27 + 1;
        uVar26 = (uint)(iVar27 < -1);
        uVar7 = (uint)(-2 < iVar27);
        goto LAB_00113c00;
      }
      break;
    case 0x6b:
      if (uVar15 != 0x45) {
        uVar13 = param_4->tm_hour;
        goto LAB_00113cdc;
      }
      break;
    case 0x6c:
      if (uVar15 != 0x45) goto LAB_00113cdc;
      break;
    case 0x6d:
      if (uVar15 != 0x45) {
        iVar27 = param_4->tm_mon;
        uVar14 = 0;
        bVar4 = false;
        iVar16 = 2;
        uVar13 = iVar27 + 1;
        uVar26 = (uint)(iVar27 < -1);
        uVar7 = (uint)(-2 < iVar27);
        goto LAB_00113c00;
      }
      break;
    case 0x6e:
      pbVar36 = param_1;
      if ((uVar25 == 0x2d) || (param_7 < 0)) {
        if (1 < (ulong)(param_2 - lVar37)) {
          uVar17 = 1;
          if (param_1 == (byte *)0x0) {
            lVar21 = lVar37 + 1;
            goto LAB_001131f8;
          }
LAB_00113c90:
          lVar21 = lVar37 + uVar17;
          param_1 = pbVar36 + 1;
          *pbVar36 = 10;
          goto LAB_001131f8;
        }
        goto LAB_00113230;
      }
      uVar23 = (ulong)param_7;
      uVar17 = uVar23;
      if (uVar23 == 0) {
        uVar17 = 1;
      }
      if ((ulong)(param_2 - lVar37) <= uVar17) goto LAB_00113230;
      if (param_1 != (byte *)0x0) {
        if (uVar23 < 2) {
          uVar17 = 1;
        }
        else {
          sVar33 = uVar23 - 1;
          if (uVar25 == 0x30 || uVar25 == 0x2b) {
            memset(param_1,0x30,sVar33);
          }
          else {
            memset(param_1,0x20,sVar33);
          }
          pbVar36 = param_1 + sVar33;
        }
        goto LAB_00113c90;
      }
      goto LAB_00113908;
    case 0x70:
      uVar13 = 0;
LAB_00114320:
      uVar12 = 0x70;
      if (uVar26 != 0) {
        uVar30 = 0;
        uVar13 = uVar26;
      }
LAB_001134d8:
      puVar28 = &local_46e;
      uVar26 = uVar13;
      if (uVar15 != 0) goto LAB_0011392c;
      goto LAB_001134e8;
    case 0x71:
      if (uVar15 == 0x4f) goto LAB_00113920;
      iVar16 = 1;
      uVar14 = 0;
      bVar4 = false;
      uVar26 = 0;
      uVar15 = (param_4->tm_mon * 0xb >> 5) + 1;
      goto LAB_001137f0;
    case 0x72:
code_r0x001134d4:
      uVar13 = 0;
      goto LAB_001134d8;
    case 0x73:
      local_4f0.tm_hour = param_4->tm_hour;
      local_4f0.tm_mday = param_4->tm_mday;
      local_4f0.tm_sec = param_4->tm_sec;
      local_4f0.tm_min = param_4->tm_min;
      uVar38 = param_4->tm_wday;
      local_4f0.tm_mon = param_4->tm_mon;
      local_4f0.tm_year = param_4->tm_year;
      local_4f0.tm_gmtoff = param_4->tm_gmtoff;
      local_4f0.tm_isdst = param_4->tm_isdst;
      local_4f0._36_4_ = *(undefined4 *)&param_4->field_0x24;
      local_4f0.tm_zone = param_4->tm_zone;
      local_4f0.tm_yday = 0xffffffff;
      local_4f0.tm_wday = uVar38;
      if (param_8 == 0) {
        tVar10 = timegm(&local_4f0);
      }
      else {
        lVar21 = FUN_0010d1e4(param_8);
        if (lVar21 != 0) {
          local_4b0.tm_hour = local_4f0.tm_hour;
          local_4b0.tm_mday = local_4f0.tm_mday;
          local_4b0.tm_sec = local_4f0.tm_sec;
          local_4b0.tm_min = local_4f0.tm_min;
          local_4b0.tm_mon = local_4f0.tm_mon;
          local_4b0.tm_year = local_4f0.tm_year;
          local_4b0.tm_yday = -1;
          local_4b0.tm_isdst = local_4f0.tm_isdst;
          tVar10 = mktime(&local_4b0);
          if ((local_4b0.tm_yday < 0) || (uVar17 = FUN_0010d080(param_8), (uVar17 & 1) == 0)) {
            if (lVar21 != 1) {
              FUN_0010d304(lVar21);
            }
          }
          else if ((lVar21 == 1) || (uVar17 = FUN_0010d304(lVar21), (uVar17 & 1) != 0))
          goto LAB_00113a84;
        }
        tVar10 = -1;
      }
LAB_00113a84:
      if (-1 < (long)local_4f0._24_8_) {
        pcVar24 = local_452 + 1;
        lVar21 = tVar10;
        do {
          lVar18 = lVar21 / 10 + (lVar21 >> 0x3f);
          cVar3 = (char)lVar21 + ((char)lVar18 - (char)(lVar21 >> 0x3f)) * -10;
          if (tVar10 < 0) {
            cVar3 = -cVar3;
          }
          pcVar24 = pcVar24 + -1;
          *pcVar24 = cVar3 + '0';
          lVar21 = lVar18 - (lVar21 >> 0x3f);
        } while (lVar21 != 0);
        uVar26 = (uint)((ulong)tVar10 >> 0x3f);
        bVar4 = false;
        iVar16 = 1;
        goto LAB_00113848;
      }
      *piVar8 = 0x4b;
      goto LAB_00113238;
    case 0x74:
      pbVar36 = param_1;
      if ((uVar25 == 0x2d) || (param_7 < 0)) {
        if (1 < (ulong)(param_2 - lVar37)) {
          uVar17 = 1;
          if (param_1 == (byte *)0x0) {
            lVar21 = lVar37 + 1;
            goto LAB_001131f8;
          }
          goto LAB_001139a0;
        }
      }
      else {
        uVar23 = (ulong)param_7;
        uVar17 = uVar23;
        if (uVar23 == 0) {
          uVar17 = 1;
        }
        if (uVar17 < (ulong)(param_2 - lVar37)) {
          if (param_1 == (byte *)0x0) goto LAB_00113908;
          if (uVar23 < 2) {
            uVar17 = 1;
          }
          else {
            sVar33 = uVar23 - 1;
            if (uVar25 == 0x30 || uVar25 == 0x2b) {
              memset(param_1,0x30,sVar33);
            }
            else {
              memset(param_1,0x20,sVar33);
            }
            pbVar36 = param_1 + sVar33;
          }
LAB_001139a0:
          lVar21 = lVar37 + uVar17;
          param_1 = pbVar36 + 1;
          *pbVar36 = 9;
          goto LAB_001131f8;
        }
      }
      goto LAB_00113230;
    case 0x75:
      iVar16 = 1;
      uVar13 = (param_4->tm_wday + 6) % 7 + 1;
LAB_00113ce8:
      uVar14 = 0;
      uVar26 = uVar13 >> 0x1f;
      bVar4 = false;
      uVar7 = ~uVar13 >> 0x1f;
      goto LAB_00113c00;
    case 0x77:
      if (uVar15 != 0x45) {
        iVar16 = 1;
        uVar13 = param_4->tm_wday;
        goto LAB_00113ce8;
      }
      break;
    case 0x79:
      if (uVar15 != 0x45) {
        uVar26 = param_4->tm_year % 100;
        uVar13 = uVar26;
        if (((int)uVar26 < 0) && (uVar13 = uVar26 + 100, param_4->tm_year < -0x76c)) {
          uVar13 = -uVar26;
        }
joined_r0x00113740:
        uVar26 = param_6;
        if (uVar25 != 0) {
          uVar26 = uVar25;
        }
        uVar25 = uVar26;
        if (uVar25 == 0x2b) {
          uVar26 = 0;
          iVar16 = 2;
          uVar14 = 99;
          goto LAB_00114380;
        }
        uVar7 = 1;
        bVar4 = false;
        uVar26 = 0;
        iVar16 = 2;
        uVar14 = 0;
        goto LAB_00113c00;
      }
LAB_00113920:
      uVar13 = 0;
LAB_0011392c:
      puVar28 = local_46d;
      local_46e = (undefined1)uVar15;
      uVar26 = uVar13;
LAB_001134e8:
      local_470 = 0x2520;
      *puVar28 = uVar12;
      puVar28[1] = 0;
      sVar33 = strftime(acStack_469 + 1,0x400,(char *)&local_470,param_4);
      if (sVar33 != 0) {
        uVar23 = sVar33 - 1;
        uVar17 = uVar23;
        if ((uVar25 == 0x2d) || (param_7 < 0)) {
          if ((ulong)(param_2 - lVar37) <= uVar23) goto LAB_00113230;
          if (param_1 != (byte *)0x0) goto LAB_001135b0;
          lVar21 = lVar37 + uVar23;
        }
        else {
          uVar32 = (ulong)param_7;
          if (uVar23 < uVar32) {
            uVar17 = uVar32;
          }
          if ((ulong)(param_2 - lVar37) <= uVar17) goto LAB_00113230;
          if (param_1 != (byte *)0x0) {
            if (uVar23 < uVar32) {
              sVar34 = uVar32 - uVar23;
              if (uVar25 == 0x30 || uVar25 == 0x2b) {
                memset(param_1,0x30,sVar34);
                param_1 = param_1 + sVar34;
              }
              else {
                memset(param_1,0x20,sVar34);
                param_1 = param_1 + sVar34;
              }
            }
LAB_001135b0:
            if (uVar26 == 0) {
              if ((uVar30 & 1) == 0) {
                memcpy(param_1,acStack_469 + 2,uVar23);
                param_1 = param_1 + uVar23;
              }
              else {
                lVar21 = sVar33 - 2;
                if (uVar23 != 0) {
                  pp_Var9 = __ctype_toupper_loc();
                  do {
                    param_1[lVar21] = (byte)(*pp_Var9)[(byte)acStack_469[lVar21 + 2]];
                    lVar21 = lVar21 + -1;
                  } while (lVar21 != -1);
                }
LAB_001135f8:
                param_1 = param_1 + uVar23;
              }
            }
            else {
              lVar21 = sVar33 - 2;
              if (uVar23 == 0) goto LAB_001135f8;
              pp_Var9 = __ctype_tolower_loc();
              do {
                param_1[lVar21] = (byte)(*pp_Var9)[(byte)acStack_469[lVar21 + 2]];
                lVar21 = lVar21 + -1;
              } while (lVar21 != -1);
              param_1 = param_1 + uVar23;
            }
          }
          lVar21 = lVar37 + uVar17;
        }
      }
      goto LAB_001131f8;
    case 0x7a:
      uVar17 = 0;
      pbVar19 = pbVar29;
LAB_00113b40:
      pbVar29 = pbVar19;
      if (param_4->tm_isdst < 0) goto LAB_001131f8;
      uVar26 = 1;
      iVar27 = (int)param_4->tm_gmtoff;
      if ((-1 < iVar27) && (uVar26 = 0, iVar27 == 0)) {
        uVar26 = (uint)(*__s == '-');
      }
      uVar13 = iVar27 / 0xe10;
      iVar6 = (iVar27 / 0x3c) % 0x3c;
      if (uVar17 == 2) {
LAB_0011499c:
        uVar7 = uVar26 ^ 1;
        bVar4 = true;
        iVar16 = 9;
        uVar14 = 0x14;
        uVar13 = iVar6 * 100 + uVar13 * 10000 + iVar27 % 0x3c;
      }
      else if (uVar17 < 3) {
        if (uVar17 == 0) {
          uVar7 = uVar26 ^ 1;
          bVar4 = true;
          iVar16 = 5;
          uVar13 = iVar6 + uVar13 * 100;
          uVar14 = 0;
        }
        else {
LAB_00113be4:
          uVar7 = uVar26 ^ 1;
          bVar4 = true;
          iVar16 = 6;
          uVar13 = iVar6 + uVar13 * 100;
          uVar14 = 4;
        }
      }
      else {
        pbVar36 = pbVar29;
        if (uVar17 != 3) break;
        if (iVar27 % 0x3c != 0) goto LAB_0011499c;
        if (iVar6 != 0) goto LAB_00113be4;
        iVar16 = 3;
        uVar7 = uVar26 ^ 1;
        bVar4 = true;
        uVar14 = 0;
      }
LAB_00113c00:
      if (uVar15 == 0x4f && uVar7 != 0) goto LAB_00113920;
LAB_001137e8:
      uVar15 = -uVar13;
      if (uVar26 == 0) {
        uVar15 = uVar13;
      }
LAB_001137f0:
      pcVar24 = local_452 + 1;
      while( true ) {
        pcVar22 = pcVar24;
        if ((uVar14 & 1) != 0) {
          pcVar22 = pcVar24 + -1;
          pcVar24[-1] = ':';
        }
        uVar14 = (int)uVar14 >> 1;
        pcVar24 = pcVar22 + -1;
        pcVar22[-1] = (char)uVar15 + (char)(uVar15 / 10) * -10 + '0';
        if (uVar14 == 0 && uVar15 < 10) break;
        uVar15 = uVar15 / 10;
      }
LAB_00113848:
      uVar13 = uVar25;
      if (uVar25 == 0) {
        uVar13 = 0x30;
      }
      bVar20 = uVar25 != 0x2d;
      iVar27 = ((int)local_452 + 1) - (int)pcVar24;
      if (-1 < param_7) {
        iVar16 = param_7;
      }
      if (uVar26 != 0) {
        bVar31 = 0x2d;
        iVar6 = (iVar16 + -1) - iVar27;
        if (iVar6 < 1 || !bVar20) {
          iVar6 = 0;
        }
LAB_00113880:
        if (uVar13 == 0x5f) {
          sVar33 = (size_t)iVar6;
          lVar37 = lVar37 + sVar33;
          iVar16 = iVar16 - iVar6;
          if (param_1 == (byte *)0x0) {
            if (1 < (ulong)(param_2 - lVar37)) {
              lVar37 = lVar37 + 1;
              goto LAB_001138ac;
            }
          }
          else {
            memset(param_1,0x20,sVar33);
            param_1 = param_1 + sVar33;
            if (1 < (ulong)(param_2 - lVar37)) goto LAB_00113898;
          }
        }
        else if (1 < (ulong)(param_2 - lVar37)) {
          pbVar36 = param_1;
          if (param_1 != (byte *)0x0) {
LAB_00113898:
            pbVar36 = param_1 + 1;
            *param_1 = bVar31;
          }
          lVar37 = lVar37 + 1;
          param_1 = pbVar36;
          if (!bVar20) goto LAB_00113224;
LAB_001138ac:
          iVar16 = iVar16 + -1;
          uVar23 = param_2 - lVar37;
          if (-1 < iVar16) goto LAB_00114438;
          if ((ulong)(long)iVar27 < uVar23) goto LAB_001138bc;
        }
        goto LAB_00113230;
      }
      if (bVar4) {
        bVar31 = 0x2b;
        iVar6 = (iVar16 + -1) - iVar27;
        if (iVar6 < 1 || !bVar20) {
          iVar6 = 0;
        }
        goto LAB_00113880;
      }
      if (iVar16 - iVar27 < 1 || !bVar20) {
        if (bVar20) {
          uVar23 = param_2 - lVar37;
          goto LAB_00114438;
        }
LAB_00113224:
        if ((ulong)(param_2 - lVar37) <= (ulong)(long)iVar27) goto LAB_00113230;
LAB_001138bc:
        uVar17 = (ulong)iVar27;
        if (param_1 != (byte *)0x0) {
LAB_001138c4:
          sVar33 = (size_t)iVar27;
          if ((uVar30 & 1) == 0) {
            memcpy(param_1,pcVar24,sVar33);
            param_1 = param_1 + sVar33;
          }
          else {
            lVar21 = sVar33 - 1;
            if (sVar33 != 0) {
              pp_Var9 = __ctype_toupper_loc();
              do {
                param_1[lVar21] = (byte)(*pp_Var9)[(byte)pcVar24[lVar21]];
                lVar21 = lVar21 + -1;
              } while (lVar21 != -1);
            }
            param_1 = param_1 + sVar33;
          }
        }
      }
      else {
        uVar23 = param_2 - lVar37;
LAB_00114438:
        uVar11 = (ulong)iVar27;
        uVar32 = (ulong)iVar16;
        uVar17 = uVar32;
        if (uVar32 < uVar11) {
          uVar17 = uVar11;
        }
        if (uVar23 <= uVar17) goto LAB_00113230;
        if (param_1 != (byte *)0x0) {
          if (uVar11 < uVar32) {
            sVar33 = uVar32 - uVar11;
            if (uVar13 == 0x30 || uVar13 == 0x2b) {
              memset(param_1,0x30,sVar33);
              param_1 = param_1 + sVar33;
            }
            else {
              memset(param_1,0x20,sVar33);
              param_1 = param_1 + sVar33;
            }
          }
          goto LAB_001138c4;
        }
      }
LAB_00113908:
      lVar21 = lVar37 + uVar17;
      goto LAB_001131f8;
    }
    pbVar29 = pbVar36;
    lVar21 = (long)pbVar29 - (long)param_3;
    uVar17 = lVar21 + 1;
    uVar23 = uVar17;
    if ((uVar25 == 0x2d) || (param_7 < 0)) {
      if (uVar17 < (ulong)(param_2 - lVar37)) {
        if (param_1 != (byte *)0x0) {
          if ((uVar30 & 1) == 0) goto LAB_0011349c;
LAB_001133ac:
          if (uVar17 != 0) {
            pp_Var9 = __ctype_toupper_loc();
            do {
              param_1[lVar21] = (byte)(*pp_Var9)[param_3[lVar21]];
              lVar21 = lVar21 + -1;
            } while (lVar21 != -1);
          }
          param_1 = param_1 + uVar17;
        }
        goto LAB_001133e8;
      }
      goto LAB_00113230;
    }
    uVar32 = (ulong)param_7;
    if (uVar17 < uVar32) {
      uVar23 = uVar32;
    }
    if ((ulong)(param_2 - lVar37) <= uVar23) goto LAB_00113230;
    if (param_1 != (byte *)0x0) {
      if (uVar17 < uVar32) {
        sVar33 = uVar32 - uVar17;
        if (uVar25 == 0x30 || uVar25 == 0x2b) {
          memset(param_1,0x30,sVar33);
          param_1 = param_1 + sVar33;
        }
        else {
          memset(param_1,0x20,sVar33);
          param_1 = param_1 + sVar33;
        }
      }
      if ((uVar30 & 1) != 0) goto LAB_001133ac;
LAB_0011349c:
      memcpy(param_1,param_3,uVar17);
      param_1 = param_1 + uVar17;
    }
LAB_001133e8:
    lVar21 = lVar37 + uVar23;
    goto LAB_001131f8;
  }
  if (param_1 != (byte *)0x0 && param_2 != 0) {
    *param_1 = 0;
  }
  *piVar8 = iVar1;
LAB_0011323c:
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return lVar37;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
code_r0x00113300:
  pbVar29 = pbVar29 + 1;
  uVar13 = (uint)*pbVar29;
  uVar15 = *pbVar29 - 0x23 & 0xff;
  uVar26 = uVar14;
  if (0x3c < uVar15) goto LAB_00113318;
  goto LAB_001132e4;
code_r0x00113f14:
  uVar17 = (ulong)iVar16;
LAB_00113f1c:
  uVar23 = uVar17;
  do {
    uVar32 = uVar23 - 1;
    acStack_469[uVar23] = (char)iVar27 + (char)(iVar27 / 10) * -10 + '0';
    uVar23 = uVar32;
    iVar27 = iVar27 / 10;
  } while ((int)uVar32 != 0);
  bVar4 = (ulong)(param_2 - lVar37) <= uVar17;
  if (uVar25 == 0) {
    if (bVar4) goto LAB_00113230;
    uVar25 = 0x30;
    if (param_1 != (byte *)0x0) {
LAB_00113f74:
      if ((uVar30 & 1) == 0) {
        memcpy(param_1,acStack_469 + 1,uVar17);
      }
      else {
        pp_Var9 = __ctype_toupper_loc();
        lVar21 = uVar17 - 2;
        do {
          param_1[lVar21 + 1] = (byte)(*pp_Var9)[(byte)acStack_469[lVar21 + 2]];
          lVar21 = lVar21 + -1;
        } while (lVar21 != -2);
      }
      param_1 = param_1 + uVar17;
      goto LAB_00113fc4;
    }
    uVar23 = (ulong)(param_7 - iVar16);
    if (param_2 - (lVar37 + uVar17) <= (ulong)(long)(param_7 - iVar16)) goto LAB_00113230;
  }
  else {
    if (bVar4) goto LAB_00113230;
    if (param_1 != (byte *)0x0) goto LAB_00113f74;
LAB_00113fc4:
    lVar21 = lVar37 + uVar17;
    if (uVar25 == 0x2d) {
      if (param_2 == lVar21) goto LAB_00113230;
      goto LAB_001131f8;
    }
    uVar23 = (ulong)(param_7 - iVar16);
    if ((ulong)(param_2 - lVar21) <= uVar23) {
LAB_00113230:
      *piVar8 = 0x22;
LAB_00113238:
      lVar37 = 0;
      goto LAB_0011323c;
    }
    if (param_1 != (byte *)0x0) {
      if (uVar23 != 0) {
        if (uVar25 == 0x30 || uVar25 == 0x2b) {
          memset(param_1,0x30,uVar23);
        }
        else {
          memset(param_1,0x20,uVar23);
        }
        param_1 = param_1 + uVar23;
        lVar21 = lVar21 + uVar23;
      }
      goto LAB_001131f8;
    }
  }
  lVar21 = lVar37 + uVar17 + uVar23;
  param_1 = (byte *)0x0;
LAB_001131f8:
  bVar31 = pbVar29[1];
  param_3 = pbVar29 + 1;
  param_7 = -1;
  lVar37 = lVar21;
  goto joined_r0x001131ac;
}

