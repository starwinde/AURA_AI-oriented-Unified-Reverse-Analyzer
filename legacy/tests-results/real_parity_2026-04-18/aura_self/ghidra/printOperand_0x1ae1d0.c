
void printOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  char cVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  
  uVar5 = MCInst_getOperand();
  uVar6 = MCOperand_isReg();
  if ((uVar6 & 1) != 0) {
    uVar3 = MCOperand_getReg(uVar5);
    uVar5 = (**(code **)(*(long *)(param_1 + 800) + 0x78))();
    SStream_concat0(param_3,uVar5);
    lVar10 = *(long *)(param_1 + 800);
    if (*(int *)(lVar10 + 0x60) == 0) {
      return;
    }
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar9 + 0x80);
    if ((*(byte *)(lVar10 + 0x6c) & 1) != 0) {
      lVar9 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      if (*(int *)(lVar9 + 0x98) == 0) {
        *(undefined4 *)(lVar9 + 0x98) = uVar3;
        return;
      }
      *(undefined4 *)(lVar9 + 0x9c) = uVar3;
      return;
    }
    lVar9 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar9 + 0x94) = 1;
    *(undefined4 *)(lVar9 + 0x98) = uVar3;
    uVar3 = MCInst_getOpcode(param_1);
    bVar2 = *(byte *)(param_1 + 0x366);
    lVar10 = ARM_get_op_access(lVar10,uVar3);
    if (lVar10 == 0) {
      cVar7 = '\0';
    }
    else {
      cVar7 = *(char *)(lVar10 + (ulong)bVar2);
      if (cVar7 == -0x80) {
        cVar7 = '\0';
      }
    }
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    *(char *)(lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xb1) = cVar7;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(byte *)(lVar10 + 0x80) = bVar2 + 1;
    return;
  }
  uVar6 = MCOperand_isImm(uVar5);
  if ((uVar6 & 1) == 0) {
    return;
  }
  uVar3 = MCInst_getOpcode(param_1);
  iVar4 = MCOperand_getImm(uVar5);
  uVar6 = ARM_rel_branch(*(undefined8 *)(param_1 + 800),uVar3);
  if ((uVar6 & 1) != 0) {
    iVar8 = (int)*(undefined8 *)(param_1 + 0x318);
    uVar11 = iVar8 + 8;
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 4 & 1) != 0) {
      uVar1 = iVar8 + 4;
      uVar6 = ARM_blx_to_arm_mode(*(long *)(param_1 + 800),uVar3);
      uVar11 = uVar1 & 0xfffffffc;
      if ((uVar6 & 1) == 0) {
        uVar11 = uVar1;
      }
    }
    iVar4 = uVar11 + iVar4;
    printUInt32Bang(param_3,iVar4);
    goto LAB_001ae2c0;
  }
  uVar11 = **(uint **)(param_1 + 0x310);
  if (uVar11 < 0x2e) {
    if ((uVar11 < 9) || ((0x200000004200U >> ((ulong)uVar11 & 0x3f) & 1) == 0)) {
LAB_001ae394:
      if (*(int *)(*(long *)(param_1 + 800) + 100) == 0) {
        printInt32Bang(param_3,iVar4);
        goto LAB_001ae2c0;
      }
    }
  }
  else if ((uVar11 - 0x75 & 0xfffffffb) != 0) goto LAB_001ae394;
  printUInt32Bang(param_3,iVar4);
LAB_001ae2c0:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) {
      lVar9 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar9 + 0x94) = 2;
      *(int *)(lVar9 + 0x98) = iVar4;
      *(byte *)(lVar10 + 0x80) = bVar2 + 1;
    }
    else {
      *(int *)(lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xa4) = iVar4;
    }
  }
  return;
}

