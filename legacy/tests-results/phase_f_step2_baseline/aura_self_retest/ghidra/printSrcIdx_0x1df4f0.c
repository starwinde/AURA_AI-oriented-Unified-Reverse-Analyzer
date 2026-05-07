
void printSrcIdx(long param_1,int param_2,undefined8 param_3)

{
  uint uVar1;
  undefined1 uVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  char *pcVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  char cVar11;
  long lVar12;
  char local_50 [8];
  long local_48;
  
  pcVar10 = local_50;
  lVar12 = *(long *)(param_1 + 800);
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (*(int *)(lVar12 + 0x60) == 0) {
    MCInst_getOperand(param_1,param_2 + 1);
    iVar4 = MCOperand_getReg();
  }
  else {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0xa0) * 0x30;
    *(undefined4 *)(lVar8 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar8 + 0xb0) = 0;
    *(undefined8 *)(lVar8 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar8 + 0xc0) = 0;
    *(undefined1 *)(lVar8 + 200) = uVar2;
    uVar5 = MCInst_getOpcode();
    pcVar7 = (char *)X86_get_op_access(lVar12,uVar5,
                                       *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar7 == (char *)0x0) {
      local_50[0] = '\0';
    }
    else {
      cVar11 = *pcVar7;
      uVar6 = 0;
      uVar9 = 0;
      if (cVar11 != '\0') {
        do {
          while( true ) {
            uVar1 = uVar6 + 1;
            if (cVar11 == -0x80) break;
            uVar6 = uVar1 & 0xff;
            local_50[uVar9] = cVar11;
            uVar9 = (ulong)uVar1 & 0xff;
            cVar11 = pcVar7[uVar6];
            if (cVar11 == '\0') {
              pcVar10 = local_50 + uVar9;
              goto LAB_001df684;
            }
          }
          uVar6 = uVar1 & 0xff;
          local_50[uVar9] = '\0';
          uVar9 = (ulong)uVar1 & 0xff;
          cVar11 = pcVar7[uVar6];
        } while (cVar11 != '\0');
        pcVar10 = local_50 + uVar9;
      }
LAB_001df684:
      *pcVar10 = '\0';
    }
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar12 + 0xa0);
    *(char *)(lVar12 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10 + 0xc9) = local_50[(int)(uint)bVar3]
    ;
    MCInst_getOperand(param_1,param_2 + 1);
    iVar4 = MCOperand_getReg();
  }
  if (iVar4 != 0) {
    _printOperand(param_1,param_2 + 1,param_3);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar6 = X86_register_map(iVar4);
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30 + 0xb0) = uVar6 & 0xffff;
    }
    SStream_concat0(param_3,&DAT_001fbbf0);
  }
  SStream_concat0(param_3,&DAT_001fbd60);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 1;
  }
  printOperand(param_1,param_2,param_3);
  SStream_concat0(param_3,&DAT_001fc378);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar12 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar12 = *(long *)(lVar12 + 0xf0);
    *(char *)(lVar12 + 0xa0) = *(char *)(lVar12 + 0xa0) + '\x01';
  }
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

