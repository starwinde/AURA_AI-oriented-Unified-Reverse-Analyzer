
void param_id_run_part_0(long param_1,long param_2,ulong param_3,long param_4,undefined8 *param_5)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  byte bVar8;
  byte bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  undefined1 uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  long lVar19;
  undefined8 *puVar20;
  void *pvVar21;
  byte *pbVar22;
  size_t sVar23;
  byte *pbVar24;
  char *pcVar25;
  char *pcVar26;
  char *pcVar27;
  uint uVar28;
  undefined8 *puVar29;
  ulong uVar30;
  undefined8 uVar31;
  undefined **ppuVar32;
  undefined **ppuVar33;
  undefined4 uVar34;
  uint uVar35;
  byte *__s;
  undefined8 *puVar36;
  ulong uVar37;
  ulong uVar38;
  char *pcVar39;
  ulong uVar40;
  char *pcVar41;
  uint uVar42;
  char *pcVar43;
  bool bVar44;
  ulong uVar45;
  long lVar46;
  char *local_1f0;
  uint local_1c4;
  undefined4 local_1b0;
  long local_128;
  uint local_120;
  uint local_11c;
  int local_118;
  char acStack_108 [16];
  char acStack_f8 [98];
  char acStack_96 [14];
  ulong local_88 [2];
  undefined8 local_78;
  undefined8 local_70;
  long local_68;
  
  iVar3 = *(int *)(param_1 + 0xc);
  uVar1 = iVar3 - 2U & 0xfffffffd;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  cc_detect(&local_120,param_2,param_3,iVar3,0);
  lVar19 = stack_analyze(param_2,param_3,param_4,iVar3,&local_120,0);
  local_128 = lVar19;
  puVar20 = calloc(1,0x98);
  if (puVar20 == (undefined8 *)0x0) {
    stack_frame_destroy(&local_128);
    uVar31 = 2;
    goto LAB_0016691c;
  }
  uVar28 = *(uint *)(puVar20 + 1);
  uVar30 = (ulong)uVar28;
  if (local_11c != 0) {
    if (local_120 == 5) {
      uVar34 = 8;
      bVar12 = true;
      uVar42 = 4;
      ppuVar33 = (undefined **)0x0;
      ppuVar32 = (undefined **)s_ms_x64_reg_names;
      goto LAB_00166dec;
    }
    if (local_120 < 6) {
      if (local_120 == 3) {
        uVar34 = 4;
        bVar12 = false;
        uVar42 = 2;
        ppuVar33 = (undefined **)0x0;
        ppuVar32 = (undefined **)s_ms_x64_reg_names;
        goto LAB_00166dec;
      }
      if (local_120 == 4) {
        ppuVar33 = &s_sysv_reg_names_32;
        uVar34 = 8;
        bVar12 = true;
        uVar42 = 6;
        ppuVar32 = (undefined **)s_sysv_reg_names;
        goto LAB_00166dec;
      }
    }
    else {
      if (local_120 == 6) {
        uVar34 = 4;
        uVar42 = 4;
        bVar12 = false;
        ppuVar33 = (undefined **)0x0;
        ppuVar32 = (undefined **)s_arm_reg_names;
LAB_00166dec:
        uVar15 = local_11c;
        if (uVar42 < local_11c) {
          uVar15 = uVar42;
        }
        uVar42 = *(uint *)((long)puVar20 + 0xc);
        uVar37 = 0;
        local_1b0 = 0;
        uVar30 = (ulong)uVar28;
        if (uVar28 < uVar42) goto LAB_00167a64;
LAB_00166e48:
        uVar35 = 8;
        if ((uVar42 != 0) && (uVar35 = uVar42 << 1, 0x20 < uVar35)) {
          uVar35 = 0x20;
        }
        lVar19 = local_128;
        if (uVar28 < uVar35) {
          pvVar21 = realloc((void *)*puVar20,(ulong)uVar35 * 0xd8);
          if (pvVar21 != (void *)0x0) {
            uVar30 = (ulong)*(uint *)(puVar20 + 1);
            *puVar20 = pvVar21;
            *(uint *)((long)puVar20 + 0xc) = uVar35;
LAB_00166e88:
            pcVar43 = (char *)0x0;
            puVar29 = (undefined8 *)((long)pvVar21 + uVar30 * 0xd8);
            puVar29[0x1a] = 0;
            puVar29[1] = 0;
            *puVar29 = 0;
            puVar29[3] = 0;
            puVar29[2] = 0;
            puVar29[5] = 0;
            puVar29[4] = 0;
            puVar29[7] = 0;
            puVar29[6] = 0;
            puVar29[9] = 0;
            puVar29[8] = 0;
            puVar29[0xb] = 0;
            puVar29[10] = 0;
            puVar29[0xd] = 0;
            puVar29[0xc] = 0;
            puVar29[0xf] = 0;
            puVar29[0xe] = 0;
            puVar29[0x11] = 0;
            puVar29[0x10] = 0;
            puVar29[0x13] = 0;
            puVar29[0x12] = 0;
            puVar29[0x15] = 0;
            puVar29[0x14] = 0;
            puVar29[0x17] = 0;
            puVar29[0x16] = 0;
            puVar29[0x19] = 0;
            puVar29[0x18] = 0;
            pcVar41 = ppuVar32[uVar37];
            *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
            *(undefined4 *)((long)pvVar21 + uVar30 * 0xd8) = local_1b0;
            *(undefined4 *)(puVar29 + 0x1a) = uVar34;
            *(undefined4 *)((long)puVar29 + 0xc4) = 1;
            puVar29[0x19] = 0;
            if (ppuVar33 != (undefined **)0x0) {
              pcVar43 = ppuVar33[uVar37];
            }
            uVar30 = param_3;
            if (0x80 < param_3) {
              uVar30 = 0x80;
            }
            if (param_3 != 0) {
              uVar45 = 0;
              pcVar25 = (char *)(param_2 + 0x20);
              do {
                if ((*pcVar25 != '\0') && (iVar16 = strcmp(pcVar25,"ret"), iVar16 == 0)) {
                  uVar30 = uVar45 + 1;
                  snprintf(acStack_108,0x10,"%s",pcVar41);
                  goto LAB_00166f60;
                }
                uVar45 = uVar45 + 1;
                pcVar25 = pcVar25 + 0xe0;
              } while (uVar45 < uVar30);
              snprintf(acStack_108,0x10,"%s",pcVar41);
LAB_00166f60:
              __s = (byte *)(param_2 + 0x60);
              bVar44 = false;
              uVar45 = 0;
              bVar8 = 0;
              iVar16 = 1;
              local_1c4 = 0;
              bVar13 = false;
              bVar9 = 0;
              bVar11 = false;
LAB_00166fa0:
              local_88[0] = 0;
              local_88[1] = 0;
              local_78 = 0;
              local_70 = 0;
              pbVar22 = (byte *)strchr((char *)__s,0x2c);
              if (pbVar22 != (byte *)0x0) {
                sVar23 = (long)pbVar22 - (long)__s;
                if (0xf < sVar23) {
                  sVar23 = 0xf;
                }
                memcpy(local_88,__s,sVar23);
                *(char *)((long)local_88 + sVar23) = '\0';
                if ((((__s != pbVar22) &&
                     (lVar19 = sVar23 - 1, cVar7 = *(char *)((long)local_88 + lVar19),
                     cVar7 == ' ' || cVar7 == '\t')) &&
                    (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)) &&
                   (((((lVar19 = sVar23 - 2, cVar7 = *(char *)((long)local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t' &&
                       (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)) &&
                      ((lVar19 = sVar23 - 3, cVar7 = *(char *)((long)local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t' &&
                       ((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                        (lVar19 = sVar23 - 4, cVar7 = *(char *)((long)local_88 + lVar19),
                        cVar7 == ' ' || cVar7 == '\t')))))) &&
                     ((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                      (((((lVar19 = sVar23 - 5, cVar7 = *(char *)((long)local_88 + lVar19),
                          cVar7 == ' ' || cVar7 == '\t' &&
                          (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)) &&
                         (lVar19 = sVar23 - 6, cVar7 = *(char *)((long)local_88 + lVar19),
                         cVar7 == ' ' || cVar7 == '\t')) &&
                        ((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                         (lVar19 = sVar23 - 7, cVar7 = *(char *)((long)local_88 + lVar19),
                         cVar7 == ' ' || cVar7 == '\t')))) &&
                       (((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                         ((lVar19 = sVar23 - 8, cVar7 = *(char *)((long)local_88 + lVar19),
                          cVar7 == ' ' || cVar7 == '\t' &&
                          (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)))) &&
                        (lVar19 = sVar23 - 9, cVar7 = *(char *)((long)local_88 + lVar19),
                        cVar7 == ' ' || cVar7 == '\t')))))))) &&
                    ((((((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                         (lVar19 = sVar23 - 10, cVar7 = *(char *)((long)local_88 + lVar19),
                         cVar7 == ' ' || cVar7 == '\t')) &&
                        (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)) &&
                       ((lVar19 = sVar23 - 0xb, cVar7 = *(char *)((long)local_88 + lVar19),
                        cVar7 == ' ' || cVar7 == '\t' &&
                        (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)))) &&
                      (lVar19 = sVar23 - 0xc, cVar7 = *(char *)((long)local_88 + lVar19),
                      cVar7 == ' ' || cVar7 == '\t')) &&
                     (((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                       (lVar19 = sVar23 - 0xd, cVar7 = *(char *)((long)local_88 + lVar19),
                       cVar7 == ' ' || cVar7 == '\t')) &&
                      ((*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0 &&
                       (((lVar19 = sVar23 - 0xe, cVar7 = *(char *)((long)local_88 + lVar19),
                         cVar7 == ' ' || cVar7 == '\t' &&
                         (*(char *)((long)local_88 + lVar19) = '\0', lVar19 != 0)) &&
                        ((char)local_88[0] == ' ' || (char)local_88[0] == '\t')))))))))))) {
                  local_88[0] = local_88[0] & 0xffffffffffffff00;
                }
                uVar31 = local_70;
                uVar38 = local_78;
                bVar6 = pbVar22[1];
                pbVar22 = pbVar22 + 1;
                while (bVar6 == 0x20) {
                  pbVar22 = pbVar22 + 1;
                  bVar6 = *pbVar22;
                }
                if (bVar6 == 0x2c || bVar6 == 0) {
                  iVar18 = 0;
                }
                else {
                  bVar4 = pbVar22[1];
                  local_78 = CONCAT71(local_78._1_7_,bVar6);
                  if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                    iVar18 = 1;
                  }
                  else {
                    bVar5 = pbVar22[2];
                    local_78._2_6_ = SUB86(uVar38,2);
                    local_78._0_2_ = CONCAT11(bVar4,bVar6);
                    if (bVar5 == 0x2c || (bVar5 & 0xdf) == 0) {
                      iVar18 = 2;
                    }
                    else {
                      bVar6 = pbVar22[3];
                      local_78._3_5_ = SUB85(uVar38,3);
                      local_78._0_3_ = CONCAT12(bVar5,(undefined2)local_78);
                      if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                        iVar18 = 3;
                      }
                      else {
                        bVar4 = pbVar22[4];
                        local_78._4_4_ = SUB84(uVar38,4);
                        local_78._0_4_ = CONCAT13(bVar6,(undefined3)local_78);
                        if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                          iVar18 = 4;
                        }
                        else {
                          bVar6 = pbVar22[5];
                          local_78._5_3_ = SUB83(uVar38,5);
                          local_78._0_5_ = CONCAT14(bVar4,(undefined4)local_78);
                          if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                            iVar18 = 5;
                          }
                          else {
                            bVar4 = pbVar22[6];
                            local_78._6_2_ = SUB82(uVar38,6);
                            local_78._0_6_ = CONCAT15(bVar6,(undefined5)local_78);
                            if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                              iVar18 = 6;
                            }
                            else {
                              bVar6 = pbVar22[7];
                              local_78._7_1_ = SUB81(uVar38,7);
                              local_78._0_7_ = CONCAT16(bVar4,(undefined6)local_78);
                              if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                iVar18 = 7;
                              }
                              else {
                                bVar4 = pbVar22[8];
                                local_78 = CONCAT17(bVar6,(undefined7)local_78);
                                if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                  iVar18 = 8;
                                }
                                else {
                                  bVar6 = pbVar22[9];
                                  local_70 = CONCAT71(local_70._1_7_,bVar4);
                                  if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                    iVar18 = 9;
                                  }
                                  else {
                                    bVar5 = pbVar22[10];
                                    local_70._2_6_ = SUB86(uVar31,2);
                                    local_70._0_2_ = CONCAT11(bVar6,bVar4);
                                    if (bVar5 == 0x2c || (bVar5 & 0xdf) == 0) {
                                      iVar18 = 10;
                                    }
                                    else {
                                      bVar6 = pbVar22[0xb];
                                      local_70._3_5_ = SUB85(uVar31,3);
                                      local_70._0_3_ = CONCAT12(bVar5,(undefined2)local_70);
                                      if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                        iVar18 = 0xb;
                                      }
                                      else {
                                        bVar4 = pbVar22[0xc];
                                        local_70._4_4_ = SUB84(uVar31,4);
                                        local_70._0_4_ = CONCAT13(bVar6,(undefined3)local_70);
                                        if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                          iVar18 = 0xc;
                                        }
                                        else {
                                          bVar6 = pbVar22[0xd];
                                          local_70._5_3_ = SUB83(uVar31,5);
                                          local_70._0_5_ = CONCAT14(bVar4,(undefined4)local_70);
                                          if (bVar6 == 0x2c || (bVar6 & 0xdf) == 0) {
                                            iVar18 = 0xd;
                                          }
                                          else {
                                            bVar4 = pbVar22[0xe];
                                            local_70._6_2_ = SUB82(uVar31,6);
                                            local_70._0_6_ = CONCAT15(bVar6,(undefined5)local_70);
                                            if (bVar4 == 0x2c || (bVar4 & 0xdf) == 0) {
                                              iVar18 = 0xe;
                                            }
                                            else {
                                              local_70._7_1_ = SUB81(uVar31,7);
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
                if ((char)local_88[0] != '\0') {
                  pbVar22 = __s + -0x40;
                  iVar18 = strcmp((char *)pbVar22,"cmp");
                  if (((((iVar18 != 0) && (iVar18 = strcmp((char *)pbVar22,"cmn"), iVar18 != 0)) &&
                       ((iVar18 = strcmp((char *)pbVar22,"tst"), iVar18 != 0 &&
                        ((iVar18 = strcmp((char *)pbVar22,"str"), iVar18 != 0 &&
                         (iVar18 = strcmp((char *)pbVar22,"strb"), iVar18 != 0)))))) &&
                      ((((iVar18 = strcmp((char *)pbVar22,"strh"), iVar18 != 0 &&
                         (((iVar18 = strcmp((char *)pbVar22,"stp"), iVar18 != 0 &&
                           (iVar18 = strcmp((char *)pbVar22,"cbz"), iVar18 != 0)) &&
                          (iVar18 = strcmp((char *)pbVar22,"cbnz"), iVar18 != 0)))) &&
                        (((iVar18 = strcmp((char *)pbVar22,"tbz"), iVar18 != 0 &&
                          (iVar18 = strcmp((char *)pbVar22,"tbnz"), iVar18 != 0)) &&
                         ((*pbVar22 != 0x62 || (__s[-0x3f] != 0)))))) &&
                       (((*pbVar22 != 0x62 || (__s[-0x3f] != 0x6c)) || (__s[-0x3e] != 0)))))) &&
                     (((iVar18 = strcmp((char *)pbVar22,"br"), iVar18 != 0 &&
                       (iVar18 = strcmp((char *)pbVar22,"blr"), iVar18 != 0)) &&
                      (iVar18 = strcmp((char *)pbVar22,"ret"), iVar18 != 0)))) {
                    iVar18 = strcmp((char *)pbVar22,"mov");
                    uVar28 = (uint)(-0x3ff000800000002 >> (local_78 & 0x3f)) & 1;
                    if (0x39 < (byte)local_78) {
                      uVar28 = 1;
                    }
                    if (iVar18 == 0 && uVar28 != 0) {
                      pcVar25 = acStack_108;
                      for (iVar18 = 0; iVar18 < iVar16; iVar18 = iVar18 + 1) {
                        iVar17 = strcmp(pcVar25,(char *)&local_78);
                        if (iVar17 == 0) {
                          iVar18 = 0;
                          local_1f0 = acStack_108;
                          goto LAB_001680f0;
                        }
                        pcVar25 = pcVar25 + 0x10;
                      }
                    }
                    uVar38 = 1;
                    pcVar25 = acStack_f8;
LAB_001677ec:
                    iVar18 = (int)uVar38;
                    if (iVar18 < iVar16) {
                      iVar17 = strcmp(pcVar25,(char *)local_88);
                      if (iVar17 != 0) goto code_r0x001677e8;
                      uVar40 = -(uVar38 >> 0x1f) & 0xfffffff000000000 | uVar38 << 4;
                      iVar16 = iVar16 + -1;
                      pcVar25 = acStack_108 + (long)iVar18 * 0x10;
                      for (; (int)uVar38 < iVar16; uVar38 = (ulong)((int)uVar38 + 1)) {
                        uVar2 = uVar40;
                        if (uVar40 < 0x80) {
                          uVar2 = 0x80;
                        }
                        __memcpy_chk(pcVar25,pcVar25 + 0x10,0x10,uVar2 - uVar40);
                        uVar40 = uVar40 + 0x10;
                        pcVar25 = pcVar25 + 0x10;
                      }
                    }
                  }
                }
              }
              goto joined_r0x00166fc0;
            }
            snprintf(acStack_108,0x10,"%s",pcVar41);
            bVar11 = false;
            goto LAB_00167d1c;
          }
LAB_00167df4:
          uVar30 = (ulong)*(uint *)(puVar20 + 1);
          lVar19 = local_128;
        }
        goto LAB_00166720;
      }
      if (local_120 == 7) {
        ppuVar33 = &s_aarch64_reg_names_32;
        uVar34 = 8;
        ppuVar32 = &s_aarch64_reg_names;
        uVar42 = 8;
        bVar12 = true;
        goto LAB_00166dec;
      }
    }
  }
LAB_00166720:
  if ((lVar19 == 0) || (uVar28 = *(uint *)(lVar19 + 0x20), uVar28 == 0)) {
LAB_001668d0:
    *(bool *)(puVar20 + 0x12) = local_118 != 0;
    if (local_118 == 0) goto LAB_001668e4;
LAB_00166b08:
    puVar29 = *(undefined8 **)(param_1 + 0x28);
    if ((puVar29 != (undefined8 *)0x0) && (*(uint *)(param_1 + 0x30) != 0)) {
      puVar36 = puVar29 + (ulong)*(uint *)(param_1 + 0x30) * 5;
      do {
        if ((param_4 == puVar29[2]) &&
           ((((pcVar41 = (char *)*puVar29, pcVar41 != (char *)0x0 && (*pcVar41 != '\0')) &&
             ((((iVar16 = strcmp(pcVar41,"deregister_tm_clones"), iVar16 == 0 ||
                (((iVar16 = strncmp(pcVar41,"deregister_tm_clones",0x14), iVar16 == 0 &&
                  ((pcVar41[0x14] & 0xbfU) == 0)) ||
                 (iVar16 = strcmp(pcVar41,"_start"), iVar16 == 0)))) ||
               ((((iVar16 = strncmp(pcVar41,"_start",6), iVar16 == 0 && ((pcVar41[6] & 0xbfU) == 0))
                 || (iVar16 = strcmp(pcVar41,"call_weak_fn"), iVar16 == 0)) ||
                ((iVar16 = strncmp(pcVar41,"call_weak_fn",0xc), iVar16 == 0 &&
                 ((pcVar41[0xc] & 0xbfU) == 0)))))) ||
              ((iVar16 = strcmp(pcVar41,"__do_global_dtors_aux"), iVar16 == 0 ||
               ((iVar16 = strncmp(pcVar41,"__do_global_dtors_aux",0x15), iVar16 == 0 &&
                ((pcVar41[0x15] & 0xbfU) == 0)))))))) ||
            (((pcVar41 = (char *)puVar29[1], pcVar41 != (char *)0x0 && (*pcVar41 != '\0')) &&
             (((((iVar16 = strcmp(pcVar41,"deregister_tm_clones"), iVar16 == 0 ||
                 (((iVar16 = strncmp(pcVar41,"deregister_tm_clones",0x14), iVar16 == 0 &&
                   ((pcVar41[0x14] & 0xbfU) == 0)) ||
                  (iVar16 = strcmp(pcVar41,"_start"), iVar16 == 0)))) ||
                ((iVar16 = strncmp(pcVar41,"_start",6), iVar16 == 0 && ((pcVar41[6] & 0xbfU) == 0)))
                ) || (iVar16 = strcmp(pcVar41,"call_weak_fn"), iVar16 == 0)) ||
              (((iVar16 = strncmp(pcVar41,"call_weak_fn",0xc), iVar16 == 0 &&
                ((pcVar41[0xc] & 0xbfU) == 0)) ||
               ((iVar16 = strcmp(pcVar41,"__do_global_dtors_aux"), iVar16 == 0 ||
                ((iVar16 = strncmp(pcVar41,"__do_global_dtors_aux",0x15), iVar16 == 0 &&
                 ((pcVar41[0x15] & 0xbfU) == 0)))))))))))))) {
          *(undefined1 *)(puVar20 + 0x12) = 0;
          goto LAB_001668e4;
        }
        puVar29 = puVar29 + 5;
      } while (puVar36 != puVar29);
    }
    if (uVar1 == 0) {
      pcVar41 = "int64_t";
      if (param_3 == 0) {
        pcVar43 = "int64_t";
        if (iVar3 == 4) goto LAB_00166da0;
LAB_00167e24:
        pcVar43 = (char *)(param_2 + 0x60);
        pcVar25 = pcVar43 + param_3 * 0xe0;
        bVar8 = 0;
        bVar9 = 0;
        pcVar39 = pcVar43;
LAB_00167e58:
        do {
          pcVar27 = strstr(pcVar43,"rax");
          pcVar26 = pcVar39;
          if (pcVar27 != (char *)0x0) {
            pcVar43 = pcVar27 + 3;
            if (((pcVar39 < pcVar27) &&
                ((byte)(pcVar27[-1] + 0x9fU) < 0x1a || (byte)(pcVar27[-1] - 0x30U) < 10)) ||
               ((byte)(pcVar27[3] + 0x9fU) < 0x1a || (byte)(pcVar27[3] - 0x30U) < 10))
            goto LAB_00167e58;
            bVar9 = 1;
          }
          do {
            pcVar43 = strstr(pcVar26,"eax");
            if (pcVar43 == (char *)0x0) goto LAB_00167f1c;
            pcVar26 = pcVar43 + 3;
          } while (((pcVar39 < pcVar43) &&
                   ((byte)(pcVar43[-1] + 0x9fU) < 0x1a || (byte)(pcVar43[-1] - 0x30U) < 10)) ||
                  ((byte)(pcVar43[3] + 0x9fU) < 0x1a || (byte)(pcVar43[3] - 0x30U) < 10));
          bVar8 = 1;
LAB_00167f1c:
          pcVar43 = pcVar39 + 0xe0;
          pcVar39 = pcVar43;
        } while (pcVar43 != pcVar25);
        pcVar43 = "int";
        if (!(bool)((bVar9 ^ 1) & bVar8)) {
          pcVar43 = pcVar41;
        }
      }
      else {
LAB_00166d48:
        pcVar43 = (char *)(param_2 + 0x20);
        uVar30 = 0;
        do {
          if ((*pcVar43 != '\0') && (iVar16 = strcmp(pcVar43,"ret"), iVar16 == 0)) {
            param_3 = uVar30 + 1;
            break;
          }
          uVar30 = uVar30 + 1;
          pcVar43 = pcVar43 + 0xe0;
        } while ((0x7f >= uVar30 && uVar30 <= param_3) && (0x7f < uVar30 || param_3 != uVar30));
        if (iVar3 == 4) {
          pcVar43 = (char *)(param_2 + 0x60);
          pcVar25 = pcVar43 + param_3 * 0xe0;
          bVar8 = 0;
          bVar9 = 0;
          pcVar39 = pcVar43;
LAB_001671f0:
          do {
            pcVar27 = strstr(pcVar43,"x0");
            pcVar26 = pcVar39;
            if (pcVar27 != (char *)0x0) {
              pcVar43 = pcVar27 + 2;
              if (((pcVar39 < pcVar27) &&
                  ((byte)(pcVar27[-1] + 0x9fU) < 0x1a || (byte)(pcVar27[-1] - 0x30U) < 10)) ||
                 ((byte)(pcVar27[2] + 0x9fU) < 0x1a || (byte)(pcVar27[2] - 0x30U) < 10))
              goto LAB_001671f0;
              bVar9 = 1;
            }
            do {
              pcVar43 = strstr(pcVar26,"w0");
              if (pcVar43 == (char *)0x0) goto LAB_001672b4;
              pcVar26 = pcVar43 + 2;
            } while (((pcVar39 < pcVar43) &&
                     ((byte)(pcVar43[-1] + 0x9fU) < 0x1a || (byte)(pcVar43[-1] - 0x30U) < 10)) ||
                    ((byte)(pcVar43[2] + 0x9fU) < 0x1a || (byte)(pcVar43[2] - 0x30U) < 10));
            bVar8 = 1;
LAB_001672b4:
            pcVar43 = pcVar39 + 0xe0;
            pcVar39 = pcVar43;
          } while (pcVar25 != pcVar43);
          pcVar43 = "int";
          if (!(bool)((bVar9 ^ 1) & bVar8)) {
            pcVar43 = pcVar41;
          }
        }
        else {
          pcVar43 = pcVar41;
          if (iVar3 == 2) goto LAB_00167e24;
        }
      }
    }
    else {
      pcVar41 = "int";
      pcVar43 = pcVar41;
      if (param_3 != 0) goto LAB_00166d48;
    }
LAB_00166da0:
    snprintf((char *)(puVar20 + 2),0x80,"%s",pcVar43);
  }
  else {
    if (uVar1 != 0) {
      uVar42 = 0;
      lVar46 = 0;
      do {
        while (puVar29 = (undefined8 *)(*(long *)(lVar19 + 0x18) + lVar46),
              *(int *)(puVar29 + 4) == 2) {
          uVar15 = *(uint *)(puVar20 + 1);
          uVar28 = *(uint *)((long)puVar20 + 0xc);
          if (uVar15 < uVar28) {
            pvVar21 = (void *)*puVar20;
          }
          else {
            if (uVar28 == 0) {
              uVar28 = 8;
            }
            else {
              uVar28 = uVar28 << 1;
              if (0x20 < uVar28) {
                uVar28 = 0x20;
              }
            }
            if ((uVar28 <= uVar15) ||
               (pvVar21 = realloc((void *)*puVar20,(ulong)uVar28 * 0xd8), pvVar21 == (void *)0x0))
            goto LAB_001668d0;
            uVar15 = *(uint *)(puVar20 + 1);
            *puVar20 = pvVar21;
            *(uint *)((long)puVar20 + 0xc) = uVar28;
          }
          uVar28 = (int)uVar30 + 1;
          puVar36 = (undefined8 *)((long)pvVar21 + (ulong)uVar15 * 0xd8);
          puVar36[0x1a] = 0;
          puVar36[1] = 0;
          *puVar36 = 0;
          puVar36[3] = 0;
          puVar36[2] = 0;
          puVar36[5] = 0;
          puVar36[4] = 0;
          puVar36[7] = 0;
          puVar36[6] = 0;
          puVar36[9] = 0;
          puVar36[8] = 0;
          puVar36[0xb] = 0;
          puVar36[10] = 0;
          puVar36[0xd] = 0;
          puVar36[0xc] = 0;
          puVar36[0xf] = 0;
          puVar36[0xe] = 0;
          puVar36[0x11] = 0;
          puVar36[0x10] = 0;
          puVar36[0x13] = 0;
          puVar36[0x12] = 0;
          puVar36[0x15] = 0;
          puVar36[0x14] = 0;
          puVar36[0x17] = 0;
          puVar36[0x16] = 0;
          puVar36[0x19] = 0;
          puVar36[0x18] = 0;
          pcVar41 = (char *)puVar29[3];
          *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
          uVar31 = *puVar29;
          *(int *)((long)pvVar21 + (ulong)uVar15 * 0xd8) = (int)uVar30;
          iVar16 = *(int *)(puVar29 + 1);
          *(undefined4 *)((long)puVar36 + 0xc4) = 2;
          puVar36[0x19] = uVar31;
          *(int *)(puVar36 + 0x1a) = iVar16;
          if ((pcVar41 == (char *)0x0) || (*pcVar41 == '\0')) {
            if (iVar16 == 2) {
              pcVar41 = "uint16_t";
            }
            else if (iVar16 == 8) {
              pcVar41 = "uint64_t";
            }
            else {
              pcVar41 = "uint8_t";
              if (iVar16 != 1) {
                pcVar41 = "int";
              }
            }
            snprintf((char *)((long)puVar36 + 4),0x80,"%s",pcVar41);
          }
          else {
            snprintf((char *)((long)puVar36 + 4),0x80,"%s");
          }
          if (((char *)puVar29[2] != (char *)0x0) && (*(char *)puVar29[2] != '\0')) {
            snprintf((char *)((long)puVar36 + 0x84),0x40,"%s");
            uVar30 = (ulong)uVar28;
            uVar28 = *(uint *)(lVar19 + 0x20);
            break;
          }
          uVar42 = uVar42 + 1;
          uVar30 = (ulong)uVar28;
          lVar46 = lVar46 + 0x30;
          __snprintf_chk((long)puVar36 + 0x84,0x40,2,0x40,"arg%u",*(undefined4 *)puVar36);
          uVar28 = *(uint *)(lVar19 + 0x20);
          if (uVar28 <= uVar42) goto LAB_001668d0;
        }
        uVar42 = uVar42 + 1;
        lVar46 = lVar46 + 0x30;
      } while (uVar42 < uVar28);
      goto LAB_001668d0;
    }
    lVar46 = 0;
    uVar42 = 0;
    do {
      while (puVar29 = (undefined8 *)(*(long *)(lVar19 + 0x18) + lVar46), *(int *)(puVar29 + 4) == 2
            ) {
        uVar28 = *(uint *)(puVar20 + 1);
        uVar15 = *(uint *)((long)puVar20 + 0xc);
        if (uVar28 < uVar15) {
          pvVar21 = (void *)*puVar20;
        }
        else {
          uVar35 = 8;
          if ((uVar15 != 0) && (uVar35 = uVar15 << 1, 0x20 < uVar35)) {
            uVar35 = 0x20;
          }
          if ((uVar35 <= uVar28) ||
             (pvVar21 = realloc((void *)*puVar20,(ulong)uVar35 * 0xd8), pvVar21 == (void *)0x0))
          goto LAB_00166ae8;
          uVar28 = *(uint *)(puVar20 + 1);
          *puVar20 = pvVar21;
          *(uint *)((long)puVar20 + 0xc) = uVar35;
        }
        uVar15 = (int)uVar30 + 1;
        puVar36 = (undefined8 *)((long)pvVar21 + (ulong)uVar28 * 0xd8);
        puVar36[0x1a] = 0;
        puVar36[1] = 0;
        *puVar36 = 0;
        puVar36[3] = 0;
        puVar36[2] = 0;
        puVar36[5] = 0;
        puVar36[4] = 0;
        puVar36[7] = 0;
        puVar36[6] = 0;
        puVar36[9] = 0;
        puVar36[8] = 0;
        puVar36[0xb] = 0;
        puVar36[10] = 0;
        puVar36[0xd] = 0;
        puVar36[0xc] = 0;
        puVar36[0xf] = 0;
        puVar36[0xe] = 0;
        puVar36[0x11] = 0;
        puVar36[0x10] = 0;
        puVar36[0x13] = 0;
        puVar36[0x12] = 0;
        puVar36[0x15] = 0;
        puVar36[0x14] = 0;
        puVar36[0x17] = 0;
        puVar36[0x16] = 0;
        puVar36[0x19] = 0;
        puVar36[0x18] = 0;
        pcVar41 = (char *)puVar29[3];
        *(int *)(puVar20 + 1) = *(int *)(puVar20 + 1) + 1;
        uVar31 = *puVar29;
        *(int *)((long)pvVar21 + (ulong)uVar28 * 0xd8) = (int)uVar30;
        uVar28 = *(uint *)(puVar29 + 1);
        *(undefined4 *)((long)puVar36 + 0xc4) = 2;
        puVar36[0x19] = uVar31;
        *(uint *)(puVar36 + 0x1a) = uVar28;
        if ((pcVar41 == (char *)0x0) || (*pcVar41 == '\0')) {
          if (uVar28 == 4) {
            pcVar41 = "uint32_t";
          }
          else if (uVar28 < 5) {
            if (uVar28 == 1) {
              pcVar41 = "uint8_t";
            }
            else {
              pcVar41 = "int";
              if (uVar28 == 2) {
                pcVar41 = "uint16_t";
              }
            }
          }
          else {
            pcVar41 = "int";
            if (uVar28 == 8) {
              pcVar41 = "uint64_t";
            }
          }
          snprintf((char *)((long)puVar36 + 4),0x80,"%s",pcVar41);
        }
        else {
          snprintf((char *)((long)puVar36 + 4),0x80,"%s");
        }
        if (((char *)puVar29[2] != (char *)0x0) && (*(char *)puVar29[2] != '\0')) {
          snprintf((char *)((long)puVar36 + 0x84),0x40,"%s");
          uVar28 = *(uint *)(lVar19 + 0x20);
          uVar30 = (ulong)uVar15;
          break;
        }
        uVar42 = uVar42 + 1;
        uVar30 = (ulong)uVar15;
        lVar46 = lVar46 + 0x30;
        __snprintf_chk((long)puVar36 + 0x84,0x40,2,0x40,"arg%u",*(undefined4 *)puVar36);
        uVar28 = *(uint *)(lVar19 + 0x20);
        if (uVar28 <= uVar42) goto LAB_00166ae8;
      }
      uVar42 = uVar42 + 1;
      lVar46 = lVar46 + 0x30;
    } while (uVar42 < uVar28);
LAB_00166ae8:
    *(bool *)(puVar20 + 0x12) = local_118 != 0;
    if (local_118 != 0) goto LAB_00166b08;
LAB_001668e4:
    uVar14 = DAT_001f7ca4;
    *(undefined4 *)(puVar20 + 2) = DAT_001f7ca0;
    *(undefined1 *)((long)puVar20 + 0x14) = uVar14;
  }
  stack_frame_destroy(&local_128);
  uVar31 = 0;
  *param_5 = puVar20;
LAB_0016691c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar31,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
LAB_001680f0:
  if (iVar16 <= iVar18) goto code_r0x001680fc;
  iVar17 = strcmp(local_1f0,(char *)local_88);
  local_1f0 = local_1f0 + 0x10;
  if (iVar17 == 0) goto joined_r0x00166fc0;
  iVar18 = iVar18 + 1;
  goto LAB_001680f0;
code_r0x001680fc:
  if (iVar16 < 8) {
    snprintf(acStack_108 + (long)iVar16 * 0x10,0x10,"%s",local_88);
    iVar16 = iVar16 + 1;
    if (pcVar41 == (char *)0x0) {
      bVar10 = false;
      if (pcVar43 != (char *)0x0) goto LAB_00167038;
LAB_00167814:
      pcVar25 = acStack_108;
      do {
        sVar23 = strlen(pcVar25);
        pbVar22 = __s;
        while (pbVar24 = (byte *)strstr((char *)pbVar22,pcVar25), pbVar24 != (byte *)0x0) {
          pbVar22 = pbVar24 + sVar23;
          if (((pbVar24 <= __s) ||
              (0x19 < (byte)(pbVar24[-1] + 0x9f) && 9 < (byte)(pbVar24[-1] - 0x30))) &&
             (0x19 < (byte)(pbVar24[sVar23] + 0x9f) && 9 < (byte)(pbVar24[sVar23] - 0x30))) {
            pcVar25 = strchr((char *)__s,0x5b);
            bVar10 = bVar11;
            if (pcVar25 != (char *)0x0) goto LAB_00167ac0;
            goto LAB_001678ac;
          }
        }
        pcVar25 = pcVar25 + 0x10;
        bVar10 = bVar11;
      } while (pcVar25 != acStack_108 + (long)iVar16 * 0x10);
      goto LAB_001679b4;
    }
LAB_00166fc4:
    sVar23 = strlen(pcVar41);
    pbVar22 = __s;
    do {
      pbVar24 = (byte *)strstr((char *)pbVar22,pcVar41);
      if (pbVar24 == (byte *)0x0) goto LAB_00167800;
      pbVar22 = pbVar24 + sVar23;
    } while (((__s < pbVar24) &&
             ((byte)(pbVar24[-1] + 0x9f) < 0x1a || (byte)(pbVar24[-1] - 0x30) < 10)) ||
            ((byte)(pbVar24[sVar23] + 0x9f) < 0x1a || (byte)(pbVar24[sVar23] - 0x30) < 10));
    bVar10 = true;
    if (pcVar43 != (char *)0x0) goto LAB_00167038;
    bVar10 = true;
  }
  else {
joined_r0x00166fc0:
    if (pcVar41 != (char *)0x0) goto LAB_00166fc4;
LAB_00167800:
    bVar10 = false;
    if (pcVar43 == (char *)0x0) {
LAB_00167808:
      bVar10 = bVar11;
      if (iVar16 < 1) goto LAB_001679b4;
      goto LAB_00167814;
    }
LAB_00167038:
    sVar23 = strlen(pcVar43);
    pbVar22 = __s;
    do {
      pbVar24 = (byte *)strstr((char *)pbVar22,pcVar43);
      if (pbVar24 == (byte *)0x0) {
        if (!bVar10) goto LAB_00167808;
        goto LAB_001670ac;
      }
      pbVar22 = pbVar24 + sVar23;
    } while (((__s < pbVar24) &&
             ((byte)(pbVar24[-1] + 0x9f) < 0x1a || (byte)(pbVar24[-1] - 0x30) < 10)) ||
            ((byte)(pbVar24[sVar23] + 0x9f) < 0x1a || (byte)(pbVar24[sVar23] - 0x30) < 10));
    if (bVar10) {
      bVar9 = 1;
    }
    else {
      bVar9 = 1;
      bVar10 = bVar11;
    }
  }
LAB_001670ac:
  pcVar25 = strchr((char *)__s,0x5b);
  if ((pcVar25 != (char *)0x0) && (0 < iVar16)) {
LAB_00167ac0:
    pcVar39 = acStack_108;
    do {
      sVar23 = strlen(pcVar39);
      pcVar26 = pcVar25;
      while (pcVar27 = strstr(pcVar26,pcVar39), pcVar27 != (char *)0x0) {
        pcVar26 = pcVar27 + sVar23;
        if (((pcVar27 <= pcVar25) ||
            (0x19 < (byte)(pcVar27[-1] + 0x9fU) && 9 < (byte)(pcVar27[-1] - 0x30U))) &&
           (0x19 < (byte)(pcVar27[sVar23] + 0x9fU) && 9 < (byte)(pcVar27[sVar23] - 0x30U))) {
          pbVar22 = __s + -0x40;
          iVar18 = strcmp((char *)pbVar22,"ldrb");
          if (((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar22,"strb"), iVar18 == 0)) ||
             (iVar18 = strcmp((char *)pbVar22,"ldrsb"), iVar18 == 0)) {
            uVar28 = 1;
          }
          else {
            iVar18 = strcmp((char *)pbVar22,"ldrh");
            if (((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar22,"strh"), iVar18 == 0)) ||
               (iVar18 = strcmp((char *)pbVar22,"ldrsh"), iVar18 == 0)) {
              uVar28 = 2;
            }
            else {
              iVar18 = strcmp((char *)pbVar22,"ldrsw");
              if (iVar18 != 0) {
                iVar18 = strcmp((char *)pbVar22,"ldr");
                if (iVar18 != 0) {
                  iVar18 = strcmp((char *)pbVar22,"str");
                  bVar13 = true;
                  if (iVar18 != 0) goto LAB_001678ac;
                }
                bVar6 = *__s;
                if (bVar6 != 0x77) {
                  if (bVar6 < 0x78) {
                    if (bVar6 == 0x57) goto LAB_00167f64;
                    if (bVar6 != 0x58) {
                      bVar13 = true;
                      goto LAB_001678ac;
                    }
                  }
                  else {
                    bVar13 = true;
                    if (bVar6 != 0x78) goto LAB_001678ac;
                  }
                  uVar28 = 8;
                  goto LAB_00167c38;
                }
              }
LAB_00167f64:
              uVar28 = 4;
            }
          }
LAB_00167c38:
          if (local_1c4 < uVar28) {
            local_1c4 = uVar28;
          }
          bVar13 = true;
          goto LAB_001678ac;
        }
      }
      pcVar39 = pcVar39 + 0x10;
    } while (pcVar39 != acStack_108 + (long)iVar16 * 0x10);
  }
LAB_001678ac:
  pbVar22 = __s + -0x40;
  iVar18 = strcmp((char *)pbVar22,"test");
  if ((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar22,"cmp"), iVar18 == 0)) {
    pcVar25 = strchr((char *)__s,0x30);
    if (pcVar25 == (char *)0x0) {
      pcVar25 = strstr((char *)__s,pcVar41);
      if (pcVar25 != (char *)0x0) {
        bVar8 = 1;
      }
    }
    else {
      bVar8 = 1;
    }
  }
  iVar18 = strcmp((char *)pbVar22,"add");
  if ((((((iVar18 == 0) || (iVar18 = strcmp((char *)pbVar22,"sub"), iVar18 == 0)) ||
        (iVar18 = strcmp((char *)pbVar22,"imul"), iVar18 == 0)) ||
       ((iVar18 = strcmp((char *)pbVar22,"mul"), iVar18 == 0 ||
        (iVar18 = strcmp((char *)pbVar22,"shl"), iVar18 == 0)))) ||
      ((iVar18 = strcmp((char *)pbVar22,"shr"), iVar18 == 0 ||
       ((iVar18 = strcmp((char *)pbVar22,"csel"), iVar18 == 0 ||
        (iVar18 = strcmp((char *)pbVar22,"ccmp"), iVar18 == 0)))))) ||
     ((iVar18 = strcmp((char *)pbVar22,"orr"), iVar18 == 0 ||
      (iVar18 = strcmp((char *)pbVar22,"and"), iVar18 == 0)))) {
    bVar44 = true;
  }
  else {
    iVar18 = strcmp((char *)pbVar22,"eor");
    if (iVar18 == 0) {
      bVar44 = true;
    }
  }
LAB_001679b4:
  uVar45 = uVar45 + 1;
  __s = __s + 0xe0;
  bVar11 = bVar10;
  if (uVar30 <= uVar45) goto code_r0x001679c4;
  goto LAB_00166fa0;
code_r0x001677e8:
  uVar38 = (ulong)(iVar18 + 1);
  pcVar25 = pcVar25 + 0x10;
  goto LAB_001677ec;
code_r0x001679c4:
  if (bVar13) {
    if (local_1c4 == 4) {
      pcVar41 = "int32_t*";
    }
    else if (local_1c4 < 5) {
      if (local_1c4 == 1) {
        pcVar41 = "int8_t*";
      }
      else {
        pcVar41 = "void*";
        if (local_1c4 == 2) {
          pcVar41 = "int16_t*";
        }
      }
    }
    else {
      pcVar41 = "void*";
      if (local_1c4 == 8) {
        pcVar41 = "int64_t*";
      }
    }
    goto LAB_00167a08;
  }
  if ((bool)((bVar44 ^ 1U) & bVar8)) {
    pcVar41 = "void*";
    if (!bVar12) {
      pcVar41 = "int*";
    }
    goto LAB_00167a08;
  }
  bVar11 = (bool)((bVar10 ^ 1U) & bVar9);
  if (bVar44) {
    if ((!bVar11) && (bVar12)) goto LAB_00167d2c;
  }
  else {
LAB_00167d1c:
    if ((bool)((bVar11 ^ 1U) & bVar12)) {
LAB_00167d2c:
      pcVar41 = "int64_t";
      goto LAB_00167a08;
    }
  }
  pcVar41 = "int";
LAB_00167a08:
  snprintf((char *)((long)puVar29 + 4),0x80,"%s",pcVar41);
  uVar37 = uVar37 + 1;
  __snprintf_chk((long)puVar29 + 0x84,0x40,2,0x40,"arg%u",local_1b0);
  if (uVar37 == uVar15) goto LAB_00167df4;
  uVar28 = *(uint *)(puVar20 + 1);
  uVar42 = *(uint *)((long)puVar20 + 0xc);
  local_1b0 = (undefined4)uVar37;
  uVar30 = (ulong)uVar28;
  if (uVar42 <= uVar28) goto LAB_00166e48;
LAB_00167a64:
  pvVar21 = (void *)*puVar20;
  goto LAB_00166e88;
}

