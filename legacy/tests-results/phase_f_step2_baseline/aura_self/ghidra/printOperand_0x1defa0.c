
void printOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined8 uVar8;
  ulong uVar9;
  char *pcVar10;
  ulong uVar11;
  char cVar12;
  long lVar13;
  char *pcVar14;
  int *piVar15;
  long lVar16;
  undefined1 local_51;
  char local_50 [8];
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar8 = MCInst_getOperand(param_1,param_2,0);
  uVar9 = MCOperand_isReg();
  if ((uVar9 & 1) == 0) {
    uVar9 = MCOperand_isImm(uVar8);
    if ((uVar9 & 1) == 0) goto LAB_001df130;
    uVar11 = MCOperand_getImm(uVar8);
    uVar8 = MCInst_getOpcode(param_1);
    uVar4 = X86_immediate_size(uVar8,&local_51);
    uVar4 = uVar4 & 0xff;
    uVar3 = *(undefined1 *)(param_1 + 6);
    uVar9 = uVar11 & 0xff;
    if (uVar4 != 1) {
      uVar9 = uVar11;
    }
    uVar6 = **(uint **)(param_1 + 0x310);
    if (uVar6 < 0x1ce) {
      if (uVar6 < 0x1cc) {
        if (0xac < uVar6) {
          if (uVar6 != 0xee) {
            if (uVar6 == 0x15f) goto LAB_001df3d8;
            if (uVar6 != 0xe5) goto LAB_001df3b8;
          }
LAB_001df36c:
          uVar9 = uVar9 & 0xff;
          printImm_isra_0(uVar3,*(undefined8 *)(param_1 + 800),param_3,uVar9,1);
          goto LAB_001df1f4;
        }
        if (uVar6 < 0xaa) {
          if (uVar6 == 0x18) goto LAB_001df424;
          goto LAB_001df3b8;
        }
        uVar4 = 4;
        if ((int)param_2 == 1) {
          uVar9 = uVar9 & 0xffff;
          uVar4 = 2;
        }
      }
      printImm_isra_0(uVar3,*(undefined8 *)(param_1 + 800),param_3,uVar9,1);
    }
    else if (uVar6 == 0x279) {
LAB_001df3d8:
      uVar8 = *(undefined8 *)(param_1 + 800);
      if (uVar9 < 10) {
LAB_001df460:
        printImm_isra_0(uVar3,uVar8,param_3,uVar9,1);
      }
      else {
        uVar9 = uVar9 & 0xffff;
        printImm_isra_0(uVar3,uVar8,param_3,uVar9,1);
      }
    }
    else {
      if (uVar6 < 0x27a) {
        if (uVar6 == 0x200) {
LAB_001df424:
          uVar8 = *(undefined8 *)(param_1 + 800);
          if (uVar9 < 10) goto LAB_001df460;
          uVar6 = uVar4;
          if (uVar4 == 0) {
            uVar6 = (uint)*(byte *)(param_1 + 0x334);
          }
          uVar9 = uVar9 & *(ulong *)(PTR_arch_masks_005ffe50 + (long)(int)uVar6 * 8);
          printImm_isra_0(uVar3,uVar8,param_3,uVar9,1);
          goto LAB_001df1f4;
        }
        if (uVar6 == 0x203) goto LAB_001df36c;
      }
      else if (uVar6 == 0x5df) goto LAB_001df424;
LAB_001df3b8:
      printImm_isra_0(uVar3,*(long *)(param_1 + 800),param_3,uVar9,
                      *(int *)(*(long *)(param_1 + 800) + 100) != 0);
    }
LAB_001df1f4:
    lVar13 = *(long *)(param_1 + 800);
    if (*(int *)(lVar13 + 0x60) != 0) {
      piVar15 = *(int **)(param_1 + 0x310);
      lVar16 = *(long *)(piVar15 + 0x3c);
      bVar2 = *(byte *)(lVar16 + 0xa0);
      if ((*(byte *)(lVar13 + 0x6c) & 1) == 0) {
        lVar1 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
        *(undefined4 *)(lVar1 + 0xa8) = 2;
        if (uVar4 == 0) {
          if (bVar2 == 0) {
            *(undefined1 *)(lVar16 + 200) = *(undefined1 *)(param_1 + 0x334);
          }
          else if (*piVar15 - 0xaaU < 2) {
            *(undefined1 *)(lVar1 + 200) = *(undefined1 *)(param_1 + 0x334);
          }
          else {
            *(undefined1 *)(lVar1 + 200) = *(undefined1 *)(lVar16 + 200);
          }
        }
        else {
          *(char *)(lVar1 + 200) = (char)uVar4;
          *(undefined1 *)(lVar16 + 0x22c) = local_51;
        }
        *(ulong *)(lVar16 + (long)(int)(uint)bVar2 * 0x30 + 0xb0) = uVar9;
        uVar7 = MCInst_getOpcode(param_1);
        pcVar10 = (char *)X86_get_op_access(lVar13,uVar7,
                                            *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
        if (pcVar10 == (char *)0x0) {
          local_50[0] = '\0';
        }
        else {
          cVar12 = *pcVar10;
          pcVar14 = local_50;
          uVar4 = 0;
          uVar9 = 0;
          if (cVar12 != '\0') {
            do {
              while (cVar12 != -0x80) {
                uVar6 = uVar4 + 1;
                pcVar14[uVar9] = cVar12;
                uVar4 = uVar6 & 0xff;
                uVar9 = (ulong)uVar6 & 0xff;
                cVar12 = pcVar10[uVar4];
                if (cVar12 == '\0') {
                  pcVar14 = pcVar14 + uVar9;
                  goto LAB_001df2a4;
                }
              }
              uVar6 = uVar4 + 1;
              pcVar14[uVar9] = '\0';
              uVar4 = uVar6 & 0xff;
              uVar9 = (ulong)uVar6 & 0xff;
              cVar12 = pcVar10[uVar4];
            } while (cVar12 != '\0');
            pcVar14 = pcVar14 + uVar9;
          }
LAB_001df2a4:
          *pcVar14 = '\0';
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar13 + 0xa0);
        *(char *)(lVar13 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc9) =
             local_50[(int)(uint)bVar2];
        *(byte *)(lVar13 + 0xa0) = bVar2 + 1;
      }
      else {
        *(ulong *)(lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc0) = uVar9;
      }
    }
    goto LAB_001df130;
  }
  uVar4 = MCOperand_getReg(uVar8);
  SStream_concat0(param_3,&AsmStrs_0 + *(ushort *)(RegAsmOffset_1 + (ulong)(uVar4 - 1) * 2));
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
LAB_001df128:
    cVar12 = *(char *)(param_1 + 6);
  }
  else {
    uVar6 = uVar4 & 0xffff;
    if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0xa0) * 0x30 + 0xa8) = 1;
      uVar5 = X86_register_map(uVar6);
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar16 = *(long *)(*(long *)(param_1 + 800) + 0xa0);
      *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0xa0) * 0x30 + 0xb0) = uVar5 & 0xffff;
      uVar6 = X86_register_map(uVar6);
      uVar8 = *(undefined8 *)(param_1 + 800);
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined1 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0xa0) * 0x30 + 200) =
           *(undefined1 *)(lVar16 + (ulong)(uVar6 & 0xffff));
      uVar7 = MCInst_getOpcode(param_1);
      pcVar10 = (char *)X86_get_op_access(uVar8,uVar7,
                                          *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
      if (pcVar10 == (char *)0x0) {
        local_50[0] = '\0';
      }
      else {
        cVar12 = *pcVar10;
        pcVar14 = local_50;
        uVar6 = 0;
        uVar9 = 0;
        if (cVar12 != '\0') {
          do {
            while (cVar12 != -0x80) {
              uVar5 = uVar6 + 1;
              pcVar14[uVar9] = cVar12;
              uVar6 = uVar5 & 0xff;
              uVar9 = (ulong)uVar5 & 0xff;
              cVar12 = pcVar10[uVar6];
              if (cVar12 == '\0') {
                pcVar14 = pcVar14 + uVar9;
                goto LAB_001df0fc;
              }
            }
            uVar5 = uVar6 + 1;
            pcVar14[uVar9] = '\0';
            uVar6 = uVar5 & 0xff;
            uVar9 = (ulong)uVar5 & 0xff;
            cVar12 = pcVar10[uVar6];
          } while (cVar12 != '\0');
          pcVar14 = pcVar14 + uVar9;
        }
LAB_001df0fc:
        *pcVar14 = '\0';
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar13 + 0xa0);
      *(char *)(lVar13 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc9) =
           local_50[(int)(uint)bVar2];
      *(byte *)(lVar13 + 0xa0) = bVar2 + 1;
      goto LAB_001df128;
    }
    uVar6 = X86_register_map(uVar6);
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0xa0) * 0x30 + 0xb4) = uVar6 & 0xffff;
    cVar12 = *(char *)(param_1 + 6);
  }
  if (cVar12 == '\0') {
    lVar13 = *(long *)(*(long *)(param_1 + 800) + 0xa0);
    uVar4 = X86_register_map(uVar4);
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(lVar13 + (ulong)(uVar4 & 0xffff));
  }
LAB_001df130:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

