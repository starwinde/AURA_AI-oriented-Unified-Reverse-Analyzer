
void printPredicateOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  MCInst_getOperand();
  iVar2 = MCOperand_getImm();
  if (iVar2 == 0xf) {
    SStream_concat0(param_3,"<und>");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x74) = 0;
      return;
    }
  }
  else {
    if (iVar2 == 0xe) {
      iVar1 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    }
    else {
      switch(iVar2) {
      case 0:
        pcVar3 = "eq";
        break;
      case 1:
        pcVar3 = "ne";
        break;
      case 2:
        pcVar3 = "hs";
        break;
      case 3:
        pcVar3 = "lo";
        break;
      case 4:
        pcVar3 = "mi";
        break;
      case 5:
        pcVar3 = "pl";
        break;
      case 6:
        pcVar3 = "vs";
        break;
      case 7:
        pcVar3 = "vc";
        break;
      case 8:
        pcVar3 = "hi";
        break;
      case 9:
        pcVar3 = "ls";
        break;
      case 10:
        pcVar3 = "ge";
        break;
      case 0xb:
        pcVar3 = "lt";
        break;
      case 0xc:
        pcVar3 = "gt";
        break;
      case 0xd:
        pcVar3 = "le";
        break;
      default:
        pcVar3 = "";
      }
      SStream_concat0(param_3,pcVar3);
      iVar1 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    }
    if (iVar1 != 0) {
      *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x74) = iVar2 + 1;
    }
  }
  return;
}

