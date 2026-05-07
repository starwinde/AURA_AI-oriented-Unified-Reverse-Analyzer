
void printAddrMode3OffsetOperand(long param_1,int param_2,undefined8 param_3)

{
  undefined *puVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  
  uVar7 = MCInst_getOperand();
  uVar8 = MCInst_getOperand(param_1,param_2 + 1);
  uVar3 = MCOperand_getImm();
  uVar3 = uVar3 & 0x100;
  iVar4 = MCOperand_getReg(uVar7);
  if (iVar4 == 0) {
    uVar5 = MCOperand_getImm(uVar8);
    uVar5 = uVar5 & 0xff;
    puVar1 = &DAT_001fc428;
    if (uVar3 != 0) {
      puVar1 = &DAT_001f88c0;
    }
    if (uVar5 < 10) {
      SStream_concat(param_3,"#%s%u",puVar1,uVar5);
    }
    else {
      SStream_concat(param_3,"#%s0x%x",puVar1,uVar5);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar9 + 0x80);
      lVar10 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar10 + 0x94) = 2;
      *(uint *)(lVar10 + 0x98) = uVar5;
      *(bool *)(lVar10 + 0xb0) = uVar3 != 0;
      *(byte *)(lVar9 + 0x80) = bVar2 + 1;
      return;
    }
  }
  else {
    puVar1 = &DAT_001fc428;
    if (uVar3 != 0) {
      puVar1 = &DAT_001f88c0;
    }
    SStream_concat0(param_3,puVar1);
    lVar10 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar7);
    uVar8 = (**(code **)(lVar10 + 0x78))();
    SStream_concat0(param_3,uVar8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 0x80) * 0x30 + 0x94) = 1;
      uVar6 = MCOperand_getReg(uVar7);
      lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar9 + 0x80);
      lVar10 = lVar9 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar10 + 0x98) = uVar6;
      *(bool *)(lVar10 + 0xb0) = uVar3 != 0;
      *(undefined1 *)(lVar10 + 0xb1) = 1;
      *(byte *)(lVar9 + 0x80) = bVar2 + 1;
      return;
    }
  }
  return;
}

