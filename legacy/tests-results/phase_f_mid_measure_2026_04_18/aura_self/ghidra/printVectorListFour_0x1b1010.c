
void printVectorListFour(long param_1,undefined4 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  char cVar6;
  undefined8 uVar7;
  
  uVar7 = *(undefined8 *)(param_1 + 800);
  uVar2 = MCInst_getOpcode();
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar4 = ARM_get_op_access(uVar7,uVar2);
  if (lVar4 == 0) {
    cVar6 = '\0';
  }
  else {
    cVar6 = *(char *)(lVar4 + (ulong)bVar1);
    if (cVar6 == -0x80) {
      cVar6 = '\0';
    }
  }
  SStream_concat0(param_3,&DAT_001f8fe0);
  lVar4 = *(long *)(param_1 + 800);
  MCInst_getOperand(param_1,param_2);
  MCOperand_getReg();
  uVar7 = (**(code **)(lVar4 + 0x78))();
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x80) * 0x30 + 0x94) = 1;
    MCInst_getOperand(param_1,param_2);
    uVar2 = MCOperand_getReg();
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    lVar4 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar4 + 0x98) = uVar2;
    *(char *)(lVar4 + 0xb1) = cVar6;
    *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,", ");
  lVar4 = *(long *)(param_1 + 800);
  MCInst_getOperand(param_1,param_2);
  iVar3 = MCOperand_getReg();
  uVar7 = (**(code **)(lVar4 + 0x78))(iVar3 + 1);
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x80) * 0x30 + 0x94) = 1;
    MCInst_getOperand(param_1,param_2);
    iVar3 = MCOperand_getReg();
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    lVar4 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(int *)(lVar4 + 0x98) = iVar3 + 1;
    *(char *)(lVar4 + 0xb1) = cVar6;
    *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,", ");
  lVar4 = *(long *)(param_1 + 800);
  MCInst_getOperand(param_1,param_2);
  iVar3 = MCOperand_getReg();
  uVar7 = (**(code **)(lVar4 + 0x78))(iVar3 + 2);
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x80) * 0x30 + 0x94) = 1;
    MCInst_getOperand(param_1,param_2);
    iVar3 = MCOperand_getReg();
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    lVar4 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(int *)(lVar4 + 0x98) = iVar3 + 2;
    *(char *)(lVar4 + 0xb1) = cVar6;
    *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,", ");
  lVar4 = *(long *)(param_1 + 800);
  MCInst_getOperand(param_1,param_2);
  iVar3 = MCOperand_getReg();
  uVar7 = (**(code **)(lVar4 + 0x78))(iVar3 + 3);
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x80) * 0x30 + 0x94) = 1;
    MCInst_getOperand(param_1,param_2);
    iVar3 = MCOperand_getReg();
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    lVar4 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(int *)(lVar4 + 0x98) = iVar3 + 3;
    *(char *)(lVar4 + 0xb1) = cVar6;
    *(byte *)(lVar5 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,&DAT_001f90e0);
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  return;
}

