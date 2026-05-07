
void emit_region_constprop_0
               (long *param_1,uint param_2,uint param_3,long param_4,undefined8 *param_5,
               long param_6,undefined8 param_7,long param_8,FILE *param_9)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  uint *puVar13;
  int *piVar14;
  void *pvVar15;
  char *pcVar16;
  long lVar17;
  long lVar18;
  uint extraout_w11;
  long lVar19;
  long extraout_x12;
  uint uVar20;
  uint uVar21;
  ulong uVar22;
  ulong uVar23;
  uint uVar24;
  long lVar25;
  uint local_80 [2];
  undefined8 *local_78;
  long *plStack_70;
  long local_68;
  
  uVar21 = *(uint *)(param_1 + 1);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar23 = (ulong)param_2;
  if (uVar21 <= param_2 || param_3 == param_2) {
LAB_00163864:
    lVar19 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar19 == 0) {
      return;
    }
LAB_00165068:
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar19);
  }
LAB_0016373c:
  if ((*(byte *)(param_8 + uVar23) & 1) != 0) goto LAB_00163864;
  lVar19 = *param_1;
  *(undefined1 *)(param_8 + uVar23) = 1;
  lVar25 = lVar19 + uVar23 * 0x50;
  uVar7 = *(uint *)(lVar25 + 0x10) - 1;
  uVar20 = (uint)uVar23;
  if ((int)uVar7 < 0) {
    if (((*(byte *)(param_4 + uVar23) & 1) == 0) || (param_5 == (undefined8 *)0x0)) {
      piVar12 = (int *)0x0;
    }
    else {
      uVar7 = *(uint *)(param_5 + 1);
      piVar12 = (int *)0x0;
      if (uVar7 != 0) goto LAB_001637c4;
    }
  }
  else {
    piVar12 = (int *)(*(long *)(lVar25 + 8) + (long)(int)uVar7 * 0x88);
    do {
      if (*piVar12 - 0x17U < 2 || *piVar12 == 0x1a) goto LAB_001637b0;
      piVar12 = piVar12 + -0x22;
    } while ((int *)(*(long *)(lVar25 + 8) + -0x110 +
                    ((ulong)*(uint *)(lVar25 + 0x10) - (ulong)uVar7) * 0x88) != piVar12);
    piVar12 = (int *)0x0;
LAB_001637b0:
    if ((*(byte *)(param_4 + uVar23) & 1) != 0) {
      if ((param_5 == (undefined8 *)0x0) || (uVar7 = *(uint *)(param_5 + 1), uVar7 == 0)) {
        if (piVar12 != (int *)0x0) {
          if (*piVar12 == 0x17) {
            uVar21 = piVar12[0x19];
            uVar7 = piVar12[0x1a];
            cf_emit_block_body_part_0_constprop_0_isra_0(lVar19,uVar23,param_9);
LAB_00164c20:
            uVar24 = *(uint *)(param_1 + 1);
            uVar6 = uVar7;
            uVar2 = uVar21;
            if (uVar21 < uVar24) {
              lVar19 = *param_1;
              if (uVar21 != uVar20) {
                puVar13 = (uint *)0x0;
LAB_00164cac:
                uVar6 = 0;
                uVar11 = uVar21;
                do {
                  uVar3 = *(uint *)(lVar19 + (ulong)uVar11 * 0x50 + 0x34);
                  uVar2 = uVar21;
                  uVar5 = uVar7;
                  if ((uVar3 == uVar11) || (uVar6 = uVar6 + 1, uVar24 < uVar6)) {
                    if ((uVar7 < uVar24) &&
                       (uVar6 = uVar21, uVar2 = uVar20, uVar5 = uVar21, uVar7 != uVar20))
                    goto LAB_001648e8;
                    break;
                  }
                  uVar11 = uVar3;
                } while (uVar3 != uVar20);
joined_r0x00164cfc:
                uVar6 = uVar5;
                if (puVar13 != (uint *)0x0) goto LAB_0016455c;
              }
LAB_00164924:
              iVar8 = 4;
              do {
                fputc(0x20,param_9);
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              fwrite("while (",1,7,param_9);
              if (piVar12[0x12] == 0) {
                fwrite(&DAT_001f94c8,1,4,param_9);
              }
              else if (piVar12[6] == -1) {
                fwrite("__undef",1,7,param_9);
              }
              else {
                __fprintf_chk(param_9,2,&DAT_001f9570);
              }
              fwrite(&DAT_001f9680,1,4,param_9);
            }
            else {
              if ((uVar24 <= uVar7) ||
                 (lVar19 = *param_1, uVar6 = uVar21, uVar2 = uVar20, uVar7 == uVar20))
              goto LAB_00164924;
              puVar13 = (uint *)0x0;
LAB_001648e8:
              uVar21 = 0;
              uVar11 = uVar7;
              do {
                uVar3 = *(uint *)(lVar19 + (ulong)uVar11 * 0x50 + 0x34);
                uVar2 = uVar6;
                uVar5 = uVar7;
                if ((uVar3 == uVar11) || (uVar21 = uVar21 + 1, uVar24 < uVar21))
                goto joined_r0x00164cfc;
                uVar11 = uVar3;
              } while (uVar3 != uVar20);
              uVar2 = uVar7;
              if (puVar13 == (uint *)0x0) goto LAB_00164924;
LAB_0016455c:
              if ((puVar13[6] != 3) || (iVar8 = 4, (puVar13[0x11] & 1) == 0)) goto LAB_00164924;
              do {
                fputc(0x20,param_9);
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              __fprintf_chk(param_9,2,"for (v%u = v%u; ",puVar13[8],puVar13[9]);
              __fprintf_chk(param_9,2,&DAT_001f9570,puVar13[8]);
              uVar21 = puVar13[0x10];
              if (uVar21 == 0x10) {
LAB_00164dd8:
                fwrite(&DAT_001f9638,1,4,param_9);
              }
              else if (uVar21 < 0x11) {
                if (uVar21 != 0xd) {
                  if (uVar21 < 0xe) {
                    if (uVar21 == 0xb) {
                      fwrite(&DAT_001f9658,1,4,param_9);
                    }
                    else {
                      if (uVar21 != 0xc) goto LAB_00164e2c;
                      fwrite(&DAT_001f9650,1,4,param_9);
                    }
                    goto LAB_00164610;
                  }
                  if (uVar21 == 0xe) goto LAB_00164dd8;
                }
                fwrite(&DAT_001f9630,1,3,param_9);
              }
              else if (uVar21 == 0x13) {
LAB_00164e08:
                fwrite(&DAT_001f9640,1,3,param_9);
              }
              else {
                if (uVar21 < 0x14) {
                  if (uVar21 == 0x11) goto LAB_00164e08;
                }
                else if (uVar21 != 0x14) {
LAB_00164e2c:
                  fwrite(&DAT_001f95a0,1,3,param_9);
                  goto LAB_00164610;
                }
                fwrite(&DAT_001f9648,1,4,param_9);
              }
LAB_00164610:
              __fprintf_chk(param_9,2,"v%u; ",puVar13[0xf]);
              __fprintf_chk(param_9,2,&DAT_001f9570,puVar13[8]);
              if (puVar13[0xe] == 2) {
                fwrite(&DAT_001f9668,1,4,param_9);
              }
              else {
                fwrite(&DAT_001f9670,1,4,param_9);
              }
              __fprintf_chk(param_9,2,"%ldLL",*(undefined8 *)(puVar13 + 0xc));
              fwrite(&DAT_001f9680,1,4,param_9);
            }
            pvVar15 = calloc((ulong)*(uint *)(param_1 + 1),1);
            if (pvVar15 != (void *)0x0) {
              *(undefined1 *)((long)pvVar15 + uVar23) = 1;
              emit_region_constprop_1
                        (param_1,uVar2,uVar23,param_4,param_5,param_6,param_7,pvVar15,param_9);
              free(pvVar15);
            }
            iVar8 = 4;
            do {
              fputc(0x20,param_9);
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            fwrite(&DAT_001f8ab0,1,2,param_9);
            uVar21 = *(uint *)(param_1 + 1);
            if (param_3 == uVar6 || uVar21 <= uVar6) goto LAB_00163864;
            uVar23 = (ulong)uVar6;
            goto LAB_0016373c;
          }
          if (*piVar12 == 0x18) {
            puVar13 = (uint *)0x0;
LAB_00163f44:
            uVar7 = find_latch(param_1,uVar23);
            lVar19 = extraout_x12;
            uVar21 = extraout_w11;
            if (uVar7 < extraout_w11) goto LAB_00163adc;
          }
        }
      }
      else {
LAB_001637c4:
        puVar13 = (uint *)*param_5;
        uVar6 = 0;
        do {
          if (*puVar13 == uVar20) goto LAB_001637f0;
          uVar6 = uVar6 + 1;
          puVar13 = puVar13 + 0x18;
        } while (uVar6 < uVar7);
        puVar13 = (uint *)0x0;
LAB_001637f0:
        if (piVar12 != (int *)0x0) {
          if (*piVar12 == 0x17) {
            uVar21 = piVar12[0x19];
            uVar7 = piVar12[0x1a];
            cf_emit_block_body_part_0_constprop_0_isra_0(lVar19,uVar23,param_9);
            if (puVar13 == (uint *)0x0) goto LAB_00164c20;
            uVar6 = puVar13[5];
            uVar24 = *(uint *)(param_1 + 1);
            uVar2 = uVar21;
            if (uVar6 < uVar24) {
              if (uVar21 == uVar6) {
                uVar2 = uVar7;
              }
            }
            else {
              uVar6 = uVar7;
              if (uVar21 < uVar24) {
                lVar19 = *param_1;
                if (uVar21 != uVar20) goto LAB_00164cac;
              }
              else if ((uVar7 < uVar24) &&
                      (lVar19 = *param_1, uVar6 = uVar21, uVar2 = uVar20, uVar7 != uVar20))
              goto LAB_001648e8;
            }
            goto LAB_0016455c;
          }
          if (*piVar12 == 0x18) {
            if ((puVar13 == (uint *)0x0) || (uVar7 = puVar13[1], uVar21 <= uVar7))
            goto LAB_00163f44;
LAB_00163adc:
            if (uVar7 != uVar20) {
              lVar19 = lVar19 + (ulong)uVar7 * 0x50;
              uVar6 = *(uint *)(lVar19 + 0x10);
              uVar24 = uVar6 - 1;
              if (-1 < (int)uVar24) {
                lVar19 = *(long *)(lVar19 + 8);
                piVar14 = (int *)(lVar19 + (long)(int)uVar24 * 0x88);
                do {
                  if (*piVar14 - 0x17U < 2 || *piVar14 == 0x1a) {
                    if ((((puVar13 == (uint *)0x0) || (uVar6 = puVar13[5], uVar21 <= puVar13[5])) &&
                        (uVar6 = uVar21, *piVar14 == 0x17)) &&
                       (uVar6 = piVar14[0x19], piVar14[0x19] == uVar20)) {
                      uVar6 = piVar14[0x1a];
                    }
                    goto LAB_00163b68;
                  }
                  piVar14 = piVar14 + -0x22;
                } while (piVar14 != (int *)(lVar19 + -0x110 + ((ulong)uVar6 - (ulong)uVar24) * 0x88)
                        );
              }
              if (puVar13 == (uint *)0x0) {
                piVar14 = (int *)0x0;
                uVar6 = uVar21;
              }
              else {
                piVar14 = (int *)0x0;
                uVar6 = puVar13[5];
                if (uVar21 < puVar13[5]) {
                  uVar6 = uVar21;
                }
              }
LAB_00163b68:
              iVar8 = 4;
              do {
                fputc(0x20,param_9);
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              fwrite("do {\n",1,5,param_9);
              uVar21 = *(uint *)(param_1 + 1);
              if (uVar20 < uVar21) {
                cf_emit_block_body_part_0_isra_0(*param_1,uVar23,param_9,2);
                uVar21 = *(uint *)(param_1 + 1);
              }
              uVar20 = piVar12[0x19];
              if ((uVar20 != uVar7) && (pvVar15 = calloc((ulong)uVar21,1), pvVar15 != (void *)0x0))
              {
                *(undefined1 *)((long)pvVar15 + uVar23) = 1;
                emit_region_constprop_1
                          (param_1,uVar20,uVar7,param_4,param_5,param_6,param_7,pvVar15,param_9);
                free(pvVar15);
                uVar21 = *(uint *)(param_1 + 1);
              }
              if (uVar7 < uVar21) {
                cf_emit_block_body_part_0_isra_0(*param_1,uVar7,param_9,2);
              }
              iVar8 = 4;
              do {
                fputc(0x20,param_9);
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              fwrite("} while (",1,9,param_9);
              if ((piVar14 == (int *)0x0) || (piVar14[0x12] == 0)) {
                fwrite(&DAT_001f94c8,1,4,param_9);
              }
              else if (piVar14[6] == -1) {
                fwrite("__undef",1,7,param_9);
              }
              else {
                __fprintf_chk(param_9,2,&DAT_001f9570);
              }
              fwrite(&DAT_001f95f0,1,3,param_9);
              uVar21 = *(uint *)(param_1 + 1);
              if (param_3 == uVar6 || uVar21 <= uVar6) goto LAB_00163864;
              uVar23 = (ulong)uVar6;
              goto LAB_0016373c;
            }
          }
        }
      }
    }
  }
  cf_emit_block_body_part_0_constprop_0_isra_0(lVar19,uVar23,param_9);
  piVar14 = (int *)sr_is_switch_head(param_7,uVar23);
  if ((piVar14 != (int *)0x0) && (piVar14[4] != 0)) {
    iVar8 = piVar14[8];
    if (iVar8 != 0) {
      uVar21 = *(uint *)(param_1 + 1);
      iVar9 = 0;
      uVar22 = uVar23;
      while ((uint)uVar22 < uVar21) {
        lVar19 = *param_1;
        *(undefined1 *)(param_8 + uVar22) = 1;
        lVar19 = lVar19 + uVar22 * 0x50;
        uVar7 = *(uint *)(lVar19 + 0x10);
        uVar6 = uVar7 - 1;
        if ((int)uVar6 < 0) break;
        lVar19 = *(long *)(lVar19 + 8);
        piVar12 = (int *)(lVar19 + (long)(int)uVar6 * 0x88);
        while (iVar10 = *piVar12, 1 < iVar10 - 0x17U && iVar10 != 0x1a) {
          piVar12 = piVar12 + -0x22;
          if (piVar12 == (int *)(lVar19 + -0x110 + ((ulong)uVar7 - (ulong)uVar6) * 0x88))
          goto LAB_00164260;
        }
        if (iVar10 != 0x17) break;
        iVar9 = iVar9 + 1;
        uVar22 = (ulong)(uint)piVar12[0x1a];
        if (iVar9 == iVar8) break;
      }
    }
LAB_00164260:
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    fwrite("switch (",1,8,param_9);
    if (*piVar14 == -1) {
      fwrite("__undef",1,7,param_9);
    }
    else {
      __fprintf_chk(param_9,2,&DAT_001f9570);
    }
    fwrite(&DAT_001f9680,1,4,param_9);
    lVar19 = 0;
    if (piVar14[4] != 0) {
      do {
        lVar17 = *(long *)(piVar14 + 2);
        iVar8 = 4;
        lVar25 = lVar17 + lVar19 * 0x10;
        do {
          fputc(0x20,param_9);
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        if ((*(byte *)(lVar25 + 0xc) & 1) == 0) {
          __fprintf_chk(param_9,2,"case %ld:\n",*(undefined8 *)(lVar17 + lVar19 * 0x10));
          uVar21 = *(uint *)(param_1 + 1);
          uVar7 = *(uint *)(lVar25 + 8);
          if (uVar7 < uVar21) goto LAB_001643d0;
LAB_00164340:
          bVar4 = *(byte *)(lVar25 + 0xd);
        }
        else {
          fwrite("default:\n",1,9,param_9);
          uVar21 = *(uint *)(param_1 + 1);
          uVar7 = *(uint *)(lVar25 + 8);
          if (uVar21 <= uVar7) goto LAB_00164340;
LAB_001643d0:
          pvVar15 = calloc((ulong)uVar21,1);
          if (pvVar15 == (void *)0x0) goto LAB_00164340;
          uVar6 = piVar14[8];
          if (uVar6 != 0 && uVar20 < uVar21) {
            lVar17 = *param_1;
            uVar24 = 0;
            uVar22 = uVar23;
            while( true ) {
              lVar18 = lVar17 + uVar22 * 0x50;
              *(undefined1 *)((long)pvVar15 + uVar22) = 1;
              uVar2 = *(uint *)(lVar18 + 0x10);
              uVar11 = uVar2 - 1;
              if ((int)uVar11 < 0) break;
              lVar18 = *(long *)(lVar18 + 8);
              piVar12 = (int *)(lVar18 + (long)(int)uVar11 * 0x88);
              while (iVar8 = *piVar12, 1 < iVar8 - 0x17U && iVar8 != 0x1a) {
                piVar12 = piVar12 + -0x22;
                if ((int *)(lVar18 + -0x110 + ((ulong)uVar2 - (ulong)uVar11) * 0x88) == piVar12)
                goto LAB_00164488;
              }
              if (iVar8 != 0x17) break;
              uVar22 = (ulong)(uint)piVar12[0x1a];
              uVar24 = uVar24 + 1;
              if (uVar21 <= (uint)piVar12[0x1a] || uVar6 <= uVar24) break;
            }
          }
LAB_00164488:
          emit_region_constprop_2
                    (param_1,uVar7,param_3,param_4,param_5,param_6,param_7,pvVar15,param_9);
          free(pvVar15);
          bVar4 = *(byte *)(lVar25 + 0xd);
        }
        if ((bVar4 & 1) == 0) {
          iVar8 = 8;
          do {
            fputc(0x20,param_9);
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          fwrite("break;\n",1,7,param_9);
        }
        lVar19 = lVar19 + 1;
      } while ((uint)lVar19 < (uint)piVar14[4]);
    }
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    fwrite(&DAT_001f8ab0,1,2,param_9);
    uVar21 = *(uint *)(param_1 + 1);
    uVar7 = piVar14[6];
    if (uVar7 < uVar21 && param_3 != uVar7) goto LAB_00163e88;
    goto LAB_00163864;
  }
  if (2 < *(uint *)(lVar25 + 0x30)) {
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    fwrite("switch (expr) {\n",1,0x10,param_9);
    uVar22 = 0;
    if (*(int *)(lVar25 + 0x30) != 0) {
      do {
        iVar8 = 4;
        do {
          fputc(0x20,param_9);
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        if (*(int *)(lVar25 + 0x30) + -1 == (int)uVar22) {
          fwrite("default:\n",1,9,param_9);
        }
        else {
          __fprintf_chk(param_9,2,"case %u:\n",uVar22 & 0xffffffff);
        }
        uVar21 = *(uint *)(param_1 + 1);
        uVar7 = *(uint *)(*(long *)(lVar25 + 0x28) + uVar22 * 4);
        pvVar15 = calloc((ulong)uVar21,1);
        if (pvVar15 != (void *)0x0) {
          *(undefined1 *)((long)pvVar15 + uVar23) = 1;
          if ((uVar7 < uVar21) && ((*(byte *)(param_8 + (ulong)uVar7) & 1) == 0)) {
            emit_region(param_1,uVar7,param_3,param_4,param_5,param_6,param_7,pvVar15,param_9,3);
          }
          free(pvVar15);
        }
        iVar8 = 8;
        do {
          fputc(0x20,param_9);
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        fwrite("break;\n",1,7,param_9);
        uVar22 = uVar22 + 1;
      } while ((uint)uVar22 < *(uint *)(lVar25 + 0x30));
    }
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    lVar19 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar19 == 0) {
      pcVar16 = "}\n";
LAB_00163e4c:
      fwrite(pcVar16,1,2,param_9);
      return;
    }
    goto LAB_00165068;
  }
  if (piVar12 == (int *)0x0) goto LAB_00163864;
  iVar8 = *piVar12;
  if (iVar8 == 0x18) {
    uVar7 = piVar12[0x19];
    uVar21 = *(uint *)(param_1 + 1);
    if (uVar7 < uVar21 && param_3 != uVar7) goto LAB_00163e88;
    goto LAB_00163864;
  }
  if (iVar8 == 0x1a) {
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    fwrite("return ",1,7,param_9);
    if ((piVar12[0x19] == -1) && (1 < (uint)piVar12[0x12])) {
      if (*(long *)(piVar12 + 0xc) == 0) {
        fwrite("call(",1,5,param_9);
      }
      else {
        __fprintf_chk(param_9,2,"sub_%lx(");
      }
      lVar19 = 0;
      if (piVar12[0x18] != 0) {
        do {
          uVar21 = (uint)lVar19;
          while( true ) {
            if (uVar21 != 0) {
              fwrite(", ",1,2,param_9);
            }
            if (*(int *)(*(long *)(piVar12 + 0x14) + lVar19 * 0x10) != -1) break;
            fwrite("__undef",1,7,param_9);
            lVar19 = lVar19 + 1;
            uVar21 = (uint)lVar19;
            if ((uint)piVar12[0x18] <= uVar21) goto LAB_00163f18;
          }
          __fprintf_chk(param_9,2,&DAT_001f9570);
          lVar19 = lVar19 + 1;
        } while ((uint)lVar19 < (uint)piVar12[0x18]);
      }
LAB_00163f18:
      fputc(0x29,param_9);
    }
    else if ((piVar12[0x12] == 0) || (piVar12[6] == -1)) {
      fputc(0x30,param_9);
    }
    else {
      __fprintf_chk(param_9,2,&DAT_001f9570);
    }
    lVar19 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar19 == 0) {
      pcVar16 = ";\n";
      goto LAB_00163e4c;
    }
    goto LAB_00165068;
  }
  if (iVar8 != 0x17) goto LAB_00163864;
  uVar21 = piVar12[0x19];
  uVar7 = piVar12[0x1a];
  if ((param_5 != (undefined8 *)0x0) && (param_3 < *(uint *)(param_1 + 1))) {
    local_80[0] = *(uint *)(param_1 + 1);
    local_78 = param_5;
    plStack_70 = param_1;
    iVar8 = ge_classify_edge(local_80,uVar23,uVar21);
    iVar9 = ge_classify_edge(local_80,uVar23,uVar7);
    if (iVar8 - 1U < 2) {
      iVar10 = 4;
      if (iVar9 - 1U < 2) {
        do {
          fputc(0x20,param_9);
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        fwrite(&DAT_001f9720,1,4,param_9);
        emit_cond(param_9,piVar12);
        pcVar16 = "continue";
        if (iVar8 == 1) {
          pcVar16 = "break";
        }
        pcVar1 = "continue";
        if (iVar9 == 1) {
          pcVar1 = "break";
        }
        __fprintf_chk(param_9,2,") %s; else %s;\n",pcVar16,pcVar1);
      }
      else {
        do {
          fputc(0x20,param_9);
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        fwrite(&DAT_001f9720,1,4,param_9);
        if (piVar12[0x12] == 0) {
          fwrite(&DAT_001f94c8,1,4,param_9);
        }
        else if (piVar12[6] == -1) {
          fwrite("__undef",1,7,param_9);
        }
        else {
          __fprintf_chk(param_9,2,&DAT_001f9570);
        }
        pcVar16 = "continue";
        if (iVar8 == 1) {
          pcVar16 = "break";
        }
        __fprintf_chk(param_9,2,") %s;\n",pcVar16);
        if ((uVar7 < *(uint *)(param_1 + 1) && param_3 != uVar7) &&
           ((*(byte *)(param_8 + (ulong)uVar7) & 1) == 0)) {
          emit_region_constprop_0
                    (param_1,uVar7,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
        }
      }
    }
    else {
      if (1 < iVar9 - 1U) goto LAB_001638c8;
      iVar8 = 4;
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite("if (!(",1,6,param_9);
      if (piVar12[0x12] == 0) {
        fwrite(&DAT_001f94c8,1,4,param_9);
      }
      else if (piVar12[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9570);
      }
      pcVar16 = "continue";
      if (iVar9 == 1) {
        pcVar16 = "break";
      }
      __fprintf_chk(param_9,2,")) %s;\n",pcVar16);
      if ((uVar21 < *(uint *)(param_1 + 1) && param_3 != uVar21) &&
         ((*(byte *)(param_8 + (ulong)uVar21) & 1) == 0)) {
        emit_region_constprop_0
                  (param_1,(ulong)uVar21,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      }
    }
    goto LAB_00163864;
  }
LAB_001638c8:
  if (param_6 == 0) {
    uVar20 = *(uint *)(param_1 + 1);
LAB_001640c8:
    uVar6 = find_join_isra_0(*param_1,uVar20,uVar21,uVar7);
    if (uVar20 <= uVar6) {
      local_80[0] = uVar20;
      local_78 = param_5;
      plStack_70 = param_1;
      iVar9 = ge_classify_edge(local_80,uVar23,uVar21);
      iVar10 = ge_classify_edge(local_80,uVar23,uVar7);
      iVar8 = 4;
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite(&DAT_001f9720,1,4,param_9);
      if (piVar12[0x12] == 0) {
        fwrite(&DAT_001f94c8,1,4,param_9);
      }
      else if (piVar12[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9570);
      }
      if (iVar9 == 1) {
        fwrite(") break;",1,8,param_9);
      }
      else if (iVar9 == 2) {
        fwrite(") continue;",1,0xb,param_9);
      }
      else {
        __fprintf_chk(param_9,2,") goto bb%u;",uVar21);
      }
      if (iVar10 == 1) {
        fwrite(" else break;\n",1,0xd,param_9);
      }
      else if (iVar10 == 2) {
        fwrite(" else continue;\n",1,0x10,param_9);
      }
      else {
        __fprintf_chk(param_9,2," else goto bb%u;\n",uVar7);
      }
      goto LAB_00163864;
    }
  }
  else {
    uVar6 = sa_find_join(param_6,param_1,uVar23);
    uVar20 = *(uint *)(param_1 + 1);
    if (uVar20 <= uVar6) goto LAB_001640c8;
  }
  uVar22 = (ulong)uVar6;
  if (uVar7 == uVar6) {
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    fwrite(&DAT_001f9720,1,4,param_9);
    if (piVar12[0x12] == 0) {
      fwrite(&DAT_001f94c8,1,4,param_9);
    }
    else if (piVar12[6] == -1) {
      fwrite("__undef",1,7,param_9);
    }
    else {
      __fprintf_chk(param_9,2,&DAT_001f9570);
    }
    fwrite(&DAT_001f9680,1,4,param_9);
    pvVar15 = calloc((ulong)*(uint *)(param_1 + 1),1);
    if (pvVar15 != (void *)0x0) {
      *(undefined1 *)((long)pvVar15 + uVar23) = 1;
      emit_region_constprop_1(param_1,uVar21,uVar22,param_4,param_5,param_6,param_7,pvVar15,param_9)
      ;
      if (uVar6 < *(uint *)(param_1 + 1)) {
        emit_phi_assigns_part_0_constprop_0_isra_0(*param_1,uVar22,uVar21,param_9);
      }
      free(pvVar15);
    }
    iVar8 = 4;
    do {
      fputc(0x20,param_9);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  else {
    iVar8 = 4;
    if (uVar21 == uVar6) {
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite("if (!(",1,6,param_9);
      if (piVar12[0x12] == 0) {
        fwrite(&DAT_001f94c8,1,4,param_9);
      }
      else if (piVar12[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9570);
      }
      fwrite(")) {\n",1,5,param_9);
      pvVar15 = calloc((ulong)*(uint *)(param_1 + 1),1);
      if (pvVar15 != (void *)0x0) {
        *(undefined1 *)((long)pvVar15 + uVar23) = 1;
        emit_region_constprop_1
                  (param_1,uVar7,uVar22,param_4,param_5,param_6,param_7,pvVar15,param_9);
        if (uVar6 < *(uint *)(param_1 + 1)) {
          emit_phi_assigns_part_0_constprop_0_isra_0(*param_1,uVar22,uVar7,param_9);
        }
        free(pvVar15);
      }
      iVar8 = 4;
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    else {
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite(&DAT_001f9720,1,4,param_9);
      if (piVar12[0x12] == 0) {
        fwrite(&DAT_001f94c8,1,4,param_9);
      }
      else if (piVar12[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9570);
      }
      fwrite(&DAT_001f9680,1,4,param_9);
      pvVar15 = calloc((ulong)*(uint *)(param_1 + 1),1);
      if (pvVar15 != (void *)0x0) {
        *(undefined1 *)((long)pvVar15 + uVar23) = 1;
        emit_region_constprop_1
                  (param_1,uVar21,uVar22,param_4,param_5,param_6,param_7,pvVar15,param_9);
        if (uVar6 < *(uint *)(param_1 + 1)) {
          emit_phi_assigns_part_0_constprop_0_isra_0(*param_1,uVar22,uVar21,param_9);
        }
        free(pvVar15);
      }
      iVar8 = 4;
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      fwrite("} else {\n",1,9,param_9);
      pvVar15 = calloc((ulong)*(uint *)(param_1 + 1),1);
      if (pvVar15 != (void *)0x0) {
        *(undefined1 *)((long)pvVar15 + uVar23) = 1;
        emit_region_constprop_1
                  (param_1,uVar7,uVar22,param_4,param_5,param_6,param_7,pvVar15,param_9);
        if (uVar6 < *(uint *)(param_1 + 1)) {
          emit_phi_assigns_part_0_constprop_0_isra_0(*param_1,uVar22,uVar7,param_9);
        }
        free(pvVar15);
      }
      iVar8 = 4;
      do {
        fputc(0x20,param_9);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  fwrite(&DAT_001f8ab0,1,2,param_9);
  uVar21 = *(uint *)(param_1 + 1);
  uVar23 = uVar22;
  if (uVar21 <= uVar6 || param_3 == uVar6) goto LAB_00163864;
  goto LAB_0016373c;
LAB_00163e88:
  uVar23 = (ulong)uVar7;
  if ((*(byte *)(param_8 + (ulong)uVar7) & 1) != 0) goto LAB_00163864;
  goto LAB_0016373c;
}

