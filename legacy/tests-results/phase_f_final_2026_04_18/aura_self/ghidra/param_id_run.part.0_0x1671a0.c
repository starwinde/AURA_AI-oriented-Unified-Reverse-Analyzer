
void param_id_run_part_0(long param_1,long param_2,ulong param_3,long param_4,undefined8 *param_5)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  bool bVar8;
  byte bVar9;
  byte bVar10;
  bool bVar11;
  bool bVar12;
  undefined1 uVar13;
  bool bVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  long lVar19;
  undefined8 *puVar20;
  char *pcVar21;
  undefined *puVar22;
  void *pvVar23;
  byte *pbVar24;
  size_t sVar25;
  byte *pbVar26;
  char *pcVar27;
  char *pcVar28;
  char *pcVar29;
  uint uVar30;
  undefined8 *puVar31;
  ulong uVar32;
  undefined8 uVar33;
  undefined **ppuVar34;
  undefined **ppuVar35;
  undefined4 uVar36;
  uint uVar37;
  byte *__s;
  undefined4 uVar38;
  ulong uVar39;
  undefined8 *puVar40;
  ulong uVar41;
  char *pcVar42;
  ulong uVar43;
  long lVar44;
  char *pcVar45;
  char *pcVar46;
  int *piVar47;
  char *pcVar48;
  bool bVar49;
  ulong uVar50;
  uint uVar51;
  char *local_218;
  char *local_1e8;
  long local_138;
  uint local_130;
  uint local_12c;
  int local_128;
  char acStack_118 [16];
  char acStack_108 [111];
  char cStack_99;
  undefined8 local_98;
  undefined8 local_90;
  ulong local_88;
  undefined8 uStack_80;
  char cStack_79;
  undefined8 local_78;
  undefined8 local_70;
  long local_68;
  
  iVar3 = *(int *)(param_1 + 0xc);
  uVar1 = iVar3 - 2U & 0xfffffffd;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  cc_detect(&local_130,param_2,param_3,iVar3,0);
  lVar19 = stack_analyze(param_2,param_3,param_4,iVar3,&local_130,0);
  local_138 = lVar19;
  puVar20 = calloc(1,0x98);
  if (puVar20 != (undefined8 *)0x0) {
    uVar30 = *(uint *)(puVar20 + 1);
    uVar32 = (ulong)uVar30;
    if (local_12c != 0) {
      if (local_130 == 5) {
        uVar36 = 8;
        bVar14 = true;
        uVar51 = 4;
        ppuVar35 = (undefined **)0x0;
        ppuVar34 = (undefined **)s_ms_x64_reg_names;
      }
      else if (local_130 < 6) {
        if (local_130 == 3) {
          uVar36 = 4;
          bVar14 = false;
          uVar51 = 2;
          ppuVar35 = (undefined **)0x0;
          ppuVar34 = (undefined **)s_ms_x64_reg_names;
        }
        else {
          if (local_130 != 4) goto LAB_001672b4;
          ppuVar35 = &s_sysv_reg_names_32;
          uVar36 = 8;
          bVar14 = true;
          uVar51 = 6;
          ppuVar34 = (undefined **)s_sysv_reg_names;
        }
      }
      else if (local_130 == 6) {
        uVar36 = 4;
        uVar51 = 4;
        bVar14 = false;
        ppuVar35 = (undefined **)0x0;
        ppuVar34 = (undefined **)s_arm_reg_names;
      }
      else {
        if (local_130 != 7) goto LAB_001672b4;
        ppuVar35 = &s_aarch64_reg_names_32;
        uVar36 = 8;
        ppuVar34 = &s_aarch64_reg_names;
        uVar51 = 8;
        bVar14 = true;
      }
      uVar15 = local_12c;
      if (uVar51 < local_12c) {
        uVar15 = uVar51;
      }
      uVar51 = *(uint *)((long)puVar20 + 0xc);
      uVar39 = 0;
      uVar38 = 0;
      uVar32 = (ulong)uVar30;
      if (uVar30 < uVar51) goto LAB_00168a5c;
LAB_00167b78:
      uVar37 = 8;
      if ((uVar51 != 0) && (uVar37 = uVar51 << 1, 0x20 < uVar37)) {
        uVar37 = 0x20;
      }
      lVar19 = local_138;
      if (uVar30 < uVar37) {
        pvVar23 = realloc((void *)*puVar20,(ulong)uVar37 * 0xd8);
        if (pvVar23 != (void *)0x0) {
          uVar32 = (ulong)*(uint *)(puVar20 + 1);
          *puVar20 = pvVar23;
          *(uint *)((long)puVar20 + 0xc) = uVar37;
LAB_00167bb8:
          pcVar48 = (char *)0x0;
          puVar31 = (undefined8 *)((long)pvVar23 + uVar32 * 0xd8);
          puVar31[0x1a] = 0;
          puVar31[1] = 0;
          *puVar31 = 0;
          puVar31[3] = 0;
          puVar31[2] = 0;
          puVar31[5] = 0;
          puVar31[4] = 0;
          puVar31[7] = 0;
          puVar31[6] = 0;
          puVar31[9] = 0;
          puVar31[8] = 0;
          puVar31[0xb] = 0;
          puVar31[10] = 0;
          puVar31[0xd] = 0;
          puVar31[0xc] = 0;
          puVar31[0xf] = 0;
          puVar31[0xe] = 0;
          puVar31[0x11] = 0;
          puVar31[0x10] = 0;
          puVar31[0x13] = 0;
          puVar31[0x12] = 0;
          puVar31[0x15] = 0;
          puVar31[0x14] = 0;
          puVar31[0x17] = 0;
          puVar31[0x16] = 0;
          puVar31[0x19] = 0;
          puVar31[0x18] = 0;
          pcVar45 = ppuVar34[uVar39];
          *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
          *(undefined4 *)((long)pvVar23 + uVar32 * 0xd8) = uVar38;
          *(undefined4 *)(puVar31 + 0x1a) = uVar36;
          *(undefined4 *)((long)puVar31 + 0xc4) = 1;
          puVar31[0x19] = 0;
          if (ppuVar35 != (undefined **)0x0) {
            pcVar48 = ppuVar35[uVar39];
          }
          uVar32 = param_3;
          if (0x80 < param_3) {
            uVar32 = 0x80;
          }
          if (param_3 != 0) {
            uVar50 = 0;
            pcVar27 = (char *)(param_2 + 0x20);
            do {
              if ((*pcVar27 != '\0') && (iVar16 = strcmp(pcVar27,"ret"), iVar16 == 0)) {
                uVar32 = uVar50 + 1;
                snprintf(acStack_118,0x10,"%s",pcVar45);
                goto LAB_00167c90;
              }
              uVar50 = uVar50 + 1;
              pcVar27 = pcVar27 + 0xe0;
            } while (uVar50 < uVar32);
            snprintf(acStack_118,0x10,"%s",pcVar45);
LAB_00167c90:
            __s = (byte *)(param_2 + 0x60);
            bVar49 = false;
            uVar50 = 0;
            bVar9 = 0;
            iVar16 = 1;
            uVar30 = 0;
            bVar12 = false;
            bVar10 = 0;
            bVar8 = false;
LAB_00167cd8:
            local_88 = 0;
            uStack_80 = 0;
            local_78 = 0;
            local_70 = 0;
            pbVar24 = (byte *)strchr((char *)__s,0x2c);
            if (pbVar24 != (byte *)0x0) {
              sVar25 = (long)pbVar24 - (long)__s;
              if (0xf < sVar25) {
                sVar25 = 0xf;
              }
              memcpy(&local_88,__s,sVar25);
              *(char *)((long)&local_88 + sVar25) = '\0';
              if (((((__s != pbVar24) &&
                    (lVar19 = sVar25 - 1, cVar7 = *(char *)((long)&local_88 + lVar19),
                    cVar7 == ' ' || cVar7 == '\t')) &&
                   (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)) &&
                  (((lVar19 = sVar25 - 2, cVar7 = *(char *)((long)&local_88 + lVar19),
                    cVar7 == ' ' || cVar7 == '\t' &&
                    (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)) &&
                   ((lVar19 = sVar25 - 3, cVar7 = *(char *)((long)&local_88 + lVar19),
                    cVar7 == ' ' || cVar7 == '\t' &&
                    ((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                     (lVar19 = sVar25 - 4, cVar7 = *(char *)((long)&local_88 + lVar19),
                     cVar7 == ' ' || cVar7 == '\t')))))))) &&
                 (((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                   ((((((lVar19 = sVar25 - 5, cVar7 = *(char *)((long)&local_88 + lVar19),
                        cVar7 == ' ' || cVar7 == '\t' &&
                        (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)) &&
                       (lVar19 = sVar25 - 6, cVar7 = *(char *)((long)&local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t')) &&
                      ((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                       (lVar19 = sVar25 - 7, cVar7 = *(char *)((long)&local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t')))) &&
                     ((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                      ((lVar19 = sVar25 - 8, cVar7 = *(char *)((long)&local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t' &&
                       (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)))))) &&
                    (lVar19 = sVar25 - 9, cVar7 = *(char *)((long)&local_88 + lVar19),
                    cVar7 == ' ' || cVar7 == '\t')))) &&
                  ((((((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                       (lVar19 = sVar25 - 10, cVar7 = *(char *)((long)&local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t')) &&
                      (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)) &&
                     ((lVar19 = sVar25 - 0xb, cVar7 = *(char *)((long)&local_88 + lVar19),
                      cVar7 == ' ' || cVar7 == '\t' &&
                      (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)))) &&
                    (lVar19 = sVar25 - 0xc, cVar7 = *(char *)((long)&local_88 + lVar19),
                    cVar7 == ' ' || cVar7 == '\t')) &&
                   (((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                     (lVar19 = sVar25 - 0xd, cVar7 = *(char *)((long)&local_88 + lVar19),
                     cVar7 == ' ' || cVar7 == '\t')) &&
                    ((*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0 &&
                     (((lVar19 = sVar25 - 0xe, cVar7 = *(char *)((long)&local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t' &&
                       (*(char *)((long)&local_88 + lVar19) = '\0', lVar19 != 0)) &&
                      ((char)local_88 == ' ' || (char)local_88 == '\t')))))))))))) {
                local_88 = local_88 & 0xffffffffffffff00;
              }
              uVar33 = local_70;
              uVar41 = local_78;
              bVar6 = pbVar24[1];
              pbVar24 = pbVar24 + 1;
              while (bVar6 == 0x20) {
                pbVar24 = pbVar24 + 1;
                bVar6 = *pbVar24;
              }
              if (bVar6 == 0x2c || bVar6 == 0) {
                iVar18 = 0;
              }
              else {
                bVar4 = pbVar24[1];
                local_78 = CONCAT71(local_78._1_7_,bVar6);
                if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                  iVar18 = 1;
                }
                else {
                  bVar5 = pbVar24[2];
                  local_78._2_6_ = SUB86(uVar41,2);
                  local_78._0_2_ = CONCAT11(bVar4,bVar6);
                  if (bVar5 == 0x2c || (bVar5 & 0xdf) == 0) {
                    iVar18 = 2;
                  }
                  else {
                    bVar6 = pbVar24[3];
                    local_78._3_5_ = SUB85(uVar41,3);
                    local_78._0_3_ = CONCAT12(bVar5,(undefined2)local_78);
                    if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                      iVar18 = 3;
                    }
                    else {
                      bVar4 = pbVar24[4];
                      local_78._4_4_ = SUB84(uVar41,4);
                      local_78._0_4_ = CONCAT13(bVar6,(undefined3)local_78);
                      if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                        iVar18 = 4;
                      }
                      else {
                        bVar6 = pbVar24[5];
                        local_78._5_3_ = SUB83(uVar41,5);
                        local_78._0_5_ = CONCAT14(bVar4,(undefined4)local_78);
                        if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                          iVar18 = 5;
                        }
                        else {
                          bVar4 = pbVar24[6];
                          local_78._6_2_ = SUB82(uVar41,6);
                          local_78._0_6_ = CONCAT15(bVar6,(undefined5)local_78);
                          if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                            iVar18 = 6;
                          }
                          else {
                            bVar6 = pbVar24[7];
                            local_78._7_1_ = SUB81(uVar41,7);
                            local_78._0_7_ = CONCAT16(bVar4,(undefined6)local_78);
                            if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                              iVar18 = 7;
                            }
                            else {
                              bVar4 = pbVar24[8];
                              local_78 = CONCAT17(bVar6,(undefined7)local_78);
                              if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                iVar18 = 8;
                              }
                              else {
                                bVar6 = pbVar24[9];
                                local_70 = CONCAT71(local_70._1_7_,bVar4);
                                if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                  iVar18 = 9;
                                }
                                else {
                                  bVar5 = pbVar24[10];
                                  local_70._2_6_ = SUB86(uVar33,2);
                                  local_70._0_2_ = CONCAT11(bVar6,bVar4);
                                  if (bVar5 == 0x2c || (bVar5 & 0xdf) == 0) {
                                    iVar18 = 10;
                                  }
                                  else {
                                    bVar6 = pbVar24[0xb];
                                    local_70._3_5_ = SUB85(uVar33,3);
                                    local_70._0_3_ = CONCAT12(bVar5,(undefined2)local_70);
                                    if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                      iVar18 = 0xb;
                                    }
                                    else {
                                      bVar4 = pbVar24[0xc];
                                      local_70._4_4_ = SUB84(uVar33,4);
                                      local_70._0_4_ = CONCAT13(bVar6,(undefined3)local_70);
                                      if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                        iVar18 = 0xc;
                                      }
                                      else {
                                        bVar6 = pbVar24[0xd];
                                        local_70._5_3_ = SUB83(uVar33,5);
                                        local_70._0_5_ = CONCAT14(bVar4,(undefined4)local_70);
                                        if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                          iVar18 = 0xd;
                                        }
                                        else {
                                          bVar4 = pbVar24[0xe];
                                          local_70._6_2_ = SUB82(uVar33,6);
                                          local_70._0_6_ = CONCAT15(bVar6,(undefined5)local_70);
                                          if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                            iVar18 = 0xe;
                                          }
                                          else {
                                            local_70._7_1_ = SUB81(uVar33,7);
                                            local_70._0_7_ = CONCAT16(bVar4,(undefined6)local_70);
                                            iVar18 = 0xf;
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              *(char *)((long)&local_78 + (long)iVar18) = '\0';
              if ((char)local_88 != '\0') {
                pbVar24 = __s + -0x40;
                iVar18 = strcmp((char *)pbVar24,"cmp");
                if (((((iVar18 != 0) && (iVar18 = strcmp((char *)pbVar24,"cmn"), iVar18 != 0)) &&
                     ((((iVar18 = strcmp((char *)pbVar24,"tst"), iVar18 != 0 &&
                        ((iVar18 = strcmp((char *)pbVar24,"str"), iVar18 != 0 &&
                         (iVar18 = strcmp((char *)pbVar24,"strb"), iVar18 != 0)))) &&
                       (iVar18 = strcmp((char *)pbVar24,"strh"), iVar18 != 0)) &&
                      (((iVar18 = strcmp((char *)pbVar24,"stp"), iVar18 != 0 &&
                        (iVar18 = strcmp((char *)pbVar24,"cbz"), iVar18 != 0)) &&
                       (iVar18 = strcmp((char *)pbVar24,"cbnz"), iVar18 != 0)))))) &&
                    ((((iVar18 = strcmp((char *)pbVar24,"tbz"), iVar18 != 0 &&
                       (iVar18 = strcmp((char *)pbVar24,"tbnz"), iVar18 != 0)) &&
                      ((*pbVar24 != 0x62 || (__s[-0x3f] != 0)))) &&
                     (((*pbVar24 != 0x62 || (__s[-0x3f] != 0x6c)) || (__s[-0x3e] != 0)))))) &&
                   (((iVar18 = strcmp((char *)pbVar24,"br"), iVar18 != 0 &&
                     (iVar18 = strcmp((char *)pbVar24,"blr"), iVar18 != 0)) &&
                    (iVar18 = strcmp((char *)pbVar24,"ret"), iVar18 != 0)))) {
                  iVar18 = strcmp((char *)pbVar24,"mov");
                  uVar51 = (uint)(-0x3ff000800000002 >> (local_78 & 0x3f)) & 1;
                  if (0x39 < (byte)local_78) {
                    uVar51 = 1;
                  }
                  if (iVar18 == 0 && uVar51 != 0) {
                    pcVar27 = acStack_118;
                    for (iVar18 = 0; iVar18 < iVar16; iVar18 = iVar18 + 1) {
                      iVar17 = strcmp(pcVar27,(char *)&local_78);
                      if (iVar17 == 0) {
                        iVar18 = 0;
                        local_218 = acStack_118;
                        goto LAB_001695c0;
                      }
                      pcVar27 = pcVar27 + 0x10;
                    }
                  }
                  uVar41 = 1;
                  pcVar27 = acStack_108;
LAB_001687e4:
                  iVar18 = (int)uVar41;
                  if (iVar18 < iVar16) {
                    iVar17 = strcmp(pcVar27,(char *)&local_88);
                    if (iVar17 != 0) goto code_r0x001687e0;
                    uVar43 = -(uVar41 >> 0x1f) & 0xfffffff000000000 | uVar41 << 4;
                    iVar16 = iVar16 + -1;
                    pcVar27 = acStack_118 + (long)iVar18 * 0x10;
                    for (; (int)uVar41 < iVar16; uVar41 = (ulong)((int)uVar41 + 1)) {
                      uVar2 = uVar43;
                      if (uVar43 < 0x80) {
                        uVar2 = 0x80;
                      }
                      __memcpy_chk(pcVar27,pcVar27 + 0x10,0x10,uVar2 - uVar43);
                      uVar43 = uVar43 + 0x10;
                      pcVar27 = pcVar27 + 0x10;
                    }
                  }
                }
              }
            }
            goto joined_r0x00167cf8;
          }
          snprintf(acStack_118,0x10,"%s",pcVar45);
          bVar8 = false;
          goto LAB_00168df4;
        }
LAB_00168ee8:
        uVar32 = (ulong)*(uint *)(puVar20 + 1);
        lVar19 = local_138;
      }
    }
LAB_001672b4:
    if ((lVar19 != 0) && (uVar30 = *(uint *)(lVar19 + 0x20), uVar30 != 0)) {
      if (uVar1 == 0) {
        uVar51 = 0;
        lVar44 = 0;
        do {
          while (puVar31 = (undefined8 *)(*(long *)(lVar19 + 0x18) + lVar44),
                *(int *)(puVar31 + 4) == 2) {
            uVar30 = *(uint *)(puVar20 + 1);
            uVar15 = *(uint *)((long)puVar20 + 0xc);
            if (uVar30 < uVar15) {
              pvVar23 = (void *)*puVar20;
            }
            else {
              uVar37 = 8;
              if ((uVar15 != 0) && (uVar37 = uVar15 << 1, 0x20 < uVar37)) {
                uVar37 = 0x20;
              }
              if ((uVar37 <= uVar30) ||
                 (pvVar23 = realloc((void *)*puVar20,(ulong)uVar37 * 0xd8), pvVar23 == (void *)0x0))
              goto joined_r0x00167464;
              uVar30 = *(uint *)(puVar20 + 1);
              *puVar20 = pvVar23;
              *(uint *)((long)puVar20 + 0xc) = uVar37;
            }
            uVar15 = (int)uVar32 + 1;
            puVar40 = (undefined8 *)((long)pvVar23 + (ulong)uVar30 * 0xd8);
            puVar40[0x1a] = 0;
            puVar40[1] = 0;
            *puVar40 = 0;
            puVar40[3] = 0;
            puVar40[2] = 0;
            puVar40[5] = 0;
            puVar40[4] = 0;
            puVar40[7] = 0;
            puVar40[6] = 0;
            puVar40[9] = 0;
            puVar40[8] = 0;
            puVar40[0xb] = 0;
            puVar40[10] = 0;
            puVar40[0xd] = 0;
            puVar40[0xc] = 0;
            puVar40[0xf] = 0;
            puVar40[0xe] = 0;
            puVar40[0x11] = 0;
            puVar40[0x10] = 0;
            puVar40[0x13] = 0;
            puVar40[0x12] = 0;
            puVar40[0x15] = 0;
            puVar40[0x14] = 0;
            puVar40[0x17] = 0;
            puVar40[0x16] = 0;
            puVar40[0x19] = 0;
            puVar40[0x18] = 0;
            pcVar45 = (char *)puVar31[3];
            *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
            uVar33 = *puVar31;
            *(int *)((long)pvVar23 + (ulong)uVar30 * 0xd8) = (int)uVar32;
            uVar30 = *(uint *)(puVar31 + 1);
            *(undefined4 *)((long)puVar40 + 0xc4) = 2;
            puVar40[0x19] = uVar33;
            *(uint *)(puVar40 + 0x1a) = uVar30;
            if ((pcVar45 == (char *)0x0) || (*pcVar45 == '\0')) {
              if (uVar30 == 4) {
                pcVar45 = "uint32_t";
              }
              else if (uVar30 < 5) {
                if (uVar30 == 1) {
                  pcVar45 = "uint8_t";
                }
                else {
                  pcVar45 = "int";
                  if (uVar30 == 2) {
                    pcVar45 = "uint16_t";
                  }
                }
              }
              else {
                pcVar45 = "int";
                if (uVar30 == 8) {
                  pcVar45 = "uint64_t";
                }
              }
              snprintf((char *)((long)puVar40 + 4),0x80,"%s",pcVar45);
            }
            else {
              snprintf((char *)((long)puVar40 + 4),0x80,"%s");
            }
            if (((char *)puVar31[2] != (char *)0x0) && (*(char *)puVar31[2] != '\0')) {
              snprintf((char *)((long)puVar40 + 0x84),0x40,"%s");
              uVar30 = *(uint *)(lVar19 + 0x20);
              uVar32 = (ulong)uVar15;
              break;
            }
            uVar51 = uVar51 + 1;
            uVar32 = (ulong)uVar15;
            lVar44 = lVar44 + 0x30;
            __snprintf_chk((long)puVar40 + 0x84,0x40,2,0x40,"arg%u",*(undefined4 *)puVar40);
            uVar30 = *(uint *)(lVar19 + 0x20);
            if (uVar30 <= uVar51) goto joined_r0x00167464;
          }
          uVar51 = uVar51 + 1;
          lVar44 = lVar44 + 0x30;
        } while (uVar51 < uVar30);
      }
      else {
        uVar51 = 0;
        lVar44 = 0;
        do {
          while (puVar31 = (undefined8 *)(*(long *)(lVar19 + 0x18) + lVar44),
                *(int *)(puVar31 + 4) == 2) {
            uVar15 = *(uint *)(puVar20 + 1);
            uVar30 = *(uint *)((long)puVar20 + 0xc);
            if (uVar15 < uVar30) {
              pvVar23 = (void *)*puVar20;
            }
            else {
              if (uVar30 == 0) {
                uVar30 = 8;
              }
              else {
                uVar30 = uVar30 << 1;
                if (0x20 < uVar30) {
                  uVar30 = 0x20;
                }
              }
              if ((uVar30 <= uVar15) ||
                 (pvVar23 = realloc((void *)*puVar20,(ulong)uVar30 * 0xd8), pvVar23 == (void *)0x0))
              goto joined_r0x00167464;
              uVar15 = *(uint *)(puVar20 + 1);
              *puVar20 = pvVar23;
              *(uint *)((long)puVar20 + 0xc) = uVar30;
            }
            uVar30 = (int)uVar32 + 1;
            puVar40 = (undefined8 *)((long)pvVar23 + (ulong)uVar15 * 0xd8);
            puVar40[0x1a] = 0;
            puVar40[1] = 0;
            *puVar40 = 0;
            puVar40[3] = 0;
            puVar40[2] = 0;
            puVar40[5] = 0;
            puVar40[4] = 0;
            puVar40[7] = 0;
            puVar40[6] = 0;
            puVar40[9] = 0;
            puVar40[8] = 0;
            puVar40[0xb] = 0;
            puVar40[10] = 0;
            puVar40[0xd] = 0;
            puVar40[0xc] = 0;
            puVar40[0xf] = 0;
            puVar40[0xe] = 0;
            puVar40[0x11] = 0;
            puVar40[0x10] = 0;
            puVar40[0x13] = 0;
            puVar40[0x12] = 0;
            puVar40[0x15] = 0;
            puVar40[0x14] = 0;
            puVar40[0x17] = 0;
            puVar40[0x16] = 0;
            puVar40[0x19] = 0;
            puVar40[0x18] = 0;
            pcVar45 = (char *)puVar31[3];
            *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
            uVar33 = *puVar31;
            *(int *)((long)pvVar23 + (ulong)uVar15 * 0xd8) = (int)uVar32;
            iVar16 = *(int *)(puVar31 + 1);
            *(undefined4 *)((long)puVar40 + 0xc4) = 2;
            puVar40[0x19] = uVar33;
            *(int *)(puVar40 + 0x1a) = iVar16;
            if ((pcVar45 == (char *)0x0) || (*pcVar45 == '\0')) {
              if (iVar16 == 2) {
                pcVar45 = "uint16_t";
              }
              else if (iVar16 == 8) {
                pcVar45 = "uint64_t";
              }
              else {
                pcVar45 = "uint8_t";
                if (iVar16 != 1) {
                  pcVar45 = "int";
                }
              }
              snprintf((char *)((long)puVar40 + 4),0x80,"%s",pcVar45);
            }
            else {
              snprintf((char *)((long)puVar40 + 4),0x80,"%s");
            }
            if (((char *)puVar31[2] != (char *)0x0) && (*(char *)puVar31[2] != '\0')) {
              snprintf((char *)((long)puVar40 + 0x84),0x40,"%s");
              uVar32 = (ulong)uVar30;
              uVar30 = *(uint *)(lVar19 + 0x20);
              break;
            }
            uVar51 = uVar51 + 1;
            uVar32 = (ulong)uVar30;
            lVar44 = lVar44 + 0x30;
            __snprintf_chk((long)puVar40 + 0x84,0x40,2,0x40,"arg%u",*(undefined4 *)puVar40);
            uVar30 = *(uint *)(lVar19 + 0x20);
            if (uVar30 <= uVar51) goto joined_r0x00167464;
          }
          uVar51 = uVar51 + 1;
          lVar44 = lVar44 + 0x30;
        } while (uVar51 < uVar30);
      }
    }
joined_r0x00167464:
    if ((iVar3 == 4) && (param_2 != 0 && param_3 != 0)) {
      uVar32 = param_3;
      if (0x20 < param_3) {
        uVar32 = 0x20;
      }
      uVar39 = 0;
      pcVar45 = (char *)(param_2 + 0x20);
      while ((*pcVar45 == '\0' || (iVar16 = strcmp(pcVar45,"ret"), iVar16 != 0))) {
        uVar39 = uVar39 + 1;
        pcVar45 = pcVar45 + 0xe0;
        if (uVar39 == uVar32) {
LAB_00167708:
          local_78 = 0;
          local_88 = 0;
          local_90 = 0;
          local_98 = 0;
          pcVar45 = (char *)(param_2 + 0x60);
          pcVar48 = pcVar45 + uVar32 * 0xe0;
          local_1e8 = "s0";
LAB_00167798:
          pcVar27 = pcVar45 + -0x40;
          iVar16 = strcmp(pcVar27,"fcmp");
          bVar14 = true;
          if (((((iVar16 != 0) && (iVar16 = strcmp(pcVar27,"fcmpe"), iVar16 != 0)) &&
               (iVar16 = strcmp(pcVar27,"str"), iVar16 != 0)) &&
              (((iVar16 = strcmp(pcVar27,"stp"), iVar16 != 0 &&
                (iVar16 = strcmp(pcVar27,"stur"), iVar16 != 0)) &&
               ((iVar16 = strcmp(pcVar27,"ret"), iVar16 != 0 &&
                ((*pcVar27 != 'b' || (pcVar45[-0x3f] != '\0')))))))) &&
             ((*pcVar27 != 'b' ||
              (((pcVar45[-0x3f] != 'l' || (bVar14 = true, pcVar45[-0x3e] != '\0')) &&
               ((pcVar45[-0x3f] != 'r' || (bVar14 = true, pcVar45[-0x3e] != '\0')))))))) {
            iVar16 = strcmp(pcVar27,"blr");
            bVar14 = true;
            if ((iVar16 != 0) && (iVar16 = strcmp(pcVar27,"cbz"), iVar16 != 0)) {
              iVar16 = strcmp(pcVar27,"cbnz");
              bVar14 = iVar16 == 0;
            }
          }
          lVar19 = 1;
          ppuVar35 = &s_aarch64_fp_s_regs;
          pcVar42 = s_aarch64_fp_d_regs;
          pcVar46 = local_1e8;
          pcVar27 = (char *)&local_90;
          if (s_aarch64_fp_d_regs == (undefined *)0x0) goto LAB_00167970;
LAB_00167818:
          sVar25 = strlen(pcVar42);
          pcVar29 = pcVar45;
          do {
            pcVar21 = strstr(pcVar29,pcVar42);
            if (pcVar21 == (char *)0x0) {
              puVar22 = *ppuVar35;
              goto joined_r0x00168e94;
            }
            pcVar29 = pcVar21 + sVar25;
          } while (((pcVar45 < pcVar21) &&
                   ((byte)(pcVar21[-1] + 0x9fU) < 0x1a || (byte)(pcVar21[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar21[sVar25] + 0x9fU) < 0x1a || (byte)(pcVar21[sVar25] - 0x30U) < 10));
          bVar49 = true;
          if (*ppuVar35 == (undefined *)0x0) {
            pcVar46 = (char *)0x0;
            bVar49 = true;
            bVar8 = false;
            goto LAB_00167900;
          }
LAB_00167890:
          sVar25 = strlen(pcVar46);
          pcVar29 = pcVar45;
          do {
            pcVar21 = strstr(pcVar29,pcVar46);
            if (pcVar21 == (char *)0x0) {
              if (!bVar49) goto joined_r0x0016795c;
              bVar8 = false;
              goto LAB_00167900;
            }
            pcVar29 = pcVar21 + sVar25;
          } while (((pcVar45 < pcVar21) &&
                   ((byte)(pcVar21[-1] + 0x9fU) < 0x1a || (byte)(pcVar21[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar21[sVar25] + 0x9fU) < 0x1a || (byte)(pcVar21[sVar25] - 0x30U) < 10));
          bVar8 = true;
LAB_00167900:
          iVar16 = strncmp(pcVar45,pcVar42,2);
          if (((iVar16 == 0) || (iVar16 = strncmp(pcVar45,pcVar46,2), iVar16 == 0)) && (!bVar14)) {
            if ((*pcVar27 == '\0') && (pcVar29 = strchr(pcVar45,0x2c), pcVar29 != (char *)0x0)) {
              pcVar29 = pcVar29 + 1;
              sVar25 = strlen(pcVar42);
              pcVar21 = pcVar29;
              do {
                pcVar28 = strstr(pcVar21,pcVar42);
                if (pcVar28 == (char *)0x0) {
                  if (pcVar46 == (char *)0x0) goto LAB_00168d24;
                  sVar25 = strlen(pcVar46);
                  pcVar42 = pcVar29;
                  goto LAB_001692d4;
                }
                pcVar21 = pcVar28 + sVar25;
              } while (((pcVar29 < pcVar28) &&
                       ((byte)(pcVar28[-1] + 0x9fU) < 0x1a || (byte)(pcVar28[-1] - 0x30U) < 10)) ||
                      ((byte)(pcVar28[sVar25] + 0x9fU) < 0x1a ||
                       (byte)(pcVar28[sVar25] - 0x30U) < 10));
              goto LAB_00168d18;
            }
            goto LAB_00168d24;
          }
          if (*pcVar27 == '\0') {
            (&cStack_99)[lVar19] = '\x01';
          }
          goto joined_r0x00168d28;
        }
      }
      local_98 = 0;
      local_90 = 0;
      local_88 = 0;
      local_78 = 0;
      uVar32 = uVar39;
      if (uVar39 == 0) goto LAB_001679ac;
      goto LAB_00167708;
    }
    goto LAB_00167468;
  }
  stack_frame_destroy(&local_138);
  uVar33 = 2;
  goto LAB_001674b8;
LAB_001695c0:
  if (iVar16 <= iVar18) goto code_r0x001695cc;
  iVar17 = strcmp(local_218,(char *)&local_88);
  local_218 = local_218 + 0x10;
  if (iVar17 == 0) goto joined_r0x00167cf8;
  iVar18 = iVar18 + 1;
  goto LAB_001695c0;
code_r0x001695cc:
  if (iVar16 < 8) {
    snprintf(acStack_118 + (long)iVar16 * 0x10,0x10,"%s",&local_88);
    iVar16 = iVar16 + 1;
    if (pcVar45 == (char *)0x0) {
      bVar11 = false;
      if (pcVar48 != (char *)0x0) goto LAB_00167d70;
LAB_0016880c:
      pcVar27 = acStack_118;
      do {
        sVar25 = strlen(pcVar27);
        pbVar24 = __s;
        while (pbVar26 = (byte *)strstr((char *)pbVar24,pcVar27), pbVar26 != (byte *)0x0) {
          pbVar24 = pbVar26 + sVar25;
          if (((pbVar26 <= __s) ||
              (0x19 < (byte)(pbVar26[-1] + 0x9f) && 9 < (byte)(pbVar26[-1] - 0x30))) &&
             (0x19 < (byte)(pbVar26[sVar25] + 0x9f) && 9 < (byte)(pbVar26[sVar25] - 0x30))) {
            pcVar27 = strchr((char *)__s,0x5b);
            bVar11 = bVar8;
            if (pcVar27 != (char *)0x0) goto LAB_00168ab8;
            goto LAB_001688a4;
          }
        }
        pcVar27 = pcVar27 + 0x10;
        bVar11 = bVar8;
      } while (pcVar27 != acStack_118 + (long)iVar16 * 0x10);
      goto LAB_001689ac;
    }
LAB_00167cfc:
    sVar25 = strlen(pcVar45);
    pbVar24 = __s;
    do {
      pbVar26 = (byte *)strstr((char *)pbVar24,pcVar45);
      if (pbVar26 == (byte *)0x0) goto LAB_001687f8;
      pbVar24 = pbVar26 + sVar25;
    } while (((__s < pbVar26) &&
             ((byte)(pbVar26[-1] + 0x9f) < 0x1a || (byte)(pbVar26[-1] - 0x30) < 10)) ||
            ((byte)(pbVar26[sVar25] + 0x9f) < 0x1a || (byte)(pbVar26[sVar25] - 0x30) < 10));
    bVar11 = true;
    if (pcVar48 != (char *)0x0) goto LAB_00167d70;
    bVar11 = true;
  }
  else {
joined_r0x00167cf8:
    if (pcVar45 != (char *)0x0) goto LAB_00167cfc;
LAB_001687f8:
    bVar11 = false;
    if (pcVar48 == (char *)0x0) {
LAB_00168800:
      bVar11 = bVar8;
      if (iVar16 < 1) goto LAB_001689ac;
      goto LAB_0016880c;
    }
LAB_00167d70:
    sVar25 = strlen(pcVar48);
    pbVar24 = __s;
    do {
      pbVar26 = (byte *)strstr((char *)pbVar24,pcVar48);
      if (pbVar26 == (byte *)0x0) {
        if (!bVar11) goto LAB_00168800;
        goto LAB_00167de4;
      }
      pbVar24 = pbVar26 + sVar25;
    } while (((__s < pbVar26) &&
             ((byte)(pbVar26[-1] + 0x9f) < 0x1a || (byte)(pbVar26[-1] - 0x30) < 10)) ||
            ((byte)(pbVar26[sVar25] + 0x9f) < 0x1a || (byte)(pbVar26[sVar25] - 0x30) < 10));
    if (bVar11) {
      bVar10 = 1;
    }
    else {
      bVar10 = 1;
      bVar11 = bVar8;
    }
  }
LAB_00167de4:
  pcVar27 = strchr((char *)__s,0x5b);
  if ((pcVar27 != (char *)0x0) && (0 < iVar16)) {
LAB_00168ab8:
    pcVar42 = acStack_118;
    do {
      sVar25 = strlen(pcVar42);
      pcVar46 = pcVar27;
      while (pcVar29 = strstr(pcVar46,pcVar42), pcVar29 != (char *)0x0) {
        pcVar46 = pcVar29 + sVar25;
        if (((pcVar29 <= pcVar27) ||
            (0x19 < (byte)(pcVar29[-1] + 0x9fU) && 9 < (byte)(pcVar29[-1] - 0x30U))) &&
           (0x19 < (byte)(pcVar29[sVar25] + 0x9fU) && 9 < (byte)(pcVar29[sVar25] - 0x30U))) {
          pbVar24 = __s + -0x40;
          iVar18 = strcmp((char *)pbVar24,"ldrb");
          if (((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar24,"strb"), iVar18 == 0)) ||
             (iVar18 = strcmp((char *)pbVar24,"ldrsb"), iVar18 == 0)) {
            uVar51 = 1;
          }
          else {
            iVar18 = strcmp((char *)pbVar24,"ldrh");
            if (((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar24,"strh"), iVar18 == 0)) ||
               (iVar18 = strcmp((char *)pbVar24,"ldrsh"), iVar18 == 0)) {
              uVar51 = 2;
            }
            else {
              iVar18 = strcmp((char *)pbVar24,"ldrsw");
              if (iVar18 != 0) {
                iVar18 = strcmp((char *)pbVar24,"ldr");
                if (iVar18 != 0) {
                  iVar18 = strcmp((char *)pbVar24,"str");
                  bVar12 = true;
                  if (iVar18 != 0) goto LAB_001688a4;
                }
                bVar6 = *__s;
                if (bVar6 != 0x77) {
                  if (bVar6 < 0x78) {
                    if (bVar6 == 0x57) goto LAB_001692b4;
                    if (bVar6 != 0x58) {
                      bVar12 = true;
                      goto LAB_001688a4;
                    }
                  }
                  else {
                    bVar12 = true;
                    if (bVar6 != 0x78) goto LAB_001688a4;
                  }
                  uVar51 = 8;
                  goto LAB_00168c30;
                }
              }
LAB_001692b4:
              uVar51 = 4;
            }
          }
LAB_00168c30:
          bVar12 = true;
          if (uVar30 < uVar51) {
            uVar30 = uVar51;
          }
          goto LAB_001688a4;
        }
      }
      pcVar42 = pcVar42 + 0x10;
    } while (pcVar42 != acStack_118 + (long)iVar16 * 0x10);
  }
LAB_001688a4:
  pbVar24 = __s + -0x40;
  iVar18 = strcmp((char *)pbVar24,"test");
  if ((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar24,"cmp"), iVar18 == 0)) {
    pcVar27 = strchr((char *)__s,0x30);
    if (pcVar27 == (char *)0x0) {
      pcVar27 = strstr((char *)__s,pcVar45);
      if (pcVar27 != (char *)0x0) {
        bVar9 = 1;
      }
    }
    else {
      bVar9 = 1;
    }
  }
  iVar18 = strcmp((char *)pbVar24,"add");
  if ((((((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar24,"sub"), iVar18 == 0)) ||
        (iVar18 = strcmp((char *)pbVar24,"imul"), iVar18 == 0)) ||
       ((iVar18 = strcmp((char *)pbVar24,"mul"), iVar18 == 0 ||
        (iVar18 = strcmp((char *)pbVar24,"shl"), iVar18 == 0)))) ||
      ((iVar18 = strcmp((char *)pbVar24,"shr"), iVar18 == 0 ||
       ((iVar18 = strcmp((char *)pbVar24,"csel"), iVar18 == 0 ||
        (iVar18 = strcmp((char *)pbVar24,"ccmp"), iVar18 == 0)))))) ||
     ((iVar18 = strcmp((char *)pbVar24,"orr"), iVar18 == 0 ||
      (iVar18 = strcmp((char *)pbVar24,"and"), iVar18 == 0)))) {
    bVar49 = true;
  }
  else {
    iVar18 = strcmp((char *)pbVar24,"eor");
    if (iVar18 == 0) {
      bVar49 = true;
    }
  }
LAB_001689ac:
  uVar50 = uVar50 + 1;
  __s = __s + 0xe0;
  bVar8 = bVar11;
  if (uVar32 <= uVar50) goto code_r0x001689bc;
  goto LAB_00167cd8;
code_r0x001687e0:
  uVar41 = (ulong)(iVar18 + 1);
  pcVar27 = pcVar27 + 0x10;
  goto LAB_001687e4;
code_r0x001689bc:
  if (bVar12) {
    if (uVar30 == 4) {
      pcVar45 = "int32_t*";
    }
    else if (uVar30 < 5) {
      if (uVar30 == 1) {
        pcVar45 = "int8_t*";
      }
      else {
        pcVar45 = "void*";
        if (uVar30 == 2) {
          pcVar45 = "int16_t*";
        }
      }
    }
    else {
      pcVar45 = "void*";
      if (uVar30 == 8) {
        pcVar45 = "int64_t*";
      }
    }
    goto LAB_00168a00;
  }
  if ((bool)((bVar49 ^ 1U) & bVar9)) {
    pcVar45 = "void*";
    if (!bVar14) {
      pcVar45 = "int*";
    }
    goto LAB_00168a00;
  }
  bVar8 = (bool)((bVar11 ^ 1U) & bVar10);
  if (bVar49) {
    if ((!bVar8) && (bVar14)) goto LAB_00168e04;
  }
  else {
LAB_00168df4:
    if ((bool)((bVar8 ^ 1U) & bVar14)) {
LAB_00168e04:
      pcVar45 = "int64_t";
      goto LAB_00168a00;
    }
  }
  pcVar45 = "int";
LAB_00168a00:
  snprintf((char *)((long)puVar31 + 4),0x80,"%s",pcVar45);
  uVar39 = uVar39 + 1;
  __snprintf_chk((long)puVar31 + 0x84,0x40,2,0x40,"arg%u",uVar38);
  if (uVar39 == uVar15) goto LAB_00168ee8;
  uVar30 = *(uint *)(puVar20 + 1);
  uVar51 = *(uint *)((long)puVar20 + 0xc);
  uVar38 = (undefined4)uVar39;
  uVar32 = (ulong)uVar30;
  if (uVar51 <= uVar30) goto LAB_00167b78;
LAB_00168a5c:
  pvVar23 = (void *)*puVar20;
  goto LAB_00167bb8;
  while (((pcVar42 = pcVar21 + sVar25, pcVar29 < pcVar21 &&
          ((byte)(pcVar21[-1] + 0x9fU) < 0x1a || (byte)(pcVar21[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar21[sVar25] + 0x9fU) < 0x1a || (byte)(pcVar21[sVar25] - 0x30U) < 10))) {
LAB_001692d4:
    pcVar21 = strstr(pcVar42,pcVar46);
    if (pcVar21 == (char *)0x0) goto LAB_00168d24;
  }
LAB_00168d18:
  (&cStack_99)[lVar19] = '\x01';
LAB_00168d24:
  *pcVar27 = '\x01';
joined_r0x00168d28:
  if ((!bVar49) || (*(undefined1 *)((long)&local_90 + lVar19 + 7) = 1, bVar8)) {
    (&cStack_79)[lVar19] = '\x01';
  }
joined_r0x0016795c:
  do {
    lVar19 = lVar19 + 1;
    if (lVar19 == 9) {
      pcVar45 = pcVar45 + 0xe0;
      if (pcVar45 != pcVar48) goto LAB_00167798;
      goto LAB_001679ac;
    }
    pcVar27 = pcVar27 + 1;
    ppuVar35 = ppuVar35 + 1;
    pcVar46 = *ppuVar35;
    pcVar42 = (&PTR_DAT_005dfe38)[lVar19];
    if (pcVar42 != (char *)0x0) goto LAB_00167818;
LAB_00167970:
    puVar22 = *ppuVar35;
joined_r0x00168e94:
    bVar49 = false;
  } while (puVar22 == (undefined *)0x0);
  goto LAB_00167890;
LAB_001679ac:
  iVar16 = *(int *)(puVar20 + 1);
  lVar19 = 1;
  while ((&cStack_99)[lVar19] != '\0') {
    uVar30 = *(uint *)(puVar20 + 1);
    uVar51 = *(uint *)((long)puVar20 + 0xc);
    if (uVar30 < uVar51) {
      pvVar23 = (void *)*puVar20;
    }
    else {
      uVar15 = 8;
      if ((uVar51 != 0) && (uVar15 = uVar51 << 1, 0x20 < uVar15)) {
        uVar15 = 0x20;
      }
      if ((uVar15 <= uVar30) ||
         (pvVar23 = realloc((void *)*puVar20,(ulong)uVar15 * 0xd8), pvVar23 == (void *)0x0)) break;
      uVar30 = *(uint *)(puVar20 + 1);
      *puVar20 = pvVar23;
      *(uint *)((long)puVar20 + 0xc) = uVar15;
    }
    piVar47 = (int *)((long)pvVar23 + (ulong)uVar30 * 0xd8);
    iVar18 = iVar16 + -1 + (int)lVar19;
    piVar47[0x34] = 0;
    piVar47[0x35] = 0;
    piVar47[2] = 0;
    piVar47[3] = 0;
    piVar47[0] = 0;
    piVar47[1] = 0;
    piVar47[6] = 0;
    piVar47[7] = 0;
    piVar47[4] = 0;
    piVar47[5] = 0;
    piVar47[10] = 0;
    piVar47[0xb] = 0;
    piVar47[8] = 0;
    piVar47[9] = 0;
    piVar47[0xe] = 0;
    piVar47[0xf] = 0;
    piVar47[0xc] = 0;
    piVar47[0xd] = 0;
    piVar47[0x12] = 0;
    piVar47[0x13] = 0;
    piVar47[0x10] = 0;
    piVar47[0x11] = 0;
    piVar47[0x16] = 0;
    piVar47[0x17] = 0;
    piVar47[0x14] = 0;
    piVar47[0x15] = 0;
    piVar47[0x1a] = 0;
    piVar47[0x1b] = 0;
    piVar47[0x18] = 0;
    piVar47[0x19] = 0;
    piVar47[0x1e] = 0;
    piVar47[0x1f] = 0;
    piVar47[0x1c] = 0;
    piVar47[0x1d] = 0;
    piVar47[0x22] = 0;
    piVar47[0x23] = 0;
    piVar47[0x20] = 0;
    piVar47[0x21] = 0;
    piVar47[0x26] = 0;
    piVar47[0x27] = 0;
    piVar47[0x24] = 0;
    piVar47[0x25] = 0;
    piVar47[0x2a] = 0;
    piVar47[0x2b] = 0;
    piVar47[0x28] = 0;
    piVar47[0x29] = 0;
    piVar47[0x2e] = 0;
    piVar47[0x2f] = 0;
    piVar47[0x2c] = 0;
    piVar47[0x2d] = 0;
    piVar47[0x32] = 0;
    piVar47[0x33] = 0;
    piVar47[0x30] = 0;
    piVar47[0x31] = 0;
    cVar7 = *(char *)((long)&local_90 + lVar19 + 7);
    *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
    if ((cVar7 == '\0') && ((&cStack_79)[lVar19] != '\0')) {
      pcVar45 = "float";
      iVar17 = 4;
    }
    else {
      iVar17 = 8;
      pcVar45 = "double";
    }
    *piVar47 = iVar18;
    piVar47[0x31] = 1;
    piVar47[0x32] = 0;
    piVar47[0x33] = 0;
    piVar47[0x34] = iVar17;
    lVar19 = lVar19 + 1;
    snprintf((char *)(piVar47 + 1),0x80,"%s",pcVar45);
    __snprintf_chk(piVar47 + 0x21,0x40,2,0x40,"arg%u",iVar18);
    if (lVar19 == 9) break;
  }
  iVar16 = strcmp((char *)(param_2 + 0x20),"stp");
  if (iVar16 == 0) {
    pcVar45 = strstr((char *)(param_2 + 0x60),"[sp");
    if (((((pcVar45 != (char *)0x0) &&
          (pcVar45 = strstr((char *)(param_2 + 0x60),"]!"), pcVar45 != (char *)0x0)) &&
         (*(char *)(param_2 + 0x60) == 'x')) &&
        (((byte)(*(char *)(param_2 + 0x61) - 0x30U) < 8 &&
         (*(char *)(param_2 + 0x62) == ' ' || *(char *)(param_2 + 0x62) == ',')))) &&
       ((1 < param_3 && (iVar16 = strcmp((char *)(param_2 + 0x100),"stp"), iVar16 == 0)))) {
      pcVar45 = strstr((char *)(param_2 + 0x140),"[sp");
      if ((((pcVar45 != (char *)0x0) &&
           (pcVar45 = strstr((char *)(param_2 + 0x140),"]!"), pcVar45 != (char *)0x0)) &&
          (*(char *)(param_2 + 0x140) == 'x')) &&
         (((((byte)(*(char *)(param_2 + 0x141) - 0x30U) < 8 &&
            (*(char *)(param_2 + 0x142) == ' ' || *(char *)(param_2 + 0x142) == ',')) &&
           (2 < param_3)) && (iVar16 = strcmp((char *)(param_2 + 0x1e0),"stp"), iVar16 == 0)))) {
        pcVar45 = strstr((char *)(param_2 + 0x220),"[sp");
        if (((pcVar45 != (char *)0x0) &&
            (pcVar45 = strstr((char *)(param_2 + 0x220),"]!"), pcVar45 != (char *)0x0)) &&
           ((*(char *)(param_2 + 0x220) == 'x' &&
            (((byte)(*(char *)(param_2 + 0x221) - 0x30U) < 8 &&
             (*(char *)(param_2 + 0x222) == ',' || *(char *)(param_2 + 0x222) == ' ')))))) {
          uVar30 = *(uint *)(puVar20 + 1);
          uVar51 = *(uint *)((long)puVar20 + 0xc);
          if (uVar30 < uVar51) {
            pvVar23 = (void *)*puVar20;
          }
          else {
            uVar15 = 8;
            if ((uVar51 != 0) && (uVar15 = uVar51 << 1, 0x20 < uVar15)) {
              uVar15 = 0x20;
            }
            if ((uVar15 <= uVar30) ||
               (pvVar23 = realloc((void *)*puVar20,(ulong)uVar15 * 0xd8), pvVar23 == (void *)0x0))
            goto LAB_00167468;
            uVar30 = *(uint *)(puVar20 + 1);
            *puVar20 = pvVar23;
            *(uint *)((long)puVar20 + 0xc) = uVar15;
          }
          puVar31 = (undefined8 *)((long)pvVar23 + (ulong)uVar30 * 0xd8);
          puVar31[0x1a] = 0;
          puVar31[1] = 0;
          *puVar31 = 0;
          puVar31[3] = 0;
          puVar31[2] = 0;
          puVar31[5] = 0;
          puVar31[4] = 0;
          puVar31[7] = 0;
          puVar31[6] = 0;
          puVar31[9] = 0;
          puVar31[8] = 0;
          puVar31[0xb] = 0;
          puVar31[10] = 0;
          puVar31[0xd] = 0;
          puVar31[0xc] = 0;
          puVar31[0xf] = 0;
          puVar31[0xe] = 0;
          puVar31[0x11] = 0;
          puVar31[0x10] = 0;
          puVar31[0x13] = 0;
          puVar31[0x12] = 0;
          puVar31[0x15] = 0;
          puVar31[0x14] = 0;
          puVar31[0x17] = 0;
          puVar31[0x16] = 0;
          puVar31[0x19] = 0;
          puVar31[0x18] = 0;
          iVar16 = *(int *)(puVar20 + 1);
          *(int *)(puVar20 + 1) = iVar16 + 1;
          *(int *)((long)pvVar23 + (ulong)uVar30 * 0xd8) = iVar16;
          *(undefined4 *)((long)puVar31 + 4) = 0x2e2e2e;
          *(undefined4 *)((long)puVar31 + 0x84) = 0x2e2e2e;
          *(undefined8 *)((long)puVar31 + 0xc4) = 1;
          *(undefined8 *)((long)puVar31 + 0xcc) = 0;
        }
      }
    }
  }
LAB_00167468:
  *(bool *)(puVar20 + 0x12) = local_128 != 0;
  if (local_128 != 0) {
    puVar31 = *(undefined8 **)(param_1 + 0x28);
    if ((puVar31 != (undefined8 *)0x0) && (*(uint *)(param_1 + 0x30) != 0)) {
      puVar40 = puVar31 + (ulong)*(uint *)(param_1 + 0x30) * 5;
      do {
        if ((param_4 == puVar31[2]) &&
           ((((pcVar45 = (char *)*puVar31, pcVar45 != (char *)0x0 && (*pcVar45 != '\0')) &&
             ((((iVar16 = strcmp(pcVar45,"deregister_tm_clones"), iVar16 == 0 ||
                (((iVar16 = strncmp(pcVar45,"deregister_tm_clones",0x14), iVar16 == 0 &&
                  ((pcVar45[0x14] & 0xbfU) == 0)) ||
                 (iVar16 = strcmp(pcVar45,"_start"), iVar16 == 0)))) ||
               (((iVar16 = strncmp(pcVar45,"_start",6), iVar16 == 0 && ((pcVar45[6] & 0xbfU) == 0))
                || (iVar16 = strcmp(pcVar45,"call_weak_fn"), iVar16 == 0)))) ||
              (((iVar16 = strncmp(pcVar45,"call_weak_fn",0xc), iVar16 == 0 &&
                ((pcVar45[0xc] & 0xbfU) == 0)) ||
               ((iVar16 = strcmp(pcVar45,"__do_global_dtors_aux"), iVar16 == 0 ||
                ((iVar16 = strncmp(pcVar45,"__do_global_dtors_aux",0x15), iVar16 == 0 &&
                 ((pcVar45[0x15] & 0xbfU) == 0)))))))))) ||
            (((pcVar45 = (char *)puVar31[1], pcVar45 != (char *)0x0 && (*pcVar45 != '\0')) &&
             ((((iVar16 = strcmp(pcVar45,"deregister_tm_clones"), iVar16 == 0 ||
                (((((iVar16 = strncmp(pcVar45,"deregister_tm_clones",0x14), iVar16 == 0 &&
                    ((pcVar45[0x14] & 0xbfU) == 0)) ||
                   (iVar16 = strcmp(pcVar45,"_start"), iVar16 == 0)) ||
                  ((iVar16 = strncmp(pcVar45,"_start",6), iVar16 == 0 && ((pcVar45[6] & 0xbfU) == 0)
                   ))) || (iVar16 = strcmp(pcVar45,"call_weak_fn"), iVar16 == 0)))) ||
               ((iVar16 = strncmp(pcVar45,"call_weak_fn",0xc), iVar16 == 0 &&
                ((pcVar45[0xc] & 0xbfU) == 0)))) ||
              ((iVar16 = strcmp(pcVar45,"__do_global_dtors_aux"), iVar16 == 0 ||
               ((iVar16 = strncmp(pcVar45,"__do_global_dtors_aux",0x15), iVar16 == 0 &&
                ((pcVar45[0x15] & 0xbfU) == 0)))))))))))) {
          *(undefined1 *)(puVar20 + 0x12) = 0;
          goto LAB_0016747c;
        }
        puVar31 = puVar31 + 5;
      } while (puVar31 != puVar40);
    }
    if (uVar1 == 0) {
      pcVar45 = "int64_t";
      if (param_3 == 0) {
        pcVar48 = "int64_t";
        if (iVar3 == 4) goto LAB_00168170;
LAB_00169174:
        pcVar48 = (char *)(param_2 + 0x60);
        pcVar27 = pcVar48 + param_3 * 0xe0;
        bVar9 = 0;
        bVar10 = 0;
        pcVar42 = pcVar48;
LAB_001691a8:
        do {
          pcVar29 = strstr(pcVar48,"rax");
          pcVar46 = pcVar42;
          if (pcVar29 != (char *)0x0) {
            pcVar48 = pcVar29 + 3;
            if (((pcVar42 < pcVar29) &&
                ((byte)(pcVar29[-1] + 0x9fU) < 0x1a || (byte)(pcVar29[-1] - 0x30U) < 10)) ||
               ((byte)(pcVar29[3] + 0x9fU) < 0x1a || (byte)(pcVar29[3] - 0x30U) < 10))
            goto LAB_001691a8;
            bVar10 = 1;
          }
          do {
            pcVar48 = strstr(pcVar46,"eax");
            if (pcVar48 == (char *)0x0) goto LAB_0016926c;
            pcVar46 = pcVar48 + 3;
          } while (((pcVar42 < pcVar48) &&
                   ((byte)(pcVar48[-1] + 0x9fU) < 0x1a || (byte)(pcVar48[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar48[3] + 0x9fU) < 0x1a || (byte)(pcVar48[3] - 0x30U) < 10));
          bVar9 = 1;
LAB_0016926c:
          pcVar48 = pcVar42 + 0xe0;
          pcVar42 = pcVar48;
        } while (pcVar48 != pcVar27);
        pcVar48 = "int";
        if (!(bool)((bVar10 ^ 1) & bVar9)) {
          pcVar48 = pcVar45;
        }
      }
      else {
LAB_00168118:
        pcVar48 = (char *)(param_2 + 0x20);
        uVar32 = 0;
        do {
          if ((*pcVar48 != '\0') && (iVar16 = strcmp(pcVar48,"ret"), iVar16 == 0)) {
            param_3 = uVar32 + 1;
            break;
          }
          uVar32 = uVar32 + 1;
          pcVar48 = pcVar48 + 0xe0;
        } while ((0x7f >= uVar32 && uVar32 <= param_3) && (0x7f < uVar32 || param_3 != uVar32));
        if (iVar3 == 4) {
          pcVar48 = (char *)(param_2 + 0x60);
          pcVar27 = pcVar48 + param_3 * 0xe0;
          bVar9 = 0;
          bVar10 = 0;
          pcVar42 = pcVar48;
LAB_001681e8:
          do {
            pcVar29 = strstr(pcVar48,"x0");
            pcVar46 = pcVar42;
            if (pcVar29 != (char *)0x0) {
              pcVar48 = pcVar29 + 2;
              if (((pcVar42 < pcVar29) &&
                  ((byte)(pcVar29[-1] + 0x9fU) < 0x1a || (byte)(pcVar29[-1] - 0x30U) < 10)) ||
                 ((byte)(pcVar29[2] + 0x9fU) < 0x1a || (byte)(pcVar29[2] - 0x30U) < 10))
              goto LAB_001681e8;
              bVar10 = 1;
            }
            do {
              pcVar48 = strstr(pcVar46,"w0");
              if (pcVar48 == (char *)0x0) goto LAB_001682ac;
              pcVar46 = pcVar48 + 2;
            } while (((pcVar42 < pcVar48) &&
                     ((byte)(pcVar48[-1] + 0x9fU) < 0x1a || (byte)(pcVar48[-1] - 0x30U) < 10)) ||
                    ((byte)(pcVar48[2] + 0x9fU) < 0x1a || (byte)(pcVar48[2] - 0x30U) < 10));
            bVar9 = 1;
LAB_001682ac:
            pcVar48 = pcVar42 + 0xe0;
            pcVar42 = pcVar48;
          } while (pcVar27 != pcVar48);
          pcVar48 = "int";
          if (!(bool)((bVar10 ^ 1) & bVar9)) {
            pcVar48 = pcVar45;
          }
        }
        else {
          pcVar48 = pcVar45;
          if (iVar3 == 2) goto LAB_00169174;
        }
      }
    }
    else {
      pcVar45 = "int";
      pcVar48 = pcVar45;
      if (param_3 != 0) goto LAB_00168118;
    }
LAB_00168170:
    snprintf((char *)(puVar20 + 2),0x80,"%s",pcVar48);
  }
  else {
LAB_0016747c:
    uVar13 = DAT_001f929c;
    *(undefined4 *)(puVar20 + 2) = DAT_001f9298;
    *(undefined1 *)((long)puVar20 + 0x14) = uVar13;
  }
  stack_frame_destroy(&local_138);
  uVar33 = 0;
  *param_5 = puVar20;
LAB_001674b8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar33,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

