
void FUN_001b453c(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  undefined4 uVar9;
  long lVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  
  uVar6 = MCInst_getOperand();
  uVar3 = MCOperand_getImm();
  uVar4 = MCOperand_getImm(uVar6);
  uVar7 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x3e);
  if ((uVar7 & 1) == 0) {
    uVar1 = uVar4 & 0xf;
    if (uVar3 >> 4 == 0) {
      if ((0x1110UL >> uVar1 & 1) != 0) {
        SStream_concat0(param_3,"apsr_");
        if (uVar1 == 8) {
          SStream_concat0(param_3,"nzcvq");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10200000043;
        }
        else if (uVar1 == 0xc) {
          SStream_concat0(param_3,"nzcvqg");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10300000043;
        }
        else {
          SStream_concat0(param_3,"g");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10100000043;
        }
        lVar8 = *(long *)(lVar8 + 0xf0);
        bVar2 = *(byte *)(lVar8 + 0x80);
        *(undefined8 *)(lVar8 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x94) = uVar6;
        *(byte *)(lVar8 + 0x80) = bVar2 + 1;
        return;
      }
      SStream_concat0(param_3,&DAT_001fdbb8);
    }
    else {
      SStream_concat0(param_3,&DAT_001fdbb0);
    }
    if ((uVar4 & 0xf) == 0) {
      return;
    }
    SStream_concat0(param_3,&DAT_001fdbc0);
    if ((uVar4 >> 3 & 1) == 0) {
      uVar9 = 0;
      uVar11 = 1;
      uVar13 = 2;
      uVar12 = 3;
      uVar17 = 4;
      uVar16 = 5;
      uVar15 = 6;
      uVar14 = 7;
    }
    else {
      SStream_concat0(param_3,&DAT_001fdbc8);
      uVar9 = 8;
      uVar11 = 9;
      uVar13 = 10;
      uVar12 = 0xb;
      uVar17 = 0xc;
      uVar16 = 0xd;
      uVar15 = 0xe;
      uVar14 = 0xf;
    }
    if ((uVar4 >> 2 & 1) != 0) {
      SStream_concat0(param_3,"s");
      uVar9 = uVar17;
      uVar13 = uVar15;
      uVar11 = uVar16;
      uVar12 = uVar14;
    }
    if ((uVar4 >> 1 & 1) != 0) {
      SStream_concat0(param_3,&DAT_001fd950);
      uVar11 = uVar12;
      uVar9 = uVar13;
    }
    if ((uVar4 & 1) != 0) {
      SStream_concat0(param_3,"c");
      uVar9 = uVar11;
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar8 + 0x94) = 0x43;
    *(undefined4 *)(lVar8 + 0x98) = uVar9;
    *(byte *)(lVar10 + 0x80) = bVar2 + 1;
    return;
  }
  uVar3 = MCOperand_getImm(uVar6);
  iVar5 = MCInst_getOpcode(param_1);
  if (iVar5 == 0xb5b) {
    uVar7 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2c);
    if (((uVar7 & 1) != 0) &&
       (uVar4 = binsearch_IndexTypeEncoding(Index_8,0x25,uVar3 & 0xfff), uVar4 != 0xffffffff)) {
      lVar8 = (ulong)*(uint *)(Index_8 + (ulong)uVar4 * 8 + 4) * 0x20;
      if ((*(int *)(MClassSysRegsList + lVar8 + 0x14) == 0x2c) ||
         (*(int *)(MClassSysRegsList + lVar8 + 0x18) == 0x2c)) {
        lVar8 = (ulong)*(uint *)(Index_8 + (ulong)uVar4 * 8 + 4) * 0x20;
        SStream_concat0(param_3,*(undefined8 *)(MClassSysRegsList + lVar8));
        uVar9 = *(undefined4 *)(MClassSysRegsList + lVar8 + 8);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar10 + 0x80);
        lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
        *(undefined4 *)(lVar8 + 0x94) = 0x43;
        *(undefined4 *)(lVar8 + 0x98) = uVar9;
        *(byte *)(lVar10 + 0x80) = bVar2 + 1;
        return;
      }
    }
    uVar7 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6e);
    if (((uVar7 & 1) != 0) &&
       (uVar4 = binsearch_IndexTypeEncoding(Index_9,0x25,uVar3 & 0xff | 0x200), uVar4 != 0xffffffff)
       ) goto LAB_001b4664;
  }
  uVar3 = uVar3 & 0xff;
  uVar4 = binsearch_IndexTypeEncoding(Index_9,0x25,uVar3 | 0x100);
  if (uVar4 == 0xffffffff) {
    if (uVar3 < 10) {
      SStream_concat(param_3,&DAT_001fd760,uVar3);
    }
    else {
      SStream_concat(param_3,&DAT_001fdb90,uVar3);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    MCOperand_CreateImm0(param_1,uVar3);
    return;
  }
LAB_001b4664:
  uVar3 = *(uint *)(Index_9 + (ulong)uVar4 * 8 + 4);
  SStream_concat0(param_3,*(undefined8 *)(MClassSysRegsList + (ulong)uVar3 * 0x20));
  uVar9 = *(undefined4 *)(MClassSysRegsList + (ulong)uVar3 * 0x20 + 8);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar8 + 0x94) = 0x43;
    *(undefined4 *)(lVar8 + 0x98) = uVar9;
    *(byte *)(lVar10 + 0x80) = bVar2 + 1;
  }
  return;
}

