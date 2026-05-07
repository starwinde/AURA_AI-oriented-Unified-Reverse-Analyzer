
void printFPImmOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  long lVar10;
  double dVar11;
  float fVar12;
  
  uVar5 = MCInst_getOperand();
  uVar6 = MCOperand_isFPImm();
  if ((uVar6 & 1) == 0) {
    uVar3 = MCOperand_getImm(uVar5);
    uVar9 = 0x3e000000;
    uVar7 = (uVar3 >> 7) << 0x1f;
    if ((uVar3 >> 6 & 1) == 0) {
      uVar7 = uVar7 | 0x40000000;
      uVar9 = 0;
    }
    fVar12 = (float)((uVar3 >> 4 & 3) << 0x17 | (uVar3 & 0xf) << 0x13 | uVar9 | uVar7);
  }
  else {
    dVar11 = (double)MCOperand_getFPImm(uVar5);
    fVar12 = (float)dVar11;
  }
  SStream_concat((double)fVar12,param_3,"#%.8f");
  lVar10 = *(long *)(param_1 + 800);
  if (*(int *)(lVar10 + 0x60) == 0) {
    return;
  }
  uVar4 = MCInst_getOpcode(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar10 = AArch64_get_op_access(lVar10,uVar4);
  lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar2 = *(char *)(lVar10 + (ulong)bVar1);
  bVar1 = *(byte *)(lVar8 + 0x67);
  if (cVar2 == -0x80) {
    cVar2 = '\0';
  }
  lVar10 = lVar8 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
  *(char *)(lVar10 + 0x98) = cVar2;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar10 + 0x7c) = 4;
  *(double *)(lVar10 + 0x88) = (double)fVar12;
  *(byte *)(lVar8 + 0x67) = bVar1 + 1;
  return;
}

