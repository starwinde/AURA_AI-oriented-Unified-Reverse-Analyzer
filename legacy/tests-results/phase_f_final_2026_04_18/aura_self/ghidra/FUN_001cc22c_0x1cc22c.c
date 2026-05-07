
void FUN_001cc22c(long param_1,undefined8 param_2,undefined8 param_3,ulong param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  
  uVar5 = MCInst_getOperand();
  uVar6 = MCOperand_isReg();
  if ((uVar6 & 1) != 0) {
    iVar3 = MCOperand_getReg(uVar5);
    if (iVar3 == 9) {
      printInt32Bang(param_3,param_4 & 0xffffffff);
      lVar8 = *(long *)(param_1 + 800);
      if (*(int *)(lVar8 + 0x60) != 0) {
        uVar4 = MCInst_getOpcode(param_1);
        bVar1 = *(byte *)(param_1 + 0x366);
        lVar8 = AArch64_get_op_access(lVar8,uVar4);
        lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar2 = *(char *)(lVar8 + (ulong)bVar1);
        bVar1 = *(byte *)(lVar7 + 0x67);
        if (cVar2 == -0x80) {
          cVar2 = '\0';
        }
        lVar8 = lVar7 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
        *(char *)(lVar8 + 0x98) = cVar2;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar8 + 0x7c) = 2;
        *(ulong *)(lVar8 + 0x88) = param_4 & 0xffffffff;
        *(byte *)(lVar7 + 0x67) = bVar1 + 1;
      }
    }
    else {
      SStream_concat0(param_3,&AsmStrsNoRegAltName_11 +
                              *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar3 - 1) * 2));
      lVar8 = *(long *)(param_1 + 800);
      if (*(int *)(lVar8 + 0x60) != 0) {
        uVar4 = MCInst_getOpcode(param_1);
        bVar1 = *(byte *)(param_1 + 0x366);
        lVar8 = AArch64_get_op_access(lVar8,uVar4);
        lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar2 = *(char *)(lVar8 + (ulong)bVar1);
        bVar1 = *(byte *)(lVar7 + 0x67);
        if (cVar2 == -0x80) {
          cVar2 = '\0';
        }
        lVar8 = lVar7 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
        *(char *)(lVar8 + 0x98) = cVar2;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar8 + 0x7c) = 1;
        *(int *)(lVar8 + 0x88) = iVar3;
        *(byte *)(lVar7 + 0x67) = bVar1 + 1;
      }
    }
  }
  return;
}

