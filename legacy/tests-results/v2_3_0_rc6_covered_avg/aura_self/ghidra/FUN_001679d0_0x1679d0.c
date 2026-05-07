
undefined4 FUN_001679d0(char *param_1)

{
  long lVar1;
  int iVar2;
  undefined4 uVar3;
  size_t __n;
  char *__s2;
  long lVar4;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  uVar3 = 0;
  if (*param_1 != '\0') {
    lVar4 = 0;
    while( true ) {
      __s2 = (&PTR_s_abort_005dfc18)[lVar4 * 2];
      iVar2 = strcmp(param_1,__s2);
      if (iVar2 == 0) break;
      __n = strlen(__s2);
      lVar1 = lVar4 + 1;
      iVar2 = strncmp(param_1,__s2,__n);
      if ((iVar2 == 0) && ((param_1[__n] & 0xbfU) == 0)) {
        return (&DAT_005dfc20)[lVar4 * 4];
      }
      lVar4 = lVar1;
      if (lVar1 == 0x1e) {
        return 0;
      }
    }
    uVar3 = (&DAT_005dfc20)[lVar4 * 4];
  }
  return uVar3;
}

