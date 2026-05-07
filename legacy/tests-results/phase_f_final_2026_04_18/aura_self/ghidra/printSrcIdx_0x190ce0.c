
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printSrcIdx(long param_1,int param_2,undefined8 param_3)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  byte *pbVar14;
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
  byte local_50 [4];
  byte bStack_4c;
  byte bStack_4b;
  byte bStack_4a;
  byte bStack_49;
  undefined8 uStack_48;
  
  pbVar14 = local_50;
  lVar15 = *(long *)(param_1 + 800);
  uStack_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (*(int *)(lVar15 + 0x60) == 0) {
    MCInst_getOperand(param_1,param_2 + 1);
    iVar5 = MCOperand_getReg();
    goto joined_r0x001911c8;
  }
  lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  lVar10 = lVar10 + (ulong)*(byte *)(lVar10 + 0xa0) * 0x30;
  *(undefined4 *)(lVar10 + 0xa8) = 3;
  uVar2 = *(undefined1 *)(param_1 + 0x328);
  *(undefined8 *)(lVar10 + 0xb0) = 0;
  *(undefined8 *)(lVar10 + 0xb8) = 0x100000000;
  *(undefined8 *)(lVar10 + 0xc0) = 0;
  *(undefined1 *)(lVar10 + 200) = uVar2;
  uVar6 = MCInst_getOpcode();
  pcVar8 = (char *)X86_get_op_access(lVar15,uVar6,
                                     *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
  if (pcVar8 == (char *)0x0) {
    local_50[0] = 0;
  }
  else {
    uVar13 = 0;
    if (*pcVar8 != '\0') {
      do {
        uVar12 = uVar13;
        uVar11 = (uint)uVar12;
        uVar7 = uVar11 + 1;
        uVar1 = uVar7 & 0xff;
        uVar13 = (ulong)uVar1;
      } while (pcVar8[uVar13] != '\0');
      if (uVar1 != 0) {
        if ((uVar11 - 7 & 0xff) < 0xf8) {
          uVar9 = 0;
          if (uVar11 < 0xf) {
LAB_00191064:
            uVar16 = NEON_rev64(*(undefined8 *)(pcVar8 + ((uVar12 - 7) - (ulong)(byte)uVar9)),1);
            bVar18 = (byte)((ulong)uVar16 >> 8);
            bVar19 = (byte)((ulong)uVar16 >> 0x10);
            bVar20 = (byte)((ulong)uVar16 >> 0x18);
            bVar21 = (byte)((ulong)uVar16 >> 0x20);
            bVar22 = (byte)((ulong)uVar16 >> 0x28);
            bVar23 = (byte)((ulong)uVar16 >> 0x30);
            bVar24 = (byte)((ulong)uVar16 >> 0x38);
            *(ulong *)(local_50 + uVar9) =
                 CONCAT17(bVar24 & ~-(bVar24 == 0x80),
                          CONCAT16(bVar23 & ~-(bVar23 == 0x80),
                                   CONCAT15(bVar22 & ~-(bVar22 == 0x80),
                                            CONCAT14(bVar21 & ~-(bVar21 == 0x80),
                                                     CONCAT13(bVar20 & ~-(bVar20 == 0x80),
                                                              CONCAT12(bVar19 & ~-(bVar19 == 0x80),
                                                                       CONCAT11(bVar18 & ~-(bVar18 
                                                  == 0x80),(byte)uVar16 & ~-((byte)uVar16 == 0x80)))
                                                  )))));
            uVar9 = uVar9 + ((uint)uVar13 & 0xfffffff8) & 0xff;
            if ((uVar13 & 7) != 0) {
              uVar7 = uVar11 - uVar9;
LAB_001910a0:
              bVar18 = pcVar8[(int)uVar7];
              uVar7 = uVar9 + 1 & 0xff;
              if (bVar18 == 0x80) {
                bVar18 = 0;
              }
              local_50[uVar9] = bVar18;
              if ((uVar9 + 1 & 0xff) <= uVar11) {
                uVar1 = uVar9 + 2 & 0xff;
                bVar18 = pcVar8[(int)(uVar11 - uVar7)];
                if (bVar18 == 0x80) {
                  bVar18 = 0;
                }
                local_50[uVar7] = bVar18;
                if ((uVar9 + 2 & 0xff) <= uVar11) {
                  uVar7 = uVar9 + 3 & 0xff;
                  bVar18 = pcVar8[(int)(uVar11 - uVar1)];
                  if (bVar18 == 0x80) {
                    bVar18 = 0;
                  }
                  local_50[uVar1] = bVar18;
                  if ((uVar9 + 3 & 0xff) <= uVar11) {
                    uVar1 = uVar9 + 4 & 0xff;
                    bVar18 = pcVar8[(int)(uVar11 - uVar7)];
                    if (bVar18 == 0x80) {
                      bVar18 = 0;
                    }
                    local_50[uVar7] = bVar18;
                    if ((uVar9 + 4 & 0xff) <= uVar11) {
                      uVar7 = uVar9 + 5 & 0xff;
                      bVar18 = pcVar8[(int)(uVar11 - uVar1)];
                      if (bVar18 == 0x80) {
                        bVar18 = 0;
                      }
                      local_50[uVar1] = bVar18;
                      if ((uVar9 + 5 & 0xff) <= uVar11) {
                        uVar1 = uVar9 + 6 & 0xff;
                        bVar18 = pcVar8[(int)(uVar11 - uVar7)];
                        if (bVar18 == 0x80) {
                          bVar18 = 0;
                        }
                        local_50[uVar7] = bVar18;
                        if ((uVar9 + 6 & 0xff) <= uVar11) {
                          bVar18 = pcVar8[(int)(uVar11 - uVar1)];
                          if (bVar18 == 0x80) {
                            bVar18 = 0;
                          }
                          local_50[uVar1] = bVar18;
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
            auVar17 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xf)),
                              _DAT_0020b540);
            uStack_48 = CONCAT17(auVar17[0xf] & ~-(auVar17[0xf] == 0x80),
                                 CONCAT16(auVar17[0xe] & ~-(auVar17[0xe] == 0x80),
                                          CONCAT15(auVar17[0xd] & ~-(auVar17[0xd] == 0x80),
                                                   CONCAT14(auVar17[0xc] & ~-(auVar17[0xc] == 0x80),
                                                            CONCAT13(auVar17[0xb] &
                                                                     ~-(auVar17[0xb] == 0x80),
                                                                     CONCAT12(auVar17[10] &
                                                                              ~-(auVar17[10] == 0x80
                                                                                ),CONCAT11(auVar17[9
                                                  ] & ~-(auVar17[9] == 0x80),
                                                  auVar17[8] & ~-(auVar17[8] == 0x80))))))));
            local_50[0] = auVar17[0] & ~-(auVar17[0] == 0x80);
            local_50[1] = auVar17[1] & ~-(auVar17[1] == 0x80);
            local_50[2] = auVar17[2] & ~-(auVar17[2] == 0x80);
            local_50[3] = auVar17[3] & ~-(auVar17[3] == 0x80);
            bStack_4c = auVar17[4] & ~-(auVar17[4] == 0x80);
            bStack_4b = auVar17[5] & ~-(auVar17[5] == 0x80);
            bStack_4a = auVar17[6] & ~-(auVar17[6] == 0x80);
            bStack_49 = auVar17[7] & ~-(auVar17[7] == 0x80);
            if (((((uVar1 != 1) &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x1f)),_DAT_0020b540
                          ), uVar1 != 2)) &&
                 (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x2f)),_DAT_0020b540)
                 , uVar1 != 3)) &&
                ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x3f)),
                            _DAT_0020b540), uVar1 != 4 &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x4f)),
                            _DAT_0020b540), uVar1 != 5)) &&
                  ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x5f)),
                            _DAT_0020b540), uVar1 != 6 &&
                   ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x6f)),
                             _DAT_0020b540), uVar1 != 7 &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x7f)),
                             _DAT_0020b540), uVar1 != 8)))))) &&
                 (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x8f)),_DAT_0020b540)
                 , uVar1 != 9)))) &&
               ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0x9f)),_DAT_0020b540
                          ), uVar1 != 10 &&
                  (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xaf)),_DAT_0020b540
                          ), uVar1 != 0xb)) &&
                 (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xbf)),_DAT_0020b540)
                 , uVar1 != 0xc)) &&
                ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xcf)),_DAT_0020b540)
                 , uVar1 != 0xd &&
                 (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xdf)),_DAT_0020b540)
                 , uVar1 == 0xf)))))) {
              a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar8 + (uVar12 - 0xef)),_DAT_0020b540);
            }
            uVar9 = uVar7 & 0xf0;
            if ((uVar7 & 0xf) != 0) {
              uVar7 = uVar11 - uVar9;
              uVar13 = (ulong)((uVar7 & 0xff) + 1 & 0xff);
              if (6 < (uVar7 & 0xff)) goto LAB_00191064;
              goto LAB_001910a0;
            }
          }
        }
        else {
          pcVar8 = pcVar8 + uVar12;
          uVar7 = 0;
          do {
            cVar3 = *pcVar8;
            pcVar4 = (char *)pbVar14;
            while (cVar3 != -0x80) {
              uVar1 = uVar7 + 1;
              *pcVar4 = cVar3;
              pcVar8 = pcVar8 + -1;
              uVar7 = uVar1 & 0xff;
              if (uVar11 < (uVar1 & 0xff)) goto LAB_00191190;
              pcVar4 = pcVar4 + 1;
              cVar3 = *pcVar8;
            }
            uVar1 = uVar7 + 1;
            pbVar14 = (byte *)(pcVar4 + 1);
            *pcVar4 = '\0';
            pcVar8 = pcVar8 + -1;
            uVar7 = uVar1 & 0xff;
          } while ((uVar1 & 0xff) <= uVar11);
        }
      }
    }
  }
LAB_00191190:
  lVar15 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar18 = *(byte *)(lVar15 + 0xa0);
  *(byte *)(lVar15 + ((ulong)bVar18 * 2 + (ulong)bVar18) * 0x10 + 0xc9) =
       local_50[(int)(uint)bVar18];
  MCInst_getOperand(param_1,param_2 + 1);
  iVar5 = MCOperand_getReg();
joined_r0x001911c8:
  if (iVar5 != 0) {
    _printOperand(param_1,param_2 + 1,param_3);
    SStream_concat0(param_3,&DAT_001fcc70);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar7 = X86_register_map(iVar5);
      lVar15 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar15 + (ulong)*(byte *)(lVar15 + 0xa0) * 0x30 + 0xb0) = uVar7 & 0xffff;
    }
  }
  SStream_concat0(param_3,"(");
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 1;
  }
  printOperand(param_1,param_2,param_3);
  SStream_concat0(param_3,")");
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar15 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar15 = *(long *)(lVar15 + 0xf0);
    *(char *)(lVar15 + 0xa0) = *(char *)(lVar15 + 0xa0) + '\x01';
  }
  if (uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

