
void FUN_001cad3c(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  undefined8 uVar2;
  long lVar3;
  
  MCInst_getOperand();
  uVar2 = MCOperand_getImm();
  printInt64(param_3,uVar2);
  if ((*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) &&
     ((*(byte *)(*(long *)(param_1 + 800) + 0x6d) & 1) != 0)) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar1 = *(byte *)(lVar3 + 0x67) - 1;
    *(int *)(lVar3 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3) -
                     (long)(int)uVar1) * 8 + 0x90) = (int)uVar2;
  }
  return;
}

