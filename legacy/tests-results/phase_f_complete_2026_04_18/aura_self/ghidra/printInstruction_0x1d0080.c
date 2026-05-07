
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printInstruction(long param_1,undefined8 param_2)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  ushort uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  byte bVar14;
  int iVar15;
  uint uVar16;
  undefined4 uVar17;
  ulong uVar18;
  undefined8 *puVar19;
  long *plVar20;
  char *pcVar21;
  long lVar22;
  long lVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  ulong uVar26;
  long lVar27;
  int iVar28;
  int iVar29;
  byte bVar30;
  byte bVar31;
  byte bVar32;
  uint uVar33;
  uint uVar34;
  undefined1 auStack_e8 [128];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar18 = MCInst_getOpcode(param_1,0);
  uVar16 = *(uint *)(OpInfo0_2 + (uVar18 & 0xffffffff) * 4);
  uVar33 = *(uint *)(OpInfo1_1 + (uVar18 & 0xffffffff) * 4);
  SStream_concat0(param_2,(uVar16 & 0x3fff) + 0x2b4e9f);
  uVar18 = (((ulong)uVar16 & 0x1fc000) >> 0xe) - 1;
  if (0x42 < uVar18) goto switchD_001d014c_default;
  switch(uVar18 & 0xffffffff) {
  case 0:
    printOperand(param_1,0,param_2);
    break;
  case 1:
    printSVERegOp(param_1,0,param_2,0x62);
    break;
  case 2:
    printSVERegOp(param_1,0,param_2,100);
    break;
  case 3:
    uVar24 = 0x68;
    goto LAB_001d0a70;
  case 4:
    printSVERegOp(param_1,0,param_2,0x73);
    break;
  case 5:
    printVRegOperand(param_1,0,param_2);
    break;
  case 6:
    MCInst_getOperand(param_1,0);
    iVar15 = MCOperand_getReg();
    SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar15 - 1) * 2));
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      bVar14 = *(byte *)(lVar22 + 0x67);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 1;
      *(int *)(lVar27 + 0x88) = iVar15;
      *(byte *)(lVar22 + 0x67) = bVar14 + 1;
    }
    SStream_concat0(param_2,", ");
    printSVERegOp(param_1,1,param_2,0);
    SStream_concat0(param_2,&DAT_001ffc98);
    printSVERegOp(param_1,2,param_2,0);
    SStream_concat0(param_2,&DAT_001ffc98);
    break;
  case 7:
    printVRegOperand(param_1,1,param_2);
    break;
  case 8:
    printZPRasFPR(param_1,0,param_2,8);
    SStream_concat0(param_2,", ");
    printSVERegOp(param_1,1,param_2,0);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x62);
    return;
  case 9:
    uVar24 = 0x40;
    goto LAB_001d1a8c;
  case 10:
    uVar24 = 0x10;
    goto LAB_001d1a8c;
  case 0xb:
    uVar24 = 0x20;
LAB_001d1a8c:
    printZPRasFPR(param_1,0,param_2,uVar24);
    SStream_concat0(param_2,", ");
    printSVERegOp(param_1,1,param_2,0);
    SStream_concat0(param_2,", ");
    break;
  case 0xc:
    printOperand(param_1,1,param_2);
    break;
  case 0xd:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printAlignedLabel(param_1,0,param_2);
    return;
  case 0xe:
    printCondCode(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fe368);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printAlignedLabel(param_1,1,param_2);
    return;
  case 0xf:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImmHex(param_1,0,param_2);
    return;
  case 0x10:
    printGPRSeqPairsClassOperand(param_1,1,param_2,0x20);
    SStream_concat0(param_2,", ");
    uVar24 = 0x20;
    goto LAB_001d0cb0;
  case 0x11:
    printGPRSeqPairsClassOperand(param_1,1,param_2,0x40);
    SStream_concat0(param_2,", ");
    uVar24 = 0x40;
LAB_001d0cb0:
    printGPRSeqPairsClassOperand(param_1,2,param_2,uVar24);
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    uVar24 = 3;
    goto LAB_001d07fc;
  case 0x12:
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,"]!, [");
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      if (*(int *)(lVar27 + 0x60) != 3) {
        *(undefined1 *)(lVar27 + 0x6c) = 1;
        goto LAB_001d0be4;
      }
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(char *)(lVar22 + 0x67) = *(char *)(lVar22 + 0x67) + '\x01';
      *(undefined1 *)(lVar27 + 0x6c) = 1;
    }
    else {
      *(undefined2 *)(lVar27 + 0x6c) = 1;
      if (*(int *)(lVar27 + 0x60) != 3) goto LAB_001d0be4;
    }
    uVar17 = MCInst_getOpcode(param_1);
    bVar14 = *(byte *)(param_1 + 0x366);
    lVar27 = AArch64_get_op_access(lVar27,uVar17);
    cVar4 = *(char *)(lVar27 + (ulong)bVar14);
    lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    if (cVar4 == -0x80) {
      cVar4 = '\0';
    }
    lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
    *(char *)(lVar27 + 0x98) = cVar4;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar27 + 0x7c) = 3;
    *(undefined8 *)(lVar27 + 0x88) = 0;
    *(undefined4 *)(lVar27 + 0x90) = 0;
LAB_001d0be4:
    printOperand(param_1,4,param_2);
    SStream_concat0(param_2,&DAT_001ffcb0);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    printOperand(param_1,5,param_2);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    SStream_concat0(param_2,&DAT_001fd630);
    return;
  case 0x13:
    MCInst_getOperand(param_1,0);
    uVar16 = MCOperand_getImm();
    iVar15 = MCInst_getOpcode(param_1);
    if (iVar15 == 0xb54) {
      plVar20 = (long *)lookupISBByEncoding(uVar16);
      if (plVar20 != (long *)0x0) {
        lVar27 = *plVar20;
        goto LAB_001d0ab4;
      }
    }
    else {
      if (iVar15 == 0x1583) {
        plVar20 = (long *)lookupTSBByEncoding(uVar16 & 0xffff);
        goto joined_r0x001d0aac;
      }
      plVar20 = (long *)lookupDBByEncoding();
      if (plVar20 != (long *)0x0) {
        lVar27 = *plVar20;
        goto LAB_001d0ab4;
      }
    }
    goto LAB_001d2c28;
  case 0x14:
    MCInst_getOperand(param_1,0);
    uVar16 = MCOperand_getImm();
    plVar20 = (long *)lookupDBnXSByEncoding();
joined_r0x001d0aac:
    if (plVar20 != (long *)0x0) {
      lVar27 = *plVar20;
LAB_001d0ab4:
      if (lVar27 != 0) {
        SStream_concat0(param_2);
        lVar27 = *(long *)(param_1 + 800);
        if (*(int *)(lVar27 + 0x60) != 0) {
          uVar17 = MCInst_getOpcode(param_1);
          bVar14 = *(byte *)(param_1 + 0x366);
          lVar27 = AArch64_get_op_access(lVar27,uVar17);
          lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar4 = *(char *)(lVar27 + (ulong)bVar14);
          bVar14 = *(byte *)(lVar22 + 0x67);
          if (cVar4 == -0x80) {
            cVar4 = '\0';
          }
          lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
          *(char *)(lVar27 + 0x98) = cVar4;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar27 + 0x7c) = 0x47;
          *(uint *)(lVar27 + 0x88) = uVar16;
          *(byte *)(lVar22 + 0x67) = bVar14 + 1;
        }
        goto switchD_001d014c_default;
      }
    }
LAB_001d2c28:
    printUInt32Bang(param_2,uVar16);
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      bVar14 = *(byte *)(lVar22 + 0x67);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 2;
      *(ulong *)(lVar27 + 0x88) = (ulong)uVar16;
      *(byte *)(lVar22 + 0x67) = bVar14 + 1;
    }
    goto switchD_001d014c_default;
  case 0x15:
    uVar24 = 0x71;
LAB_001d0a70:
    printSVERegOp(param_1,0,param_2,uVar24);
    SStream_concat0(param_2,", ");
    break;
  case 0x16:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xd;
    goto LAB_001d0a3c;
  case 0x17:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xb;
    goto LAB_001d0a3c;
  case 0x18:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImmHex(param_1,0,param_2);
    return;
  case 0x19:
    uVar24 = 0;
    goto LAB_001d0e0c;
  case 0x1a:
    uVar24 = 1;
