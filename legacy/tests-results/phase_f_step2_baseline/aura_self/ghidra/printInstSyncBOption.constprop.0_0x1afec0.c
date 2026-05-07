
void printInstSyncBOption_constprop_0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  MCInst_getOperand(param_1,0);
  uVar1 = MCOperand_getImm();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fbe70;
    break;
  case 2:
    puVar2 = &DAT_001fbe78;
    break;
  case 3:
    puVar2 = &DAT_001fbe80;
    break;
  case 4:
    puVar2 = &DAT_001fbe88;
    break;
  case 5:
    puVar2 = &DAT_001fbe90;
    break;
  case 6:
    puVar2 = &DAT_001fbe98;
    break;
  case 7:
    puVar2 = &DAT_001fbea0;
    break;
  case 8:
    puVar2 = &DAT_001fbea8;
    break;
  case 9:
    puVar2 = &DAT_001fbeb0;
    break;
  case 10:
    puVar2 = &DAT_001fbeb8;
    break;
  case 0xb:
    puVar2 = &DAT_001fbec0;
    break;
  case 0xc:
    puVar2 = &DAT_001fbde8;
    break;
  case 0xd:
    puVar2 = &DAT_001fbde0;
    break;
  case 0xe:
    puVar2 = &DAT_001fbec8;
    break;
  case 0xf:
    puVar2 = &DAT_001fbdd8;
    break;
  default:
    puVar2 = &DAT_001fbe68;
  }
  SStream_concat0(param_2,puVar2);
  return;
}

