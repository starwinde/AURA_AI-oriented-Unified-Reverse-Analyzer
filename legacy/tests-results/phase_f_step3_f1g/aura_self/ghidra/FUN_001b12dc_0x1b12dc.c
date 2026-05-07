
void FUN_001b12dc(long param_1,undefined8 param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  
  MCInst_getOperand(param_1,0);
  iVar1 = MCOperand_getImm();
  uVar2 = ARM_getFeatureBits(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71);
  switch(iVar1) {
  case 0:
    pcVar3 = "#0";
    break;
  case 1:
    pcVar3 = "#1";
    if ((uVar2 & 1) != 0) {
      pcVar3 = "oshld";
    }
    break;
  case 2:
    pcVar3 = "oshst";
    break;
  case 3:
    pcVar3 = "osh";
    break;
  case 4:
    pcVar3 = "#4";
    break;
  case 5:
    pcVar3 = "#5";
    if ((uVar2 & 1) != 0) {
      pcVar3 = "nshld";
    }
    break;
  case 6:
    pcVar3 = "nshst";
    break;
  case 7:
    pcVar3 = "nsh";
    break;
  case 8:
    pcVar3 = "#8";
    break;
  case 9:
    pcVar3 = "#9";
    if ((uVar2 & 1) != 0) {
      pcVar3 = "ishld";
    }
    break;
  case 10:
    pcVar3 = "ishst";
    break;
  case 0xb:
    pcVar3 = "ish";
    break;
  case 0xc:
    pcVar3 = "#0xc";
    break;
  case 0xd:
    pcVar3 = "#0xd";
    if ((uVar2 & 1) != 0) {
      pcVar3 = "ld";
    }
    break;
  case 0xe:
    pcVar3 = "st";
    break;
  case 0xf:
    pcVar3 = "sy";
    break;
  default:
    pcVar3 = "BUGBUG";
  }
  SStream_concat0(param_2,pcVar3);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x7c) = iVar1 + 1;
  }
  return;
}

