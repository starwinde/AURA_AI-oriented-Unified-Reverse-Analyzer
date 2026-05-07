
void printAddrMode3Operand(long param_1,int param_2,undefined8 param_3,char param_4)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined *puVar11;
  long lVar12;
  
  MCInst_getOperand();
  uVar6 = MCOperand_isReg();
  if ((uVar6 & 1) == 0) {
    printOperand(param_1,param_2,param_3);
    return;
  }
  uVar7 = MCInst_getOperand(param_1,param_2);
  uVar8 = MCInst_getOperand(param_1,param_2 + 1);
  uVar9 = MCInst_getOperand(param_1,param_2 + 2);
  uVar3 = MCOperand_getImm();
  uVar3 = uVar3 & 0x100;
  SStream_concat0(param_3,&DAT_001fd940);
  set_mem_access(param_1,1);
  lVar12 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar7);
  uVar10 = (**(code **)(lVar12 + 0x78))();
  SStream_concat0(param_3,uVar10);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar4 = MCOperand_getReg(uVar8);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar12 + 0x80);
    uVar5 = MCOperand_getReg(uVar7);
    *(undefined4 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x98) = uVar5;
    iVar4 = MCOperand_getReg(uVar8);
  }
  if (iVar4 != 0) {
    SStream_concat0(param_3,", ");
    puVar11 = &DAT_001fe008;
    if (uVar3 != 0) {
      puVar11 = &DAT_001fa418;
    }
    SStream_concat0(param_3,puVar11);
    lVar12 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar8);
    uVar7 = (**(code **)(lVar12 + 0x78))();
    SStream_concat0(param_3,uVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar12 + 0x80);
      uVar5 = MCOperand_getReg(uVar8);
      *(undefined4 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x9c) = uVar5;
      if (uVar3 != 0) {
        lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
        *(undefined4 *)(lVar12 + 0xa0) = 0xffffffff;
        *(undefined1 *)(lVar12 + 0xb0) = 1;
      }
    }
    goto LAB_001b4340;
  }
  bVar2 = MCOperand_getImm(uVar9);
  uVar1 = (uint)bVar2;
  if (bVar2 == 0 && param_4 == '\0') {
    if (uVar3 != 0) {
      puVar11 = &DAT_001fa418;
LAB_001b4508:
      SStream_concat(param_3,", #%s%u",puVar11,uVar1);
      goto LAB_001b44c4;
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b4340;
    lVar12 = *(long *)(param_1 + 0x310);
  }
  else {
    if (uVar1 < 10) {
      puVar11 = &DAT_001fa418;
      if (uVar3 == 0) {
        puVar11 = &DAT_001fe008;
      }
      goto LAB_001b4508;
    }
    puVar11 = &DAT_001fe008;
    if (uVar3 != 0) {
      puVar11 = &DAT_001fa418;
    }
    SStream_concat(param_3,&DAT_001fd948,puVar11,uVar1);
LAB_001b44c4:
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b4340;
    lVar12 = *(long *)(param_1 + 0x310);
    bVar2 = *(byte *)(*(long *)(lVar12 + 0xf0) + 0x80);
    if (uVar3 != 0) {
      lVar12 = *(long *)(lVar12 + 0xf0) + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(uint *)(lVar12 + 0xa4) = -uVar1;
      *(undefined1 *)(lVar12 + 0xb0) = 1;
      goto LAB_001b4340;
    }
  }
  *(uint *)(*(long *)(lVar12 + 0xf0) + (ulong)*(byte *)(*(long *)(lVar12 + 0xf0) + 0x80) * 0x30 +
           0xa4) = uVar1;
LAB_001b4340:
  SStream_concat0(param_3,&DAT_001fdf58);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar12 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar12 = *(long *)(lVar12 + 0xf0);
    *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
  }
  return;
}

