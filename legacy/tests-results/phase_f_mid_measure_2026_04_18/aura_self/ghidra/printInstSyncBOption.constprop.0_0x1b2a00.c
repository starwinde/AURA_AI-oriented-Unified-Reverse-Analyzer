
void printInstSyncBOption_constprop_0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  MCInst_getOperand(param_1,0);
  uVar1 = MCOperand_getImm();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fda50;
    break;
  case 2:
    puVar2 = &DAT_001fda58;
    break;
  case 3:
    puVar2 = &DAT_001fda60;
    break;
  case 4:
    puVar2 = &DAT_001fda68;
    break;
  case 5:
    puVar2 = &DAT_001fda70;
    break;
  case 6:
    puVar2 = &DAT_001fda78;
    break;
  case 7:
    puVar2 = &DAT_001fda80;
    break;
  case 8:
    puVar2 = &DAT_001fda88;
    break;
  case 9:
    puVar2 = &DAT_001fda90;
    break;
  case 10:
    puVar2 = &DAT_001fda98;
    break;
  case 0xb:
    puVar2 = &DAT_001fdaa0;
    break;
  case 0xc:
    puVar2 = &DAT_001fd9c8;
    break;
  case 0xd:
    puVar2 = &DAT_001fd9c0;
    break;
  case 0xe:
    puVar2 = &DAT_001fdaa8;
    break;
  case 0xf:
    puVar2 = &DAT_001fd9b8;
    break;
  default:
    puVar2 = &DAT_001fda48;
  }
  SStream_concat0(param_2,puVar2);
  return;
}

