
undefined8 * eh_frame_parse(long param_1)

{
  byte *pbVar1;
  char *pcVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  long lVar10;
  void *pvVar11;
  void *pvVar12;
  long *plVar13;
  long lVar14;
  undefined8 uVar15;
  undefined1 uVar16;
  size_t sVar17;
  ulong uVar18;
  long lVar19;
  uint uVar20;
  char cVar21;
  undefined8 uVar22;
  ulong uVar23;
  undefined4 uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  long *plVar28;
  long *extraout_x11;
  long extraout_x11_00;
  long extraout_x11_01;
  long extraout_x11_02;
  ulong *puVar29;
  ulong *extraout_x11_03;
  undefined8 extraout_x12;
  undefined8 extraout_x12_00;
  ulong extraout_x12_01;
  uint extraout_w13;
  ulong extraout_x13;
  undefined8 *puVar30;
  ulong uVar31;
  undefined8 *puVar32;
  ulong uVar33;
  undefined8 *puVar34;
  ulong uVar35;
  long lVar36;
  ulong uVar37;
  ulong uVar38;
  long *__ptr;
  ulong uVar39;
  uint uVar40;
  ulong unaff_x26;
  uint uVar41;
  ulong uVar42;
  void *local_d8;
  ulong local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != 0) {
    puVar30 = *(undefined8 **)(param_1 + 0x18);
    if (*(uint *)(param_1 + 0x20) != 0) {
      puVar34 = puVar30 + (ulong)*(uint *)(param_1 + 0x20) * 7;
      puVar32 = puVar30;
      do {
        if (((char *)*puVar32 != (char *)0x0) &&
           (iVar9 = strcmp((char *)*puVar32,".eh_frame"), iVar9 == 0)) {
          lVar36 = puVar32[5];
          if (lVar36 != 0) goto LAB_00186008;
          break;
        }
        puVar32 = puVar32 + 7;
      } while (puVar34 != puVar32);
    }
  }
  goto LAB_00185fb4;
  while (puVar30 = puVar30 + 7, puVar34 != puVar30) {
LAB_00186008:
    if (((char *)*puVar30 != (char *)0x0) &&
       (iVar9 = strcmp((char *)*puVar30,".gcc_except_table"), iVar9 == 0)) goto LAB_00186030;
  }
  puVar30 = (undefined8 *)0x0;
