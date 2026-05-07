
__uid_t * FUN_0010e300(__uid_t param_1)

{
  passwd *ppVar1;
  size_t sVar2;
  __uid_t *p_Var3;
  char *__s;
  
  for (p_Var3 = DAT_001412b8; p_Var3 != (__uid_t *)0x0; p_Var3 = *(__uid_t **)(p_Var3 + 2)) {
    if (*p_Var3 == param_1) {
      p_Var3 = p_Var3 + 4;
      if ((char)*p_Var3 == '\0') {
        p_Var3 = (__uid_t *)0x0;
      }
      return p_Var3;
    }
  }
  ppVar1 = getpwuid(param_1);
  if (ppVar1 == (passwd *)0x0) {
    sVar2 = 0x18;
    __s = "";
  }
  else {
    __s = ppVar1->pw_name;
    sVar2 = strlen(__s);
    sVar2 = sVar2 + 0x18 & 0xfffffffffffffff8;
  }
  p_Var3 = malloc(sVar2);
  if (p_Var3 != (__uid_t *)0x0) {
    *p_Var3 = param_1;
    __strcpy_chk(p_Var3 + 4,__s,sVar2 - 0x10);
    *(__uid_t **)(p_Var3 + 2) = DAT_001412b8;
    DAT_001412b8 = p_Var3;
    p_Var3 = p_Var3 + 4;
    if ((char)*p_Var3 == '\0') {
      p_Var3 = (__uid_t *)0x0;
    }
    return p_Var3;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

