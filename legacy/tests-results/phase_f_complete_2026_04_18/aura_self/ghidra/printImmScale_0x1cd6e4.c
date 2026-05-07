
void printImmScale(long param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  MCInst_getOperand();
  lVar4 = MCOperand_getImm();
  lVar4 = param_4 * lVar4;
  printInt64Bang(param_3,lVar4);
  lVar6 = *(long *)(param_1 + 800);
  if (*(int *)(lVar6 + 0x60) != 0) {
    if ((*(byte *)(lVar6 + 0x6c) & 1) == 0) {
      uVar3 = MCInst_getOpcode(param_1);
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar6 = AArch64_get_op_access(lVar6,uVar3);
      lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      cVar2 = *(char *)(lVar6 + (ulong)bVar1);
      bVar1 = *(byte *)(lVar5 + 0x67);
      if (cVar2 == -0x80) {
        cVar2 = '\0';
      }
      lVar6 = lVar5 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
      *(char *)(lVar6 + 0x98) = cVar2;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar6 + 0x7c) = 2;
      *(long *)(lVar6 + 0x88) = lVar4;
      *(byte *)(lVar5 + 0x67) = bVar1 + 1;
      return;
    }
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(int *)(lVar6 + (ulong)*(byte *)(lVar6 + 0x67) * 0x38 + 0x90) = (int)lVar4;
  }
  return;
}

