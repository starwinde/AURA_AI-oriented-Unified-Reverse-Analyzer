
undefined4 FUN_0014c50c(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (*param_1 == '\0') {
    return 0x1d;
  }
  if ((*param_1 == 'e') && (param_1[1] == '\0')) {
    return 0xb;
  }
  cVar1 = *param_1;
  if ((cVar1 == 'z') && (param_1[1] == '\0')) {
    return 0xb;
  }
  cVar2 = *param_1;
  if (((cVar2 != 'n') ||
      (((param_1[1] != 'e' || (uVar4 = 0xc, param_1[2] != '\0')) &&
       ((param_1[1] != 'z' || (uVar4 = 0xc, param_1[2] != '\0')))))) &&
     ((cVar1 != 'l' || (uVar4 = 0xd, param_1[1] != '\0')))) {
    iVar3 = strcmp(param_1,"nge");
    uVar4 = 0xd;
    if ((iVar3 != 0) &&
       (((((cVar2 != 'l' || (param_1[1] != 'e')) || (uVar4 = 0xe, param_1[2] != '\0')) &&
         (((cVar2 != 'n' || (param_1[1] != 'g')) || (uVar4 = 0xe, param_1[2] != '\0')))) &&
        ((cVar1 != 'g' || (uVar4 = 0x11, param_1[1] != '\0')))))) {
      iVar3 = strcmp(param_1,"nle");
      uVar4 = 0x11;
      if ((((iVar3 != 0) &&
           (((cVar2 != 'g' || (param_1[1] != 'e')) || (uVar4 = 0x12, param_1[2] != '\0')))) &&
          (((cVar2 != 'n' || (param_1[1] != 'l')) || (uVar4 = 0x12, param_1[2] != '\0')))) &&
         ((cVar1 != 'b' || (uVar4 = 0xf, param_1[1] != '\0')))) {
        iVar3 = strcmp(param_1,"nae");
        uVar4 = 0xf;
        if (((iVar3 != 0) && ((cVar1 != 'c' || (param_1[1] != '\0')))) &&
           ((cVar2 != 'b' || ((param_1[1] != 'e' || (uVar4 = 0x10, param_1[2] != '\0')))))) {
          iVar3 = strcmp(param_1,"na");
          if (iVar3 == 0) {
            uVar4 = 0x10;
          }
          else {
            iVar3 = strcmp(param_1,"a");
            if ((iVar3 == 0) || (iVar3 = strcmp(param_1,"nbe"), iVar3 == 0)) {
              uVar4 = 0x13;
            }
            else {
              iVar3 = strcmp(param_1,"ae");
              if ((iVar3 == 0) || (iVar3 = strcmp(param_1,"nb"), iVar3 == 0)) {
                uVar4 = 0x14;
              }
              else {
                iVar3 = strcmp(param_1,"nc");
                uVar4 = 0x14;
                if (iVar3 != 0) {
                  uVar4 = 0x1d;
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar4;
}

