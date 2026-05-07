
void FUN_001b0a0c(long param_1,int param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  long lVar9;
  ulong uVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  
  uVar8 = MCInst_getOperand();
  uVar5 = MCOperand_getImm();
  lVar9 = MCOperand_getImm(uVar8);
  uVar5 = uVar5 & 0xff;
  uVar1 = (uint)(lVar9 >> 7) & 0x1e;
  iVar6 = MCInst_getOpcode(param_1);
  if (iVar6 == 0x2ac) {
    MCInst_getOperand(param_1,param_2 + -1);
    iVar6 = MCOperand_getReg();
    bVar4 = iVar6 == 0xb;
  }
  else {
    bVar4 = iVar6 == 699;
  }
  uVar3 = uVar5 >> uVar1 | uVar5 << 0x20 - uVar1;
  uVar14 = (ulong)uVar3;
  if (0xff < uVar3) {
    uVar7 = (uVar3 & 0xaaaaaaaa) >> 1 | (uVar3 & 0x55555555) << 1;
    uVar7 = (uVar7 & 0xcccccccc) >> 2 | (uVar7 & 0x33333333) << 2;
    uVar7 = (uVar7 & 0xf0f0f0f0) >> 4 | (uVar7 & 0xf0f0f0f) << 4;
    uVar7 = (uVar7 & 0xff00ff00) >> 8 | (uVar7 & 0xff00ff) << 8;
    uVar11 = (uint)LZCOUNT(uVar7 >> 0x10 | uVar7 << 0x10);
    uVar7 = uVar11 & 0x1e;
    if ((((uVar3 >> uVar7 | uVar3 << 0x20 - uVar7) < 0x100) || ((uVar3 & 0x3f) == 0)) ||
       (uVar7 = (uVar3 & 0xaaaaaa80) >> 1 | (uVar3 & 0x55555540) << 1,
       uVar7 = (uVar7 & 0xcccccccc) >> 2 | (uVar7 & 0x33333333) << 2,
       uVar7 = (uVar7 & 0xf0f0f0f0) >> 4 | (uVar7 & 0xf0f0f0f) << 4,
       uVar7 = (uVar7 & 0xff00ff00) >> 8 | (uVar7 & 0xff00ff) << 8,
       uVar7 = (uint)LZCOUNT(uVar7 >> 0x10 | uVar7 << 0x10),
       0xff < (uVar3 >> (uVar7 & 0x1e) | uVar3 << 0x20 - (uVar7 & 0x1e)))) {
      uVar7 = uVar11;
    }
    uVar7 = -(uVar7 & 0xfffffffe) & 0x1f;
    if (((0xffffff00U >> uVar7 | -0x100 << 0x20 - uVar7) & uVar3) == 0) {
      uVar14 = (ulong)(int)(uVar3 >> (-uVar7 & 0x1f) | uVar3 << 0x20 - (-uVar7 & 0x1f) |
                           (uVar7 >> 1) << 8);
    }
    else {
      uVar14 = 0xffffffffffffffff;
    }
  }
  uVar10 = MCOperand_getImm(uVar8);
  if (uVar10 != uVar14) {
    SStream_concat(param_3,"#%u, #%u",uVar5,uVar1);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar13 + 0x80);
    lVar9 = lVar13 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    lVar12 = lVar13 + ((ulong)(byte)(bVar2 + 1) * 2 + (ulong)(byte)(bVar2 + 1)) * 0x10;
    *(undefined4 *)(lVar9 + 0x94) = 2;
    *(uint *)(lVar9 + 0x98) = uVar5;
    *(undefined4 *)(lVar12 + 0x94) = 2;
    *(uint *)(lVar12 + 0x98) = uVar1;
    *(byte *)(lVar13 + 0x80) = bVar2 + 2;
    return;
  }
  if (bVar4) {
    if (0x12 < uVar3 + 9) goto LAB_001b0bf4;
  }
  else if (((int)uVar3 < 0) || (9 < (int)uVar3)) {
LAB_001b0bf4:
    SStream_concat(param_3,"#0x%x",uVar3);
    goto LAB_001b0b7c;
  }
  SStream_concat(param_3,&DAT_001fc818,(ulong)uVar3);
LAB_001b0b7c:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar2 = *(byte *)(lVar12 + 0x80);
  lVar9 = lVar12 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
  *(undefined4 *)(lVar9 + 0x94) = 2;
  *(uint *)(lVar9 + 0x98) = uVar3;
  *(byte *)(lVar12 + 0x80) = bVar2 + 1;
  return;
}

