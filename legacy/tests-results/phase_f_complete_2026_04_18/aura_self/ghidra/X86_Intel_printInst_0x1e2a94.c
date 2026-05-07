
void X86_Intel_printInst(long param_1,char *param_2)

{
  ulong uVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  ulong uVar9;
  undefined8 uVar10;
  char *pcVar11;
  long lVar12;
  undefined1 uVar13;
  long lVar14;
  undefined *puVar15;
  undefined4 *puVar16;
  long lVar17;
  uint local_60;
  uint uStack_5c;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined4 local_50;
  undefined2 local_4c;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (*(char *)(param_1 + 0x368) != '\0') {
    lVar12 = local_48 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar12 == 0) {
      strncpy(param_2,(char *)(param_1 + 0x368),0x200);
      return;
    }
    goto LAB_001e4c60;
  }
  X86_lockrep();
  uVar9 = MCInst_getOpcode(param_1);
  uVar5 = *(uint *)(OpInfo1_3 + (uVar9 & 0xffffffff) * 4);
  uVar8 = *(uint *)(OpInfo0_4 + (uVar9 & 0xffffffff) * 4);
  SStream_concat0(param_2,(uVar8 & 0x3fff) + 0x3e849f);
  uVar9 = (((ulong)uVar8 & 0xfc000) >> 0xe) - 1;
  if (0x32 < uVar9) goto switchD_001e2c60_default;
  switch(uVar9 & 0xffffffff) {
  case 0:
    printOperand(param_1,0,param_2);
    break;
  case 1:
    pcVar11 = "word ptr ";
    *(undefined1 *)(param_1 + 0x328) = 2;
    goto LAB_001e3558;
  case 2:
    printOperand(param_1,1,param_2);
    break;
  case 3:
    pcVar11 = "dword ptr ";
    *(undefined1 *)(param_1 + 0x328) = 4;
LAB_001e3558:
    SStream_concat0(param_2,pcVar11);
    printMemReference(param_1,0,param_2);
    break;
  case 4:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e2d80;
  case 5:
    SStream_concat0(param_2,"byte ptr ");
    uVar3 = 1;
    goto LAB_001e2d80;
  case 6:
    iVar7 = MCInst_getOpcode(param_1);
    if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
      iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar7 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar7 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      SStream_concat0(param_2,"dword ptr ");
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    printMemReference(param_1,0,param_2);
    break;
  case 7:
    if ((*(char *)(param_1 + 6) == '\x10') &&
       ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
    }
    else {
      uVar3 = 8;
      SStream_concat0(param_2,"qword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,0,param_2);
    break;
  case 8:
  case 0x1f:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e2d80;
  case 9:
    uVar5 = *(uint *)(param_1 + 8);
    if (uVar5 < 0x4e2) {
      if (uVar5 < 0x4e0) {
        if (uVar5 < 0x19b) {
          if ((0x184 < uVar5) && ((0x201555UL >> ((ulong)(uVar5 - 0x185) & 0x3f) & 1) != 0)) {
            *(undefined1 *)(param_1 + 0x328) = 0x10;
          }
        }
        else if (uVar5 == 0x4df) {
          *(undefined1 *)(param_1 + 0x328) = 2;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x328) = 4;
      }
    }
    else if (uVar5 == 0x4e2) {
      *(undefined1 *)(param_1 + 0x328) = 8;
    }
    printMemReference(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,5,param_2);
    goto switchD_001e2c60_default;
  case 10:
    uVar10 = MCInst_getOperand(param_1,0);
    uVar9 = MCOperand_isImm();
    if ((uVar9 & 1) != 0) {
      lVar12 = MCOperand_getImm(uVar10);
      uVar9 = (ulong)*(ushort *)(*(long *)(param_1 + 0x310) + 0x10) + lVar12 +
              *(long *)(param_1 + 0x318);
      cVar4 = X86_immediate_size(*(undefined4 *)(param_1 + 8),0);
      uVar1 = uVar9 & 0xffffffff;
      if (*(int *)(*(long *)(param_1 + 800) + 4) == 8) {
        uVar1 = uVar9;
      }
      printImm_isra_0(*(undefined1 *)(param_1 + 6),*(long *)(param_1 + 800),param_2,uVar1,1);
      lVar12 = *(long *)(param_1 + 800);
      if (*(int *)(lVar12 + 0x60) != 0) {
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar17 + 0xa0);
        lVar14 = lVar17 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
        *(undefined4 *)(lVar14 + 0xa8) = 2;
        if (bVar2 == 0) {
          if (cVar4 == '\0') {
            *(undefined1 *)(lVar17 + 200) = *(undefined1 *)(param_1 + 0x334);
          }
          else {
            *(char *)(lVar17 + 200) = cVar4;
          }
        }
        else {
          *(undefined1 *)(lVar14 + 200) = *(undefined1 *)(lVar17 + 200);
        }
        *(ulong *)(lVar17 + (ulong)bVar2 * 0x30 + 0xb0) = uVar1;
        uVar6 = MCInst_getOpcode(param_1);
        pcVar11 = (char *)X86_get_op_access(lVar12,uVar6,
                                            *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
        if (pcVar11 == (char *)0x0) {
          local_50 = local_50 & 0xffffff00;
        }
        else {
          uVar5 = 0;
          uVar9 = 0;
          cVar4 = *pcVar11;
          while (cVar4 != '\0') {
            while (cVar4 == -0x80) {
              uVar8 = uVar5 + 1;
              *(undefined1 *)((long)&local_50 + uVar9) = 0;
              uVar5 = uVar8 & 0xff;
              uVar9 = (ulong)uVar8 & 0xff;
              cVar4 = pcVar11[uVar5];
              if (cVar4 == '\0') goto LAB_001e37d0;
            }
            uVar8 = uVar5 + 1;
            *(char *)((long)&local_50 + uVar9) = cVar4;
            uVar5 = uVar8 & 0xff;
            uVar9 = (ulong)uVar8 & 0xff;
            cVar4 = pcVar11[uVar5];
          }
LAB_001e37d0:
          *(undefined1 *)((long)&local_50 + uVar9) = 0;
        }
        lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar12 + 0xa0);
        *(undefined1 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc9) =
             *(undefined1 *)((long)&local_50 + (long)(int)(uint)bVar2);
        *(byte *)(lVar12 + 0xa0) = bVar2 + 1;
      }
      if (*(char *)(param_1 + 6) == '\0') {
        *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x334);
      }
    }
    goto switchD_001e2c60_default;
  case 0xb:
    printSSEAVXCC(param_1,7,param_2);
    break;
  case 0xc:
    printSSEAVXCC(param_1,3,param_2);
    break;
  case 0xd:
    pcVar11 = "byte ptr ";
    SStream_concat0(param_2,"byte ptr ");
    uVar3 = 1;
    goto LAB_001e32a0;
  case 0xe:
    pcVar11 = "dword ptr ";
    SStream_concat0(param_2,"dword ptr ");
    uVar3 = 4;
    goto LAB_001e32a0;
  case 0xf:
    pcVar11 = "qword ptr ";
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e32a0;
  case 0x10:
    pcVar11 = "word ptr ";
    SStream_concat0(param_2,"word ptr ");
    uVar3 = 2;
LAB_001e32a0:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printSrcIdx(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    SStream_concat0(param_2,pcVar11);
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printDstIdx_constprop_0(param_1,param_2);
    goto switchD_001e2c60_default;
  case 0x11:
    printopaquemem(param_1,0,param_2);
    goto switchD_001e2c60_default;
  case 0x12:
    iVar7 = MCInst_getOpcode(param_1);
    if (1 < iVar7 - 0x388U) {
      SStream_concat0(param_2,"xword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = 10;
    printMemReference(param_1,0,param_2);
    goto switchD_001e2c60_default;
  case 0x13:
    printU8Imm(param_1,0,param_2);
    break;
  case 0x14:
    SStream_concat0(param_2,"byte ptr ");
    *(undefined1 *)(param_1 + 0x328) = 1;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x15:
    SStream_concat0(param_2,"dword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 4;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x16:
    SStream_concat0(param_2,"word ptr ");
    *(undefined1 *)(param_1 + 0x328) = 2;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x17:
    SStream_concat0(param_2,"byte ptr ");
    uVar3 = 1;
    goto LAB_001e33fc;
  case 0x18:
    SStream_concat0(param_2,"dword ptr ");
    uVar3 = 4;
    goto LAB_001e33fc;
  case 0x19:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e33fc;
  case 0x1a:
    SStream_concat0(param_2,"word ptr ");
    uVar3 = 2;
LAB_001e33fc:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printSrcIdx(param_1,0,param_2);
    goto switchD_001e2c60_default;
  case 0x1b:
    SStream_concat0(param_2,"word ptr ");
    *(undefined1 *)(param_1 + 0x328) = 2;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x1c:
    SStream_concat0(param_2,"dword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 4;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x1d:
    SStream_concat0(param_2,"qword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 8;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x1e:
    SStream_concat0(param_2,"byte ptr ");
    *(undefined1 *)(param_1 + 0x328) = 1;
    printMemOffset_constprop_0(param_1,param_2);
    break;
  case 0x20:
    SStream_concat0(param_2,"qword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 8;
    printDstIdx_constprop_0(param_1,param_2);
    break;
  case 0x21:
    printSSEAVXCC(param_1,8,param_2);
    break;
  case 0x22:
    printSSEAVXCC(param_1,4,param_2);
    break;
  case 0x23:
  case 0x25:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
    goto LAB_001e2d80;
  case 0x24:
  case 0x26:
    SStream_concat0(param_2,"zmmword ptr ");
    uVar3 = 0x40;
LAB_001e2d80:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,0,param_2);
    break;
  case 0x27:
    printXOPCC(param_1,7,param_2);
    break;
  case 0x28:
    printXOPCC(param_1,3,param_2);
    break;
  case 0x29:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e3130;
  case 0x2a:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
    goto LAB_001e3130;
  case 0x2b:
    SStream_concat0(param_2,"zmmword ptr ");
    uVar3 = 0x40;
    goto LAB_001e3130;
  case 0x2c:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
LAB_001e3130:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fde50);
    printOperand(param_1,6,param_2);
    SStream_concat0(param_2,&DAT_001fe650);
    printOperand(param_1,7,param_2);
    goto switchD_001e2c60_default;
  case 0x2d:
    *(undefined1 *)(param_1 + 0x328) = 2;
    SStream_concat0(param_2,"word ptr ");
    goto LAB_001e30d4;
  case 0x2e:
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    goto switchD_001e2c60_default;
  case 0x2f:
    *(undefined1 *)(param_1 + 0x328) = 4;
    SStream_concat0(param_2,"dword ptr ");
    goto LAB_001e30d4;
  case 0x30:
    SStream_concat0(param_2,"qword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 8;
    goto LAB_001e30d4;
  case 0x31:
    SStream_concat0(param_2,"byte ptr ");
    *(undefined1 *)(param_1 + 0x328) = 1;
LAB_001e30d4:
    printMemReference(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    goto switchD_001e2c60_default;
  case 0x32:
    printOperand(param_1,3,param_2);
    goto LAB_001e350c;
  default:
    goto switchD_001e2c60_default;
  }
  uVar9 = (((ulong)uVar8 & 0x1f00000) >> 0x14) - 1;
  if (0x17 < uVar9) goto switchD_001e2c60_default;
  switch(uVar9 & 0xffffffff) {
  case 0:
    SStream_concat0(param_2,", ");
    goto LAB_001e2e48;
  case 1:
    SStream_concat0(param_2,", st(0)");
    op_addReg(param_1,0x72);
    goto switchD_001e2c60_default;
  case 2:
    puVar15 = &DAT_001fde80;
    break;
  case 3:
    puVar15 = &DAT_001fde88;
    break;
  case 4:
    puVar15 = &DAT_001fde90;
    break;
  case 5:
    puVar15 = &DAT_001fde98;
    break;
  case 6:
    SStream_concat0(param_2,&DAT_001fde30);
    printOperand(param_1,0,param_2);
    goto switchD_001e2c60_default;
  case 7:
    SStream_concat0(param_2,&DAT_00203a00);
    op_addReg(param_1,0x12);
    goto switchD_001e2c60_default;
  case 8:
    SStream_concat0(param_2,&DAT_00203a08);
    op_addReg(param_1,3);
    goto switchD_001e2c60_default;
  case 9:
    SStream_concat0(param_2,", eax");
    op_addReg(param_1,0x13);
    goto switchD_001e2c60_default;
  case 10:
    SStream_concat0(param_2,", rax");
    op_addReg(param_1,0x23);
    goto switchD_001e2c60_default;
  case 0xb:
    SStream_concat0(param_2,&DAT_00203a20);
    op_addReg(param_1,2);
    goto switchD_001e2c60_default;
  case 0xc:
    goto switchD_001e2dc0_caseD_c;
  case 0xd:
    SStream_concat0(param_2,&DAT_00203a30);
    op_addImm(param_1,1);
    goto switchD_001e2c60_default;
  case 0xe:
    SStream_concat0(param_2,&DAT_001fde50);
    goto LAB_001e2e48;
  case 0xf:
    SStream_concat0(param_2,&DAT_001fe650);
    goto LAB_001e2e48;
  case 0x10:
    puVar15 = &DAT_001fdf40;
    break;
  case 0x11:
    puVar15 = &DAT_001fdf48;
    break;
  case 0x12:
    puVar15 = &DAT_001fdf50;
    break;
  case 0x13:
    puVar15 = &DAT_001fdf58;
    break;
  case 0x14:
    puVar15 = &DAT_001fdf60;
    break;
  case 0x15:
    puVar15 = &DAT_001fdf68;
    break;
  case 0x16:
    puVar15 = &DAT_001fdf70;
    break;
  case 0x17:
    puVar15 = &DAT_001fdf78;
    break;
  default:
    goto switchD_001e2c60_default;
  }
  SStream_concat0(param_2,puVar15);
  printOperand(param_1,0,param_2);
LAB_001e2e48:
  uVar9 = (((ulong)uVar8 & 0x7e000000) >> 0x19) - 1;
  if (0x24 < uVar9) {
switchD_001e3cbc_default:
    printOperand(param_1,5,param_2);
    goto LAB_001e2e70;
  }
  switch(uVar9 & 0xffffffff) {
  case 0:
    printOperand(param_1,2,param_2);
    break;
  case 1:
    pcVar11 = "word ptr ";
    *(undefined1 *)(param_1 + 0x328) = 2;
    goto LAB_001e4028;
  case 2:
    pcVar11 = "dword ptr ";
    *(undefined1 *)(param_1 + 0x328) = 4;
LAB_001e4028:
    SStream_concat0(param_2,pcVar11);
    printMemReference(param_1,2,param_2);
    break;
  case 3:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e3d30;
  case 4:
    SStream_concat0(param_2,"byte ptr ");
    uVar3 = 1;
    goto LAB_001e3d30;
  case 5:
  case 8:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
LAB_001e3d30:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,2,param_2);
    break;
  case 6:
    if ((*(char *)(param_1 + 6) == '\x10') &&
       ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
    }
    else {
      uVar3 = 8;
      SStream_concat0(param_2,"qword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,2,param_2);
    break;
  case 7:
    iVar7 = MCInst_getOpcode(param_1);
    if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
      iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar7 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar7 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      SStream_concat0(param_2,"dword ptr ");
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    printMemReference(param_1,2,param_2);
    break;
  case 9:
  case 0x13:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e3cd4;
  case 10:
    printOperand(param_1,1,param_2);
    break;
  case 0xb:
    pcVar11 = "dword ptr ";
    *(undefined1 *)(param_1 + 0x328) = 4;
    goto LAB_001e3dc4;
  case 0xc:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e3cd4;
  case 0xd:
    uVar5 = *(uint *)(param_1 + 8);
    if (uVar5 < 0x4e2) {
      if (uVar5 < 0x4e0) {
        if (uVar5 < 0x19b) {
          if ((0x184 < uVar5) && ((0x201555UL >> ((ulong)(uVar5 - 0x185) & 0x3f) & 1) != 0)) {
            *(undefined1 *)(param_1 + 0x328) = 0x10;
          }
        }
        else if (uVar5 == 0x4df) {
          *(undefined1 *)(param_1 + 0x328) = 2;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x328) = 4;
      }
    }
    else if (uVar5 == 0x4e2) {
      *(undefined1 *)(param_1 + 0x328) = 8;
    }
    printMemReference(param_1,1,param_2);
    goto switchD_001e2c60_default;
  case 0xe:
    pcVar11 = "word ptr ";
    *(undefined1 *)(param_1 + 0x328) = 2;
LAB_001e3dc4:
    SStream_concat0(param_2,pcVar11);
    printMemReference(param_1,1,param_2);
    break;
  case 0xf:
    SStream_concat0(param_2,"byte ptr ");
    *(undefined1 *)(param_1 + 0x328) = 1;
    printMemReference(param_1,1,param_2);
    goto switchD_001e2c60_default;
  case 0x11:
    if ((*(char *)(param_1 + 6) == '\x10') &&
       ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
    }
    else {
      uVar3 = 8;
      SStream_concat0(param_2,"qword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,1,param_2);
    break;
  case 0x12:
    iVar7 = MCInst_getOpcode(param_1);
    if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
      iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar7 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar7 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      SStream_concat0(param_2,"dword ptr ");
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    printMemReference(param_1,1,param_2);
    break;
  case 0x14:
    printU8Imm(param_1,2,param_2);
    break;
  case 0x15:
    printOperand(param_1,0,param_2);
    goto switchD_001e2c60_default;
  case 0x16:
    printopaquemem(param_1,1,param_2);
    goto switchD_001e2c60_default;
  case 0x17:
  case 0x20:
    SStream_concat0(param_2,"zmmword ptr ");
    uVar3 = 0x40;
    goto LAB_001e3cd4;
  case 0x18:
    SStream_concat0(param_2,"byte ptr ");
    uVar3 = 1;
    goto LAB_001e3e84;
  case 0x19:
    SStream_concat0(param_2,"dword ptr ");
    uVar3 = 4;
    goto LAB_001e3e84;
  case 0x1a:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
    goto LAB_001e3e84;
  case 0x1b:
    SStream_concat0(param_2,"word ptr ");
    uVar3 = 2;
LAB_001e3e84:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printSrcIdx(param_1,1,param_2);
    goto switchD_001e2c60_default;
  case 0x1c:
    goto switchD_001e3cbc_caseD_1c;
  case 0x1d:
  case 0x1e:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
LAB_001e3cd4:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,1,param_2);
    break;
  case 0x1f:
    SStream_concat0(param_2,&DAT_001fde50);
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fe650);
    printOperand(param_1,2,param_2);
  case 0x10:
    SStream_concat0(param_2,", ");
    break;
  case 0x21:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
    goto LAB_001e3f88;
  case 0x22:
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,&DAT_001fe650);
    break;
  case 0x23:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e3f88;
  case 0x24:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
LAB_001e3f88:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,8,param_2);
    goto switchD_001e2c60_default;
  default:
    goto switchD_001e3cbc_default;
  }
LAB_001e2e70:
  uVar9 = (CONCAT44(uVar5,uVar8) >> 0x1f & 0x3f) - 1;
  if (0x22 < uVar9) goto switchD_001e2c60_default;
  switch(uVar9 & 0xffffffff) {
  case 0:
    goto switchD_001e2e9c_caseD_0;
  case 1:
    SStream_concat0(param_2,", xmm0");
    break;
  case 2:
    SStream_concat0(param_2,"xmmword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    printMemReference(param_1,2,param_2);
    break;
  case 3:
    printOperand(param_1,2,param_2);
    break;
  case 4:
    if ((*(char *)(param_1 + 6) == '\x10') &&
       ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
    }
    else {
      uVar3 = 8;
      SStream_concat0(param_2,"qword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,2,param_2);
    break;
  case 5:
    iVar7 = MCInst_getOpcode(param_1);
    if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
      iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar7 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar7 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      SStream_concat0(param_2,"dword ptr ");
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    printMemReference(param_1,2,param_2);
    break;
  case 6:
switchD_001e2dc0_caseD_c:
    SStream_concat0(param_2,&DAT_00203a28);
    op_addReg(param_1,10);
    break;
  case 7:
    SStream_concat0(param_2,&DAT_001fe650);
    goto LAB_001e3908;
  case 8:
    SStream_concat0(param_2,"} {z}, ");
    op_addAvxZeroOpmask(param_1);
    goto LAB_001e3908;
  case 9:
    printOperand(param_1,1,param_2);
    goto switchD_001e2e9c_caseD_0;
  case 10:
    if ((*(char *)(param_1 + 6) == '\x10') &&
       ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
    }
    else {
      uVar3 = 8;
      SStream_concat0(param_2,"qword ptr ");
    }
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,3,param_2);
    goto LAB_001e3908;
  case 0xb:
  case 0x1e:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e38a0;
  case 0xc:
    printOperand(param_1,3,param_2);
    goto LAB_001e3908;
  case 0xd:
  case 0x1f:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
    goto LAB_001e38a0;
  case 0xe:
  case 0x20:
    SStream_concat0(param_2,"zmmword ptr ");
    uVar3 = 0x40;
    goto LAB_001e38a0;
  case 0xf:
    iVar7 = MCInst_getOpcode(param_1);
    if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
      iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
      if ((iVar7 - 4U & 0xfffffffb) == 0) {
        *(undefined1 *)(param_1 + 0x328) = 0x1c;
      }
      else if (iVar7 == 2) {
        *(undefined1 *)(param_1 + 0x328) = 0xe;
      }
    }
    else {
      SStream_concat0(param_2,"dword ptr ");
      *(undefined1 *)(param_1 + 0x328) = 4;
    }
    printMemReference(param_1,3,param_2);
    goto LAB_001e3908;
  case 0x10:
    goto switchD_001e2e9c_caseD_10;
  case 0x11:
    goto switchD_001e2e9c_caseD_11;
  case 0x12:
    goto switchD_001e2e9c_caseD_12;
  case 0x13:
    goto switchD_001e2e9c_caseD_13;
  case 0x14:
    goto switchD_001e2e9c_caseD_14;
  case 0x15:
    SStream_concat0(param_2,", {sae}, ");
    op_addAvxSae(param_1);
    printU8Imm(param_1,2,param_2);
    break;
  case 0x16:
    SStream_concat0(param_2,"{1to2}, ");
    uVar10 = 1;
    goto LAB_001e39e0;
  case 0x17:
    SStream_concat0(param_2,"{1to4}, ");
    uVar10 = 2;
    goto LAB_001e39e0;
  case 0x18:
    SStream_concat0(param_2,"{1to8}, ");
    uVar10 = 3;
    goto LAB_001e39e0;
  case 0x19:
    SStream_concat0(param_2,"{1to16}, ");
    uVar10 = 4;
LAB_001e39e0:
    op_addAvxBroadcast(param_1,uVar10);
    printU8Imm(param_1,6,param_2);
    break;
  case 0x1a:
    SStream_concat0(param_2,"xmmword ptr ");
    uVar3 = 0x10;
    goto LAB_001e3b64;
  case 0x1b:
    SStream_concat0(param_2,"ymmword ptr ");
    uVar3 = 0x20;
    goto LAB_001e3b64;
  case 0x1c:
    SStream_concat0(param_2,"zmmword ptr ");
    uVar3 = 0x40;
    goto LAB_001e3b64;
  case 0x1d:
    SStream_concat0(param_2,"qword ptr ");
    uVar3 = 8;
LAB_001e3b64:
    *(undefined1 *)(param_1 + 0x328) = uVar3;
    printMemReference(param_1,4,param_2);
    break;
  case 0x21:
    *(undefined1 *)(param_1 + 0x328) = 4;
    SStream_concat0(param_2,"dword ptr ");
    printMemReference(param_1,3,param_2);
    goto LAB_001e3908;
  case 0x22:
    SStream_concat0(param_2,"qword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 8;
    printMemReference(param_1,3,param_2);
LAB_001e3908:
    uVar9 = ((ulong)(uVar5 >> 5) & 0x3f) - 1;
    if (0x25 < uVar9) {
switchD_001e4194_default:
      printU8Imm(param_1,6,param_2);
      break;
    }
    switch(uVar9 & 0xffffffff) {
    case 0:
      printU8Imm(param_1,2,param_2);
      goto switchD_001e2c60_default;
    case 1:
      pcVar11 = "dword ptr ";
      *(undefined1 *)(param_1 + 0x328) = 4;
      goto LAB_001e4570;
    case 2:
      printOperand(param_1,2,param_2);
      break;
    case 3:
      SStream_concat0(param_2,"qword ptr ");
      uVar3 = 8;
      goto LAB_001e42f4;
    case 4:
      printOperand(param_1,6,param_2);
      break;
    case 5:
      goto switchD_001e4194_caseD_5;
    case 6:
      printU8Imm(param_1,3,param_2);
      break;
    case 7:
    case 0x14:
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
      goto LAB_001e41ac;
    case 8:
      printOperand(param_1,3,param_2);
      break;
    case 9:
    case 0xe:
      SStream_concat0(param_2,"ymmword ptr ");
      uVar3 = 0x20;
      goto LAB_001e42f4;
    case 10:
    case 0xf:
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
      goto LAB_001e42f4;
    case 0xb:
      if ((*(char *)(param_1 + 6) == '\x10') &&
         ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
        SStream_concat0(param_2,"xmmword ptr ");
        uVar3 = 0x10;
      }
      else {
        uVar3 = 8;
        SStream_concat0(param_2,"qword ptr ");
      }
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,2,param_2);
      break;
    case 0xc:
    case 0x10:
      SStream_concat0(param_2,"zmmword ptr ");
      uVar3 = 0x40;
      goto LAB_001e42f4;
    case 0xd:
      iVar7 = MCInst_getOpcode(param_1);
      if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
        iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
        if ((iVar7 - 4U & 0xfffffffb) == 0) {
          *(undefined1 *)(param_1 + 0x328) = 0x1c;
        }
        else if (iVar7 == 2) {
          *(undefined1 *)(param_1 + 0x328) = 0xe;
        }
      }
      else {
        SStream_concat0(param_2,"dword ptr ");
        *(undefined1 *)(param_1 + 0x328) = 4;
      }
      printMemReference(param_1,2,param_2);
      break;
    case 0x11:
      if ((*(char *)(param_1 + 6) == '\x10') &&
         ((iVar7 = MCInst_getOpcode(param_1), iVar7 == 0x2c9 || (iVar7 == 0x68b)))) {
        SStream_concat0(param_2,"xmmword ptr ");
        uVar3 = 0x10;
      }
      else {
        uVar3 = 8;
        SStream_concat0(param_2,"qword ptr ");
      }
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,3,param_2);
      break;
    case 0x12:
    case 0x15:
      SStream_concat0(param_2,"ymmword ptr ");
      uVar3 = 0x20;
      goto LAB_001e41ac;
    case 0x13:
      SStream_concat0(param_2,"qword ptr ");
      uVar3 = 8;
      goto LAB_001e41ac;
    case 0x16:
      iVar7 = MCInst_getOpcode(param_1);
      if ((iVar7 == 0x39b) || (iVar7 == 0x3b2)) {
        iVar7 = *(int *)(*(long *)(param_1 + 800) + 4);
        if ((iVar7 - 4U & 0xfffffffb) == 0) {
          *(undefined1 *)(param_1 + 0x328) = 0x1c;
        }
        else if (iVar7 == 2) {
          *(undefined1 *)(param_1 + 0x328) = 0xe;
        }
      }
      else {
        SStream_concat0(param_2,"dword ptr ");
        *(undefined1 *)(param_1 + 0x328) = 4;
      }
      printMemReference(param_1,3,param_2);
      break;
    case 0x17:
      goto switchD_001e2e9c_caseD_11;
    case 0x18:
      goto switchD_001e2c60_default;
    case 0x19:
      goto switchD_001e2e9c_caseD_12;
    case 0x1a:
      goto switchD_001e2e9c_caseD_13;
    case 0x1b:
      goto switchD_001e2e9c_caseD_10;
    case 0x1c:
      goto switchD_001e2e9c_caseD_14;
    case 0x1d:
      *(undefined1 *)(param_1 + 0x328) = 4;
      SStream_concat0(param_2,"dword ptr ");
      printMemReference(param_1,3,param_2);
      break;
    case 0x1e:
    case 0x20:
      SStream_concat0(param_2,"zmmword ptr ");
      uVar3 = 0x40;
LAB_001e41ac:
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,3,param_2);
      break;
    case 0x1f:
      printRoundingControl(param_1,2,param_2);
      goto switchD_001e2c60_default;
    case 0x21:
      printRoundingControl(param_1,3,param_2);
LAB_001e350c:
      SStream_concat0(param_2,", ");
      printOperand(param_1,2,param_2);
      goto switchD_001e2c60_default;
    case 0x22:
      SStream_concat0(param_2,"byte ptr ");
      uVar3 = 1;
LAB_001e42f4:
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,2,param_2);
      break;
    case 0x23:
      SStream_concat0(param_2,"byte ptr ");
      uVar3 = 1;
LAB_001e38a0:
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,3,param_2);
      goto switchD_001e2c60_default;
    case 0x24:
      *(undefined1 *)(param_1 + 0x328) = 2;
      SStream_concat0(param_2,"word ptr ");
      printMemReference(param_1,3,param_2);
      goto switchD_001e2c60_default;
    case 0x25:
      pcVar11 = "word ptr ";
      *(undefined1 *)(param_1 + 0x328) = 2;
LAB_001e4570:
      SStream_concat0(param_2,pcVar11);
      printMemReference(param_1,2,param_2);
      break;
    default:
      goto switchD_001e4194_default;
    }
    uVar9 = ((ulong)(uVar5 >> 0xb) & 0xf) - 1;
    if (10 < uVar9) break;
    switch(uVar9 & 0xffffffff) {
    case 0:
      SStream_concat0(param_2,", ");
      break;
    case 1:
      goto switchD_001e2e9c_caseD_11;
    case 2:
      goto switchD_001e2e9c_caseD_12;
    case 3:
      goto switchD_001e2e9c_caseD_13;
    case 4:
      goto switchD_001e2e9c_caseD_14;
    case 5:
      SStream_concat0(param_2,"{1to4}, ");
      op_addAvxBroadcast(param_1,2);
      break;
    case 6:
      SStream_concat0(param_2,"{1to8}, ");
      op_addAvxBroadcast(param_1,3);
      break;
    case 7:
      SStream_concat0(param_2,"{1to16}, ");
      op_addAvxBroadcast(param_1,4);
      break;
    case 8:
      SStream_concat0(param_2,"{1to2}, ");
      op_addAvxBroadcast(param_1,1);
      break;
    case 9:
      goto switchD_001e2e9c_caseD_10;
    case 10:
      SStream_concat0(param_2,", {sae}, ");
      op_addAvxSae(param_1);
      break;
    default:
      goto switchD_001e2c60_default;
    }
    uVar9 = ((ulong)(uVar5 >> 0xf) & 0x1f) - 1;
    if (0x1d < uVar9) goto switchD_001e4634_default;
    switch(uVar9 & 0xffffffff) {
    case 0:
    case 0x10:
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
      goto LAB_001e4784;
    case 1:
      printf64mem(param_1,4,param_2);
      break;
    case 2:
      printf64mem(param_1,3,param_2);
      break;
    case 3:
    case 0x11:
      SStream_concat0(param_2,"xmmword ptr ");
      uVar3 = 0x10;
      goto LAB_001e464c;
    case 4:
      printOperand(param_1,4,param_2);
      break;
    case 5:
      printOperand(param_1,3,param_2);
      break;
    case 6:
    case 0x13:
      SStream_concat0(param_2,"ymmword ptr ");
      uVar3 = 0x20;
      goto LAB_001e4784;
    case 7:
    case 0x14:
      SStream_concat0(param_2,"ymmword ptr ");
      uVar3 = 0x20;
      goto LAB_001e464c;
    case 8:
    case 0x15:
      SStream_concat0(param_2,"zmmword ptr ");
      uVar3 = 0x40;
      goto LAB_001e4784;
    case 9:
    case 0x16:
      SStream_concat0(param_2,"zmmword ptr ");
      uVar3 = 0x40;
      goto LAB_001e464c;
    case 10:
      printRoundingControl(param_1,3,param_2);
      goto switchD_001e2c60_default;
    case 0xb:
      printf32mem(param_1,4,param_2);
      break;
    case 0xc:
      printf32mem(param_1,3,param_2);
      break;
    case 0xd:
switchD_001e4194_caseD_5:
      printU8Imm(param_1,7,param_2);
      goto switchD_001e2c60_default;
    case 0xe:
      *(undefined1 *)(param_1 + 0x328) = 4;
      SStream_concat0(param_2,"dword ptr ");
      printMemReference(param_1,4,param_2);
      break;
    case 0xf:
      *(undefined1 *)(param_1 + 0x328) = 4;
      SStream_concat0(param_2,"dword ptr ");
      printMemReference(param_1,3,param_2);
      break;
    case 0x12:
      printU8Imm(param_1,3,param_2);
      goto switchD_001e2c60_default;
    case 0x17:
      SStream_concat0(param_2,"qword ptr ");
      uVar3 = 8;
      goto LAB_001e4784;
    case 0x18:
      SStream_concat0(param_2,"qword ptr ");
      uVar3 = 8;
      goto LAB_001e464c;
    case 0x19:
      printOperand(param_1,7,param_2);
      break;
    case 0x1a:
      goto switchD_001e4634_caseD_1a;
    case 0x1b:
      goto switchD_001e4634_caseD_1b;
    case 0x1c:
      SStream_concat0(param_2,"byte ptr ");
      uVar3 = 1;
LAB_001e4784:
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,4,param_2);
      break;
    case 0x1d:
      SStream_concat0(param_2,"byte ptr ");
      uVar3 = 1;
LAB_001e464c:
      *(undefined1 *)(param_1 + 0x328) = uVar3;
      printMemReference(param_1,3,param_2);
      break;
    default:
      goto switchD_001e4634_default;
    }
    uVar9 = ((ulong)(uVar5 >> 0x14) & 0xf) - 1;
    if (10 < uVar9) break;
    switch(uVar9 & 0xffffffff) {
    case 0:
switchD_001e2e9c_caseD_11:
      SStream_concat0(param_2,"{1to2}");
      break;
    case 1:
switchD_001e2e9c_caseD_12:
      SStream_concat0(param_2,"{1to4}");
      break;
    case 2:
switchD_001e2e9c_caseD_13:
      SStream_concat0(param_2,"{1to8}");
      break;
    case 3:
      SStream_concat0(param_2,", ");
      goto LAB_001e46a8;
    case 4:
switchD_001e2e9c_caseD_14:
      SStream_concat0(param_2,"{1to16}");
      break;
    case 5:
      SStream_concat0(param_2,"{1to4}, ");
      op_addAvxBroadcast(param_1,2);
      goto LAB_001e46a8;
    case 6:
      SStream_concat0(param_2,"{1to8}, ");
      op_addAvxBroadcast(param_1,3);
      goto LAB_001e46a8;
    case 7:
      SStream_concat0(param_2,"{1to16}, ");
      op_addAvxBroadcast(param_1,4);
      goto LAB_001e46a8;
    case 8:
      SStream_concat0(param_2,"{1to2}, ");
      op_addAvxBroadcast(param_1,1);
      goto LAB_001e46a8;
    case 9:
      SStream_concat0(param_2,", {sae}, ");
      op_addAvxSae(param_1);
LAB_001e46a8:
      uVar8 = uVar5 >> 0x18 & 7;
      if (uVar8 == 3) {
switchD_001e4634_caseD_1b:
        printU8Imm(param_1,8,param_2);
      }
      else if ((uVar5 >> 0x1a & 1) == 0) {
        if (uVar8 == 1) {
switchD_001e4634_caseD_1a:
          printRoundingControl(param_1,4,param_2);
        }
        else if (uVar8 == 2) {
          printU8Imm(param_1,9,param_2);
        }
        else {
LAB_001e4ac8:
          printRoundingControl(param_1,5,param_2);
        }
      }
      else if (uVar8 == 4) {
switchD_001e3cbc_caseD_1c:
        printU8Imm(param_1,5,param_2);
      }
      else {
        if (uVar8 != 5) goto LAB_001e4ac8;
switchD_001e4634_default:
        printU8Imm(param_1,4,param_2);
      }
      break;
    case 10:
switchD_001e2e9c_caseD_10:
      SStream_concat0(param_2,", {sae}");
      op_addAvxSae(param_1);
    }
  }
switchD_001e2c60_default:
  uVar10 = MCInst_getOpcode(param_1);
  uVar5 = X86_insn_reg_intel(uVar10,local_58);
  local_60 = uVar5;
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    local_50 = 0;
    local_4c = 0;
    if (uVar5 == 0) {
      uVar10 = MCInst_getOpcode(param_1);
      uVar9 = X86_insn_reg_intel2(uVar10,&local_60,local_58,&uStack_5c,local_54);
      if ((uVar9 & 1) == 0) {
        lVar17 = *(long *)(param_1 + 800);
      }
      else {
        lVar17 = *(long *)(param_1 + 800);
        lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar14 = *(long *)(lVar17 + 0xa0);
        *(undefined4 *)(lVar12 + 0xa8) = 1;
        *(uint *)(lVar12 + 0xb0) = local_60;
        *(undefined1 *)(lVar12 + 200) = *(undefined1 *)(lVar14 + (ulong)local_60);
        *(undefined1 *)(lVar12 + 0xc9) = local_58[0];
        *(undefined4 *)(lVar12 + 0xd8) = 1;
        *(uint *)(lVar12 + 0xe0) = uStack_5c;
        uVar3 = *(undefined1 *)(lVar14 + (ulong)uStack_5c);
        *(undefined1 *)(lVar12 + 0xa0) = 2;
        *(undefined1 *)(lVar12 + 0xf8) = uVar3;
        *(undefined1 *)(lVar12 + 0xf9) = local_54[0];
      }
    }
    else {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      memmove((void *)(lVar12 + 0xd8),(void *)(lVar12 + 0xa8),0x150);
      lVar17 = *(long *)(param_1 + 800);
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar14 = *(long *)(lVar17 + 0xa0);
      *(undefined4 *)(lVar12 + 0xa8) = 1;
      *(uint *)(lVar12 + 0xb0) = uVar5;
      uVar3 = *(undefined1 *)(lVar14 + (ulong)uVar5);
      *(char *)(lVar12 + 0xa0) = *(char *)(lVar12 + 0xa0) + '\x01';
      *(undefined1 *)(lVar12 + 200) = uVar3;
      *(undefined1 *)(lVar12 + 0xc9) = local_58[0];
    }
    uVar6 = MCInst_getOpcode(param_1);
    pcVar11 = (char *)X86_get_op_access(lVar17,uVar6,
                                        *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar11 == (char *)0x0) {
      uVar13 = 0;
      uVar3 = 0;
    }
    else {
      cVar4 = *pcVar11;
      puVar16 = &local_50;
      if (cVar4 != '\0') {
        uVar9 = 0;
        uVar5 = 0;
        do {
          while (cVar4 != -0x80) {
            uVar8 = uVar5 + 1;
            *(char *)((long)puVar16 + uVar9) = cVar4;
            uVar5 = uVar8 & 0xff;
            uVar9 = (ulong)uVar8 & 0xff;
            cVar4 = pcVar11[uVar5];
            if (cVar4 == '\0') goto LAB_001e2bd8;
          }
          uVar8 = uVar5 + 1;
          *(undefined1 *)((long)puVar16 + uVar9) = 0;
          uVar5 = uVar8 & 0xff;
          uVar9 = (ulong)uVar8 & 0xff;
          cVar4 = pcVar11[uVar5];
        } while (cVar4 != '\0');
LAB_001e2bd8:
        puVar16 = (undefined4 *)((long)puVar16 + uVar9);
      }
      *(undefined1 *)puVar16 = 0;
      uVar13 = local_50._1_1_;
      uVar3 = (undefined1)local_50;
    }
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined1 *)(lVar12 + 0xc9) = uVar3;
    *(undefined1 *)(lVar12 + 0xf9) = uVar13;
  }
  if ((*(char *)(param_1 + 6) == '\0') && (local_60 != 0)) {
    *(undefined1 *)(param_1 + 6) =
         *(undefined1 *)(*(long *)(*(long *)(param_1 + 800) + 0xa0) + (ulong)local_60);
  }
  lVar12 = local_48 - *(long *)PTR___stack_chk_guard_005ffe88;
  if (lVar12 == 0) {
    return;
  }
LAB_001e4c60:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar12);
switchD_001e2e9c_caseD_0:
  SStream_concat0(param_2,", ");
  goto LAB_001e3908;
}

