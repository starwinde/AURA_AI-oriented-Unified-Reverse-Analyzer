
void printVectorListTwo(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  char cVar7;
  undefined8 uVar8;
  
  MCInst_getOperand();
  uVar2 = MCOperand_getReg();
  uVar3 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar2,1);
  uVar2 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar2,2);
  uVar8 = *(undefined8 *)(param_1 + 800);
  uVar4 = MCInst_getOpcode(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar5 = ARM_get_op_access(uVar8,uVar4);
  if (lVar5 == 0) {
    cVar7 = '\0';
  }
  else {
    cVar7 = *(char *)(lVar5 + (ulong)bVar1);
    if (cVar7 == -0x80) {
      cVar7 = '\0';
    }
  }
  SStream_concat0(param_3,&DAT_001f8480);
  uVar8 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar3);
  SStream_concat0(param_3,uVar8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar6 + 0x80);
    lVar5 = lVar6 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar5 + 0x94) = 1;
    *(undefined4 *)(lVar5 + 0x98) = uVar3;
    *(char *)(lVar5 + 0xb1) = cVar7;
    *(byte *)(lVar6 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,", ");
  uVar8 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar2);
  SStream_concat0(param_3,uVar8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar6 + 0x80);
    lVar5 = lVar6 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar5 + 0x94) = 1;
    *(undefined4 *)(lVar5 + 0x98) = uVar2;
    *(char *)(lVar5 + 0xb1) = cVar7;
    *(byte *)(lVar6 + 0x80) = bVar1 + 1;
  }
  SStream_concat0(param_3,&DAT_001f8580);
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  return;
}

