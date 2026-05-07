
void printThumbAddrModeImm5SOperand_constprop_0(long param_1,undefined8 param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  
  uVar4 = MCInst_getOperand(param_1,1);
  uVar5 = MCInst_getOperand(param_1,2);
  uVar6 = MCOperand_isReg(uVar4);
  if ((uVar6 & 1) == 0) {
    printOperand(param_1,1,param_2);
    return;
  }
  SStream_concat0(param_2,&DAT_001fbd60);
  set_mem_access(param_1,1);
  lVar9 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar7 = (**(code **)(lVar9 + 0x78))();
  SStream_concat0(param_2,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar2 = MCOperand_getImm(uVar5);
  }
  else {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar9 + 0x80);
    uVar3 = MCOperand_getReg(uVar4);
    *(undefined4 *)(lVar9 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
    iVar2 = MCOperand_getImm(uVar5);
  }
  if (iVar2 != 0) {
    SStream_concat0(param_2,", ");
    printUInt32Bang(param_2,param_3 * iVar2);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(int *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30 + 0xa4) = param_3 * iVar2;
      SStream_concat0(param_2,&DAT_001fc378);
      lVar9 = *(long *)(param_1 + 800);
      iVar2 = *(int *)(lVar9 + 0x60);
      goto joined_r0x001b0fcc;
    }
  }
  SStream_concat0(param_2,&DAT_001fc378);
  lVar9 = *(long *)(param_1 + 800);
  iVar2 = *(int *)(lVar9 + 0x60);
joined_r0x001b0fcc:
  if (iVar2 != 3) {
    return;
  }
  lVar8 = *(long *)(param_1 + 0x310);
  *(undefined1 *)(lVar9 + 0x6c) = 0;
  lVar9 = *(long *)(lVar8 + 0xf0);
  *(char *)(lVar9 + 0x80) = *(char *)(lVar9 + 0x80) + '\x01';
  return;
}

