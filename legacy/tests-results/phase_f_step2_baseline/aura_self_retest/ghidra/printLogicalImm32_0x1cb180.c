
void printLogicalImm32(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  
  MCInst_getOperand();
  uVar8 = MCOperand_getImm();
  uVar11 = (uint)uVar8 & 0x3f;
  uVar4 = ((uint)(uVar8 >> 0xc) & 1) << 6 | uVar11 ^ 0x3f;
  uVar6 = 0x1f - (int)LZCOUNT(uVar4);
  if (uVar4 == 0) {
    uVar6 = 0xffffffff;
  }
  uVar3 = 1 << (ulong)(uVar6 & 0x1f);
  uVar5 = uVar3 - 1;
  uVar4 = uVar5 & (uint)(uVar8 >> 6);
  uVar8 = (1L << ((ulong)((uVar11 & uVar5) + 1) & 0x3f)) - 1;
  if (uVar4 != 0) {
    uVar11 = 0;
    do {
      uVar11 = uVar11 + 1;
      uVar8 = (uVar8 & 1) << ((ulong)uVar5 & 0x3f) | uVar8 >> 1;
    } while (uVar11 != uVar4);
  }
  if (uVar6 != 5) {
    do {
      uVar9 = (ulong)uVar3;
      uVar3 = uVar3 << 1;
      uVar8 = uVar8 | uVar8 << (uVar9 & 0x3f);
    } while (uVar3 != 0x20);
  }
  printUInt32Bang(param_3,uVar8 & 0xffffffff);
  lVar12 = *(long *)(param_1 + 800);
  if (*(int *)(lVar12 + 0x60) == 0) {
    return;
  }
  uVar7 = MCInst_getOpcode(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar12 = AArch64_get_op_access(lVar12,uVar7);
  lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar2 = *(char *)(lVar12 + (ulong)bVar1);
  bVar1 = *(byte *)(lVar10 + 0x67);
  if (cVar2 == -0x80) {
    cVar2 = '\0';
  }
  lVar12 = lVar10 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
  *(char *)(lVar12 + 0x98) = cVar2;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar12 + 0x7c) = 2;
  *(ulong *)(lVar12 + 0x88) = uVar8;
  *(byte *)(lVar10 + 0x67) = bVar1 + 1;
  return;
}

