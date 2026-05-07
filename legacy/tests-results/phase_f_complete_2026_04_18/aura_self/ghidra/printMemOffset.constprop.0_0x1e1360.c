
void printMemOffset_constprop_0(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulong uVar9;
  char *pcVar10;
  char *pcVar11;
  long lVar12;
  char cVar13;
  long lVar14;
  char local_50 [8];
  long local_48;
  
  pcVar11 = local_50;
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar7 = MCInst_getOperand(param_1,0);
  uVar8 = MCInst_getOperand(param_1,1);
  lVar14 = *(long *)(param_1 + 800);
  if (*(int *)(lVar14 + 0x60) == 0) {
    iVar4 = MCOperand_getReg(uVar8);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30;
    *(undefined4 *)(lVar12 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar12 + 0xb0) = 0;
    *(undefined8 *)(lVar12 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar12 + 0xc0) = 0;
    *(undefined1 *)(lVar12 + 200) = uVar2;
    uVar5 = MCInst_getOpcode(param_1);
    pcVar10 = (char *)X86_get_op_access(lVar14,uVar5,
                                        *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar10 == (char *)0x0) {
      local_50[0] = '\0';
    }
    else {
      cVar13 = *pcVar10;
      uVar6 = 0;
      uVar9 = 0;
      if (cVar13 != '\0') {
        do {
          while( true ) {
            uVar1 = uVar6 + 1;
            if (cVar13 == -0x80) break;
            uVar6 = uVar1 & 0xff;
            local_50[uVar9] = cVar13;
            uVar9 = (ulong)uVar1 & 0xff;
            cVar13 = pcVar10[uVar6];
            if (cVar13 == '\0') {
              pcVar11 = local_50 + uVar9;
              goto LAB_001e14ec;
            }
          }
          uVar6 = uVar1 & 0xff;
          local_50[uVar9] = '\0';
          uVar9 = (ulong)uVar1 & 0xff;
          cVar13 = pcVar10[uVar6];
        } while (cVar13 != '\0');
        pcVar11 = local_50 + uVar9;
      }
LAB_001e14ec:
      *pcVar11 = '\0';
    }
    lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar14 + 0xa0);
    *(char *)(lVar14 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10 + 0xc9) = local_50[(int)(uint)bVar3]
    ;
    iVar4 = MCOperand_getReg(uVar8);
  }
  if (iVar4 != 0) {
    _printOperand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fde30);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar6 = X86_register_map(iVar4);
      lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar14 + (ulong)*(byte *)(lVar14 + 0xa0) * 0x30 + 0xb0) = uVar6 & 0xffff;
      SStream_concat0(param_2,&DAT_001fdfa0);
      uVar9 = MCOperand_isImm(uVar7);
      goto joined_r0x001e1588;
    }
  }
  SStream_concat0(param_2,&DAT_001fdfa0);
  uVar9 = MCOperand_isImm(uVar7);
joined_r0x001e1588:
  if ((uVar9 & 1) != 0) {
    uVar9 = MCOperand_getImm(uVar7);
    lVar14 = *(long *)(param_1 + 800);
    if (*(int *)(lVar14 + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30 + 0xc0) = uVar9;
    }
    if ((long)uVar9 < 0) {
      printImm_isra_0(*(undefined1 *)(param_1 + 6),lVar14,param_2,
                      uVar9 & *(ulong *)(PTR_arch_masks_005ffe50 + (ulong)*(uint *)(lVar14 + 4) * 8)
                      ,1);
    }
    else {
      printImm_isra_0(*(undefined1 *)(param_1 + 6),lVar14,param_2,uVar9,1);
    }
  }
  SStream_concat0(param_2,&DAT_001fe5b8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar14 + 0xa0) = *(char *)(lVar14 + 0xa0) + '\x01';
  }
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x328);
  }
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

