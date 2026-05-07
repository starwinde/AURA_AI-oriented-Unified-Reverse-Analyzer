
bool FUN_0014c870(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if ((cVar1 != '[') && (pcVar2 = strstr(param_1,"ptr"), pcVar2 == (char *)0x0)) {
    pcVar2 = strchr(param_1,0x5b);
    return pcVar2 != (char *)0x0;
  }
  return true;
}

