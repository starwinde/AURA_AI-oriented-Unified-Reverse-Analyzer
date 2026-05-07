
void printSORegRegOperand(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  
  uVar5 = MCInst_getOperand();
  uVar6 = MCInst_getOperand(param_1,param_2 + 1);
  uVar7 = MCInst_getOperand(param_1,param_2 + 2);
  lVar9 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar5);
  uVar8 = (**(code **)(lVar9 + 0x78))();
  SStream_concat0(param_3,uVar8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30 + 0x94) = 1;
    uVar4 = MCOperand_getReg(uVar5);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar9 = lVar9 + (ulong)*(byte *)(lVar9 + 0x80) * 0x30;
    *(undefined4 *)(lVar9 + 0x98) = uVar4;
    *(undefined1 *)(lVar9 + 0xb1) = 1;
    uVar3 = MCOperand_getImm(uVar7);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar9 + 0x80);
    *(uint *)(lVar9 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x8c) = (uVar3 & 7) + 5;
    *(byte *)(lVar9 + 0x80) = bVar1 + 1;
  }
  uVar2 = MCOperand_getImm(uVar7);
  uVar3 = uVar2 & 7;
  SStream_concat0(param_3,", ");
  if (uVar3 == 3) {
    SStream_concat0(param_3,&DAT_001f92c8);
    goto LAB_001af7a0;
  }
  if ((uVar2 >> 2 & 1) == 0) {
    if (uVar3 == 1) {
      SStream_concat0(param_3,&DAT_001f92d0);
      goto LAB_001af7a0;
    }
    if (uVar3 == 2) {
      SStream_concat0(param_3,&DAT_001f92c0);
      goto LAB_001af7a0;
    }
  }
  else {
    if (uVar3 == 4) {
      SStream_concat0(param_3,"ror");
      goto LAB_001af7a0;
    }
    if (uVar3 == 5) {
      SStream_concat0(param_3,&DAT_001fca10);
      return;
    }
  }
  SStream_concat0(param_3,&DAT_001fd0e8);
LAB_001af7a0:
  SStream_concat0(param_3,&DAT_001fd008);
  lVar9 = *(long *)(param_1 + 800);
  MCOperand_getReg(uVar6);
  uVar5 = (**(code **)(lVar9 + 0x78))();
  SStream_concat0(param_3,uVar5);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar1 = *(byte *)(lVar9 + 0x80);
  uVar4 = MCOperand_getReg(uVar6);
  uVar3 = bVar1 - 1;
  *(undefined4 *)
   (lVar9 + ((-(ulong)(uVar3 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar3 << 1) + (long)(int)uVar3)
            * 0x10 + 0x90) = uVar4;
  return;
}

