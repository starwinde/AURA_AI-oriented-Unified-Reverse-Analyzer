
void printInstSyncBOption_constprop_0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  MCInst_getOperand(param_1,0);
  uVar1 = MCOperand_getImm();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fcef0;
    break;
  case 2:
    puVar2 = &DAT_001fcef8;
    break;
  case 3:
    puVar2 = &DAT_001fcf00;
    break;
  case 4:
    puVar2 = &DAT_001fcf08;
    break;
  case 5:
    puVar2 = &DAT_001fcf10;
    break;
  case 6:
    puVar2 = &DAT_001fcf18;
    break;
  case 7:
    puVar2 = &DAT_001fcf20;
    break;
  case 8:
    puVar2 = &DAT_001fcf28;
    break;
  case 9:
    puVar2 = &DAT_001fcf30;
    break;
  case 10:
    puVar2 = &DAT_001fcf38;
    break;
  case 0xb:
    puVar2 = &DAT_001fcf40;
    break;
  case 0xc:
    puVar2 = &DAT_001fce68;
    break;
  case 0xd:
    puVar2 = &DAT_001fce60;
    break;
  case 0xe:
    puVar2 = &DAT_001fcf48;
    break;
  case 0xf:
    puVar2 = &DAT_001fce58;
    break;
  default:
    puVar2 = &DAT_001fcee8;
  }
  SStream_concat0(param_2,puVar2);
  return;
}

