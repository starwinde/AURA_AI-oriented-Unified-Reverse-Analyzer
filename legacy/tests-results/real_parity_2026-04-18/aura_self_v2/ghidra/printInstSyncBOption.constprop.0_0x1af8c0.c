
void printInstSyncBOption_constprop_0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  MCInst_getOperand(param_1,0);
  uVar1 = MCOperand_getImm();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fb7c8;
    break;
  case 2:
    puVar2 = &DAT_001fb7d0;
    break;
  case 3:
    puVar2 = &DAT_001fb7d8;
    break;
  case 4:
    puVar2 = &DAT_001fb7e0;
    break;
  case 5:
    puVar2 = &DAT_001fb7e8;
    break;
  case 6:
    puVar2 = &DAT_001fb7f0;
    break;
  case 7:
    puVar2 = &DAT_001fb7f8;
    break;
  case 8:
    puVar2 = &DAT_001fb800;
    break;
  case 9:
    puVar2 = &DAT_001fb808;
    break;
  case 10:
    puVar2 = &DAT_001fb810;
    break;
  case 0xb:
    puVar2 = &DAT_001fb818;
    break;
  case 0xc:
    puVar2 = &DAT_001fb740;
    break;
  case 0xd:
    puVar2 = &DAT_001fb738;
    break;
  case 0xe:
    puVar2 = &DAT_001fb820;
    break;
  case 0xf:
    puVar2 = &DAT_001fb730;
    break;
  default:
    puVar2 = &DAT_001fb7c0;
  }
  SStream_concat0(param_2,puVar2);
  return;
}

