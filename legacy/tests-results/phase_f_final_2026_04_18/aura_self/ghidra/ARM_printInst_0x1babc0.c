
void ARM_printInst(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  long lVar16;
  ulong uVar17;
  undefined8 uVar18;
  ulong uVar19;
  byte *pbVar20;
  undefined1 auStack_418 [960];
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar7 = MCInst_getOpcode(param_1,0);
  if (uVar7 == 0x370) {
    MCInst_getOperand(param_1,2);
    iVar8 = MCOperand_getReg();
    if (iVar8 == 0xc) {
      MCInst_getOperand(param_1,3);
      lVar12 = MCOperand_getImm();
      if (lVar12 == -4) {
        SStream_concat0(param_2,&DAT_001f8f68);
        MCInst_setOpcodePub(param_1,0x80);
        printPredicateOperand(param_1,4,param_2);
        SStream_concat0(param_2,&DAT_001fd588);
        lVar12 = *(long *)(param_1 + 800);
        MCInst_getOperand(param_1,1);
        MCOperand_getReg();
        uVar18 = (**(code **)(lVar12 + 0x78))();
        SStream_concat0(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          MCInst_getOperand(param_1);
          uVar11 = MCOperand_getReg();
          uVar18 = *(undefined8 *)(param_1 + 800);
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x98) = uVar11;
          uVar11 = MCInst_getOpcode(param_1);
          bVar2 = *(byte *)(param_1 + 0x366);
          lVar12 = ARM_get_op_access(uVar18,uVar11);
          if (lVar12 == 0) {
            cVar6 = '\0';
          }
          else {
            cVar6 = *(char *)(lVar12 + (ulong)bVar2);
            if (cVar6 == -0x80) {
              cVar6 = '\0';
            }
          }
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar12 + 0x80);
          *(char *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0xb1) = cVar6;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(char *)(lVar12 + 0x80) = cVar3 + '\x01';
        }
LAB_001bb89c:
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          SStream_concat0(param_2,&DAT_001f8580,0);
          return;
        }
        goto LAB_001bc894;
      }
    }
    goto LAB_001bad40;
  }
  if (0x370 < uVar7) {
    if (uVar7 == 0xa49) {
LAB_001bb7a4:
      MCInst_getOperand(param_1,0);
      iVar8 = MCOperand_getReg();
      if (iVar8 != 0xc) goto LAB_001bad40;
      SStream_concat0(param_2,"vpush");
      uVar18 = 0x18b;
LAB_001bb7d0:
      MCInst_setOpcodePub(param_1,uVar18);
      printPredicateOperand(param_1,2,param_2);
      SStream_concat0(param_2,&DAT_001fd1a8);
LAB_001bacd8:
      lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
      if (lVar12 == 0) {
        uVar18 = 4;
LAB_001bb1e8:
        printRegisterList(param_1,uVar18,param_2);
        return;
      }
      goto LAB_001bc894;
    }
    if (uVar7 < 0xa4a) {
      if (uVar7 == 0x696) {
LAB_001bb0b4:
        MCInst_getOperand(param_1,0);
        iVar8 = MCOperand_getReg();
        if (iVar8 == 0xc) {
          SStream_concat0(param_2,&DAT_001fd598);
          uVar18 = 0x18a;
          goto LAB_001bb7d0;
        }
      }
      else if (uVar7 < 0x697) {
        if (uVar7 == 0x387) goto LAB_001baf64;
        if (uVar7 == 0x692) goto LAB_001bb0b4;
      }
      else if (uVar7 == 0xa45) goto LAB_001bb7a4;
    }
    else {
      if (uVar7 == 0xc0f) {
LAB_001baf64:
        SStream_concat0(param_2,"tsb\tcsync");
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          MCInst_setOpcodePub(param_1,0x10b,0);
          return;
        }
        goto LAB_001bc894;
      }
      if (uVar7 < 0xc10) {
        if (uVar7 == 0xb17) {
LAB_001bb58c:
          MCInst_getOperand(param_1,0);
          iVar8 = MCOperand_getReg();
          if ((iVar8 == 0xc) && (uVar9 = MCInst_getNumOperands(param_1), 5 < uVar9)) {
            SStream_concat0(param_2,&DAT_001f8f70);
            MCInst_setOpcodePub(param_1,0x7f);
            printPredicateOperand(param_1,2,param_2);
            if (uVar7 == 0xb17) {
              SStream_concat0(param_2,&DAT_001fd4d8);
            }
            SStream_concat0(param_2,&DAT_001fd1a8);
            *(undefined1 *)(param_1 + 0x366) = 1;
            iVar8 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001baca4:
            if (iVar8 != 0) {
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              bVar2 = *(byte *)(lVar12 + 0x28);
              *(undefined2 *)(lVar12 + (ulong)bVar2 * 2) = 0xc;
              *(byte *)(lVar12 + 0x28) = bVar2 + 1;
              bVar2 = *(byte *)(lVar12 + 0x52);
              *(undefined2 *)(lVar12 + (ulong)bVar2 * 2 + 0x2a) = 0xc;
              *(byte *)(lVar12 + 0x52) = bVar2 + 1;
            }
            goto LAB_001bacd8;
          }
        }
        else if (uVar7 == 0xbe3) goto LAB_001bac30;
      }
      else if (uVar7 == 0xc5d) {
        uVar7 = 3;
        bVar5 = true;
        MCInst_getOperand(param_1,0);
        iVar8 = MCOperand_getReg();
        while (uVar9 = MCInst_getNumOperands(param_1), uVar7 < uVar9) {
          MCInst_getOperand(param_1,uVar7);
          uVar7 = uVar7 + 1;
          iVar10 = MCOperand_getReg();
          if (iVar10 == iVar8) {
            bVar5 = false;
          }
        }
        SStream_concat0(param_2,&DAT_001fd5a0);
        MCInst_setOpcodePub(param_1,0x4f);
        printPredicateOperand(param_1,1,param_2);
        SStream_concat0(param_2,&DAT_001fd1a8);
        uVar18 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(iVar8);
        SStream_concat0(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x94) = 1;
          *(int *)(lVar12 + 0x98) = iVar8;
          *(undefined1 *)(lVar12 + 0xb1) = 3;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        if (bVar5) {
          *(undefined1 *)(param_1 + 0x335) = 1;
          SStream_concat0(param_2,&DAT_001fc470);
        }
        SStream_concat0(param_2,", ");
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          uVar18 = 3;
          goto LAB_001bb1e8;
        }
        goto LAB_001bc88c;
      }
    }
    goto LAB_001bad40;
  }
  if (uVar7 != 0x2b0) {
    if (uVar7 < 0x2b1) {
      if (uVar7 == 0x28a) {
LAB_001bba18:
        uVar18 = MCRegisterInfo_getRegClass(param_3,2);
        MCInst_getOperand(param_1,0);
        uVar11 = MCOperand_getReg();
        uVar17 = MCRegisterClass_contains(uVar18,uVar11);
        if ((uVar17 & 1) != 0) {
          MCInst_Init(auStack_418);
          uVar9 = 0;
          MCInst_setOpcode(auStack_418,uVar7);
LAB_001bc66c:
          uVar18 = MCRegisterInfo_getRegClass(param_3,0x15);
          uVar11 = MCRegisterInfo_getMatchingSuperReg(param_3,uVar11,9,uVar18);
          MCOperand_CreateReg0(auStack_418,uVar11);
          for (uVar9 = uVar9 + 2; uVar7 = MCInst_getNumOperands(param_1), uVar9 < uVar7;
              uVar9 = uVar9 + 1) {
            uVar18 = MCInst_getOperand(param_1,uVar9);
            MCInst_addOperand2(auStack_418,uVar18);
          }
          printInstruction(auStack_418,param_2);
          goto LAB_001baf2c;
        }
      }
      else if (uVar7 < 0x28b) {
        if (uVar7 == 0x262) goto LAB_001bba18;
        if (uVar7 == 0x27a) goto LAB_001bb58c;
      }
      else if (uVar7 == 0x29d) {
        MCInst_getOperand(param_1,2);
        iVar8 = MCOperand_getReg();
        if (iVar8 == 0xc) {
          MCInst_getOperand(param_1,4);
          uVar7 = MCOperand_getImm();
          if ((uVar7 & 0xfff) == 4) {
            SStream_concat0(param_2,&DAT_001f8f70);
            MCInst_setOpcodePub(param_1,0x7f);
            printPredicateOperand(param_1,5,param_2);
            SStream_concat0(param_2,&DAT_001fd588);
            lVar12 = *(long *)(param_1 + 800);
            MCInst_getOperand(param_1,0);
            MCOperand_getReg();
            uVar18 = (**(code **)(lVar12 + 0x78))();
            SStream_concat0(param_2,uVar18);
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
              MCInst_getOperand(param_1,0);
              uVar11 = MCOperand_getReg();
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              cVar6 = *(char *)(lVar12 + 0x80);
              lVar16 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
              *(undefined4 *)(lVar16 + 0x98) = uVar11;
              *(undefined1 *)(lVar16 + 0xb1) = 2;
              *(char *)(lVar12 + 0x80) = cVar6 + '\x01';
              cVar6 = *(char *)(lVar12 + 0x28);
              *(undefined2 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x28) * 2) = 0xc;
              *(char *)(lVar12 + 0x28) = cVar6 + '\x01';
              cVar6 = *(char *)(lVar12 + 0x52);
              *(undefined2 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x52) * 2 + 0x2a) = 0xc;
              *(char *)(lVar12 + 0x52) = cVar6 + '\x01';
            }
            goto LAB_001bb89c;
          }
        }
      }
    }
    else if (uVar7 == 0x34d) {
LAB_001bb8e8:
      uVar18 = MCRegisterInfo_getRegClass(param_3,2);
      bVar5 = uVar7 == 0x365 || uVar7 == 0x34d;
      uVar9 = (uint)bVar5;
      MCInst_getOperand(param_1,bVar5);
      uVar11 = MCOperand_getReg();
      uVar17 = MCRegisterClass_contains(uVar18,uVar11);
      if ((uVar17 & 1) != 0) {
        MCInst_Init(auStack_418);
        MCInst_setOpcode(auStack_418,uVar7);
        uVar18 = MCInst_getOperand(param_1,0);
        MCInst_addOperand2(auStack_418,uVar18);
        goto LAB_001bc66c;
      }
    }
    else if (uVar7 < 0x34e) {
      if (uVar7 == 0x2b1) {
        uVar18 = MCInst_getOperand(param_1,0);
        uVar13 = MCInst_getOperand(param_1,1);
        uVar14 = MCInst_getOperand(param_1,2);
        MCInst_getOperand(param_1,3);
        uVar9 = MCOperand_getImm();
        uVar7 = uVar9 & 7;
        if (uVar7 == 3) {
          SStream_concat0(param_2,&DAT_001f9680);
          MCInst_setOpcodePub(param_1,99);
        }
        else if ((uVar9 >> 2 & 1) == 0) {
          if (uVar7 == 1) {
            SStream_concat0(param_2,&DAT_001f9688);
            MCInst_setOpcodePub(param_1,10);
          }
          else {
            if (uVar7 != 2) goto LAB_001bc564;
            SStream_concat0(param_2,&DAT_001f9678);
            MCInst_setOpcodePub(param_1,0x62);
          }
        }
        else if (uVar7 == 4) {
          SStream_concat0(param_2,"ror");
          MCInst_setOpcodePub(param_1,0x93);
        }
        else if (uVar7 == 5) {
          SStream_concat0(param_2,&DAT_001fcdd0);
          MCInst_setOpcodePub(param_1,0x94);
        }
        else {
LAB_001bc564:
          SStream_concat0(param_2,&DAT_001fd4a8);
        }
        MCInst_getOperand(param_1,6);
        iVar8 = MCOperand_getReg();
        if ((iVar8 != 0) &&
           (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
          *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
        }
        printPredicateOperand(param_1,4,param_2);
        SStream_concat0(param_2,&DAT_001fd1a8);
        lVar12 = *(long *)(param_1 + 800);
        MCOperand_getReg(uVar18);
        uVar15 = (**(code **)(lVar12 + 0x78))();
        SStream_concat0(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = MCOperand_getReg(uVar18);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 2;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        SStream_concat0(param_2,", ");
        lVar12 = *(long *)(param_1 + 800);
        MCOperand_getReg(uVar13);
        uVar18 = (**(code **)(lVar12 + 0x78))();
        SStream_concat0(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = MCOperand_getReg(uVar13);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 1;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        SStream_concat0(param_2,", ");
        lVar12 = *(long *)(param_1 + 800);
        MCOperand_getReg(uVar14);
        uVar18 = (**(code **)(lVar12 + 0x78))();
        SStream_concat0(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = MCOperand_getReg(uVar14);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 1;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        goto LAB_001baf2c;
      }
    }
    else if (uVar7 == 0x353) {
LAB_001bac30:
      MCInst_getOperand(param_1,0);
      iVar8 = MCOperand_getReg();
      if ((iVar8 == 0xc) && (uVar9 = MCInst_getNumOperands(param_1), 5 < uVar9)) {
        SStream_concat0(param_2,&DAT_001f8f68);
        MCInst_setOpcodePub(param_1,0x80);
        printPredicateOperand(param_1,2,param_2);
        if (uVar7 == 0xbe3) {
          SStream_concat0(param_2,&DAT_001fd4d8);
        }
        SStream_concat0(param_2,&DAT_001fd1a8);
        iVar8 = *(int *)(*(long *)(param_1 + 800) + 0x60);
        goto joined_r0x001baca4;
      }
    }
    else if (uVar7 == 0x365) goto LAB_001bb8e8;
LAB_001bad40:
    *(undefined8 *)(param_1 + 0x3b0) = param_3;
    uVar7 = MCInst_getOpcode(param_1);
    if (uVar7 == 0xaf7) {
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 0) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd520;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 1) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd510;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 2) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd500;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 3) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd4f0;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 4) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd4e0;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 5) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
              (uVar17 & 1) != 0)))) {
            pbVar20 = &DAT_001fd4d0;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if ((((lVar12 == 0x10) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
               (uVar17 & 1) != 0)) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x4f),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd4c0;
            goto LAB_001bb2e4;
          }
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if ((lVar12 == 0x14) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
             (uVar17 & 1) != 0)) {
            uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b);