LAB_001d0e0c:
    printMatrixTileVector(param_1,0,param_2,uVar24);
    SStream_concat0(param_2,&DAT_001fdfa0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6d) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar18 = (ulong)(*(byte *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x67) - 1);
      MCInst_getOperand(param_1,uVar18);
      uVar17 = MCOperand_getReg();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + uVar18 * 0x38;
      *(undefined4 *)(lVar27 + 0x7c) = 0x48;
      *(undefined4 *)(lVar27 + 0x88) = uVar17;
      *(undefined8 *)(lVar27 + 0x8c) = 0;
    }
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    uVar24 = MCOperand_getImm();
    printInt64(param_2,uVar24);
    if ((*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) &&
       ((*(byte *)(*(long *)(param_1 + 800) + 0x6d) & 1) != 0)) {
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar34 = *(byte *)(lVar27 + 0x67) - 1;
      *(int *)(lVar27 + ((-(ulong)(uVar34 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar34 << 3) -
                        (long)(int)uVar34) * 8 + 0x90) = (int)uVar24;
    }
    break;
  case 0x1b:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 4;
    goto LAB_001d0a3c;
  case 0x1c:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 8;
LAB_001d0a3c:
    printVectorList(param_1,0,param_2,auStack_e8,uVar24,uVar25);
    SStream_concat0(param_2,", ");
    printSVERegOp(param_1,1,param_2,0);
    break;
  case 0x1d:
    cs_snprintf(auStack_e8,0x20,".%u%c",0x10,0x62);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),1);
    goto LAB_001d0770;
  case 0x1e:
    cs_snprintf(auStack_e8,0x20,".%u%c",0x10,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 1;
    goto LAB_001d0648;
  case 0x1f:
    cs_snprintf(auStack_e8,0x20,".%u%c",1,100);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),0xd);
    goto LAB_001d0770;
  case 0x20:
    cs_snprintf(auStack_e8,0x20,".%u%c",1,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xd;
    goto LAB_001d0648;
  case 0x21:
    cs_snprintf(auStack_e8,0x20,".%u%c",2,100);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),0xc);
    goto LAB_001d0770;
  case 0x22:
    cs_snprintf(auStack_e8,0x20,".%u%c",2,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xc;
    goto LAB_001d0648;
  case 0x23:
    cs_snprintf(auStack_e8,0x20,".%u%c",2,0x73);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),10);
    goto LAB_001d0770;
  case 0x24:
    cs_snprintf(auStack_e8,0x20,".%u%c",2,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 10;
    goto LAB_001d0648;
  case 0x25:
    cs_snprintf(auStack_e8,0x20,".%u%c",4,0x68);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),6);
    goto LAB_001d0770;
  case 0x26:
    cs_snprintf(auStack_e8,0x20,".%u%c",4,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 6;
    goto LAB_001d0648;
  case 0x27:
    cs_snprintf(auStack_e8,0x20,".%u%c",4,0x73);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),9);
    goto LAB_001d0770;
  case 0x28:
    cs_snprintf(auStack_e8,0x20,".%u%c",4,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 9;
    goto LAB_001d0648;
  case 0x29:
    cs_snprintf(auStack_e8,0x20,".%u%c",8,0x62);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),2);
    goto LAB_001d0770;
  case 0x2a:
    cs_snprintf(auStack_e8,0x20,".%u%c",8,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 2;
    goto LAB_001d0648;
  case 0x2b:
    cs_snprintf(auStack_e8,0x20,".%u%c",8,0x68);
    printVectorList(param_1,0,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),5);
    goto LAB_001d0770;
  case 0x2c:
    cs_snprintf(auStack_e8,0x20,".%u%c",8,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 5;
LAB_001d0648:
    printVectorList(param_1,1,param_2,auStack_e8,uVar24,uVar25);
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    uVar24 = 2;
LAB_001d06dc:
    printOperand(param_1,uVar24,param_2);
    SStream_concat0(param_2,&DAT_001fe630);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    break;
  case 0x2d:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 8;
    goto LAB_001d12d0;
  case 0x2e:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 8;
    goto LAB_001d087c;
  case 0x2f:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xb;
    goto LAB_001d12d0;
  case 0x30:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xb;
    goto LAB_001d087c;
  case 0x31:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xd;
    goto LAB_001d12d0;
  case 0x32:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xd;
    goto LAB_001d087c;
  case 0x33:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 4;
LAB_001d12d0:
    printVectorList(param_1,1,param_2,auStack_e8,uVar24,uVar25);
    SStream_concat0(param_2,&DAT_001fdfa0);
    MCInst_getOperand(param_1,2);
    uVar17 = MCOperand_getImm();
    printInt32(param_2,uVar17);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      MCInst_getOperand(param_1,2);
      uVar17 = MCOperand_getImm();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar34 = *(byte *)(lVar27 + 0x67) - 1;
      *(undefined4 *)
       (lVar27 + ((-(ulong)(uVar34 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar34 << 3) -
                 (long)(int)uVar34) * 8 + 0x68) = uVar17;
    }
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    printOperand(param_1,3,param_2);
    break;
  case 0x34:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 4;
LAB_001d087c:
    printVectorList(param_1,2,param_2,auStack_e8,uVar24,uVar25);
    SStream_concat0(param_2,&DAT_001fdfa0);
    MCInst_getOperand(param_1,3);
    uVar17 = MCOperand_getImm();
    printInt32(param_2,uVar17);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      MCInst_getOperand(param_1,3);
      uVar17 = MCOperand_getImm();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar34 = *(byte *)(lVar27 + 0x67) - 1;
      *(undefined4 *)
       (lVar27 + ((-(ulong)(uVar34 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar34 << 3) -
                 (long)(int)uVar34) * 8 + 0x68) = uVar17;
    }
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    uVar24 = 4;
    goto LAB_001d06dc;
  case 0x35:
    MCInst_getOperand(param_1,0);
    uVar17 = MCOperand_getReg();
    iVar15 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar17,0x12);
    SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar15 - 1) * 2));
LAB_001d0770:
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    uVar24 = 1;
    goto LAB_001d07fc;
  case 0x36:
    printSVERegOp(param_1,0,param_2,0);
    break;
  case 0x37:
    printMatrix_constprop_0(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fdfa0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6d) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar18 = (ulong)(*(byte *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x67) - 1);
      MCInst_getOperand(param_1,uVar18);
      uVar17 = MCOperand_getReg();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + uVar18 * 0x38;
      *(undefined4 *)(lVar27 + 0x7c) = 0x48;
      *(undefined4 *)(lVar27 + 0x88) = uVar17;
      *(undefined8 *)(lVar27 + 0x8c) = 0;
    }
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    uVar24 = MCOperand_getImm();
    printInt64(param_2,uVar24);
    if ((*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) &&
       ((*(byte *)(*(long *)(param_1 + 800) + 0x6d) & 1) != 0)) {
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar16 = *(byte *)(lVar27 + 0x67) - 1;
      *(int *)(lVar27 + ((-(ulong)(uVar16 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar16 << 3) -
                        (long)(int)uVar16) * 8 + 0x90) = (int)uVar24;
    }
    SStream_concat0(param_2,&DAT_001ffcb8);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar22 + 0x67) = *(char *)(lVar22 + 0x67) + '\x01';
        *(undefined1 *)(lVar27 + 0x6c) = 1;
LAB_001d15a0:
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar27 = AArch64_get_op_access(lVar27,uVar17);
        cVar4 = *(char *)(lVar27 + (ulong)bVar14);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
        *(char *)(lVar27 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar27 + 0x7c) = 3;
        *(undefined8 *)(lVar27 + 0x88) = 0;
        *(undefined4 *)(lVar27 + 0x90) = 0;
      }
      else {
        *(undefined1 *)(lVar27 + 0x6c) = 1;
      }
    }
    else {
      *(undefined2 *)(lVar27 + 0x6c) = 1;
      if (*(int *)(lVar27 + 0x60) == 3) goto LAB_001d15a0;
    }
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,4,param_2);
    SStream_concat0(param_2,", mul vl]");
    lVar27 = *(long *)(param_1 + 800);
    bVar14 = *(byte *)(lVar27 + 0x6d);
    goto joined_r0x001d1648;
  case 0x38:
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,&DAT_001ffcb0);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,&DAT_001fe5c8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,4,param_2);
    return;
  case 0x39:
    MCInst_getOperand(param_1,0);
    uVar16 = MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSysRegByEncoding();
    if (uVar16 == 0x9828) {
      SStream_concat0(param_2,"dbgdtrtx_el0");
      lVar27 = *(long *)(param_1 + 800);
      if (*(int *)(lVar27 + 0x60) != 0) {
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar27 = AArch64_get_op_access(lVar27,uVar17);
        cVar4 = *(char *)(lVar27 + (ulong)bVar14);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        cVar3 = *(char *)(lVar27 + 0x67);
        lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
        *(char *)(lVar22 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar22 + 0x7c) = 0x44;
        *(undefined4 *)(lVar22 + 0x88) = 0x9828;
        *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
      }
      goto LAB_001d04b0;
    }
    if (uVar16 == 0xe100) {
      SStream_concat0(param_2,"ttbr0_el2");
      lVar27 = *(long *)(param_1 + 800);
      if (*(int *)(lVar27 + 0x60) != 0) {
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar27 = AArch64_get_op_access(lVar27,uVar17);
        cVar4 = *(char *)(lVar27 + (ulong)bVar14);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        cVar3 = *(char *)(lVar27 + 0x67);
        lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
        *(char *)(lVar22 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar22 + 0x7c) = 0x44;
        *(undefined4 *)(lVar22 + 0x88) = 0xe100;
        *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
      }
      goto LAB_001d04b0;
    }
    if ((puVar19 != (undefined8 *)0x0) && ((*(byte *)((long)puVar19 + 0xb) & 1) != 0)) {
      SStream_concat0(param_2,*puVar19);
      lVar27 = *(long *)(param_1 + 800);
      if (*(int *)(lVar27 + 0x60) != 0) {
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar27 = AArch64_get_op_access(lVar27,uVar17);
        lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar4 = *(char *)(lVar27 + (ulong)bVar14);
        bVar14 = *(byte *)(lVar22 + 0x67);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
        *(char *)(lVar27 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        uVar5 = *(ushort *)(puVar19 + 1);
        *(undefined4 *)(lVar27 + 0x7c) = 0x44;
        *(uint *)(lVar27 + 0x88) = (uint)uVar5;
        *(byte *)(lVar22 + 0x67) = bVar14 + 1;
      }
      goto LAB_001d04b0;
    }
    AArch64SysReg_genericRegisterString(uVar16,auStack_e8);
    SStream_concat0(param_2,auStack_e8);
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) == 0) goto LAB_001d04b0;
    uVar17 = MCInst_getOpcode(param_1);
    bVar14 = *(byte *)(param_1 + 0x366);
    lVar27 = AArch64_get_op_access(lVar27,uVar17);
    lVar22 = *(long *)(param_1 + 0x310);
    uVar17 = 0x41;
    goto LAB_001d0554;
  case 0x3a:
    MCInst_getOperand(param_1,0);
    uVar16 = MCOperand_getImm();
    puVar19 = (undefined8 *)lookupPStateByEncoding();
    if (puVar19 == (undefined8 *)0x0) {
      printUInt32Bang(param_2,uVar16);
      lVar27 = *(long *)(param_1 + 800);
      if (*(int *)(lVar27 + 0x60) != 0) {
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar27 = AArch64_get_op_access(lVar27,uVar17);
        lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar4 = *(char *)(lVar27 + (ulong)bVar14);
        bVar14 = *(byte *)(lVar22 + 0x67);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
        *(char *)(lVar27 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar27 + 0x7c) = 2;
        *(ulong *)(lVar27 + 0x88) = (ulong)uVar16;
        *(byte *)(lVar22 + 0x67) = bVar14 + 1;
      }
      goto LAB_001d04b0;
    }
    SStream_concat0(param_2,*puVar19);
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) == 0) goto LAB_001d04b0;
    uVar17 = MCInst_getOpcode(param_1);
    bVar14 = *(byte *)(param_1 + 0x366);
    lVar27 = AArch64_get_op_access(lVar27,uVar17);
    lVar22 = *(long *)(param_1 + 0x310);
    uVar17 = 0x43;
LAB_001d0554:
    lVar22 = *(long *)(lVar22 + 0xf0);
    cVar4 = *(char *)(lVar27 + (ulong)bVar14);
    bVar14 = *(byte *)(lVar22 + 0x67);
    if (cVar4 == -0x80) {
      cVar4 = '\0';
    }
    lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
    *(char *)(lVar27 + 0x98) = cVar4;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar27 + 0x7c) = uVar17;
    *(uint *)(lVar27 + 0x88) = uVar16;
    *(byte *)(lVar22 + 0x67) = bVar14 + 1;
