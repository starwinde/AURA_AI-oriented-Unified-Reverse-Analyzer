
void FUN_0014c9e0(char *param_1,uint *param_2)

{
  char cVar1;
  long lVar2;
  
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if ((((cVar1 == 'y') && (param_1[1] == 'm')) && (param_1[2] == 'm')) &&
     ((byte)(param_1[3] - 0x30U) < 10)) {
    lVar2 = strtol(param_1 + 3,(char **)0x0,10);
    if ((uint)lVar2 < 0x10) {
      *param_2 = (uint)lVar2;
    }
  }
  return;
}