joined_r0x001bb564:
            if ((uVar17 & 1) != 0) {
              pbVar20 = &DAT_001fd4a0;
              goto LAB_001bb2e4;
            }
          }
        }
      }
    }
    else if (uVar7 < 0xaf8) {
      if (uVar7 == 0x25a) {
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 0) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bbab0:
              pbVar20 = &DAT_001fd578;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 1) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bbbd0:
              pbVar20 = &DAT_001fd568;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 2) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bbcf8:
              pbVar20 = &DAT_001fd560;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 3) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bbe20:
              pbVar20 = &DAT_001fd558;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 4) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bbf48:
              pbVar20 = &DAT_001fd550;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 5) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
               (uVar17 & 1) != 0)) {
LAB_001bb084:
              pbVar20 = &DAT_001fd540;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if (((lVar12 == 0x10) &&
                (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x4f),
               (uVar17 & 1) != 0)) {
              pbVar20 = &DAT_001fd538;
              goto LAB_001bb2e4;
            }
          }
        }
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if ((lVar12 == 0x14) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
               (uVar17 & 1) == 0)) {
              uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a);
              goto joined_r0x001bb564;
            }
          }
        }
      }
      else if (uVar7 == 0xaf3) {
        iVar8 = MCInst_getNumOperands(param_1);
        if (iVar8 == 3) {
          MCInst_getOperand(param_1,0);
          uVar17 = MCOperand_isImm();
          if ((uVar17 & 1) != 0) {
            MCInst_getOperand(param_1,0);
            lVar12 = MCOperand_getImm();
            if ((lVar12 == 0xc) &&
               (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2b),
               (uVar17 & 1) != 0)) {
              pbVar20 = &DAT_001fd530;
              goto LAB_001bb2e4;
            }
          }
        }
      }
      else if ((uVar7 == 0x24a) && (iVar8 = MCInst_getNumOperands(param_1), iVar8 == 1)) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 0xc) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) == 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fd580;
