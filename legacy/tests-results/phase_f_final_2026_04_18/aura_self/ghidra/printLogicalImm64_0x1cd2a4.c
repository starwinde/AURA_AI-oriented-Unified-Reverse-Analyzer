
void printLogicalImm64(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  
  MCInst_getOperand();
  uVar9 = MCOperand_getImm();
  uVar12 = (uint)uVar9 & 0x3f;
  uVar5 = ((uint)(uVar9 >> 0xc) & 1) << 6 | uVar12 ^ 0x3f;
  uVar7 = 0x1f - (int)LZCOUNT(uVar5);
  if (uVar5 == 0) {
    uVar7 = 0xffffffff;
  }
  uVar4 = 1 << (ulong)(uVar7 & 0x1f);
  uVar6 = uVar4 - 1;
  uVar5 = uVar6 & (uint)(uVar9 >> 6);
  uVar9 = (1L << ((ulong)((uVar12 & uVar6) + 1) & 0x3f)) - 1;
  if (uVar5 != 0) {
    uVar12 = 0;
    do {
      uVar12 = uVar12 + 1;
      uVar9 = (uVar9 & 1) << ((ulong)uVar6 & 0x3f) | uVar9 >> 1;
    } while (uVar12 != uVar5);
  }
  if (uVar7 != 6) {
    do {
      uVar10 = (ulong)uVar4;
      uVar4 = uVar4 << 1;
      uVar9 = uVar9 | uVar9 << (uVar10 & 0x3f);
    } while (uVar4 != 0x40);
  }
  uVar12 = **(uint **)(param_1 + 0x310);
  if (uVar12 == 0x2ac) {
LAB_001cd378:
    if (uVar9 < 10) {
      SStream_concat(param_3,&DAT_001fcbd8,uVar9 & 0xffffffff);
      lVar13 = *(long *)(param_1 + 800);
      iVar1 = *(int *)(lVar13 + 0x60);
      goto joined_r0x001cd3c8;
    }
    SStream_concat(param_3,"#0x%lx",uVar9);
  }
  else {
    if (uVar12 < 0x2ad) {
      if ((uVar12 == 0x19) || (uVar12 == 0x120)) goto LAB_001cd378;
    }
    else if (uVar12 == 0x467) goto LAB_001cd378;
    printInt64Bang(param_3,uVar9);
  }
  lVar13 = *(long *)(param_1 + 800);
  iVar1 = *(int *)(lVar13 + 0x60);
joined_r0x001cd3c8:
  if (iVar1 == 0) {
    return;
  }
  uVar8 = MCInst_getOpcode(param_1);
  bVar2 = *(byte *)(param_1 + 0x366);
  lVar13 = AArch64_get_op_access(lVar13,uVar8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar3 = *(char *)(lVar13 + (ulong)bVar2);
  bVar2 = *(byte *)(lVar11 + 0x67);
  if (cVar3 == -0x80) {
    cVar3 = '\0';
  }
  lVar13 = lVar11 + ((ulong)bVar2 * 8 - (ulong)bVar2) * 8;
  *(char *)(lVar13 + 0x98) = cVar3;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar13 + 0x7c) = 2;
  *(ulong *)(lVar13 + 0x88) = uVar9;
  *(byte *)(lVar11 + 0x67) = bVar2 + 1;
  return;
}

