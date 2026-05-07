
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void X86_ATT_printInst(long param_1,char *param_2)

{
  uint uVar1;
  char cVar2;
  uint6 uVar3;
  char *pcVar4;
  undefined1 uVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  char *pcVar15;
  uint uVar16;
  undefined1 uVar17;
  long lVar18;
  char *pcVar19;
  uint uVar20;
  long lVar21;
  byte bVar23;
  byte bVar24;
  byte bVar25;
  byte bVar26;
  byte bVar27;
  undefined1 auVar22 [16];
  uint local_60;
  uint uStack_5c;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined8 local_50;
  undefined8 uStack_48;
  
  uStack_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (*(char *)(param_1 + 0x368) != '\0') {
    lVar13 = uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar13 == 0) {
      strncpy(param_2,(char *)(param_1 + 0x368),0x200);
      return;
    }
    goto LAB_00193c3c;
  }
  if ((*(int *)(*(long *)(param_1 + 800) + 4) == 8) &&
     (iVar8 = MCInst_getOpcode(param_1,8,0), iVar8 == 0x1ee)) {
    SStream_concat0(param_2,"callq\t");
    MCInst_setOpcodePub(param_1,0x3e);
    lVar13 = uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar13 == 0) {
      printPCRelImm_constprop_0(param_1,param_2,0);
      return;
    }
    goto LAB_00193c3c;
  }
  X86_lockrep(param_1,param_2);
  uVar11 = MCInst_getOpcode(param_1);
  uVar11 = uVar11 & 0xffffffff;
  bVar6 = OpInfo2_3[uVar11];
  uVar12 = (ulong)*(ushort *)(OpInfo1_4 + uVar11 * 2) << 0x20;
  uVar3 = CONCAT24(*(ushort *)(OpInfo1_4 + uVar11 * 2),*(uint *)(OpInfo0_5 + uVar11 * 4));
  SStream_concat0(param_2,(*(uint *)(OpInfo0_5 + uVar11 * 4) & 0x3fff) + 0x20b88f);
  uVar11 = ((ulong)(uVar3 >> 0xe) & 0x7f) - 1;
  if (0x65 < uVar11) goto switchD_001919dc_default;
  switch(uVar11 & 0xffffffff) {
  case 0:
    printOperand(param_1,0,param_2);
    break;
  case 1:
    uVar14 = 5;
    goto LAB_00192d18;
  case 2:
    uVar14 = 2;
    goto LAB_00192d18;
  case 3:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 2;
    goto LAB_00192178;
  case 4:
    uVar5 = 4;
    goto LAB_00192124;
  case 5:
  case 8:
    uVar5 = 8;
LAB_00192124:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192128:
    printMemReference(param_1,2,param_2);
    break;
  case 6:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 1;
    goto LAB_00192178;
  case 7:
  case 0xe:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    goto LAB_00192178;
  case 9:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192124;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192128;
  case 10:
    goto switchD_001919dc_caseD_a;
  case 0xb:
  case 0x1a:
    goto switchD_001919dc_caseD_b;
  case 0xc:
    goto switchD_001919dc_caseD_c;
  case 0xd:
    goto switchD_001919dc_caseD_d;
  case 0xf:
  case 0x27:
    goto switchD_001919dc_caseD_f;
  case 0x10:
    printOperand(param_1,1,param_2);
    break;
  case 0x11:
    uVar14 = 6;
    goto LAB_00192c54;
  case 0x12:
    uVar14 = 2;
    goto LAB_00192bc4;
  case 0x13:
    uVar14 = 6;
    goto LAB_00192d18;
  case 0x14:
    uVar5 = 4;
    goto LAB_001921ac;
  case 0x15:
  case 0x25:
    uVar5 = 8;
    goto LAB_001921ac;
  case 0x16:
    uVar14 = 7;
    goto LAB_00192c54;
  case 0x17:
    uVar14 = 3;
    goto LAB_00192bc4;
  case 0x18:
    uVar9 = *(uint *)(param_1 + 8);
    if (uVar9 < 0x4e2) {
      if (uVar9 < 0x4e0) {
        if (uVar9 < 0x19b) {
          if ((0x184 < uVar9) && ((0x201555UL >> ((ulong)(uVar9 - 0x185) & 0x3f) & 1) != 0))
          goto switchD_001919dc_caseD_f;
        }
        else if (uVar9 == 0x4df) {
          *(undefined1 *)(param_1 + 0x328) = 2;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x328) = 4;
      }
    }
    else if (uVar9 == 0x4e2) {
      *(undefined1 *)(param_1 + 0x328) = 8;
    }
    goto LAB_001920e4;
  case 0x19:
    goto switchD_001919dc_caseD_19;
  case 0x1b:
    printPCRelImm_constprop_0(param_1,param_2);
    goto switchD_001919dc_default;
  case 0x1c:
    goto switchD_001919dc_caseD_1c;
  case 0x1d:
    uVar5 = 1;
    goto LAB_001920e0;
  case 0x1e:
    printSSEAVXCC(param_1,7,param_2);
    break;
  case 0x1f:
    printSSEAVXCC(param_1,3,param_2);
    break;
  case 0x20:
    *(undefined1 *)(param_1 + 0x328) = 1;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x21:
    *(undefined1 *)(param_1 + 0x328) = 4;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x22:
    *(undefined1 *)(param_1 + 0x328) = 8;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x23:
    *(undefined1 *)(param_1 + 0x328) = 2;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x24:
    uVar5 = 0x10;
    goto LAB_00192084;
  case 0x26:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_001921ac;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_001921b0;
  case 0x28:
    printopaquemem(param_1,0,param_2);
    goto switchD_001919dc_default;
  case 0x29:
    uVar5 = 10;
    goto LAB_00192084;
  case 0x2a:
    uVar14 = 0;
    goto LAB_00192bc4;
  case 0x2b:
    uVar14 = 4;
    goto LAB_00192bc4;
  case 0x2c:
    printopaquemem(param_1,1,param_2);
    pcVar15 = ", ";
    goto LAB_00192100;
  case 0x2d:
    uVar5 = 1;
    goto LAB_001931f8;
  case 0x2e:
    uVar5 = 4;
    goto LAB_001931f8;
  case 0x2f:
    *(undefined1 *)(param_1 + 0x328) = 8;
    printSrcIdx(param_1,0,param_2);
    goto LAB_00193238;
  case 0x30:
    uVar5 = 2;
LAB_001931f8:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printSrcIdx(param_1,0,param_2);
    break;
  case 0x31:
    *(undefined1 *)(param_1 + 0x328) = 2;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x32:
    *(undefined1 *)(param_1 + 0x328) = 4;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x33:
    *(undefined1 *)(param_1 + 0x328) = 8;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x34:
    *(undefined1 *)(param_1 + 0x328) = 1;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x35:
    uVar5 = 0x40;
    goto LAB_001921ac;
  case 0x36:
    uVar5 = 1;
    goto LAB_00192df4;
  case 0x37:
    uVar5 = 4;
    goto LAB_00192df4;
  case 0x38:
    uVar5 = 8;
    goto LAB_00192df4;
  case 0x39:
    uVar5 = 2;
LAB_00192df4:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printSrcIdx(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printDstIdx_constprop_0(param_1,param_2);
    goto switchD_001919dc_default;
  case 0x3a:
    uVar14 = 5;
LAB_00192bc4:
    MCInst_getOperand(param_1,uVar14);
    bVar7 = MCOperand_getImm();
    if (bVar7 < 10) {
      SStream_concat(param_2,&DAT_001fc238);
    }
    else {
      SStream_concat(param_2,"$0x%x");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar23 = *(byte *)(lVar18 + 0xa0);
      lVar13 = lVar18 + ((ulong)bVar23 * 2 + (ulong)bVar23) * 0x10;
      *(undefined4 *)(lVar13 + 0xa8) = 2;
      *(ulong *)(lVar13 + 0xb0) = (ulong)bVar7;
      *(undefined1 *)(lVar13 + 200) = 1;
      *(byte *)(lVar18 + 0xa0) = bVar23 + 1;
    }
    break;
  case 0x3b:
  case 0x53:
    uVar14 = 3;
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    goto LAB_00192178;
  case 0x3c:
    uVar5 = 0x10;
    goto LAB_00192e3c;
  case 0x3d:
  case 0x4c:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 0x20;
    goto LAB_00192178;
  case 0x3e:
  case 0x60:
    uVar5 = 8;
    goto LAB_00192204;
  case 0x3f:
  case 0x52:
    uVar5 = 8;
    goto LAB_00192220;
  case 0x40:
    printOperand(param_1,4,param_2);
    goto LAB_00192e50;
  case 0x41:
    uVar14 = 3;
    goto LAB_00192d18;
  case 0x42:
    uVar5 = 0x20;
    goto LAB_00192e3c;
  case 0x43:
  case 0x55:
    uVar14 = 3;
    *(undefined1 *)(param_1 + 0x328) = 0x20;
    goto LAB_00192178;
  case 0x44:
  case 0x4d:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 0x40;
    goto LAB_00192178;
  case 0x45:
    uVar5 = 0x40;
LAB_00192e3c:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,4,param_2);
LAB_00192e50:
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
LAB_00192e98:
    SStream_concat0(param_2,&DAT_001fc270);
    printOperand(param_1,2,param_2);
    break;
  case 0x46:
  case 0x59:
    uVar14 = 3;
    *(undefined1 *)(param_1 + 0x328) = 0x40;
    goto LAB_00192178;
  case 0x47:
    printRoundingControl(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    uVar14 = 2;
    goto LAB_00192dd8;
  case 0x48:
    printRoundingControl(param_1,5,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    goto LAB_00192e98;
  case 0x49:
    printRoundingControl(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    uVar14 = 3;
LAB_00192dd8:
    printOperand(param_1,uVar14,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x4a:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192204;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192208;
  case 0x4b:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192220;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192224;
  case 0x4e:
    uVar14 = 9;
    goto LAB_00192c54;
  case 0x4f:
    uVar14 = 8;
LAB_00192c54:
    MCInst_getOperand(param_1,uVar14);
    bVar7 = MCOperand_getImm();
    if (bVar7 < 10) {
      SStream_concat(param_2,&DAT_001fc238);
    }
    else {
      SStream_concat(param_2,"$0x%x");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar23 = *(byte *)(lVar18 + 0xa0);
      lVar13 = lVar18 + ((ulong)bVar23 * 2 + (ulong)bVar23) * 0x10;
      *(undefined4 *)(lVar13 + 0xa8) = 2;
      *(ulong *)(lVar13 + 0xb0) = (ulong)bVar7;
      *(undefined1 *)(lVar13 + 200) = 1;
      *(byte *)(lVar18 + 0xa0) = bVar23 + 1;
    }
    SStream_concat0(param_2,", ");
    break;
  case 0x50:
    uVar14 = 7;
    goto LAB_00192d18;
  case 0x51:
    goto switchD_001919dc_caseD_51;
  case 0x54:
    uVar5 = 0x20;
LAB_001921ac:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_001921b0:
    printMemReference(param_1,1,param_2);
    break;
  case 0x56:
    printSSEAVXCC(param_1,8,param_2);
    break;
  case 0x57:
    printSSEAVXCC(param_1,4,param_2);
    break;
  case 0x58:
    uVar5 = 4;
LAB_00192220:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192224:
    printMemReference(param_1,3,param_2);
    break;
  case 0x5a:
    printRoundingControl(param_1,2,param_2);
    goto LAB_00192394;
  case 0x5b:
    goto switchD_001919dc_caseD_5b;
  case 0x5c:
    uVar14 = 8;
LAB_00192d18:
    printOperand(param_1,uVar14,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x5d:
    uVar5 = 0x10;
    goto LAB_00192cec;
  case 0x5e:
    uVar5 = 0x20;
    goto LAB_00192cec;
  case 0x5f:
    uVar5 = 0x40;
LAB_00192cec:
    uVar14 = 4;
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192178:
    printMemReference(param_1,uVar14,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x61:
    uVar5 = 4;
LAB_00192204:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192208:
    printMemReference(param_1,4,param_2);
    break;
  case 0x62:
    uVar5 = 1;
    goto LAB_00192f08;
  case 99:
    uVar5 = 2;
LAB_00192f08:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fc270);
    uVar14 = 2;
    goto LAB_0019235c;
  case 100:
    printXOPCC(param_1,7,param_2);
    break;
  case 0x65:
    printXOPCC(param_1,3,param_2);
    break;
  default:
    goto switchD_001919dc_default;
  }
  uVar11 = ((ulong)(uVar3 >> 0x15) & 0x7f) - 1;
  if (0x61 < uVar11) goto switchD_001919dc_default;
  switch(uVar11 & 0xffffffff) {
  case 0:
    SStream_concat0(param_2,", %ax");
    op_addReg(param_1,3);
    goto switchD_001919dc_default;
  case 1:
    uVar5 = 2;
    goto LAB_00192250;
  case 2:
    printOperand(param_1,1,param_2);
    break;
  case 3:
    printOperand(param_1,0,param_2);
    break;
  case 4:
    SStream_concat0(param_2,", %eax");
    op_addReg(param_1,0x13);
    goto switchD_001919dc_default;
  case 5:
    uVar5 = 4;
    goto LAB_00192250;
  case 6:
    goto switchD_00192164_caseD_6;
  case 7:
LAB_00193238:
    SStream_concat0(param_2,", %rax");
    op_addReg(param_1,0x23);
    goto switchD_001919dc_default;
  case 8:
  case 0x1f:
    uVar5 = 8;
    goto LAB_00192250;
  case 9:
    SStream_concat0(param_2,", %al");
    op_addReg(param_1,2);
    goto switchD_001919dc_default;
  case 10:
    goto switchD_001919dc_caseD_1c;
  case 0xb:
    uVar5 = 0x10;
    goto LAB_00192740;
  case 0xc:
    uVar5 = 4;
    goto LAB_00192740;
  case 0xd:
  case 0x25:
    uVar5 = 8;
    goto LAB_00192740;
  case 0xe:
  case 0x1a:
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    printMemReference(param_1,2,param_2);
    goto switchD_00192164_caseD_6;
  case 0xf:
  case 0x1e:
    uVar5 = 0x10;
    goto LAB_00192250;
  case 0x10:
    uVar9 = *(uint *)(param_1 + 8);
    if (uVar9 < 0x4e2) {
      if (uVar9 < 0x4e0) {
        if (uVar9 < 0x19b) {
          if ((0x184 < uVar9) && ((0x201555UL >> ((ulong)(uVar9 - 0x185) & 0x3f) & 1) != 0)) {
            *(undefined1 *)(param_1 + 0x328) = 0x10;
          }
        }
        else if (uVar9 == 0x4df) {
          *(undefined1 *)(param_1 + 0x328) = 2;
        }
        goto LAB_00192088;
      }
      goto LAB_001927f4;
    }
    if (uVar9 == 0x4e2) {
      *(undefined1 *)(param_1 + 0x328) = 8;
    }
    goto LAB_00192088;
  case 0x11:
    SStream_concat0(param_2,", %st(0)");
    op_addReg(param_1,0x72);
    goto switchD_001919dc_default;
  case 0x12:
    SStream_concat0(param_2,&DAT_001fc2a0);
    break;
  case 0x13:
    SStream_concat0(param_2,&DAT_001fc2a8);
    break;
  case 0x14:
    SStream_concat0(param_2,&DAT_001fc2b0);
    break;
  case 0x15:
  case 0x1c:
    uVar5 = 8;
    goto LAB_00192700;
  case 0x16:
    SStream_concat0(param_2,&DAT_001fc2b8);
    break;
  case 0x17:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192700;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192704;
  case 0x18:
    uVar14 = 5;
    goto LAB_00193420;
  case 0x19:
    pcVar15 = ":";
    goto LAB_00192100;
  case 0x1b:
switchD_001919dc_caseD_19:
    uVar5 = 2;
    goto LAB_001920e0;
  case 0x1d:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 2;
    goto LAB_00192698;
  case 0x20:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192250;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192254;
  case 0x21:
    SStream_concat0(param_2,", %dx");
    op_addReg(param_1,0x12);
    goto switchD_001919dc_default;
  case 0x22:
    uVar5 = 1;
    goto LAB_00192700;
  case 0x23:
    uVar5 = 4;
LAB_00192700:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192704:
    printMemReference(param_1,2,param_2);
    break;
  case 0x24:
switchD_001919dc_caseD_f:
    uVar5 = 0x10;
    goto LAB_001920e0;
  case 0x26:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192744;
  case 0x27:
    printOperand(param_1,2,param_2);
    break;
  case 0x28:
    goto switchD_00192164_caseD_28;
  case 0x29:
    goto switchD_00192164_caseD_29;
  case 0x2a:
    SStream_concat0(param_2,"{1to2}, ");
    op_addAvxBroadcast(param_1,1);
    break;
  case 0x2b:
    SStream_concat0(param_2,"{1to4}, ");
    op_addAvxBroadcast(param_1,2);
    break;
  case 0x2c:
    SStream_concat0(param_2,"{1to8}, ");
    op_addAvxBroadcast(param_1,3);
    break;
  case 0x2d:
    SStream_concat0(param_2,"{1to16}, ");
    op_addAvxBroadcast(param_1,4);
    break;
  case 0x2e:
    uVar5 = 4;
    goto LAB_00192780;
  case 0x2f:
    uVar5 = 4;
    goto LAB_00192764;
  case 0x30:
  case 0x4b:
    uVar5 = 0x10;
    goto LAB_0019260c;
  case 0x31:
  case 0x3c:
    uVar5 = 0x10;
    goto LAB_001926b8;
  case 0x32:
  case 0x3a:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 0x20;
    goto LAB_00192698;
  case 0x33:
  case 0x4c:
    uVar5 = 0x20;
    goto LAB_0019260c;
  case 0x34:
  case 0x3d:
    uVar5 = 0x20;
    goto LAB_001926b8;
  case 0x35:
  case 0x3e:
    uVar14 = 2;
    *(undefined1 *)(param_1 + 0x328) = 0x40;
    goto LAB_00192698;
  case 0x36:
  case 0x4d:
    uVar5 = 0x40;
LAB_0019260c:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fc270);
    printOperand(param_1,2,param_2);
    break;
  case 0x37:
  case 0x3f:
    uVar5 = 0x40;
LAB_001926b8:
    uVar14 = 3;
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192698:
    printMemReference(param_1,uVar14,param_2);
switchD_00192164_caseD_6:
    SStream_concat0(param_2,", ");
    break;
  case 0x38:
  case 0x4a:
    uVar5 = 8;
    goto LAB_00192780;
  case 0x39:
  case 0x3b:
    uVar5 = 8;
    goto LAB_00192764;
  case 0x40:
    SStream_concat0(param_2,"pd\t{sae}, ");
    op_addAvxSae(param_1);
    break;
  case 0x41:
    SStream_concat0(param_2,", {sae}, ");
    op_addAvxSae(param_1);
    break;
  case 0x42:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192764;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192768;
  case 0x43:
    SStream_concat0(param_2,"ps\t{sae}, ");
    op_addAvxSae(param_1);
    break;
  case 0x44:
    SStream_concat0(param_2,"sd\t{sae}, ");
    op_addAvxSae(param_1);
    break;
  case 0x45:
    SStream_concat0(param_2,"ss\t{sae}, ");
    op_addAvxSae(param_1);
    break;
  case 0x46:
  case 0x55:
    uVar5 = 0x20;
    goto LAB_00192250;
  case 0x47:
  case 0x56:
    uVar5 = 0x40;
LAB_00192250:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192254:
    printMemReference(param_1,0,param_2);
    break;
  case 0x48:
    uVar14 = 6;
    goto LAB_00193420;
  case 0x49:
    printRoundingControl(param_1,3,param_2);
    goto LAB_00192394;
  case 0x4e:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192780;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192784;
  case 0x4f:
switchD_001919dc_caseD_51:
    uVar5 = 0x20;
    goto LAB_001920e0;
  case 0x50:
switchD_001919dc_caseD_5b:
    uVar5 = 0x40;
LAB_001920e0:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_001920e4:
    printMemReference(param_1,1,param_2);
    pcVar15 = ", ";
    goto LAB_00192100;
  case 0x51:
    SStream_concat0(param_2,&DAT_001fc270);
    uVar14 = 0;
    goto LAB_0019235c;
  case 0x52:
    uVar5 = 1;
LAB_00192780:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192784:
    printMemReference(param_1,4,param_2);
    break;
  case 0x53:
    uVar5 = 1;
LAB_00192764:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192768:
    printMemReference(param_1,3,param_2);
    break;
  case 0x54:
    printOperand(param_1,3,param_2);
    break;
  case 0x57:
    SStream_concat0(param_2,&DAT_001fc360);
    break;
  case 0x58:
    SStream_concat0(param_2,&DAT_001fc368);
    break;
  case 0x59:
    SStream_concat0(param_2,&DAT_001fc370);
    break;
  case 0x5a:
    SStream_concat0(param_2,&DAT_001fc378);
    break;
  case 0x5b:
    SStream_concat0(param_2,&DAT_001fc380);
    break;
  case 0x5c:
    SStream_concat0(param_2,&DAT_001fc388);
    break;
  case 0x5d:
    SStream_concat0(param_2,&DAT_001fc390);
    break;
  case 0x5e:
    SStream_concat0(param_2,&DAT_001fc398);
    break;
  case 0x5f:
    uVar14 = 7;
LAB_00193420:
    printOperand(param_1,uVar14,param_2);
    goto switchD_00192164_caseD_6;
  case 0x60:
    uVar5 = 0x20;
    goto LAB_00192740;
  case 0x61:
    uVar5 = 0x40;
LAB_00192740:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192744:
    printMemReference(param_1,1,param_2);
    break;
  default:
    goto switchD_001919dc_default;
  }
  uVar11 = ((ulong)(uVar3 >> 0x1c) & 0x3f) - 1;
  if (0x34 < uVar11) goto switchD_001919dc_default;
  switch(uVar11 & 0xffffffff) {
  case 0:
    printOperand(param_1,1,param_2);
    break;
  case 1:
    printOperand(param_1,0,param_2);
    break;
  case 2:
    goto switchD_00192294_caseD_2;
  case 3:
    uVar14 = 2;
    goto LAB_001927a8;
  case 4:
    uVar5 = 4;
    goto LAB_00192928;
  case 5:
    uVar5 = 8;
LAB_00192928:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,1,param_2);
    goto switchD_001919dc_default;
  case 6:
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    printMemReference(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 7:
    uVar5 = 1;
    goto LAB_001928d0;
  case 8:
  case 0x31:
    uVar5 = 8;
    goto LAB_001923fc;
  case 9:
    uVar5 = 4;
    goto LAB_001928d0;
  case 10:
    uVar5 = 8;
    goto LAB_001928d0;
  case 0xb:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_001923fc;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192400;
  case 0xc:
    uVar5 = 2;
LAB_001928d0:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printSrcIdx(param_1,1,param_2);
    goto switchD_001919dc_default;
  case 0xd:
switchD_001919dc_caseD_a:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_00192084;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
LAB_001927f4:
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_00192088;
  case 0xe:
    MCInst_getOperand(param_1,2);
    bVar6 = MCOperand_getImm();
    if (bVar6 < 10) {
      SStream_concat(param_2,&DAT_001fc238);
    }
    else {
      SStream_concat(param_2,"$0x%x");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar7 = *(byte *)(lVar18 + 0xa0);
      lVar13 = lVar18 + ((ulong)bVar7 * 2 + (ulong)bVar7) * 0x10;
      *(undefined4 *)(lVar13 + 0xa8) = 2;
      *(ulong *)(lVar13 + 0xb0) = (ulong)bVar6;
      *(undefined1 *)(lVar13 + 200) = 1;
      *(byte *)(lVar18 + 0xa0) = bVar7 + 1;
    }
    goto LAB_00192ab0;
  case 0xf:
    MCInst_getOperand(param_1,3);
    bVar6 = MCOperand_getImm();
    if (bVar6 < 10) {
      SStream_concat(param_2,&DAT_001fc238);
    }
    else {
      SStream_concat(param_2,"$0x%x");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar7 = *(byte *)(lVar18 + 0xa0);
      lVar13 = lVar18 + ((ulong)bVar7 * 2 + (ulong)bVar7) * 0x10;
      *(undefined4 *)(lVar13 + 0xa8) = 2;
      *(ulong *)(lVar13 + 0xb0) = (ulong)bVar6;
      *(undefined1 *)(lVar13 + 200) = 1;
      *(byte *)(lVar18 + 0xa0) = bVar7 + 1;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
LAB_00192ab0:
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    goto switchD_001919dc_default;
  case 0x10:
switchD_001919dc_caseD_1c:
    uVar5 = 1;
    goto LAB_00192084;
  case 0x11:
switchD_001919dc_caseD_d:
    uVar5 = 4;
    goto LAB_00192084;
  case 0x12:
switchD_001919dc_caseD_b:
    uVar5 = 8;
    goto LAB_00192084;
  case 0x13:
switchD_001919dc_caseD_c:
    uVar5 = 2;
LAB_00192084:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192088:
    printMemReference(param_1,0,param_2);
    bVar6 = *(byte *)(param_1 + 5);
    goto joined_r0x00192374;
  case 0x14:
    uVar14 = 3;
LAB_001927a8:
    printOperand(param_1,uVar14,param_2);
switchD_00192294_caseD_2:
    SStream_concat0(param_2,", ");
    break;
  case 0x15:
    SStream_concat0(param_2,"{1to4}, ");
    op_addAvxBroadcast(param_1,2);
    break;
  case 0x16:
    goto switchD_00192164_caseD_28;
  case 0x17:
    printOperand(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fc270);
    printOperand(param_1,2,param_2);
    break;
  case 0x18:
    SStream_concat0(param_2,"{1to8}, ");
    op_addAvxBroadcast(param_1,3);
    break;
  case 0x19:
    SStream_concat0(param_2,"{1to16}, ");
    op_addAvxBroadcast(param_1,4);
    break;
  case 0x1a:
    SStream_concat0(param_2,"{1to2}, ");
    op_addAvxBroadcast(param_1,1);
    break;
  case 0x1b:
    SStream_concat0(param_2,&DAT_001fc270);
    break;
  case 0x1c:
  case 0x2b:
    uVar5 = 0x20;
    goto LAB_00192380;
  case 0x1d:
  case 0x32:
    uVar5 = 8;
    goto LAB_001923d8;
  case 0x1e:
  case 0x2a:
    uVar5 = 0x10;
    goto LAB_001922ec;
  case 0x1f:
  case 0x2c:
    uVar5 = 0x20;
    goto LAB_001922ec;
  case 0x20:
  case 0x2d:
    uVar5 = 0x40;
    goto LAB_00192380;
  case 0x21:
  case 0x2e:
    uVar5 = 0x40;
LAB_001922ec:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,&DAT_001fc270);
    uVar14 = 1;
    goto LAB_0019235c;
  case 0x22:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 == 0x39b) || (iVar8 == 0x3b2)) {
      iVar8 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar8 - 4U & 0xfffffffb) == 0) {
        uVar5 = 0x1c;
        goto LAB_001923d8;
      }
      if (iVar8 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    goto LAB_001923dc;
  case 0x23:
  case 0x26:
    uVar5 = 0x10;
    goto LAB_0019229c;
  case 0x24:
    uVar5 = 8;
    goto LAB_0019229c;
  case 0x25:
  case 0x27:
    uVar5 = 0x20;
LAB_0019229c:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,0,param_2);
    break;
  case 0x28:
    goto switchD_00192164_caseD_29;
  case 0x29:
    uVar5 = 0x10;
LAB_00192380:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,2,param_2);
LAB_00192394:
    pcVar15 = ", ";
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    goto LAB_00192100;
  case 0x2f:
    uVar5 = 4;
LAB_001923fc:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_00192400:
    printMemReference(param_1,2,param_2);
    break;
  case 0x30:
    uVar5 = 4;
LAB_001923d8:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
LAB_001923dc:
    printMemReference(param_1,3,param_2);
    break;
  case 0x33:
    uVar5 = 2;
    goto LAB_00192870;
  case 0x34:
    uVar5 = 1;
LAB_00192870:
    *(undefined1 *)(param_1 + 0x328) = uVar5;
    printMemReference(param_1,2,param_2);
  default:
    goto switchD_001919dc_default;
  }
  uVar11 = (uVar12 >> 0x22 & 0xf) - 1;
  if (0xd < uVar11) goto switchD_001919dc_default;
  switch(uVar11 & 0xffffffff) {
  case 0:
    printOperand(param_1,0,param_2);
    break;
  case 1:
    SStream_concat0(param_2,", ");
    break;
  case 2:
    printOperand(param_1,1,param_2);
    break;
  case 3:
    printOperand(param_1,3,param_2);
    break;
  case 4:
    printOperand(param_1,2,param_2);
    break;
  case 5:
    goto switchD_00192164_caseD_28;
  case 6:
    SStream_concat0(param_2,&DAT_001fc270);
    break;
  case 7:
    SStream_concat0(param_2,"{1to2}, ");
    op_addAvxBroadcast(param_1,1);
    break;
  case 8:
    SStream_concat0(param_2,"{1to4}, ");
    op_addAvxBroadcast(param_1,2);
    break;
  case 9:
    SStream_concat0(param_2,"{1to8}, ");
    op_addAvxBroadcast(param_1,3);
    break;
  case 10:
    SStream_concat0(param_2,"{1to16}, ");
    op_addAvxBroadcast(param_1,4);
    break;
  case 0xb:
    goto switchD_001922dc_caseD_b;
  case 0xc:
    goto switchD_00192164_caseD_29;
  case 0xd:
    uVar14 = 6;
    goto LAB_0019235c;
  default:
    goto switchD_001919dc_default;
  }
  uVar11 = uVar12 >> 0x26 & 0xf;
  if (uVar11 == 5) {
    printOperand(param_1,1,param_2);
    goto LAB_001924a0;
  }
  if (uVar11 < 6) {
    if (uVar11 == 3) {
      SStream_concat0(param_2,", ");
LAB_001924a0:
      uVar11 = uVar12 >> 0x2a & 7;
      if (uVar11 != 3) {
        if ((uVar12 & 0x100000000000) == 0) {
          if (uVar11 == 1) {
            printOperand(param_1,1,param_2);
          }
          else if (uVar11 == 2) {
            printOperand(param_1,0,param_2);
          }
          else {
LAB_00193900:
            printOperand(param_1,2,param_2);
          }
        }
        else {
          if (uVar11 == 4) goto switchD_00192164_caseD_29;
          if (uVar11 != 5) goto LAB_00193900;
          SStream_concat0(param_2,", ");
          printOperand(param_1,0,param_2);
        }
        uVar11 = uVar12 >> 0x2d;
        if (uVar11 == 3) {
          SStream_concat0(param_2,&DAT_001fc270);
          if ((bVar6 & 1) == 0) {
            printOperand(param_1,2,param_2);
          }
          else {
            printOperand(param_1,1,param_2);
          }
          if ((bVar6 & 2) != 0) goto LAB_0019242c;
          SStream_concat0(param_2,&DAT_001f7b60);
          goto switchD_001919dc_default;
        }
        if (uVar12 >> 0x2f == 0) {
          if (uVar11 == 1) goto switchD_00192164_caseD_29;
          if (uVar11 == 2) goto switchD_001919dc_default;
        }
        else if (uVar11 == 4) {
          pcVar15 = ", ";
LAB_00192100:
          SStream_concat0(param_2,pcVar15);
          printOperand(param_1,0,param_2);
          bVar6 = *(byte *)(param_1 + 5);
          goto joined_r0x00192374;
        }
      }
switchD_00192164_caseD_28:
      SStream_concat0(param_2,&DAT_001f7b60);
    }
    else {
      if (uVar11 == 4) {
        printOperand(param_1,2,param_2);
        goto LAB_001924a0;
      }
      if (uVar11 == 1) {
        printOperand(param_1,0,param_2);
      }
      else if (uVar11 == 2) {
        SStream_concat0(param_2,&DAT_001fc270);
        goto LAB_001924a0;
      }
    }
switchD_001919dc_default:
    bVar6 = *(byte *)(param_1 + 5);
  }
  else {
    if (uVar11 != 8) {
      if (8 < uVar11) {
        uVar14 = 3;
        if (uVar11 != 9) goto switchD_001919dc_default;
        goto LAB_0019235c;
      }
      if (uVar11 == 6) goto switchD_00192164_caseD_28;
switchD_00192164_caseD_29:
LAB_0019242c:
      SStream_concat0(param_2,"} {z}");
      op_addAvxZeroOpmask(param_1);
      goto switchD_001919dc_default;
    }
switchD_001922dc_caseD_b:
    uVar14 = 5;
LAB_0019235c:
    printOperand(param_1,uVar14,param_2);
    SStream_concat0(param_2,&DAT_001f7b60);
    bVar6 = *(byte *)(param_1 + 5);
  }
