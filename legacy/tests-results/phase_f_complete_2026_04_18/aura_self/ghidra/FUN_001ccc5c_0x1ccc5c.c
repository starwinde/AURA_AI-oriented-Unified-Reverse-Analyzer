
void FUN_001ccc5c(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  uVar6 = MCInst_getOperand();
  uVar7 = MCOperand_isReg();
  if ((uVar7 & 1) == 0) {
    uVar7 = MCOperand_isImm(uVar6);
    if ((uVar7 & 1) != 0) {
      lVar10 = MCOperand_getImm(uVar6);
      if (*(int *)(param_1 + 8) == 0x40d) {
        lVar10 = lVar10 + *(long *)(param_1 + 0x318);
        printUInt64Bang(param_3,lVar10);
      }
      else if (((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) ||
              (*(int *)(*(long *)(param_1 + 800) + 100) != 0)) {
        printUInt64Bang(param_3,lVar10);
      }
      else {
        printInt64Bang(param_3,lVar10);
      }
      lVar8 = *(long *)(param_1 + 800);
      if (*(int *)(lVar8 + 0x60) != 0) {
        if ((*(byte *)(lVar8 + 0x6c) & 1) == 0) {
          if ((*(byte *)(lVar8 + 0x6d) & 1) == 0) {
            uVar5 = MCInst_getOpcode(param_1);
            bVar1 = *(byte *)(param_1 + 0x366);
            lVar8 = AArch64_get_op_access(lVar8,uVar5);
            lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            cVar2 = *(char *)(lVar8 + (ulong)bVar1);
            bVar1 = *(byte *)(lVar9 + 0x67);
            if (cVar2 == -0x80) {
              cVar2 = '\0';
            }
            lVar8 = lVar9 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
            *(undefined4 *)(lVar8 + 0x7c) = 2;
            *(long *)(lVar8 + 0x88) = lVar10;
            *(char *)(lVar8 + 0x98) = cVar2;
            *(byte *)(lVar9 + 0x67) = bVar1 + 1;
          }
          else {
            lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            uVar3 = *(byte *)(lVar8 + 0x67) - 1;
            *(int *)(lVar8 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar3 << 3) -
                             (long)(int)uVar3) * 8 + 0x90) = (int)lVar10;
          }
        }
        else {
          lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(int *)(lVar8 + (ulong)*(byte *)(lVar8 + 0x67) * 0x38 + 0x90) = (int)lVar10;
        }
      }
    }
  }
  else {
    iVar4 = MCOperand_getReg(uVar6);
    SStream_concat0(param_3,&AsmStrsNoRegAltName_11 +
                            *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar4 - 1) * 2));
    lVar10 = *(long *)(param_1 + 800);
    if (*(int *)(lVar10 + 0x60) != 0) {
      if ((*(byte *)(lVar10 + 0x6c) & 1) == 0) {
        if ((*(byte *)(lVar10 + 0x6d) & 1) != 0) {
          lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          uVar3 = *(byte *)(lVar10 + 0x67) - 1;
          *(int *)(lVar10 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar3 << 3) -
                            (long)(int)uVar3) * 8 + 0x8c) = iVar4;
          return;
        }
        uVar5 = MCInst_getOpcode(param_1);
        bVar1 = *(byte *)(param_1 + 0x366);
        lVar10 = AArch64_get_op_access(lVar10,uVar5);
        lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar2 = *(char *)(lVar10 + (ulong)bVar1);
        bVar1 = *(byte *)(lVar8 + 0x67);
        if (cVar2 == -0x80) {
          cVar2 = '\0';
        }
        lVar10 = lVar8 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
        *(char *)(lVar10 + 0x98) = cVar2;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar10 + 0x7c) = 1;
        *(int *)(lVar10 + 0x88) = iVar4;
        *(byte *)(lVar8 + 0x67) = bVar1 + 1;
      }
      else {
        lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar10 = lVar10 + (ulong)*(byte *)(lVar10 + 0x67) * 0x38;
        if (*(int *)(lVar10 + 0x88) == 0) {
          *(int *)(lVar10 + 0x88) = iVar4;
        }
        else if (*(int *)(lVar10 + 0x8c) == 0) {
          *(int *)(lVar10 + 0x8c) = iVar4;
          return;
        }
      }
    }
  }
  return;
}

