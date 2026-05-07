
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printDstIdx_constprop_0(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  byte *pbVar11;
  uint uVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  undefined8 uVar16;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  byte bVar21;
  byte bVar22;
  byte bVar23;
  byte bVar24;
  undefined1 auVar17 [16];
  byte local_40 [4];
  byte bStack_3c;
  byte bStack_3b;
  byte bStack_3a;
  byte bStack_39;
  undefined8 uStack_38;
  
  pbVar11 = local_40;
  lVar15 = *(long *)(param_1 + 800);
  uStack_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  lVar10 = 0;
  if (*(int *)(lVar15 + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar10 = lVar10 + (ulong)*(byte *)(lVar10 + 0xa0) * 0x30;
    *(undefined4 *)(lVar10 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar10 + 0xb0) = 0;
    *(undefined8 *)(lVar10 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar10 + 0xc0) = 0;
    *(undefined1 *)(lVar10 + 200) = uVar2;
    uVar5 = MCInst_getOpcode();
    pcVar6 = (char *)X86_get_op_access(lVar15,uVar5,
                                       *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar6 == (char *)0x0) {
      local_40[0] = 0;
    }
    else {
      uVar14 = 0;
      if (*pcVar6 != '\0') {
        do {
          uVar13 = uVar14;
          uVar12 = (uint)uVar13;
          uVar9 = uVar12 + 1;
          uVar1 = uVar9 & 0xff;
          uVar14 = (ulong)uVar1;
        } while (pcVar6[uVar14] != '\0');
        if (uVar1 != 0) {
          if ((uVar12 - 7 & 0xff) < 0xf8) {
            uVar8 = 0;
            if (uVar12 < 0xf) {
LAB_0018eb34:
              uVar16 = NEON_rev64(*(undefined8 *)(pcVar6 + ((uVar13 - 7) - (ulong)(byte)uVar8)),1);
              bVar18 = (byte)((ulong)uVar16 >> 8);
              bVar19 = (byte)((ulong)uVar16 >> 0x10);
              bVar20 = (byte)((ulong)uVar16 >> 0x18);
              bVar21 = (byte)((ulong)uVar16 >> 0x20);
              bVar22 = (byte)((ulong)uVar16 >> 0x28);
              bVar23 = (byte)((ulong)uVar16 >> 0x30);
              bVar24 = (byte)((ulong)uVar16 >> 0x38);
              *(ulong *)(local_40 + uVar8) =
                   CONCAT17(bVar24 & ~-(bVar24 == 0x80),
                            CONCAT16(bVar23 & ~-(bVar23 == 0x80),
                                     CONCAT15(bVar22 & ~-(bVar22 == 0x80),
                                              CONCAT14(bVar21 & ~-(bVar21 == 0x80),
                                                       CONCAT13(bVar20 & ~-(bVar20 == 0x80),
                                                                CONCAT12(bVar19 & ~-(bVar19 == 0x80)
                                                                         ,CONCAT11(bVar18 & ~-(
                                                  bVar18 == 0x80),
                                                  (byte)uVar16 & ~-((byte)uVar16 == 0x80))))))));
              uVar8 = uVar8 + ((uint)uVar14 & 0xfffffff8) & 0xff;
              if ((uVar14 & 7) != 0) {
                uVar9 = uVar12 - uVar8;
LAB_0018eb70:
                bVar18 = pcVar6[(int)uVar9];
                uVar9 = uVar8 + 1 & 0xff;
                if (bVar18 == 0x80) {
                  bVar18 = 0;
                }
                local_40[uVar8] = bVar18;
                if ((uVar8 + 1 & 0xff) <= uVar12) {
                  uVar1 = uVar8 + 2 & 0xff;
                  bVar18 = pcVar6[(int)(uVar12 - uVar9)];
                  if (bVar18 == 0x80) {
                    bVar18 = 0;
                  }
                  local_40[uVar9] = bVar18;
                  if ((uVar8 + 2 & 0xff) <= uVar12) {
                    uVar9 = uVar8 + 3 & 0xff;
                    bVar18 = pcVar6[(int)(uVar12 - uVar1)];
                    if (bVar18 == 0x80) {
                      bVar18 = 0;
                    }
                    local_40[uVar1] = bVar18;
                    if ((uVar8 + 3 & 0xff) <= uVar12) {
                      uVar1 = uVar8 + 4 & 0xff;
                      bVar18 = pcVar6[(int)(uVar12 - uVar9)];
                      if (bVar18 == 0x80) {
                        bVar18 = 0;
                      }
                      local_40[uVar9] = bVar18;
                      if ((uVar8 + 4 & 0xff) <= uVar12) {
                        uVar9 = uVar8 + 5 & 0xff;
                        bVar18 = pcVar6[(int)(uVar12 - uVar1)];
                        if (bVar18 == 0x80) {
                          bVar18 = 0;
                        }
                        local_40[uVar1] = bVar18;
                        if ((uVar8 + 5 & 0xff) <= uVar12) {
                          uVar1 = uVar8 + 6 & 0xff;
                          bVar18 = pcVar6[(int)(uVar12 - uVar9)];
                          if (bVar18 == 0x80) {
                            bVar18 = 0;
                          }
                          local_40[uVar9] = bVar18;
                          if ((uVar8 + 6 & 0xff) <= uVar12) {
                            bVar18 = pcVar6[(int)(uVar12 - uVar1)];
                            if (bVar18 == 0x80) {
                              bVar18 = 0;
                            }
                            local_40[uVar1] = bVar18;
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
              auVar17 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xf)),
                                _DAT_0020a560);
              uStack_38 = CONCAT17(auVar17[0xf] & ~-(auVar17[0xf] == 0x80),
                                   CONCAT16(auVar17[0xe] & ~-(auVar17[0xe] == 0x80),
                                            CONCAT15(auVar17[0xd] & ~-(auVar17[0xd] == 0x80),
                                                     CONCAT14(auVar17[0xc] &
                                                              ~-(auVar17[0xc] == 0x80),
                                                              CONCAT13(auVar17[0xb] &
                                                                       ~-(auVar17[0xb] == 0x80),
                                                                       CONCAT12(auVar17[10] &
                                                                                ~-(auVar17[10] ==
                                                                                  0x80),CONCAT11(
                                                  auVar17[9] & ~-(auVar17[9] == 0x80),
                                                  auVar17[8] & ~-(auVar17[8] == 0x80))))))));
              local_40[0] = auVar17[0] & ~-(auVar17[0] == 0x80);
              local_40[1] = auVar17[1] & ~-(auVar17[1] == 0x80);
              local_40[2] = auVar17[2] & ~-(auVar17[2] == 0x80);
              local_40[3] = auVar17[3] & ~-(auVar17[3] == 0x80);
              bStack_3c = auVar17[4] & ~-(auVar17[4] == 0x80);
              bStack_3b = auVar17[5] & ~-(auVar17[5] == 0x80);
              bStack_3a = auVar17[6] & ~-(auVar17[6] == 0x80);
              bStack_39 = auVar17[7] & ~-(auVar17[7] == 0x80);
              if (((((uVar1 != 1) &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x1f)),
                             _DAT_0020a560), uVar1 != 2)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x2f)),
                            _DAT_0020a560), uVar1 != 3)) &&
                  ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x3f)),
                              _DAT_0020a560), uVar1 != 4 &&
                     (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x4f)),
                              _DAT_0020a560), uVar1 != 5)) &&
                    ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x5f)),
                              _DAT_0020a560), uVar1 != 6 &&
                     ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x6f)),
                               _DAT_0020a560), uVar1 != 7 &&
                      (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x7f)),
                               _DAT_0020a560), uVar1 != 8)))))) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x8f)),
                            _DAT_0020a560), uVar1 != 9)))) &&
                 ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0x9f)),
                             _DAT_0020a560), uVar1 != 10 &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xaf)),
                             _DAT_0020a560), uVar1 != 0xb)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xbf)),
                            _DAT_0020a560), uVar1 != 0xc)) &&
                  ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xcf)),
                            _DAT_0020a560), uVar1 != 0xd &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xdf)),
                            _DAT_0020a560), uVar1 == 0xf)))))) {
                a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar6 + (uVar13 - 0xef)),_DAT_0020a560);
              }
              uVar8 = uVar9 & 0xf0;
              if ((uVar9 & 0xf) != 0) {
                uVar9 = uVar12 - uVar8;
                uVar14 = (ulong)((uVar9 & 0xff) + 1 & 0xff);
                if (6 < (uVar9 & 0xff)) goto LAB_0018eb34;
                goto LAB_0018eb70;
              }
            }
          }
          else {
            pcVar6 = pcVar6 + uVar13;
            uVar9 = 0;
            do {
              cVar3 = *pcVar6;
              pcVar4 = (char *)pbVar11;
              while (cVar3 != -0x80) {
                uVar1 = uVar9 + 1;
                *pcVar4 = cVar3;
                pcVar6 = pcVar6 + -1;
                uVar9 = uVar1 & 0xff;
                if (uVar12 < (uVar1 & 0xff)) goto LAB_0018ec60;
                pcVar4 = pcVar4 + 1;
                cVar3 = *pcVar6;
              }
              uVar1 = uVar9 + 1;
              pbVar11 = (byte *)(pcVar4 + 1);
              *pcVar4 = '\0';
              pcVar6 = pcVar6 + -1;
              uVar9 = uVar1 & 0xff;
            } while ((uVar1 & 0xff) <= uVar12);
          }
        }
      }
    }
