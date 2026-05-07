
void printAddrMode5Operand(long param_1,int param_2,undefined8 param_3,char param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined *puVar9;
  uint uVar10;
  uint uVar11;
  long lVar12;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCInst_getOperand(param_1,param_2 + 1);
  uVar2 = MCOperand_getImm();
  uVar6 = MCOperand_isReg(uVar4);
  if ((uVar6 & 1) == 0) {
    printOperand(param_1,param_2,param_3);
    return;
  }
  SStream_concat0(param_3,&DAT_001fcde0);
  lVar12 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar7 = (**(code **)(lVar12 + 0x78))();
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    bVar1 = MCOperand_getImm(uVar5);
    uVar10 = (uint)bVar1;
    if (bVar1 != 0 || param_4 != '\0') goto LAB_001b0b98;
LAB_001b0c48:
    if ((uVar2 & 0x100) == 0) goto LAB_001b0c00;
    uVar11 = 0;
    puVar9 = &DAT_001f98b8;
LAB_001b0c58:
    SStream_concat(param_3,", #%s%u",puVar9,uVar11);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
    *(undefined4 *)(lVar12 + 0x94) = 3;
    uVar3 = MCOperand_getReg(uVar4);
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + 0x98) = uVar3;
    uVar4 = DAT_0020b3d8;
    lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30;
    *(undefined4 *)(lVar8 + 0x9c) = 0;
    *(undefined1 *)(lVar8 + 0xb1) = 1;
    *(undefined8 *)(lVar8 + 0xa0) = uVar4;
    bVar1 = MCOperand_getImm(uVar5);
    uVar10 = (uint)bVar1;
    if (bVar1 == 0 && param_4 == '\0') goto LAB_001b0c48;
LAB_001b0b98:
    uVar11 = uVar10 << 2;
    if (uVar11 < 10) {
      puVar9 = &DAT_001fd4a8;
      if ((uVar2 & 0x100) != 0) {
        puVar9 = &DAT_001f98b8;
      }
      goto LAB_001b0c58;
    }
    puVar9 = &DAT_001fd4a8;
    if ((uVar2 & 0x100) != 0) {
      puVar9 = &DAT_001f98b8;
    }
    SStream_concat(param_3,&DAT_001fcde8,puVar9,uVar11);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar12 + 0x80);
    if ((uVar2 & 0x100) == 0) {
      *(uint *)(lVar12 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0xa4) = uVar11;
    }
    else {
      *(uint *)(lVar12 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0xa4) = uVar10 * -4;
    }
  }
LAB_001b0c00:
  SStream_concat0(param_3,&DAT_001fd3f8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
  }
  return;
}

