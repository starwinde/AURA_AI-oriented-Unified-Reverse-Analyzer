
void FUN_001cc5dc(long param_1,undefined8 param_2,undefined8 param_3,long param_4,long param_5)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  long lVar4;
  
  MCInst_getOperand();
  uVar3 = MCOperand_getImm();
  printInt64Bang(param_3,param_5 + (ulong)uVar3 * param_4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x67);
    lVar1 = lVar4 + ((ulong)bVar2 * 8 - (ulong)bVar2) * 8;
    *(undefined4 *)(lVar1 + 0x7c) = 2;
    *(long *)(lVar1 + 0x88) = (long)(int)((int)param_5 + (int)param_4 * uVar3);
    *(byte *)(lVar4 + 0x67) = bVar2 + 1;
  }
  return;
}