LAB_001d04b0:
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,1,param_2);
    return;
  case 0x3b:
    MCInst_getOperand(param_1,0);
    MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSVCRByEncoding();
    SStream_concat0(param_2,*puVar19);
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      bVar14 = *(byte *)(lVar27 + 0x67);
      lVar22 = lVar27 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
      *(char *)(lVar22 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      uVar5 = *(ushort *)(puVar19 + 1);
      *(undefined4 *)(lVar22 + 0x7c) = 0x45;
      *(uint *)(lVar22 + 0x80) = (uint)uVar5;
      *(undefined4 *)(lVar22 + 0x88) = 0xda12;
      *(byte *)(lVar27 + 0x67) = bVar14 + 1;
    }
    goto LAB_001d04b0;
  case 0x3c:
    MCInst_getOperand(param_1,0);
    MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSVEPRFMByEncoding();
    if (puVar19 != (undefined8 *)0x0) {
      SStream_concat0(param_2,*puVar19);
    }
    SStream_concat0(param_2,", ");
    printSVERegOp(param_1,1,param_2,0);
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    break;
  case 0x3d:
    MCInst_getOperand(param_1,0);
    MCOperand_getImm();
    puVar19 = (undefined8 *)lookupPRFMByEncoding();
    if (puVar19 != (undefined8 *)0x0) {
      SStream_concat0(param_2,*puVar19);
    }
    break;
  case 0x3e:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x68);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 8;
    goto LAB_001d0184;
  case 0x3f:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x73);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xb;
    goto LAB_001d0184;
  case 0x40:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,100);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 0xd;
    goto LAB_001d0184;
  case 0x41:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x62);
    uVar24 = *(undefined8 *)(param_1 + 0x3b0);
    uVar25 = 4;
LAB_001d0184:
    printVectorList(param_1,0,param_2,auStack_e8,uVar24,uVar25);
    SStream_concat0(param_2,&DAT_001fdfa0);
    MCInst_getOperand(param_1,1);
    uVar17 = MCOperand_getImm();
    printInt32(param_2,uVar17);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      MCInst_getOperand(param_1,1);
      uVar17 = MCOperand_getImm();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar16 = *(byte *)(lVar27 + 0x67) - 1;
      *(undefined4 *)
       (lVar27 + ((-(ulong)(uVar16 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar16 << 3) -
                 (long)(int)uVar16) * 8 + 0x68) = uVar17;
    }
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,&DAT_001fe5b8);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    goto switchD_001d014c_default;
  case 0x42:
    lVar27 = 0;
    iVar15 = 0;
    MCInst_getOperand(param_1,0);
    uVar16 = MCOperand_getImm();
    bVar14 = (byte)uVar16;
    bVar30 = (byte)(uVar16 >> 8);
    bVar31 = (byte)(uVar16 >> 0x10);
    bVar32 = (byte)(uVar16 >> 0x18);
    iVar28 = CONCAT13(bVar32 & (byte)((ulong)_DAT_0020c710 >> 0x18),
                      CONCAT12(bVar31 & (byte)((ulong)_DAT_0020c710 >> 0x10),
                               CONCAT11(bVar30 & (byte)((ulong)_DAT_0020c710 >> 8),
                                        bVar14 & (byte)_DAT_0020c710)));
    uVar18 = (ulong)_DAT_0020c710 >> 0x20;
    uVar26 = (ulong)_DAT_0020c710 >> 0x28;
    uVar6 = (ulong)_DAT_0020c710 >> 0x30;
    uVar7 = (ulong)_DAT_0020c710 >> 0x38;
    iVar29 = CONCAT13(bVar32 & (byte)((ulong)_UNK_0020c718 >> 0x18),
                      CONCAT12(bVar31 & (byte)((ulong)_UNK_0020c718 >> 0x10),
                               CONCAT11(bVar30 & (byte)((ulong)_UNK_0020c718 >> 8),
                                        bVar14 & (byte)_UNK_0020c718)));
    uVar8 = (ulong)_UNK_0020c718 >> 0x20;
    uVar9 = (ulong)_UNK_0020c718 >> 0x28;
    uVar10 = (ulong)_UNK_0020c718 >> 0x30;
    uVar11 = (ulong)_UNK_0020c718 >> 0x38;
    uVar33 = (uint)_DAT_0020c720;
    uVar12 = (ulong)_DAT_0020c720 >> 0x20;
    uVar34 = (uint)_UNK_0020c728;
    uVar13 = (ulong)_UNK_0020c728 >> 0x20;
    SStream_concat0(param_2,&DAT_001f95d0);
    do {
      if ((1 << (ulong)((uint)lVar27 & 0x1f) & uVar16) != 0) {
        iVar1 = (&MatrixZADRegisterTable)[lVar27];
        SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                                *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar1 - 1) * 2));
        lVar22 = *(long *)(param_1 + 800);
        if (*(int *)(lVar22 + 0x60) != 0) {
          uVar17 = MCInst_getOpcode(param_1);
          bVar2 = *(byte *)(param_1 + 0x366);
          lVar22 = AArch64_get_op_access(lVar22,uVar17);
          lVar23 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar4 = *(char *)(lVar22 + (ulong)bVar2);
          bVar2 = *(byte *)(lVar23 + 0x67);
          if (cVar4 == -0x80) {
            cVar4 = '\0';
          }
          lVar22 = lVar23 + ((ulong)bVar2 * 8 - (ulong)bVar2) * 8;
          *(char *)(lVar22 + 0x98) = cVar4;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar22 + 0x7c) = 1;
          *(int *)(lVar22 + 0x88) = iVar1;
          *(byte *)(lVar23 + 0x67) = bVar2 + 1;
        }
        iVar15 = iVar15 + 1;
        if ((uint)(~-(iVar28 == 0) & 1) + (uint)((uVar16 & uVar33) != 0) +
            (uint)(~-((int)(CONCAT17(bVar32 & (byte)uVar7,
                                     CONCAT16(bVar31 & (byte)uVar6,
                                              CONCAT15(bVar30 & (byte)uVar26,
                                                       CONCAT14(bVar14 & (byte)uVar18,iVar28)))) >>
                           0x20) == 0) & 1) + (uint)((uVar16 & (uint)uVar12) != 0) +
            (uint)(~-(iVar29 == 0) & 1) + (uint)((uVar16 & uVar34) != 0) +
            (uint)(~-((int)(CONCAT17(bVar32 & (byte)uVar11,
                                     CONCAT16(bVar31 & (byte)uVar10,
                                              CONCAT15(bVar30 & (byte)uVar9,
                                                       CONCAT14(bVar14 & (byte)uVar8,iVar29)))) >>
                           0x20) == 0) & 1) + (uint)((uVar16 & (uint)uVar13) != 0) != iVar15) {
          SStream_concat0(param_2,", ");
        }
      }
      lVar27 = lVar27 + 1;
    } while (lVar27 != 8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    SStream_concat0(param_2,&DAT_001f96d0);
    return;
  default:
    goto switchD_001d014c_default;
  }
  uVar18 = (((ulong)uVar16 & 0xfe00000) >> 0x15) - 1;
  if (0x43 < uVar18) goto switchD_001d014c_default;
  switch(uVar18 & 0xffffffff) {
  case 0:
    goto switchD_001d03a4_caseD_0;
  case 1:
    printSVERegOp(param_1,2,param_2,0);
    SStream_concat0(param_2,&DAT_001ffc98);
    break;
  case 2:
    SStream_concat0(param_2,".16b, ");
    arm64_op_addVectorArrSpecifier(param_1,1);
    break;
  case 3:
    SStream_concat0(param_2,".2s, ");
    arm64_op_addVectorArrSpecifier(param_1,10);
    break;
  case 4:
    SStream_concat0(param_2,".2d, ");
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    break;
  case 5:
    SStream_concat0(param_2,".4h, ");
    arm64_op_addVectorArrSpecifier(param_1,6);
    break;
  case 6:
    SStream_concat0(param_2,".4s, ");
    arm64_op_addVectorArrSpecifier(param_1,9);
    break;
  case 7:
    SStream_concat0(param_2,".8h, ");
    arm64_op_addVectorArrSpecifier(param_1,5);
    break;
  case 8:
    SStream_concat0(param_2,".8b, ");
    arm64_op_addVectorArrSpecifier(param_1,2);
    break;
  case 9:
    printSVERegOp(param_1,3,param_2,100);
    break;
  case 10:
    printSVERegOp(param_1,3,param_2,0x73);
    break;
  case 0xb:
    printSVERegOp(param_1,1,param_2,0x73);
    break;
  case 0xc:
    printSVERegOp(param_1,2,param_2,0x73);
    break;
  case 0xd:
    printSVERegOp(param_1,1,param_2,0);
    break;
  case 0xe:
    printSVERegOp(param_1,1,param_2,0x68);
    break;
  case 0xf:
    pcVar21 = ", [";
    goto LAB_001d1fd0;
  case 0x10:
    printSVERegOp(param_1,2,param_2,100);
    break;
  case 0x11:
    printSVERegOp(param_1,2,param_2,0x68);
    break;
  case 0x12:
    goto switchD_001d03a4_caseD_12;
  case 0x13:
    MCInst_getOperand(param_1,1);
    iVar15 = MCOperand_getImm();
    MCInst_getOperand(param_1,2);
    uVar16 = MCOperand_getImm();
    if ((iVar15 != 0) || ((uVar16 & 0x3f) == 0)) {
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,uVar16 & 0x3f,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printUInt32Bang(param_2,iVar15 << (ulong)(uVar16 & 0x1f));
      return;
    }
    goto LAB_001d6fe0;
  case 0x14:
    printOperand(param_1,1,param_2);
    break;
  case 0x15:
    printSVERegOp(param_1,1,param_2,0x71);
    break;
  case 0x16:
    printZPRasFPR(param_1,2,param_2,0x40);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,3,param_2,100);
    return;
  case 0x17:
    printZPRasFPR(param_1,2,param_2,0x10);
    break;
  case 0x18:
    printZPRasFPR(param_1,2,param_2,0x20);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,3,param_2,0x73);
    return;
  case 0x19:
    goto switchD_001d03a4_caseD_19;
  case 0x1a:
    goto switchD_001d03a4_caseD_1a;
  case 0x1b:
    SStream_concat0(param_2,&DAT_001ffd38);
    SStream_concat0(param_2,&DAT_001fdfa0);
    goto LAB_001d1c9c;
  case 0x1c:
    pcVar21 = "/z, [";
