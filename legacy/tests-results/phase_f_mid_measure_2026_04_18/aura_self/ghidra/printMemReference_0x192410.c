
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printMemReference(long param_1,ulong param_2,undefined8 param_3)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulong uVar14;
  char *pcVar15;
  long lVar16;
  long lVar17;
  uint uVar18;
  byte *pbVar19;
  ulong uVar20;
  undefined8 uVar21;
  byte bVar23;
  byte bVar24;
  byte bVar25;
  byte bVar26;
  byte bVar27;
  byte bVar28;
  byte bVar29;
  undefined1 auVar22 [16];
  byte local_70 [4];
  byte bStack_6c;
  byte bStack_6b;
  byte bStack_6a;
  byte bStack_69;
  undefined8 uStack_68;
  
  pbVar19 = local_70;
  iVar4 = (int)param_2;
  uStack_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar10 = MCInst_getOperand(param_1,param_2,0);
  uVar11 = MCInst_getOperand(param_1,iVar4 + 2);
  uVar12 = MCInst_getOperand(param_1,iVar4 + 3);
  uVar13 = MCInst_getOperand(param_1,iVar4 + 4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_0019249c;
  lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  lVar16 = lVar16 + (ulong)*(byte *)(lVar16 + 0xa0) * 0x30;
  *(undefined4 *)(lVar16 + 0xa8) = 3;
  uVar2 = *(undefined1 *)(param_1 + 0x328);
  *(undefined4 *)(lVar16 + 0xb0) = 0;
  *(undefined1 *)(lVar16 + 200) = uVar2;
  MCOperand_getReg(uVar10);
  uVar7 = X86_register_map();
  lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(uint *)(lVar16 + (ulong)*(byte *)(lVar16 + 0xa0) * 0x30 + 0xb4) = uVar7 & 0xffff;
  iVar6 = MCOperand_getReg(uVar11);
  if (iVar6 == 0x1e) {
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar14 = (ulong)*(byte *)(lVar16 + 0xa0);
  }
  else {
    MCOperand_getReg(uVar11);
    uVar7 = X86_register_map();
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar14 = (ulong)*(byte *)(lVar16 + 0xa0);
    *(uint *)(lVar16 + uVar14 * 0x30 + 0xb8) = uVar7 & 0xffff;
  }
  uVar21 = *(undefined8 *)(param_1 + 800);
  lVar16 = lVar16 + uVar14 * 0x30;
  *(undefined4 *)(lVar16 + 0xbc) = 1;
  *(undefined8 *)(lVar16 + 0xc0) = 0;
  uVar8 = MCInst_getOpcode(param_1);
  pcVar15 = (char *)X86_get_op_access(uVar21,uVar8,
                                      *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
  if (pcVar15 == (char *)0x0) {
    local_70[0] = 0;
  }
  else {
    uVar14 = 0;
    if (*pcVar15 != '\0') {
      do {
        uVar20 = uVar14;
        uVar18 = (uint)uVar20;
        uVar7 = uVar18 + 1;
        uVar1 = uVar7 & 0xff;
        uVar14 = (ulong)uVar1;
      } while (pcVar15[uVar14] != '\0');
      if (uVar1 != 0) {
        if ((uVar18 - 7 & 0xff) < 0xf8) {
          uVar9 = 0;
          if (uVar18 < 0xf) {
LAB_00192924:
            uVar21 = NEON_rev64(*(undefined8 *)(pcVar15 + ((uVar20 - 7) - (ulong)(byte)uVar9)),1);
            bVar23 = (byte)((ulong)uVar21 >> 8);
            bVar24 = (byte)((ulong)uVar21 >> 0x10);
            bVar25 = (byte)((ulong)uVar21 >> 0x18);
            bVar26 = (byte)((ulong)uVar21 >> 0x20);
            bVar27 = (byte)((ulong)uVar21 >> 0x28);
            bVar28 = (byte)((ulong)uVar21 >> 0x30);
            bVar29 = (byte)((ulong)uVar21 >> 0x38);
            *(ulong *)(local_70 + uVar9) =
                 CONCAT17(bVar29 & ~-(bVar29 == 0x80),
                          CONCAT16(bVar28 & ~-(bVar28 == 0x80),
                                   CONCAT15(bVar27 & ~-(bVar27 == 0x80),
                                            CONCAT14(bVar26 & ~-(bVar26 == 0x80),
                                                     CONCAT13(bVar25 & ~-(bVar25 == 0x80),
                                                              CONCAT12(bVar24 & ~-(bVar24 == 0x80),
                                                                       CONCAT11(bVar23 & ~-(bVar23 
                                                  == 0x80),(byte)uVar21 & ~-((byte)uVar21 == 0x80)))
                                                  )))));
            uVar9 = uVar9 + ((uint)uVar14 & 0xfffffff8) & 0xff;
            if ((uVar14 & 7) != 0) {
              uVar7 = uVar18 - uVar9;
LAB_00192960:
              bVar23 = pcVar15[(int)uVar7];
              uVar7 = uVar9 + 1 & 0xff;
              if (bVar23 == 0x80) {
                bVar23 = 0;
              }
              local_70[uVar9] = bVar23;
              if ((uVar9 + 1 & 0xff) <= uVar18) {
                uVar1 = uVar9 + 2 & 0xff;
                bVar23 = pcVar15[(int)(uVar18 - uVar7)];
                if (bVar23 == 0x80) {
                  bVar23 = 0;
                }
                local_70[uVar7] = bVar23;
                if ((uVar9 + 2 & 0xff) <= uVar18) {
                  uVar7 = uVar9 + 3 & 0xff;
                  bVar23 = pcVar15[(int)(uVar18 - uVar1)];
                  if (bVar23 == 0x80) {
                    bVar23 = 0;
                  }
                  local_70[uVar1] = bVar23;
                  if ((uVar9 + 3 & 0xff) <= uVar18) {
                    uVar1 = uVar9 + 4 & 0xff;
                    bVar23 = pcVar15[(int)(uVar18 - uVar7)];
                    if (bVar23 == 0x80) {
                      bVar23 = 0;
                    }
                    local_70[uVar7] = bVar23;
                    if ((uVar9 + 4 & 0xff) <= uVar18) {
                      uVar7 = uVar9 + 5 & 0xff;
                      bVar23 = pcVar15[(int)(uVar18 - uVar1)];
                      if (bVar23 == 0x80) {
                        bVar23 = 0;
                      }
                      local_70[uVar1] = bVar23;
                      if ((uVar9 + 5 & 0xff) <= uVar18) {
                        uVar1 = uVar9 + 6 & 0xff;
                        bVar23 = pcVar15[(int)(uVar18 - uVar7)];
                        if (bVar23 == 0x80) {
                          bVar23 = 0;
                        }
                        local_70[uVar7] = bVar23;
                        if ((uVar9 + 6 & 0xff) <= uVar18) {
                          bVar23 = pcVar15[(int)(uVar18 - uVar1)];
                          if (bVar23 == 0x80) {
                            bVar23 = 0;
                          }
                          local_70[uVar1] = bVar23;
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
            auVar22 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xf)),
                              _DAT_0020c0a0);
            uStack_68 = CONCAT17(auVar22[0xf] & ~-(auVar22[0xf] == 0x80),
                                 CONCAT16(auVar22[0xe] & ~-(auVar22[0xe] == 0x80),
                                          CONCAT15(auVar22[0xd] & ~-(auVar22[0xd] == 0x80),
                                                   CONCAT14(auVar22[0xc] & ~-(auVar22[0xc] == 0x80),
                                                            CONCAT13(auVar22[0xb] &
                                                                     ~-(auVar22[0xb] == 0x80),
                                                                     CONCAT12(auVar22[10] &
                                                                              ~-(auVar22[10] == 0x80
                                                                                ),CONCAT11(auVar22[9
                                                  ] & ~-(auVar22[9] == 0x80),
                                                  auVar22[8] & ~-(auVar22[8] == 0x80))))))));
            local_70[0] = auVar22[0] & ~-(auVar22[0] == 0x80);
            local_70[1] = auVar22[1] & ~-(auVar22[1] == 0x80);
            local_70[2] = auVar22[2] & ~-(auVar22[2] == 0x80);
            local_70[3] = auVar22[3] & ~-(auVar22[3] == 0x80);
            bStack_6c = auVar22[4] & ~-(auVar22[4] == 0x80);
            bStack_6b = auVar22[5] & ~-(auVar22[5] == 0x80);
            bStack_6a = auVar22[6] & ~-(auVar22[6] == 0x80);
            bStack_69 = auVar22[7] & ~-(auVar22[7] == 0x80);
            if ((((((uVar1 != 1) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x1f)),
                            _DAT_0020c0a0), uVar1 != 2)) &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x2f)),
                           _DAT_0020c0a0), uVar1 != 3)) &&
                 ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x3f)),
                           _DAT_0020c0a0), uVar1 != 4 &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x4f)),
                           _DAT_0020c0a0), uVar1 != 5)))) &&
                ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x5f)),_DAT_0020c0a0
                         ), uVar1 != 6 &&
                 ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x6f)),
                           _DAT_0020c0a0), uVar1 != 7 &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x7f)),
                           _DAT_0020c0a0), uVar1 != 8)))))) &&
               ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x8f)),_DAT_0020c0a0)
                , uVar1 != 9 &&
                ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0x9f)),
                            _DAT_0020c0a0), uVar1 != 10 &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xaf)),
                            _DAT_0020c0a0), uVar1 != 0xb)) &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xbf)),
                           _DAT_0020c0a0), uVar1 != 0xc)) &&
                 ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xcf)),
                           _DAT_0020c0a0), uVar1 != 0xd &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xdf)),
                           _DAT_0020c0a0), uVar1 == 0xf)))))))) {
              a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar20 - 0xef)),_DAT_0020c0a0);
            }
            uVar9 = uVar7 & 0xf0;
            if ((uVar7 & 0xf) != 0) {
              uVar7 = uVar18 - uVar9;
              uVar14 = (ulong)((uVar7 & 0xff) + 1 & 0xff);
              if (6 < (uVar7 & 0xff)) goto LAB_00192924;
              goto LAB_00192960;
            }
          }
        }
        else {
          pcVar15 = pcVar15 + uVar20;
          uVar7 = 0;
          do {
            cVar3 = *pcVar15;
            pcVar5 = (char *)pbVar19;
            while (cVar3 != -0x80) {
              uVar1 = uVar7 + 1;
              *pcVar5 = cVar3;
              pcVar15 = pcVar15 + -1;
              uVar7 = uVar1 & 0xff;
              if (uVar18 < (uVar1 & 0xff)) goto LAB_00192a50;
              pcVar5 = pcVar5 + 1;
              cVar3 = *pcVar15;
            }
            uVar1 = uVar7 + 1;
            pbVar19 = (byte *)(pcVar5 + 1);
            *pcVar5 = '\0';
            pcVar15 = pcVar15 + -1;
            uVar7 = uVar1 & 0xff;
          } while ((uVar1 & 0xff) <= uVar18);
        }
      }
    }
  }