LAB_001bb2e4:
            lVar16 = cs_strdup(pbVar20);
            uVar19 = (ulong)*pbVar20;
            uVar17 = 0;
            do {
              if ((int)uVar19 == 0x24) break;
              if ((int)uVar19 == 0) {
                *(undefined1 *)(lVar16 + uVar17) = 0;
                SStream_concat0(param_2,lVar16);
                lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
                if (lVar12 == 0) {
                  (**(code **)PTR_cs_mem_free_005fff60)(lVar16,*(code **)PTR_cs_mem_free_005fff60,0)
                  ;
                  return;
                }
                goto LAB_001bc88c;
              }
              uVar17 = (ulong)((int)uVar17 + 1);
              bVar2 = pbVar20[uVar17];
              uVar19 = (ulong)bVar2;
            } while (bVar2 != 0x20 && bVar2 != 9);
            *(undefined1 *)(lVar16 + uVar17) = 0;
            SStream_concat0(param_2,lVar16);
            (**(code **)PTR_cs_mem_free_005fff60)(lVar16);
            if ((0x100000200U >> (uVar19 & 0x3f) & 1) != 0) {
              uVar17 = (ulong)((int)uVar17 + 1);
              SStream_concat0(param_2,&DAT_001fd3c8);
            }
            bVar2 = pbVar20[uVar17];
            do {
              iVar8 = (int)uVar17;
              uVar17 = (ulong)(iVar8 + 1);
              if (bVar2 == 0x24) {
                pbVar1 = pbVar20 + uVar17;
                if (*pbVar1 == 0xff) {
                  if (pbVar20[iVar8 + 3] == 1) {
                    uVar17 = (ulong)(iVar8 + 4);
                    printPredicateOperand(param_1,pbVar20[iVar8 + 2U] - 1,param_2);
                  }
                  else {
                    uVar17 = (ulong)(iVar8 + 4);
                  }
                }
                else {
                  uVar17 = (ulong)(iVar8 + 2U);
                  printOperand(param_1,*pbVar1 - 1,param_2);
                }
              }
              else {
                if (bVar2 == 0x5b) {
                  set_mem_access(param_1,1);
                }
                else if ((bVar2 == 0x5d) && (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3)) {
                  lVar12 = *(long *)(param_1 + 0x310);
                  *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
                  lVar12 = *(long *)(lVar12 + 0xf0);
                  *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
                }
                SStream_concat1(param_2,bVar2);
              }
              bVar2 = pbVar20[uVar17];
            } while (bVar2 != 0);
            goto LAB_001baf2c;
          }
        }
      }
    }
    else if (uVar7 == 0xbff) {
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 0) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x65),
              (uVar17 & 1) != 0)))) {
            pbVar20 = &DAT_001fd4b0;
            goto LAB_001bb2e4;
          }
        }
      }
    }
    else if (uVar7 == 0xc58) {
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 0) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bbab0;
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 1) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bbbd0;
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 2) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bbcf8;
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 3) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bbe20;
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 4) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bbf48;
        }
      }
      iVar8 = MCInst_getNumOperands(param_1);
      if (iVar8 == 3) {
        MCInst_getOperand(param_1,0);
        uVar17 = MCOperand_isImm();
        if ((uVar17 & 1) != 0) {
          MCInst_getOperand(param_1,0);
          lVar12 = MCOperand_getImm();
          if (((lVar12 == 5) &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
              (uVar17 & 1) != 0)))) goto LAB_001bb084;
        }
      }
    }
    lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar12 == 0) {
      printInstruction(param_1,param_2,0);
      return;
    }
