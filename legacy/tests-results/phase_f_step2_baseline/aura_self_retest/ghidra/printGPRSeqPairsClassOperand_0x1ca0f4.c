
void printGPRSeqPairsClassOperand(long param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  long lVar10;
  
  MCInst_getOperand();
  uVar5 = MCOperand_getReg();
  uVar8 = 0x11;
  if (param_4 == 0x20) {
    uVar8 = 0x10;
  }
  uVar9 = 0xf;
  if (param_4 == 0x20) {
    uVar9 = 0xe;
  }
  iVar6 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar5,uVar9);
  iVar7 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar5,uVar8);
  SStream_concat(param_3,"%s, %s",
                 &AsmStrsNoRegAltName_11 +
                 *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar6 - 1) * 2),
                 &AsmStrsNoRegAltName_11 +
                 *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar7 - 1) * 2));
  lVar10 = *(long *)(param_1 + 800);
  if (*(int *)(lVar10 + 0x60) == 0) {
    return;
  }
  uVar8 = MCInst_getOpcode(param_1);
  bVar3 = *(byte *)(param_1 + 0x366);
  lVar10 = AArch64_get_op_access(lVar10,uVar8);
  cVar4 = *(char *)(lVar10 + (ulong)bVar3);
  lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (cVar4 == -0x80) {
    cVar4 = '\0';
  }
  bVar3 = *(byte *)(lVar10 + 0x67);
  lVar1 = lVar10 + ((ulong)bVar3 * 8 - (ulong)bVar3) * 8;
  lVar2 = lVar10 + ((ulong)(byte)(bVar3 + 1) * 8 - (ulong)(byte)(bVar3 + 1)) * 8;
  *(char *)(lVar1 + 0x98) = cVar4;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar1 + 0x7c) = 1;
  *(int *)(lVar1 + 0x88) = iVar6;
  *(undefined4 *)(lVar2 + 0x7c) = 1;
  *(int *)(lVar2 + 0x88) = iVar7;
  *(byte *)(lVar10 + 0x67) = bVar3 + 2;
  return;
}

