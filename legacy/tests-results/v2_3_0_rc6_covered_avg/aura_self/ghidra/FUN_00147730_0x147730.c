
undefined4 FUN_00147730(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  cVar1 = *param_1;
  if (cVar1 != '\0') {
    if (((cVar1 == 'r') && (param_1[1] == 'e')) && (param_1[2] == 't')) {
      return 1;
    }
    uVar4 = 1;
    iVar3 = strncmp(param_1,"iret",4);
    if ((iVar3 != 0) &&
       (((cVar2 = *param_1, cVar2 != 'b' || (param_1[1] != 'r')) || (uVar4 = 5, param_1[2] != '\0'))
       )) {
      uVar4 = 3;
      iVar3 = strcmp(param_1,"blr");
      if ((iVar3 != 0) &&
         (((cVar2 != 'b' || (param_1[1] != 'l')) || (uVar4 = 2, param_1[2] != '\0')))) {
        uVar4 = 7;
        iVar3 = strcmp(param_1,"cbz");
        if ((iVar3 != 0) && (iVar3 = strcmp(param_1,"cbnz"), iVar3 != 0)) {
          uVar4 = 8;
          iVar3 = strcmp(param_1,"tbz");
          if (((iVar3 != 0) && (iVar3 = strcmp(param_1,"tbnz"), iVar3 != 0)) &&
             ((((cVar1 != 'b' || (param_1[1] != '.')) || (uVar4 = 6, param_1[2] == '\0')) &&
              ((*param_1 != 'b' || (uVar4 = 4, param_1[1] != '\0')))))) {
            uVar4 = 2;
            iVar3 = strncmp(param_1,"call",4);
            if (iVar3 != 0) {
              uVar4 = 4;
              iVar3 = strcmp(param_1,"jmp");
              if (iVar3 != 0) {
                if (cVar1 == 'j') {
                  uVar4 = 6;
                }
                else {
                  uVar4 = 9;
                  iVar3 = strcmp(param_1,"ud2");
                  if (iVar3 != 0) {
                    iVar3 = strcmp(param_1,"hlt");
                    uVar4 = 9;
                    if (iVar3 != 0) {
                      uVar4 = 0;
                    }
                  }
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

