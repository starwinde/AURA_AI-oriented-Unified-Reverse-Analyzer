
bool FUN_00175690(char *param_1)

{
  bool bVar1;
  int iVar2;
  
  if (((*param_1 != 'c') || (param_1[1] != 'a')) || (bVar1 = true, param_1[2] != 's')) {
    bVar1 = true;
    iVar2 = strcmp(param_1,"cmp");
    if ((((iVar2 != 0) && (iVar2 = strcmp(param_1,"cmn"), iVar2 != 0)) &&
        ((iVar2 = strcmp(param_1,"tst"), iVar2 != 0 &&
         ((iVar2 = strcmp(param_1,"ccmp"), iVar2 != 0 &&
          (iVar2 = strcmp(param_1,"ccmn"), iVar2 != 0)))))) &&
       ((iVar2 = strcmp(param_1,"str"), iVar2 != 0 &&
        ((((iVar2 = strcmp(param_1,"strb"), iVar2 != 0 &&
           (iVar2 = strcmp(param_1,"strh"), iVar2 != 0)) &&
          (iVar2 = strcmp(param_1,"stp"), iVar2 != 0)) &&
         (iVar2 = strcmp(param_1,"cbz"), iVar2 != 0)))))) {
      iVar2 = strcmp(param_1,"cbnz");
      if (((iVar2 == 0) || (iVar2 = strcmp(param_1,"tbz"), iVar2 == 0)) ||
         (((iVar2 = strcmp(param_1,"tbnz"), iVar2 == 0 ||
           ((iVar2 = strcmp(param_1,"b"), iVar2 == 0 || (iVar2 = strcmp(param_1,"bl"), iVar2 == 0)))
           ) || (iVar2 = strcmp(param_1,"br"), iVar2 == 0)))) {
        bVar1 = true;
      }
      else {
        iVar2 = strcmp(param_1,"blr");
        bVar1 = iVar2 == 0;
      }
    }
  }
  return bVar1;
}