joined_r0x00192374:
  if ((bVar6 & 1) != 0) {
    lVar13 = *(long *)(*(int **)(param_1 + 0x310) + 0x3c);
    bVar6 = *(byte *)(lVar13 + 0xa0);
    if (bVar6 < 2) {
      *(undefined1 *)(lVar13 + 200) = *(undefined1 *)(param_1 + 0x334);
    }
    else if (2 < **(int **)(param_1 + 0x310) - 0xaaU) {
      if (*(int *)(lVar13 + 0xa8) == 2) {
        uVar9 = bVar6 - 1;
        *(undefined1 *)(lVar13 + 200) =
             *(undefined1 *)
              (lVar13 + ((-(ulong)(uVar9 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar9 << 1) +
                        (long)(int)uVar9) * 0x10 + 200);
      }
      if (*(int *)(lVar13 + 0xd8) == 2) {
        uVar9 = bVar6 - 1;
        *(undefined1 *)(lVar13 + 0xf8) =
             *(undefined1 *)
              (lVar13 + ((-(ulong)(uVar9 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar9 << 1) +
                        (long)(int)uVar9) * 0x10 + 200);
      }
      uVar9 = (uint)bVar6;
      if (uVar9 != 2) {
        if (*(int *)(lVar13 + 0x108) == 2) {
          uVar1 = uVar9 - 1;
          *(undefined1 *)(lVar13 + 0x128) =
               *(undefined1 *)
                (lVar13 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                          (long)(int)uVar1) * 0x10 + 200);
        }
        if (uVar9 != 3) {
          if (*(int *)(lVar13 + 0x138) == 2) {
            uVar1 = uVar9 - 1;
            *(undefined1 *)(lVar13 + 0x158) =
                 *(undefined1 *)
                  (lVar13 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                            (long)(int)uVar1) * 0x10 + 200);
          }
          if (uVar9 != 4) {
            if (*(int *)(lVar13 + 0x168) == 2) {
              uVar1 = uVar9 - 1;
              *(undefined1 *)(lVar13 + 0x188) =
                   *(undefined1 *)
                    (lVar13 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                              (long)(int)uVar1) * 0x10 + 200);
            }
            if (uVar9 != 5) {
              if (*(int *)(lVar13 + 0x198) == 2) {
                uVar9 = uVar9 - 1;
                *(undefined1 *)(lVar13 + 0x1b8) =
                     *(undefined1 *)
                      (lVar13 + ((-(ulong)(uVar9 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar9 << 1)
                                + (long)(int)uVar9) * 0x10 + 200);
              }
              uVar9 = (uint)bVar6;
              if (uVar9 != 6) {
                if (*(int *)(lVar13 + 0x1c8) == 2) {
                  uVar1 = uVar9 - 1;
                  *(undefined1 *)(lVar13 + 0x1e8) =
                       *(undefined1 *)
                        (lVar13 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1
                                   ) + (long)(int)uVar1) * 0x10 + 200);
                }
                if ((uVar9 != 7) && (*(int *)(lVar13 + 0x1f8) == 2)) {
                  uVar9 = uVar9 - 1;
                  *(undefined1 *)(lVar13 + 0x218) =
                       *(undefined1 *)
                        (lVar13 + ((-(ulong)(uVar9 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar9 << 1
                                   ) + (long)(int)uVar9) * 0x10 + 200);
                }
              }
            }
          }
        }
      }
    }
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    local_50._0_4_ = 0;
    local_50._4_2_ = 0;
    uVar9 = MCInst_getOpcode(param_1);
    if (uVar9 < 0x9a5) {
      if (0x975 < uVar9) {
        uVar12 = 0x492492249249 >> ((ulong)(uVar9 - 0x976) & 0x3f);
        goto joined_r0x00193804;
      }
      if (uVar9 < 0x90f) {
        if (0x8da < uVar9) {
          uVar12 = 0x9249240249249 >> ((ulong)(uVar9 - 0x8db) & 0x3f);
          goto joined_r0x00193804;
        }
      }
      else if (uVar9 - 0x92d < 0x2e) {
        uVar12 = 0x249249249249 >> ((ulong)(uVar9 - 0x92d) & 0x3f);
        goto joined_r0x00193804;
      }
    }
    else {
      if (0x3d < uVar9 - 0xa07) goto LAB_00191acc;
      uVar12 = 0x2492490000249249 >> ((ulong)(uVar9 - 0xa07) & 0x3f);
joined_r0x00193804:
      if ((uVar12 & 1) != 0) {
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        memmove((void *)(lVar13 + 0xd8),(void *)(lVar13 + 0xa8),0x150);
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar13 + 0xa8) = 2;
        *(char *)(lVar13 + 0xa0) = *(char *)(lVar13 + 0xa0) + '\x01';
        *(undefined8 *)(lVar13 + 0xb0) = 1;
        *(undefined1 *)(lVar13 + 200) = 1;
      }
    }
