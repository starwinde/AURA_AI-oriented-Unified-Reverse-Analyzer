
void printShifter(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  char *pcVar5;
  undefined4 uVar6;
  uint uVar7;
  
  MCInst_getOperand();
  uVar3 = MCOperand_getImm();
  uVar7 = uVar3 >> 6 & 7;
  if (4 < uVar7) {
    SStream_concat(param_3,", %s ",0);
    printInt32BangDec(param_3,uVar3 & 0x3f);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    uVar6 = 1;
    goto LAB_001ccb08;
  }
  uVar1 = uVar3 & 0x3f;
  if (uVar7 == 0) {
    if (uVar1 == 0) {
      return;
    }
    SStream_concat(param_3,", %s ",&DAT_001f9678);
    printInt32BangDec(param_3,uVar1);
    uVar6 = 1;
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    goto LAB_001ccb08;
  }
  if (uVar7 == 2) {
    pcVar5 = "asr";
LAB_001ccbd0:
    SStream_concat(param_3,", %s ",pcVar5);
    printInt32BangDec(param_3,uVar1);
    uVar7 = uVar7 - 1;
    iVar2 = *(int *)(*(long *)(param_1 + 800) + 0x60);
  }
  else {
    if (uVar7 < 3) {
      pcVar5 = "lsr";
      goto LAB_001ccbd0;
    }
    if (uVar7 == 3) {
      pcVar5 = "ror";
      goto LAB_001ccbd0;
    }
    SStream_concat(param_3,", %s ",&DAT_001feac8);
    printInt32BangDec(param_3,uVar1);
    uVar7 = 3;
    iVar2 = *(int *)(*(long *)(param_1 + 800) + 0x60);
  }
  if (iVar2 == 0) {
    return;
  }
  uVar6 = *(undefined4 *)(CSWTCH_132 + (ulong)uVar7 * 4);
LAB_001ccb08:
  lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  uVar7 = *(byte *)(lVar4 + 0x67) - 1;
  lVar4 = lVar4 + ((-(ulong)(uVar7 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar7 << 3) -
                  (long)(int)uVar7) * 8;
  *(undefined4 *)(lVar4 + 0x70) = uVar6;
  *(uint *)(lVar4 + 0x74) = uVar3 & 0x3f;
  return;
}

