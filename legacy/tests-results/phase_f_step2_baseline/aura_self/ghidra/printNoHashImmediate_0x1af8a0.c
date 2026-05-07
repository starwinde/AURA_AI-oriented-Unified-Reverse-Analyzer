
void printNoHashImmediate(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  undefined4 uVar3;
  long lVar4;
  
  MCInst_getOperand();
  uVar3 = MCOperand_getImm();
  printUInt32(param_3,uVar3);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    if ((*(byte *)(*(long *)(param_1 + 800) + 0x6c) & 1) == 0) {
      lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
      *(undefined4 *)(lVar1 + 0x94) = 2;
      *(undefined4 *)(lVar1 + 0x98) = uVar3;
      *(byte *)(lVar4 + 0x80) = bVar2 + 1;
      return;
    }
    bVar2 = bVar2 - 1;
    *(byte *)(lVar4 + 0x80) = bVar2;
    *(char *)(lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xb2) = (char)uVar3;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + -1;
  }
  return;
}

