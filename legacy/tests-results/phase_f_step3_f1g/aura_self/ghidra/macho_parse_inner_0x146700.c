
void macho_parse_inner(long param_1,long param_2,ulong param_3,ulong param_4)

{
  char *__string;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  void *pvVar13;
  undefined8 uVar14;
  long lVar15;
  size_t sVar16;
  char *pcVar17;
  uint uVar18;
  uint uVar19;
  long lVar20;
  ulong uVar21;
  uint uVar22;
  long lVar23;
  undefined4 uVar24;
  ulong uVar25;
  uint uVar26;
  ulong uVar27;
  ulong uVar28;
  uint uVar29;
  ulong uVar30;
  uint uVar31;
  ulong uVar32;
  uint uVar33;
  uint uVar34;
  ulong uVar35;
  uint uVar36;
  ulong local_f8;
  uint local_f0;
  uint local_ec;
  uint local_c8;
  char local_80 [24];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((7 < param_3) && (uVar30 = param_3 - 8, param_4 <= uVar30)) {
    uVar3 = *(uint *)(param_2 + param_4);
    uVar1 = uVar3 & 0xfeffffff;
    if (uVar3 + 0x1120532 < 2 || uVar1 == 0xcefaedfe) {
      bVar7 = uVar3 == 0xfeedfacf || uVar3 == 0xcffaedfe;
      uVar32 = 0x1c;
      if (bVar7) {
        uVar32 = 0x20;
      }
      if ((uVar32 <= param_3) && (param_4 <= param_3 - uVar32)) {
        lVar20 = param_2 + param_4;
        uVar18 = *(uint *)(lVar20 + 4);
        uVar33 = *(uint *)(lVar20 + 0x10);
        uVar10 = *(uint *)(lVar20 + 0x14);
        if (uVar1 == 0xcefaedfe) {
          uVar18 = (uVar18 & 0xff00ff00) >> 8 | (uVar18 & 0xff00ff) << 8;
          uVar18 = uVar18 >> 0x10 | uVar18 << 0x10;
          uVar33 = (uVar33 & 0xff00ff00) >> 8 | (uVar33 & 0xff00ff) << 8;
          uVar33 = uVar33 >> 0x10 | uVar33 << 0x10;
          uVar10 = (uVar10 & 0xff00ff00) >> 8 | (uVar10 & 0xff00ff) << 8;
          uVar10 = uVar10 >> 0x10 | uVar10 << 0x10;
        }
        if ((uVar10 <= param_3) && (uVar32 = uVar32 + param_4, uVar32 <= param_3 - uVar10)) {
          if (uVar18 == 0x1000007) {
            iVar12 = 2;
          }
          else if (uVar18 < 0x1000008) {
            iVar12 = 1;
            if ((uVar18 != 7) && (iVar12 = 3, uVar18 != 0xc)) {
              iVar12 = 0;
            }
          }
          else {
            iVar12 = (uint)(uVar18 == 0x100000c) << 2;
          }
          *(undefined4 *)(param_1 + 8) = 3;
          *(int *)(param_1 + 0xc) = iVar12;
          if (uVar33 == 0 || uVar30 < uVar32) {
            *(undefined4 *)(param_1 + 0x20) = 0;
          }
          else {
            if (uVar1 == 0xcefaedfe) {
              uVar10 = 0;
              uVar18 = 0;
              uVar21 = uVar32;
              do {
                uVar11 = *(uint *)(param_2 + uVar21 + 4);
                uVar11 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
                uVar11 = uVar11 >> 0x10 | uVar11 << 0x10;
                uVar25 = (ulong)uVar11;
                if (uVar11 < 8) break;
                if (*(int *)(param_2 + uVar21) == 0x1000000) {
                  if ((0x37 < param_3) && (uVar21 <= param_3 - 0x38)) {
                    iVar12 = ctx32_isra_0(param_2,1,uVar21 + 0x30);
                    goto LAB_0014717c;
                  }
                }
                else if ((0x47 < param_3 && *(int *)(param_2 + uVar21) == 0x19000000) &&
                        (uVar21 <= param_3 - 0x48)) {
                  iVar12 = ctx32_isra_0(param_2,1,uVar21 + 0x40);
LAB_0014717c:
                  uVar18 = uVar18 + iVar12;
                  if (0x200 < uVar18) {
                    uVar18 = 0x200;
                    goto LAB_001468a8;
                  }
                }
                uVar10 = uVar10 + 1;
                uVar21 = uVar21 + (uVar25 & 0xffffffff);
              } while (uVar10 < uVar33 && uVar21 <= uVar30);
LAB_001468a4:
              if (uVar18 == 0) goto LAB_00146c00;
LAB_001468a8:
              pvVar13 = calloc((ulong)uVar18,0x38);
              *(void **)(param_1 + 0x18) = pvVar13;
              if (pvVar13 == (void *)0x0) goto LAB_001469e8;
            }
            else {
              if (0x37 < param_3) {
                uVar10 = 0;
                uVar18 = 0;
                uVar21 = uVar32;
                do {
                  uVar11 = *(uint *)(param_2 + uVar21 + 4);
                  uVar25 = (ulong)uVar11;
                  if (uVar11 < 8) break;
                  if (*(int *)(param_2 + uVar21) == 1) {
                    if (uVar21 <= param_3 - 0x38) {
                      iVar12 = ctx32_isra_0(param_2,0,uVar21 + 0x30);
                      goto LAB_00147290;
                    }
                  }
                  else if ((0x47 < param_3 && *(int *)(param_2 + uVar21) == 0x19) &&
                          (uVar21 <= param_3 - 0x48)) {
                    iVar12 = ctx32_isra_0(param_2,0,uVar21 + 0x40);
LAB_00147290:
                    uVar18 = uVar18 + iVar12;
                    if (0x200 < uVar18) {
                      uVar18 = 0x200;
                      goto LAB_001468a8;
                    }
                  }
                  uVar10 = uVar10 + 1;
                  uVar21 = uVar21 + (uVar25 & 0xffffffff);
                } while (uVar10 < uVar33 && uVar21 <= uVar30);
                goto LAB_001468a4;
              }
              uVar18 = 0;
LAB_00146c00:
              pvVar13 = *(void **)(param_1 + 0x18);
            }
            uVar25 = 0;
            uVar36 = 0;
            uVar10 = 0;
            bVar8 = false;
            bVar9 = false;
            uVar11 = 0;
            local_f8 = 0;
            local_f0 = 0;
            local_ec = 0;
            uVar21 = 0;
            do {
              lVar20 = param_2 + uVar32;
              uVar19 = *(uint *)(param_2 + uVar32);
              uVar2 = *(uint *)(lVar20 + 4);
              if (uVar1 == 0xcefaedfe) {
                uVar19 = (uVar19 & 0xff00ff00) >> 8 | (uVar19 & 0xff00ff) << 8;
                uVar19 = uVar19 >> 0x10 | uVar19 << 0x10;
                uVar2 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
                uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
              }
              uVar35 = uVar21;
              if (uVar2 < 8) break;
              uVar22 = uVar36;
              if (uVar19 == 1) {
                if ((0x37 < param_3) && (uVar32 <= param_3 - 0x38)) {
                  uVar19 = *(uint *)(lVar20 + 0x2c);
                  local_c8 = *(uint *)(lVar20 + 0x30);
                  uVar22 = *(uint *)(lVar20 + 0x18);
                  if (uVar1 == 0xcefaedfe) {
                    uVar19 = uVar19 >> 0x18;
                    uVar22 = (uVar22 & 0xff00ff00) >> 8 | (uVar22 & 0xff00ff) << 8;
                    uVar22 = uVar22 >> 0x10 | uVar22 << 0x10;
                    uVar34 = (local_c8 & 0xff00ff00) >> 8 | (local_c8 & 0xff00ff) << 8;
                    local_c8 = uVar34 >> 0x10 | uVar34 << 0x10;
                  }
                  uVar34 = uVar19 & 1;
                  if ((uVar19 >> 1 & 1) != 0) {
                    uVar34 = uVar34 | 2;
                  }
                  if ((uVar19 >> 2 & 1) != 0) {
                    uVar34 = uVar34 | 4;
                  }
                  cVar4 = *(char *)(lVar20 + 8);
                  if (cVar4 == '\0') {
                    lVar23 = 0;
                  }
                  else {
                    cVar5 = *(char *)(lVar20 + 9);
                    local_80[0] = cVar4;
                    if (cVar5 == '\0') {
                      lVar23 = 1;
                    }
                    else {
                      cVar4 = *(char *)(lVar20 + 10);
                      local_80[1] = cVar5;
                      if (cVar4 == '\0') {
                        lVar23 = 2;
                      }
                      else {
                        cVar5 = *(char *)(lVar20 + 0xb);
                        local_80[2] = cVar4;
                        if (cVar5 == '\0') {
                          lVar23 = 3;
                        }
                        else {
                          cVar4 = *(char *)(lVar20 + 0xc);
                          local_80[3] = cVar5;
                          if (cVar4 == '\0') {
                            lVar23 = 4;
                          }
                          else {
                            cVar5 = *(char *)(lVar20 + 0xd);
                            local_80[4] = cVar4;
                            if (cVar5 == '\0') {
                              lVar23 = 5;
                            }
                            else {
                              cVar4 = *(char *)(lVar20 + 0xe);
                              local_80[5] = cVar5;
                              if (cVar4 == '\0') {
                                lVar23 = 6;
                              }
                              else {
                                cVar5 = *(char *)(lVar20 + 0xf);
                                local_80[6] = cVar4;
                                if (cVar5 == '\0') {
                                  lVar23 = 7;
                                }
                                else {
                                  cVar4 = *(char *)(lVar20 + 0x10);
                                  local_80[7] = cVar5;
                                  if (cVar4 == '\0') {
                                    lVar23 = 8;
                                  }
                                  else {
                                    cVar5 = *(char *)(lVar20 + 0x11);
                                    local_80[8] = cVar4;
                                    if (cVar5 == '\0') {
                                      lVar23 = 9;
                                    }
                                    else {
                                      cVar4 = *(char *)(lVar20 + 0x12);
                                      local_80[9] = cVar5;
                                      if (cVar4 == '\0') {
                                        lVar23 = 10;
                                      }
                                      else {
                                        cVar5 = *(char *)(lVar20 + 0x13);
                                        local_80[10] = cVar4;
                                        if (cVar5 == '\0') {
                                          lVar23 = 0xb;
                                        }
                                        else {
                                          cVar4 = *(char *)(lVar20 + 0x14);
                                          local_80[0xb] = cVar5;
                                          if (cVar4 == '\0') {
                                            lVar23 = 0xc;
                                          }
                                          else {
                                            cVar5 = *(char *)(lVar20 + 0x15);
                                            local_80[0xc] = cVar4;
                                            if (cVar5 == '\0') {
                                              lVar23 = 0xd;
                                            }
                                            else {
                                              cVar4 = *(char *)(lVar20 + 0x16);
                                              local_80[0xd] = cVar5;
                                              if (cVar4 == '\0') {
                                                lVar23 = 0xe;
                                              }
                                              else {
                                                local_80[0xe] = cVar4;
                                                if (*(char *)(lVar20 + 0x17) == '\0') {
                                                  lVar23 = 0xf;
                                                }
                                                else {
                                                  lVar23 = 0x10;
                                                  local_80[0xf] = *(char *)(lVar20 + 0x17);
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
                  }
                  local_80[lVar23] = '\0';
                  iVar12 = strcmp(local_80,"__TEXT");
                  if (iVar12 == 0) {
                    uVar35 = (ulong)uVar22;
                  }
                  uVar19 = 0;
                  for (lVar20 = param_2 + uVar32 + 0x38;
                      (uVar22 = uVar19 + uVar36,
                      (uVar19 < local_c8 && uVar22 < uVar18) && 0x43 < param_3 &&
                      ((ulong)(lVar20 - param_2) <= param_3 - 0x44)); lVar20 = lVar20 + 0x44) {
                    uVar26 = *(uint *)(lVar20 + 0x28);
                    uVar29 = *(uint *)(lVar20 + 0x20);
                    uVar31 = *(uint *)(lVar20 + 0x24);
                    if (uVar1 == 0xcefaedfe) {
                      uVar29 = (uVar29 & 0xff00ff00) >> 8 | (uVar29 & 0xff00ff) << 8;
                      uVar29 = uVar29 >> 0x10 | uVar29 << 0x10;
                      uVar31 = (uVar31 & 0xff00ff00) >> 8 | (uVar31 & 0xff00ff) << 8;
                      uVar31 = uVar31 >> 0x10 | uVar31 << 0x10;
                      uVar26 = (uVar26 & 0xff00ff00) >> 8 | (uVar26 & 0xff00ff) << 8;
                      uVar26 = uVar26 >> 0x10 | uVar26 << 0x10;
                    }
                    lVar23 = (ulong)uVar22 * 0x38;
                    uVar14 = make_section_name(lVar20 + 0x10);
                    *(undefined8 *)((long)pvVar13 + lVar23) = uVar14;
                    uVar21 = (ulong)uVar31;
                    uVar27 = (ulong)uVar26;
                    *(ulong *)((long)pvVar13 + lVar23 + 8) = (ulong)uVar29;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x10) = uVar27;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x18) = uVar21;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x20) = uVar21;
                    *(uint *)((long)pvVar13 + lVar23 + 0x30) = uVar34;
                    if ((uVar26 == 0 || uVar31 == 0) || param_3 < uVar21) {
                      lVar15 = 0;
                    }
                    else {
                      lVar15 = param_2 + uVar27;
                      if (param_3 - uVar21 < uVar27) {
                        lVar15 = 0;
                      }
                    }
                    uVar19 = uVar19 + 1;
                    *(long *)((long)pvVar13 + lVar23 + 0x28) = lVar15;
                  }
                }
              }
              else if (uVar19 == 0x19) {
                if ((0x47 < param_3) && (uVar32 <= param_3 - 0x48)) {
                  uVar19 = *(uint *)(lVar20 + 0x3c);
                  local_c8 = *(uint *)(lVar20 + 0x40);
                  uVar35 = *(ulong *)(lVar20 + 0x18);
                  if (uVar1 == 0xcefaedfe) {
                    uVar19 = uVar19 >> 0x18;
                    uVar35 = (uVar35 & 0xff00ff00ff00ff00) >> 8 | (uVar35 & 0xff00ff00ff00ff) << 8;
                    uVar35 = (uVar35 & 0xffff0000ffff0000) >> 0x10 |
                             (uVar35 & 0xffff0000ffff) << 0x10;
                    uVar35 = uVar35 >> 0x20 | uVar35 << 0x20;
                    uVar22 = (local_c8 & 0xff00ff00) >> 8 | (local_c8 & 0xff00ff) << 8;
                    local_c8 = uVar22 >> 0x10 | uVar22 << 0x10;
                  }
                  uVar34 = uVar19 & 1;
                  if ((uVar19 >> 1 & 1) != 0) {
                    uVar34 = uVar34 | 2;
                  }
                  if ((uVar19 >> 2 & 1) != 0) {
                    uVar34 = uVar34 | 4;
                  }
                  cVar4 = *(char *)(lVar20 + 8);
                  if (cVar4 == '\0') {
                    lVar23 = 0;
                  }
                  else {
                    cVar5 = *(char *)(lVar20 + 9);
                    local_80[0] = cVar4;
                    if (cVar5 == '\0') {
                      lVar23 = 1;
                    }
                    else {
                      cVar4 = *(char *)(lVar20 + 10);
                      local_80[1] = cVar5;
                      if (cVar4 == '\0') {
                        lVar23 = 2;
                      }
                      else {
                        cVar5 = *(char *)(lVar20 + 0xb);
                        local_80[2] = cVar4;
                        if (cVar5 == '\0') {
                          lVar23 = 3;
                        }
                        else {
                          cVar4 = *(char *)(lVar20 + 0xc);
                          local_80[3] = cVar5;
                          if (cVar4 == '\0') {
                            lVar23 = 4;
                          }
                          else {
                            cVar5 = *(char *)(lVar20 + 0xd);
                            local_80[4] = cVar4;
                            if (cVar5 == '\0') {
                              lVar23 = 5;
                            }
                            else {
                              cVar4 = *(char *)(lVar20 + 0xe);
                              local_80[5] = cVar5;
                              if (cVar4 == '\0') {
                                lVar23 = 6;
                              }
                              else {
                                cVar5 = *(char *)(lVar20 + 0xf);
                                local_80[6] = cVar4;
                                if (cVar5 == '\0') {
                                  lVar23 = 7;
                                }
                                else {
                                  cVar4 = *(char *)(lVar20 + 0x10);
                                  local_80[7] = cVar5;
                                  if (cVar4 == '\0') {
                                    lVar23 = 8;
                                  }
                                  else {
                                    cVar5 = *(char *)(lVar20 + 0x11);
                                    local_80[8] = cVar4;
                                    if (cVar5 == '\0') {
                                      lVar23 = 9;
                                    }
                                    else {
                                      cVar4 = *(char *)(lVar20 + 0x12);
                                      local_80[9] = cVar5;
                                      if (cVar4 == '\0') {
                                        lVar23 = 10;
                                      }
                                      else {
                                        cVar5 = *(char *)(lVar20 + 0x13);
                                        local_80[10] = cVar4;
                                        if (cVar5 == '\0') {
                                          lVar23 = 0xb;
                                        }
                                        else {
                                          cVar4 = *(char *)(lVar20 + 0x14);
                                          local_80[0xb] = cVar5;
                                          if (cVar4 == '\0') {
                                            lVar23 = 0xc;
                                          }
                                          else {
                                            cVar5 = *(char *)(lVar20 + 0x15);
                                            local_80[0xc] = cVar4;
                                            if (cVar5 == '\0') {
                                              lVar23 = 0xd;
                                            }
                                            else {
                                              cVar4 = *(char *)(lVar20 + 0x16);
                                              local_80[0xd] = cVar5;
                                              if (cVar4 == '\0') {
                                                lVar23 = 0xe;
                                              }
                                              else {
                                                local_80[0xe] = cVar4;
                                                if (*(char *)(lVar20 + 0x17) == '\0') {
                                                  lVar23 = 0xf;
                                                }
                                                else {
                                                  lVar23 = 0x10;
                                                  local_80[0xf] = *(char *)(lVar20 + 0x17);
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
                  }
                  local_80[lVar23] = '\0';
                  iVar12 = strcmp(local_80,"__TEXT");
                  if (iVar12 != 0) {
                    uVar35 = uVar21;
                  }
                  uVar19 = 0;
                  for (lVar20 = param_2 + uVar32 + 0x48;
                      (uVar22 = uVar19 + uVar36,
                      (uVar19 < local_c8 && uVar22 < uVar18) && 0x4f < param_3 &&
                      ((ulong)(lVar20 - param_2) <= param_3 - 0x50)); lVar20 = lVar20 + 0x50) {
                    uVar29 = *(uint *)(lVar20 + 0x30);
                    uVar21 = *(ulong *)(lVar20 + 0x20);
                    uVar27 = *(ulong *)(lVar20 + 0x28);
                    if (uVar1 == 0xcefaedfe) {
                      uVar21 = (uVar21 & 0xff00ff00ff00ff00) >> 8 | (uVar21 & 0xff00ff00ff00ff) << 8
                      ;
                      uVar21 = (uVar21 & 0xffff0000ffff0000) >> 0x10 |
                               (uVar21 & 0xffff0000ffff) << 0x10;
                      uVar21 = uVar21 >> 0x20 | uVar21 << 0x20;
                      uVar27 = (uVar27 & 0xff00ff00ff00ff00) >> 8 | (uVar27 & 0xff00ff00ff00ff) << 8
                      ;
                      uVar27 = (uVar27 & 0xffff0000ffff0000) >> 0x10 |
                               (uVar27 & 0xffff0000ffff) << 0x10;
                      uVar27 = uVar27 >> 0x20 | uVar27 << 0x20;
                      uVar29 = (uVar29 & 0xff00ff00) >> 8 | (uVar29 & 0xff00ff) << 8;
                      uVar29 = uVar29 >> 0x10 | uVar29 << 0x10;
                    }
                    lVar23 = (ulong)uVar22 * 0x38;
                    uVar14 = make_section_name(lVar20 + 0x10);
                    *(undefined8 *)((long)pvVar13 + lVar23) = uVar14;
                    uVar28 = (ulong)uVar29;
                    *(ulong *)((long)pvVar13 + lVar23 + 8) = uVar21;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x10) = uVar28;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x18) = uVar27;
                    *(ulong *)((long)pvVar13 + lVar23 + 0x20) = uVar27;
                    *(uint *)((long)pvVar13 + lVar23 + 0x30) = uVar34;
                    if ((uVar29 == 0 || uVar27 == 0) || param_3 < uVar27) {
                      lVar15 = 0;
                    }
                    else {
                      lVar15 = param_2 + uVar28;
                      if (param_3 - uVar27 < uVar28) {
                        lVar15 = 0;
                      }
                    }
                    uVar19 = uVar19 + 1;
                    *(long *)((long)pvVar13 + lVar23 + 0x28) = lVar15;
                  }
                }
              }
              else if (uVar19 == 2) {
                if (uVar32 <= param_3 - 0x18) {
                  local_ec = *(uint *)(lVar20 + 8);
                  uVar11 = *(uint *)(lVar20 + 0xc);
                  local_f0 = *(uint *)(lVar20 + 0x10);
                  uVar36 = *(uint *)(lVar20 + 0x14);
                  if (uVar1 == 0xcefaedfe) {
                    uVar19 = (local_ec & 0xff00ff00) >> 8 | (local_ec & 0xff00ff) << 8;
                    local_ec = uVar19 >> 0x10 | uVar19 << 0x10;
                    uVar11 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
                    uVar11 = uVar11 >> 0x10 | uVar11 << 0x10;
                    uVar36 = (uVar36 & 0xff00ff00) >> 8 | (uVar36 & 0xff00ff) << 8;
                    uVar36 = uVar36 >> 0x10 | uVar36 << 0x10;
                    uVar19 = (local_f0 & 0xff00ff00) >> 8 | (local_f0 & 0xff00ff) << 8;
                    local_f0 = uVar19 >> 0x10 | uVar19 << 0x10;
                  }
                  local_f8 = (ulong)uVar36;
                  bVar9 = true;
                }
              }
              else if ((uVar19 == 0x80000028) && (uVar32 <= param_3 - 0x18)) {
                uVar25 = *(ulong *)(lVar20 + 8);
                if (uVar1 == 0xcefaedfe) {
                  uVar21 = (uVar25 & 0xff00ff00ff00ff00) >> 8 | (uVar25 & 0xff00ff00ff00ff) << 8;
                  uVar21 = (uVar21 & 0xffff0000ffff0000) >> 0x10 | (uVar21 & 0xffff0000ffff) << 0x10
                  ;
                  uVar25 = uVar21 >> 0x20 | uVar21 << 0x20;
                }
                bVar8 = true;
              }
              uVar36 = uVar22;
              uVar32 = uVar32 + uVar2;
              uVar10 = uVar10 + 1;
              uVar21 = uVar35;
            } while (uVar32 <= uVar30 && uVar10 < uVar33);
            *(uint *)(param_1 + 0x20) = uVar36;
            if (bVar8) {
              *(ulong *)(param_1 + 0x10) = uVar25 + uVar35;
            }
            if ((bVar9) && (uVar11 != 0)) {
              uVar33 = uVar11;
              if (0x10000 < uVar11) {
                uVar33 = 0x10000;
              }
              pvVar13 = calloc((ulong)uVar33,0x28);
              if (pvVar13 == (void *)0x0) goto LAB_001469e8;
              if ((param_3 < local_f8) || (param_3 - local_f8 < (ulong)local_f0)) {
LAB_00147140:
                *(undefined4 *)(param_1 + 0x30) = 0;
              }
              else {
                lVar20 = 0xc;
                if (bVar7) {
                  lVar20 = 0x10;
                }
                uVar30 = (ulong)local_ec;
                if (param_3 - lVar20 < (ulong)local_ec) goto LAB_00147140;
                if (uVar11 < uVar33) {
                  uVar33 = uVar11;
                }
                uVar10 = 0;
                uVar18 = 0;
                do {
                  uVar11 = ctx32_isra_0(param_2,uVar1 == 0xcefaedfe,uVar30);
                  bVar6 = *(byte *)(param_2 + 4 + uVar30);
                  if (uVar3 == 0xfeedfacf || uVar3 == 0xcffaedfe) {
                    uVar32 = *(ulong *)(param_2 + 8 + uVar30);
                    if (uVar1 == 0xcefaedfe) {
                      uVar32 = (uVar32 & 0xff00ff00ff00ff00) >> 8 | (uVar32 & 0xff00ff00ff00ff) << 8
                      ;
                      uVar32 = (uVar32 & 0xffff0000ffff0000) >> 0x10 |
                               (uVar32 & 0xffff0000ffff) << 0x10;
                      uVar32 = uVar32 >> 0x20 | uVar32 << 0x20;
                    }
                  }
                  else {
                    uVar32 = ctx32_isra_0(param_2,uVar1 == 0xcefaedfe,uVar30 + 8);
                    uVar32 = uVar32 & 0xffffffff;
                  }
                  if (((uVar11 != 0 && uVar11 < (uint)local_f8) && bVar6 < 0x20) &&
                     (uVar21 = (ulong)(local_f0 + uVar11), uVar21 < param_3)) {
                    __string = (char *)(param_2 + uVar21);
                    sVar16 = strnlen(__string,param_3 - uVar21);
                    if (sVar16 < param_3 - uVar21) {
                      uVar11 = bVar6 & 1;
                      if ((bVar6 & (bVar6 & 0xe) == 0) == 0) {
                        if ((bVar6 & 0xe) != 0xe) goto LAB_00146b2c;
                        uVar24 = 1;
                      }
                      else {
                        uVar11 = 1;
                        uVar24 = 3;
                      }
                      lVar23 = (ulong)uVar18 * 0x28;
                      uVar18 = uVar18 + 1;
                      pcVar17 = strdup(__string);
                      *(char **)((long)pvVar13 + lVar23) = pcVar17;
                      uVar14 = aura_demangle(__string);
                      *(undefined8 *)((long)pvVar13 + lVar23 + 8) = uVar14;
                      *(ulong *)((long)pvVar13 + lVar23 + 0x10) = uVar32;
                      *(undefined8 *)((long)pvVar13 + lVar23 + 0x18) = 0;
                      *(undefined4 *)((long)pvVar13 + lVar23 + 0x20) = uVar24;
                      *(uint *)((long)pvVar13 + lVar23 + 0x24) = uVar11;
                    }
                  }
LAB_00146b2c:
                  uVar10 = uVar10 + 1;
                } while ((uVar33 != uVar10) &&
                        (uVar30 = uVar30 + lVar20, uVar30 <= param_3 - lVar20));
                *(uint *)(param_1 + 0x30) = uVar18;
                if (uVar18 != 0) {
                  *(void **)(param_1 + 0x28) = pvVar13;
                  goto LAB_001469cc;
                }
              }
              free(pvVar13);
            }
          }
LAB_001469cc:
          uVar14 = 0;
          goto LAB_001469ec;
        }
      }
    }
  }
LAB_001469e8:
  uVar14 = 0xffffffff;
LAB_001469ec:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar14,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