LAB_001d1fd0:
    SStream_concat0(param_2,pcVar21);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    break;
  case 0x1d:
    printSImm(param_1,1,param_2,0x10);
    SStream_concat0(param_2,", ");
    break;
  case 0x1e:
    SStream_concat0(param_2,&DAT_001fe630);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    break;
  case 0x1f:
    printOperand(param_1,2,param_2);
    break;
  case 0x20:
    SStream_concat0(param_2,&DAT_001ffd48);
    uVar24 = 8;
    goto LAB_001d28b4;
  case 0x21:
    SStream_concat0(param_2,&DAT_001ffd50);
    uVar24 = 0xb;
    goto LAB_001d28b4;
  case 0x22:
    SStream_concat0(param_2,&DAT_001ffd58);
    uVar24 = 4;
LAB_001d28b4:
    arm64_op_addVectorArrSpecifier(param_1,uVar24);
    SStream_concat0(param_2,&DAT_001fdfa0);
LAB_001d1c9c:
    MCInst_getOperand(param_1,2);
    uVar17 = MCOperand_getImm();
    printInt32(param_2,uVar17);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      MCInst_getOperand(param_1,2);
      uVar17 = MCOperand_getImm();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar34 = *(byte *)(lVar27 + 0x67) - 1;
      *(undefined4 *)
       (lVar27 + ((-(ulong)(uVar34 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar34 << 3) -
                 (long)(int)uVar34) * 8 + 0x68) = uVar17;
    }
switchD_001d03a4_caseD_0:
    SStream_concat0(param_2,", ");
    break;
  case 0x23:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0x40);
    return;
  case 0x24:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0x20);
    return;
  case 0x25:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0x10);
    return;
  case 0x26:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,8);
    return;
  case 0x27:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,1);
    return;
  case 0x28:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,4);
    return;
  case 0x29:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,2);
    return;
  case 0x2a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0x30);
    return;
  case 0x2b:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0x18);
    return;
  case 0x2c:
    SStream_concat0(param_2,&DAT_001fe640);
    lVar27 = *(long *)(param_1 + 800);
    if ((*(byte *)(lVar27 + 0x6d) & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    printSVERegOp(param_1,3,param_2,0);
    break;
  case 0x2d:
    goto LAB_001d080c;
  case 0x2e:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,2);
    return;
  case 0x2f:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,4);
    return;
  case 0x30:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,8);
    return;
  case 0x31:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,1);
    return;
  case 0x32:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,0x10);
    return;
  case 0x33:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2);
    return;
  case 0x34:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,0xc);
    return;
  case 0x35:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,3,param_2,6);
    return;
  case 0x36:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,6);
    return;
  case 0x37:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,0xc);
    return;
  case 0x38:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,0x18);
    return;
  case 0x39:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,3);
    return;
  case 0x3a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,5,param_2,0x20);
    return;
  case 0x3b:
    printSVERegOp(param_1,1,param_2,0x62);
    break;
  case 0x3c:
    printSVERegOp(param_1,1,param_2,100);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,100);
    return;
  case 0x3d:
    SStream_concat0(param_2,".1q, ");
    arm64_op_addVectorArrSpecifier(param_1,0xe);
    printVRegOperand(param_1,1,param_2);
    break;
  case 0x3e:
    MCInst_getOperand(param_1,1);
    uVar17 = MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSVEPREDPATByEncoding();
    if (puVar19 == (undefined8 *)0x0) {
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printUInt32Bang(param_2,uVar17);
      return;
    }
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(puVar19,PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    SStream_concat0(param_2,*puVar19);
    return;
  case 0x3f:
    printSVERegOp(param_1,2,param_2,0x62);
    break;
  case 0x40:
    SStream_concat0(param_2,".1d, ");
    arm64_op_addVectorArrSpecifier(param_1,0xd);
    break;
  case 0x41:
    printSVERegOp(param_1,3,param_2,0x68);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x68);
    return;
  case 0x42:
    goto switchD_001d03a4_caseD_42;
  case 0x43:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x68);
    printVectorList(param_1,1,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),8);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x68);
    return;
  default:
    goto switchD_001d014c_default;
  }
  uVar18 = (CONCAT44(uVar33,uVar16) >> 0x1c & 0x7f) - 1;
  if (0x43 < uVar18) {
switchD_001d47b8_default:
    uVar24 = 2;
LAB_001d1d34:
    printSVERegOp(param_1,uVar24,param_2,0);
    SStream_concat0(param_2,&DAT_001ffc98);
    goto LAB_001d1d50;
  }
  switch(uVar18 & 0xffffffff) {
  case 0:
    goto switchD_001d47b8_caseD_0;
  case 1:
    printVRegOperand(param_1,1,param_2);
    break;
  case 2:
    printOperand(param_1,1,param_2);
    break;
  case 3:
    printSVERegOp(param_1,2,param_2,100);
    break;
  case 4:
    printSVERegOp(param_1,2,param_2,0x73);
    break;
  case 5:
    goto switchD_001d014c_default;
  case 6:
    printSVERegOp(param_1,1,param_2,0x68);
    break;
  case 7:
    SStream_concat0(param_2,", ");
    break;
  case 8:
    printSVERegOp(param_1,1,param_2,100);
    break;
  case 9:
    printSVERegOp(param_1,2,param_2,0x68);
    break;
  case 10:
    printVRegOperand(param_1,2,param_2);
    break;
  case 0xb:
    printSVERegOp(param_1,1,param_2,0);
    break;
  case 0xc:
    SStream_concat0(param_2,&DAT_001ffc98);
    break;
  case 0xd:
    printSVERegOp(param_1,1,param_2,0x62);
    break;
  case 0xe:
    printSVERegOp(param_1,1,param_2,0x73);
    break;
  case 0xf:
    uVar24 = MCInst_getOperand(param_1,1);
    uVar18 = MCOperand_isImm();
    if ((uVar18 & 1) != 0) {
      lVar27 = MCOperand_getImm(uVar24);
      lVar27 = (*(ulong *)(param_1 + 0x318) & 0xfffffffffffff000) + lVar27 * 0x1000;
      printUInt64Bang(param_2,lVar27);
      lVar22 = *(long *)(param_1 + 800);
      if (*(int *)(lVar22 + 0x60) != 0) {
        uVar17 = MCInst_getOpcode(param_1);
        bVar14 = *(byte *)(param_1 + 0x366);
        lVar22 = AArch64_get_op_access(lVar22,uVar17);
        cVar4 = *(char *)(lVar22 + (ulong)bVar14);
        lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        if (cVar4 == -0x80) {
          cVar4 = '\0';
        }
        cVar3 = *(char *)(lVar22 + 0x67);
        lVar23 = lVar22 + (ulong)*(byte *)(lVar22 + 0x67) * 0x38;
        *(char *)(lVar23 + 0x98) = cVar4;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar23 + 0x7c) = 2;
        *(long *)(lVar23 + 0x88) = lVar27;
        *(char *)(lVar22 + 0x67) = cVar3 + '\x01';
      }
    }
    goto switchD_001d014c_default;
  case 0x10:
    printOperand(param_1,2,param_2);
    break;
  case 0x11:
    goto switchD_001d5990_caseD_1;
  case 0x12:
    printImmHex(param_1,2,param_2);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printShifter(param_1,3,param_2);
    return;
  case 0x13:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printAlignedLabel(param_1,1,param_2);
    return;
  case 0x14:
    printSVERegOp(param_1,2,param_2,0x62);
    SStream_concat0(param_2,", ");
    break;
  case 0x15:
    SStream_concat0(param_2,&DAT_001ffd70);
    break;
  case 0x16:
    MCInst_getOperand(param_1,1);
    uVar17 = MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSVEPREDPATByEncoding();
    if (puVar19 == (undefined8 *)0x0) {
      printUInt32Bang(param_2,uVar17);
    }
    else {
      SStream_concat0(param_2,*puVar19);
    }
    break;
  case 0x17:
    MCInst_getOperand(param_1,3);
    iVar15 = MCOperand_getImm();
    MCInst_getOperand(param_1,4);
    uVar16 = MCOperand_getImm();
    if ((iVar15 == 0) && ((uVar16 & 0x3f) != 0)) {
      printUInt32Bang(param_2,0);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printShifter(param_1,4,param_2);
      return;
    }
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(uVar16 & 0x3f,PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printUInt32Bang(param_2,iVar15 << (ulong)(uVar16 & 0x1f));
    return;
  case 0x18:
    goto switchD_001d47b8_caseD_18;
  case 0x19:
    goto switchD_001d03a4_caseD_12;
  case 0x1a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printLogicalImm64(param_1,1,param_2);
    return;
  case 0x1b:
    MCInst_getOperand(param_1,1);
    iVar15 = MCOperand_getImm();
    MCInst_getOperand(param_1,2);
    uVar16 = MCOperand_getImm();
    if ((iVar15 != 0) || ((uVar16 & 0x3f) == 0)) {
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(uVar16 & 0x3f,PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printUInt32Bang(param_2,iVar15 << (ulong)(uVar16 & 0x1f));
      return;
    }
    goto LAB_001d6fe0;
  case 0x1c:
    MCInst_getOperand(param_1,1);
    iVar15 = MCOperand_getImm();
    MCInst_getOperand(param_1,2);
    uVar16 = MCOperand_getImm();
    if ((iVar15 != 0) || ((uVar16 & 0x3f) == 0)) {
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(uVar16 & 0x3f,PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printUInt64Bang(param_2,iVar15 << (ulong)(uVar16 & 0x1f));
      return;
    }
    goto LAB_001d6fe0;
  case 0x1d:
    MCInst_getOperand(param_1,1);
    iVar15 = MCOperand_getImm();
    MCInst_getOperand(param_1,2);
    uVar16 = MCOperand_getImm();
    if ((iVar15 != 0) || ((uVar16 & 0x3f) == 0)) {
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(uVar16 & 0x3f,PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printUInt32Bang(param_2,iVar15 << (ulong)(uVar16 & 0x1f));
      return;
    }
LAB_001d6fe0:
    printUInt32Bang(param_2,0);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printShifter(param_1,2,param_2);
    return;
  case 0x1e:
    SStream_concat0(param_2,&DAT_001fdfa0);
    MCInst_getOperand(param_1,2);
    uVar17 = MCOperand_getImm();
    printInt32(param_2,uVar17);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      MCInst_getOperand(param_1,2);
      uVar17 = MCOperand_getImm();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar16 = *(byte *)(lVar27 + 0x67) - 1;
      *(undefined4 *)
       (lVar27 + ((-(ulong)(uVar16 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar16 << 3) -
                 (long)(int)uVar16) * 8 + 0x68) = uVar17;
    }
    goto switchD_001d014c_default;
  case 0x1f:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x62);
    printVectorList(param_1,1,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),4);
    SStream_concat0(param_2,", ");
    break;
  case 0x20:
    goto switchD_001d5990_caseD_38;
  case 0x21:
    goto switchD_001d5990_caseD_0;
  case 0x22:
switchD_001d03a4_caseD_1a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printFPImmOperand(param_1,1,param_2);
    return;
  case 0x23:
    printSImm(param_1,1,param_2,8);
    SStream_concat0(param_2,", ");
    break;
  case 0x24:
    goto switchD_001d5990_caseD_3d;
  case 0x25:
    uVar24 = 3;
    goto LAB_001d1d34;
  case 0x26:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printZPRasFPR(param_1,2,param_2,8);
    return;
  case 0x27:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printZPRasFPR(param_1,2,param_2,0x40);
    return;
  case 0x28:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printZPRasFPR(param_1,2,param_2,0x20);
    return;
  case 0x29:
    printVRegOperand(param_1,3,param_2);
    break;
  case 0x2a:
    pcVar21 = "/z, [";
    goto LAB_001d4bd4;
  case 0x2b:
    printOperand(param_1,0,param_2);
    goto LAB_001d4f90;
  case 0x2c:
    MCInst_getOperand(param_1,1);
    bVar14 = MCOperand_getImm();
    uVar18 = 0xffff000000000000;
    if (-1 < (char)bVar14) {
      uVar18 = 0xff000000000000;
    }
    uVar26 = 0xff00000000000000;
    if (-1 < (char)bVar14) {
      uVar26 = 0;
    }
    if ((bVar14 & 0x40) == 0) {
      uVar18 = uVar26;
    }
    uVar26 = uVar18 | 0xff0000000000;
    if ((bVar14 & 0x20) == 0) {
      uVar26 = uVar18;
    }
    uVar18 = uVar26 | 0xff00000000;
    if ((bVar14 & 0x10) == 0) {
      uVar18 = uVar26;
    }
    uVar26 = uVar18 | 0xff000000;
    if ((bVar14 & 8) == 0) {
      uVar26 = uVar18;
    }
    uVar18 = uVar26 | 0xff0000;
    if ((bVar14 & 4) == 0) {
      uVar18 = uVar26;
    }
    uVar26 = uVar18 | 0xff00;
    if ((bVar14 & 2) == 0) {
      uVar26 = uVar18;
    }
    uVar26 = (byte)-(bVar14 & 1) | uVar26;
    SStream_concat(param_2,"#%#016llx",uVar26);
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      bVar14 = *(byte *)(lVar22 + 0x67);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar22 + ((ulong)bVar14 * 8 - (ulong)bVar14) * 8;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 2;
      *(ulong *)(lVar27 + 0x88) = uVar26;
      *(byte *)(lVar22 + 0x67) = bVar14 + 1;
    }
    goto switchD_001d014c_default;
  case 0x2d:
    printImmHex(param_1,1,param_2);
    break;
  case 0x2e:
    MCInst_getOperand(param_1,1);
    iVar15 = MCOperand_getImm();
    puVar19 = (undefined8 *)lookupSysRegByEncoding();
    if (iVar15 == 0x9828) {
      SStream_concat0(param_2,"dbgdtrrx_el0");
      lVar27 = *(long *)(param_1 + 800);
      iVar28 = *(int *)(lVar27 + 0x60);
joined_r0x001d7280:
      if (iVar28 == 0) goto switchD_001d014c_default;
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      uVar17 = 0x44;
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    }
    else {
      if (iVar15 == 0xe100) {
        SStream_concat0(param_2,"ttbr0_el2");
        lVar27 = *(long *)(param_1 + 800);
        iVar28 = *(int *)(lVar27 + 0x60);
        goto joined_r0x001d7280;
      }
      if ((puVar19 != (undefined8 *)0x0) && ((*(byte *)((long)puVar19 + 10) & 1) != 0)) {
        SStream_concat0(param_2,*puVar19);
        lVar27 = *(long *)(param_1 + 800);
        if (*(int *)(lVar27 + 0x60) != 0) {
          uVar17 = MCInst_getOpcode(param_1);
          bVar14 = *(byte *)(param_1 + 0x366);
          lVar27 = AArch64_get_op_access(lVar27,uVar17);
          cVar4 = *(char *)(lVar27 + (ulong)bVar14);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar4 == -0x80) {
            cVar4 = '\0';
          }
          cVar3 = *(char *)(lVar27 + 0x67);
          lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
          *(char *)(lVar22 + 0x98) = cVar4;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          uVar5 = *(ushort *)(puVar19 + 1);
          *(undefined4 *)(lVar22 + 0x7c) = 0x44;
          *(uint *)(lVar22 + 0x88) = (uint)uVar5;
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
        }
        goto switchD_001d014c_default;
      }
      AArch64SysReg_genericRegisterString(iVar15,auStack_e8);
      SStream_concat0(param_2,auStack_e8);
      lVar27 = *(long *)(param_1 + 800);
      if (*(int *)(lVar27 + 0x60) == 0) goto switchD_001d014c_default;
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      uVar17 = 0x41;
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    }
    if (cVar4 == -0x80) {
      cVar4 = '\0';
    }
    cVar3 = *(char *)(lVar27 + 0x67);
    lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
    *(char *)(lVar22 + 0x98) = cVar4;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar22 + 0x7c) = uVar17;
    *(int *)(lVar22 + 0x88) = iVar15;
    *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
    goto switchD_001d014c_default;
  case 0x2f:
    SStream_concat0(param_2,".1d, ");
    arm64_op_addVectorArrSpecifier(param_1,0xd);
    printVRegOperand(param_1,2,param_2);
    SStream_concat0(param_2,&DAT_001ffd98);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addVectorArrSpecifier(param_1,0xd);
    return;
  case 0x30:
    SStream_concat0(param_2,".2d, ");
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    printVRegOperand(param_1,2,param_2);
    SStream_concat0(param_2,&DAT_001ffda0);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    return;
  case 0x31:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,3,param_2,0x71);
    return;
  case 0x32:
    printGPR64as32(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    goto switchD_001d03a4_caseD_12;
  case 0x33:
    pcVar21 = ", [";
LAB_001d4bd4:
    SStream_concat0(param_2,pcVar21);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    printOperand(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x34:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,2);
    return;
  case 0x35:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2);
    return;
  case 0x36:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,8);
    return;
  case 0x37:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,1);
    return;
  case 0x38:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,0x10);
    return;
  case 0x39:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,6);
    return;
  case 0x3a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,0xc);
    return;
  case 0x3b:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,0x18);
    return;
  case 0x3c:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,3);
    return;
  case 0x3d:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printPostIncOperand(param_1,4,param_2,0x20);
    return;
  case 0x3e:
    MCInst_getOperand(param_1,1);
    uVar17 = MCOperand_getReg();
    iVar15 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar17,0x12);
    SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar15 - 1) * 2));
