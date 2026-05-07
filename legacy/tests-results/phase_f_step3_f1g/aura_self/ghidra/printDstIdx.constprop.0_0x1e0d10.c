
void printDstIdx_constprop_0(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  ulong uVar7;
  char *pcVar8;
  long lVar9;
  char cVar10;
  uint uVar11;
  long lVar12;
  char local_40 [8];
  long local_38;
  
  pcVar8 = local_40;
  lVar12 = *(long *)(param_1 + 800);
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  lVar9 = 0;
  if (*(int *)(lVar12 + 0x60) != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar9 = lVar9 + (ulong)*(byte *)(lVar9 + 0xa0) * 0x30;
    *(undefined4 *)(lVar9 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar9 + 0xb0) = 0;
    *(undefined8 *)(lVar9 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar9 + 0xc0) = 0;
    *(undefined1 *)(lVar9 + 200) = uVar2;
    uVar4 = MCInst_getOpcode();
    pcVar5 = (char *)X86_get_op_access(lVar12,uVar4,
                                       *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98);
    if (pcVar5 == (char *)0x0) {
      local_40[0] = '\0';
    }
    else {
      cVar10 = *pcVar5;
      uVar11 = 0;
      uVar7 = 0;
      if (cVar10 != '\0') {
        do {
          while( true ) {
            uVar1 = uVar11 + 1;
            if (cVar10 == -0x80) break;
            uVar11 = uVar1 & 0xff;
            local_40[uVar7] = cVar10;
            uVar7 = (ulong)uVar1 & 0xff;
            cVar10 = pcVar5[uVar11];
            if (cVar10 == '\0') {
              pcVar8 = local_40 + uVar7;
              goto LAB_001e0ec4;
            }
          }
          uVar11 = uVar1 & 0xff;
          local_40[uVar7] = '\0';
          uVar7 = (ulong)uVar1 & 0xff;
          cVar10 = pcVar5[uVar11];
        } while (cVar10 != '\0');
        pcVar8 = local_40 + uVar7;
      }
LAB_001e0ec4:
      *pcVar8 = '\0';
    }
    lVar12 = *(long *)(param_1 + 800);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar9 + 0xa0);
    *(char *)(lVar9 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10 + 0xc9) = local_40[(int)(uint)bVar3];
  }
  if (*(int *)(lVar12 + 4) == 8) {
    SStream_concat0(param_2,&DAT_001fc3c0,lVar9);
    lVar9 = *(long *)(param_1 + 800);
    iVar6 = *(int *)(lVar9 + 0x60);
  }
  else {
    SStream_concat0(param_2,&DAT_00201dc0,lVar9);
    lVar9 = *(long *)(param_1 + 800);
    iVar6 = *(int *)(lVar9 + 0x60);
    if (iVar6 == 0) goto LAB_001e0da0;
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30 + 0xb0) = 0x1c;
  }
  if (iVar6 == 3) {
    *(undefined1 *)(lVar9 + 0x6c) = 1;
  }
LAB_001e0da0:
  printOperand(param_1,0,param_2);
  SStream_concat0(param_2,&DAT_001fc9d8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar9 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar9 = *(long *)(lVar9 + 0xf0);
    *(char *)(lVar9 + 0xa0) = *(char *)(lVar9 + 0xa0) + '\x01';
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

