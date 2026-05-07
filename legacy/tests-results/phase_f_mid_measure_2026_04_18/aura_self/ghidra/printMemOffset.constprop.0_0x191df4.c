
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printMemOffset_constprop_0(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  ulong uVar11;
  char *pcVar12;
  uint uVar13;
  ulong uVar14;
  long lVar15;
  byte *pbVar16;
  long lVar17;
  undefined8 uVar18;
  byte bVar20;
  byte bVar21;
  byte bVar22;
  byte bVar23;
  byte bVar24;
  byte bVar25;
  byte bVar26;
  undefined1 auVar19 [16];
  byte local_50 [4];
  byte bStack_4c;
  byte bStack_4b;
  byte bStack_4a;
  byte bStack_49;
  undefined8 uStack_48;
  
  pbVar16 = local_50;
  uStack_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar9 = MCInst_getOperand(param_1,0);
  uVar10 = MCInst_getOperand(param_1,1);
  lVar17 = *(long *)(param_1 + 800);
  if (*(int *)(lVar17 + 0x60) == 0) {
    iVar5 = MCOperand_getReg(uVar10);
  }
  else {
    lVar15 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar15 = lVar15 + (ulong)*(byte *)(lVar15 + 0xa0) * 0x30;
    *(undefined4 *)(lVar15 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar15 + 0xb0) = 0;
    *(undefined8 *)(lVar15 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar15 + 0xc0) = 0;
    *(undefined1 *)(lVar15 + 200) = uVar2;
    uVar6 = MCInst_getOpcode(param_1);
    pcVar12 = (char *)X86_get_op_access(lVar17,uVar6,
                                        *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar12 == (char *)0x0) {
      local_50[0] = 0;
    }
    else {
      uVar11 = 0;
      if (*pcVar12 != '\0') {
        do {
          uVar14 = uVar11;
          uVar13 = (uint)uVar14;
          uVar8 = uVar13 + 1;
          uVar1 = uVar8 & 0xff;
          uVar11 = (ulong)uVar1;
        } while (pcVar12[uVar11] != '\0');
        if (uVar1 != 0) {
          if ((uVar13 - 7 & 0xff) < 0xf8) {
            uVar7 = 0;
            if (uVar13 < 0xf) {
LAB_0019214c:
              uVar18 = NEON_rev64(*(undefined8 *)(pcVar12 + ((uVar14 - 7) - (ulong)(byte)uVar7)),1);
              bVar20 = (byte)((ulong)uVar18 >> 8);
              bVar21 = (byte)((ulong)uVar18 >> 0x10);
              bVar22 = (byte)((ulong)uVar18 >> 0x18);
              bVar23 = (byte)((ulong)uVar18 >> 0x20);
              bVar24 = (byte)((ulong)uVar18 >> 0x28);
              bVar25 = (byte)((ulong)uVar18 >> 0x30);
              bVar26 = (byte)((ulong)uVar18 >> 0x38);
              *(ulong *)(local_50 + uVar7) =
                   CONCAT17(bVar26 & ~-(bVar26 == 0x80),
                            CONCAT16(bVar25 & ~-(bVar25 == 0x80),
                                     CONCAT15(bVar24 & ~-(bVar24 == 0x80),
                                              CONCAT14(bVar23 & ~-(bVar23 == 0x80),
                                                       CONCAT13(bVar22 & ~-(bVar22 == 0x80),
                                                                CONCAT12(bVar21 & ~-(bVar21 == 0x80)
                                                                         ,CONCAT11(bVar20 & ~-(
                                                  bVar20 == 0x80),
                                                  (byte)uVar18 & ~-((byte)uVar18 == 0x80))))))));
              uVar7 = uVar7 + ((uint)uVar11 & 0xfffffff8) & 0xff;
              if ((uVar11 & 7) != 0) {
                uVar8 = uVar13 - uVar7;
LAB_00192188:
                bVar20 = pcVar12[(int)uVar8];
                uVar8 = uVar7 + 1 & 0xff;
                if (bVar20 == 0x80) {
                  bVar20 = 0;
                }
                local_50[uVar7] = bVar20;
                if ((uVar7 + 1 & 0xff) <= uVar13) {
                  uVar1 = uVar7 + 2 & 0xff;
                  bVar20 = pcVar12[(int)(uVar13 - uVar8)];
                  if (bVar20 == 0x80) {
                    bVar20 = 0;
                  }
                  local_50[uVar8] = bVar20;
                  if ((uVar7 + 2 & 0xff) <= uVar13) {
                    uVar8 = uVar7 + 3 & 0xff;
                    bVar20 = pcVar12[(int)(uVar13 - uVar1)];
                    if (bVar20 == 0x80) {
                      bVar20 = 0;
                    }
                    local_50[uVar1] = bVar20;
                    if ((uVar7 + 3 & 0xff) <= uVar13) {
                      uVar1 = uVar7 + 4 & 0xff;
                      bVar20 = pcVar12[(int)(uVar13 - uVar8)];
                      if (bVar20 == 0x80) {
                        bVar20 = 0;
                      }
                      local_50[uVar8] = bVar20;
                      if ((uVar7 + 4 & 0xff) <= uVar13) {
                        uVar8 = uVar7 + 5 & 0xff;
                        bVar20 = pcVar12[(int)(uVar13 - uVar1)];
                        if (bVar20 == 0x80) {
                          bVar20 = 0;
                        }
                        local_50[uVar1] = bVar20;
                        if ((uVar7 + 5 & 0xff) <= uVar13) {
                          uVar1 = uVar7 + 6 & 0xff;
                          bVar20 = pcVar12[(int)(uVar13 - uVar8)];
                          if (bVar20 == 0x80) {
                            bVar20 = 0;
                          }
                          local_50[uVar8] = bVar20;
                          if ((uVar7 + 6 & 0xff) <= uVar13) {
                            bVar20 = pcVar12[(int)(uVar13 - uVar1)];
                            if (bVar20 == 0x80) {
                              bVar20 = 0;
                            }
                            local_50[uVar1] = bVar20;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            else {
              uVar1 = uVar1 >> 4;
              auVar19 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xf)),
                                _DAT_0020c0a0);
              uStack_48 = CONCAT17(auVar19[0xf] & ~-(auVar19[0xf] == 0x80),
                                   CONCAT16(auVar19[0xe] & ~-(auVar19[0xe] == 0x80),
                                            CONCAT15(auVar19[0xd] & ~-(auVar19[0xd] == 0x80),
                                                     CONCAT14(auVar19[0xc] &
                                                              ~-(auVar19[0xc] == 0x80),
                                                              CONCAT13(auVar19[0xb] &
                                                                       ~-(auVar19[0xb] == 0x80),
                                                                       CONCAT12(auVar19[10] &
                                                                                ~-(auVar19[10] ==
                                                                                  0x80),CONCAT11(
                                                  auVar19[9] & ~-(auVar19[9] == 0x80),
                                                  auVar19[8] & ~-(auVar19[8] == 0x80))))))));
              local_50[0] = auVar19[0] & ~-(auVar19[0] == 0x80);
              local_50[1] = auVar19[1] & ~-(auVar19[1] == 0x80);
              local_50[2] = auVar19[2] & ~-(auVar19[2] == 0x80);
              local_50[3] = auVar19[3] & ~-(auVar19[3] == 0x80);
              bStack_4c = auVar19[4] & ~-(auVar19[4] == 0x80);
              bStack_4b = auVar19[5] & ~-(auVar19[5] == 0x80);
              bStack_4a = auVar19[6] & ~-(auVar19[6] == 0x80);
              bStack_49 = auVar19[7] & ~-(auVar19[7] == 0x80);
              if (((((uVar1 != 1) &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x1f)),
                             _DAT_0020c0a0), uVar1 != 2)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x2f)),
                            _DAT_0020c0a0), uVar1 != 3)) &&
                  ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x3f)),
                              _DAT_0020c0a0), uVar1 != 4 &&
                     (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x4f)),
                              _DAT_0020c0a0), uVar1 != 5)) &&
                    ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x5f)),
                              _DAT_0020c0a0), uVar1 != 6 &&
                     ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x6f)),
                               _DAT_0020c0a0), uVar1 != 7 &&
                      (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x7f)),
                               _DAT_0020c0a0), uVar1 != 8)))))) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x8f)),
                            _DAT_0020c0a0), uVar1 != 9)))) &&
                 ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0x9f)),
                             _DAT_0020c0a0), uVar1 != 10 &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xaf)),
                             _DAT_0020c0a0), uVar1 != 0xb)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xbf)),
                            _DAT_0020c0a0), uVar1 != 0xc)) &&
                  ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xcf)),
                            _DAT_0020c0a0), uVar1 != 0xd &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xdf)),
                            _DAT_0020c0a0), uVar1 == 0xf)))))) {
                a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar12 + (uVar14 - 0xef)),_DAT_0020c0a0);
              }
              uVar7 = uVar8 & 0xf0;
              if ((uVar8 & 0xf) != 0) {
                uVar8 = uVar13 - uVar7;
                uVar11 = (ulong)((uVar8 & 0xff) + 1 & 0xff);
                if (6 < (uVar8 & 0xff)) goto LAB_0019214c;
                goto LAB_00192188;
              }
            }
          }
          else {
            pcVar12 = pcVar12 + uVar14;
            uVar8 = 0;
            do {
              cVar3 = *pcVar12;
              pcVar4 = (char *)pbVar16;
              while (cVar3 != -0x80) {
                uVar1 = uVar8 + 1;
                *pcVar4 = cVar3;
                pcVar12 = pcVar12 + -1;
                uVar8 = uVar1 & 0xff;
                if (uVar13 < (uVar1 & 0xff)) goto LAB_00192278;
                pcVar4 = pcVar4 + 1;
                cVar3 = *pcVar12;
              }
              uVar1 = uVar8 + 1;
              pbVar16 = (byte *)(pcVar4 + 1);
              *pcVar4 = '\0';
              pcVar12 = pcVar12 + -1;
              uVar8 = uVar1 & 0xff;
            } while ((uVar1 & 0xff) <= uVar13);
          }
        }
      }
    }