LAB_001d4f90:
    SStream_concat0(param_2,&DAT_001ffca0);
    lVar27 = *(long *)(param_1 + 800);
    *(undefined1 *)(lVar27 + 0x6c) = 1;
    if (*(int *)(lVar27 + 0x60) == 3) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar27 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar27 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar27 + 0x7c) = 3;
      *(undefined8 *)(lVar27 + 0x88) = 0;
      *(undefined4 *)(lVar27 + 0x90) = 0;
    }
    uVar24 = 2;
LAB_001d07fc:
    printOperand(param_1,uVar24,param_2);
LAB_001d080c:
    SStream_concat0(param_2,&DAT_001fe5b8);
    lVar27 = *(long *)(param_1 + 800);
    bVar14 = *(byte *)(lVar27 + 0x6d);
joined_r0x001d1648:
    if ((bVar14 & 1) == 0) {
      *(undefined1 *)(lVar27 + 0x6c) = 0;
      if (*(int *)(lVar27 + 0x60) == 3) {
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
      }
    }
    else {
      *(undefined1 *)(lVar27 + 0x6d) = 0;
    }
    goto switchD_001d014c_default;
  case 0x3f:
    printSysCROperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printSysCROperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,4,param_2);
    return;
  case 0x40:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,100);
    printVectorList(param_1,1,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),0xd);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,100);
    return;
  case 0x41:
    cs_snprintf(auStack_e8,0x20,&DAT_001ffc50,0x73);
    printVectorList(param_1,1,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),0xb);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x73);
    return;
  case 0x42:
    cs_snprintf(auStack_e8,0x20,".%u%c",0x10,0x62);
    printVectorList(param_1,1,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0));
    SStream_concat0(param_2,", ");
    printVRegOperand(param_1,2,param_2);
    break;
  case 0x43:
    cs_snprintf(auStack_e8,0x20,".%u%c",0x10,0x62);
    printVectorList(param_1,2,param_2,auStack_e8,*(undefined8 *)(param_1 + 0x3b0),1);
    SStream_concat0(param_2,", ");
    printVRegOperand(param_1,3,param_2);
    break;
  default:
    goto switchD_001d47b8_default;
  }
