
long * pe_parser_load(long param_1)

{
  undefined8 *puVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  ulong uVar5;
  uint uVar6;
  ushort uVar7;
  ushort uVar8;
  bool bVar9;
  uint uVar10;
  bool bVar11;
  uint uVar12;
  long *plVar13;
  long lVar14;
  undefined8 *puVar15;
  char *pcVar16;
  long lVar17;
  long lVar18;
  size_t sVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  int iVar22;
  ulong uVar23;
  ulong uVar24;
  char *pcVar25;
  ulong uVar26;
  int extraout_w8;
  long extraout_x8;
  ulong extraout_x8_00;
  undefined8 extraout_x9;
  undefined8 extraout_x9_00;
  undefined8 extraout_x9_01;
  int extraout_w10;
  uint extraout_w10_00;
  ulong extraout_x10;
  long extraout_x10_00;
  ulong extraout_x10_01;
  long extraout_x11;
  ulong extraout_x11_00;
  int *piVar27;
  long extraout_x12;
  ulong uVar28;
  ulong uVar29;
  ulong uVar30;
  long lVar31;
  ulong uVar32;
  uint uVar33;
  undefined8 *puVar34;
  uint uVar35;
  void *local_e0;
  ulong local_c0;
  int local_a4;
  int local_a0;
  uint local_88;
  long local_80;
  undefined8 local_78;
  undefined1 local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0) &&
     (local_80 = mapped_file_open(param_1,PTR___stack_chk_guard_005ffe88,0), local_80 != 0)) {
    plVar13 = (long *)file_info_create(&local_80);
    if (plVar13 == (long *)0x0) {
      mapped_file_destroy(local_80);
    }
    else {
      pcVar4 = *(char **)(*plVar13 + 8);
      uVar5 = *(ulong *)(*plVar13 + 0x10);
      if (((0x3f < uVar5) && (*pcVar4 == 'M')) && (pcVar4[1] == 'Z')) {
        uVar32 = uVar5 - 4;
        uVar12 = *(uint *)(pcVar4 + 0x3c);
        if ((uVar12 <= uVar32) && (*(int *)(pcVar4 + uVar12) == 0x4550)) {
          uVar23 = (ulong)(uVar12 + 4);
          uVar30 = uVar5 - 0x14;
          if (uVar23 <= uVar30) {
            uVar26 = uVar23 + 0x14;
            uVar29 = uVar5 - 2;
            uVar8 = *(ushort *)(pcVar4 + (uVar12 + 4));
            uVar7 = *(ushort *)(pcVar4 + uVar23 + 2);
            uVar28 = (ulong)uVar7;
            if ((uVar26 <= uVar29) && ((*(short *)(pcVar4 + uVar26) - 0x10bU & 0xfeff) == 0)) {
              if (*(short *)(pcVar4 + uVar26) == 0x20b) {
                if (uVar23 + 0x2c <= uVar5 - 8) {
                  local_c0 = *(ulong *)(pcVar4 + uVar23 + 0x2c);
                  if (uVar23 + 0x24 <= uVar32) {
                    uVar12 = *(uint *)(pcVar4 + uVar23 + 0x24);
                    lVar14 = 0x70;
                    goto LAB_00145b74;
                  }
                }
              }
              else if (uVar23 + 0x30 <= uVar32) {
                if (uVar23 + 0x24 <= uVar32) {
                  uVar12 = *(uint *)(pcVar4 + uVar23 + 0x24);
                  local_c0 = (ulong)*(uint *)(pcVar4 + uVar23 + 0x30);
                  lVar14 = 0x60;
LAB_00145b74:
                  uVar24 = uVar26 + lVar14;
                  if (uVar5 - 0x10 < uVar24) {
                    local_a4 = 0;
                    local_a0 = 0;
                  }
                  else {
                    local_a4 = *(int *)(pcVar4 + uVar24);
                    local_a0 = *(int *)(pcVar4 + uVar24 + 8);
                  }
                  if ((uVar28 * 0x28 <= uVar5) &&
                     (uVar26 + *(ushort *)(pcVar4 + uVar23 + 0x10) <= uVar5 + uVar28 * -0x28)) {
                    pcVar2 = pcVar4 + uVar26 + *(ushort *)(pcVar4 + uVar23 + 0x10);
                    if (uVar8 == 0x8664) {
                      iVar22 = 2;
                    }
                    else if (uVar8 < 0x8665) {
                      iVar22 = 1;
                      if ((uVar8 != 0x14c) && (iVar22 = 3, uVar8 != 0x1c0)) {
                        iVar22 = 0;
                      }
                    }
                    else {
                      iVar22 = (uint)(uVar8 == 0xaa64) << 2;
                    }
                    local_88 = (uint)uVar7;
                    *(undefined4 *)(plVar13 + 1) = 2;
                    *(int *)((long)plVar13 + 0xc) = iVar22;
                    plVar13[2] = local_c0 + uVar12;
                    if (local_88 < 0x101) {
                      if (uVar7 == 0) {
LAB_00145db0:
                        if (((local_a0 == 0) ||
                            (uVar23 = rva_to_offset(pcVar2,local_88,local_a0,uVar5), uVar23 == 0))
                           || (uVar30 < uVar23)) {
                          if (((local_a4 == 0) ||
                              (uVar23 = rva_to_offset(pcVar2,local_88,local_a4,uVar5), uVar23 == 0))
                             || (uVar5 - 0x28 < uVar23)) goto LAB_00145d3c;
                          uVar12 = 0;
                          uVar33 = *(uint *)(pcVar4 + uVar23 + 0x18);
                          uVar35 = uVar33;
                          if (0x10000 < uVar33) {
                            uVar33 = 0x10000;
                            uVar35 = uVar33;
                          }
joined_r0x001462a0:
                          uVar23 = (ulong)uVar35;
                          if (uVar35 == 0) goto LAB_00145d3c;
LAB_00145e04:
                          uVar35 = (uint)uVar23;
                        }
                        else {
                          piVar27 = (int *)(pcVar4 + uVar23);
                          uVar12 = 0;
                          do {
                            if (piVar27[3] == 0) break;
                            iVar22 = *piVar27;
                            if (iVar22 == 0) {
                              iVar22 = piVar27[4];
                            }
                            uVar23 = rva_to_offset(pcVar2,local_88,iVar22,uVar5);
                            if (uVar23 != 0) {
                              lVar14 = 4;
                              if (extraout_w10 == 0x20b) {
                                lVar14 = 8;
                              }
                              for (; uVar23 <= uVar5 - lVar14; uVar23 = uVar23 + lVar14) {
                                if (extraout_w10 == 0x20b) {
                                  uVar26 = *(ulong *)(pcVar4 + uVar23);
                                  if (uVar26 == 0) break;
                                  uVar28 = 0x8000000000000000;
                                }
                                else {
                                  if (*(uint *)(pcVar4 + uVar23) == 0) break;
                                  uVar26 = (ulong)*(uint *)(pcVar4 + uVar23);
                                  uVar28 = 0x80000000;
                                }
                                if (((uVar28 & uVar26) == 0) &&
                                   (uVar12 = uVar12 + 1, 0xffff < uVar12)) {
                                  uVar12 = 0x10000;
                                  if (local_a4 != 0) goto LAB_00146280;
                                  uVar23 = 0x10000;
                                  uVar33 = 0;
                                  goto LAB_00145e04;
                                }
                              }
                            }
                            piVar27 = (int *)(extraout_x12 + 0x14);
                          } while (extraout_x11_00 <= uVar30);
                          if (0x10000 < uVar12) {
                            uVar12 = 0x10000;
                          }
                          if (local_a4 == 0) {
LAB_00146298:
                            uVar33 = 0;
                            uVar35 = uVar12;
                            goto joined_r0x001462a0;
                          }
LAB_00146280:
                          uVar23 = rva_to_offset(pcVar2,local_88,local_a4,uVar5);
                          if ((uVar23 == 0) || (uVar5 - 0x28 < uVar23)) goto LAB_00146298;
                          uVar33 = *(uint *)(pcVar4 + uVar23 + 0x18);
                          if (0x10000 < uVar33) {
                            uVar33 = 0x10000;
                          }
                          uVar35 = uVar12 + uVar33;
                          if (uVar12 + uVar33 < 0x10001) goto joined_r0x001462a0;
                          uVar23 = 0x10000;
                          uVar35 = 0x10000;
                        }
                        local_e0 = calloc(uVar23,0x28);
                        plVar13[5] = (long)local_e0;
                        if (local_e0 != (void *)0x0) {
                          bVar9 = uVar33 != 0 && local_a4 != 0;
                          if (local_a0 == 0 || uVar12 == 0) {
                            uVar12 = 0;
                            if (bVar9) {
                              uVar12 = 0;
                              goto LAB_00145e5c;
                            }
                          }
                          else {
                            lVar14 = rva_to_offset(pcVar2,local_88,local_a0,uVar5);
                            if (lVar14 == 0) {
                              uVar12 = 0;
                              if (bVar9) goto LAB_00145e5c;
                            }
                            else {
                              uVar12 = 0;
                              for (piVar27 = (int *)(pcVar4 + lVar14);
                                  ((ulong)((long)piVar27 - (long)pcVar4) <= uVar30 &&
                                  (piVar27[3] != 0)); piVar27 = piVar27 + 5) {
                                iVar22 = piVar27[4];
                                if (*piVar27 != 0) {
                                  iVar22 = *piVar27;
                                }
                                uVar23 = rva_to_offset(pcVar2,local_88,iVar22,uVar5);
                                if (uVar23 != 0) {
                                  bVar11 = (int)extraout_x10_01 == 0x20b;
                                  lVar14 = 4;
                                  if (bVar11) {
                                    lVar14 = 8;
                                  }
                                  uVar26 = 0x80000000;
                                  if (bVar11) {
                                    uVar26 = 0x8000000000000000;
                                  }
                                  uVar28 = extraout_x10_01;
                                  for (; uVar23 <= uVar5 - lVar14 && uVar12 < uVar35;
                                      uVar23 = uVar23 + lVar14) {
                                    if ((int)uVar28 == 0x20b) {
                                      uVar24 = *(ulong *)(pcVar4 + uVar23);
                                    }
                                    else {
                                      uVar24 = (ulong)*(uint *)(pcVar4 + uVar23);
                                    }
                                    if (uVar24 == 0) break;
                                    if ((uVar24 & uVar26) == 0) {
                                      lVar17 = rva_to_offset(pcVar2,local_88,
                                                             (uint)uVar24 & 0x7fffffff,uVar5);
                                      if ((lVar17 == 0) || (uVar5 - 1 < lVar17 + 2U)) {
LAB_001461cc:
                                        pcVar25 = "(unknown)";
                                      }
                                      else {
                                        pcVar25 = pcVar4 + lVar17 + 2U;
                                        sVar19 = strnlen(pcVar25,uVar29 - lVar17);
                                        if (uVar29 - lVar17 <= sVar19) goto LAB_001461cc;
                                      }
                                      lVar17 = (ulong)uVar12 * 0x28;
                                      uVar12 = uVar12 + 1;
                                      pcVar16 = strdup(pcVar25);
                                      *(char **)((long)local_e0 + lVar17) = pcVar16;
                                      uVar21 = aura_demangle(pcVar25);
                                      uVar20 = DAT_0020bf10;
                                      uVar28 = (ulong)extraout_w10_00;
                                      *(undefined8 *)((long)local_e0 + lVar17 + 8) = uVar21;
                                      *(undefined8 *)((long)local_e0 + lVar17 + 0x10) = 0;
                                      *(undefined8 *)((long)local_e0 + lVar17 + 0x18) = 0;
                                      *(undefined8 *)((long)local_e0 + lVar17 + 0x20) = uVar20;
                                    }
                                  }
                                }
                              }
                              if (bVar9 && uVar12 < uVar35) {
                                local_e0 = (void *)plVar13[5];
                                uVar35 = uVar35 - uVar12;
LAB_00145e5c:
                                uVar30 = (ulong)local_88;
                                uVar23 = rva_to_offset(pcVar2,uVar30,local_a4,uVar5);
                                if ((uVar23 == 0) || (uVar5 - 0x28 < uVar23)) {
LAB_00145fd0:
                                  uVar33 = 0;
                                }
                                else {
                                  lVar14 = rva_to_offset(extraout_x9,uVar30 & 0xffffffff,
                                                         *(undefined4 *)(pcVar4 + uVar23 + 0x20));
                                  lVar17 = rva_to_offset(extraout_x9_00,uVar30 & 0xffffffff,
                                                         extraout_x10 & 0xffffffff);
                                  if (extraout_x10_00 == 0 || lVar17 == 0) goto LAB_00145fd0;
                                  uVar33 = *(uint *)(extraout_x8 + 0x18);
                                  lVar18 = rva_to_offset(0,extraout_x9_01,uVar30 & 0xffffffff,
                                                         *(undefined4 *)(extraout_x8 + 0x1c));
                                  if (uVar35 < uVar33) {
                                    uVar33 = uVar35;
                                  }
                                  uVar23 = extraout_x8_00;
                                  puVar15 = (undefined8 *)((long)local_e0 + extraout_x11 * 0x28);
                                  while ((uVar33 != (uint)uVar23 &&
                                         (uVar23 = (ulong)((uint)uVar23 << 2) + lVar14,
                                         uVar23 <= uVar32))) {
                                    uVar23 = rva_to_offset(pcVar2,local_88,
                                                           *(undefined4 *)(pcVar4 + uVar23),uVar5);
                                    if (uVar23 == 0 || uVar5 <= uVar23) {
LAB_00145f54:
                                      pcVar25 = "(unknown)";
                                    }
                                    else {
                                      pcVar25 = pcVar4 + uVar23;
                                      sVar19 = strnlen(pcVar25,uVar5 - uVar23);
                                      if (uVar5 - uVar23 <= sVar19) goto LAB_00145f54;
                                    }
                                    if (((lVar18 == 0) ||
                                        (uVar23 = (ulong)(uint)(extraout_w8 << 1) + lVar17,
                                        uVar29 < uVar23)) ||
                                       (uVar23 = lVar18 + (ulong)*(ushort *)(pcVar4 + uVar23) * 4,
                                       uVar32 < uVar23)) {
                                      lVar31 = 0;
                                    }
                                    else {
                                      lVar31 = *(uint *)(pcVar4 + uVar23) + local_c0;
                                    }
                                    pcVar16 = strdup(pcVar25);
                                    *puVar15 = pcVar16;
                                    uVar20 = aura_demangle(pcVar25);
                                    puVar15[1] = uVar20;
                                    puVar15[2] = lVar31;
                                    uVar20 = DAT_0020bf18;
                                    uVar23 = (ulong)(extraout_w8 + 1);
                                    puVar15[3] = 0;
                                    puVar15[4] = uVar20;
                                    puVar15 = puVar15 + 5;
                                  }
                                }
                                uVar12 = uVar12 + uVar33;
                              }
                            }
                          }
                          *(uint *)(plVar13 + 6) = uVar12;
                          goto LAB_00145d3c;
                        }
                      }
                      else {
                        puVar15 = calloc(uVar28,0x38);
                        plVar13[3] = (long)puVar15;
                        if (puVar15 != (undefined8 *)0x0) goto LAB_00145c30;
                      }
                    }
                    else {
                      puVar15 = calloc(0x100,0x38);
                      plVar13[3] = (long)puVar15;
                      if (puVar15 != (undefined8 *)0x0) {
                        local_88 = 0x100;
LAB_00145c30:
                        puVar34 = puVar15;
                        pcVar25 = pcVar2;
                        do {
                          uVar35 = *(uint *)(pcVar25 + 0xc);
                          local_78 = *(undefined8 *)pcVar25;
                          uVar33 = *(uint *)(pcVar25 + 0x10);
                          uVar3 = *(uint *)(pcVar25 + 0x14);
                          uVar6 = *(uint *)(pcVar25 + 0x24);
                          uVar12 = *(uint *)(pcVar25 + 8);
                          if (*(uint *)(pcVar25 + 8) == 0) {
                            uVar12 = uVar33;
                          }
                          local_70 = 0;
                          pcVar16 = strdup((char *)&local_78);
                          puVar34[3] = (ulong)uVar12;
                          uVar10 = uVar6 >> 0x1e & 1;
                          *puVar34 = pcVar16;
                          puVar34[1] = local_c0 + uVar35;
                          uVar12 = uVar10 | 2;
                          if (-1 < (int)uVar6) {
                            uVar12 = uVar10;
                          }
                          uVar23 = (ulong)uVar33;
                          uVar26 = (ulong)uVar3;
                          puVar34[2] = uVar26;
                          puVar34[4] = uVar23;
                          *(uint *)(puVar34 + 6) = uVar12 | (uVar6 & 0x20000000) >> 0x1b;
                          pcVar16 = (char *)0x0;
                          if (((uVar3 != 0 && uVar33 != 0) && uVar23 <= uVar5) &&
                             (pcVar16 = pcVar4 + uVar26, uVar5 - uVar23 < uVar26)) {
                            pcVar16 = (char *)0x0;
                          }
                          lVar14 = plVar13[4];
                          puVar1 = puVar34 + 7;
                          puVar34[5] = pcVar16;
                          pcVar25 = pcVar25 + 0x28;
                          *(int *)(plVar13 + 4) = (int)lVar14 + 1;
                          puVar34 = puVar1;
                        } while (puVar15 + (ulong)local_88 * 7 != puVar1);
                        goto LAB_00145db0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      file_info_destroy(plVar13);
    }
  }
  plVar13 = (long *)0x0;
LAB_00145d3c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar13;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

