
/* WARNING: Type propagation algorithm not settling */

void printMemReference(long param_1,ulong param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  bool bVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined8 uVar9;
  long lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulong uVar14;
  char *pcVar15;
  char *pcVar16;
  long lVar17;
  char cVar18;
  undefined8 uVar19;
  char local_70 [8];
  long local_68;
  
  iVar3 = (int)param_2;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar9 = MCInst_getOperand(param_1,param_2,0);
  MCInst_getOperand(param_1,iVar3 + 1);
  lVar10 = MCOperand_getImm();
  uVar11 = MCInst_getOperand(param_1,iVar3 + 2);
  uVar12 = MCInst_getOperand(param_1,iVar3 + 3);
  uVar13 = MCInst_getOperand(param_1,iVar3 + 4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar6 = MCOperand_getReg(uVar13);
  }
  else {
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar17 = lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30;
    *(undefined4 *)(lVar17 + 0xa8) = 3;
    uVar5 = *(undefined1 *)(param_1 + 0x328);
    *(undefined4 *)(lVar17 + 0xb0) = 0;
    *(undefined1 *)(lVar17 + 200) = uVar5;
    MCOperand_getReg(uVar9);
    uVar8 = X86_register_map();
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(uint *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xb4) = uVar8 & 0xffff;
    iVar6 = MCOperand_getReg(uVar11);
    if (iVar6 == 0x1e) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar14 = (ulong)*(byte *)(lVar17 + 0xa0);
    }
    else {
      MCOperand_getReg(uVar11);
      uVar8 = X86_register_map();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar14 = (ulong)*(byte *)(lVar17 + 0xa0);
      *(uint *)(lVar17 + uVar14 * 0x30 + 0xb8) = uVar8 & 0xffff;
    }
    uVar19 = *(undefined8 *)(param_1 + 800);
    lVar17 = lVar17 + uVar14 * 0x30;
    *(int *)(lVar17 + 0xbc) = (int)lVar10;
    *(undefined8 *)(lVar17 + 0xc0) = 0;
    uVar7 = MCInst_getOpcode(param_1);
    pcVar15 = (char *)X86_get_op_access(uVar19,uVar7,
                                        *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar15 == (char *)0x0) {
      local_70[0] = '\0';
    }
    else {
      cVar18 = *pcVar15;
      pcVar16 = local_70;
      uVar8 = 0;
      uVar14 = 0;
      if (cVar18 != '\0') {
        do {
          while (cVar18 != -0x80) {
            uVar1 = uVar8 + 1;
            pcVar16[uVar14] = cVar18;
            uVar8 = uVar1 & 0xff;
            uVar14 = (ulong)uVar1 & 0xff;
            cVar18 = pcVar15[uVar8];
            if (cVar18 == '\0') {
              pcVar16 = pcVar16 + uVar14;
              goto LAB_001e1284;
            }
          }
          uVar1 = uVar8 + 1;
          pcVar16[uVar14] = '\0';
          uVar8 = uVar1 & 0xff;
          uVar14 = (ulong)uVar1 & 0xff;
          cVar18 = pcVar15[uVar8];
        } while (cVar18 != '\0');
        pcVar16 = pcVar16 + uVar14;
      }
LAB_001e1284:
      *pcVar16 = '\0';
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar17 + 0xa0);
    *(char *)(lVar17 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc9) = local_70[(int)(uint)bVar2]
    ;
    iVar6 = MCOperand_getReg(uVar13);
  }
  if (iVar6 == 0) {
    SStream_concat0(param_3,&DAT_001fd940);
    iVar6 = MCOperand_getReg(uVar9);
  }
  else {
    _printOperand(param_1,iVar3 + 4,param_3);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar8 = X86_register_map(iVar6);
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xb0) = uVar8 & 0xffff;
    }
    SStream_concat0(param_3,&DAT_001fd7d0);
    SStream_concat0(param_3,&DAT_001fd940);
    iVar6 = MCOperand_getReg(uVar9);
  }
  bVar4 = iVar6 != 0;
  if (bVar4) {
    _printOperand(param_1,param_2 & 0xffffffff,param_3);
    iVar6 = MCOperand_getReg(uVar11);
  }
  else {
    iVar6 = MCOperand_getReg(uVar11);
  }
  if ((iVar6 == 0) || (iVar6 = MCOperand_getReg(uVar11), iVar6 == 0x1e)) {
    uVar14 = MCOperand_isImm(uVar12);
  }
  else {
    if (bVar4) {
      SStream_concat0(param_3,&DAT_002032f8);
    }
    _printOperand(param_1,iVar3 + 2,param_3);
    if (lVar10 != 1) {
      SStream_concat(param_3,&DAT_00203300,lVar10);
    }
    bVar4 = true;
    uVar14 = MCOperand_isImm(uVar12);
  }
  if ((uVar14 & 1) != 0) {
    uVar14 = MCOperand_getImm(uVar12);
    lVar10 = *(long *)(param_1 + 800);
    if (*(int *)(lVar10 + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xc0) = uVar14;
    }
    if (uVar14 == 0) {
      if (!bVar4) {
        SStream_concat0(param_3,&DAT_001ff7d8);
      }
    }
    else if (bVar4) {
      if ((long)uVar14 < 0) {
        SStream_concat0(param_3,&DAT_00203308);
        printImm_isra_0(*(undefined1 *)(param_1 + 6),*(undefined8 *)(param_1 + 800),param_3,-uVar14,
                        1);
      }
      else {
        SStream_concat0(param_3,&DAT_002032f8);
        printImm_isra_0(*(undefined1 *)(param_1 + 6),*(undefined8 *)(param_1 + 800),param_3,uVar14,1
                       );
      }
    }
    else {
      uVar8 = *(uint *)(lVar10 + 4);
      if (uVar8 == 8) {
        *(undefined1 *)(param_1 + 6) = 8;
        uVar5 = 8;
      }
      else {
        uVar5 = *(undefined1 *)(param_1 + 6);
      }
      if ((long)uVar14 < 0) {
        printImm_isra_0(uVar5,lVar10,param_3,
                        uVar14 & *(ulong *)(PTR_arch_masks_005ffe50 + (ulong)uVar8 * 8),1);
      }
      else {
        printImm_isra_0(uVar5,lVar10,param_3,uVar14,1);
      }
    }
  }
  SStream_concat0(param_3,&DAT_001fdf58);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar10 + 0xa0) = *(char *)(lVar10 + 0xa0) + '\x01';
  }
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x328);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