LAB_001d1d50:
  uVar18 = ((ulong)(uVar33 >> 3) & 0x7f) - 1;
  if (0x6d < uVar18) {
switchD_001d5990_default:
    printSVERegOp(param_1,3,param_2,0x62);
    goto LAB_001d1d80;
  }
  switch(uVar18 & 0xffffffff) {
  case 0:
    goto switchD_001d5990_caseD_0;
  case 1:
switchD_001d5990_caseD_1:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,3,param_2,0x73);
    return;
  case 2:
    goto switchD_001d5990_caseD_2;
  case 3:
    goto switchD_001d014c_default;
  case 4:
    goto switchD_001d5990_caseD_4;
  case 5:
    goto switchD_001d5990_caseD_5;
  case 6:
    goto switchD_001d5990_caseD_6;
  case 7:
    goto switchD_001d5990_caseD_7;
  case 8:
    goto switchD_001d5990_caseD_8;
  case 9:
    goto switchD_001d5990_caseD_9;
  case 10:
    SStream_concat0(param_2,", ");
    break;
  case 0xb:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x73);
    return;
  case 0xc:
    SStream_concat0(param_2,".2d, ");
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    break;
  case 0xd:
    SStream_concat0(param_2,".4s, ");
    arm64_op_addVectorArrSpecifier(param_1,9);
    break;
  case 0xe:
    SStream_concat0(param_2,".8h, ");
    arm64_op_addVectorArrSpecifier(param_1,5);
    break;
  case 0xf:
    SStream_concat0(param_2,&DAT_001ffc98);
    break;
  case 0x10:
    printSVERegOp(param_1,2,param_2,0x68);
    break;
  case 0x11:
    SStream_concat0(param_2,".16b, ");
    arm64_op_addVectorArrSpecifier(param_1,1);
    break;
  case 0x12:
    SStream_concat0(param_2,".2s, ");
    arm64_op_addVectorArrSpecifier(param_1,10);
    break;
  case 0x13:
    SStream_concat0(param_2,".4h, ");
    arm64_op_addVectorArrSpecifier(param_1,6);
    break;
  case 0x14:
    SStream_concat0(param_2,".8b, ");
    arm64_op_addVectorArrSpecifier(param_1,2);
    break;
  case 0x15:
  case 0x28:
    goto switchD_001d1dac_caseD_f;
  case 0x16:
    SStream_concat0(param_2,&DAT_001ffd70);
    break;
  case 0x17:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,100);
    return;
  case 0x18:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,2,param_2);
    return;
  case 0x19:
    SStream_concat0(param_2,&DAT_001ffca0);
    set_mem_access(param_1,1);
    break;
  case 0x1a:
    SStream_concat0(param_2,".16b, #0");
    arm64_op_addVectorArrSpecifier(param_1,1);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x1b:
    SStream_concat0(param_2,&DAT_001fe5a8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar4 = *(char *)(lVar27 + 0x67);
      lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(undefined4 *)(lVar22 + 0x7c) = 2;
      *(undefined8 *)(lVar22 + 0x88) = 0;
      *(char *)(lVar27 + 0x67) = cVar4 + '\x01';
    }
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x1c:
    SStream_concat0(param_2,".2s, #0");
    arm64_op_addVectorArrSpecifier(param_1,10);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x1d:
    SStream_concat0(param_2,".2d, #0");
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x1e:
    SStream_concat0(param_2,".4h, #0");
    arm64_op_addVectorArrSpecifier(param_1,6);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x1f:
    SStream_concat0(param_2,0x1ffe00);
    arm64_op_addVectorArrSpecifier(param_1,9);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x20:
    SStream_concat0(param_2,".8h, #0");
    arm64_op_addVectorArrSpecifier(param_1,5);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x21:
    SStream_concat0(param_2,".8b, #0");
    arm64_op_addVectorArrSpecifier(param_1,2);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0);
    return;
  case 0x22:
    printSVERegOp(param_1,3,param_2,0x68);
    break;
  case 0x23:
    SStream_concat0(param_2,", mul ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,2,param_2);
    return;
  case 0x24:
  case 0x26:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImm8OptLsl32(param_1,3,param_2);
    return;
  case 0x25:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImm8OptLsl64(param_1,3,param_2);
    return;
  case 0x27:
    printOperand(param_1,3,param_2);
    break;
  case 0x29:
    goto switchD_001d1dac_caseD_29;
  case 0x2a:
    SStream_concat0(param_2,&DAT_001ffd48);
    arm64_op_addVectorArrSpecifier(param_1,8);
    break;
  case 0x2b:
    SStream_concat0(param_2,&DAT_001ffd50);
    arm64_op_addVectorArrSpecifier(param_1,0xb);
    break;
  case 0x2c:
    SStream_concat0(param_2,&DAT_001ffd38);
    break;
  case 0x2d:
    SStream_concat0(param_2,&DAT_001ffd58);
    arm64_op_addVectorArrSpecifier(param_1,4);
    break;
  case 0x2e:
    goto switchD_001d1dac_caseD_2a;
  case 0x2f:
    goto switchD_001d1dac_caseD_2b;
  case 0x30:
    goto switchD_001d1dac_caseD_5c;
  case 0x31:
    goto switchD_001d1dac_caseD_2e;
  case 0x32:
    goto switchD_001d03a4_caseD_19;
  case 0x33:
    SStream_concat0(param_2,".2s, #0.0");
    arm64_op_addVectorArrSpecifier(param_1,10);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addFP(0,param_1);
    return;
  case 0x34:
    SStream_concat0(param_2,&DAT_001ffe30);
    arm64_op_addVectorArrSpecifier(param_1,0xc);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addFP(0,param_1);
    return;
  case 0x35:
    SStream_concat0(param_2,".4h, #0.0");
    arm64_op_addVectorArrSpecifier(param_1,6);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addFP(0,param_1);
    return;
  case 0x36:
    SStream_concat0(param_2,".4s, #0.0");
    arm64_op_addVectorArrSpecifier(param_1,9);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addFP(0,param_1);
    return;
  case 0x37:
    SStream_concat0(param_2,".8h, #0.0");
    arm64_op_addVectorArrSpecifier(param_1,5);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addFP(0,param_1);
    return;
  case 0x38:
switchD_001d5990_caseD_38:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printFPImmOperand(param_1,3,param_2);
    return;
  case 0x39:
    SStream_concat0(param_2,".2h, ");
    arm64_op_addVectorArrSpecifier(param_1,7);
    printVRegOperand(param_1,3,param_2);
    break;
  case 0x3a:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,100);
    return;
  case 0x3b:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x73);
    return;
  case 0x3c:
    goto switchD_001d1dac_caseD_45;
  case 0x3d:
switchD_001d5990_caseD_3d:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSImm(param_1,2,param_2,0x10);
    return;
  case 0x3e:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x62);
    return;
  case 0x3f:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x68);
    return;
  case 0x40:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x71);
    return;
  case 0x41:
    printRegWithShiftExtend(param_1,5,param_2,0,8,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x42:
    printRegWithShiftExtend(param_1,5,param_2,0,0x40,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x43:
    printRegWithShiftExtend(param_1,5,param_2,0,0x10,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x44:
    printRegWithShiftExtend(param_1,5,param_2,0,0x80,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x45:
    printRegWithShiftExtend(param_1,5,param_2,0,0x20,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x46:
    goto switchD_001d1dac_caseD_54;
  case 0x47:
    SStream_concat0(param_2,&DAT_001fe630);
    set_mem_access(param_1,0);
    break;
  case 0x48:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printShifter(param_1,2,param_2);
    return;
  case 0x49:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x62);
    return;
  case 0x4a:
    goto switchD_001d1dac_caseD_30;
  case 0x4b:
    goto switchD_001d1dac_caseD_31;
  case 0x4c:
    goto switchD_001d1dac_caseD_32;
  case 0x4d:
    goto switchD_001d1dac_caseD_46;
  case 0x4e:
    goto switchD_001d1dac_caseD_33;
  case 0x4f:
    goto switchD_001d1dac_caseD_34;
  case 0x50:
    goto switchD_001d5990_caseD_50;
  case 0x51:
    goto switchD_001d1dac_caseD_36;
  case 0x52:
    goto switchD_001d1dac_caseD_37;
  case 0x53:
    goto switchD_001d1dac_caseD_38;
  case 0x54:
    goto switchD_001d1dac_caseD_47;
  case 0x55:
    printRegWithShiftExtend(param_1,3,param_2,1,0x40,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x56:
    printRegWithShiftExtend(param_1,3,param_2,0,0x40,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x57:
    printImmScale(param_1,3,param_2,2);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x58:
    goto switchD_001d1dac_caseD_3a;
  case 0x59:
    goto switchD_001d1dac_caseD_3b;
  case 0x5a:
    goto switchD_001d1dac_caseD_3c;
  case 0x5b:
    goto switchD_001d1dac_caseD_48;
  case 0x5c:
    goto switchD_001d1dac_caseD_3d;
  case 0x5d:
    goto switchD_001d1dac_caseD_3e;
  case 0x5e:
    goto switchD_001d1dac_caseD_4a;
  case 0x5f:
    goto switchD_001d5990_caseD_5f;
  case 0x60:
    goto switchD_001d1dac_caseD_40;
  case 0x61:
    goto switchD_001d1dac_caseD_41;
  case 0x62:
    goto switchD_001d1dac_caseD_42;
  case 99:
    goto switchD_001d1dac_caseD_43;
  case 100:
    goto switchD_001d1dac_caseD_44;
  case 0x65:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    SStream_concat0(param_2,&DAT_001ffe78);
    return;
  case 0x66:
    SStream_concat0(param_2,".16b, #8");
    arm64_op_addVectorArrSpecifier(param_1,1);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,8);
    return;
  case 0x67:
    SStream_concat0(param_2,".2s, #32");
    arm64_op_addVectorArrSpecifier(param_1,10);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0x20);
    return;
  case 0x68:
    SStream_concat0(param_2,".4h, #16");
    arm64_op_addVectorArrSpecifier(param_1,6);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0x10);
    return;
  case 0x69:
    SStream_concat0(param_2,".4s, #32");
    arm64_op_addVectorArrSpecifier(param_1,9);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0x20);
    return;
  case 0x6a:
    SStream_concat0(param_2,".8h, #16");
    arm64_op_addVectorArrSpecifier(param_1,5);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,0x10);
    return;
  case 0x6b:
    SStream_concat0(param_2,".8b, #8");
    arm64_op_addVectorArrSpecifier(param_1,2);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addImm(param_1,8);
    return;
  case 0x6c:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printTypedVectorList(param_1,2,param_2,0,0x68);
    return;
  case 0x6d:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,2,param_2,0x71);
    return;
  default:
    goto switchD_001d5990_default;
  }
