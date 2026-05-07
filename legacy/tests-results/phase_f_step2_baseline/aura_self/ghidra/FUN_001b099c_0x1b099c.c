
void FUN_001b099c(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  
  uVar5 = MCInst_getOperand();
  uVar6 = MCInst_getOperand(param_1,param_2 + 1);
  SStream_concat0(param_3,&DAT_001fbd60);
  set_mem_access(param_1,1);
  lVar8 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar5);
  uVar7 = (**(code **)(lVar8 + 0x78))();
  SStream_concat0(param_3,uVar7);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar8 + 0x80);
    uVar4 = MCOperand_getReg(uVar5);
    *(undefined4 *)(lVar8 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar4;
  }
  iVar3 = MCOperand_getImm(uVar6);
  if (iVar3 != 0) {
    uVar2 = iVar3 << 3;
    if (uVar2 < 10) {
      SStream_concat(param_3,&DAT_001fbf88,uVar2);
    }
    else {
      SStream_concat(param_3,":0x%x",uVar2);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar8 + (ulong)*(byte *)(lVar8 + 0x80) * 0x30 + 0xa4) = uVar2;
    }
  }
  SStream_concat0(param_3,&DAT_001fc378);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar8 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar8 = *(long *)(lVar8 + 0xf0);
    *(char *)(lVar8 + 0x80) = *(char *)(lVar8 + 0x80) + '\x01';
  }
  return;
}

