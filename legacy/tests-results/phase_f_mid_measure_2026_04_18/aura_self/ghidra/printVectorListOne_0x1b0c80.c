
void printVectorListOne(long param_1,undefined4 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  char cVar5;
  long lVar6;
  
  SStream_concat0(param_3,&DAT_001f8fe0);
  lVar6 = *(long *)(param_1 + 800);
  MCInst_getOperand(param_1,param_2);
  MCOperand_getReg();
  uVar3 = (**(code **)(lVar6 + 0x78))();
  SStream_concat0(param_3,uVar3);
  lVar6 = *(long *)(param_1 + 800);
  if (*(int *)(lVar6 + 0x60) != 0) {
    uVar2 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar6 = ARM_get_op_access(lVar6,uVar2);
    if (lVar6 == 0) {
      cVar5 = '\0';
    }
    else {
      cVar5 = *(char *)(lVar6 + (ulong)bVar1);
      if (cVar5 == -0x80) {
        cVar5 = '\0';
      }
    }
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar6 + (ulong)*(byte *)(lVar6 + 0x80) * 0x30 + 0x94) = 1;
    MCInst_getOperand(param_1,param_2);
    uVar2 = MCOperand_getReg();
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar4 + 0x80);
    lVar6 = lVar4 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar6 + 0x98) = uVar2;
    *(char *)(lVar6 + 0xb1) = cVar5;
    *(byte *)(lVar4 + 0x80) = bVar1 + 1;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    SStream_concat0(param_3,&DAT_001f90e0);
    return;
  }
  SStream_concat0(param_3,&DAT_001f90e0);
  return;
}