LAB_001d1d80:
  uVar18 = ((ulong)(uVar33 >> 10) & 0x7f) - 1;
  if (0x5c < uVar18) goto switchD_001d014c_default;
  switch(uVar18 & 0xffffffff) {
  case 0:
    printSVERegOp(param_1,3,param_2,100);
    break;
  case 1:
    printSVERegOp(param_1,3,param_2,0x73);
    break;
  case 2:
    printOperand(param_1,2,param_2);
    break;
  case 3:
    printImmScale(param_1,2,param_2,0x10);
    break;
  case 4:
    printSVERegOp(param_1,2,param_2,0x68);
    break;
  case 5:
    printSVERegOp(param_1,2,param_2,100);
    break;
  case 6:
    printSVERegOp(param_1,3,param_2,0x68);
    break;
  case 7:
    printVRegOperand(param_1,2,param_2);
    break;
  case 8:
    printVRegOperand(param_1,3,param_2);
    break;
  case 9:
    printSVERegOp(param_1,2,param_2,0x62);
    break;
  case 10:
    SStream_concat0(param_2,", ");
    break;
  case 0xb:
    printSVERegOp(param_1,2,param_2,0x73);
    break;
  case 0xc:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printAddSubImm(param_1,2,param_2);
    return;
  case 0xd:
    MCInst_getOperand(param_1,2);
    iVar15 = MCOperand_getReg();
    SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar15 - 1) * 2));
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      lVar22 = lVar22 + (ulong)*(byte *)(lVar22 + 0x67) * 0x38;
      *(char *)(lVar22 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar22 + 0x7c) = 1;
      MCInst_getOperand(param_1,2);
      lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar14 = *(byte *)(lVar22 + 0x67);
      uVar17 = MCOperand_getReg();
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar22 + (long)(int)(uint)bVar14 * 0x38 + 0x88) = uVar17;
      *(char *)(lVar27 + 0x67) = *(char *)(lVar27 + 0x67) + '\x01';
    }
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printShifter(param_1,3,param_2);
    return;
  case 0xe:
    MCInst_getOperand(param_1,2);
    iVar15 = MCOperand_getReg();
    SStream_concat0(param_2,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar15 - 1) * 2));
    lVar27 = *(long *)(param_1 + 800);
    if (*(int *)(lVar27 + 0x60) != 0) {
      uVar17 = MCInst_getOpcode(param_1);
      bVar14 = *(byte *)(param_1 + 0x366);
      lVar27 = AArch64_get_op_access(lVar27,uVar17);
      cVar4 = *(char *)(lVar27 + (ulong)bVar14);
      lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar4 == -0x80) {
        cVar4 = '\0';
      }
      cVar3 = *(char *)(lVar27 + 0x67);
      lVar22 = lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38;
      *(char *)(lVar22 + 0x98) = cVar4;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar22 + 0x7c) = 1;
      *(int *)(lVar22 + 0x88) = iVar15;
      *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
    }
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printArithExtend(param_1,3,param_2);
    return;
  case 0xf:
  case 0x11:
  case 0x26:
  case 0x28:
