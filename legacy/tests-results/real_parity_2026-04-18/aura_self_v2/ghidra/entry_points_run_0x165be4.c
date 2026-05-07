
void entry_points_run(long *param_1)

{
  uint uVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  long *__ptr;
  undefined8 uVar5;
  char *pcVar6;
  long *plVar7;
  undefined8 *puVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  undefined8 *in_x4;
  long lVar14;
  ulong extraout_x9;
  ulong extraout_x10;
  ulong extraout_x10_00;
  ulong extraout_x11;
  ulong extraout_x11_00;
  undefined8 *puVar15;
  ulong uVar16;
  long *plVar17;
  long lVar18;
  uint uVar19;
  ulong uVar20;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  long *local_a8;
  undefined8 local_a0;
  undefined1 auStack_98 [48];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0) {
LAB_00165c64:
    uVar5 = 1;
  }
  else {
    __ptr = calloc(0x10,0x18);
    local_a8 = __ptr;
    if (__ptr != (long *)0x0) {
      local_a0 = DAT_00209d78;
      if (param_1[2] == 0) {
        if ((int)param_1[1] == 1) {
          uVar19 = 0;
          goto LAB_00165cd8;
        }
        if ((int)param_1[1] == 2) {
          uVar19 = 0;
          goto LAB_00165d60;
        }
LAB_00165c58:
        free(__ptr);
        goto LAB_00165c64;
      }
      *__ptr = param_1[2];
      *(undefined4 *)(__ptr + 1) = 0;
      pcVar6 = strdup("main_entry");
      lVar18 = param_1[1];
      __ptr[2] = (long)pcVar6;
      local_a0 = CONCAT44(local_a0._4_4_,1);
      uVar19 = 1;
      if ((int)lVar18 == 1) {
LAB_00165cd8:
        uVar11 = *(ulong *)(*param_1 + 0x10);
        if ((((4 < uVar11) && (pcVar6 = *(char **)(*param_1 + 8), *pcVar6 == '\x7f')) &&
            (pcVar6[1] == 'E')) && ((pcVar6[2] == 'L' && (pcVar6[3] == 'F')))) {
          if (pcVar6[4] == '\x01') {
            if (uVar11 == 5) {
              lVar18 = 4;
              uVar11 = 8;
              uVar5 = 4;
              bVar3 = true;
            }
            else {
              lVar18 = 4;
              uVar5 = 4;
              uVar11 = 8;
              bVar3 = pcVar6[5] == '\x01';
            }
          }
          else {
            if (pcVar6[4] != '\x02') goto LAB_00165d08;
            if (uVar11 == 5) {
              lVar18 = 8;
              uVar11 = 0x10;
              uVar5 = 8;
              bVar3 = true;
            }
            else {
              lVar18 = 8;
              uVar11 = 0x10;
              uVar5 = 8;
              bVar3 = pcVar6[5] == '\x01';
            }
          }
          collect_elf_array_section(param_1,".init_array",1,".init_array",uVar5,bVar3,&local_a8);
          collect_elf_array_section(param_1,".fini_array",2,".fini_array",uVar5,bVar3,&local_a8);
          puVar8 = (undefined8 *)param_1[3];
          if (*(uint *)(param_1 + 4) != 0) {
            puVar15 = puVar8 + (ulong)*(uint *)(param_1 + 4) * 7;
            do {
              if (((char *)*puVar8 != (char *)0x0) &&
                 (iVar4 = strcmp((char *)*puVar8,".dynamic"), iVar4 == 0)) {
                if ((puVar8[5] != 0) && (uVar9 = puVar8[3], uVar9 != 0)) {
                  uVar20 = 0;
                  if (uVar11 != 0) {
                    uVar20 = uVar9 / uVar11;
                  }
                  if (uVar11 <= uVar9) {
                    uVar16 = 0;
                    uVar13 = 0;
                    goto LAB_00165fc0;
                  }
                }
                break;
              }
              puVar8 = puVar8 + 7;
            } while (puVar8 != puVar15);
          }
LAB_00165f48:
          __ptr = local_a8;
          uVar19 = (uint)local_a0;
        }
LAB_00165d08:
        if (uVar19 == 0) goto LAB_00165c58;
      }
      else {
        uVar19 = 1;
        if ((int)lVar18 == 2) {
LAB_00165d60:
          uVar11 = *(ulong *)(*param_1 + 0x10);
          if (0x3f < uVar11) {
            lVar18 = *(long *)(*param_1 + 8);
            uVar1 = *(uint *)(lVar18 + 0x3c);
            if (((((ulong)uVar1 <= uVar11 - 4) && (*(int *)(lVar18 + (ulong)uVar1) == 0x4550)) &&
                (uVar9 = (ulong)(uVar1 + 4), uVar9 <= uVar11 - 0x14)) &&
               ((uVar20 = uVar9 + 0x14, uVar20 <= uVar11 - 2 &&
                (sVar2 = *(short *)(lVar18 + uVar20), (sVar2 - 0x10bU & 0xfeff) == 0)))) {
              if (sVar2 == 0x20b) {
                if (uVar9 + 0x2c <= uVar11 - 8) {
                  lVar12 = 0x70;
                  le64(lVar18 + uVar9 + 0x2c);
                  uVar11 = extraout_x11_00;
                  goto LAB_00165dec;
                }
              }
              else if (uVar9 + 0x30 <= uVar11 - 4) {
                uVar11 = uVar11 - 8;
                lVar12 = 0x60;
LAB_00165dec:
                uVar9 = uVar20 + lVar12 + 0x48;
                if ((uVar9 <= uVar11) &&
                   (*(int *)(lVar18 + uVar20 + lVar12 + 0x4c) != 0 && *(int *)(lVar18 + uVar9) != 0)
                   ) {
                  auVar21 = pe_rva_to_offset_raw(lVar18);
                  lVar12 = auVar21._0_8_;
                  if (lVar12 != 0) {
                    if (sVar2 == 0x20b) {
                      if (lVar12 + 0x18U <= extraout_x11) {
                        auVar22 = le64(lVar18 + lVar12 + 0x18U);
                        uVar11 = extraout_x10_00;
                        goto LAB_00165e38;
                      }
                    }
                    else if (lVar12 + 0xcU <= extraout_x9) {
                      auVar22._4_4_ = 0;
                      auVar22._0_4_ = *(uint *)(lVar18 + lVar12 + 0xcU);
                      auVar22._8_8_ = auVar21._8_8_;
                      uVar11 = extraout_x10;
LAB_00165e38:
                      if (auVar22._0_8_ != 0 && uVar11 <= auVar22._0_8_) {
                        auVar21 = pe_rva_to_offset_raw
                                            (lVar18,auVar22._8_8_,auVar22._0_4_ - (int)uVar11);
                        uVar11 = auVar21._0_8_;
                        if (uVar11 != 0) {
                          lVar12 = 4;
                          if (sVar2 == 0x20b) {
                            lVar12 = 8;
                          }
                          uVar9 = auVar21._8_8_ - lVar12;
                          if (uVar11 <= uVar9) {
                            iVar4 = 0;
                            do {
                              if (sVar2 == 0x20b) {
                                uVar20 = le64(lVar18 + uVar11);
                              }
                              else {
                                uVar20 = (ulong)*(uint *)(lVar18 + uVar11);
                              }
                              if (uVar20 == 0) break;
                              __snprintf_chk(auStack_98,0x30,2,0x30,"TLS_CALLBACK[%d]",iVar4);
                              iVar4 = iVar4 + 1;
                              elist_add_isra_0(&local_a8,uVar20,5,auStack_98);
                              if (iVar4 == 0x100) goto LAB_00165f48;
                              uVar11 = uVar11 + lVar12;
                            } while (uVar11 <= uVar9);
                          }
                          __ptr = local_a8;
                          uVar19 = (uint)local_a0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          goto LAB_00165d08;
        }
      }
      plVar7 = realloc(__ptr,(ulong)uVar19 * 0x18);
      if (plVar7 != (long *)0x0) {
        __ptr = plVar7;
        local_a8 = plVar7;
      }
      puVar8 = malloc(0x10);
      if (puVar8 != (undefined8 *)0x0) {
        uVar5 = 0;
        *in_x4 = puVar8;
        *puVar8 = __ptr;
        *(uint *)(puVar8 + 1) = uVar19;
        goto LAB_00165c68;
      }
      plVar7 = __ptr + 2;
      do {
        plVar17 = plVar7 + 3;
        free((void *)*plVar7);
        plVar7 = plVar17;
      } while (__ptr + (ulong)uVar19 * 3 + 2 != plVar17);
      free(__ptr);
    }
    uVar5 = 2;
  }
LAB_00165c68:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_00165fc0:
  if (uVar9 < uVar13 + uVar11) goto LAB_00165f48;
  lVar14 = puVar8[5];
  lVar12 = uVar13 + lVar18;
  lVar10 = read_elf_ptr(lVar14 + uVar13,uVar5,bVar3,lVar12);
  lVar12 = read_elf_ptr(lVar14 + lVar12,uVar5);
  if (lVar10 == 0) goto LAB_00165f48;
  if (lVar12 == 0 || lVar10 != 0xc) {
    if (lVar12 != 0 && lVar10 == 0xd) {
      elist_add_isra_0(&local_a8,lVar12,4,"DT_FINI");
    }
  }
  else {
    elist_add_isra_0(&local_a8,lVar12,3,"DT_INIT");
  }
  uVar16 = uVar16 + 1;
  if (uVar20 <= uVar16) goto LAB_00165f48;
  uVar9 = puVar8[3];
  uVar13 = uVar13 + uVar11;
  goto LAB_00165fc0;
}

