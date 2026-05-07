
void printSysCROperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCOperand_getImm();
  SStream_concat(param_3,&DAT_001fbda8,uVar5);
  lVar7 = *(long *)(param_1 + 800);
  if (*(int *)(lVar7 + 0x60) == 0) {
    return;
  }
  uVar3 = MCInst_getOpcode(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar6 = AArch64_get_op_access(lVar7,uVar3);
  lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar2 = *(char *)(lVar6 + (ulong)bVar1);
  if (cVar2 == -0x80) {
    cVar2 = '\0';
  }
  lVar7 = lVar7 + (ulong)*(byte *)(lVar7 + 0x67) * 0x38;
  *(char *)(lVar7 + 0x98) = cVar2;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar7 + 0x7c) = 0x40;
  uVar4 = MCOperand_getImm(uVar4);
  lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(undefined8 *)(lVar7 + 0x88) = uVar4;
  *(char *)(lVar6 + 0x67) = *(char *)(lVar6 + 0x67) + '\x01';
  return;
}

