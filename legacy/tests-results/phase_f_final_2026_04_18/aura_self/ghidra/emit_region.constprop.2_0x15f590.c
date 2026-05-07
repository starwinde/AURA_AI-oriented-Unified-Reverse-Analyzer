
void emit_region_constprop_2
               (long *param_1,uint param_2,uint param_3,long param_4,undefined8 *param_5,
               long param_6,undefined8 param_7,long param_8,FILE *param_9)

{
  char *pcVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  int *piVar11;
  void *pvVar12;
  char *pcVar13;
  size_t __n;
  long lVar14;
  uint extraout_w11;
  long lVar15;
  long extraout_x12;
  uint uVar16;
  ulong uVar17;
  uint uVar18;
  uint uVar19;
  ulong uVar20;
  long lVar21;
  long lVar22;
  int *piVar23;
  ulong local_c8;
  uint local_80 [2];
  undefined8 *local_78;
  long *plStack_70;
  long local_68;
  
  uVar16 = *(uint *)(param_1 + 1);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  local_c8 = (ulong)param_2;
  if (param_3 != param_2 && param_2 < uVar16) {
LAB_0015f600:
    if ((*(byte *)(param_8 + local_c8) & 1) != 0) goto LAB_0015f740;
    lVar15 = *param_1;
    *(undefined1 *)(param_8 + local_c8) = 1;
    lVar21 = lVar15 + local_c8 * 0x50;
    uVar5 = *(uint *)(lVar21 + 0x10) - 1;
    uVar18 = (uint)local_c8;
    if ((int)uVar5 < 0) {
      if (((*(byte *)(param_4 + local_c8) & 1) == 0) || (param_5 == (undefined8 *)0x0)) {
        piVar23 = (int *)0x0;
      }
      else {
        uVar5 = *(uint *)(param_5 + 1);
        piVar23 = (int *)0x0;
        if (uVar5 != 0) goto LAB_0015f690;
      }
    }
    else {
      piVar23 = (int *)(*(long *)(lVar21 + 8) + (long)(int)uVar5 * 0x88);
      do {
        if (*piVar23 - 0x17U < 2 || *piVar23 == 0x1a) goto LAB_0015f678;
        piVar23 = piVar23 + -0x22;
      } while ((int *)(*(long *)(lVar21 + 8) + -0x110 +
                      ((ulong)*(uint *)(lVar21 + 0x10) - (ulong)uVar5) * 0x88) != piVar23);
      piVar23 = (int *)0x0;
LAB_0015f678:
      if ((*(byte *)(param_4 + local_c8) & 1) != 0) {
        if ((param_5 == (undefined8 *)0x0) || (uVar5 = *(uint *)(param_5 + 1), uVar5 == 0)) {
          if (piVar23 != (int *)0x0) {
            if (*piVar23 == 0x17) {
              uVar20 = (ulong)(uint)piVar23[0x19];
              uVar16 = piVar23[0x1a];
              cf_emit_block_body_part_0_isra_0(lVar15,local_c8,param_9,3);
LAB_0016106c:
              uVar19 = *(uint *)(param_1 + 1);
              uVar5 = (uint)uVar20;
              uVar17 = uVar20;
              uVar4 = uVar16;
              if (uVar5 < uVar19) {
                lVar15 = *param_1;
                if (uVar5 != uVar18) {
                  puVar10 = (uint *)0x0;
LAB_001610f0:
                  uVar5 = 0;
                  uVar17 = uVar20;
                  do {
                    uVar4 = *(uint *)(lVar15 + uVar17 * 0x50 + 0x34);
                    if ((uVar4 == (uint)uVar17) || (uVar5 = uVar5 + 1, uVar19 < uVar5)) {
                      if (uVar16 < uVar19) {
                        if (uVar16 != uVar18) goto LAB_00160c98;
                        uVar16 = (uint)uVar20;
                        uVar20 = local_c8;
                      }
                      break;
                    }
                    uVar17 = (ulong)uVar4;
                  } while (uVar4 != uVar18);
joined_r0x00161140:
                  uVar17 = uVar20;
                  uVar4 = uVar16;
                  if (puVar10 != (uint *)0x0) goto LAB_001607ac;
                }
LAB_00160cd4:
                iVar6 = 0xc;
                do {
                  fputc(0x20,param_9);
                  iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
                fwrite("while (",1,7,param_9);
                if (piVar23[0x12] == 0) {
                  fwrite(&DAT_001f9880,1,4,param_9);
                }
                else if (piVar23[6] == -1) {
                  fwrite("__undef",1,7,param_9);
                }
                else {
                  __fprintf_chk(param_9,2,&DAT_001f9928);
                }
                fwrite(&DAT_001f9a38,1,4,param_9);
              }
              else {
                if ((uVar19 <= uVar16) ||
                   (lVar15 = *param_1, uVar17 = local_c8, uVar4 = uVar5, uVar16 == uVar18))
                goto LAB_00160cd4;
                puVar10 = (uint *)0x0;
LAB_00160c98:
                uVar5 = 0;
                uVar4 = uVar16;
                do {
                  uVar9 = *(uint *)(lVar15 + (ulong)uVar4 * 0x50 + 0x34);
                  if ((uVar9 == uVar4) || (uVar5 = uVar5 + 1, uVar19 < uVar5))
                  goto joined_r0x00161140;
                  uVar4 = uVar9;
                } while (uVar9 != uVar18);
                uVar17 = (ulong)uVar16;
                uVar4 = (uint)uVar20;
                if (puVar10 == (uint *)0x0) goto LAB_00160cd4;
LAB_001607ac:
                if ((puVar10[6] != 3) || (iVar6 = 0xc, (puVar10[0x11] & 1) == 0)) goto LAB_00160cd4;
                do {
                  fputc(0x20,param_9);
                  iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
                __fprintf_chk(param_9,2,"for (v%u = v%u; ",puVar10[8],puVar10[9]);
                __fprintf_chk(param_9,2,&DAT_001f9928,puVar10[8]);
                uVar16 = puVar10[0x10];
                if (uVar16 == 0x10) {
LAB_0016122c:
                  fwrite(&DAT_001f99f0,1,4,param_9);
                }
                else if (uVar16 < 0x11) {
                  if (uVar16 != 0xd) {
                    if (uVar16 < 0xe) {
                      if (uVar16 == 0xb) {
                        fwrite(&DAT_001f9a10,1,4,param_9);
                      }
                      else {
                        if (uVar16 != 0xc) goto LAB_0016145c;
                        fwrite(&DAT_001f9a08,1,4,param_9);
                      }
                      goto LAB_00160864;
                    }
                    if (uVar16 == 0xe) goto LAB_0016122c;
                  }
                  fwrite(&DAT_001f99e8,1,3,param_9);
                }
                else if (uVar16 == 0x13) {
LAB_00161248:
                  fwrite(&DAT_001f99f8,1,3,param_9);
                }
                else {
                  if (uVar16 < 0x14) {
                    if (uVar16 == 0x11) goto LAB_00161248;
                  }
                  else if (uVar16 != 0x14) {
LAB_0016145c:
                    fwrite(&DAT_001f9958,1,3,param_9);
                    goto LAB_00160864;
                  }
                  fwrite(&DAT_001f9a00,1,4,param_9);
                }
LAB_00160864:
                __fprintf_chk(param_9,2,"v%u; ",puVar10[0xf]);
                __fprintf_chk(param_9,2,&DAT_001f9928,puVar10[8]);
                if (puVar10[0xe] == 2) {
                  fwrite(&DAT_001f9a20,1,4,param_9);
                }
                else {
                  fwrite(&DAT_001f9a28,1,4,param_9);
                }
                __fprintf_chk(param_9,2,"%ldLL",*(undefined8 *)(puVar10 + 0xc));
                fwrite(&DAT_001f9a38,1,4,param_9);
              }
              pvVar12 = calloc((ulong)*(uint *)(param_1 + 1),1);
              if (pvVar12 != (void *)0x0) {
                *(undefined1 *)((long)pvVar12 + local_c8) = 1;
                emit_region_constprop_3
                          (param_1,uVar17,local_c8,param_4,param_5,param_6,param_7,pvVar12,param_9);
                free(pvVar12);
              }
              iVar6 = 0xc;
              do {
                fputc(0x20,param_9);
                iVar6 = iVar6 + -1;
              } while (iVar6 != 0);
              fwrite(&DAT_001f8e68,1,2,param_9);
              uVar16 = *(uint *)(param_1 + 1);
              if (uVar16 <= uVar4 || param_3 == uVar4) goto LAB_0015f740;
              local_c8 = (ulong)uVar4;
              goto LAB_0015f600;
            }
            if (*piVar23 == 0x18) {
              puVar10 = (uint *)0x0;
LAB_0016013c:
              uVar5 = find_latch(param_1,local_c8);
              lVar15 = extraout_x12;
              uVar16 = extraout_w11;
              if (uVar5 < extraout_w11) goto LAB_0015fbf4;
            }
          }
        }
        else {
LAB_0015f690:
          uVar4 = 0;
          puVar10 = (uint *)*param_5;
          do {
            if (*puVar10 == uVar18) goto LAB_0015f6c0;
            uVar4 = uVar4 + 1;
            puVar10 = puVar10 + 0x18;
          } while (uVar4 < uVar5);
          puVar10 = (uint *)0x0;
LAB_0015f6c0:
          if (piVar23 != (int *)0x0) {
            if (*piVar23 == 0x17) {
              uVar5 = piVar23[0x19];
              uVar20 = (ulong)uVar5;
              uVar16 = piVar23[0x1a];
              cf_emit_block_body_part_0_isra_0(lVar15,local_c8,param_9,3);
              if (puVar10 == (uint *)0x0) goto LAB_0016106c;
              uVar4 = puVar10[5];
              uVar19 = *(uint *)(param_1 + 1);
              if (uVar4 < uVar19) {
                if (uVar5 == uVar4) {
                  uVar5 = uVar16;
                }
                uVar17 = (ulong)uVar5;
              }
              else {
                uVar17 = uVar20;
                uVar4 = uVar16;
                if (uVar5 < uVar19) {
                  lVar15 = *param_1;
                  if (uVar5 != uVar18) goto LAB_001610f0;
                }
                else if ((uVar16 < uVar19) &&
                        (lVar15 = *param_1, uVar17 = local_c8, uVar4 = uVar5, uVar16 != uVar18))
                goto LAB_00160c98;
              }
              goto LAB_001607ac;
            }
            if (*piVar23 == 0x18) {
              if ((puVar10 == (uint *)0x0) || (uVar5 = puVar10[1], uVar16 <= uVar5))
              goto LAB_0016013c;
LAB_0015fbf4:
              if (uVar5 != uVar18) {
                lVar15 = lVar15 + (ulong)uVar5 * 0x50;
                uVar4 = *(uint *)(lVar15 + 0x10);
                uVar19 = uVar4 - 1;
                if (-1 < (int)uVar19) {
                  lVar15 = *(long *)(lVar15 + 8);
                  piVar11 = (int *)(lVar15 + (long)(int)uVar19 * 0x88);
                  do {
                    if (*piVar11 - 0x17U < 2 || *piVar11 == 0x1a) {
                      if ((((puVar10 == (uint *)0x0) || (uVar4 = puVar10[5], uVar16 <= puVar10[5]))
                          && (uVar4 = uVar16, *piVar11 == 0x17)) &&
                         (uVar4 = piVar11[0x19], piVar11[0x19] == uVar18)) {
                        uVar4 = piVar11[0x1a];
                      }
                      goto LAB_0015fc7c;
                    }
                    piVar11 = piVar11 + -0x22;
                  } while (piVar11 !=
                           (int *)(lVar15 + -0x110 + ((ulong)uVar4 - (ulong)uVar19) * 0x88));
                }
                if (puVar10 == (uint *)0x0) {
                  piVar11 = (int *)0x0;
                  uVar4 = uVar16;
                }
                else {
                  piVar11 = (int *)0x0;
                  uVar4 = puVar10[5];
                  if (uVar16 < puVar10[5]) {
                    uVar4 = uVar16;
                  }
                }
LAB_0015fc7c:
                iVar6 = 0xc;
                do {
                  fputc(0x20,param_9);
                  iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
                fwrite("do {\n",1,5,param_9);
                uVar16 = *(uint *)(param_1 + 1);
                if (uVar18 < uVar16) {
                  cf_emit_block_body_part_0_isra_0(*param_1,local_c8,param_9,4);
                  uVar16 = *(uint *)(param_1 + 1);
                }
                uVar18 = piVar23[0x19];
                if ((uVar18 != uVar5) && (pvVar12 = calloc((ulong)uVar16,1), pvVar12 != (void *)0x0)
                   ) {
                  *(undefined1 *)((long)pvVar12 + local_c8) = 1;
                  emit_region_constprop_3
                            (param_1,uVar18,uVar5,param_4,param_5,param_6,param_7,pvVar12,param_9);
                  free(pvVar12);
                  uVar16 = *(uint *)(param_1 + 1);
                }
                if (uVar5 < uVar16) {
                  cf_emit_block_body_part_0_isra_0(*param_1,uVar5,param_9,4);
                }
                iVar6 = 0xc;
                do {
                  fputc(0x20,param_9);
                  iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
                fwrite("} while (",1,9,param_9);
                if ((piVar11 == (int *)0x0) || (piVar11[0x12] == 0)) {
                  fwrite(&DAT_001f9880,1,4,param_9);
                }
                else if (piVar11[6] == -1) {
                  fwrite("__undef",1,7,param_9);
                }
                else {
                  __fprintf_chk(param_9,2,&DAT_001f9928);
                }
                fwrite(&DAT_001f99a8,1,3,param_9);
                uVar16 = *(uint *)(param_1 + 1);
                if (uVar16 <= uVar4 || param_3 == uVar4) goto LAB_0015f740;
                local_c8 = (ulong)uVar4;
                goto LAB_0015f600;
              }
            }
          }
        }
      }
    }
    cf_emit_block_body_part_0_isra_0(lVar15,local_c8,param_9,3);
    piVar11 = (int *)sr_is_switch_head(param_7,local_c8);
    if ((piVar11 != (int *)0x0) && (piVar11[4] != 0)) {
      iVar6 = piVar11[8];
      if (iVar6 != 0) {
        uVar16 = *(uint *)(param_1 + 1);
        iVar7 = 0;
        while ((uint)local_c8 < uVar16) {
          lVar15 = *param_1;
          *(undefined1 *)(param_8 + local_c8) = 1;
          lVar15 = lVar15 + local_c8 * 0x50;
          uVar5 = *(uint *)(lVar15 + 0x10);
          uVar4 = uVar5 - 1;
          if ((int)uVar4 < 0) break;
          lVar15 = *(long *)(lVar15 + 8);
          piVar23 = (int *)(lVar15 + (long)(int)uVar4 * 0x88);
          while (iVar8 = *piVar23, 1 < iVar8 - 0x17U && iVar8 != 0x1a) {
            piVar23 = piVar23 + -0x22;
            if (piVar23 == (int *)(lVar15 + -0x110 + ((ulong)uVar5 - (ulong)uVar4) * 0x88))
            goto LAB_00160478;
          }
          if (iVar8 != 0x17) break;
          iVar7 = iVar7 + 1;
          local_c8 = (ulong)(uint)piVar23[0x1a];
          if (iVar7 == iVar6) break;
        }
      }
LAB_00160478:
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fwrite("switch (",1,8,param_9);
      if (*piVar11 == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      fwrite(&DAT_001f9a38,1,4,param_9);
      lVar15 = 0;
      if (piVar11[4] != 0) {
        do {
          lVar22 = *(long *)(piVar11 + 2);
          iVar6 = 0xc;
          lVar21 = lVar22 + lVar15 * 0x10;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          if ((*(byte *)(lVar21 + 0xc) & 1) == 0) {
            __fprintf_chk(param_9,2,"case %ld:\n",*(undefined8 *)(lVar22 + lVar15 * 0x10));
            uVar16 = *(uint *)(param_1 + 1);
            uVar5 = *(uint *)(lVar21 + 8);
            if (uVar5 < uVar16) goto LAB_001605f4;
LAB_00160568:
            bVar2 = *(byte *)(lVar21 + 0xd);
          }
          else {
            fwrite("default:\n",1,9,param_9);
            uVar16 = *(uint *)(param_1 + 1);
            uVar5 = *(uint *)(lVar21 + 8);
            if (uVar16 <= uVar5) goto LAB_00160568;
LAB_001605f4:
            pvVar12 = calloc((ulong)uVar16,1);
            if (pvVar12 == (void *)0x0) goto LAB_00160568;
            uVar4 = piVar11[8];
            if (uVar4 != 0 && uVar18 < uVar16) {
              lVar22 = *param_1;
              uVar19 = 0;
              uVar9 = uVar18;
              while( true ) {
                lVar14 = lVar22 + (ulong)uVar9 * 0x50;
                *(undefined1 *)((long)pvVar12 + (ulong)uVar9) = 1;
                uVar9 = *(uint *)(lVar14 + 0x10);
                uVar3 = uVar9 - 1;
                if ((int)uVar3 < 0) break;
                lVar14 = *(long *)(lVar14 + 8);
                piVar23 = (int *)(lVar14 + (long)(int)uVar3 * 0x88);
                while (iVar6 = *piVar23, 1 < iVar6 - 0x17U && iVar6 != 0x1a) {
                  piVar23 = piVar23 + -0x22;
                  if (piVar23 == (int *)(lVar14 + -0x110 + ((ulong)uVar9 - (ulong)uVar3) * 0x88))
                  goto LAB_001606b0;
                }
                if (iVar6 != 0x17) break;
                uVar9 = piVar23[0x1a];
                uVar19 = uVar19 + 1;
                if (uVar4 <= uVar19 || uVar16 <= uVar9) break;
              }
            }
LAB_001606b0:
            emit_region(param_1,uVar5,param_3,param_4,param_5,param_6,param_7,pvVar12,param_9,5);
            free(pvVar12);
            bVar2 = *(byte *)(lVar21 + 0xd);
          }
          if ((bVar2 & 1) == 0) {
            iVar6 = 0x10;
            do {
              fputc(0x20,param_9);
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
            fwrite("break;\n",1,7,param_9);
          }
          lVar15 = lVar15 + 1;
        } while ((uint)lVar15 < (uint)piVar11[4]);
      }
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fwrite(&DAT_001f8e68,1,2,param_9);
      uVar16 = *(uint *)(param_1 + 1);
      uVar5 = piVar11[6];
      if (uVar5 < uVar16 && param_3 != uVar5) goto LAB_00160080;
      goto LAB_0015f740;
    }
    if (2 < *(uint *)(lVar21 + 0x30)) {
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fwrite("switch (expr) {\n",1,0x10,param_9);
      if (*(int *)(lVar21 + 0x30) != 0) {
        uVar20 = 0;
        do {
          iVar6 = 0xc;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          if (*(int *)(lVar21 + 0x30) + -1 == (int)uVar20) {
            fwrite("default:\n",1,9,param_9);
          }
          else {
            __fprintf_chk(param_9,2,"case %u:\n",uVar20 & 0xffffffff);
          }
          uVar16 = *(uint *)(param_1 + 1);
          uVar5 = *(uint *)(*(long *)(lVar21 + 0x28) + uVar20 * 4);
          pvVar12 = calloc((ulong)uVar16,1);
          if (pvVar12 != (void *)0x0) {
            *(undefined1 *)((long)pvVar12 + local_c8) = 1;
            if ((uVar5 < uVar16) && ((*(byte *)(param_8 + (ulong)uVar5) & 1) == 0)) {
              emit_region(param_1,uVar5,param_3,param_4,param_5,param_6,param_7,pvVar12,param_9,5);
            }
            free(pvVar12);
          }
          iVar6 = 0x10;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          fwrite("break;\n",1,7,param_9);
          uVar20 = uVar20 + 1;
        } while ((uint)uVar20 < *(uint *)(lVar21 + 0x30));
      }
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      lVar15 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
      if (lVar15 == 0) {
        pcVar13 = "}\n";
LAB_00160044:
        fwrite(pcVar13,1,2,param_9);
        return;
      }
      goto LAB_00161554;
    }
    if (piVar23 == (int *)0x0) goto LAB_0015f740;
    iVar6 = *piVar23;
    if (iVar6 == 0x18) {
      uVar5 = piVar23[0x19];
      uVar16 = *(uint *)(param_1 + 1);
      if (param_3 != uVar5 && uVar5 < uVar16) goto LAB_00160080;
      goto LAB_0015f740;
    }
    if (iVar6 == 0x1a) {
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fwrite("return ",1,7,param_9);
      if ((piVar23[0x19] == -1) && (1 < (uint)piVar23[0x12])) {
        if (*(long *)(piVar23 + 0xc) == 0) {
          fwrite("call(",1,5,param_9);
        }
        else {
          __fprintf_chk(param_9,2,"sub_%lx(");
        }
        lVar15 = 0;
        if (piVar23[0x18] != 0) {
          do {
            uVar16 = (uint)lVar15;
            while( true ) {
              if (uVar16 != 0) {
                fwrite(", ",1,2,param_9);
              }
              if (*(int *)(*(long *)(piVar23 + 0x14) + lVar15 * 0x10) != -1) break;
              fwrite("__undef",1,7,param_9);
              lVar15 = lVar15 + 1;
              uVar16 = (uint)lVar15;
              if ((uint)piVar23[0x18] <= uVar16) goto LAB_00160110;
            }
            __fprintf_chk(param_9,2,&DAT_001f9928);
            lVar15 = lVar15 + 1;
          } while ((uint)lVar15 < (uint)piVar23[0x18]);
        }
LAB_00160110:
        fputc(0x29,param_9);
      }
      else if ((piVar23[0x12] == 0) || (piVar23[6] == -1)) {
        fputc(0x30,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      lVar15 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
      if (lVar15 == 0) {
        pcVar13 = ";\n";
        goto LAB_00160044;
      }
      goto LAB_00161554;
    }
    if (iVar6 != 0x17) goto LAB_0015f740;
    uVar16 = piVar23[0x19];
    uVar5 = piVar23[0x1a];
    if ((param_5 == (undefined8 *)0x0) || (*(uint *)(param_1 + 1) <= param_3)) {
LAB_0015f79c:
      if (param_6 == 0) {
        uVar18 = *(uint *)(param_1 + 1);
LAB_001602d0:
        uVar4 = find_join_isra_0(*param_1,uVar18,uVar16,uVar5);
        if (uVar4 < uVar18) goto LAB_0015f7bc;
        local_80[0] = uVar18;
        local_78 = param_5;
        plStack_70 = param_1;
        iVar7 = ge_classify_edge(local_80,local_c8,uVar16);
        iVar8 = ge_classify_edge(local_80,local_c8,uVar5);
        iVar6 = 0xc;
        do {
          fputc(0x20,param_9);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        fwrite(&DAT_001f9ad8,1,4,param_9);
        if (piVar23[0x12] == 0) {
          fwrite(&DAT_001f9880,1,4,param_9);
        }
        else if (piVar23[6] == -1) {
          fwrite("__undef",1,7,param_9);
        }
        else {
          __fprintf_chk(param_9,2,&DAT_001f9928);
        }
        if (iVar7 == 1) {
          fwrite(") break;",1,8,param_9);
        }
        else if (iVar7 == 2) {
          fwrite(") continue;",1,0xb,param_9);
        }
        else {
          __fprintf_chk(param_9,2,") goto bb%u;",uVar16);
        }
        if (iVar8 == 1) {
          pcVar13 = " else break;\n";
          __n = 0xd;
        }
        else {
          if (iVar8 != 2) {
            __fprintf_chk(param_9,2," else goto bb%u;\n",uVar5);
            goto LAB_0015f740;
          }
          pcVar13 = " else continue;\n";
          __n = 0x10;
        }
        fwrite(pcVar13,1,__n,param_9);
        goto LAB_0015f740;
      }
      uVar4 = sa_find_join(param_6,param_1,local_c8);
      uVar18 = *(uint *)(param_1 + 1);
      if (uVar18 <= uVar4) goto LAB_001602d0;
LAB_0015f7bc:
      uVar20 = (ulong)uVar4;
      if (uVar5 == uVar4) {
        iVar6 = 0xc;
        do {
          fputc(0x20,param_9);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        fwrite(&DAT_001f9ad8,1,4,param_9);
        if (piVar23[0x12] == 0) {
          fwrite(&DAT_001f9880,1,4,param_9);
        }
        else if (piVar23[6] == -1) {
          fwrite("__undef",1,7,param_9);
        }
        else {
          __fprintf_chk(param_9,2,&DAT_001f9928);
        }
        fwrite(&DAT_001f9a38,1,4,param_9);
        pvVar12 = calloc((ulong)*(uint *)(param_1 + 1),1);
        if (pvVar12 != (void *)0x0) {
          *(undefined1 *)((long)pvVar12 + local_c8) = 1;
          emit_region_constprop_3
                    (param_1,uVar16,uVar20,param_4,param_5,param_6,param_7,pvVar12,param_9);
          if (uVar4 < *(uint *)(param_1 + 1)) {
            lVar15 = *param_1 + uVar20 * 0x50;
            uVar5 = *(uint *)(lVar15 + 0x10);
            if (uVar5 != 0) {
              lVar21 = 0;
              do {
                lVar22 = *(long *)(lVar15 + 8) + lVar21 * 0x88;
                if ((*(int *)(*(long *)(lVar15 + 8) + lVar21 * 0x88) == 0x1b) &&
                   (*(uint *)(lVar22 + 0x60) != 0)) {
                  uVar17 = 0;
LAB_00160af0:
                  if (uVar16 != *(uint *)(*(long *)(lVar22 + 0x58) + uVar17 * 4)) goto LAB_00160ae4;
                  iVar6 = 0x10;
                  do {
                    fputc(0x20,param_9);
                    iVar6 = iVar6 + -1;
                  } while (iVar6 != 0);
                  if (*(int *)(lVar22 + 8) == -1) {
                    fwrite("__undef",1,7,param_9);
                  }
                  else {
                    __fprintf_chk(param_9,2,&DAT_001f9928);
                  }
                  fwrite(&DAT_001f9930,1,3,param_9);
                  if (*(int *)(*(long *)(lVar22 + 0x50) + uVar17 * 0x10) == -1) {
                    fwrite("__undef",1,7,param_9);
                  }
                  else {
                    __fprintf_chk(param_9,2,&DAT_001f9928);
                  }
                  fwrite("; /* phi */\n",1,0xc,param_9);
                  uVar5 = *(uint *)(lVar15 + 0x10);
                }
LAB_00160aa4:
                lVar21 = lVar21 + 1;
              } while ((uint)lVar21 < uVar5);
            }
          }
          free(pvVar12);
        }
        iVar6 = 0xc;
        do {
          fputc(0x20,param_9);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      else {
        iVar6 = 0xc;
        if (uVar16 == uVar4) {
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          fwrite("if (!(",1,6,param_9);
          if (piVar23[0x12] == 0) {
            fwrite(&DAT_001f9880,1,4,param_9);
          }
          else if (piVar23[6] == -1) {
            fwrite("__undef",1,7,param_9);
          }
          else {
            __fprintf_chk(param_9,2,&DAT_001f9928);
          }
          fwrite(")) {\n",1,5,param_9);
          pvVar12 = calloc((ulong)*(uint *)(param_1 + 1),1);
          if (pvVar12 != (void *)0x0) {
            *(undefined1 *)((long)pvVar12 + local_c8) = 1;
            emit_region_constprop_3
                      (param_1,uVar5,uVar20,param_4,param_5,param_6,param_7,pvVar12,param_9);
            if (uVar4 < *(uint *)(param_1 + 1)) {
              lVar15 = *param_1 + uVar20 * 0x50;
              uVar16 = *(uint *)(lVar15 + 0x10);
              if (uVar16 != 0) {
                lVar21 = 0;
                do {
                  lVar22 = *(long *)(lVar15 + 8) + lVar21 * 0x88;
                  if ((*(int *)(*(long *)(lVar15 + 8) + lVar21 * 0x88) == 0x1b) &&
                     (*(uint *)(lVar22 + 0x60) != 0)) {
                    uVar17 = 0;
LAB_0015ff14:
                    if (uVar5 != *(uint *)(*(long *)(lVar22 + 0x58) + uVar17 * 4))
                    goto LAB_0015ff08;
                    iVar6 = 0x10;
                    do {
                      fputc(0x20,param_9);
                      iVar6 = iVar6 + -1;
                    } while (iVar6 != 0);
                    if (*(int *)(lVar22 + 8) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    fwrite(&DAT_001f9930,1,3,param_9);
                    if (*(int *)(*(long *)(lVar22 + 0x50) + uVar17 * 0x10) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    fwrite("; /* phi */\n",1,0xc,param_9);
                    uVar16 = *(uint *)(lVar15 + 0x10);
                  }
LAB_0015fec8:
                  lVar21 = lVar21 + 1;
                } while ((uint)lVar21 < uVar16);
              }
            }
            free(pvVar12);
          }
          iVar6 = 0xc;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
        else {
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          fwrite(&DAT_001f9ad8,1,4,param_9);
          if (piVar23[0x12] == 0) {
            fwrite(&DAT_001f9880,1,4,param_9);
          }
          else if (piVar23[6] == -1) {
            fwrite("__undef",1,7,param_9);
          }
          else {
            __fprintf_chk(param_9,2,&DAT_001f9928);
          }
          fwrite(&DAT_001f9a38,1,4,param_9);
          pvVar12 = calloc((ulong)*(uint *)(param_1 + 1),1);
          if (pvVar12 != (void *)0x0) {
            *(undefined1 *)((long)pvVar12 + local_c8) = 1;
            emit_region_constprop_3
                      (param_1,uVar16,uVar20,param_4,param_5,param_6,param_7,pvVar12,param_9);
            if (uVar4 < *(uint *)(param_1 + 1)) {
              lVar15 = *param_1 + (ulong)uVar4 * 0x50;
              uVar18 = *(uint *)(lVar15 + 0x10);
              if (uVar18 != 0) {
                lVar21 = 0;
                do {
                  while ((lVar22 = *(long *)(lVar15 + 8) + lVar21 * 0x88,
                         *(int *)(*(long *)(lVar15 + 8) + lVar21 * 0x88) == 0x1b &&
                         (*(uint *)(lVar22 + 0x60) != 0))) {
                    uVar17 = 0;
LAB_0015f91c:
                    if (uVar16 != *(uint *)(*(long *)(lVar22 + 0x58) + uVar17 * 4))
                    goto LAB_0015f910;
                    iVar6 = 0x10;
                    do {
                      fputc(0x20,param_9);
                      iVar6 = iVar6 + -1;
                    } while (iVar6 != 0);
                    if (*(int *)(lVar22 + 8) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    fwrite(&DAT_001f9930,1,3,param_9);
                    if (*(int *)(*(long *)(lVar22 + 0x50) + uVar17 * 0x10) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    lVar21 = lVar21 + 1;
                    fwrite("; /* phi */\n",1,0xc,param_9);
                    uVar18 = *(uint *)(lVar15 + 0x10);
                    if (uVar18 <= (uint)lVar21) goto LAB_0015f9cc;
                  }
LAB_0015f8d0:
                  lVar21 = lVar21 + 1;
                } while ((uint)lVar21 < uVar18);
              }
            }
LAB_0015f9cc:
            free(pvVar12);
          }
          iVar6 = 0xc;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          fwrite("} else {\n",1,9,param_9);
          pvVar12 = calloc((ulong)*(uint *)(param_1 + 1),1);
          if (pvVar12 != (void *)0x0) {
            *(undefined1 *)((long)pvVar12 + local_c8) = 1;
            emit_region_constprop_3
                      (param_1,uVar5,uVar20,param_4,param_5,param_6,param_7,pvVar12,param_9);
            if (uVar4 < *(uint *)(param_1 + 1)) {
              lVar15 = *param_1 + uVar20 * 0x50;
              uVar16 = *(uint *)(lVar15 + 0x10);
              if (uVar16 != 0) {
                lVar21 = 0;
                do {
                  while ((lVar22 = *(long *)(lVar15 + 8) + lVar21 * 0x88,
                         *(int *)(*(long *)(lVar15 + 8) + lVar21 * 0x88) == 0x1b &&
                         (*(uint *)(lVar22 + 0x60) != 0))) {
                    uVar17 = 0;
LAB_0015fadc:
                    if (uVar5 != *(uint *)(*(long *)(lVar22 + 0x58) + uVar17 * 4))
                    goto LAB_0015fad0;
                    iVar6 = 0x10;
                    do {
                      fputc(0x20,param_9);
                      iVar6 = iVar6 + -1;
                    } while (iVar6 != 0);
                    if (*(int *)(lVar22 + 8) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    fwrite(&DAT_001f9930,1,3,param_9);
                    if (*(int *)(*(long *)(lVar22 + 0x50) + uVar17 * 0x10) == -1) {
                      fwrite("__undef",1,7,param_9);
                    }
                    else {
                      __fprintf_chk(param_9,2,&DAT_001f9928);
                    }
                    lVar21 = lVar21 + 1;
                    fwrite("; /* phi */\n",1,0xc,param_9);
                    uVar16 = *(uint *)(lVar15 + 0x10);
                    if (uVar16 <= (uint)lVar21) goto LAB_0015fb88;
                  }
LAB_0015fa90:
                  lVar21 = lVar21 + 1;
                } while ((uint)lVar21 < uVar16);
              }
            }
LAB_0015fb88:
            free(pvVar12);
          }
          iVar6 = 0xc;
          do {
            fputc(0x20,param_9);
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
      }
      fwrite(&DAT_001f8e68,1,2,param_9);
      uVar16 = *(uint *)(param_1 + 1);
      local_c8 = uVar20;
      if (uVar16 <= uVar4 || param_3 == uVar4) goto LAB_0015f740;
      goto LAB_0015f600;
    }
    local_80[0] = *(uint *)(param_1 + 1);
    local_78 = param_5;
    plStack_70 = param_1;
    iVar6 = ge_classify_edge(local_80,local_c8,uVar16);
    iVar7 = ge_classify_edge(local_80,local_c8,uVar5);
    if (1 < iVar6 - 1U) {
      if (1 < iVar7 - 1U) goto LAB_0015f79c;
      iVar6 = 0xc;
      do {
        fputc(0x20,param_9);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fwrite("if (!(",1,6,param_9);
      if (piVar23[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar23[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      pcVar13 = "continue";
      if (iVar7 == 1) {
        pcVar13 = "break";
      }
      __fprintf_chk(param_9,2,")) %s;\n",pcVar13);
      if (*(uint *)(param_1 + 1) <= uVar16 || param_3 == uVar16) goto LAB_0015f740;
      bVar2 = *(byte *)(param_8 + (ulong)uVar16);
      uVar5 = uVar16;
      goto joined_r0x00160264;
    }
    iVar8 = 0xc;
    if (iVar7 - 1U < 2) {
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite(&DAT_001f9ad8,1,4,param_9);
      emit_cond(param_9,piVar23);
      pcVar13 = "continue";
      if (iVar6 == 1) {
        pcVar13 = "break";
      }
      pcVar1 = "continue";
      if (iVar7 == 1) {
        pcVar1 = "break";
      }
      __fprintf_chk(param_9,2,") %s; else %s;\n",pcVar13,pcVar1);
    }
    else {
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite(&DAT_001f9ad8,1,4,param_9);
      if (piVar23[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar23[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      pcVar13 = "continue";
      if (iVar6 == 1) {
        pcVar13 = "break";
      }
      __fprintf_chk(param_9,2,") %s;\n",pcVar13);
      if (uVar5 < *(uint *)(param_1 + 1) && param_3 != uVar5) {
        bVar2 = *(byte *)(param_8 + (ulong)uVar5);
joined_r0x00160264:
        if ((bVar2 & 1) == 0) {
          emit_region(param_1,uVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9,3);
        }
      }
    }
  }
LAB_0015f740:
  lVar15 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
  if (lVar15 == 0) {
    return;
  }
LAB_00161554:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar15);
LAB_00160080:
  local_c8 = (ulong)uVar5;
  if ((*(byte *)(param_8 + (ulong)uVar5) & 1) != 0) goto LAB_0015f740;
  goto LAB_0015f600;
LAB_00160ae4:
  uVar17 = uVar17 + 1;
  if (uVar17 == *(uint *)(lVar22 + 0x60)) goto LAB_00160aa4;
  goto LAB_00160af0;
LAB_0015ff08:
  uVar17 = uVar17 + 1;
  if (uVar17 == *(uint *)(lVar22 + 0x60)) goto LAB_0015fec8;
  goto LAB_0015ff14;
LAB_0015f910:
  uVar17 = uVar17 + 1;
  if (uVar17 == *(uint *)(lVar22 + 0x60)) goto LAB_0015f8d0;
  goto LAB_0015f91c;
LAB_0015fad0:
  uVar17 = uVar17 + 1;
  if (*(uint *)(lVar22 + 0x60) == uVar17) goto LAB_0015fa90;
  goto LAB_0015fadc;
}

