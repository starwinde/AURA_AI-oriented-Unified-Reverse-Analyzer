
long FUN_00140b70(char *param_1)

{
  long lVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  
  lVar2 = DAT_006005c8;
  lVar1 = DAT_006005c0;
  if (param_1 == (char *)0x0) {
    lVar5 = 0;
  }
  else if (DAT_006005c0 == 0) {
    lVar5 = 0;
  }
  else {
    lVar4 = 0;
    while( true ) {
      lVar5 = *(long *)(lVar2 + lVar4 * 8);
      lVar4 = lVar4 + 1;
      iVar3 = strcmp(*(char **)(lVar5 + 8),param_1);
      if (iVar3 == 0) break;
      if (lVar4 == lVar1) {
        return 0;
      }
    }
  }
  return lVar5;
}