LAB_00192278:
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar20 = *(byte *)(lVar17 + 0xa0);
    *(byte *)(lVar17 + ((ulong)bVar20 * 2 + (ulong)bVar20) * 0x10 + 0xc9) =
         local_50[(int)(uint)bVar20];
    iVar5 = MCOperand_getReg(uVar10);
  }
  if (iVar5 != 0) {
    _printOperand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fd7d0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar8 = X86_register_map(iVar5);
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xb0) = uVar8 & 0xffff;
      uVar11 = MCOperand_isImm(uVar9);
      goto joined_r0x00192300;
    }
  }
  uVar11 = MCOperand_isImm(uVar9);
joined_r0x00192300:
  if ((uVar11 & 1) != 0) {
    uVar11 = MCOperand_getImm(uVar9);
    lVar17 = *(long *)(param_1 + 800);
    if (*(int *)(lVar17 + 0x60) != 0) {
      lVar15 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar15 + (ulong)*(byte *)(lVar15 + 0xa0) * 0x30 + 0xc0) = uVar11;
    }
    if ((long)uVar11 < 0) {
      SStream_concat(param_2,"0x%lx",
                     uVar11 & *(ulong *)(PTR_arch_masks_005ffe50 + (ulong)*(uint *)(lVar17 + 4) * 8)
                    );
    }
    else if ((long)uVar11 < 10) {
      SStream_concat(param_2,&DAT_001fb420);
    }
    else {
      SStream_concat(param_2,"0x%lx");
    }
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar17 + 0xa0) = *(char *)(lVar17 + 0xa0) + '\x01';
  }
  if (uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

