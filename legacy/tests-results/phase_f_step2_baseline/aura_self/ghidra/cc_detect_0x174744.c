
void cc_detect(undefined8 *param_1,long param_2,ulong param_3,uint param_4)

{
  ulong uVar1;
  char cVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  bool bVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  size_t sVar11;
  char *pcVar12;
  char *pcVar13;
  char *pcVar14;
  char *pcVar15;
  undefined **ppuVar16;
  char *pcVar17;
  ulong uVar18;
  char *pcVar19;
  char *pcVar20;
  ulong uVar21;
  undefined8 *puVar22;
  char *pcVar23;
  char *local_d0;
  undefined8 local_98;
  ulong local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  local_98 = 0;
  local_90 = 0;
  local_88 = 0;
  if (param_2 == 0 || param_3 == 0) goto LAB_00174820;
  if (param_4 == 3) {
    local_98 = 6;
    goto LAB_00174820;
  }
  if (3 < param_4) {
    if (param_4 != 4) goto LAB_00174820;
    uVar18 = param_3;
    if (0x14 < param_3) {
      uVar18 = 0x14;
    }
    pcVar17 = (char *)(param_2 + uVar18 * 0xe0 + 0x60);
    pcVar19 = (char *)(param_2 + 0x60);
    local_98 = 7;
    local_80 = 0;
    pcVar13 = pcVar19;
    do {
      pcVar20 = pcVar13 + -0x40;
      iVar8 = strcmp(pcVar20,"ret");
      if ((((iVar8 == 0) || ((pcVar13[-0x40] == 'b' && (pcVar13[-0x3f] == '\0')))) ||
          ((*pcVar20 == 'b' && ((pcVar13[-0x3f] == 'l' && (pcVar13[-0x3e] == '\0')))))) ||
         ((iVar8 = strcmp(pcVar20,"cbz"), iVar8 == 0 || (iVar8 = strcmp(pcVar20,"cbnz"), iVar8 == 0)
          ))) break;
      iVar8 = strcmp(pcVar20,"str");
      if ((iVar8 == 0) || (iVar8 = strcmp(pcVar20,"stp"), iVar8 == 0)) {
        pcVar20 = strstr(pcVar13,"[sp");
        bVar5 = true;
        if ((pcVar20 == (char *)0x0) && (pcVar20 = strstr(pcVar13,"[fp"), pcVar20 == (char *)0x0)) {
          pcVar20 = strstr(pcVar13,"[x29");
          bVar5 = pcVar20 != (char *)0x0;
        }
        puVar22 = &local_80;
        ppuVar16 = &PTR_DAT_005e00d8;
        do {
          pcVar20 = ppuVar16[-1];
          if (pcVar20 == (char *)0x0) {
LAB_00174a88:
            pcVar23 = *ppuVar16;
            if (pcVar23 != (char *)0x0) {
              sVar11 = strlen(pcVar23);
              pcVar14 = pcVar13;
              do {
                pcVar12 = strstr(pcVar14,pcVar23);
                if (pcVar12 == (char *)0x0) goto LAB_00174a70;
                pcVar14 = pcVar12 + sVar11;
              } while (((pcVar13 < pcVar12) &&
                       ((byte)(pcVar12[-1] + 0x9fU) < 0x1a || (byte)(pcVar12[-1] - 0x30U) < 10)) ||
                      ((byte)(pcVar12[sVar11] + 0x9fU) < 0x1a ||
                       (byte)(pcVar12[sVar11] - 0x30U) < 10));
              iVar8 = strncmp(pcVar13,pcVar20,2);
              if (iVar8 != 0) goto LAB_00174a54;
              goto LAB_00174b10;
            }
          }
          else {
            sVar11 = strlen(pcVar20);
            pcVar23 = pcVar13;
            do {
              pcVar14 = strstr(pcVar23,pcVar20);
              if (pcVar14 == (char *)0x0) goto LAB_00174a88;
              pcVar23 = pcVar14 + sVar11;
            } while (((pcVar13 < pcVar14) &&
                     ((byte)(pcVar14[-1] + 0x9fU) < 0x1a || (byte)(pcVar14[-1] - 0x30U) < 10)) ||
                    ((byte)(pcVar14[sVar11] + 0x9fU) < 0x1a || (byte)(pcVar14[sVar11] - 0x30U) < 10)
                    );
            iVar8 = strncmp(pcVar13,pcVar20,2);
            if (iVar8 == 0) {
LAB_00174b10:
              if (!bVar5) goto LAB_00174a70;
            }
            else {
LAB_00174a54:
              iVar8 = strncmp(pcVar13,*ppuVar16,2);
              if (iVar8 == 0) goto LAB_00174b10;
            }
            *(undefined1 *)puVar22 = 1;
          }
LAB_00174a70:
          puVar22 = (undefined8 *)((long)puVar22 + 1);
          ppuVar16 = ppuVar16 + 2;
        } while (puVar22 != &local_78);
      }
      pcVar13 = pcVar13 + 0xe0;
    } while (pcVar17 != pcVar13);
    uVar7 = 4;
    if ((char)local_80 == '\0') {
      local_d0 = "w0";
      local_78 = 0;
      local_70 = 0;
LAB_00174d90:
      iVar8 = strcmp(pcVar19 + -0x40,"ret");
      if (iVar8 != 0) {
        iVar8 = is_aarch64_non_def_first_op(pcVar19 + -0x40);
        pcVar13 = (char *)&local_70;
        puVar22 = &local_78;
        ppuVar16 = &a64_regs_0;
        pcVar20 = local_d0;
LAB_00174f04:
        pcVar23 = *ppuVar16;
        if (pcVar23 != (char *)0x0) {
          sVar11 = strlen(pcVar23);
          pcVar14 = pcVar19;
          do {
            pcVar12 = strstr(pcVar14,pcVar23);
            if (pcVar12 == (char *)0x0) {
              if (ppuVar16[1] == (undefined *)0x0) goto joined_r0x00174fd4;
              bVar5 = false;
              goto LAB_00174e48;
            }
            pcVar14 = pcVar12 + sVar11;
          } while (((pcVar19 < pcVar12) &&
                   ((byte)(pcVar12[-1] + 0x9fU) < 0x1a || (byte)(pcVar12[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar12[sVar11] + 0x9fU) < 0x1a || (byte)(pcVar12[sVar11] - 0x30U) < 10));
          if (ppuVar16[1] != (undefined *)0x0) {
            bVar5 = true;
            goto LAB_00174e48;
          }
          pcVar20 = (char *)0x0;
LAB_00174eb4:
          iVar10 = strncmp(pcVar19,pcVar23,2);
          if (((iVar10 != 0) && (iVar10 = strncmp(pcVar19,pcVar20,2), iVar10 != 0)) || (iVar8 != 0))
          {
            if (*pcVar13 == '\0') {
              *(undefined1 *)puVar22 = 1;
            }
            goto joined_r0x00174fd4;
          }
          if ((*pcVar13 == '\0') && (pcVar14 = strchr(pcVar19,0x2c), pcVar14 != (char *)0x0)) {
            pcVar14 = pcVar14 + 1;
            sVar11 = strlen(pcVar23);
            pcVar12 = pcVar14;
            do {
              pcVar15 = strstr(pcVar12,pcVar23);
              if (pcVar15 == (char *)0x0) {
                if (pcVar20 == (char *)0x0) goto LAB_00174fbc;
                sVar11 = strlen(pcVar20);
                pcVar23 = pcVar14;
                goto LAB_0017506c;
              }
              pcVar12 = pcVar15 + sVar11;
            } while (((pcVar14 < pcVar15) &&
                     ((byte)(pcVar15[-1] + 0x9fU) < 0x1a || (byte)(pcVar15[-1] - 0x30U) < 10)) ||
                    ((byte)(pcVar15[sVar11] + 0x9fU) < 0x1a || (byte)(pcVar15[sVar11] - 0x30U) < 10)
                    );
            goto LAB_00174fb4;
          }
          goto LAB_00174fbc;
        }
        if (ppuVar16[1] != (undefined *)0x0) {
          bVar5 = false;
LAB_00174e48:
          sVar11 = strlen(pcVar20);
          pcVar14 = pcVar19;
          do {
            pcVar12 = strstr(pcVar14,pcVar20);
            if (pcVar12 == (char *)0x0) {
              if (!bVar5) goto joined_r0x00174fd4;
              break;
            }
            pcVar14 = pcVar12 + sVar11;
          } while (((pcVar19 < pcVar12) &&
                   ((byte)(pcVar12[-1] + 0x9fU) < 0x1a || (byte)(pcVar12[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar12[sVar11] + 0x9fU) < 0x1a || (byte)(pcVar12[sVar11] - 0x30U) < 10));
          goto LAB_00174eb4;
        }
        goto joined_r0x00174fd4;
      }
      goto LAB_00174fe8;
    }
    if (local_80._1_1_ != '\0') {
      if (local_80._2_1_ != '\0') {
        if (local_80._3_1_ != '\0') {
          if (local_80._4_1_ != '\0') {
            if (local_80._5_1_ != '\0') {
              if (local_80._6_1_ != '\0') {
                cVar2 = local_80._7_1_;
                goto joined_r0x00175024;
              }
              goto LAB_00175240;
            }
            goto LAB_00175234;
          }
          goto LAB_0017502c;
        }
        goto LAB_0017516c;
      }
      goto LAB_00175228;
    }
    goto LAB_0017521c;
  }
  if (param_4 != 1) {
    if (param_4 == 2) {
      uVar6 = scan_arg_reg_usage_constprop_0();
      uVar7 = detect_ret_cleanup(param_2,param_3,(long)&local_88 + 4);
      local_88 = CONCAT44(local_88._4_4_,uVar7);
      if ((uVar6 & 1) == 0) {
        if (((uVar6 & 0xffff) >> 3 & 1) == 0) {
          uVar7 = 0;
          local_98._0_4_ = 4;
        }
        else {
          uVar7 = 2;
          if ((uVar6 & 4) == 0) {
            uVar7 = 1;
          }
          if ((uVar6 & 0x10) != 0) {
            uVar7 = 3;
          }
          if ((uVar6 & 0x20) != 0) {
            uVar7 = 4;
          }
          local_98._0_4_ = 5;
        }
      }
      else {
        uVar7 = 2;
        if ((uVar6 & 2) == 0) {
          uVar7 = 1;
        }
        if ((uVar6 & 4) != 0) {
          uVar7 = 3;
        }
        if ((uVar6 & 8) != 0) {
          uVar7 = 4;
        }
        if ((uVar6 & 0x10) != 0) {
          uVar7 = 5;
        }
        if ((uVar6 & 0x20) != 0) {
          uVar7 = 6;
        }
        local_98._0_4_ = 4;
      }
      local_98 = CONCAT44(uVar7,(undefined4)local_98);
      local_90 = CONCAT44(uVar6,(uVar6 & 0xffff) >> 6) & 0xffff00000001;
    }
    goto LAB_00174820;
  }
  uVar6 = scan_arg_reg_usage_constprop_0();
  iVar8 = detect_ret_cleanup(param_2,param_3,(long)&local_88 + 4);
  uVar3 = local_88;
  local_88 = CONCAT44(local_88._4_4_,iVar8);
  uVar4 = local_88;
  local_88._4_2_ = SUB82(uVar3,4);
  if ((uVar6 & 0x88) == 0 || (uVar6 & 0x104) == 0) {
    if ((iVar8 == 0) || (local_88._4_2_ == 0)) goto LAB_00174b58;
    uVar9 = (uint)(local_88._4_2_ >> 2);
    local_98._0_4_ = 2;
  }
  else if (iVar8 == 0) {
LAB_00174b58:
    uVar9 = 0;
    local_98._0_4_ = 1;
  }
  else {
    local_98._0_4_ = 3;
    uVar9 = (local_88._4_2_ >> 2) + 2;
  }
  local_98 = CONCAT44(uVar9,(undefined4)local_98);
  local_90 = CONCAT44(uVar6,(uVar6 & 0xffff) >> 6) & 0xffff00000001;
  local_88 = uVar4;
  goto LAB_00174820;
  while (((pcVar23 = pcVar12 + sVar11, pcVar14 < pcVar12 &&
          ((byte)(pcVar12[-1] + 0x9fU) < 0x1a || (byte)(pcVar12[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar12[sVar11] + 0x9fU) < 0x1a || (byte)(pcVar12[sVar11] - 0x30U) < 10))) {
LAB_0017506c:
    pcVar12 = strstr(pcVar23,pcVar20);
    if (pcVar12 == (char *)0x0) goto LAB_00174fbc;
  }
LAB_00174fb4:
  *(undefined1 *)puVar22 = 1;
LAB_00174fbc:
  *pcVar13 = '\x01';
joined_r0x00174fd4:
  if (ppuVar16 == &PTR_DAT_005e0140) goto LAB_00174fd8;
  puVar22 = (undefined8 *)((long)puVar22 + 1);
  pcVar13 = pcVar13 + 1;
  pcVar20 = ppuVar16[3];
  ppuVar16 = ppuVar16 + 2;
  goto LAB_00174f04;
LAB_00174fd8:
  pcVar19 = pcVar19 + 0xe0;
  if (pcVar17 == pcVar19) goto LAB_00174fe8;
  goto LAB_00174d90;
LAB_00174fe8:
  if ((char)local_78 != '\0') {
    if (local_78._1_1_ == '\0') {
LAB_0017521c:
      local_98 = 0x100000007;
    }
    else if (local_78._2_1_ == '\0') {
LAB_00175228:
      local_98 = 0x200000007;
    }
    else if (local_78._3_1_ == '\0') {
LAB_0017516c:
      local_98 = 0x300000007;
    }
    else if (local_78._4_1_ == '\0') {
LAB_0017502c:
      local_98 = CONCAT44(uVar7,7);
    }
    else if (local_78._5_1_ == '\0') {
LAB_00175234:
      local_98 = 0x500000007;
    }
    else if (local_78._6_1_ == '\0') {
LAB_00175240:
      local_98 = 0x600000007;
    }
    else {
      cVar2 = local_78._7_1_;
joined_r0x00175024:
      if (cVar2 == '\0') {
        uVar7 = 7;
        goto LAB_0017502c;
      }
      local_98 = 0x800000007;
    }
  }
  uVar18 = 0;
  pcVar17 = (char *)(param_2 + 0x20);
  if (0x100 < param_3) {
    param_3 = 0x100;
  }
  do {
    if ((*pcVar17 != '\0') && (iVar8 = strcmp(pcVar17,"ret"), iVar8 == 0)) {
      if (uVar18 != 0 && uVar18 < param_3) {
        uVar1 = uVar18;
        if (uVar18 < 0x10) {
          uVar1 = 0x10;
        }
        if (uVar1 - 0x10 < uVar18) {
          pcVar17 = (char *)(param_2 + uVar18 * 0xe0 + -0x80);
          uVar21 = uVar18;
          goto LAB_00174bb8;
        }
      }
      break;
    }
    uVar18 = uVar18 + 1;
    pcVar17 = pcVar17 + 0xe0;
  } while (param_3 != uVar18);
  goto LAB_00174820;
  while( true ) {
    uVar21 = uVar21 - 1;
    pcVar17 = pcVar17 + -0xe0;
    if (uVar1 - 0x10 == uVar21) break;
LAB_00174bb8:
    if ((((*pcVar17 == 'x') && (pcVar17[1] == '0')) || ((*pcVar17 == 'w' && (pcVar17[1] == '0'))))
       && ((0x19 < (byte)(pcVar17[2] + 0x9fU) && 9 < (byte)(pcVar17[2] - 0x30U) &&
           (iVar8 = is_aarch64_non_def_first_op(pcVar17 + -0x40), iVar8 == 0)))) {
      if (uVar18 <= uVar21) goto LAB_00175200;
      pcVar17 = (char *)(param_2 + uVar21 * 0xe0 + 0x62);
      pcVar19 = pcVar17;
      goto LAB_00174c2c;
    }
  }
  goto LAB_00174820;
  while( true ) {
    while (pcVar13 = strstr(pcVar17,"w0"), pcVar13 != (char *)0x0) {
      pcVar17 = pcVar13 + 2;
      if (((pcVar13 <= pcVar19) ||
          (0x19 < (byte)(pcVar13[-1] + 0x9fU) && 9 < (byte)(pcVar13[-1] - 0x30U))) &&
         (0x19 < (byte)(pcVar13[2] + 0x9fU) && 9 < (byte)(pcVar13[2] - 0x30U))) goto LAB_00174820;
    }
    pcVar17 = pcVar19 + 0xe0;
    pcVar19 = pcVar17;
    if (pcVar17 == (char *)(param_2 + 0x62 + uVar18 * 0xe0)) break;
LAB_00174c2c:
    pcVar13 = strstr(pcVar17,"x0");
    pcVar17 = pcVar19;
    if (pcVar13 != (char *)0x0) {
      pcVar17 = pcVar13 + 2;
      if (((pcVar13 <= pcVar19) ||
          (0x19 < (byte)(pcVar13[-1] + 0x9fU) && 9 < (byte)(pcVar13[-1] - 0x30U))) &&
         (0x19 < (byte)(pcVar13[2] + 0x9fU) && 9 < (byte)(pcVar13[2] - 0x30U))) goto LAB_00174820;
      goto LAB_00174c2c;
    }
  }
LAB_00175200:
  local_90 = 1;
LAB_00174820:
  *param_1 = local_98;
  param_1[1] = local_90;
  param_1[2] = local_88;
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

