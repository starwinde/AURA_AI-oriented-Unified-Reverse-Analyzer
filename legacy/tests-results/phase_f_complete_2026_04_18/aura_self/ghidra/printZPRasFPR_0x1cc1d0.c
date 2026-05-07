
void printZPRasFPR(long param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  long lVar7;
  
  if (param_4 == 0x40) {
    iVar3 = 0x2b;
  }
  else if (param_4 < 0x41) {
    iVar3 = 0x4b;
    if ((param_4 != 0x10) && (iVar3 = 0xb, param_4 == 0x20)) {
      iVar3 = 0x9b;
    }
  }
  else {
    iVar3 = 0xb;
    if (param_4 == 0x80) {
      iVar3 = 0x7b;
    }
  }
  MCInst_getOperand(param_1);
  iVar4 = MCOperand_getReg();
  SStream_concat0(param_3,&AsmStrsNoRegAltName_11 +
                          *(ushort *)
                           (RegAsmOffsetNoRegAltName_12 + (ulong)((iVar4 + iVar3) - 0xf8) * 2));
  lVar7 = *(long *)(param_1 + 800);
  if (*(int *)(lVar7 + 0x60) != 0) {
    uVar5 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar7 = AArch64_get_op_access(lVar7,uVar5);
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    cVar2 = *(char *)(lVar7 + (ulong)bVar1);
    bVar1 = *(byte *)(lVar6 + 0x67);
    if (cVar2 == -0x80) {
      cVar2 = '\0';
    }
    lVar7 = lVar6 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
    *(char *)(lVar7 + 0x98) = cVar2;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar7 + 0x7c) = 1;
    *(int *)(lVar7 + 0x88) = iVar4 + iVar3 + -0xf7;
    *(byte *)(lVar6 + 0x67) = bVar1 + 1;
    return;
  }
  return;
}