LAB_00186030:
  puVar34 = calloc(1,0x30);
  if (puVar34 != (undefined8 *)0x0) {
    uVar31 = puVar32[3];
    local_70 = 0;
    uVar22 = puVar32[1];
    if (uVar31 == 0) {
      local_d8 = (void *)0x0;
      uVar31 = 0;
      uVar40 = 0;
      uVar41 = 0;
      __ptr = (long *)0x0;
      if (puVar30 == (undefined8 *)0x0) goto LAB_001870a0;
LAB_001861e4:
      uVar40 = (uint)uVar31;
      uVar24 = 0;
      pvVar11 = (void *)0x0;
      if (puVar30[5] != 0) {
        if (uVar40 == 0) {
          pvVar11 = (void *)0x0;
        }
        else {
          plVar13 = (long *)((long)local_d8 + 0x10);
          uVar42 = 0;
          plVar28 = plVar13 + uVar31 * 5;
          pvVar11 = (void *)0x0;
          uVar27 = 0;
          do {
            uVar31 = plVar13[2];
            if (((uVar31 != 0) && (uVar23 = puVar30[1], uVar23 <= uVar31)) &&
               (uVar33 = puVar30[3], uVar31 < uVar23 + uVar33)) {
              uVar31 = uVar31 - uVar23;
              lVar36 = *plVar13;
              lVar10 = puVar30[5];
              if (uVar31 < uVar33) {
                local_70 = uVar31 + 1;
                lVar14 = lVar36;
                uVar23 = local_70;
                if (*(char *)(lVar10 + uVar31) != -1) {
                  lVar14 = read_encoded_ptr_constprop_0(lVar10,uVar33,&local_70);
                  plVar28 = extraout_x11;
                  uVar23 = local_70;
                }
                local_70 = uVar23;
                if (uVar23 < uVar33) {
                  local_70 = uVar23 + 1;
                  if (*(char *)(lVar10 + uVar23) != -1) {
                    if (uVar33 <= local_70) goto LAB_00187778;
                    pcVar2 = (char *)(lVar10 + local_70);
                    local_70 = uVar23 + 2;
                    if (((((*pcVar2 < '\0' && local_70 < uVar33) &&
                          (pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 3,
                          *pcVar2 < '\0' && local_70 < uVar33)) &&
                         ((pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 4,
                          *pcVar2 < '\0' && local_70 < uVar33 &&
                          ((pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 5,
                           *pcVar2 < '\0' && local_70 < uVar33 &&
                           (pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 6,
                           *pcVar2 < '\0' && local_70 < uVar33)))))) &&
                        (pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 7,
                        *pcVar2 < '\0' && local_70 < uVar33)) &&
                       (((pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 8,
                         *pcVar2 < '\0' && local_70 < uVar33 &&
                         (pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 9,
                         *pcVar2 < '\0' && local_70 < uVar33)) &&
                        (pcVar2 = (char *)(lVar10 + local_70), local_70 = uVar23 + 10,
                        *pcVar2 < '\0' && local_70 < uVar33)))) {
                      local_70 = uVar23 + 0xb;
                    }
                  }
                  if (local_70 < uVar33) {
                    uVar31 = local_70 + 1;
                    cVar21 = *(char *)(lVar10 + local_70);
                    uVar23 = uVar31;
                    if (uVar33 <= uVar31) goto LAB_001863f8;
                    uVar23 = local_70 + 2;
                    uVar18 = (ulong)*(byte *)(lVar10 + uVar31) & 0x7f;
                    if ((*(byte *)(lVar10 + uVar31) & 0x80) == 0 || uVar33 <= uVar23) {
LAB_00187760:
                      local_70 = uVar23;
                      uVar31 = local_70 + uVar18;
                      uVar23 = local_70;
                    }
                    else {
                      uVar31 = local_70 + 3;
                      uVar18 = ((ulong)*(byte *)(lVar10 + uVar23) & 0x7f) << 7 | uVar18;
                      if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && uVar31 < uVar33) {
                        uVar23 = local_70 + 4;
                        uVar18 = ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0xe | uVar18;
                        if ((*(byte *)(lVar10 + uVar31) & 0x80) == 0 || uVar33 <= uVar23)
                        goto LAB_00187760;
                        uVar31 = local_70 + 5;
                        uVar18 = ((ulong)*(byte *)(lVar10 + uVar23) & 0x7f) << 0x15 | uVar18;
                        if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && uVar31 < uVar33) {
                          uVar23 = local_70 + 6;
                          uVar18 = ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0x1c | uVar18;
                          if ((*(byte *)(lVar10 + uVar31) & 0x80) == 0 || uVar33 <= uVar23)
                          goto LAB_00187760;
                          uVar39 = local_70 + 7;
                          uVar18 = ((ulong)*(byte *)(lVar10 + uVar23) & 0x7f) << 0x23 | uVar18;
                          uVar31 = uVar39;
                          if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && uVar39 < uVar33) {
                            uVar23 = local_70 + 8;
                            uVar18 = ((ulong)*(byte *)(lVar10 + uVar39) & 0x7f) << 0x2a | uVar18;
                            uVar31 = uVar23;
                            if ((*(byte *)(lVar10 + uVar39) & 0x80) != 0 && uVar23 < uVar33) {
                              uVar39 = local_70 + 9;
                              uVar18 = ((ulong)*(byte *)(lVar10 + uVar23) & 0x7f) << 0x31 | uVar18;
                              uVar31 = uVar39;
                              if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && uVar39 < uVar33) {
                                uVar31 = local_70 + 10;
                                uVar18 = ((ulong)*(byte *)(lVar10 + uVar39) & 0x7f) << 0x38 | uVar18
                                ;
                                if ((*(byte *)(lVar10 + uVar39) & 0x80) != 0 && uVar31 < uVar33) {
                                  uVar18 = uVar18 | (ulong)*(byte *)(lVar10 + uVar31) << 0x3f;
                                  uVar31 = local_70 + 0xb;
                                }
                              }
                            }
                          }
                        }
                      }
                      local_70 = uVar31;
                      uVar31 = uVar18 + local_70;
                      uVar23 = local_70;
                    }
                    goto LAB_001863f8;
                  }
                }
LAB_00187778:
                cVar21 = '\0';
                uVar31 = local_70;
                uVar23 = local_70;
LAB_001863f8:
                local_70 = uVar23;
                uVar23 = local_70;
                uVar18 = uVar33;
                if (uVar31 < uVar33) {
                  uVar18 = uVar31;
                }
                do {
                  uVar25 = (uint)uVar42;
                  if (0xffff < uVar25) {
                    if (uVar23 < uVar18) {
                      if (cVar21 == '\x01') {
                        bVar8 = 0;
                        goto LAB_00187150;
                      }
                      if (cVar21 == '\x03') {
                        do {
                          if (uVar33 < uVar23 + 4) {
                            uVar39 = 0;
                            uVar31 = uVar33;
                          }
                          else {
                            lVar5 = lVar10 + uVar23;
                            uVar39 = (ulong)((uint)*(byte *)(lVar5 + 2) << 0x10 |
                                             (uint)*(byte *)(lVar5 + 1) << 8 |
                                            (uint)*(byte *)(lVar10 + uVar23) |
                                            (uint)*(byte *)(lVar5 + 3) << 0x18);
                            uVar31 = uVar23 + 4;
                          }
                          if (uVar33 < uVar31 + 4) {
                            uVar37 = 0;
                            uVar31 = uVar33;
                          }
                          else {
                            lVar5 = lVar10 + uVar31;
                            uVar37 = (ulong)((uint)*(byte *)(lVar5 + 2) << 0x10 |
                                             (uint)*(byte *)(lVar5 + 1) << 8 |
                                            (uint)*(byte *)(lVar10 + uVar31) |
                                            (uint)*(byte *)(lVar5 + 3) << 0x18);
                            uVar31 = uVar31 + 4;
                          }
                          if (uVar33 < uVar31 + 4) {
                            uVar38 = 0;
                            uVar31 = uVar33;
                          }
                          else {
                            lVar5 = lVar10 + uVar31;
                            uVar38 = (ulong)((uint)*(byte *)(lVar5 + 2) << 0x10 |
                                             (uint)*(byte *)(lVar5 + 1) << 8 |
                                            (uint)*(byte *)(lVar10 + uVar31) |
                                            (uint)*(byte *)(lVar5 + 3) << 0x18);
                            uVar31 = uVar31 + 4;
                          }
                          if (uVar33 < uVar31 + 4) {
                            uVar35 = 0;
                            uVar23 = uVar33;
                          }
                          else {
                            lVar5 = lVar10 + uVar31;
                            uVar35 = (ulong)((uint)*(byte *)(lVar5 + 2) << 0x10 |
                                             (uint)*(byte *)(lVar5 + 1) << 8 |
                                            (uint)*(byte *)(lVar10 + uVar31) |
                                            (uint)*(byte *)(lVar5 + 3) << 0x18);
                            uVar23 = uVar31 + 4;
                          }
                          unaff_x26 = uVar23;
                          bVar8 = 1;
LAB_00186510:
                          if (uVar25 < uVar27) {
                            if (bVar8 != 0) {
                              local_70 = unaff_x26;
                            }
                            goto LAB_00186520;
                          }
                          if (uVar18 <= uVar23) goto LAB_00186234;
                        } while (cVar21 != '\x01');
LAB_00187150:
                        if (uVar23 < uVar33) {
                          unaff_x26 = uVar23 + 1;
                          uVar39 = (ulong)*(byte *)(lVar10 + uVar23) & 0x7f;
                          if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && unaff_x26 < uVar33) {
                            pbVar1 = (byte *)(lVar10 + unaff_x26);
                            unaff_x26 = uVar23 + 2;
                            uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 7;
                            if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                              pbVar1 = (byte *)(lVar10 + unaff_x26);
                              unaff_x26 = uVar23 + 3;
                              uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0xe;
                              if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                pbVar1 = (byte *)(lVar10 + unaff_x26);
                                unaff_x26 = uVar23 + 4;
                                uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x15;
                                if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                  pbVar1 = (byte *)(lVar10 + unaff_x26);
                                  unaff_x26 = uVar23 + 5;
                                  uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x1c;
                                  if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                    pbVar1 = (byte *)(lVar10 + unaff_x26);
                                    unaff_x26 = uVar23 + 6;
                                    uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x23;
                                    if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                      pbVar1 = (byte *)(lVar10 + unaff_x26);
                                      unaff_x26 = uVar23 + 7;
                                      uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x2a;
                                      if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                        pbVar1 = (byte *)(lVar10 + unaff_x26);
                                        unaff_x26 = uVar23 + 8;
                                        uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x31;
                                        if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                          pbVar1 = (byte *)(lVar10 + unaff_x26);
                                          unaff_x26 = uVar23 + 9;
                                          uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x38;
                                          if ((*pbVar1 & 0x80) != 0 && unaff_x26 < uVar33) {
                                            pbVar1 = (byte *)(lVar10 + unaff_x26);
                                            unaff_x26 = uVar23 + 10;
                                            uVar39 = uVar39 | (ulong)*pbVar1 << 0x3f;
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                          if (uVar33 <= unaff_x26) {
                            bVar8 = 1;
                            uVar23 = unaff_x26;
                            goto LAB_00187de4;
                          }
                          uVar23 = unaff_x26 + 1;
                          uVar37 = (ulong)*(byte *)(lVar10 + unaff_x26) & 0x7f;
                          if ((*(byte *)(lVar10 + unaff_x26) & 0x80) != 0 && uVar23 < uVar33) {
                            pbVar1 = (byte *)(lVar10 + uVar23);
                            uVar23 = unaff_x26 + 2;
                            uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 7;
                            if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                              pbVar1 = (byte *)(lVar10 + uVar23);
                              uVar23 = unaff_x26 + 3;
                              uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0xe;
                              if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                pbVar1 = (byte *)(lVar10 + uVar23);
                                uVar23 = unaff_x26 + 4;
                                uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x15;
                                if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                  pbVar1 = (byte *)(lVar10 + uVar23);
                                  uVar23 = unaff_x26 + 5;
                                  uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x1c;
                                  if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                    pbVar1 = (byte *)(lVar10 + uVar23);
                                    uVar23 = unaff_x26 + 6;
                                    uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x23;
                                    if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                      pbVar1 = (byte *)(lVar10 + uVar23);
                                      uVar23 = unaff_x26 + 7;
                                      uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x2a;
                                      if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                        pbVar1 = (byte *)(lVar10 + uVar23);
                                        uVar23 = unaff_x26 + 8;
                                        uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x31;
                                        if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                          pbVar1 = (byte *)(lVar10 + uVar23);
                                          uVar23 = unaff_x26 + 9;
                                          uVar37 = uVar37 | ((ulong)*pbVar1 & 0x7f) << 0x38;
                                          if ((*pbVar1 & 0x80) != 0 && uVar23 < uVar33) {
                                            pbVar1 = (byte *)(lVar10 + uVar23);
                                            uVar23 = unaff_x26 + 10;
                                            uVar37 = uVar37 | (ulong)*pbVar1 << 0x3f;
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                          if (uVar23 < uVar33) {
                            uVar31 = uVar23 + 1;
                            uVar38 = (ulong)*(byte *)(lVar10 + uVar23) & 0x7f;
                            if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && uVar31 < uVar33) {
                              pbVar1 = (byte *)(lVar10 + uVar31);
                              uVar31 = uVar23 + 2;
                              uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 7;
                              if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                pbVar1 = (byte *)(lVar10 + uVar31);
                                uVar31 = uVar23 + 3;
                                uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0xe;
                                if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                  pbVar1 = (byte *)(lVar10 + uVar31);
                                  uVar31 = uVar23 + 4;
                                  uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x15;
                                  if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                    pbVar1 = (byte *)(lVar10 + uVar31);
                                    uVar31 = uVar23 + 5;
                                    uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x1c;
                                    if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                      pbVar1 = (byte *)(lVar10 + uVar31);
                                      uVar31 = uVar23 + 6;
                                      uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x23;
                                      if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                        pbVar1 = (byte *)(lVar10 + uVar31);
                                        uVar31 = uVar23 + 7;
                                        uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x2a;
                                        if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                          pbVar1 = (byte *)(lVar10 + uVar31);
                                          uVar31 = uVar23 + 8;
                                          uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x31;
                                          if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                            pbVar1 = (byte *)(lVar10 + uVar31);
                                            uVar31 = uVar23 + 9;
                                            uVar38 = uVar38 | ((ulong)*pbVar1 & 0x7f) << 0x38;
                                            if ((*pbVar1 & 0x80) != 0 && uVar31 < uVar33) {
                                              pbVar1 = (byte *)(lVar10 + uVar31);
                                              uVar31 = uVar23 + 10;
                                              uVar38 = uVar38 | (ulong)*pbVar1 << 0x3f;
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                            if (uVar31 < uVar33) {
                              unaff_x26 = uVar31 + 1;
                              uVar35 = (ulong)*(byte *)(lVar10 + uVar31) & 0x7f;
                              bVar8 = unaff_x26 < uVar33 & *(byte *)(lVar10 + uVar31) >> 7;
                              if (bVar8 == 0) {
                                uVar23 = unaff_x26;
                                bVar8 = 1;
                              }
                              else {
                                uVar23 = uVar31 + 2;
                                bVar6 = uVar23 < uVar33 & *(byte *)(lVar10 + unaff_x26) >> 7;
                                uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + unaff_x26) & 0x7f) << 7
                                ;
                                unaff_x26 = uVar23;
                                if (bVar6 != 0) {
                                  pbVar1 = (byte *)(lVar10 + uVar23);
                                  uVar23 = uVar31 + 3;
                                  bVar7 = uVar23 < uVar33 & *pbVar1 >> 7;
                                  uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0xe;
                                  unaff_x26 = uVar23;
                                  bVar8 = bVar6;
                                  if (bVar7 != 0) {
                                    pbVar1 = (byte *)(lVar10 + uVar23);
                                    uVar23 = uVar31 + 4;
                                    bVar6 = uVar23 < uVar33 & *pbVar1 >> 7;
                                    uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x15;
                                    unaff_x26 = uVar23;
                                    bVar8 = bVar7;
                                    if (bVar6 != 0) {
                                      pbVar1 = (byte *)(lVar10 + uVar23);
                                      uVar23 = uVar31 + 5;
                                      bVar7 = uVar23 < uVar33 & *pbVar1 >> 7;
                                      uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x1c;
                                      unaff_x26 = uVar23;
                                      bVar8 = bVar6;
                                      if (bVar7 != 0) {
                                        pbVar1 = (byte *)(lVar10 + uVar23);
                                        uVar23 = uVar31 + 6;
                                        bVar6 = uVar23 < uVar33 & *pbVar1 >> 7;
                                        uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x23;
                                        unaff_x26 = uVar23;
                                        bVar8 = bVar7;
                                        if (bVar6 != 0) {
                                          pbVar1 = (byte *)(lVar10 + uVar23);
                                          uVar23 = uVar31 + 7;
                                          bVar7 = uVar23 < uVar33 & *pbVar1 >> 7;
                                          uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x2a;
                                          unaff_x26 = uVar23;
                                          bVar8 = bVar6;
                                          if (bVar7 != 0) {
                                            pbVar1 = (byte *)(lVar10 + uVar23);
                                            uVar23 = uVar31 + 8;
                                            bVar6 = uVar23 < uVar33 & *pbVar1 >> 7;
                                            uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x31;
                                            unaff_x26 = uVar23;
                                            bVar8 = bVar7;
                                            if (bVar6 != 0) {
                                              pbVar1 = (byte *)(lVar10 + uVar23);
                                              uVar23 = uVar31 + 9;
                                              bVar7 = uVar23 < uVar33 & *pbVar1 >> 7;
                                              uVar35 = uVar35 | ((ulong)*pbVar1 & 0x7f) << 0x38;
                                              unaff_x26 = uVar23;
                                              bVar8 = bVar6;
                                              if (bVar7 != 0) {
                                                uVar35 = uVar35 | (ulong)*(byte *)(lVar10 + uVar23)
                                                                  << 0x3f;
                                                uVar23 = uVar31 + 10;
                                                unaff_x26 = uVar31 + 10;
                                                bVar8 = bVar7;
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
                            else {
                              uVar35 = 0;
                              uVar23 = uVar31;
                              unaff_x26 = uVar31;
                              bVar8 = 1;
                            }
                            goto LAB_00186510;
                          }
                          bVar8 = 1;
                          unaff_x26 = uVar23;
                        }
                        else {
                          uVar39 = 0;
LAB_00187de4:
                          uVar37 = 0;
                        }
                        uVar35 = 0;
                        uVar38 = 0;
                        goto LAB_00186510;
                      }
                    }
                    break;
                  }
                  if (uVar18 <= uVar23) break;
                  if (cVar21 == '\x01') goto LAB_001866b0;
                  if (cVar21 != '\x03') break;
LAB_00186574:
                  if (uVar33 < uVar23 + 4) {
                    uVar39 = 0;
                    uVar31 = uVar33;
                  }
                  else {
                    lVar5 = lVar10 + uVar23;
                    uVar39 = (ulong)((uint)*(byte *)(lVar5 + 1) << 8 |
                                     (uint)*(byte *)(lVar5 + 2) << 0x10 |
                                    (uint)*(byte *)(lVar10 + uVar23) |
                                    (uint)*(byte *)(lVar5 + 3) << 0x18);
                    uVar31 = uVar23 + 4;
                  }
                  if (uVar33 < uVar31 + 4) {
                    uVar37 = 0;
                    uVar31 = uVar33;
                  }
                  else {
                    lVar5 = lVar10 + uVar31;
                    uVar37 = (ulong)((uint)*(byte *)(lVar5 + 1) << 8 |
                                     (uint)*(byte *)(lVar5 + 2) << 0x10 |
                                    (uint)*(byte *)(lVar10 + uVar31) |
                                    (uint)*(byte *)(lVar5 + 3) << 0x18);
                    uVar31 = uVar31 + 4;
                  }
                  if (uVar33 < uVar31 + 4) {
                    uVar38 = 0;
                    uVar31 = uVar33;
                  }
                  else {
                    lVar5 = lVar10 + uVar31;
                    uVar38 = (ulong)((uint)*(byte *)(lVar5 + 1) << 8 |
                                     (uint)*(byte *)(lVar5 + 2) << 0x10 |
                                    (uint)*(byte *)(lVar10 + uVar31) |
                                    (uint)*(byte *)(lVar5 + 3) << 0x18);
                    uVar31 = uVar31 + 4;
                  }
                  uVar23 = uVar31 + 4;
                  if (uVar33 < uVar23) {
                    uVar35 = 0;
                    uVar23 = uVar33;
                    uVar31 = uVar33;
                  }
                  else {
                    lVar5 = lVar10 + uVar31;
                    uVar35 = (ulong)((uint)*(byte *)(lVar5 + 1) << 8 |
                                     (uint)*(byte *)(lVar5 + 2) << 0x10 |
                                    (uint)*(byte *)(lVar10 + uVar31) |
                                    (uint)*(byte *)(lVar5 + 3) << 0x18);
                    uVar31 = uVar23;
                  }
LAB_00186638:
                  local_70 = uVar31;
                  if (uVar27 <= uVar25) {
                    if (uVar27 != 0) goto LAB_00186b90;
LAB_00186644:
                    sVar17 = 0x500;
                    uVar26 = 0x20;
                    do {
                      pvVar12 = realloc(pvVar11,sVar17);
                      if ((pvVar12 != (void *)0x0) &&
                         (pvVar11 = pvVar12, uVar27 = uVar26, uVar25 < uVar26)) break;
                      if (uVar18 <= uVar23) goto LAB_00186234;
                      if (cVar21 != '\x01') goto LAB_00186574;
LAB_001866b0:
                      uVar39 = 0;
                      if (uVar33 <= uVar23) {
LAB_00187df8:
                        uVar37 = 0;
LAB_00187dfc:
                        uVar35 = 0;
                        uVar38 = 0;
                        uVar31 = local_70;
                        goto LAB_00186638;
                      }
                      local_70 = uVar23 + 1;
                      uVar39 = (ulong)*(byte *)(lVar10 + uVar23) & 0x7f;
                      if ((*(byte *)(lVar10 + uVar23) & 0x80) != 0 && local_70 < uVar33) {
                        pbVar1 = (byte *)(lVar10 + local_70);
                        local_70 = uVar23 + 2;
                        uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 7;
                        if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                          pbVar1 = (byte *)(lVar10 + local_70);
                          local_70 = uVar23 + 3;
                          uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0xe;
                          if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                            pbVar1 = (byte *)(lVar10 + local_70);
                            local_70 = uVar23 + 4;
                            uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x15;
                            if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                              pbVar1 = (byte *)(lVar10 + local_70);
                              local_70 = uVar23 + 5;
                              uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x1c;
                              if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                                pbVar1 = (byte *)(lVar10 + local_70);
                                local_70 = uVar23 + 6;
                                uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x23;
                                if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                                  pbVar1 = (byte *)(lVar10 + local_70);
                                  local_70 = uVar23 + 7;
                                  uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x2a;
                                  if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                                    pbVar1 = (byte *)(lVar10 + local_70);
                                    local_70 = uVar23 + 8;
                                    uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x31;
                                    if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                                      pbVar1 = (byte *)(lVar10 + local_70);
                                      local_70 = uVar23 + 9;
                                      uVar39 = uVar39 | ((ulong)*pbVar1 & 0x7f) << 0x38;
                                      if ((*pbVar1 & 0x80) != 0 && local_70 < uVar33) {
                                        pbVar1 = (byte *)(lVar10 + local_70);
                                        local_70 = uVar23 + 10;
                                        uVar39 = uVar39 | (ulong)*pbVar1 << 0x3f;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                      uVar23 = local_70;
                      if (uVar33 <= local_70) goto LAB_00187df8;
                      uVar31 = local_70 + 1;
                      uVar37 = (ulong)*(byte *)(lVar10 + local_70) & 0x7f;
                      uVar23 = uVar31;
                      if ((*(byte *)(lVar10 + local_70) & 0x80) != 0 && uVar31 < uVar33) {
                        uVar38 = local_70 + 2;
                        uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 7;
                        uVar23 = uVar38;
                        if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar38 < uVar33) {
                          uVar31 = local_70 + 3;
                          uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar38) & 0x7f) << 0xe;
                          uVar23 = uVar31;
                          if ((*(byte *)(lVar10 + uVar38) & 0x80) != 0 && uVar31 < uVar33) {
                            uVar38 = local_70 + 4;
                            uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0x15;
                            uVar23 = uVar38;
                            if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar38 < uVar33) {
                              uVar31 = local_70 + 5;
                              uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar38) & 0x7f) << 0x1c;
                              uVar23 = uVar31;
                              if ((*(byte *)(lVar10 + uVar38) & 0x80) != 0 && uVar31 < uVar33) {
                                uVar38 = local_70 + 6;
                                uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0x23
                                ;
                                uVar23 = uVar38;
                                if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar38 < uVar33) {
                                  uVar31 = local_70 + 7;
                                  uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar38) & 0x7f) <<
                                                    0x2a;
                                  uVar23 = uVar31;
                                  if ((*(byte *)(lVar10 + uVar38) & 0x80) != 0 && uVar31 < uVar33) {
                                    uVar38 = local_70 + 8;
                                    uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) <<
                                                      0x31;
                                    uVar23 = uVar38;
                                    if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar38 < uVar33)
                                    {
                                      uVar23 = local_70 + 9;
                                      uVar37 = uVar37 | ((ulong)*(byte *)(lVar10 + uVar38) & 0x7f)
                                                        << 0x38;
                                      if ((*(byte *)(lVar10 + uVar38) & 0x80) != 0 &&
                                          uVar23 < uVar33) {
                                        uVar37 = uVar37 | (ulong)*(byte *)(lVar10 + uVar23) << 0x3f;
                                        uVar23 = local_70 + 10;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                      local_70 = uVar23;
                      uVar23 = local_70;
                      if (uVar33 <= local_70) goto LAB_00187dfc;
                      uVar31 = local_70 + 1;
                      uVar38 = (ulong)*(byte *)(lVar10 + local_70) & 0x7f;
                      uVar23 = uVar31;
                      if ((*(byte *)(lVar10 + local_70) & 0x80) != 0 && uVar31 < uVar33) {
                        uVar35 = local_70 + 2;
                        uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 7;
                        uVar23 = uVar35;
                        if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar35 < uVar33) {
                          uVar31 = local_70 + 3;
                          uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar35) & 0x7f) << 0xe;
                          uVar23 = uVar31;
                          if ((*(byte *)(lVar10 + uVar35) & 0x80) != 0 && uVar31 < uVar33) {
                            uVar35 = local_70 + 4;
                            uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0x15;
                            uVar23 = uVar35;
                            if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar35 < uVar33) {
                              uVar31 = local_70 + 5;
                              uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar35) & 0x7f) << 0x1c;
                              uVar23 = uVar31;
                              if ((*(byte *)(lVar10 + uVar35) & 0x80) != 0 && uVar31 < uVar33) {
                                uVar35 = local_70 + 6;
                                uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) << 0x23
                                ;
                                uVar23 = uVar35;
                                if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar35 < uVar33) {
                                  uVar31 = local_70 + 7;
                                  uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar35) & 0x7f) <<
                                                    0x2a;
                                  uVar23 = uVar31;
                                  if ((*(byte *)(lVar10 + uVar35) & 0x80) != 0 && uVar31 < uVar33) {
                                    uVar35 = local_70 + 8;
                                    uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar31) & 0x7f) <<
                                                      0x31;
                                    uVar23 = uVar35;
                                    if ((*(byte *)(lVar10 + uVar31) & 0x80) != 0 && uVar35 < uVar33)
                                    {
                                      uVar23 = local_70 + 9;
                                      uVar38 = uVar38 | ((ulong)*(byte *)(lVar10 + uVar35) & 0x7f)
                                                        << 0x38;
                                      if ((*(byte *)(lVar10 + uVar35) & 0x80) != 0 &&
                                          uVar23 < uVar33) {
                                        uVar38 = uVar38 | (ulong)*(byte *)(lVar10 + uVar23) << 0x3f;
                                        uVar23 = local_70 + 10;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                      local_70 = uVar23;
                      if (uVar33 <= local_70) {
                        uVar35 = 0;
                        uVar23 = local_70;
                        uVar31 = local_70;
                        goto LAB_00186638;
                      }
                      uVar3 = local_70 + 1;
                      uVar35 = (ulong)*(byte *)(lVar10 + local_70) & 0x7f;
                      uVar23 = uVar3;
                      uVar31 = uVar3;
                      if ((*(byte *)(lVar10 + local_70) & 0x80) == 0 || uVar33 <= uVar3)
                      goto LAB_00186638;
                      uVar4 = local_70 + 2;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar3) & 0x7f) << 7;
                      uVar23 = uVar4;
                      uVar31 = uVar4;
                      if ((*(byte *)(lVar10 + uVar3) & 0x80) == 0 || uVar33 <= uVar4)
                      goto LAB_00186638;
                      uVar3 = local_70 + 3;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar4) & 0x7f) << 0xe;
                      uVar23 = uVar3;
                      uVar31 = uVar3;
                      if ((*(byte *)(lVar10 + uVar4) & 0x80) == 0 || uVar33 <= uVar3)
                      goto LAB_00186638;
                      uVar4 = local_70 + 4;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar3) & 0x7f) << 0x15;
                      uVar23 = uVar4;
                      uVar31 = uVar4;
                      if ((*(byte *)(lVar10 + uVar3) & 0x80) == 0 || uVar33 <= uVar4)
                      goto LAB_00186638;
                      uVar3 = local_70 + 5;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar4) & 0x7f) << 0x1c;
                      uVar23 = uVar3;
                      uVar31 = uVar3;
                      if ((*(byte *)(lVar10 + uVar4) & 0x80) == 0 || uVar33 <= uVar3)
                      goto LAB_00186638;
                      uVar4 = local_70 + 6;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar3) & 0x7f) << 0x23;
                      uVar23 = uVar4;
                      uVar31 = uVar4;
                      if ((*(byte *)(lVar10 + uVar3) & 0x80) == 0 || uVar33 <= uVar4)
                      goto LAB_00186638;
                      uVar3 = local_70 + 7;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar4) & 0x7f) << 0x2a;
                      uVar23 = uVar3;
                      uVar31 = uVar3;
                      if ((*(byte *)(lVar10 + uVar4) & 0x80) == 0 || uVar33 <= uVar3)
                      goto LAB_00186638;
                      uVar4 = local_70 + 8;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar3) & 0x7f) << 0x31;
                      uVar23 = uVar4;
                      uVar31 = uVar4;
                      if ((*(byte *)(lVar10 + uVar3) & 0x80) == 0 || uVar33 <= uVar4)
                      goto LAB_00186638;
                      uVar31 = local_70 + 9;
                      uVar35 = uVar35 | ((ulong)*(byte *)(lVar10 + uVar4) & 0x7f) << 0x38;
                      uVar23 = uVar31;
                      if ((*(byte *)(lVar10 + uVar4) & 0x80) == 0 || uVar33 <= uVar31)
                      goto LAB_00186638;
                      uVar23 = local_70 + 10;
                      uVar35 = uVar35 | (ulong)*(byte *)(lVar10 + uVar31) << 0x3f;
                      local_70 = uVar23;
                      if (uVar25 < uVar27) break;
                      if (uVar27 == 0) goto LAB_00186644;
LAB_00186b90:
                      uVar26 = uVar27 << 1;
                      if (0x10000 < uVar26) {
                        uVar26 = 0x10000;
                      }
                      sVar17 = (ulong)uVar26 * 0x28;
                    } while( true );
                  }