LAB_001bc894:
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar12);
  }
  uVar18 = MCInst_getOperand(param_1,0);
  uVar13 = MCInst_getOperand(param_1,1);
  uVar14 = MCInst_getOperand(param_1,2);
  uVar9 = MCOperand_getImm();
  uVar7 = uVar9 & 7;
  if (uVar7 == 3) {
    SStream_concat0(param_2,&DAT_001f9680);
    MCInst_setOpcodePub(param_1,99);
  }
  else if ((uVar9 >> 2 & 1) == 0) {
    if (uVar7 == 1) {
      SStream_concat0(param_2,&DAT_001f9688);
      MCInst_setOpcodePub(param_1,10);
    }
    else {
      if (uVar7 != 2) goto LAB_001bc5b8;
      SStream_concat0(param_2,&DAT_001f9678);
      MCInst_setOpcodePub(param_1,0x62);
    }
  }
  else if (uVar7 == 4) {
    SStream_concat0(param_2,"ror");
    MCInst_setOpcodePub(param_1,0x93);
  }
  else if (uVar7 == 5) {
    SStream_concat0(param_2,&DAT_001fcdd0);
    MCInst_setOpcodePub(param_1,0x94);
  }
  else {
LAB_001bc5b8:
    SStream_concat0(param_2,&DAT_001fd4a8);
  }
  MCInst_getOperand(param_1,5);
  iVar8 = MCOperand_getReg();
  if ((iVar8 != 0) && (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)
     ) {
    *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
  }
  printPredicateOperand(param_1,3,param_2);
  SStream_concat0(param_2,&DAT_001fd1a8);
  lVar12 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar18);
  uVar15 = (**(code **)(lVar12 + 0x78))();
  SStream_concat0(param_2,uVar15);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
    uVar11 = MCOperand_getReg(uVar18);
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar16 + 0x80);
    lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar12 + 0x98) = uVar11;
    *(undefined1 *)(lVar12 + 0xb1) = 2;
    *(byte *)(lVar16 + 0x80) = bVar2 + 1;
  }
  SStream_concat0(param_2,", ");
  lVar12 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar13);
  uVar18 = (**(code **)(lVar12 + 0x78))();
  SStream_concat0(param_2,uVar18);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
    uVar11 = MCOperand_getReg(uVar13);
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar16 + 0x80);
    lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar12 + 0x98) = uVar11;
    *(undefined1 *)(lVar12 + 0xb1) = 1;
    *(byte *)(lVar16 + 0x80) = bVar2 + 1;
  }
  if (uVar7 != 5) {
    SStream_concat0(param_2,", ");
    uVar17 = MCOperand_getImm(uVar14);
    uVar9 = (uint)(uVar17 >> 3) & 0x1fffffff;
    if ((uVar17 >> 3 & 0x1fffffff) == 0) {
      uVar9 = 0x20;
    }
    printUInt32Bang(param_2,uVar9);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar4 = *(byte *)(lVar12 + 0x80) - 1;
      lVar12 = lVar12 + ((-(ulong)(uVar4 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar4 << 1) +
                        (long)(int)uVar4) * 0x10;
      *(uint *)(lVar12 + 0x8c) = uVar7;
      *(uint *)(lVar12 + 0x90) = uVar9;
    }
  }
LAB_001baf2c:
  lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
  if (lVar12 == 0) {
    return;
  }
LAB_001bc88c:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar12);
}

