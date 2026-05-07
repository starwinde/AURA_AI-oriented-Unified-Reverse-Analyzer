
void printInstSyncBOption_constprop_0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  MCInst_getOperand(param_1,0);
  uVar1 = MCOperand_getImm();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fcb30;
    break;
  case 2:
    puVar2 = &DAT_001fcb38;
    break;
  case 3:
    puVar2 = &DAT_001fcb40;
    break;
  case 4:
    puVar2 = &DAT_001fcb48;
    break;
  case 5:
    puVar2 = &DAT_001fcb50;
    break;
  case 6:
    puVar2 = &DAT_001fcb58;
    break;
  case 7:
    puVar2 = &DAT_001fcb60;
    break;
  case 8:
    puVar2 = &DAT_001fcb68;
    break;
  case 9:
    puVar2 = &DAT_001fcb70;
    break;
  case 10:
    puVar2 = &DAT_001fcb78;
    break;
  case 0xb:
    puVar2 = &DAT_001fcb80;
    break;
  case 0xc:
    puVar2 = &DAT_001fcaa8;
    break;
  case 0xd:
    puVar2 = &DAT_001fcaa0;
    break;
  case 0xe:
    puVar2 = &DAT_001fcb88;
    break;
  case 0xf:
    puVar2 = &DAT_001fca98;
    break;
  default:
    puVar2 = &DAT_001fcb28;
  }
  SStream_concat0(param_2,puVar2);
  return;
}

