
void FUN_001ad8ac(long param_1,undefined8 param_2,undefined8 param_3,int param_4,int param_5)

{
  long lVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  
  MCInst_getOperand();
  iVar3 = MCOperand_getImm();
  param_5 = param_5 + param_4 * iVar3;
  printUInt32Bang(param_3,param_5);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(int *)(lVar1 + 0x98) = param_5;
    *(byte *)(lVar4 + 0x80) = bVar2 + 1;
  }
  return;
}

