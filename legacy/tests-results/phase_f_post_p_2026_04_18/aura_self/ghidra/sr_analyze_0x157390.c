
/* WARNING: Type propagation algorithm not settling */

long * sr_analyze(long *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  long *plVar3;
  int iVar4;
  undefined1 auVar5 [16];
  int iVar6;
  int iVar7;
  uint uVar8;
  long *plVar9;
  int *piVar10;
  undefined8 *puVar11;
  int *piVar12;
  void *pvVar13;
  size_t sVar14;
  undefined4 uVar15;
  int iVar16;
  long *plVar17;
  uint uVar18;
  undefined8 *puVar19;
  long lVar20;
  long *plVar21;
  undefined8 *puVar22;
  undefined8 *puVar23;
  int extraout_w18;
  uint uVar24;
  int iVar25;
  long lVar26;
  uint uVar27;
  long lVar28;
  long lVar29;
  uint uVar30;
  undefined1 auVar31 [16];
  long local_c8;
  int local_8c;
  int local_88 [2];
  long local_80;
  long lStack_78;
  long local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == (long *)0x0) || (uVar24 = *(uint *)(param_1 + 1), uVar24 == 0)) ||
     (plVar9 = calloc(1,0x20), plVar9 == (long *)0x0)) {
    plVar9 = (long *)0x0;
  }
  else {
    uVar27 = 0;
    lVar28 = 0;
    do {
      lVar29 = *param_1 + lVar28;
      uVar18 = *(uint *)(lVar29 + 0x10);
      if (uVar18 != 0) {
        lVar26 = 0;
        uVar30 = 0;
        do {
          lVar20 = *(long *)(lVar29 + 8) + lVar26;
          iVar25 = *(int *)(*(long *)(lVar29 + 8) + lVar26);
          if (((iVar25 - 0x15U < 2) && (*(int *)(lVar20 + 0x48) != 0)) &&
             (iVar4 = *(int *)(lVar20 + 0x18), iVar4 != -1)) {
            if (iVar25 == 0x15) {
              iVar25 = *(int *)(lVar20 + 0xc);
joined_r0x001578bc:
              iVar7 = 8;
              if (iVar25 - 1U < 7) {
                iVar7 = *(int *)(&CSWTCH_23 + (ulong)(iVar25 - 1U) * 4);
              }
            }
            else {
              if (*(int *)(lVar20 + 0x48) != 1) {
                iVar25 = *(int *)(lVar20 + 0x2c);
                goto joined_r0x001578bc;
              }
              iVar7 = 8;
              iVar25 = 4;
            }
            local_88[0] = 0;
            local_88[1] = 0xffffffff;
            local_80 = 0;
            local_8c = iVar4;
            iVar6 = analyze_address_part_0_constprop_0_isra_0
                              (*param_1,uVar24,iVar4,&local_8c,&local_80,local_88,local_88 + 1);
            iVar16 = local_88[0];
            iVar4 = local_8c;
            if (iVar6 == 1) {
              uVar24 = *(uint *)(plVar9 + 1);
              piVar10 = (int *)*plVar9;
              if (uVar24 == 0) {
                iVar16 = 1;
                piVar12 = piVar10;
                if (*(int *)((long)plVar9 + 0xc) == 0) {
                  lVar20 = 0;
LAB_00157ad8:
                  sVar14 = 0x300;
                  uVar18 = 8;
                  goto LAB_001579f0;
                }
              }
              else {
                lVar20 = (ulong)uVar24 * 0x60;
                piVar12 = piVar10;
                do {
                  if (local_8c == *piVar12) {
                    sr_add_field(piVar12,local_80,iVar7,iVar25);
                    uVar24 = *(uint *)(param_1 + 1);
                    goto LAB_001574ac;
                  }
                  piVar12 = piVar12 + 0x18;
                } while (piVar10 + (ulong)uVar24 * 0x18 != piVar12);
                uVar18 = *(uint *)((long)plVar9 + 0xc);
                iVar16 = uVar24 + 1;
                piVar12 = piVar10 + (ulong)uVar24 * 0x18;
                if (uVar18 <= uVar24) {
                  if (uVar18 == 0) goto LAB_00157ad8;
                  uVar18 = uVar18 << 1;
                  sVar14 = (ulong)uVar18 * 0x60;
LAB_001579f0:
                  *(uint *)((long)plVar9 + 0xc) = uVar18;
                  pvVar13 = realloc(piVar10,sVar14);
                  *plVar9 = (long)pvVar13;
                  piVar12 = (int *)((long)pvVar13 + lVar20);
                }
              }
              *(int *)(plVar9 + 1) = iVar16;
              piVar12[0x13] = 0;
              piVar12[0x14] = 0;
              piVar12[0x11] = 0;
              piVar12[0x12] = 0;
              piVar12[3] = 0;
              piVar12[4] = 0;
              piVar12[1] = 0;
              piVar12[2] = 0;
              piVar12[7] = 0;
              piVar12[8] = 0;
              piVar12[5] = 0;
              piVar12[6] = 0;
              piVar12[0xb] = 0;
              piVar12[0xc] = 0;
              piVar12[9] = 0;
              piVar12[10] = 0;
              piVar12[0xf] = 0;
              piVar12[0x10] = 0;
              piVar12[0xd] = 0;
              piVar12[0xe] = 0;
              piVar12[0x16] = 0;
              piVar12[0x17] = 0;
              piVar12[0x14] = 0;
              piVar12[0x15] = 0;
              *piVar12 = iVar4;
              __snprintf_chk(piVar12 + 7,0x40,2,0xffffffffffffffff,"struct_%u");
              sr_add_field(piVar12,local_80,iVar7,iVar25);
              uVar24 = *(uint *)(param_1 + 1);
            }
            else if (iVar6 == 2) {
              if (local_88[0] != iVar7) {
                iVar25 = 4;
                if (local_88[0] - 1U < 4) {
                  iVar25 = *(int *)(CSWTCH_25 + (ulong)(local_88[0] - 1U) * 4);
                }
              }
              uVar18 = *(uint *)(plVar9 + 3);
              piVar12 = (int *)plVar9[2];
              piVar10 = piVar12;
              if (uVar18 == 0) {
                iVar7 = 1;
                if (*(int *)((long)plVar9 + 0x1c) == 0) {
                  lVar20 = 0;
                  iVar7 = 1;
LAB_00157a94:
                  sVar14 = 0x80;
                  iVar6 = 8;
                  goto LAB_00157998;
                }
              }
              else {
                lVar20 = (ulong)uVar18 * 0x10;
                do {
                  if ((local_8c == *piVar10) && (local_88[0] == piVar10[1])) {
                    piVar10[3] = piVar10[3] + 1;
                    goto LAB_001574ac;
                  }
                  piVar10 = piVar10 + 4;
                } while (piVar10 != piVar12 + (ulong)uVar18 * 4);
                uVar8 = *(uint *)((long)plVar9 + 0x1c);
                iVar7 = uVar18 + 1;
                if (uVar8 <= uVar18) {
                  if (uVar8 == 0) goto LAB_00157a94;
                  iVar6 = uVar8 << 1;
                  sVar14 = ((ulong)uVar8 & 0x7fffffff) << 5;
LAB_00157998:
                  *(int *)((long)plVar9 + 0x1c) = iVar6;
                  pvVar13 = realloc(piVar12,sVar14);
                  uVar24 = *(uint *)(param_1 + 1);
                  plVar9[2] = (long)pvVar13;
                  piVar10 = (int *)((long)pvVar13 + lVar20);
                }
              }
              *piVar10 = iVar4;
              piVar10[1] = iVar16;
              piVar10[2] = iVar25;
              piVar10[3] = 1;
              *(int *)(plVar9 + 3) = iVar7;
            }
LAB_001574ac:
            uVar18 = *(uint *)(lVar29 + 0x10);
          }
          uVar30 = uVar30 + 1;
          lVar26 = lVar26 + 0x88;
        } while (uVar30 < uVar18);
      }
      uVar27 = uVar27 + 1;
      lVar28 = lVar28 + 0x50;
    } while (uVar27 < uVar24);
    local_c8 = 0;
    uVar27 = 0;
    if (uVar24 != 0) {
      do {
        lVar28 = *param_1 + local_c8;
        uVar18 = *(uint *)(lVar28 + 0x10);
        if (uVar18 != 0) {
          lVar29 = 0;
          uVar30 = 0;
LAB_00157530:
          do {
            lVar26 = *(long *)(lVar28 + 8) + lVar29;
            iVar25 = *(int *)(*(long *)(lVar28 + 8) + lVar29);
            if (((iVar25 - 0x15U < 2) && (iVar4 = *(int *)(lVar26 + 0x48), iVar4 != 0)) &&
               (iVar7 = *(int *)(lVar26 + 0x18), iVar7 != -1)) {
              local_88[0] = 0;
              local_88[1] = 0xffffffff;
              local_80 = 0;
              local_8c = iVar7;
              iVar7 = analyze_address_part_0_constprop_0_isra_0
                                (*param_1,uVar24,iVar7,&local_8c,&local_80,local_88,local_88 + 1);
              if ((iVar7 == 0) && (*(uint *)(plVar9 + 1) != 0)) {
                piVar10 = (int *)*plVar9;
                piVar12 = piVar10 + (ulong)*(uint *)(plVar9 + 1) * 0x18;
                do {
                  if (*piVar10 == extraout_w18) {
                    if (iVar25 == 0x15) {
                      iVar25 = *(int *)(lVar26 + 0xc);
joined_r0x00157978:
                      uVar15 = 8;
                      if (iVar25 - 1U < 7) {
                        uVar15 = *(undefined4 *)(&CSWTCH_23 + (ulong)(iVar25 - 1U) * 4);
                      }
                    }
                    else {
                      if (iVar4 != 1) {
                        iVar25 = *(int *)(lVar26 + 0x2c);
                        goto joined_r0x00157978;
                      }
                      uVar15 = 8;
                      iVar25 = 4;
                    }
                    sr_add_field(piVar10,0,uVar15,iVar25);
                    uVar18 = *(uint *)(lVar28 + 0x10);
                    uVar30 = uVar30 + 1;
                    uVar24 = *(uint *)(param_1 + 1);
                    lVar29 = lVar29 + 0x88;
                    if (uVar18 <= uVar30) goto LAB_00157600;
                    goto LAB_00157530;
                  }
                  piVar10 = piVar10 + 0x18;
                } while (piVar10 != piVar12);
              }
            }
            uVar30 = uVar30 + 1;
            lVar29 = lVar29 + 0x88;
          } while (uVar30 < uVar18);
        }
LAB_00157600:
        local_c8 = local_c8 + 0x50;
        uVar27 = uVar27 + 1;
      } while (uVar27 < uVar24);
    }
    if (*(uint *)(plVar9 + 1) != 0) {
      puVar23 = (undefined8 *)(*plVar9 + 8) + (ulong)*(uint *)(plVar9 + 1) * 0xc;
      puVar22 = (undefined8 *)(*plVar9 + 8);
      do {
        while (uVar24 = *(uint *)(puVar22 + 1), uVar24 != 0) {
          uVar27 = uVar24 - 1;
          puVar19 = (undefined8 *)*puVar22;
          if (uVar27 < 4) {
            uVar18 = 0;
            uVar30 = 0;
          }
          else {
            auVar31 = ZEXT816(0);
            puVar11 = puVar19;
            do {
              puVar1 = puVar11 + 0xc;
              auVar5._4_4_ = *(int *)(puVar11 + 4) + (int)puVar11[3];
              auVar5._0_4_ = *(int *)(puVar11 + 1) + (int)*puVar11;
              auVar5._8_4_ = *(int *)(puVar11 + 7) + (int)puVar11[6];
              auVar5._12_4_ = *(int *)(puVar11 + 10) + (int)puVar11[9];
              auVar31 = NEON_umax(auVar31,auVar5,4);
              puVar11 = puVar1;
            } while (puVar1 != puVar19 + (ulong)(uVar27 >> 2) * 0xc);
            uVar30 = NEON_umaxv(auVar31,4);
            uVar18 = uVar27 & 0xfffffffc;
          }
          uVar8 = uVar18 + 1;
          uVar2 = *(int *)(puVar19 + (ulong)uVar18 * 3 + 1) + (int)puVar19[(ulong)uVar18 * 3];
          if (uVar2 < uVar30) {
            uVar2 = uVar30;
          }
          if (uVar8 < uVar24) {
            uVar30 = uVar18 + 2;
            uVar8 = *(int *)(puVar19 + (ulong)uVar8 * 3 + 1) + (int)puVar19[(ulong)uVar8 * 3];
            if (uVar8 < uVar2) {
              uVar8 = uVar2;
            }
            if (uVar30 < uVar24) {
              uVar18 = uVar18 + 3;
              uVar30 = *(int *)(puVar19 + (ulong)uVar30 * 3 + 1) + (int)puVar19[(ulong)uVar30 * 3];
              if (uVar8 < uVar30) {
                uVar8 = uVar30;
              }
              if ((uVar18 < uVar24) &&
                 (uVar24 = *(int *)(puVar19 + (ulong)uVar18 * 3 + 1) +
                           (int)puVar19[(ulong)uVar18 * 3], uVar8 < uVar24)) {
                uVar8 = uVar24;
              }
            }
            *(uint *)(puVar22 + 2) = uVar8;
LAB_0015774c:
            plVar21 = puVar19 + 3;
            uVar24 = 0;
            do {
              local_80 = *plVar21;
              lStack_78 = plVar21[1];
              local_70 = plVar21[2];
              lVar28 = *plVar21;
              uVar18 = uVar24 + 1;
              if ((int)uVar24 < 0) {
                plVar17 = puVar19 + (long)(int)uVar18 * 3;
              }
              else {
                lVar29 = (ulong)uVar24 * 0x18;
                do {
                  if (*(long *)((long)puVar19 + lVar29) <= lVar28) {
                    plVar17 = puVar19 + (long)(int)(uVar24 + 1) * 3;
                    break;
                  }
                  plVar17 = (long *)((long)puVar19 + lVar29);
                  plVar3 = (long *)((long)(puVar19 + 3) + lVar29);
                  uVar24 = uVar24 - 1;
                  lVar29 = lVar29 + -0x18;
                  lVar26 = plVar17[1];
                  *plVar3 = *plVar17;
                  plVar3[1] = lVar26;
                  plVar3[2] = plVar17[2];
                } while (uVar24 != 0xffffffff);
              }
              *plVar17 = local_80;
              plVar17[1] = lStack_78;
              plVar21 = plVar21 + 3;
              plVar17[2] = local_70;
              uVar24 = uVar18;
            } while (uVar18 != uVar27);
          }
          else {
            *(uint *)(puVar22 + 2) = uVar2;
            if (uVar24 != 1) goto LAB_0015774c;
          }
          puVar22 = puVar22 + 0xc;
          if (puVar22 == puVar23) goto LAB_001577f8;
        }
        puVar19 = puVar22 + 0xc;
        *(undefined4 *)(puVar22 + 2) = 0;
        puVar22 = puVar19;
      } while (puVar19 != puVar23);
    }
  }
LAB_001577f8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar9;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

