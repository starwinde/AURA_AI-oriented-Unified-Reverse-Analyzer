
undefined8 FUN_0014c4a0(char *param_1,uint *param_2)

{
  char cVar1;
  byte bVar2;
  
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if ((cVar1 == 's') && (param_1[1] == 't')) {
    bVar2 = param_1[2];
    if (bVar2 == 0x28) {
      bVar2 = param_1[3];
    }
    if ((bVar2 - 0x30 & 0xff) < 8) {
      *param_2 = bVar2 - 0x30;
      return 1;
    }
  }
  return 0;
}

