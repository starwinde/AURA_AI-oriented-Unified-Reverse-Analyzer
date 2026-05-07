
void FUN_001b29cc(long param_1,int param_2,undefined8 param_3)

{
  undefined *puVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long lVar11;
  long lVar12;
  
  MCInst_getOperand();
  uVar7 = MCOperand_isReg();
  if ((uVar7 & 1) != 0) {
    uVar8 = MCInst_getOperand(param_1,param_2);
    uVar9 = MCInst_getOperand(param_1,param_2 + 1);
    uVar10 = MCInst_getOperand(param_1,param_2 + 2);
    uVar3 = MCOperand_getImm();
    uVar4 = MCOperand_getImm(uVar10);
    SStream_concat0(param_3,&DAT_001fc3c0);
    set_mem_access(param_1,1);
    lVar11 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar8);
    uVar10 = (**(code **)(lVar11 + 0x78))();
    SStream_concat0(param_3,uVar10);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      iVar5 = MCOperand_getReg(uVar9);
    }
    else {
      lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar11 + 0x80);
      uVar6 = MCOperand_getReg(uVar8);
      *(undefined4 *)(lVar11 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x98) = uVar6;
      iVar5 = MCOperand_getReg(uVar9);
    }
    if (iVar5 == 0) {
      uVar4 = uVar3 & 0xfff;
      if (uVar4 != 0) {
        uVar3 = uVar3 & 0x1000;
        SStream_concat0(param_3,", ");
        if (uVar4 < 10) {
          puVar1 = &DAT_001fca88;
          if (uVar3 != 0) {
            puVar1 = &DAT_001f8e98;
          }
          SStream_concat(param_3,"#%s%u",puVar1,uVar4);
        }
        else {
          puVar1 = &DAT_001fca88;
          if (uVar3 != 0) {
            puVar1 = &DAT_001f8e98;
          }
          SStream_concat(param_3,"#%s0x%x",puVar1,uVar4);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          lVar11 = lVar11 + (ulong)*(byte *)(lVar11 + 0x80) * 0x30;
          *(uint *)(lVar11 + 0x8c) = (uint)(uVar3 == 0);
          *(uint *)(lVar11 + 0x90) = uVar4;
          *(bool *)(lVar11 + 0xb0) = uVar3 != 0;
        }
      }
    }
    else {
      SStream_concat0(param_3,", ");
      puVar1 = &DAT_001fca88;
      if ((uVar4 & 0x1000) != 0) {
        puVar1 = &DAT_001f8e98;
      }
      SStream_concat0(param_3,puVar1);
      lVar11 = *(long *)(param_1 + 800);
      MCOperand_getReg(uVar9);
      uVar8 = (**(code **)(lVar11 + 0x78))();
      SStream_concat0(param_3,uVar8);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar12 + 0x80);
        uVar6 = MCOperand_getReg(uVar9);
        lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x9c) = uVar6;
        *(bool *)(lVar11 + (ulong)*(byte *)(lVar11 + 0x80) * 0x30 + 0xb0) = (uVar4 & 0x1000) != 0;
      }
      uVar4 = uVar3 >> 0xd & 7;
      if ((uVar4 != 0) && ((uVar3 & 0xfff) != 0 || uVar4 != 2)) {
        printRegImmShift_part_0(param_1,param_3,uVar4,uVar3 & 0xfff);
      }
    }
    SStream_concat0(param_3,&DAT_001fc9d8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
      lVar11 = *(long *)(param_1 + 0x310);
      *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
      lVar11 = *(long *)(lVar11 + 0xf0);
      *(char *)(lVar11 + 0x80) = *(char *)(lVar11 + 0x80) + '\x01';
    }
    return;
  }
  printOperand(param_1,param_2,param_3);
  return;
}

