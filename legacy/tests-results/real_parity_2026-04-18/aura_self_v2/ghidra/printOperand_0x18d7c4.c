
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  char *pcVar8;
  byte *pbVar9;
  uint uVar10;
  long lVar11;
  byte *pbVar12;
  uint uVar13;
  ulong uVar14;
  long lVar15;
  byte bVar17;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  byte bVar21;
  byte bVar22;
  byte bVar23;
  undefined1 auVar16 [16];
  undefined1 local_51;
  byte local_50 [4];
  byte bStack_4c;
  byte bStack_4b;
  byte bStack_4a;
  byte bStack_49;
  undefined8 uStack_48;
  
  uStack_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar6 = MCInst_getOperand(param_1,param_2,0);
  uVar7 = MCOperand_isReg();
  if ((uVar7 & 1) != 0) {
    uVar3 = MCOperand_getReg(uVar6);
    SStream_concat(param_3,&DAT_001fb4f0,
                   &AsmStrs_0 + *(ushort *)(RegAsmOffset_1 + (ulong)(uVar3 - 1) * 2));
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_0018d848;
    uVar3 = uVar3 & 0xffff;
    if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) != 0) {
      uVar3 = X86_register_map(uVar3);
      lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar11 + (ulong)*(byte *)(lVar11 + 0xa0) * 0x30 + 0xb4) = uVar3 & 0xffff;
      goto LAB_0018d848;
    }
    lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar11 + (ulong)*(byte *)(lVar11 + 0xa0) * 0x30 + 0xa8) = 1;
    uVar4 = X86_register_map(uVar3);
    lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar15 = *(long *)(*(long *)(param_1 + 800) + 0xa0);
    *(uint *)(lVar11 + (ulong)*(byte *)(lVar11 + 0xa0) * 0x30 + 0xb0) = uVar4 & 0xffff;
    uVar3 = X86_register_map(uVar3);
    uVar6 = *(undefined8 *)(param_1 + 800);
    lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined1 *)(lVar11 + (ulong)*(byte *)(lVar11 + 0xa0) * 0x30 + 200) =
         *(undefined1 *)(lVar15 + (ulong)(uVar3 & 0xffff));
    uVar5 = MCInst_getOpcode(param_1);
    pcVar8 = (char *)X86_get_op_access(uVar6,uVar5,
                                       *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar8 == (char *)0x0) {
      local_50[0] = 0;
    }
    else {
      uVar7 = 0;
      if (*pcVar8 != '\0') {
        do {
          uVar14 = uVar7;
          uVar10 = (uint)uVar14;
          uVar3 = uVar10 + 1;
          uVar4 = uVar3 & 0xff;
          uVar7 = (ulong)uVar4;
        } while (pcVar8[uVar7] != '\0');
        pbVar12 = local_50;
        if (uVar4 != 0) {
          if ((uVar10 - 7 & 0xff) < 0xf8) {
            uVar13 = 0;
            if (uVar10 < 0xf) {
LAB_0018dc2c:
              uVar6 = NEON_rev64(*(undefined8 *)(pcVar8 + ((uVar14 - 7) - (ulong)(byte)uVar13)),1);
              bVar17 = (byte)((ulong)uVar6 >> 8);
              bVar18 = (byte)((ulong)uVar6 >> 0x10);
              bVar19 = (byte)((ulong)uVar6 >> 0x18);
              bVar20 = (byte)((ulong)uVar6 >> 0x20);
              bVar21 = (byte)((ulong)uVar6 >> 0x28);
              bVar22 = (byte)((ulong)uVar6 >> 0x30);
              bVar23 = (byte)((ulong)uVar6 >> 0x38);
              *(ulong *)(local_50 + uVar13) =
                   CONCAT17(bVar23 & ~-(bVar23 == 0x80),
                            CONCAT16(bVar22 & ~-(bVar22 == 0x80),
                                     CONCAT15(bVar21 & ~-(bVar21 == 0x80),
                                              CONCAT14(bVar20 & ~-(bVar20 == 0x80),
                                                       CONCAT13(bVar19 & ~-(bVar19 == 0x80),
                                                                CONCAT12(bVar18 & ~-(bVar18 == 0x80)
                                                                         ,CONCAT11(bVar17 & ~-(
                                                  bVar17 == 0x80),
                                                  (byte)uVar6 & ~-((byte)uVar6 == 0x80))))))));
              uVar13 = uVar13 + ((uint)uVar7 & 0xfffffff8) & 0xff;
              if ((uVar7 & 7) != 0) {
                uVar3 = uVar10 - uVar13;
LAB_0018dc68:
                bVar17 = pcVar8[(int)uVar3];
                uVar3 = uVar13 + 1 & 0xff;
                if (bVar17 == 0x80) {
                  bVar17 = 0;
                }
                local_50[uVar13] = bVar17;
                if ((uVar13 + 1 & 0xff) <= uVar10) {
                  uVar4 = uVar13 + 2 & 0xff;
                  bVar17 = pcVar8[(int)(uVar10 - uVar3)];
                  if (bVar17 == 0x80) {
                    bVar17 = 0;
                  }
                  local_50[uVar3] = bVar17;
                  if ((uVar13 + 2 & 0xff) <= uVar10) {
                    uVar3 = uVar13 + 3 & 0xff;
                    bVar17 = pcVar8[(int)(uVar10 - uVar4)];
                    if (bVar17 == 0x80) {
                      bVar17 = 0;
                    }
                    local_50[uVar4] = bVar17;
                    if ((uVar13 + 3 & 0xff) <= uVar10) {
                      uVar4 = uVar13 + 4 & 0xff;
                      bVar17 = pcVar8[(int)(uVar10 - uVar3)];
                      if (bVar17 == 0x80) {
                        bVar17 = 0;
                      }
                      local_50[uVar3] = bVar17;
                      if ((uVar13 + 4 & 0xff) <= uVar10) {
                        uVar3 = uVar13 + 5 & 0xff;
                        bVar17 = pcVar8[(int)(uVar10 - uVar4)];
                        if (bVar17 == 0x80) {
                          bVar17 = 0;
                        }
                        local_50[uVar4] = bVar17;
                        if ((uVar13 + 5 & 0xff) <= uVar10) {
                          uVar4 = uVar13 + 6 & 0xff;
                          bVar17 = pcVar8[(int)(uVar10 - uVar3)];
                          if (bVar17 == 0x80) {
                            bVar17 = 0;
                          }
                          local_50[uVar3] = bVar17;
                          if ((uVar13 + 6 & 0xff) <= uVar10) {
                            bVar17 = pcVar8[(int)(uVar10 - uVar4)];
                            if (bVar17 == 0x80) {
                              bVar17 = 0;
                            }
                            local_50[uVar4] = bVar17;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            else {
              uVar4 = uVar4 >> 4;
              auVar16 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xf)),
                                _DAT_00209ee0);
              uStack_48 = CONCAT17(auVar16[0xf] & ~-(auVar16[0xf] == 0x80),
                                   CONCAT16(auVar16[0xe] & ~-(auVar16[0xe] == 0x80),
                                            CONCAT15(auVar16[0xd] & ~-(auVar16[0xd] == 0x80),
                                                     CONCAT14(auVar16[0xc] &
                                                              ~-(auVar16[0xc] == 0x80),
                                                              CONCAT13(auVar16[0xb] &
                                                                       ~-(auVar16[0xb] == 0x80),
                                                                       CONCAT12(auVar16[10] &
                                                                                ~-(auVar16[10] ==
                                                                                  0x80),CONCAT11(
                                                  auVar16[9] & ~-(auVar16[9] == 0x80),
                                                  auVar16[8] & ~-(auVar16[8] == 0x80))))))));
              local_50[0] = auVar16[0] & ~-(auVar16[0] == 0x80);
              local_50[1] = auVar16[1] & ~-(auVar16[1] == 0x80);
              local_50[2] = auVar16[2] & ~-(auVar16[2] == 0x80);
              local_50[3] = auVar16[3] & ~-(auVar16[3] == 0x80);
              bStack_4c = auVar16[4] & ~-(auVar16[4] == 0x80);
              bStack_4b = auVar16[5] & ~-(auVar16[5] == 0x80);
              bStack_4a = auVar16[6] & ~-(auVar16[6] == 0x80);
              bStack_49 = auVar16[7] & ~-(auVar16[7] == 0x80);
              if (((((uVar4 != 1) &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x1f)),
                             _DAT_00209ee0), uVar4 != 2)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x2f)),
                            _DAT_00209ee0), uVar4 != 3)) &&
                  ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x3f)),
                              _DAT_00209ee0), uVar4 != 4 &&
                     (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x4f)),
                              _DAT_00209ee0), uVar4 != 5)) &&
                    ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x5f)),
                              _DAT_00209ee0), uVar4 != 6 &&
                     ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x6f)),
                               _DAT_00209ee0), uVar4 != 7 &&
                      (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x7f)),
                               _DAT_00209ee0), uVar4 != 8)))))) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x8f)),
                            _DAT_00209ee0), uVar4 != 9)))) &&
                 ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0x9f)),
                             _DAT_00209ee0), uVar4 != 10 &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xaf)),
                             _DAT_00209ee0), uVar4 != 0xb)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xbf)),
                            _DAT_00209ee0), uVar4 != 0xc)) &&
                  ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xcf)),
                            _DAT_00209ee0), uVar4 != 0xd &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xdf)),
                            _DAT_00209ee0), uVar4 == 0xf)))))) {
                a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar14 - 0xef)),_DAT_00209ee0);
              }
              uVar13 = uVar3 & 0xf0;
              if ((uVar3 & 0xf) != 0) {
                uVar3 = uVar10 - uVar13;
                uVar7 = (ulong)((uVar3 & 0xff) + 1 & 0xff);
                if (6 < (uVar3 & 0xff)) goto LAB_0018dc2c;
                goto LAB_0018dc68;
              }
            }
          }
          else {
            pbVar9 = (byte *)(pcVar8 + uVar14);
            uVar3 = 0;
            do {
              bVar17 = *pbVar9;
              pbVar2 = pbVar12;
              while (bVar17 != 0x80) {
                uVar4 = uVar3 + 1;
                *pbVar2 = bVar17;
                pbVar9 = pbVar9 + -1;
                uVar3 = uVar4 & 0xff;
                if (uVar10 < (uVar4 & 0xff)) goto LAB_0018dd58;
                pbVar2 = pbVar2 + 1;
                bVar17 = *pbVar9;
              }
              uVar4 = uVar3 + 1;
              pbVar12 = pbVar2 + 1;
              *pbVar2 = 0;
              pbVar9 = pbVar9 + -1;
              uVar3 = uVar4 & 0xff;
            } while ((uVar4 & 0xff) <= uVar10);
          }
        }
      }
    }
