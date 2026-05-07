
void printVRegOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  
  MCInst_getOperand();
  iVar3 = MCOperand_getReg();
  SStream_concat0(param_3,AsmStrsvreg_7 + (byte)RegAsmOffsetvreg_8[iVar3 - 1]);
  lVar6 = *(long *)(param_1 + 800);
  if (*(int *)(lVar6 + 0x60) == 0) {
    return;
  }
  uVar4 = MCInst_getOpcode(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar5 = AArch64_get_op_access(lVar6,uVar4);
  lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar2 = *(char *)(lVar5 + (ulong)bVar1);
  if (cVar2 == -0x80) {
    cVar2 = '\0';
  }
  lVar6 = lVar6 + (ulong)*(byte *)(lVar6 + 0x67) * 0x38;
  *(char *)(lVar6 + 0x98) = cVar2;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar6 + 0x7c) = 1;
  uVar4 = AArch64_map_vregister(iVar3);
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(undefined4 *)(lVar6 + 0x88) = uVar4;
  *(char *)(lVar5 + 0x67) = *(char *)(lVar5 + 0x67) + '\x01';
  return;
}

