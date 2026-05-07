
void FUN_0014c7d4(char *param_1)

{
  size_t sVar1;
  char *pcVar2;
  char *pcVar3;
  
  sVar1 = strlen(param_1);
  pcVar3 = param_1 + (sVar1 - 1);
  if (param_1 < param_1 + (sVar1 - 1)) {
    do {
      if (*pcVar3 != ' ') break;
      pcVar2 = pcVar3 + -1;
      *pcVar3 = '\0';
      pcVar3 = pcVar2;
    } while (param_1 != pcVar2);
  }
  pcVar3 = param_1;
  if (*param_1 == ' ') {
    do {
      pcVar3 = pcVar3 + 1;
    } while (*pcVar3 == ' ');
    if (param_1 != pcVar3) {
      sVar1 = strlen(pcVar3);
      memmove(param_1,pcVar3,sVar1 + 1);
      return;
    }
  }
  return;
}

