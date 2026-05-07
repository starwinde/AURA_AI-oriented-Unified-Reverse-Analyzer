
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_0010beb0(ulong param_1,char *param_2,uint param_3,ulong param_4,ulong param_5)

{
  uint uVar1;
  uint uVar2;
  char *__s;
  byte bVar3;
  undefined *puVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  lconv *plVar10;
  char *pcVar11;
  size_t sVar12;
  size_t sVar13;
  ulong uVar14;
  long lVar15;
  ulong uVar16;
  uint uVar17;
  undefined1 *__src;
  uint uVar18;
  ulong uVar19;
  ulong uVar20;
  byte *pbVar21;
  char *pcVar22;
  char *pcVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 local_f0;
  undefined8 local_d0;
  char *local_b0;
  undefined1 auStack_98 [48];
  long local_68;
  
  uVar7 = 1000;
  if ((param_3 & 0x20) != 0) {
    uVar7 = 0x400;
  }
  uVar2 = param_3 & 3;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  plVar10 = localeconv();
  pcVar11 = plVar10->decimal_point;
  sVar12 = strlen(pcVar11);
  if (0xf < sVar12 - 1) {
    pcVar11 = ".";
    sVar12 = 1;
  }
  pcVar22 = plVar10->thousands_sep;
  pbVar21 = (byte *)plVar10->grouping;
  sVar13 = strlen(pcVar22);
  local_b0 = param_2 + 0x287;
  __s = "";
  if (sVar13 < 0x11) {
    __s = pcVar22;
  }
  if (param_4 < param_5) {
    uVar20 = 0;
    if (param_4 != 0) {
      uVar20 = param_5 / param_4;
    }
    if (param_5 != uVar20 * param_4) goto LAB_0010c0b8;
    uVar19 = 0;
    if (uVar20 != 0) {
      uVar19 = param_1 / uVar20;
    }
    uVar14 = (param_1 - uVar19 * uVar20) * 10;
    uVar16 = 0;
    if (uVar20 != 0) {
      uVar16 = uVar14 / uVar20;
    }
    uVar14 = (uVar14 - uVar16 * uVar20) * 2;
    if (uVar14 < uVar20) {
      uVar17 = (uint)(uVar14 != 0);
    }
    else {
      uVar17 = (uVar20 < uVar14) + 2;
    }
joined_r0x0010c46c:
    uVar18 = (uint)uVar16;
    pcVar23 = local_b0;
    pcVar22 = local_b0;
    if ((param_3 >> 4 & 1) == 0) {
      iVar9 = -1;
    }
    else {
      uVar14 = (ulong)uVar7;
      iVar9 = 0;
      uVar20 = uVar19;
      if (uVar14 <= uVar19) {
        do {
          uVar19 = 0;
          if (uVar14 != 0) {
            uVar19 = uVar20 / uVar14;
          }
          uVar1 = (int)uVar16 + ((int)uVar20 - (int)uVar19 * uVar7) * 10;
          uVar18 = 0;
          if (uVar7 != 0) {
            uVar18 = uVar1 / uVar7;
          }
          uVar16 = (ulong)uVar18;
          uVar1 = ((int)uVar17 >> 1) + (uVar1 - uVar18 * uVar7) * 2;
          uVar17 = uVar17 + uVar1;
          if (uVar1 < uVar7) {
            uVar17 = (uint)(uVar17 != 0);
          }
          else {
            uVar17 = (uVar7 < uVar17) + 2;
          }
          iVar9 = iVar9 + 1;
          if (uVar19 < uVar14) {
            if (uVar19 < 10) {
              if (uVar2 == 1) {
                if (2 < (uVar18 & 1) + uVar17) goto LAB_0010c65c;
LAB_0010c6c4:
                cVar6 = (char)uVar18 + '0';
                if (uVar18 != 0) goto LAB_0010c670;
LAB_0010c6d0:
                if ((param_3 >> 3 & 1) == 0) {
                  cVar6 = '0';
                  goto LAB_0010c670;
                }
              }
              else {
                if ((param_3 & 3) != 0 || uVar17 == 0) goto LAB_0010c6c4;
LAB_0010c65c:
                cVar6 = (char)uVar18 + '1';
                if (uVar18 == 9) {
                  uVar16 = uVar19 + 1;
                  uVar17 = 0;
                  bVar5 = uVar19 != 9;
                  uVar19 = uVar16;
                  if (bVar5) goto LAB_0010c6d0;
                  goto LAB_0010c008;
                }
LAB_0010c670:
                param_2[0x286] = cVar6;
                memcpy(param_2 + (0x286 - sVar12),pcVar11,sVar12);
                uVar17 = 0;
                pcVar23 = param_2 + (0x286 - sVar12);
              }
              uVar18 = 0;
              pcVar22 = pcVar23;
              if (uVar2 != 1) goto LAB_0010bfd4;
              goto LAB_0010c008;
            }
            break;
          }
          uVar20 = uVar19;
        } while (iVar9 != 10);
      }
    }
    if (uVar2 == 1) {
      if ((uVar19 & 1) + (long)(int)uVar17 != 0) {
        uVar18 = uVar18 + 1;
      }
      if (5 < (int)uVar18) goto LAB_0010bfe4;
LAB_0010c008:
      do {
        pcVar23 = pcVar23 + -1;
        *pcVar23 = (char)uVar19 + (char)(uVar19 / 10) * -10 + '0';
        bVar5 = 9 < uVar19;
        uVar19 = uVar19 / 10;
      } while (bVar5);
    }
    else {
LAB_0010bfd4:
      pcVar22 = pcVar23;
      if (((param_3 & 3) != 0) || ((int)(uVar18 + uVar17) < 1)) goto LAB_0010c008;
LAB_0010bfe4:
      uVar19 = uVar19 + 1;
      pcVar23 = pcVar22;
      if (((param_3 & 0x10) == 0) || ((uVar19 != uVar7 || (iVar9 == 10)))) goto LAB_0010c008;
      iVar9 = iVar9 + 1;
      if ((param_3 >> 3 & 1) == 0) {
        pcVar22[-1] = '0';
        pcVar22 = pcVar22 + ~sVar12;
        memcpy(pcVar22,pcVar11,sVar12);
      }
      pcVar22[-1] = '1';
      pcVar23 = pcVar22 + -1;
    }
  }
  else {
    uVar16 = 0;
    if (param_5 != 0) {
      uVar16 = param_4 / param_5;
    }
    if (param_4 == uVar16 * param_5) {
      uVar19 = param_1 * uVar16;
      uVar20 = 0;
      if (uVar16 != 0) {
        uVar20 = uVar19 / uVar16;
      }
      if (uVar20 == param_1) {
        uVar17 = 0;
        uVar16 = 0;
        goto joined_r0x0010c46c;
      }
    }
LAB_0010c0b8:
    uVar24 = FUN_00118040(param_4);
    uVar25 = FUN_00118040(param_5);
    uVar24 = FUN_00116b70(uVar24,uVar25);
    uVar25 = FUN_00118040(param_1);
    local_d0 = FUN_00117730(uVar24,uVar25);
    if ((param_3 >> 4 & 1) == 0) {
      if ((uVar2 != 1) && (iVar9 = FUN_001175d0(local_d0,_DAT_0011cd10), iVar9 < 0)) {
        lVar15 = FUN_00117f30(local_d0);
        if ((param_3 & 3) == 0) {
          uVar24 = FUN_00118040();
          iVar9 = FUN_001174c0(uVar24,local_d0);
          if (iVar9 != 0) {
            lVar15 = lVar15 + 1;
          }
        }
        local_d0 = FUN_00118040(lVar15);
      }
      __sprintf_chk(local_d0,param_2,2,0xffffffffffffffff,"%.0Lf");
      sVar13 = strlen(param_2);
      iVar9 = -1;
      sVar12 = sVar13;
    }
    else {
      iVar9 = 0;
      uVar24 = FUN_00117ec0(uVar7);
      local_f0 = _DAT_0011cd20;
      do {
        iVar9 = iVar9 + 1;
        local_f0 = FUN_00117730(local_f0,uVar24);
        uVar25 = FUN_00117730(local_f0,uVar24);
        iVar8 = FUN_001175d0(uVar25,local_d0);
        if (0 < iVar8) break;
      } while (iVar9 != 10);
      uVar24 = FUN_00116b70(local_d0,local_f0);
      uVar16 = (ulong)((param_3 & 0x20) == 0) + 1 + sVar12 + 1;
      if ((uVar2 == 1) || (iVar8 = FUN_001175d0(uVar24,_DAT_0011cd10), -1 < iVar8)) {
        __sprintf_chk(uVar24,param_2,2,0xffffffffffffffff,"%.1Lf");
        sVar13 = strlen(param_2);
        if (sVar13 <= uVar16) goto LAB_0010c440;
        uVar24 = FUN_00117730(uVar24,_DAT_0011cd30);
      }
      else {
        lVar15 = FUN_00117f30(uVar24);
        if ((param_3 & 3) == 0) {
          uVar25 = FUN_00118040();
          iVar8 = FUN_001174c0(uVar25,uVar24);
          if (iVar8 != 0) {
            lVar15 = lVar15 + 1;
          }
        }
        FUN_00118040(lVar15);
        __sprintf_chk(param_2,2,0xffffffffffffffff,"%.1Lf");
        sVar13 = strlen(param_2);
        if (uVar16 < sVar13) {
          uVar24 = FUN_00117730(uVar24,_DAT_0011cd30);
        }
        else {
LAB_0010c440:
          if (((param_3 >> 3 & 1) == 0) || (param_2[sVar13 - 1] != '0')) {
            sVar12 = sVar13 - (sVar12 + 1);
            goto LAB_0010c2dc;
          }
          uVar24 = FUN_00117730(uVar24,_DAT_0011cd30);
          if (uVar2 == 1) goto LAB_0010c4ac;
        }
        iVar8 = FUN_001175d0(uVar24,_DAT_0011cd10);
        if (iVar8 < 0) {
          lVar15 = FUN_00117f30(uVar24);
          if ((param_3 & 3) == 0) {
            uVar25 = FUN_00118040();
            iVar8 = FUN_001174c0(uVar25,uVar24);
            if (iVar8 != 0) {
              lVar15 = lVar15 + 1;
            }
          }
          uVar24 = FUN_00118040(lVar15);
        }
      }
LAB_0010c4ac:
      FUN_00116b70(uVar24,_DAT_0011cd30);
      __sprintf_chk(param_2,2,0xffffffffffffffff,"%.0Lf");
      sVar13 = strlen(param_2);
      sVar12 = sVar13;
    }
LAB_0010c2dc:
    pcVar23 = local_b0 + -sVar13;
    pcVar22 = pcVar23 + sVar12;
    memmove(pcVar23,param_2,sVar13);
  }
  if ((param_3 >> 2 & 1) != 0) {
    sVar12 = strlen(__s);
    uVar16 = 0xffffffffffffffff;
    __memcpy_chk(auStack_98,pcVar23,(long)pcVar22 - (long)pcVar23,0x29);
    uVar19 = (long)pcVar22 - (long)pcVar23;
    while( true ) {
      bVar3 = *pbVar21;
      if (bVar3 == 0) {
        if (uVar19 < uVar16) {
          uVar16 = uVar19;
        }
        uVar20 = uVar19 - uVar16;
        __src = auStack_98 + uVar20;
      }
      else if (bVar3 == 0xff) {
        pbVar21 = pbVar21 + 1;
        uVar20 = 0;
        __src = auStack_98;
        uVar16 = uVar19;
      }
      else {
        pbVar21 = pbVar21 + 1;
        uVar16 = (ulong)bVar3;
        if (uVar19 < bVar3) {
          uVar16 = uVar19;
        }
        uVar20 = uVar19 - uVar16;
        __src = auStack_98 + uVar20;
      }
      pcVar23 = pcVar22 + -uVar16;
      memcpy(pcVar23,__src,uVar16);
      if (uVar20 == 0) break;
      pcVar22 = pcVar23 + -sVar12;
      memcpy(pcVar22,__s,sVar12);
      uVar19 = uVar20;
    }
  }
  pcVar11 = local_b0;
  if ((param_3 >> 7 & 1) == 0) goto LAB_0010c050;
  if (iVar9 == -1) {
    if (param_5 < 2) {
      iVar9 = 0;
      goto LAB_0010c044;
    }
    iVar9 = 1;
    uVar16 = 1;
    do {
      uVar16 = uVar16 * uVar7;
      if (param_5 <= uVar16) break;
      iVar9 = iVar9 + 1;
    } while (iVar9 != 10);
    if ((param_3 >> 6 & 1) != 0) {
      local_b0 = param_2 + 0x288;
      param_2[0x287] = ' ';
    }
LAB_0010c55c:
    pcVar11 = local_b0 + 1;
    if ((param_3 & 0x20) == 0 && iVar9 == 1) {
      *local_b0 = 'k';
      goto joined_r0x0010c5c8;
    }
    *local_b0 = (&DAT_001184b8)[iVar9];
    if ((param_3 & 0x100) == 0) goto LAB_0010c050;
    if ((param_3 & 0x20) != 0) {
      pcVar11 = local_b0 + 2;
      local_b0[1] = 'i';
    }
  }
  else {
LAB_0010c044:
    if ((param_3 & 0x100) == 0 && iVar9 == 0) goto LAB_0010c050;
    if ((param_3 >> 6 & 1) != 0) {
      local_b0 = param_2 + 0x288;
      param_2[0x287] = ' ';
    }
    pcVar11 = local_b0;
    if (iVar9 != 0) goto LAB_0010c55c;
joined_r0x0010c5c8:
    if ((param_3 & 0x100) == 0) goto LAB_0010c050;
  }
  *pcVar11 = 'B';
  pcVar11 = pcVar11 + 1;
LAB_0010c050:
  local_b0 = pcVar11;
  puVar4 = PTR___stack_chk_guard_0013ffd0;
  *local_b0 = '\0';
  lVar15 = local_68 - *(long *)puVar4;
  if (lVar15 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(puVar4,0,lVar15);
  }
  return pcVar23;
}

