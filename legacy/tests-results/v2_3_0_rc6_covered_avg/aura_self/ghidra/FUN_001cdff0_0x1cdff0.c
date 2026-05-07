
void FUN_001cdff0(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  char *pcVar2;
  
  FUN_0018ffd0();
  iVar1 = FUN_001900a0();
  pcVar2 = (char *)0x0;
  switch(iVar1) {
  case 0:
    pcVar2 = "eq";
    break;
  case 1:
    pcVar2 = "ne";
    break;
  case 2:
    pcVar2 = "hs";
    break;
  case 3:
    pcVar2 = "lo";
    break;
  case 4:
    pcVar2 = "mi";
    break;
  case 5:
    pcVar2 = "pl";
    break;
  case 6:
    pcVar2 = "vs";
    break;
  case 7:
    pcVar2 = "vc";
    break;
  case 8:
    pcVar2 = "hi";
    break;
  case 9:
    pcVar2 = "ls";
    break;
  case 10:
    pcVar2 = "ge";
    break;
  case 0xb:
    pcVar2 = "lt";
    break;
  case 0xc:
    pcVar2 = "gt";
    break;
  case 0xd:
    pcVar2 = "le";
    break;
  case 0xe:
    pcVar2 = "al";
    break;
  case 0xf:
    pcVar2 = "nv";
  }
  FUN_00190370(param_3,pcVar2);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) = iVar1 + 1;
  }
  return;
}

