
void printVectorList(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined4 param_6)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  int iVar12;
  
  MCInst_getOperand();
  iVar3 = MCOperand_getReg();
  SStream_concat0(param_3,&DAT_001f74a0);
  uVar8 = MCRegisterInfo_getRegClass(param_5,0x21);
  uVar9 = MCRegisterClass_contains(uVar8,iVar3);
  if ((uVar9 & 1) == 0) {
    uVar8 = MCRegisterInfo_getRegClass(param_5,0x49);
    uVar9 = MCRegisterClass_contains(uVar8,iVar3);
    if ((uVar9 & 1) == 0) {
      uVar8 = MCRegisterInfo_getRegClass(param_5,0x48);
      uVar9 = MCRegisterClass_contains(uVar8,iVar3);
      if ((uVar9 & 1) == 0) {
        uVar8 = MCRegisterInfo_getRegClass(param_5,0x36);
        uVar9 = MCRegisterClass_contains(uVar8,iVar3);
        if ((uVar9 & 1) == 0) {
          uVar8 = MCRegisterInfo_getRegClass(param_5,0x55);
          uVar9 = MCRegisterClass_contains(uVar8,iVar3);
          if ((uVar9 & 1) == 0) {
            uVar8 = MCRegisterInfo_getRegClass(param_5,0x54);
            uVar9 = MCRegisterClass_contains(uVar8,iVar3);
            if ((uVar9 & 1) == 0) {
              uVar8 = MCRegisterInfo_getRegClass(param_5,0x3d);
              uVar9 = MCRegisterClass_contains(uVar8,iVar3);
              if ((uVar9 & 1) == 0) {
                uVar8 = MCRegisterInfo_getRegClass(param_5,0x69);
                uVar9 = MCRegisterClass_contains(uVar8,iVar3);
                if ((uVar9 & 1) == 0) {
                  uVar8 = MCRegisterInfo_getRegClass(param_5,0x68);
                  uVar9 = MCRegisterClass_contains(uVar8,iVar3);
                  if ((uVar9 & 1) == 0) {
                    iVar12 = 1;
                    goto LAB_001c94dc;
                  }
                }
              }
              iVar12 = 4;
              goto LAB_001c94dc;
            }
          }
        }
        iVar12 = 3;
        goto LAB_001c94dc;
      }
    }
  }
  iVar12 = 2;
LAB_001c94dc:
  iVar4 = MCRegisterInfo_getSubReg(param_5,iVar3,3);
  if (((iVar4 == 0) && (iVar4 = MCRegisterInfo_getSubReg(param_5,iVar3,8), iVar4 == 0)) &&
     (iVar4 = MCRegisterInfo_getSubReg(param_5,iVar3,0x24), iVar4 == 0)) {
    iVar4 = iVar3;
  }
  uVar8 = MCRegisterInfo_getRegClass(param_5,0x14);
  uVar9 = MCRegisterClass_contains(uVar8,iVar4);
  if ((uVar9 & 1) != 0) {
    uVar8 = MCRegisterInfo_getRegClass(param_5,0x30);
    iVar4 = MCRegisterInfo_getMatchingSuperReg(param_5,iVar4,2,uVar8);
  }
  iVar3 = 0;
  do {
    uVar8 = MCRegisterInfo_getRegClass(param_5,0x31);
    uVar5 = MCRegisterClass_contains(uVar8,iVar4);
    if ((uVar5 & 1) == 0) {
      SStream_concat(param_3,&DAT_001fb430,AsmStrsvreg_7 + (byte)RegAsmOffsetvreg_8[iVar4 - 1U],
                     param_4);
      lVar10 = *(long *)(param_1 + 800);
      if (*(int *)(lVar10 + 0x60) != 0) goto LAB_001c9624;
LAB_001c9578:
      if (iVar3 + 1 != iVar12) goto LAB_001c9584;
LAB_001c96c0:
      if ((iVar4 - 0x7bU < 0x1f) || (iVar4 == 0x9a)) break;
LAB_001c95a8:
      if (iVar4 - 0xf7U < 0x1f) {
LAB_001c95f0:
        iVar4 = iVar4 + 1;
      }
      else if (iVar4 == 0x116) {
        iVar4 = 0xf7;
      }
    }
    else {
      SStream_concat(param_3,&DAT_001fb430,
                     &AsmStrsNoRegAltName_11 +
                     *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar4 - 1U) * 2),param_4);
      lVar10 = *(long *)(param_1 + 800);
      if (*(int *)(lVar10 + 0x60) == 0) goto LAB_001c9578;
LAB_001c9624:
      uVar6 = MCInst_getOpcode(param_1);
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar10 = AArch64_get_op_access(lVar10,uVar6);
      lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar2 = *(char *)(lVar10 + (ulong)bVar1);
      uVar9 = (ulong)*(byte *)(lVar11 + 0x67);
      if (cVar2 == -0x80) {
        cVar2 = '\0';
      }
      *(char *)(lVar11 + (uVar9 * 8 - (ulong)*(byte *)(lVar11 + 0x67)) * 8 + 0x98) = cVar2;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      iVar7 = iVar4;
      if ((uVar5 & 1) == 0) {
        iVar7 = AArch64_map_vregister(iVar4);
        lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        uVar9 = (ulong)*(byte *)(lVar11 + 0x67);
      }
      lVar10 = lVar11 + uVar9 * 0x38;
      *(undefined4 *)(lVar10 + 0x6c) = param_6;
      *(undefined4 *)(lVar10 + 0x7c) = 1;
      *(int *)(lVar10 + 0x88) = iVar7;
      *(char *)(lVar11 + 0x67) = (char)uVar9 + '\x01';
      if (iVar3 + 1 == iVar12) goto LAB_001c96c0;
LAB_001c9584:
      SStream_concat0(param_3,", ");
      if (iVar4 - 0x7bU < 0x1f) goto LAB_001c95f0;
      if (iVar4 != 0x9a) goto LAB_001c95a8;
      iVar4 = 0x7b;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != iVar12);
  SStream_concat0(param_3,&DAT_001f75a0);
  return;
}

