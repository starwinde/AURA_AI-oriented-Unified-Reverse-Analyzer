
void FUN_001b31ec(long param_1,int param_2,undefined8 param_3,char param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  int iVar8;
  long lVar9;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCInst_getOperand(param_1,param_2 + 1);
  uVar6 = MCOperand_isReg(uVar4);
  if ((uVar6 & 1) == 0) {
    printOperand(param_1,param_2,param_3);
    return;
  }
  SStream_concat0(param_3,&DAT_001fcde0);
  set_mem_access(param_1,1);
  lVar9 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar7 = (**(code **)(lVar9 + 0x78))();
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar2 = MCOperand_getImm(uVar5);
    if (iVar2 != -0x80000000) goto LAB_001b3298;
LAB_001b32c8:
    iVar8 = 0;
    iVar2 = 0;
  }
  else {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar9 + 0x80);
    uVar3 = MCOperand_getReg(uVar4);
    *(undefined4 *)(lVar9 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
    iVar2 = MCOperand_getImm(uVar5);
    if (iVar2 == -0x80000000) goto LAB_001b32c8;
LAB_001b3298:
    if (-1 < iVar2) {
      if (iVar2 < 1 && param_4 == '\0') {
        iVar2 = 0;
      }
      else if (iVar2 < 10) {
        SStream_concat(param_3,", #%u",iVar2);
      }
      else {
        SStream_concat(param_3,", #0x%x",iVar2);
      }
      goto LAB_001b32e0;
    }
    iVar8 = -iVar2;
    if (iVar2 < -9) {
      SStream_concat(param_3,", #-0x%x",iVar8);
      goto LAB_001b32e0;
    }
  }
  SStream_concat(param_3,", #-%u",iVar8);
LAB_001b32e0:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(int *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30 + 0xa4) = iVar2;
  }
  SStream_concat0(param_3,&DAT_001fd3f8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar9 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar9 = *(long *)(lVar9 + 0xf0);
    *(char *)(lVar9 + 0x80) = *(char *)(lVar9 + 0x80) + '\x01';
  }
  return;
}

