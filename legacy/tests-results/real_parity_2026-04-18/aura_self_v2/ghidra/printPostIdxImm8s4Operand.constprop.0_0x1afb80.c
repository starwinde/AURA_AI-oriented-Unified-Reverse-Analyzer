
void printPostIdxImm8s4Operand_constprop_0(long param_1,undefined8 param_2)

{
  long lVar1;
  uint uVar2;
  undefined *puVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  
  MCInst_getOperand(param_1,3);
  uVar6 = MCOperand_getImm();
  uVar5 = (uVar6 & 0xff) * 4;
  puVar3 = &DAT_001f8278;
  if ((uVar6 & 0x100) != 0) {
    puVar3 = &DAT_001fbd80;
  }
  if (uVar5 < 10) {
    SStream_concat(param_2,"#%s%u",puVar3,uVar5);
  }
  else {
    SStream_concat(param_2,"#%s0x%x",puVar3,uVar5);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    uVar2 = (uVar6 & 0xff) * -4;
    if ((uVar6 & 0x100) != 0) {
      uVar2 = uVar5;
    }
    lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar4 = *(byte *)(lVar7 + 0x80);
    lVar1 = lVar7 + ((ulong)bVar4 * 2 + (ulong)bVar4) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(uint *)(lVar1 + 0x98) = uVar2;
    *(byte *)(lVar7 + 0x80) = bVar4 + 1;
  }
  return;
}

