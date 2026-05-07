
void emit_region(long *param_1,uint param_2,uint param_3,long param_4,undefined8 *param_5,
                long param_6,undefined8 param_7,long param_8,FILE *param_9,int param_10)

{
  char *pcVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  int *piVar13;
  void *pvVar14;
  char *pcVar15;
  ulong uVar16;
  uint uVar17;
  long lVar18;
  uint uVar19;
  uint extraout_w11;
  long lVar20;
  long extraout_x12;
  uint uVar21;
  uint uVar22;
  ulong uVar23;
  long lVar24;
  long lVar25;
  int *piVar26;
  uint local_80 [2];
  undefined8 *local_78;
  long *plStack_70;
  long local_68;
  
  uVar21 = *(uint *)(param_1 + 1);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (uVar21 <= param_2 || param_2 == param_3) {
LAB_0015ba08:
    lVar20 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar20 == 0) {
      return;
    }
LAB_0015d440:
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar20);
  }
  iVar4 = param_10 * 4;
  uVar16 = (ulong)param_2;
LAB_0015b8d0:
  if ((*(byte *)(param_8 + uVar16) & 1) != 0) goto LAB_0015ba08;
  lVar20 = *param_1;
  *(undefined1 *)(param_8 + uVar16) = 1;
  lVar24 = lVar20 + uVar16 * 0x50;
  uVar6 = *(uint *)(lVar24 + 0x10) - 1;
  uVar22 = (uint)uVar16;
  if ((int)uVar6 < 0) {
    if (((*(byte *)(param_4 + uVar16) & 1) == 0) || (param_5 == (undefined8 *)0x0)) {
      piVar26 = (int *)0x0;
    }
    else {
      uVar6 = *(uint *)(param_5 + 1);
      piVar26 = (int *)0x0;
      if (uVar6 != 0) goto LAB_0015b95c;
    }
  }
  else {
    piVar26 = (int *)(*(long *)(lVar24 + 8) + (long)(int)uVar6 * 0x88);
    do {
      if (*piVar26 - 0x17U < 2 || *piVar26 == 0x1a) goto LAB_0015b944;
      piVar26 = piVar26 + -0x22;
    } while ((int *)(*(long *)(lVar24 + 8) + -0x110 +
                    ((ulong)*(uint *)(lVar24 + 0x10) - (ulong)uVar6) * 0x88) != piVar26);
    piVar26 = (int *)0x0;
LAB_0015b944:
    if ((*(byte *)(param_4 + uVar16) & 1) != 0) {
      if ((param_5 == (undefined8 *)0x0) || (uVar6 = *(uint *)(param_5 + 1), uVar6 == 0)) {
        if (piVar26 != (int *)0x0) {
          if (*piVar26 == 0x17) {
            uVar21 = piVar26[0x19];
            uVar6 = piVar26[0x1a];
            cf_emit_block_body_part_0_isra_0(lVar20,uVar16,param_9,param_10);
LAB_0015cfe8:
            uVar19 = *(uint *)(param_1 + 1);
            uVar5 = uVar6;
            uVar10 = uVar21;
            if (uVar21 < uVar19) {
              lVar20 = *param_1;
              if (uVar21 != uVar22) {
                puVar12 = (uint *)0x0;
LAB_0015d0bc:
                uVar17 = 0;
                uVar11 = uVar21;
                do {
                  uVar2 = *(uint *)(lVar20 + (ulong)uVar11 * 0x50 + 0x34);
                  uVar5 = uVar6;
                  uVar10 = uVar21;
                  if ((uVar2 == uVar11) || (uVar17 = uVar17 + 1, uVar19 < uVar17)) {
                    if ((uVar6 < uVar19) && (uVar5 = uVar21, uVar10 = uVar22, uVar6 != uVar22))
                    goto LAB_0015cc1c;
                    break;
                  }
                  uVar11 = uVar2;
                } while (uVar2 != uVar22);
                goto LAB_0015cc54;
              }
            }
            else if ((uVar6 < uVar19) &&
                    (lVar20 = *param_1, uVar5 = uVar21, uVar10 = uVar22, uVar6 != uVar22)) {
              puVar12 = (uint *)0x0;
LAB_0015cc1c:
              uVar17 = 0;
              uVar11 = uVar6;
              do {
                uVar2 = *(uint *)(lVar20 + (ulong)uVar11 * 0x50 + 0x34);
                uVar5 = uVar6;
                uVar10 = uVar21;
                if ((uVar2 == uVar11) || (uVar17 = uVar17 + 1, uVar19 < uVar17)) break;
                uVar5 = uVar21;
                uVar11 = uVar2;
                uVar10 = uVar6;
              } while (uVar2 != uVar22);
LAB_0015cc54:
              if (puVar12 != (uint *)0x0) goto LAB_0015c884;
            }
LAB_0015cc58:
            iVar7 = 0;
            if (0 < param_10) {
              do {
                iVar7 = iVar7 + 1;
                fputc(0x20,param_9);
              } while (iVar7 != iVar4);
            }
            fwrite("while (",1,7,param_9);
            if (piVar26[0x12] == 0) {
              fwrite(&DAT_001f9880,1,4,param_9);
            }
            else if (piVar26[6] == -1) {
              fwrite("__undef",1,7,param_9);
            }
            else {
              __fprintf_chk(param_9,2,&DAT_001f9928);
            }
            fwrite(&DAT_001f9a38,1,4,param_9);
            goto LAB_0015c9b8;
          }
          if (*piVar26 == 0x18) {
            puVar12 = (uint *)0x0;
LAB_0015bff8:
            uVar6 = find_latch(param_1,uVar16);
            lVar20 = extraout_x12;
            uVar21 = extraout_w11;
            if (uVar6 < extraout_w11) goto LAB_0015bcb4;
          }
        }
      }
      else {
LAB_0015b95c:
        uVar5 = 0;
        puVar12 = (uint *)*param_5;
        do {
          if (*puVar12 == uVar22) goto LAB_0015b98c;
          uVar5 = uVar5 + 1;
          puVar12 = puVar12 + 0x18;
        } while (uVar5 < uVar6);
        puVar12 = (uint *)0x0;
LAB_0015b98c:
        if (piVar26 != (int *)0x0) {
          if (*piVar26 == 0x17) {
            uVar21 = piVar26[0x19];
            uVar6 = piVar26[0x1a];
            cf_emit_block_body_part_0_isra_0(lVar20,uVar16,param_9,param_10);
            if (puVar12 == (uint *)0x0) goto LAB_0015cfe8;
            uVar19 = *(uint *)(param_1 + 1);
            uVar5 = puVar12[5];
            uVar10 = uVar21;
            if (uVar5 < uVar19) {
              if (uVar5 == uVar21) {
                uVar10 = uVar6;
              }
            }
            else {
              uVar5 = uVar6;
              if (uVar21 < uVar19) {
                lVar20 = *param_1;
                if (uVar21 != uVar22) goto LAB_0015d0bc;
              }
              else if ((uVar6 < uVar19) &&
                      (lVar20 = *param_1, uVar5 = uVar21, uVar10 = uVar22, uVar6 != uVar22))
              goto LAB_0015cc1c;
            }
LAB_0015c884:
            if ((puVar12[6] != 3) || ((puVar12[0x11] & 1) == 0)) goto LAB_0015cc58;
            iVar7 = 0;
            if (0 < param_10) {
              do {
                iVar7 = iVar7 + 1;
                fputc(0x20,param_9);
              } while (iVar7 != iVar4);
            }
            __fprintf_chk(param_9,2,"for (v%u = v%u; ",puVar12[8],puVar12[9]);
            __fprintf_chk(param_9,2,&DAT_001f9928,puVar12[8]);
            uVar21 = puVar12[0x10];
            if (uVar21 == 0x10) {
LAB_0015d198:
              fwrite(&DAT_001f99f0,1,4,param_9);
            }
            else if (uVar21 < 0x11) {
              if (uVar21 != 0xd) {
                if (uVar21 < 0xe) {
                  if (uVar21 == 0xb) {
                    fwrite(&DAT_001f9a10,1,4,param_9);
                  }
                  else {
                    if (uVar21 != 0xc) goto LAB_0015d238;
                    fwrite(&DAT_001f9a08,1,4,param_9);
                  }
                  goto LAB_0015c938;
                }
                if (uVar21 == 0xe) goto LAB_0015d198;
              }
              fwrite(&DAT_001f99e8,1,3,param_9);
            }
            else if (uVar21 == 0x13) {
LAB_0015d1b4:
              fwrite(&DAT_001f99f8,1,3,param_9);
            }
            else {
              if (uVar21 < 0x14) {
                if (uVar21 == 0x11) goto LAB_0015d1b4;
              }
              else if (uVar21 != 0x14) {
LAB_0015d238:
                fwrite(&DAT_001f9958,1,3,param_9);
                goto LAB_0015c938;
              }
              fwrite(&DAT_001f9a00,1,4,param_9);
            }
LAB_0015c938:
            __fprintf_chk(param_9,2,"v%u; ",puVar12[0xf]);
            __fprintf_chk(param_9,2,&DAT_001f9928,puVar12[8]);
            if (puVar12[0xe] == 2) {
              fwrite(&DAT_001f9a20,1,4,param_9);
            }
            else {
              fwrite(&DAT_001f9a28,1,4,param_9);
            }
            __fprintf_chk(param_9,2,"%ldLL",*(undefined8 *)(puVar12 + 0xc));
            fwrite(&DAT_001f9a38,1,4,param_9);
LAB_0015c9b8:
            pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
            if (pvVar14 != (void *)0x0) {
              *(undefined1 *)((long)pvVar14 + uVar16) = 1;
              emit_region(param_1,uVar10,uVar16,param_4,param_5,param_6,param_7,pvVar14,param_9,
                          param_10 + 1);
              free(pvVar14);
            }
            iVar7 = 0;
            if (0 < iVar4) {
              do {
                iVar7 = iVar7 + 1;
                fputc(0x20,param_9);
              } while (iVar7 != iVar4);
            }
            fwrite(&DAT_001f8e68,1,2,param_9);
            uVar21 = *(uint *)(param_1 + 1);
            if (uVar21 <= uVar5 || param_3 == uVar5) goto LAB_0015ba08;
            uVar16 = (ulong)uVar5;
            goto LAB_0015b8d0;
          }
          if (*piVar26 == 0x18) {
            if ((puVar12 == (uint *)0x0) || (uVar6 = puVar12[1], uVar21 <= uVar6))
            goto LAB_0015bff8;
LAB_0015bcb4:
            if (uVar6 != uVar22) {
              lVar20 = lVar20 + (ulong)uVar6 * 0x50;
              uVar5 = *(uint *)(lVar20 + 0x10);
              uVar19 = uVar5 - 1;
              if (-1 < (int)uVar19) {
                lVar20 = *(long *)(lVar20 + 8);
                piVar13 = (int *)(lVar20 + (long)(int)uVar19 * 0x88);
                do {
                  if (*piVar13 - 0x17U < 2 || *piVar13 == 0x1a) {
                    if ((((puVar12 == (uint *)0x0) || (uVar5 = puVar12[5], uVar21 <= puVar12[5])) &&
                        (uVar5 = uVar21, *piVar13 == 0x17)) &&
                       (uVar5 = piVar13[0x19], piVar13[0x19] == uVar22)) {
                      uVar5 = piVar13[0x1a];
                    }
                    goto LAB_0015bd3c;
                  }
                  piVar13 = piVar13 + -0x22;
                } while (piVar13 != (int *)(lVar20 + -0x110 + ((ulong)uVar5 - (ulong)uVar19) * 0x88)
                        );
              }
              if (puVar12 == (uint *)0x0) {
                piVar13 = (int *)0x0;
                uVar5 = uVar21;
              }
              else {
                piVar13 = (int *)0x0;
                uVar5 = puVar12[5];
                if (uVar21 < puVar12[5]) {
                  uVar5 = uVar21;
                }
              }
LAB_0015bd3c:
              if (0 < iVar4) {
                iVar7 = 0;
                do {
                  iVar7 = iVar7 + 1;
                  fputc(0x20,param_9);
                } while (iVar7 != iVar4);
              }
              fwrite("do {\n",1,5,param_9);
              iVar7 = param_10 + 1;
              uVar21 = *(uint *)(param_1 + 1);
              if (uVar22 < uVar21) {
                cf_emit_block_body_part_0_isra_0(*param_1,uVar16,param_9,iVar7);
                uVar21 = *(uint *)(param_1 + 1);
              }
              uVar22 = piVar26[0x19];
              if ((uVar22 != uVar6) && (pvVar14 = calloc((ulong)uVar21,1), pvVar14 != (void *)0x0))
              {
                *(undefined1 *)((long)pvVar14 + uVar16) = 1;
                emit_region(param_1,uVar22,uVar6,param_4,param_5,param_6,param_7,pvVar14,param_9,
                            iVar7);
                free(pvVar14);
                uVar21 = *(uint *)(param_1 + 1);
              }
              if (uVar6 < uVar21) {
                cf_emit_block_body_part_0_isra_0(*param_1,uVar6,param_9,iVar7);
              }
              iVar7 = 0;
              if (0 < iVar4) {
                do {
                  iVar7 = iVar7 + 1;
                  fputc(0x20,param_9);
                } while (iVar7 != iVar4);
              }
              fwrite("} while (",1,9,param_9);
              if ((piVar13 == (int *)0x0) || (piVar13[0x12] == 0)) {
                fwrite(&DAT_001f9880,1,4,param_9);
              }
              else if (piVar13[6] == -1) {
                fwrite("__undef",1,7,param_9);
              }
              else {
                __fprintf_chk(param_9,2,&DAT_001f9928);
              }
              fwrite(&DAT_001f99a8,1,3,param_9);
              uVar21 = *(uint *)(param_1 + 1);
              if (uVar5 == param_3 || uVar21 <= uVar5) goto LAB_0015ba08;
              uVar16 = (ulong)uVar5;
              goto LAB_0015b8d0;
            }
          }
        }
      }
    }
  }
  cf_emit_block_body_part_0_isra_0(lVar20,uVar16,param_9,param_10);
  piVar13 = (int *)sr_is_switch_head(param_7,uVar16);
  if ((piVar13 != (int *)0x0) && (piVar13[4] != 0)) {
    iVar7 = piVar13[8];
    if (iVar7 != 0) {
      uVar21 = *(uint *)(param_1 + 1);
      iVar8 = 0;
      while ((uint)uVar16 < uVar21) {
        lVar20 = *param_1;
        *(undefined1 *)(param_8 + uVar16) = 1;
        lVar20 = lVar20 + uVar16 * 0x50;
        uVar6 = *(uint *)(lVar20 + 0x10);
        uVar5 = uVar6 - 1;
        if ((int)uVar5 < 0) break;
        lVar20 = *(long *)(lVar20 + 8);
        piVar26 = (int *)(lVar20 + (long)(int)uVar5 * 0x88);
        while (iVar9 = *piVar26, 1 < iVar9 - 0x17U && iVar9 != 0x1a) {
          piVar26 = piVar26 + -0x22;
          if ((int *)(lVar20 + -0x110 + ((ulong)uVar6 - (ulong)uVar5) * 0x88) == piVar26)
          goto LAB_0015c378;
        }
        if (iVar9 != 0x17) break;
        iVar8 = iVar8 + 1;
        uVar16 = (ulong)(uint)piVar26[0x1a];
        if (iVar8 == iVar7) break;
      }
    }
LAB_0015c378:
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
    }
    fwrite("switch (",1,8,param_9);
    if (*piVar13 == -1) {
      fwrite("__undef",1,7,param_9);
    }
    else {
      __fprintf_chk(param_9,2,&DAT_001f9928);
    }
    fwrite(&DAT_001f9a38,1,4,param_9);
    if (piVar13[4] != 0) {
      lVar20 = 0;
      do {
        lVar25 = *(long *)(piVar13 + 2);
        iVar7 = 0;
        lVar24 = lVar25 + lVar20 * 0x10;
        if (0 < iVar4) {
          do {
            iVar7 = iVar7 + 1;
            fputc(0x20,param_9);
          } while (iVar7 != iVar4);
        }
        if ((*(byte *)(lVar24 + 0xc) & 1) == 0) {
          __fprintf_chk(param_9,2,"case %ld:\n",*(undefined8 *)(lVar25 + lVar20 * 0x10));
          uVar21 = *(uint *)(param_1 + 1);
          uVar6 = *(uint *)(lVar24 + 8);
          if (uVar6 < uVar21) goto LAB_0015c528;
LAB_0015c484:
          bVar3 = *(byte *)(lVar24 + 0xd);
        }
        else {
          fwrite("default:\n",1,9,param_9);
          uVar21 = *(uint *)(param_1 + 1);
          uVar6 = *(uint *)(lVar24 + 8);
          if (uVar21 <= uVar6) goto LAB_0015c484;
LAB_0015c528:
          pvVar14 = calloc((ulong)uVar21,1);
          if (pvVar14 == (void *)0x0) goto LAB_0015c484;
          uVar5 = piVar13[8];
          if (uVar5 != 0 && uVar22 < uVar21) {
            lVar25 = *param_1;
            uVar19 = 0;
            uVar10 = uVar22;
            while( true ) {
              lVar18 = lVar25 + (ulong)uVar10 * 0x50;
              *(undefined1 *)((long)pvVar14 + (ulong)uVar10) = 1;
              uVar10 = *(uint *)(lVar18 + 0x10);
              uVar17 = uVar10 - 1;
              if ((int)uVar17 < 0) break;
              lVar18 = *(long *)(lVar18 + 8);
              piVar26 = (int *)(lVar18 + (long)(int)uVar17 * 0x88);
              while (iVar7 = *piVar26, 1 < iVar7 - 0x17U && iVar7 != 0x1a) {
                piVar26 = piVar26 + -0x22;
                if ((int *)(lVar18 + -0x110 + ((ulong)uVar10 - (ulong)uVar17) * 0x88) == piVar26)
                goto LAB_0015c5e0;
              }
              if (iVar7 != 0x17) break;
              uVar10 = piVar26[0x1a];
              uVar19 = uVar19 + 1;
              if (uVar21 <= uVar10 || uVar5 <= uVar19) break;
            }
          }
LAB_0015c5e0:
          emit_region(param_1,uVar6,param_3,param_4,param_5,param_6,param_7,pvVar14,param_9,
                      param_10 + 2);
          free(pvVar14);
          bVar3 = *(byte *)(lVar24 + 0xd);
        }
        if ((bVar3 & 1) == 0) {
          iVar7 = 0;
          if (0 < param_10 + 1) {
            do {
              iVar7 = iVar7 + 1;
              fputc(0x20,param_9);
            } while (iVar7 < iVar4 + 4);
          }
          fwrite("break;\n",1,7,param_9);
        }
        lVar20 = lVar20 + 1;
      } while ((uint)lVar20 < (uint)piVar13[4]);
    }
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
    }
    fwrite(&DAT_001f8e68,1,2,param_9);
    uVar21 = *(uint *)(param_1 + 1);
    uVar6 = piVar13[6];
    if (uVar6 < uVar21 && uVar6 != param_3) goto LAB_0015bfcc;
    goto LAB_0015ba08;
  }
  if (2 < *(uint *)(lVar24 + 0x30)) {
    if (iVar4 < 1) {
      fwrite("switch (expr) {\n",1,0x10,param_9);
      uVar21 = *(uint *)(lVar24 + 0x30);
      if (uVar21 != 0) goto LAB_0015cd70;
    }
    else {
      iVar7 = 0;
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
      fwrite("switch (expr) {\n",1,0x10,param_9);
      uVar21 = *(uint *)(lVar24 + 0x30);
      if (uVar21 == 0) {
LAB_0015ce90:
        iVar7 = 0;
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
      else {
LAB_0015cd70:
        uVar23 = 0;
        do {
          iVar7 = 0;
          if (0 < iVar4) {
            do {
              iVar7 = iVar7 + 1;
              fputc(0x20,param_9);
            } while (iVar7 != iVar4);
            uVar21 = *(uint *)(lVar24 + 0x30);
          }
          if (uVar21 - 1 == (int)uVar23) {
            fwrite("default:\n",1,9,param_9);
          }
          else {
            __fprintf_chk(param_9,2,"case %u:\n",uVar23 & 0xffffffff);
          }
          uVar21 = *(uint *)(param_1 + 1);
          uVar6 = *(uint *)(*(long *)(lVar24 + 0x28) + uVar23 * 4);
          pvVar14 = calloc((ulong)uVar21,1);
          if (pvVar14 != (void *)0x0) {
            *(undefined1 *)((long)pvVar14 + uVar16) = 1;
            if ((uVar6 < uVar21) && ((*(byte *)(param_8 + (ulong)uVar6) & 1) == 0)) {
              emit_region(param_1,uVar6,param_3,param_4,param_5,param_6,param_7,pvVar14,param_9,
                          param_10 + 2);
            }
            free(pvVar14);
          }
          iVar7 = 0;
          if (0 < param_10 + 1) {
            do {
              iVar7 = iVar7 + 1;
              fputc(0x20,param_9);
            } while (iVar7 < (param_10 + 1) * 4);
          }
          fwrite("break;\n",1,7,param_9);
          uVar21 = *(uint *)(lVar24 + 0x30);
          uVar23 = uVar23 + 1;
        } while ((uint)uVar23 < uVar21);
        if (0 < iVar4) goto LAB_0015ce90;
      }
    }
    lVar20 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar20 == 0) {
      pcVar15 = "}\n";
LAB_0015bf90:
      fwrite(pcVar15,1,2,param_9);
      return;
    }
    goto LAB_0015d440;
  }
  if (piVar26 == (int *)0x0) goto LAB_0015ba08;
  iVar7 = *piVar26;
  if (iVar7 == 0x18) {
    uVar6 = piVar26[0x19];
    uVar21 = *(uint *)(param_1 + 1);
    if (param_3 != uVar6 && uVar6 < uVar21) goto LAB_0015bfcc;
    goto LAB_0015ba08;
  }
  if (iVar7 == 0x1a) {
    iVar7 = 0;
    if (0 < param_10) {
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
    }
    fwrite("return ",1,7,param_9);
    if (piVar26[0x19] == -1) {
      uVar21 = piVar26[0x12];
      if (uVar21 < 2) goto LAB_0015bf48;
      if (*(long *)(piVar26 + 0xc) == 0) {
        fwrite("call(",1,5,param_9);
      }
      else {
        __fprintf_chk(param_9,2,"sub_%lx(");
      }
      lVar20 = 0;
      if (piVar26[0x18] != 0) {
        do {
          uVar21 = (uint)lVar20;
          while( true ) {
            if (uVar21 != 0) {
              fwrite(", ",1,2,param_9);
            }
            if (*(int *)(*(long *)(piVar26 + 0x14) + lVar20 * 0x10) != -1) break;
            fwrite("__undef",1,7,param_9);
            lVar20 = lVar20 + 1;
            uVar21 = (uint)lVar20;
            if ((uint)piVar26[0x18] <= uVar21) goto LAB_0015c6e8;
          }
          __fprintf_chk(param_9,2,&DAT_001f9928);
          lVar20 = lVar20 + 1;
        } while ((uint)lVar20 < (uint)piVar26[0x18]);
      }
LAB_0015c6e8:
      fputc(0x29,param_9);
    }
    else {
      uVar21 = piVar26[0x12];
LAB_0015bf48:
      if ((uVar21 == 0) || (piVar26[6] == -1)) {
        fputc(0x30,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
    }
    lVar20 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar20 == 0) {
      pcVar15 = ";\n";
      goto LAB_0015bf90;
    }
    goto LAB_0015d440;
  }
  if (iVar7 != 0x17) goto LAB_0015ba08;
  uVar21 = piVar26[0x19];
  uVar6 = piVar26[0x1a];
  if ((param_5 != (undefined8 *)0x0) && (param_3 < *(uint *)(param_1 + 1))) {
    local_80[0] = *(uint *)(param_1 + 1);
    local_78 = param_5;
    plStack_70 = param_1;
    iVar7 = ge_classify_edge(local_80,uVar16,uVar21);
    iVar8 = ge_classify_edge(local_80,uVar16,uVar6);
    if (iVar7 - 1U < 2) {
      if (iVar8 - 1U < 2) {
        iVar9 = 0;
        if (0 < param_10) {
          do {
            iVar9 = iVar9 + 1;
            fputc(0x20,param_9);
          } while (iVar9 != iVar4);
        }
        fwrite(&DAT_001f9ad8,1,4,param_9);
        emit_cond(param_9,piVar26);
        pcVar15 = "continue";
        if (iVar7 == 1) {
          pcVar15 = "break";
        }
        pcVar1 = "continue";
        if (iVar8 == 1) {
          pcVar1 = "break";
        }
        __fprintf_chk(param_9,2,") %s; else %s;\n",pcVar15,pcVar1);
      }
      else {
        iVar8 = 0;
        if (0 < param_10) {
          do {
            iVar8 = iVar8 + 1;
            fputc(0x20,param_9);
          } while (iVar8 != iVar4);
        }
        fwrite(&DAT_001f9ad8,1,4,param_9);
        if (piVar26[0x12] == 0) {
          fwrite(&DAT_001f9880,1,4,param_9);
        }
        else if (piVar26[6] == -1) {
          fwrite("__undef",1,7,param_9);
        }
        else {
          __fprintf_chk(param_9,2,&DAT_001f9928);
        }
        pcVar15 = "continue";
        if (iVar7 == 1) {
          pcVar15 = "break";
        }
        __fprintf_chk(param_9,2,") %s;\n",pcVar15);
        if ((uVar6 < *(uint *)(param_1 + 1) && param_3 != uVar6) &&
           ((*(byte *)(param_8 + (ulong)uVar6) & 1) == 0)) {
          emit_region(param_1,uVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10
                     );
        }
      }
    }
    else {
      if (1 < iVar8 - 1U) goto LAB_0015ba6c;
      iVar7 = 0;
      if (0 < param_10) {
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
      fwrite("if (!(",1,6,param_9);
      if (piVar26[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar26[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      pcVar15 = "continue";
      if (iVar8 == 1) {
        pcVar15 = "break";
      }
      __fprintf_chk(param_9,2,")) %s;\n",pcVar15);
      if ((uVar21 < *(uint *)(param_1 + 1) && param_3 != uVar21) &&
         ((*(byte *)(param_8 + (ulong)uVar21) & 1) == 0)) {
        emit_region(param_1,uVar21,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10)
        ;
      }
    }
    goto LAB_0015ba08;
  }
LAB_0015ba6c:
  if (param_6 == 0) {
    uVar22 = *(uint *)(param_1 + 1);
LAB_0015c1b8:
    uVar5 = find_join_isra_0(*param_1,uVar22,uVar21,uVar6);
    if (uVar22 <= uVar5) {
      local_80[0] = uVar22;
      local_78 = param_5;
      plStack_70 = param_1;
      iVar8 = ge_classify_edge(local_80,uVar16,uVar21);
      iVar9 = ge_classify_edge(local_80,uVar16,uVar6);
      iVar7 = 0;
      if (0 < param_10) {
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
      fwrite(&DAT_001f9ad8,1,4,param_9);
      if (piVar26[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar26[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      if (iVar8 == 1) {
        fwrite(") break;",1,8,param_9);
      }
      else if (iVar8 == 2) {
        fwrite(") continue;",1,0xb,param_9);
      }
      else {
        __fprintf_chk(param_9,2,") goto bb%u;",uVar21);
      }
      if (iVar9 == 1) {
        fwrite(" else break;\n",1,0xd,param_9);
      }
      else if (iVar9 == 2) {
        fwrite(" else continue;\n",1,0x10,param_9);
      }
      else {
        __fprintf_chk(param_9,2," else goto bb%u;\n",uVar6);
      }
      goto LAB_0015ba08;
    }
  }
  else {
    uVar5 = sa_find_join(param_6,param_1,uVar16);
    uVar22 = *(uint *)(param_1 + 1);
    if (uVar22 <= uVar5) goto LAB_0015c1b8;
  }
  uVar23 = (ulong)uVar5;
  if (uVar5 == uVar6) {
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
    }
    fwrite(&DAT_001f9ad8,1,4,param_9);
    if (piVar26[0x12] == 0) {
      fwrite(&DAT_001f9880,1,4,param_9);
    }
    else if (piVar26[6] == -1) {
      fwrite("__undef",1,7,param_9);
    }
    else {
      __fprintf_chk(param_9,2,&DAT_001f9928);
    }
    fwrite(&DAT_001f9a38,1,4,param_9);
    pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
    if (pvVar14 != (void *)0x0) {
      *(undefined1 *)((long)pvVar14 + uVar16) = 1;
      emit_region(param_1,uVar21,uVar6,param_4,param_5,param_6,param_7,pvVar14,param_9,param_10 + 1)
      ;
      if (uVar6 < *(uint *)(param_1 + 1)) {
        emit_phi_assigns_part_0_isra_0(*param_1,uVar6,uVar21,param_9,param_10 + 1);
      }
      free(pvVar14);
    }
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        iVar7 = iVar7 + 1;
        fputc(0x20,param_9);
      } while (iVar7 != iVar4);
    }
  }
  else {
    iVar7 = 0;
    if (uVar5 == uVar21) {
      if (0 < iVar4) {
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
      fwrite("if (!(",1,6,param_9);
      if (piVar26[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar26[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      fwrite(")) {\n",1,5,param_9);
      pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
      if (pvVar14 != (void *)0x0) {
        *(undefined1 *)((long)pvVar14 + uVar16) = 1;
        emit_region(param_1,uVar6,uVar21,param_4,param_5,param_6,param_7,pvVar14,param_9,
                    param_10 + 1);
        if (uVar21 < *(uint *)(param_1 + 1)) {
          emit_phi_assigns_part_0_isra_0(*param_1,uVar21,uVar6,param_9,param_10 + 1);
        }
        free(pvVar14);
      }
      if (0 < iVar4) {
        iVar7 = 0;
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
    }
    else {
      if (0 < param_10) {
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
      fwrite(&DAT_001f9ad8,1,4,param_9);
      if (piVar26[0x12] == 0) {
        fwrite(&DAT_001f9880,1,4,param_9);
      }
      else if (piVar26[6] == -1) {
        fwrite("__undef",1,7,param_9);
      }
      else {
        __fprintf_chk(param_9,2,&DAT_001f9928);
      }
      fwrite(&DAT_001f9a38,1,4,param_9);
      pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
      if (pvVar14 != (void *)0x0) {
        *(undefined1 *)((long)pvVar14 + uVar16) = 1;
        emit_region(param_1,uVar21,uVar5,param_4,param_5,param_6,param_7,pvVar14,param_9,
                    param_10 + 1);
        if (uVar5 < *(uint *)(param_1 + 1)) {
          emit_phi_assigns_part_0_isra_0(*param_1,uVar23,uVar21,param_9,param_10 + 1);
        }
        free(pvVar14);
      }
      if (iVar4 < 1) {
        fwrite("} else {\n",1,9,param_9);
        pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
        if (pvVar14 != (void *)0x0) goto LAB_0015bbec;
      }
      else {
        iVar7 = 0;
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
        fwrite("} else {\n",1,9,param_9);
        pvVar14 = calloc((ulong)*(uint *)(param_1 + 1),1);
        if (pvVar14 != (void *)0x0) {
LAB_0015bbec:
          *(undefined1 *)((long)pvVar14 + uVar16) = 1;
          emit_region(param_1,uVar6,uVar23,param_4,param_5,param_6,param_7,pvVar14,param_9,
                      param_10 + 1);
          if (uVar5 < *(uint *)(param_1 + 1)) {
            emit_phi_assigns_part_0_isra_0(*param_1,uVar23,uVar6,param_9,param_10 + 1);
          }
          free(pvVar14);
          if (iVar4 < 1) goto LAB_0015bc70;
        }
        iVar7 = 0;
        do {
          iVar7 = iVar7 + 1;
          fputc(0x20,param_9);
        } while (iVar7 != iVar4);
      }
    }
  }
LAB_0015bc70:
  fwrite(&DAT_001f8e68,1,2,param_9);
  uVar21 = *(uint *)(param_1 + 1);
  uVar16 = uVar23;
  if (uVar5 == param_3 || uVar21 <= uVar5) goto LAB_0015ba08;
  goto LAB_0015b8d0;
LAB_0015bfcc:
  uVar16 = (ulong)uVar6;
  if ((*(byte *)(param_8 + (ulong)uVar6) & 1) != 0) goto LAB_0015ba08;
  goto LAB_0015b8d0;
}

