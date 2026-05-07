
void printT2AddrModeImm8Operand(long param_1,int param_2,undefined8 param_3,char param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  int iVar7;
  long lVar8;
  
  uVar4 = MCInst_getOperand();
  uVar5 = MCInst_getOperand(param_1,param_2 + 1);
  SStream_concat0(param_3,&DAT_001fcde0);
  set_mem_access(param_1,1);
  lVar8 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar4);
  uVar6 = (**(code **)(lVar8 + 0x78))();
  SStream_concat0(param_3,uVar6);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar3 = MCOperand_getReg(uVar4);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar3;
  }
  iVar2 = MCOperand_getImm(uVar5);
  if (iVar2 == -0x80000000) {
    iVar7 = 0;
    iVar2 = 0;
  }
  else {
    iVar7 = -iVar2;
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
      goto LAB_001b2bc8;
    }
  }
  SStream_concat(param_3,", #-0x%x",iVar7);
LAB_001b2bc8:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(int *)(lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30 + 0xa4) = iVar2;
  }
  SStream_concat0(param_3,&DAT_001fd3f8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar8 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar8 = *(long *)(lVar8 + 0xf0);
    *(char *)(lVar8 + 0x80) = *(char *)(lVar8 + 0x80) + '\x01';
  }
  return;
}

