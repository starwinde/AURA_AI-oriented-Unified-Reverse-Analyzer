
void printU8Imm(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  undefined4 uVar4;
  ulong uVar5;
  char *pcVar6;
  char cVar7;
  uint uVar8;
  long lVar9;
  char *pcVar10;
  ulong uVar11;
  long lVar12;
  char local_40 [8];
  long local_38;
  
  pcVar10 = local_40;
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  MCInst_getOperand(param_1,param_2,0);
  uVar5 = MCOperand_getImm();
  uVar11 = uVar5 & 0xff;
  if (*(int *)(*(long *)(param_1 + 800) + 0x68) == 4) {
    if (uVar11 < 10) {
      SStream_concat(param_3,&DAT_001f9830,uVar11);
    }
    else if (((uVar5 & 0xf0) == 0) || (0x9f < uVar11)) {
      SStream_concat(param_3,"0%lxh",uVar11);
    }
    else {
      SStream_concat(param_3,&DAT_00201788,uVar11);
    }
  }
  else {
    if (9 < uVar11) {
      SStream_concat(param_3,"0x%lx",uVar11);
      lVar12 = *(long *)(param_1 + 800);
      iVar2 = *(int *)(lVar12 + 0x60);
      goto joined_r0x001dee4c;
    }
    SStream_concat(param_3,&DAT_001f9830,uVar11);
  }
  lVar12 = *(long *)(param_1 + 800);
  iVar2 = *(int *)(lVar12 + 0x60);
joined_r0x001dee4c:
  if (iVar2 != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar9 = lVar9 + (ulong)*(byte *)(lVar9 + 0xa0) * 0x30;
    *(undefined4 *)(lVar9 + 0xa8) = 2;
    *(ulong *)(lVar9 + 0xb0) = uVar11;
    *(undefined1 *)(lVar9 + 200) = 1;
    uVar4 = MCInst_getOpcode(param_1);
    pcVar6 = (char *)X86_get_op_access(lVar12,uVar4,
                                       *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar6 == (char *)0x0) {
      local_40[0] = '\0';
    }
    else {
      cVar7 = *pcVar6;
      uVar8 = 0;
      uVar5 = 0;
      if (cVar7 != '\0') {
        do {
          while (cVar7 != -0x80) {
            uVar1 = uVar8 + 1;
            local_40[uVar5] = cVar7;
            uVar8 = uVar1 & 0xff;
            uVar5 = (ulong)uVar1 & 0xff;
            cVar7 = pcVar6[uVar8];
            if (cVar7 == '\0') {
              pcVar10 = local_40 + uVar5;
              goto LAB_001deed4;
            }
          }
          uVar1 = uVar8 + 1;
          local_40[uVar5] = '\0';
          uVar8 = uVar1 & 0xff;
          uVar5 = (ulong)uVar1 & 0xff;
          cVar7 = pcVar6[uVar8];
        } while (cVar7 != '\0');
        pcVar10 = local_40 + uVar5;
      }
LAB_001deed4:
      *pcVar10 = '\0';
    }
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar12 + 0xa0);
    *(char *)(lVar12 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10 + 0xc9) = local_40[(int)(uint)bVar3]
    ;
    *(byte *)(lVar12 + 0xa0) = bVar3 + 1;
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