LAB_00186520:
                  lVar19 = uVar42 * 0x28;
                  lVar5 = uVar38 + lVar14;
                  if (uVar38 == 0) {
                    lVar5 = 0;
                  }
                  uVar42 = (ulong)(uVar25 + 1);
                  *(ulong *)((long)pvVar11 + lVar19) = lVar36 + uVar39;
                  *(ulong *)((long)pvVar11 + lVar19 + 8) = uVar37;
                  *(long *)((long)pvVar11 + lVar19 + 0x10) = lVar5;
                  *(uint *)((long)pvVar11 + lVar19 + 0x18) = (uint)(uVar35 != 0);
                  *(ulong *)((long)pvVar11 + lVar19 + 0x20) = uVar35;
                } while( true );
              }
            }
LAB_00186234:
            uVar24 = (undefined4)uVar42;
            plVar13 = plVar13 + 5;
          } while (plVar28 != plVar13);
        }
      }
    }
    else {
      uVar40 = 0;
      __ptr = (long *)0x0;
      uVar25 = 0;
      uVar41 = 0;
      local_d8 = (void *)0x0;
      uVar27 = 0;
      uVar42 = 0;
      do {
        uVar33 = uVar42 + 4;
        uVar23 = uVar31;
        if (uVar31 < uVar33) {
LAB_00186bb4:
          local_70 = uVar23;
          if (uVar31 < uVar23 + 8) break;
        }
        else {
          lVar10 = lVar36 + uVar42;
          uVar26 = (uint)*(byte *)(lVar10 + 2) << 0x10 | (uint)*(byte *)(lVar10 + 1) << 8 |
                   (uint)*(byte *)(lVar36 + uVar42) | (uint)*(byte *)(lVar10 + 3) << 0x18;
          uVar23 = uVar33;
          if (uVar26 == 0) goto LAB_00186bb4;
          if (uVar26 == 0xffffffff) {
            local_70 = uVar42 + 0xc;
            uVar18 = uVar31;
            uVar23 = uVar31;
            if (uVar31 < local_70) {
LAB_00187024:
              uVar33 = uVar18 + 8;
              local_70 = uVar31;
              if (uVar31 < uVar33) goto LAB_00186bf0;
              if (uVar31 < uVar18 + 4) goto LAB_00187740;
              lVar10 = lVar36 + uVar18;
              uVar26 = (uint)*(byte *)(lVar10 + 2) << 0x10 | (uint)*(byte *)(lVar10 + 1) << 8 |
                       (uint)*(byte *)(lVar36 + uVar18) | (uint)*(byte *)(lVar10 + 3) << 0x18;
            }
            else {
              if (uVar42 + 8 <= uVar31) {
                uVar33 = (ulong)((uint)*(byte *)(lVar10 + 6) << 0x10 |
                                 (uint)*(byte *)(lVar10 + 5) << 8 |
                                (uint)*(byte *)(lVar36 + uVar33) |
                                (uint)*(byte *)(lVar10 + 7) << 0x18);
                uVar23 = uVar42 + 8;
LAB_00187104:
                lVar10 = lVar36 + uVar23;
                uVar23 = local_70 +
                         (uVar33 | (ulong)((uint)*(byte *)(lVar10 + 2) << 0x10 |
                                           (uint)*(byte *)(lVar10 + 1) << 8 |
                                          (uint)*(byte *)(lVar36 + uVar23) |
                                          (uint)*(byte *)(lVar10 + 3) << 0x18) << 0x20);
                uVar18 = local_70;
                if (uVar23 <= uVar31) goto LAB_00187024;
                break;
              }
              local_70 = uVar31 + 4;
              if (local_70 <= uVar31) {
                uVar33 = 0;
                goto LAB_00187104;
              }
              local_70 = uVar31;
              if (uVar31 < 0xfffffffffffffff8) goto LAB_00186bf0;
LAB_00187740:
              uVar33 = uVar31 + 4;
              local_70 = uVar31;
              if (uVar31 < uVar33) goto LAB_00186bf0;
              uVar26 = 0;
            }
            local_70 = uVar33;
            if (uVar26 == 0) goto LAB_00186bf0;
            lVar10 = uVar18 - uVar26;
LAB_0018611c:
            if (uVar41 != 0) {
              uVar26 = 0;
              plVar13 = __ptr;
              do {
                if (*plVar13 == lVar10) {
                  pvVar11 = local_d8;
                  uVar20 = uVar27;
                  if (uVar40 < 0x80000) {
                    if (uVar27 <= uVar40) {
                      if (uVar27 == 0) {
                        sVar17 = 0x500;
                        uVar20 = 0x20;
                      }
                      else {
                        uVar20 = uVar27 << 1;
                        if (0x80000 < uVar20) {
                          uVar20 = 0x80000;
                        }
                        sVar17 = (ulong)uVar20 * 0x28;
                      }
                      pvVar11 = realloc(local_d8,sVar17);
                      if (pvVar11 != (void *)0x0) goto LAB_001861b0;
                      break;
                    }
                  }
                  else {
LAB_001861b0:
                    local_d8 = pvVar11;
                    uVar27 = uVar20;
                    if (uVar20 <= uVar40) break;
                  }
                  uVar16 = *(undefined1 *)((long)plVar13 + 0x21);
                  lVar10 = (ulong)uVar40 * 0x28;
                  *(undefined8 *)((long)local_d8 + lVar10 + 0xc) = 0;
                  *(undefined8 *)((long)local_d8 + lVar10 + 0x14) = 0;
                  *(undefined8 *)((long)local_d8 + lVar10 + 0x1c) = 0;
                  *(undefined4 *)((long)local_d8 + lVar10 + 0x24) = 0;
                  *(ulong *)((long)local_d8 + lVar10) = uVar42;
                  *(uint *)((long)local_d8 + lVar10 + 8) = uVar26;
                  uVar15 = read_encoded_ptr_constprop_0(lVar36,uVar31,&local_70,uVar16,uVar22);
                  *(undefined8 *)(extraout_x11_00 + 0x10) = uVar15;
                  uVar15 = read_encoded_ptr_constprop_0
                                     (lVar36,uVar31,extraout_x12,extraout_w13 & 0xf,0);
                  cVar21 = *(char *)((long)plVar13 + 0x23);
                  *(undefined8 *)(extraout_x11_01 + 0x18) = uVar15;
                  if ((cVar21 != '\0') && (local_70 < uVar31)) {
                    uVar42 = local_70 + 1;
                    uVar18 = (ulong)*(byte *)(lVar36 + local_70) & 0x7f;
                    uVar33 = uVar42;
                    if ((*(byte *)(lVar36 + local_70) & 0x80) != 0 && uVar42 < uVar31) {
                      uVar39 = local_70 + 2;
                      uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar42) & 0x7f) << 7;
                      uVar33 = uVar39;
                      if ((*(byte *)(lVar36 + uVar42) & 0x80) != 0 && uVar39 < uVar31) {
                        uVar42 = local_70 + 3;
                        uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar39) & 0x7f) << 0xe;
                        uVar33 = uVar42;
                        if ((*(byte *)(lVar36 + uVar39) & 0x80) != 0 && uVar42 < uVar31) {
                          uVar39 = local_70 + 4;
                          uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar42) & 0x7f) << 0x15;
                          uVar33 = uVar39;
                          if ((*(byte *)(lVar36 + uVar42) & 0x80) != 0 && uVar39 < uVar31) {
                            uVar42 = local_70 + 5;
                            uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar39) & 0x7f) << 0x1c;
                            uVar33 = uVar42;
                            if ((*(byte *)(lVar36 + uVar39) & 0x80) != 0 && uVar42 < uVar31) {
                              uVar39 = local_70 + 6;
                              uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar42) & 0x7f) << 0x23;
                              uVar33 = uVar39;
                              if ((*(byte *)(lVar36 + uVar42) & 0x80) != 0 && uVar39 < uVar31) {
                                uVar42 = local_70 + 7;
                                uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar39) & 0x7f) << 0x2a
                                ;
                                uVar33 = uVar42;
                                if ((*(byte *)(lVar36 + uVar39) & 0x80) != 0 && uVar42 < uVar31) {
                                  uVar39 = local_70 + 8;
                                  uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar42) & 0x7f) <<
                                                    0x31;
                                  uVar33 = uVar39;
                                  if ((*(byte *)(lVar36 + uVar42) & 0x80) != 0 && uVar39 < uVar31) {
                                    uVar33 = local_70 + 9;
                                    uVar18 = uVar18 | ((ulong)*(byte *)(lVar36 + uVar39) & 0x7f) <<
                                                      0x38;
                                    if ((*(byte *)(lVar36 + uVar39) & 0x80) != 0 && uVar33 < uVar31)
                                    {
                                      uVar18 = uVar18 | (ulong)*(byte *)(lVar36 + uVar33) << 0x3f;
                                      uVar33 = local_70 + 10;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                    local_70 = uVar33;
                    if (*(char *)((long)plVar13 + 0x22) != -1 && uVar18 != 0) {
                      uVar15 = read_encoded_ptr_constprop_0
                                         (lVar36,uVar31,extraout_x12_00,
                                          *(char *)((long)plVar13 + 0x22),uVar22);
                      *(undefined8 *)(extraout_x11_02 + 0x20) = uVar15;
                    }
                  }
                  uVar40 = uVar40 + 1;
                  uVar27 = uVar20;
                  break;
                }
                uVar26 = uVar26 + 1;
                plVar13 = plVar13 + 9;
              } while (uVar41 != uVar26);
            }
          }
          else {
            uVar23 = uVar33 + uVar26;
            local_70 = uVar33;
            if (uVar31 < uVar23) break;
            uVar18 = uVar42 + 8;
            local_70 = uVar31;
            if ((uVar18 <= uVar31) &&
               (uVar26 = (uint)*(byte *)(lVar10 + 6) << 0x10 | (uint)*(byte *)(lVar10 + 5) << 8 |
                         (uint)*(byte *)(lVar36 + uVar33) | (uint)*(byte *)(lVar10 + 7) << 0x18,
               local_70 = uVar18, uVar26 != 0)) {
              lVar10 = uVar33 - uVar26;
              goto LAB_0018611c;
            }
LAB_00186bf0:
            uVar33 = local_70;
            plVar13 = __ptr;
            uVar26 = uVar25;
            if (uVar41 < 0x10000) {
              if (uVar41 < uVar25) goto LAB_00186c00;
              if (uVar25 == 0) {
                sVar17 = 0x900;
                uVar26 = 0x20;
              }
              else {
                uVar26 = uVar25 << 1;
                if (0x10000 < uVar26) {
                  uVar26 = 0x10000;
                }
                sVar17 = (ulong)uVar26 * 0x48;
              }
              plVar13 = realloc(__ptr,sVar17);
              if (plVar13 != (long *)0x0) goto LAB_00187000;
            }
            else {
LAB_00187000:
              __ptr = plVar13;
              uVar25 = uVar26;
              if (uVar41 < uVar26) {
LAB_00186c00:
                bVar8 = 0;
                uVar18 = (ulong)uVar41;
                lVar10 = uVar18 * 0x48;
                plVar13[uVar18 * 9 + 2] = 0;
                plVar13[uVar18 * 9 + 1] = 0;
                plVar13[uVar18 * 9 + 4] = 0;
                plVar13[uVar18 * 9 + 3] = 0;
                plVar13[uVar18 * 9 + 6] = 0;
                plVar13[uVar18 * 9 + 5] = 0;
                plVar13[uVar18 * 9 + 8] = 0;
                plVar13[uVar18 * 9 + 7] = 0;
                plVar13[uVar18 * 9] = uVar42;
                if (uVar33 < uVar31) {
                  bVar8 = *(byte *)(lVar36 + uVar33);
                  uVar33 = uVar33 + 1;
                }
                *(byte *)(plVar13 + uVar18 * 9 + 1) = bVar8;
                uVar42 = 0;
                uVar39 = uVar33;
                if (uVar33 < uVar23) {
                  do {
                    uVar37 = uVar39 + 1;
                    if (*(char *)(lVar36 + uVar39) == '\0') {
                      uVar37 = uVar39;
                      uVar39 = uVar42;
                      if (0x1f < uVar42) {
                        uVar39 = 0x1f;
                      }
                      goto LAB_00186c78;
                    }
                    uVar42 = uVar42 + 1;
                    uVar39 = uVar37;
                  } while (uVar42 != uVar23 - uVar33);
                  uVar39 = uVar42;
                  if (0x1f < uVar42) {
                    uVar39 = 0x1f;
                  }
                }
                else {
                  uVar37 = uVar33;
                  uVar39 = 0;
                }
LAB_00186c78:
                uVar38 = uVar37 + 1;
                local_70 = uVar38;
                pvVar11 = memcpy((void *)((long)plVar13 + lVar10 + 0x24),(void *)(lVar36 + uVar33),
                                 uVar39);
                *(undefined1 *)((long)plVar13 + uVar39 + lVar10 + 0x24) = 0;
                if (uVar38 < uVar31) {
                  local_70 = uVar37 + 2;
                  uVar33 = (ulong)*(byte *)(lVar36 + uVar38) & 0x7f;
                  if ((*(byte *)(lVar36 + uVar38) & 0x80) != 0 && local_70 < uVar31) {
                    pbVar1 = (byte *)(lVar36 + local_70);
                    local_70 = uVar37 + 3;
                    uVar33 = ((ulong)*pbVar1 & 0x7f) << 7 | uVar33;
                    if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                      pbVar1 = (byte *)(lVar36 + local_70);
                      local_70 = uVar37 + 4;
                      uVar33 = ((ulong)*pbVar1 & 0x7f) << 0xe | uVar33;
                      if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                        pbVar1 = (byte *)(lVar36 + local_70);
                        local_70 = uVar37 + 5;
                        uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x15 | uVar33;
                        if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                          pbVar1 = (byte *)(lVar36 + local_70);
                          local_70 = uVar37 + 6;
                          uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x1c | uVar33;
                          if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                            pbVar1 = (byte *)(lVar36 + local_70);
                            local_70 = uVar37 + 7;
                            uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x23 | uVar33;
                            if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                              pbVar1 = (byte *)(lVar36 + local_70);
                              local_70 = uVar37 + 8;
                              uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x2a | uVar33;
                              if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                                pbVar1 = (byte *)(lVar36 + local_70);
                                local_70 = uVar37 + 9;
                                uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x31 | uVar33;
                                if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                                  pbVar1 = (byte *)(lVar36 + local_70);
                                  local_70 = uVar37 + 10;
                                  uVar33 = ((ulong)*pbVar1 & 0x7f) << 0x38 | uVar33;
                                  if ((*pbVar1 & 0x80) != 0 && local_70 < uVar31) {
                                    pbVar1 = (byte *)(lVar36 + local_70);
                                    local_70 = uVar37 + 0xb;
                                    uVar33 = uVar33 | (ulong)*pbVar1 << 0x3f;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  plVar13[uVar18 * 9 + 2] = uVar33;
                  if (uVar31 <= local_70) goto LAB_00187af0;
                  uVar37 = (ulong)*(byte *)(lVar36 + local_70);
                  uVar33 = local_70 + 1;
                  uVar38 = uVar37 & 0x7f;
                  if ((*(byte *)(lVar36 + local_70) & 0x80) == 0 || uVar31 <= uVar33) {
                    uVar35 = 0xffffffffffffff80;
                    local_70 = uVar33;
LAB_00187d74:
                    uVar33 = uVar38 | uVar35;
                    if ((uVar37 & 0x40) == 0) {
                      uVar33 = uVar38;
                    }
                  }
                  else {
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar33);
                    uVar3 = local_70 + 2;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 7;
                    if ((*(byte *)(lVar36 + uVar33) & 0x80) == 0 || uVar31 <= uVar3) {
                      uVar35 = 0xffffffffffffc000;
                      local_70 = uVar3;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar3);
                    uVar33 = local_70 + 3;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0xe;
                    if ((*(byte *)(lVar36 + uVar3) & 0x80) == 0 || uVar31 <= uVar33) {
                      uVar35 = 0xffffffffffe00000;
                      local_70 = uVar33;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar33);
                    uVar3 = local_70 + 4;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x15;
                    if ((*(byte *)(lVar36 + uVar33) & 0x80) == 0 || uVar31 <= uVar3) {
                      uVar35 = 0xfffffffff0000000;
                      local_70 = uVar3;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar3);
                    uVar33 = local_70 + 5;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x1c;
                    if ((*(byte *)(lVar36 + uVar3) & 0x80) == 0 || uVar31 <= uVar33) {
                      uVar35 = 0xfffffff800000000;
                      local_70 = uVar33;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar33);
                    uVar3 = local_70 + 6;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x23;
                    if ((*(byte *)(lVar36 + uVar33) & 0x80) == 0 || uVar31 <= uVar3) {
                      uVar35 = 0xfffffc0000000000;
                      local_70 = uVar3;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar3);
                    uVar33 = local_70 + 7;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x2a;
                    if ((*(byte *)(lVar36 + uVar3) & 0x80) == 0 || uVar31 <= uVar33) {
                      uVar35 = 0xfffe000000000000;
                      local_70 = uVar33;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar33);
                    uVar3 = local_70 + 8;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x31;
                    if ((*(byte *)(lVar36 + uVar33) & 0x80) == 0 || uVar31 <= uVar3) {
                      uVar35 = 0xff00000000000000;
                      local_70 = uVar3;
                      goto LAB_00187d74;
                    }
                    uVar37 = (ulong)*(byte *)(lVar36 + uVar3);
                    uVar33 = local_70 + 9;
                    uVar38 = uVar38 | (uVar37 & 0x7f) << 0x38;
                    if ((*(byte *)(lVar36 + uVar3) & 0x80) == 0 || uVar31 <= uVar33) {
                      uVar35 = 0x8000000000000000;
                      local_70 = uVar33;
                      goto LAB_00187d74;
                    }
                    local_70 = local_70 + 10;
                    uVar33 = uVar38 | (ulong)*(byte *)(lVar36 + uVar33) << 0x3f;
                  }
                  plVar13[uVar18 * 9 + 3] = uVar33;
                  if (bVar8 < 3) {
                    if (local_70 < uVar31) {
                      bVar8 = *(byte *)(lVar36 + local_70);
                      uVar37 = local_70 + 1;
                      goto LAB_00186f4c;
                    }
                    goto LAB_00187af4;
                  }
                  if (uVar31 <= local_70) goto LAB_00187af4;
                  bVar6 = *(byte *)(lVar36 + local_70);
                  uVar33 = local_70 + 1;
                  bVar8 = bVar6 & 0x7f;
                  uVar37 = uVar33;
                  if ((bVar6 & 0x80) != 0 && uVar33 < uVar31) {
                    uVar38 = local_70 + 2;
                    bVar8 = *(byte *)(lVar36 + uVar33) << 7 | bVar6 & 0x7f;
                    uVar37 = uVar38;
                    if (((((*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31) &&
                         (uVar33 = local_70 + 3, uVar37 = uVar33,
                         (*(byte *)(lVar36 + uVar38) & 0x80) != 0 && uVar33 < uVar31)) &&
                        (uVar38 = local_70 + 4, uVar37 = uVar38,
                        (*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31)) &&
                       (((uVar33 = local_70 + 5, uVar37 = uVar33,
                         (*(byte *)(lVar36 + uVar38) & 0x80) != 0 && uVar33 < uVar31 &&
                         (uVar38 = local_70 + 6, uVar37 = uVar38,
                         (*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31)) &&
                        ((uVar33 = local_70 + 7, uVar37 = uVar33,
                         (*(byte *)(lVar36 + uVar38) & 0x80) != 0 && uVar33 < uVar31 &&
                         ((uVar38 = local_70 + 8, uVar37 = uVar38,
                          (*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31 &&
                          (uVar37 = local_70 + 9,
                          (*(byte *)(lVar36 + uVar38) & 0x80) != 0 && local_70 + 9 < uVar31))))))))
                    {
                      uVar37 = local_70 + 10;
                    }
                  }
                }
                else {
                  plVar13[uVar18 * 9 + 2] = 0;
LAB_00187af0:
                  plVar13[uVar18 * 9 + 3] = 0;
LAB_00187af4:
                  bVar8 = 0;
                  uVar37 = local_70;
                }
LAB_00186f4c:
                local_70 = uVar37;
                cVar21 = *(char *)((long)plVar13 + lVar10 + 0x24);
                *(byte *)(plVar13 + uVar18 * 9 + 4) = bVar8;
                *(undefined1 *)((long)plVar13 + lVar10 + 0x22) = 0xff;
                if (cVar21 == 'z') {
                  *(undefined1 *)((long)plVar13 + lVar10 + 0x23) = 1;
                  uVar33 = local_70;
                  if (local_70 < uVar31) {
                    uVar33 = local_70 + 1;
                    uVar37 = (ulong)*(byte *)(lVar36 + local_70) & 0x7f;
                    uVar18 = uVar33;
                    if ((*(byte *)(lVar36 + local_70) & 0x80) != 0 && uVar33 < uVar31) {
                      uVar38 = local_70 + 2;
                      uVar37 = ((ulong)*(byte *)(lVar36 + uVar33) & 0x7f) << 7 | uVar37;
                      uVar18 = uVar38;
                      if ((*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31) {
                        uVar33 = local_70 + 3;
                        uVar37 = ((ulong)*(byte *)(lVar36 + uVar38) & 0x7f) << 0xe | uVar37;
                        uVar18 = uVar33;
                        if ((*(byte *)(lVar36 + uVar38) & 0x80) != 0 && uVar33 < uVar31) {
                          uVar18 = local_70 + 4;
                          uVar37 = ((ulong)*(byte *)(lVar36 + uVar33) & 0x7f) << 0x15 | uVar37;
                          if ((*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar18 < uVar31) {
                            uVar33 = local_70 + 5;
                            uVar37 = ((ulong)*(byte *)(lVar36 + uVar18) & 0x7f) << 0x1c | uVar37;
                            uVar38 = uVar33;
                            if ((*(byte *)(lVar36 + uVar18) & 0x80) != 0 && uVar33 < uVar31) {
                              uVar38 = local_70 + 6;
                              uVar37 = ((ulong)*(byte *)(lVar36 + uVar33) & 0x7f) << 0x23 | uVar37;
                              if ((*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar38 < uVar31) {
                                uVar33 = local_70 + 7;
                                uVar37 = ((ulong)*(byte *)(lVar36 + uVar38) & 0x7f) << 0x2a | uVar37
                                ;
                                uVar18 = uVar33;
                                if ((*(byte *)(lVar36 + uVar38) & 0x80) != 0 && uVar33 < uVar31) {
                                  uVar18 = local_70 + 8;
                                  uVar37 = ((ulong)*(byte *)(lVar36 + uVar33) & 0x7f) << 0x31 |
                                           uVar37;
                                  if ((*(byte *)(lVar36 + uVar33) & 0x80) != 0 && uVar18 < uVar31) {
                                    uVar38 = local_70 + 9;
                                    uVar37 = ((ulong)*(byte *)(lVar36 + uVar18) & 0x7f) << 0x38 |
                                             uVar37;
                                    if ((*(byte *)(lVar36 + uVar18) & 0x80) != 0 && uVar38 < uVar31)
                                    {
                                      uVar37 = uVar37 | (ulong)*(byte *)(lVar36 + uVar38) << 0x3f;
                                      uVar38 = local_70 + 10;
                                    }
                                    goto LAB_00187c4c;
                                  }
                                }
                                goto LAB_00187db0;
                              }
                            }
LAB_00187c4c:
                            local_70 = uVar38;
                            uVar33 = uVar37 + local_70;
                            goto LAB_00187c50;
                          }
                        }
                      }
                    }
LAB_00187db0:
                    local_70 = uVar18;
                    uVar33 = local_70 + uVar37;
                  }
LAB_00187c50:
                  puVar29 = &local_70;
                  uVar18 = 1;
                  if (1 < uVar42) {
                    do {
                      if (uVar33 <= local_70) break;
                      cVar21 = *(char *)((long)pvVar11 + uVar18);
                      if (cVar21 == 'P') {
                        uVar16 = 0;
                        if (local_70 < uVar31) {
                          uVar16 = *(undefined1 *)(lVar36 + local_70);
                          local_70 = local_70 + 1;
                        }
                        read_encoded_ptr_constprop_0(lVar36,uVar31,puVar29,uVar16,uVar22);
                        puVar29 = extraout_x11_03;
                        uVar18 = extraout_x12_01;
                        uVar33 = extraout_x13;
                      }
                      else if (cVar21 == 'R') {
                        uVar16 = 0;
                        if (local_70 < uVar31) {
                          uVar16 = *(undefined1 *)(lVar36 + local_70);
                          local_70 = local_70 + 1;
                        }
                        *(undefined1 *)((long)plVar13 + lVar10 + 0x21) = uVar16;
                      }
                      else if (cVar21 == 'L') {
                        uVar16 = 0;
                        if (local_70 < uVar31) {
                          uVar16 = *(undefined1 *)(lVar36 + local_70);
                          local_70 = local_70 + 1;
                        }
                        *(undefined1 *)((long)plVar13 + lVar10 + 0x22) = uVar16;
                      }
                      uVar18 = uVar18 + 1;
                    } while (uVar18 < uVar39);
                  }
                }
                uVar41 = uVar41 + 1;
                __ptr = plVar13;
                uVar25 = uVar26;
              }
            }
          }
        }
        local_70 = uVar23;
        uVar42 = local_70;
      } while (local_70 < uVar31);
      uVar31 = (ulong)uVar40;
      if (puVar30 != (undefined8 *)0x0) goto LAB_001861e4;
LAB_001870a0:
      pvVar11 = (void *)0x0;
      uVar24 = 0;
    }
    *puVar34 = __ptr;
    *(uint *)(puVar34 + 1) = uVar41;
    puVar34[2] = local_d8;
    *(uint *)(puVar34 + 3) = uVar40;
    puVar34[4] = pvVar11;
    *(undefined4 *)(puVar34 + 5) = uVar24;
    goto LAB_00185fb8;
  }
LAB_00185fb4:
  puVar34 = (undefined8 *)0x0;
LAB_00185fb8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return puVar34;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

