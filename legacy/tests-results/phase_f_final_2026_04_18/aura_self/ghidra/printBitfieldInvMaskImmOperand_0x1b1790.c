
void printBitfieldInvMaskImmOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  int iVar8;
  
  MCInst_getOperand();
  uVar4 = MCOperand_getImm();
  uVar4 = ~uVar4;
  if (uVar4 == 0) {
    iVar6 = 0x20;
    iVar8 = -0x20;
    printUInt32Bang(param_3,0x20);
  }
  else {
    uVar3 = (uVar4 & 0xaaaaaaaa) >> 1 | (uVar4 & 0x55555555) << 1;
    uVar3 = (uVar3 & 0xcccccccc) >> 2 | (uVar3 & 0x33333333) << 2;
    uVar3 = (uVar3 & 0xf0f0f0f0) >> 4 | (uVar3 & 0xf0f0f0f) << 4;
    uVar3 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
    lVar7 = LZCOUNT(uVar3 >> 0x10 | uVar3 << 0x10);
    iVar6 = (int)lVar7;
    iVar8 = 0x20 - ((int)LZCOUNT(uVar4) + iVar6);
    printUInt32Bang(param_3,lVar7);
    if (9 < iVar8) {
      SStream_concat(param_3,", #0x%x",iVar8);
      goto LAB_001b17f8;
    }
  }
  SStream_concat(param_3,", #%u",iVar8);
LAB_001b17f8:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar5 + 0x80);
    lVar7 = lVar5 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    lVar1 = lVar5 + ((ulong)(byte)(bVar2 + 1) * 2 + (ulong)(byte)(bVar2 + 1)) * 0x10;
    *(undefined4 *)(lVar7 + 0x94) = 2;
    *(int *)(lVar7 + 0x98) = iVar6;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(int *)(lVar1 + 0x98) = iVar8;
    *(byte *)(lVar5 + 0x80) = bVar2 + 2;
  }
  return;
}

