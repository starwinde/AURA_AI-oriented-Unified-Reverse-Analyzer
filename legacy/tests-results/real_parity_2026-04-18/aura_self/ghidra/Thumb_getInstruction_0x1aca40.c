
bool Thumb_getInstruction(long param_1,uint *param_2,ulong param_3,long param_4,undefined2 *param_5)

{
  uint uVar1;
  undefined4 *puVar2;
  ushort uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  bool bVar7;
  undefined2 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  void *__s;
  ulong uVar14;
  undefined8 uVar15;
  undefined4 *puVar16;
  byte bVar17;
  long lVar18;
  ulong uVar19;
  uint uVar20;
  char cVar21;
  undefined1 auVar22 [16];
  
  if (param_3 < 2) {
LAB_001acc84:
    iVar9 = 0;
    goto LAB_001accbc;
  }
  __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
  if (__s != (void *)0x0) {
    memset(__s,0,0x748);
    lVar18 = *(long *)(*(long *)(param_4 + 0x310) + 0xf0);
    puVar16 = (undefined4 *)(lVar18 + 0x88);
    do {
      puVar2 = puVar16 + 0xc;
      *puVar16 = 0xffffffff;
      *(undefined1 *)((long)puVar16 + 0x2a) = 0xff;
      puVar16 = puVar2;
    } while (puVar2 != (undefined4 *)(lVar18 + 0x748));
  }
  uVar5 = (ushort)*param_2;
  uVar3 = uVar5 >> 8 | uVar5 << 8;
  if (-1 < *(int *)(param_1 + 4)) {
    uVar3 = uVar5;
  }
  iVar9 = decodeInstruction_2_isra_0(DecoderTableThumb16,param_4,uVar3);
  if (iVar9 != 0) {
    uVar8 = 2;
    goto LAB_001acc90;
  }
  MCInst_clear(param_4);
  iVar10 = decodeInstruction_2_isra_0(DecoderTableThumbSBit16,param_4,uVar3);
  if (iVar10 != 0) {
    iVar9 = *(int *)(param_1 + 0x5c);
    *param_5 = 2;
    bVar7 = iVar9 != 0;
    iVar9 = AddThumbPredicate(param_1,param_4);
    if ((iVar9 != 0) && (iVar9 != 1)) {
      iVar9 = iVar10;
    }
LAB_001acd28:
    AddThumb1SBit(param_4,bVar7);
    goto LAB_001accbc;
  }
  MCInst_clear(param_4);
  iVar10 = decodeInstruction_2_isra_0(DecoderTableThumb216,param_4,uVar3);
  if (iVar10 == 0) {
    if (3 < param_3) {
      if (*(int *)(param_1 + 4) < 0) {
        uVar20 = (*param_2 & 0xff00ff00) >> 8 | (*param_2 & 0xff00ff) << 8;
        uVar20 = uVar20 >> 0x10 | uVar20 << 0x10;
      }
      else {
        uVar20 = (uint)*(ushort *)((long)param_2 + 2) | (uint)*(byte *)((long)param_2 + 1) << 0x18 |
                 (uint)(byte)*param_2 << 0x10;
      }
      MCInst_clear(param_4);
      iVar10 = decodeInstruction_4_isra_0(DecoderTableThumb32,param_4,uVar20);
      if (iVar10 != 0) {
        iVar9 = *(int *)(param_1 + 0x5c);
        *param_5 = 4;
        bVar7 = iVar9 != 0;
        iVar9 = AddThumbPredicate(param_1,param_4);
        if ((iVar9 != 0) && (iVar9 != 1)) {
          iVar9 = iVar10;
        }
        goto LAB_001acd28;
      }
      MCInst_clear(param_4);
      iVar9 = decodeInstruction_4_isra_0(DecoderTableThumb232,param_4,uVar20);
      if (iVar9 == 0) {
        if (uVar20 >> 0x1c == 0xe) {
          MCInst_clear(param_4);
          iVar9 = decodeInstruction_4_isra_0(DecoderTableVFP32,param_4,uVar20);
          if (iVar9 != 0) {
            *param_5 = 4;
            cVar21 = '\x0e';
            if (*(int *)(param_1 + 0x5c) != 0) {
              uVar20 = *(int *)(param_1 + 0x5c) - 1;
              cVar21 = *(char *)(param_1 + 0x54 + (ulong)uVar20);
              *(uint *)(param_1 + 0x5c) = uVar20;
            }
            uVar14 = MCInst_getOpcode(param_4);
            lVar18 = *(long *)(ARMInsts + (uVar14 & 0xffffffff) * 0x10 + 8);
            auVar22 = MCInst_getOpcode(param_4);
            bVar4 = ARMInsts[(auVar22._0_8_ & 0xffffffff) * 0x10];
            uVar20 = 0;
            uVar14 = auVar22._8_8_;
            if (bVar4 != 0) {
              do {
                uVar19 = (ulong)uVar20;
                uVar14 = MCOperandInfo_isPredicate(lVar18,uVar14);
                uVar20 = uVar20 + 1;
                if ((uVar14 & 1) != 0) {
                  uVar15 = MCInst_getOperand(param_4);
                  MCOperand_setImm(uVar15,cVar21);
                  if (cVar21 == '\x0e') {
                    uVar15 = MCInst_getOperand(param_4,uVar20);
                    MCOperand_setReg(uVar15,0);
                  }
                  else {
                    uVar15 = MCInst_getOperand(param_4,uVar20);
                    MCOperand_setReg(uVar15,3);
                  }
                  break;
                }
                lVar18 = lVar18 + 8;
                uVar14 = uVar19;
              } while (bVar4 != uVar20);
            }
            goto LAB_001accbc;
          }
          MCInst_clear(param_4);
          iVar9 = decodeInstruction_4_isra_0(DecoderTableVFPV832,param_4,uVar20);
          if (iVar9 == 0) {
            MCInst_clear(param_4);
            iVar9 = decodeInstruction_4_isra_0(DecoderTableNEONDup32,param_4,uVar20);
            if (iVar9 != 0) {
              uVar8 = 4;
              goto LAB_001acc90;
            }
            goto LAB_001acbe0;
          }
        }
        else {
          MCInst_clear(param_4);
          iVar9 = decodeInstruction_4_isra_0(DecoderTableVFPV832,param_4,uVar20);
          if (iVar9 == 0) {
            if (uVar20 >> 0x18 == 0xf9) {
              MCInst_clear(param_4);
              iVar9 = decodeInstruction_4_isra_0
                                (DecoderTableNEONLoadStore32,param_4,uVar20 & 0xf0ffffff | 0x4000000
                                );
              uVar11 = uVar20 & 0xf0ffffff | 0x13000000;
              if (iVar9 == 0) goto LAB_001acc00;
              uVar8 = 4;
              goto LAB_001acc90;
            }
LAB_001acbe0:
            uVar11 = uVar20 & 0xf0ffffff | (uVar20 & 0x10000000) >> 4 | 0x12000000;
            if ((uVar20 >> 0x18 & 0xf) == 0xf) {
              MCInst_clear(param_4);
              iVar9 = decodeInstruction_4_isra_0(DecoderTableNEONData32,param_4,uVar11);
              if (iVar9 != 0) goto LAB_001acf64;
            }
LAB_001acc00:
            MCInst_clear(param_4);
            iVar9 = decodeInstruction_4_isra_0(DecoderTablev8Crypto32,param_4,uVar11);
            if (iVar9 == 0) {
              MCInst_clear(param_4);
              iVar9 = decodeInstruction_4_isra_0(DecoderTablev8NEON32,param_4,uVar20 & 0xf3ffffff);
              if (iVar9 == 0) {
                MCInst_clear(param_4);
                iVar9 = decodeInstruction_4_isra_0(DecoderTableThumb2CoProc32,param_4,uVar20);
                if (iVar9 == 0) {
                  MCInst_clear(param_4);
                  *param_5 = 0;
                  goto LAB_001acc84;
                }
                goto LAB_001acf64;
              }
            }
          }
        }
        *param_5 = 4;
        goto LAB_001accbc;
      }
LAB_001acf64:
      uVar8 = 4;
LAB_001acc90:
      *param_5 = uVar8;
      iVar10 = AddThumbPredicate(param_1,param_4);
      if (iVar10 != 0) {
        if (iVar10 != 1) goto LAB_001accbc;
        goto LAB_001ace90;
      }
    }
    iVar9 = 0;
    goto LAB_001accbc;
  }
  *param_5 = 2;
  iVar9 = MCInst_getOpcode(param_4);
  if ((iVar9 == 0xafa) && (*(int *)(param_1 + 0x5c) != 0)) {
LAB_001ace90:
    iVar9 = 1;
    goto LAB_001accbc;
  }
  iVar9 = AddThumbPredicate(param_1,param_4);
  if ((iVar9 != 0) && (iVar9 != 1)) {
    iVar9 = iVar10;
  }
  iVar10 = MCInst_getOpcode(param_4);
  if (iVar10 != 0xafa) goto LAB_001accbc;
  MCInst_getOperand(param_4,0);
  uVar11 = MCOperand_getImm();
  MCInst_getOperand(param_4,1);
  uVar12 = MCOperand_getImm();
  uVar20 = uVar12 & 0xff;
  lVar18 = param_1 + 0x54;
  if ((uVar12 & 0xff) == 0) {
    uVar12 = *(uint *)(param_1 + 0x5c);
LAB_001acfd8:
    iVar10 = 1;
    uVar14 = 0;
    if (uVar12 < 8) {
      uVar14 = (ulong)uVar12;
      goto LAB_001ace64;
    }
  }
  else {
    uVar12 = (uVar12 & 0xaa) >> 1 | (uVar12 & 0x55) << 1;
    uVar6 = (uVar12 & 0xcccccccc) >> 2 | (uVar12 & 0x33333333) << 2;
    uVar12 = *(uint *)(param_1 + 0x5c);
    bVar4 = (byte)uVar11 & 0xf;
    iVar10 = (int)LZCOUNT((uVar6 >> 4 | (uVar6 & 0xf0f0f0f) << 4) << 0x18);
    if (3 < iVar10 + 1U) goto LAB_001acfd8;
    uVar6 = uVar11 & 1;
    if (((int)uVar20 >> (iVar10 + 1U & 0x1f) & 1U) == uVar6) {
      bVar17 = bVar4;
      if (uVar12 < 8) goto LAB_001ad0a8;
      *(byte *)(param_1 + 0x54) = bVar4;
LAB_001ace08:
      *(undefined4 *)(param_1 + 0x5c) = 1;
      if (iVar10 == 2) goto LAB_001ad16c;
      if (uVar6 == ((int)uVar20 >> (iVar10 + 2U & 0x1f) & 1U)) {
        uVar14 = 1;
LAB_001ad148:
        *(byte *)(lVar18 + uVar14) = bVar4;
        iVar13 = (int)uVar14;
      }
      else {
        uVar14 = 1;
LAB_001ace34:
        *(byte *)(lVar18 + uVar14) = bVar4 ^ 1;
        iVar13 = (int)uVar14;
      }
      uVar12 = iVar13 + 1;
      *(uint *)(param_1 + 0x5c) = uVar12;
      if (iVar10 != 0) goto LAB_001acfd8;
      if ((uVar20 >> 3 & 1) == uVar6) {
        if (uVar12 != 8) {
          *(byte *)(lVar18 + (ulong)uVar12) = bVar4;
          uVar12 = iVar13 + 2;
          goto LAB_001acfd8;
        }
        uVar14 = 1;
        *(byte *)(param_1 + 0x54) = bVar4;
      }
      else {
        if (uVar12 != 8) {
          *(byte *)(lVar18 + (ulong)uVar12) = bVar4 ^ 1;
          uVar12 = iVar13 + 2;
          goto LAB_001acfd8;
        }
        uVar14 = 1;
        *(byte *)(param_1 + 0x54) = bVar4 ^ 1;
      }
    }
    else {
      bVar17 = bVar4 ^ 1;
      if (7 < uVar12) {
        *(byte *)(param_1 + 0x54) = bVar17;
        goto LAB_001ace08;
      }
LAB_001ad0a8:
      uVar1 = uVar12 + 1;
      uVar14 = (ulong)uVar1;
      *(byte *)(lVar18 + (ulong)uVar12) = bVar17;
      *(uint *)(param_1 + 0x5c) = uVar1;
      uVar12 = uVar1;
      if (iVar10 == 2) goto LAB_001acfd8;
      if (((int)uVar20 >> (iVar10 + 2U & 0x1f) & 1U) == uVar6) {
        if (uVar1 != 8) goto LAB_001ad148;
        *(byte *)(param_1 + 0x54) = bVar4;
        *(undefined4 *)(param_1 + 0x5c) = 1;
        if (iVar10 != 0) goto LAB_001ad16c;
LAB_001ad0e8:
        if (uVar6 == (uVar20 >> 3 & 1)) {
          uVar14 = 2;
          *(byte *)(param_1 + 0x55) = bVar4;
        }
        else {
          uVar14 = 2;
          *(byte *)(param_1 + 0x55) = bVar4 ^ 1;
        }
        goto LAB_001ace64;
      }
      if (uVar1 != 8) goto LAB_001ace34;
      *(byte *)(param_1 + 0x54) = bVar4 ^ 1;
      *(undefined4 *)(param_1 + 0x5c) = 1;
      if (iVar10 == 0) goto LAB_001ad0e8;
LAB_001ad16c:
      uVar14 = 1;
    }
LAB_001ace64:
    iVar10 = (int)uVar14 + 1;
  }
  *(byte *)(lVar18 + uVar14) = (byte)uVar11 & 0xf;
  *(int *)(param_1 + 0x5c) = iVar10;
LAB_001accbc:
  return *(int *)(param_4 + 8) != 0xc90 && iVar9 != 0;
}

