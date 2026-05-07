
void FUN_001b336c(long param_1,undefined8 param_2)

{
  long lVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  
  MCInst_getOperand(param_1,2);
  iVar3 = MCOperand_getImm();
  printUInt32Bang(param_2,iVar3 << 2);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(int *)(lVar1 + 0x98) = iVar3 << 2;
    *(byte *)(lVar4 + 0x80) = bVar2 + 1;
  }
  return;
}