switchD_001d1dac_caseD_f:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImm8OptLsl32(param_1,2,param_2);
    return;
  case 0x10:
  case 0x27:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImm8OptLsl64(param_1,2,param_2);
    return;
  case 0x12:
    printRegWithShiftExtend(param_1,2,param_2,0,8,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x13:
    printRegWithShiftExtend(param_1,2,param_2,0,0x10,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x14:
    printRegWithShiftExtend(param_1,2,param_2,0,0x20,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x15:
    printRegWithShiftExtend(param_1,2,param_2,0,0x40,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x16:
    printRegWithShiftExtend(param_1,2,param_2,0,8,0x78,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x17:
    printRegWithShiftExtend(param_1,2,param_2,0,0x10,0x78,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x18:
    printRegWithShiftExtend(param_1,2,param_2,0,0x20,0x78,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x19:
    printRegWithShiftExtend(param_1,2,param_2,0,0x40,0x78,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1a:
    printRegWithShiftExtend(param_1,2,param_2,1,8,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1b:
    printRegWithShiftExtend(param_1,2,param_2,1,0x10,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1c:
    printRegWithShiftExtend(param_1,2,param_2,1,0x20,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1d:
    printRegWithShiftExtend(param_1,2,param_2,1,0x40,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1e:
    printRegWithShiftExtend(param_1,2,param_2,0,8,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x1f:
    printRegWithShiftExtend(param_1,2,param_2,0,0x10,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x20:
    printRegWithShiftExtend(param_1,2,param_2,0,0x20,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x21:
    printRegWithShiftExtend(param_1,2,param_2,0,0x40,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x22:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printLogicalImm32(param_1,2,param_2);
    return;
  case 0x23:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printLogicalImm64(param_1,2,param_2);
    return;
  case 0x24:
    printOperand(param_1,3,param_2);
    break;
  case 0x25:
    printVectorIndex(param_1,4,param_2);
    break;
  case 0x29:
switchD_001d1dac_caseD_29:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printVectorIndex(param_1,2,param_2);
    return;
  case 0x2a:
switchD_001d1dac_caseD_2a:
    uVar24 = 0;
    goto LAB_001d301c;
  case 0x2b:
switchD_001d1dac_caseD_2b:
    uVar24 = 1;
LAB_001d301c:
    printMatrixTileVector(param_1,2,param_2,uVar24);
    goto LAB_001d3034;
  case 0x2c:
    goto switchD_001d03a4_caseD_19;
  case 0x2d:
    SStream_concat0(param_2,&DAT_001ffd48);
    arm64_op_addVectorArrSpecifier(param_1,8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printVectorIndex(param_1,4,param_2);
    return;
  case 0x2e:
switchD_001d1dac_caseD_2e:
    SStream_concat0(param_2,&DAT_001ffe18);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    arm64_op_addVectorArrSpecifier(param_1,7);
    return;
  case 0x2f:
    goto switchD_001d1dac_caseD_2f;
  case 0x30:
switchD_001d1dac_caseD_30:
    printRegWithShiftExtend(param_1,3,param_2,0,8,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x31:
switchD_001d1dac_caseD_31:
    printRegWithShiftExtend(param_1,3,param_2,1,8,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x32:
switchD_001d1dac_caseD_32:
    printRegWithShiftExtend(param_1,3,param_2,0,8,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x33:
switchD_001d1dac_caseD_33:
    printRegWithShiftExtend(param_1,3,param_2,1,8,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x34:
switchD_001d1dac_caseD_34:
    printRegWithShiftExtend(param_1,3,param_2,0,8,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x35:
    printImmScale(param_1,3,param_2,8);
    break;
  case 0x36:
switchD_001d1dac_caseD_36:
    printRegWithShiftExtend(param_1,3,param_2,0,0x40,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x37:
switchD_001d1dac_caseD_37:
    printRegWithShiftExtend(param_1,3,param_2,1,0x40,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x38:
switchD_001d1dac_caseD_38:
    printRegWithShiftExtend(param_1,3,param_2,0,0x40,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x39:
    printImmScale(param_1,3,param_2,2);
    break;
  case 0x3a:
switchD_001d1dac_caseD_3a:
    printRegWithShiftExtend(param_1,3,param_2,0,0x10,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x3b:
switchD_001d1dac_caseD_3b:
    printRegWithShiftExtend(param_1,3,param_2,1,0x10,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x3c:
switchD_001d1dac_caseD_3c:
    printRegWithShiftExtend(param_1,3,param_2,0,0x10,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x3d:
switchD_001d1dac_caseD_3d:
    printRegWithShiftExtend(param_1,3,param_2,1,0x10,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x3e:
switchD_001d1dac_caseD_3e:
    printRegWithShiftExtend(param_1,3,param_2,0,0x10,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x3f:
    printImmScale(param_1,3,param_2,4);
    break;
  case 0x40:
switchD_001d1dac_caseD_40:
    printRegWithShiftExtend(param_1,3,param_2,0,0x20,0x78,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x41:
switchD_001d1dac_caseD_41:
    printRegWithShiftExtend(param_1,3,param_2,1,0x20,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x42:
switchD_001d1dac_caseD_42:
    printRegWithShiftExtend(param_1,3,param_2,0,0x20,0x77,100);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x43:
switchD_001d1dac_caseD_43:
    printRegWithShiftExtend(param_1,3,param_2,1,0x20,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x44:
switchD_001d1dac_caseD_44:
    printRegWithShiftExtend(param_1,3,param_2,0,0x20,0x77,0x73);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x45:
switchD_001d1dac_caseD_45:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSImm(param_1,2,param_2,8);
    return;
  case 0x46:
switchD_001d1dac_caseD_46:
    printRegWithShiftExtend(param_1,3,param_2,0,8,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x47:
switchD_001d1dac_caseD_47:
    printRegWithShiftExtend(param_1,3,param_2,0,0x40,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x48:
switchD_001d1dac_caseD_48:
    printRegWithShiftExtend(param_1,3,param_2,0,0x10,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x49:
    printImmScale(param_1,3,param_2,0x20);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x4a:
switchD_001d1dac_caseD_4a:
    printRegWithShiftExtend(param_1,3,param_2,0,0x20,0x78,0);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x4b:
    printImmScale(param_1,3,param_2,0x10);
    break;
  case 0x4c:
    printImmScale(param_1,3,param_2);
    SStream_concat0(param_2,", mul vl]");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x4d:
    printImmScale(param_1,2,param_2,8);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x4e:
    printUImm12Offset_constprop_0(param_1,param_2,1);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x4f:
    printUImm12Offset_constprop_0(param_1,param_2,8);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x50:
    printUImm12Offset_constprop_0(param_1,param_2,2);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x51:
    printUImm12Offset_constprop_0(param_1,param_2,0x10);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x52:
    printUImm12Offset_constprop_0(param_1,param_2,4);
    SStream_concat0(param_2,&DAT_001fe5b8);
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access(param_1,0);
    return;
  case 0x53:
switchD_001d03a4_caseD_42:
    printSVERegOp(param_1,3,param_2,0x62);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp(param_1,4,param_2,0x62);
    return;
  case 0x54:
    goto switchD_001d1dac_caseD_54;
  case 0x55:
    goto switchD_001d1dac_caseD_55;
  case 0x56:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printTypedVectorList(param_1,2,param_2,0,0x62);
    return;
  case 0x57:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printTypedVectorList(param_1,2,param_2,0,100);
    return;
  case 0x58:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printTypedVectorList(param_1,2,param_2,0,0x73);
    return;
  case 0x59:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printGPR64as32(param_1,2,param_2);
    return;
  case 0x5a:
    printSysCROperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printSysCROperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand(param_1,4,param_2);
    return;
  case 0x5b:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printAlignedLabel(param_1,2,param_2);
    return;
  case 0x5c:
switchD_001d1dac_caseD_5c:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImmHex(param_1,2,param_2);
    return;
  default:
    goto switchD_001d014c_default;
  }
  uVar18 = ((ulong)(uVar33 >> 0x11) & 0x3f) - 1;
  if (uVar18 < 0x28) {
    switch(uVar18 & 0xffffffff) {
    case 0:
      SStream_concat0(param_2,", ");
      break;
    case 1:
switchD_001d5990_caseD_5:
      SStream_concat0(param_2,&DAT_001ffda0);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,0xc);
      return;
    case 2:
      goto switchD_001d5990_caseD_7;
    case 3:
switchD_001d5990_caseD_8:
      SStream_concat0(param_2,&DAT_001ffdc8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,5);
      return;
    case 4:
      printSVERegOp(param_1,3,param_2,0x68);
      break;
    case 5:
      goto switchD_001d5990_caseD_2;
    case 6:
switchD_001d5990_caseD_4:
      SStream_concat0(param_2,&DAT_001ffdb0);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,10);
      return;
    case 7:
switchD_001d5990_caseD_6:
      SStream_concat0(param_2,&DAT_001ffdb8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,6);
      return;
    case 8:
switchD_001d5990_caseD_9:
      SStream_concat0(param_2,&DAT_001ffdd0);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,2);
      return;
    case 9:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printArithExtend(param_1,3,param_2);
      return;
    case 10:
      goto switchD_001d47b8_caseD_18;
    case 0xb:
switchD_001d5990_caseD_0:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printSVERegOp(param_1,3,param_2,100);
      return;
    case 0xc:
      SStream_concat0(param_2,".16b, ");
      arm64_op_addVectorArrSpecifier(param_1,1);
      break;
    case 0xd:
      SStream_concat0(param_2,&DAT_001ffe18);
      arm64_op_addVectorArrSpecifier(param_1,7);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printVectorIndex(param_1,4,param_2);
      return;
    case 0xe:
      printVectorIndex(param_1,4,param_2);
      break;
    case 0xf:
      SStream_concat0(param_2,&DAT_001ffd48);
      arm64_op_addVectorArrSpecifier(param_1,8);
      break;
    case 0x10:
      goto switchD_001d3f24_caseD_10;
    case 0x11:
switchD_001d1dac_caseD_54:
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x12:
      goto switchD_001d3f24_caseD_12;
    case 0x13:
      goto switchD_001d3f24_caseD_13;
    case 0x14:
      SStream_concat0(param_2,".8b, ");
      arm64_op_addVectorArrSpecifier(param_1,2);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printOperand(param_1,3,param_2);
      return;
    case 0x15:
      goto switchD_001d3f24_caseD_15;
    case 0x16:
      SStream_concat0(param_2,".2s, ");
      arm64_op_addVectorArrSpecifier(param_1,10);
      break;
    case 0x17:
      SStream_concat0(param_2,".2d, ");
      arm64_op_addVectorArrSpecifier(param_1,0xc);
      break;
    case 0x18:
      SStream_concat0(param_2,".4h, ");
      arm64_op_addVectorArrSpecifier(param_1,6);
      break;
    case 0x19:
      SStream_concat0(param_2,".4s, ");
      arm64_op_addVectorArrSpecifier(param_1,9);
      break;
    case 0x1a:
      SStream_concat0(param_2,".8h, ");
      arm64_op_addVectorArrSpecifier(param_1,5);
      break;
    case 0x1b:
switchD_001d03a4_caseD_19:
      SStream_concat0(param_2,", #0.0");
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addFP(0,param_1);
      return;
    case 0x1c:
      printSVERegOp(param_1,4,param_2,0x68);
      break;
    case 0x1d:
      SStream_concat0(param_2,&DAT_001ffd50);
      arm64_op_addVectorArrSpecifier(param_1,0xb);
      break;
    case 0x1e:
      goto switchD_001d3f24_caseD_1e;
    case 0x1f:
      SStream_concat0(param_2,&DAT_001ffd38);
      break;
    case 0x20:
      goto switchD_001d3f24_caseD_20;
    case 0x21:
      goto switchD_001d1dac_caseD_2f;
    case 0x22:
switchD_001d1dac_caseD_55:
      SStream_concat0(param_2,", mul vl]");
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x23:
      SStream_concat0(param_2,&DAT_001fe630);
      set_mem_access(param_1,0);
      break;
    case 0x24:
      goto switchD_001d3f24_caseD_24;
    case 0x25:
LAB_001d3034:
      SStream_concat0(param_2,&DAT_001fdfa0);
      lVar27 = *(long *)(param_1 + 800);
      *(undefined1 *)(lVar27 + 0x6d) = 1;
      if (*(int *)(lVar27 + 0x60) == 3) {
        set_sme_index_part_0(param_1);
      }
      printOperand(param_1,3,param_2);
      SStream_concat0(param_2,", ");
      printMatrixIndex(param_1,4,param_2);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x26:
      SStream_concat0(param_2,&DAT_001ffed8);
      arm64_op_addVectorArrSpecifier(param_1,3);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printVectorIndex(param_1,4,param_2);
      return;
    case 0x27:
      SStream_concat0(param_2,&DAT_001ffca0);
      set_mem_access(param_1,1);
      printOperand(param_1,3,param_2);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    default:
      goto switchD_001d014c_default;
    }
    uVar18 = ((ulong)(uVar33 >> 0x17) & 0x3f) - 1;
    if (0x23 < uVar18) {
switchD_001d47b8_caseD_18:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printOperand(param_1,3,param_2);
      return;
    }
    switch(uVar18 & 0xffffffff) {
    case 0:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printSVERegOp(param_1,3,param_2,0x62);
      return;
    case 1:
      printSVERegOp(param_1,3,param_2,100);
      break;
    case 2:
      goto switchD_001d014c_default;
    case 3:
      printSVERegOp(param_1,3,param_2,0x73);
      break;
    case 4:
      printVRegOperand(param_1,3,param_2);
      break;
    case 5:
      printVectorIndex(param_1,4,param_2);
      break;
    case 6:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printOperand(param_1,4,param_2);
      return;
    case 7:
switchD_001d3f24_caseD_10:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printComplexRotationOp(param_1,3,param_2,0xb4,0x5a);
      return;
    case 8:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printCondCode(param_1,3,param_2);
      return;
    case 9:
      SStream_concat0(param_2,", ");
      break;
    case 10:
      goto switchD_001d7314_caseD_a;
    case 0xb:
switchD_001d3f24_caseD_12:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printComplexRotationOp(param_1,4,param_2,0x5a,0);
      return;
    case 0xc:
switchD_001d47b8_caseD_0:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printSVERegOp(param_1,3,param_2,0x68);
      return;
    case 0xd:
switchD_001d3f24_caseD_13:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printImmHex(param_1,3,param_2);
      return;
    case 0xe:
switchD_001d3f24_caseD_15:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printExactFPImm_constprop_0(param_1,param_2,1,2);
      return;
    case 0xf:
      printSVERegOp(param_1,4,param_2,100);
      break;
    case 0x10:
      printSVERegOp(param_1,4,param_2,0x73);
      break;
    case 0x11:
switchD_001d3f24_caseD_1e:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printExactFPImm_constprop_0(param_1,param_2,0,2);
      return;
    case 0x12:
switchD_001d1dac_caseD_2f:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printVectorIndex(param_1,3,param_2);
      return;
    case 0x13:
switchD_001d3f24_caseD_20:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printExactFPImm_constprop_0(param_1,param_2,1,3);
      return;
    case 0x14:
switchD_001d5990_caseD_50:
      printImmScale(param_1,3,param_2,8);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x15:
      printImmScale(param_1,3,param_2,0x10);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x16:
switchD_001d5990_caseD_5f:
      printImmScale(param_1,3,param_2,4);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x17:
      printImmScale(param_1,4,param_2,8);
      break;
    case 0x18:
      printImmScale(param_1,4,param_2,0x10);
      break;
    case 0x19:
      printImmScale(param_1,4,param_2);
      break;
    case 0x1a:
      printMemExtend_constprop_0(param_1,param_2,0x77,8);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x1b:
      printMemExtend_constprop_0(param_1,param_2,0x78,8);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x1c:
      printMemExtend_constprop_0(param_1,param_2,0x77,0x40);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x1d:
      printMemExtend_constprop_0(param_1,param_2,0x78,0x40);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x1e:
      printMemExtend_constprop_0(param_1,param_2,0x77,0x10);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x1f:
      printMemExtend_constprop_0(param_1,param_2,0x78,0x10);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x20:
      printMemExtend_constprop_0(param_1,param_2,0x77,0x80);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x21:
      printMemExtend_constprop_0(param_1,param_2,0x78,0x80);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x22:
      printMemExtend_constprop_0(param_1,param_2,0x77,0x20);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    case 0x23:
      printMemExtend_constprop_0(param_1,param_2,0x78,0x20);
      SStream_concat0(param_2,&DAT_001fe5b8);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    default:
      goto switchD_001d47b8_caseD_18;
    }
    uVar33 = uVar33 >> 0x1d;
    if (uVar33 == 4) {
LAB_001d830c:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printComplexRotationOp(param_1,4,param_2,0xb4,0x5a);
      return;
    }
    if (uVar33 < 5) {
      if (uVar33 != 2) {
        if (uVar33 != 3) {
          if (uVar33 == 1) {
switchD_001d5990_caseD_2:
            SStream_concat0(param_2,&DAT_001ffda8);
            if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
              __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                               local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            }
            arm64_op_addVectorArrSpecifier(param_1,1);
            return;
          }
          goto switchD_001d014c_default;
        }
        SStream_concat0(param_2,", ");
        MCInst_getOpcode(param_1);
        iVar15 = MCInst_getOpcode(param_1);
        if ((0xc < iVar15 - 0x77aU) || ((0x1505UL >> ((ulong)(iVar15 - 0x77aU) & 0x3f) & 1) == 0))
        goto LAB_001d830c;
      }
switchD_001d7314_caseD_a:
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      printComplexRotationOp(param_1,5,param_2,0x5a,0);
      return;
    }
    if (uVar33 == 5) {
switchD_001d3f24_caseD_24:
      SStream_concat0(param_2,&DAT_001fb460);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access(param_1,0);
      return;
    }
    if (uVar33 == 6) {
switchD_001d5990_caseD_7:
      SStream_concat0(param_2,&DAT_001ffdc0);
      if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier(param_1,9);
      return;
    }
  }
switchD_001d014c_default:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
switchD_001d03a4_caseD_12:
  MCInst_getOperand(param_1,2);
  uVar17 = MCOperand_getImm();
  puVar19 = (undefined8 *)lookupSVEPREDPATByEncoding();
  if (puVar19 == (undefined8 *)0x0) {
    printUInt32Bang(param_2,uVar17);
  }
  else {
    SStream_concat0(param_2,*puVar19);
  }
  SStream_concat0(param_2,", mul ");
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  printOperand(param_1,3,param_2);
  return;
}

