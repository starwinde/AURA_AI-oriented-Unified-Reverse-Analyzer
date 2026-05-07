
void FUN_001b2ff0(undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  FUN_0018ffd0(param_1,0);
  uVar1 = FUN_001900a0();
  switch(uVar1) {
  case 1:
    puVar2 = &DAT_001fe090;
    break;
  case 2:
    puVar2 = &DAT_001fe098;
    break;
  case 3:
    puVar2 = &DAT_001fe0a0;
    break;
  case 4:
    puVar2 = &DAT_001fe0a8;
    break;
  case 5:
    puVar2 = &DAT_001fe0b0;
    break;
  case 6:
    puVar2 = &DAT_001fe0b8;
    break;
  case 7:
    puVar2 = &DAT_001fe0c0;
    break;
  case 8:
    puVar2 = &DAT_001fe0c8;
    break;
  case 9:
    puVar2 = &DAT_001fe0d0;
    break;
  case 10:
    puVar2 = &DAT_001fe0d8;
    break;
  case 0xb:
    puVar2 = &DAT_001fe0e0;
    break;
  case 0xc:
    puVar2 = &DAT_001fe008;
    break;
  case 0xd:
    puVar2 = (undefined *)0x1fe000;
    break;
  case 0xe:
    puVar2 = &DAT_001fe0e8;
    break;
  case 0xf:
    puVar2 = &DAT_001fdff8;
    break;
  default:
    puVar2 = &DAT_001fe088;
  }
  FUN_00190370(param_2,puVar2);
  return;
}

