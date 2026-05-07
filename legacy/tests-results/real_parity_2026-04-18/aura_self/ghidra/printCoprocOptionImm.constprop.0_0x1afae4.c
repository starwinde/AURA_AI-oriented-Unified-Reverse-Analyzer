
void printCoprocOptionImm_constprop_0(long param_1,undefined8 param_2)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  long lVar4;
  
  MCInst_getOperand(param_1,3);
  uVar3 = MCOperand_getImm();
  if (uVar3 < 10) {
    SStream_concat(param_2,&DAT_001fb830,uVar3);
  }
  else {
    SStream_concat(param_2,"{0x%x}",uVar3);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(uint *)(lVar1 + 0x98) = uVar3;
    *(byte *)(lVar4 + 0x80) = bVar2 + 1;
  }
  return;
}