LAB_0018dd58:
    lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar17 = *(byte *)(lVar11 + 0xa0);
    *(byte *)(lVar11 + ((ulong)bVar17 * 2 + (ulong)bVar17) * 0x10 + 0xc9) =
         local_50[(int)(uint)bVar17];
    *(byte *)(lVar11 + 0xa0) = bVar17 + 1;
    goto LAB_0018d848;
  }
  uVar7 = MCOperand_isImm(uVar6);
  if ((uVar7 & 1) == 0) goto LAB_0018d848;
  uVar7 = MCOperand_getImm(uVar6);
  uVar6 = MCInst_getOpcode(param_1);
  uVar3 = X86_immediate_size(uVar6,&local_51);
  uVar3 = uVar3 & 0xff;
  uVar4 = uVar3;
  if (uVar3 == 1) {
    uVar10 = **(uint **)(param_1 + 0x310);
    uVar14 = uVar7 & 0xff;
    if (uVar10 < 0x1ce) {
      if (uVar10 < 0x1cc) {
        if (0xac < uVar10) {
          if (uVar10 != 0xee) {
            if (uVar10 == 0x15f) goto LAB_0018dfa8;
            if (uVar10 != 0xe5) goto LAB_0018df20;
          }
LAB_0018de88:
          uVar7 = uVar7 & 0xff;
          if (uVar7 < 10) goto LAB_0018df94;
          SStream_concat(param_3,"$0x%x",uVar7);
          goto LAB_0018d918;
        }
        if (0xa9 < uVar10) goto LAB_0018de28;
        if (uVar10 == 0x18) goto LAB_0018df88;
      }
      goto LAB_0018df20;
    }
    if (uVar10 == 0x279) goto LAB_0018dfa8;
    if (uVar10 < 0x27a) {
      if (uVar10 == 0x200) {
LAB_0018df88:
        uVar7 = uVar14;
        if (uVar14 < 10) goto LAB_0018df94;
        goto LAB_0018d8f0;
      }
      if (uVar10 == 0x203) goto LAB_0018de88;
    }
    else if (uVar10 == 0x5df) goto LAB_0018df88;
LAB_0018df20:
    uVar7 = uVar14;
    uVar14 = uVar7;
    if ((long)uVar7 < 10) {
      SStream_concat(param_3,&DAT_001fb510,uVar7);
      goto LAB_0018d918;
    }
LAB_0018de38:
    uVar7 = uVar14;
    SStream_concat(param_3,"$0x%lx",uVar7);
  }
  else {
    uVar10 = **(uint **)(param_1 + 0x310);
    uVar14 = uVar7;
    if (uVar10 < 0x1ce) {
      if (0x1cb < uVar10) goto LAB_0018df20;
      if (0xac < uVar10) {
        if (uVar10 != 0xee) {
          if (uVar10 == 0x15f) goto LAB_0018dfa8;
          if (uVar10 != 0xe5) goto LAB_0018ded0;
        }
        goto LAB_0018de88;
      }
      if (uVar10 < 0xaa) {
        if (uVar10 == 0x18) goto LAB_0018d8e0;
        goto LAB_0018ded0;
      }
LAB_0018de28:
      uVar3 = 4;
      if ((int)param_2 == 1) {
        uVar3 = 2;
        uVar14 = uVar14 & 0xffff;
      }
      goto LAB_0018de38;
    }
    if (uVar10 == 0x279) {
LAB_0018dfa8:
      uVar7 = uVar14;
      if (uVar14 < 10) goto LAB_0018df94;
      uVar7 = uVar14 & 0xffff;
      SStream_concat(param_3,"$0x%x",uVar7);
    }
    else {
      if (uVar10 < 0x27a) {
        if (uVar10 != 0x200) {
          if (uVar10 == 0x203) goto LAB_0018de88;
LAB_0018ded0:
          if (-1 < (long)uVar7) goto LAB_0018df20;
          if (*(int *)(*(long *)(param_1 + 800) + 100) != 0) {
            if (uVar3 != 0) {
              if (uVar3 == 2) {
                uVar14 = uVar7 & 0xffff;
              }
              else {
                uVar14 = uVar7 & 0xffffffff;
                if (uVar3 != 4) {
                  uVar14 = uVar7;
                }
              }
            }
            goto LAB_0018de38;
          }
          if (uVar7 == 0x8000000000000000) {
            SStream_concat0(param_3,"$0x8000000000000000");
          }
          else if ((long)uVar7 < -9) {
            SStream_concat(param_3,"$-0x%lx",-uVar7);
          }
          else {
            SStream_concat(param_3,"$-%lu",-uVar7);
          }
          goto LAB_0018d918;
        }
      }
      else if (uVar10 != 0x5df) goto LAB_0018ded0;
LAB_0018d8e0:
      if (uVar7 < 10) {
LAB_0018df94:
        SStream_concat(param_3,&DAT_001fb530,uVar7);
      }
      else {
        if (uVar3 == 0) {
          uVar4 = (uint)*(byte *)(param_1 + 0x334);
        }
LAB_0018d8f0:
        uVar7 = uVar14 & *(ulong *)(PTR_arch_masks_005ffe50 + (long)(int)uVar4 * 8);
        SStream_concat(param_3,"$0x%lx",uVar7);
      }
    }
  }
LAB_0018d918:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar17 = *(byte *)(lVar11 + 0xa0);
    if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) {
      lVar15 = lVar11 + ((ulong)bVar17 * 2 + (ulong)bVar17) * 0x10;
      *(undefined4 *)(lVar15 + 0xa8) = 2;
      *(undefined1 *)(param_1 + 5) = 1;
      *(ulong *)(lVar15 + 0xb0) = uVar7;
      if (uVar3 == 0) {
        cVar1 = *(char *)(param_1 + 6);
        if (cVar1 == '\0') {
          cVar1 = *(char *)(param_1 + 0x334);
        }
        *(char *)(lVar15 + 200) = cVar1;
      }
      else {
        *(char *)(lVar15 + 200) = (char)uVar3;
        *(undefined1 *)(lVar11 + 0x22c) = local_51;
      }
      *(byte *)(lVar11 + 0xa0) = bVar17 + 1;
    }
    else {
      lVar11 = lVar11 + ((ulong)bVar17 * 2 + (ulong)bVar17) * 0x10;
      *(undefined4 *)(lVar11 + 0xa8) = 3;
      *(ulong *)(lVar11 + 0xc0) = uVar7;
    }
  }
LAB_0018d848:
  if (uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

