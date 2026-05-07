
void printT2AddrModeSoRegOperand(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCInst_getOperand(param_1,param_2 + 1);
  uVar6 = MCInst_getOperand(param_1,param_2 + 2);
  SStream_concat0(param_3,&DAT_001fd940);
  set_mem_access(param_1,1);
  lVar8 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar7 = (**(code **)(lVar8 + 0x78))();
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar3 = MCOperand_getReg(uVar4);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
  }
  SStream_concat0(param_3,", ");
  lVar8 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar5);
  uVar4 = (**(code **)(lVar8 + 0x78))();
  SStream_concat0(param_3,uVar4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar3 = MCOperand_getReg(uVar5);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar3;
  }
  iVar2 = MCOperand_getImm(uVar6);
  if (iVar2 != 0) {
    SStream_concat0(param_3,", lsl ");
    SStream_concat(param_3,&DAT_001fd738,iVar2);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30;
      *(undefined4 *)(lVar8 + 0x8c) = 2;
      *(int *)(lVar8 + 0x90) = iVar2;
    }
  }
  SStream_concat0(param_3,&DAT_001fdf58);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar8 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar8 = *(long *)(lVar8 + 0xf0);
    *(char *)(lVar8 + 0x80) = *(char *)(lVar8 + 0x80) + '\x01';
  }
  return;
}

