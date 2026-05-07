
void printT2AddrModeImm0_1020s4Operand(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long lVar7;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCInst_getOperand(param_1,param_2 + 1);
  SStream_concat0(param_3,&DAT_001fcde0);
  set_mem_access(param_1,1);
  lVar7 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar6 = (**(code **)(lVar7 + 0x78))();
  SStream_concat0(param_3,uVar6);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    lVar7 = MCOperand_getImm(uVar5);
  }
  else {
    lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar7 + 0x80);
    uVar2 = MCOperand_getReg(uVar4);
    *(undefined4 *)(lVar7 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar2;
    lVar7 = MCOperand_getImm(uVar5);
  }
  if (lVar7 != 0) {
    SStream_concat0(param_3,", ");
    iVar3 = MCOperand_getImm(uVar5);
    printUInt32Bang(param_3,iVar3 << 2);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(int *)(lVar7 + (ulong)*(byte *)(lVar7 + 0x80) * 0x30 + 0xa4) = iVar3 << 2;
    }
  }
  SStream_concat0(param_3,&DAT_001fd3f8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar7 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar7 = *(long *)(lVar7 + 0xf0);
    *(char *)(lVar7 + 0x80) = *(char *)(lVar7 + 0x80) + '\x01';
  }
  return;
}