LAB_00191acc:
    uVar14 = MCInst_getOpcode(param_1);
    uVar9 = X86_insn_reg_att(uVar14,local_58);
    local_60 = uVar9;
    if (uVar9 == 0) {
      uVar14 = MCInst_getOpcode(param_1);
      uVar12 = X86_insn_reg_att2(uVar14,&local_60,local_58,&uStack_5c,local_54);
      if ((uVar12 & 1) == 0) {
        lVar21 = *(long *)(param_1 + 800);
      }
      else {
        lVar21 = *(long *)(param_1 + 800);
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar18 = *(long *)(lVar21 + 0xa0);
        *(undefined4 *)(lVar13 + 0xa8) = 1;
        *(uint *)(lVar13 + 0xb0) = local_60;
        *(undefined1 *)(lVar13 + 200) = *(undefined1 *)(lVar18 + (ulong)local_60);
        *(undefined1 *)(lVar13 + 0xc9) = local_58[0];
        *(undefined4 *)(lVar13 + 0xd8) = 1;
        *(uint *)(lVar13 + 0xe0) = uStack_5c;
        uVar5 = *(undefined1 *)(lVar18 + (ulong)uStack_5c);
        *(undefined1 *)(lVar13 + 0xa0) = 2;
        *(undefined1 *)(lVar13 + 0xc9) = local_54[0];
        *(undefined1 *)(lVar13 + 0xf8) = uVar5;
      }
    }
    else {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      memmove((void *)(lVar13 + 0xd8),(void *)(lVar13 + 0xa8),0x150);
      lVar21 = *(long *)(param_1 + 800);
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar18 = *(long *)(lVar21 + 0xa0);
      *(undefined4 *)(lVar13 + 0xa8) = 1;
      *(uint *)(lVar13 + 0xb0) = uVar9;
      uVar5 = *(undefined1 *)(lVar18 + (ulong)uVar9);
      *(char *)(lVar13 + 0xa0) = *(char *)(lVar13 + 0xa0) + '\x01';
      *(undefined1 *)(lVar13 + 200) = uVar5;
      *(undefined1 *)(lVar13 + 0xc9) = local_58[0];
    }
    uVar10 = MCInst_getOpcode(param_1);
    pcVar15 = (char *)X86_get_op_access(lVar21,uVar10,
                                        *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar15 == (char *)0x0) {
      uVar17 = 0;
      uVar5 = 0;
    }
    else {
      uVar12 = 0;
      if (*pcVar15 == '\0') {
        uVar5 = 0;
        uVar17 = 0;
      }
      else {
        do {
          uVar11 = uVar12;
          uVar20 = (uint)uVar11;
          uVar9 = uVar20 + 1;
          uVar1 = uVar9 & 0xff;
          uVar12 = (ulong)uVar1;
        } while (pcVar15[uVar12] != '\0');
        uVar5 = 0;
        uVar17 = 0;
        if (uVar1 != 0) {
          if ((uVar20 - 7 & 0xff) < 0xf8) {
            uVar16 = 0;
            if (uVar20 < 0xf) {
LAB_00191d84:
              uVar14 = NEON_rev64(*(undefined8 *)(pcVar15 + ((uVar11 - 7) - (ulong)(byte)uVar16)),1)
              ;
              bVar6 = (byte)((ulong)uVar14 >> 8);
              bVar7 = (byte)((ulong)uVar14 >> 0x10);
              bVar23 = (byte)((ulong)uVar14 >> 0x18);
              bVar24 = (byte)((ulong)uVar14 >> 0x20);
              bVar25 = (byte)((ulong)uVar14 >> 0x28);
              bVar26 = (byte)((ulong)uVar14 >> 0x30);
              bVar27 = (byte)((ulong)uVar14 >> 0x38);
              *(ulong *)((long)&local_50 + (ulong)uVar16) =
                   CONCAT17(bVar27 & ~-(bVar27 == 0x80),
                            CONCAT16(bVar26 & ~-(bVar26 == 0x80),
                                     CONCAT15(bVar25 & ~-(bVar25 == 0x80),
                                              CONCAT14(bVar24 & ~-(bVar24 == 0x80),
                                                       CONCAT13(bVar23 & ~-(bVar23 == 0x80),
                                                                CONCAT12(bVar7 & ~-(bVar7 == 0x80),
                                                                         CONCAT11(bVar6 & ~-(bVar6 
                                                  == 0x80),(byte)uVar14 & ~-((byte)uVar14 == 0x80)))
                                                  )))));
              uVar16 = uVar16 + ((uint)uVar12 & 0xfffffff8) & 0xff;
              if ((uVar12 & 7) != 0) {
                uVar9 = uVar20 - uVar16;
LAB_00191dc0:
                cVar2 = pcVar15[(int)uVar9];
                uVar9 = uVar16 + 1 & 0xff;
                if (cVar2 == -0x80) {
                  cVar2 = '\0';
                }
                *(char *)((long)&local_50 + (ulong)uVar16) = cVar2;
                if ((uVar16 + 1 & 0xff) <= uVar20) {
                  uVar1 = uVar16 + 2 & 0xff;
                  cVar2 = pcVar15[(int)(uVar20 - uVar9)];
                  if (cVar2 == -0x80) {
                    cVar2 = '\0';
                  }
                  *(char *)((long)&local_50 + (ulong)uVar9) = cVar2;
                  if ((uVar16 + 2 & 0xff) <= uVar20) {
                    uVar9 = uVar16 + 3 & 0xff;
                    cVar2 = pcVar15[(int)(uVar20 - uVar1)];
                    if (cVar2 == -0x80) {
                      cVar2 = '\0';
                    }
                    *(char *)((long)&local_50 + (ulong)uVar1) = cVar2;
                    if ((uVar16 + 3 & 0xff) <= uVar20) {
                      uVar1 = uVar16 + 4 & 0xff;
                      cVar2 = pcVar15[(int)(uVar20 - uVar9)];
                      if (cVar2 == -0x80) {
                        cVar2 = '\0';
                      }
                      *(char *)((long)&local_50 + (ulong)uVar9) = cVar2;
                      if ((uVar16 + 4 & 0xff) <= uVar20) {
                        uVar9 = uVar16 + 5 & 0xff;
                        cVar2 = pcVar15[(int)(uVar20 - uVar1)];
                        if (cVar2 == -0x80) {
                          cVar2 = '\0';
                        }
                        *(char *)((long)&local_50 + (ulong)uVar1) = cVar2;
                        if ((uVar16 + 5 & 0xff) <= uVar20) {
                          uVar1 = uVar16 + 6 & 0xff;
                          cVar2 = pcVar15[(int)(uVar20 - uVar9)];
                          if (cVar2 == -0x80) {
                            cVar2 = '\0';
                          }
                          *(char *)((long)&local_50 + (ulong)uVar9) = cVar2;
                          if ((uVar16 + 6 & 0xff) <= uVar20) {
                            cVar2 = pcVar15[(int)(uVar20 - uVar1)];
                            if (cVar2 == -0x80) {
                              cVar2 = '\0';
                            }
                            *(char *)((long)&local_50 + (ulong)uVar1) = cVar2;
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
              auVar22 = a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xf)),
                                _DAT_0020ab20);
              local_50._6_1_ = auVar22[6] & ~-(auVar22[6] == 0x80);
              local_50._7_1_ = auVar22[7] & ~-(auVar22[7] == 0x80);
              uStack_48 = CONCAT17(auVar22[0xf] & ~-(auVar22[0xf] == 0x80),
                                   CONCAT16(auVar22[0xe] & ~-(auVar22[0xe] == 0x80),
                                            CONCAT15(auVar22[0xd] & ~-(auVar22[0xd] == 0x80),
                                                     CONCAT14(auVar22[0xc] &
                                                              ~-(auVar22[0xc] == 0x80),
                                                              CONCAT13(auVar22[0xb] &
                                                                       ~-(auVar22[0xb] == 0x80),
                                                                       CONCAT12(auVar22[10] &
                                                                                ~-(auVar22[10] ==
                                                                                  0x80),CONCAT11(
                                                  auVar22[9] & ~-(auVar22[9] == 0x80),
                                                  auVar22[8] & ~-(auVar22[8] == 0x80))))))));
              local_50._0_4_ =
                   CONCAT13(auVar22[3] & ~-(auVar22[3] == 0x80),
                            CONCAT12(auVar22[2] & ~-(auVar22[2] == 0x80),
                                     CONCAT11(auVar22[1] & ~-(auVar22[1] == 0x80),
                                              auVar22[0] & ~-(auVar22[0] == 0x80))));
              local_50._4_2_ =
                   CONCAT11(auVar22[5] & ~-(auVar22[5] == 0x80),auVar22[4] & ~-(auVar22[4] == 0x80))
              ;
              if (((((uVar1 != 1) &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x1f)),
                             _DAT_0020ab20), uVar1 != 2)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x2f)),
                            _DAT_0020ab20), uVar1 != 3)) &&
                  ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x3f)),
                              _DAT_0020ab20), uVar1 != 4 &&
                     (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x4f)),
                              _DAT_0020ab20), uVar1 != 5)) &&
                    ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x5f)),
                              _DAT_0020ab20), uVar1 != 6 &&
                     ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x6f)),
                               _DAT_0020ab20), uVar1 != 7 &&
                      (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x7f)),
                               _DAT_0020ab20), uVar1 != 8)))))) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x8f)),
                            _DAT_0020ab20), uVar1 != 9)))) &&
                 ((((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0x9f)),
                             _DAT_0020ab20), uVar1 != 10 &&
                    (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xaf)),
                             _DAT_0020ab20), uVar1 != 0xb)) &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xbf)),
                            _DAT_0020ab20), uVar1 != 0xc)) &&
                  ((a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xcf)),
                            _DAT_0020ab20), uVar1 != 0xd &&
                   (a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xdf)),
                            _DAT_0020ab20), uVar1 == 0xf)))))) {
                a64_TBL(ZEXT816(0),*(undefined1 (*) [16])(pcVar15 + (uVar11 - 0xef)),_DAT_0020ab20);
              }
              uVar16 = uVar9 & 0xf0;
              if ((uVar9 & 0xf) != 0) {
                uVar9 = uVar20 - uVar16;
                uVar12 = (ulong)((uVar9 & 0xff) + 1 & 0xff);
                if (6 < (uVar9 & 0xff)) goto LAB_00191d84;
                goto LAB_00191dc0;
              }
            }
          }
          else {
            pcVar15 = pcVar15 + uVar11;
            pcVar19 = (char *)&local_50;
            uVar9 = 0;
            do {
              cVar2 = *pcVar15;
              pcVar4 = pcVar19;
              while (cVar2 != -0x80) {
                uVar1 = uVar9 + 1;
                *pcVar4 = cVar2;
                pcVar15 = pcVar15 + -1;
                uVar9 = uVar1 & 0xff;
                if (uVar20 < (uVar1 & 0xff)) goto LAB_00191eac;
                pcVar4 = pcVar4 + 1;
                cVar2 = *pcVar15;
              }
              uVar1 = uVar9 + 1;
              pcVar19 = pcVar4 + 1;
              *pcVar4 = '\0';
              pcVar15 = pcVar15 + -1;
              uVar9 = uVar1 & 0xff;
            } while ((uVar1 & 0xff) <= uVar20);
          }
LAB_00191eac:
          uVar5 = (undefined1)(undefined4)local_50;
          uVar17 = local_50._1_1_;
        }
      }
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined1 *)(lVar13 + 0xc9) = uVar5;
    *(undefined1 *)(lVar13 + 0xf9) = uVar17;
  }
  lVar13 = uStack_48 - *(long *)PTR___stack_chk_guard_005ffe88;
  if (lVar13 == 0) {
    return;
  }
LAB_00193c3c:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar13);
}