LAB_00192a50:
  lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar23 = *(byte *)(lVar16 + 0xa0);
  *(byte *)(lVar16 + ((ulong)bVar23 * 2 + (ulong)bVar23) * 0x10 + 0xc9) =
       local_70[(int)(uint)bVar23];
LAB_0019249c:
  iVar6 = MCOperand_getReg(uVar13);
  if (iVar6 != 0) {
    _printOperand(param_1,iVar4 + 4,param_3);
    SStream_concat0(param_3,&DAT_001fd7d0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar7 = X86_register_map(iVar6);
      lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar16 + (ulong)*(byte *)(lVar16 + 0xa0) * 0x30 + 0xb0) = uVar7 & 0xffff;
    }
  }
  uVar20 = 1;
  uVar14 = MCOperand_isImm(uVar12);
  if ((uVar14 & 1) != 0) {
    uVar20 = MCOperand_getImm(uVar12);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar16 + (ulong)*(byte *)(lVar16 + 0xa0) * 0x30 + 0xc0) = uVar20;
    }
    if (uVar20 != 0) {
      iVar6 = MCOperand_getReg(uVar11);
      if ((iVar6 == 0) && (iVar6 = MCOperand_getReg(uVar10), iVar6 == 0)) {
        if ((long)uVar20 < 0) {
          SStream_concat(param_3,"0x%lx",
                         uVar20 & *(ulong *)(PTR_arch_masks_005ffe50 +
                                            (ulong)*(uint *)(*(long *)(param_1 + 800) + 4) * 8));
        }
        else if ((long)uVar20 < 10) {
          SStream_concat(param_3,&DAT_001fb420,uVar20);
        }
        else {
          SStream_concat(param_3,"0x%lx",uVar20);
        }
      }
      else {
        printInt64(param_3,uVar20);
      }
    }
  }
  iVar6 = MCOperand_getReg(uVar11);
  if ((iVar6 == 0) && (iVar6 = MCOperand_getReg(uVar10), iVar6 == 0)) {
    if (uVar20 == 0) {
      SStream_concat0(param_3,&DAT_001ff7d8);
    }
  }
  else {
    SStream_concat0(param_3,"(");
    iVar6 = MCOperand_getReg(uVar10);
    if (iVar6 != 0) {
      _printOperand(param_1,param_2 & 0xffffffff,param_3);
    }
    iVar6 = MCOperand_getReg(uVar11);
    if ((iVar6 != 0) && (iVar6 = MCOperand_getReg(uVar11), iVar6 != 0x1e)) {
      SStream_concat0(param_3,", ");
      _printOperand(param_1,iVar4 + 2,param_3);
      MCInst_getOperand(param_1,iVar4 + 1);
      lVar16 = MCOperand_getImm();
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(int *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xbc) = (int)lVar16;
      }
      if (lVar16 != 1) {
        SStream_concat(param_3,&DAT_001fd7d8);
      }
    }
    SStream_concat0(param_3,")");
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar16 + 0xa0) = *(char *)(lVar16 + 0xa0) + '\x01';
  }
  if (uStack_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   uStack_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