LAB_0018ec60:
    lVar15 = *(long *)(param_1 + 800);
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar18 = *(byte *)(lVar10 + 0xa0);
    *(byte *)(lVar10 + ((ulong)bVar18 * 2 + (ulong)bVar18) * 0x10 + 0xc9) =
         local_40[(int)(uint)bVar18];
  }
  if (*(int *)(lVar15 + 4) == 8) {
    SStream_concat0(param_2,"(",lVar10);
    lVar10 = *(long *)(param_1 + 800);
    iVar7 = *(int *)(lVar10 + 0x60);
  }
  else {
    SStream_concat0(param_2,"%es:(",lVar10);
    lVar10 = *(long *)(param_1 + 800);
    iVar7 = *(int *)(lVar10 + 0x60);
    if (iVar7 == 0) goto LAB_0018e820;
    lVar15 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar15 + (ulong)*(byte *)(lVar15 + 0xa0) * 0x30 + 0xb0) = 0x1c;
  }
  if (iVar7 == 3) {
    *(undefined1 *)(lVar10 + 0x6c) = 1;
  }
LAB_0018e820:
  printOperand(param_1,0,param_2);
  SStream_concat0(param_2,")");
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar10 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar10 = *(long *)(lVar10 + 0xf0);
    *(char *)(lVar10 + 0xa0) = *(char *)(lVar10 + 0xa0) + '\x01';
  }
  if (uStack_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   uStack_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

