
long FUN_001108c4(char *param_1,long *param_2,long param_3)

{
  long lVar1;
  int iVar2;
  size_t __n;
  size_t sVar3;
  char *__s1;
  long lVar4;
  long lVar5;
  bool bVar6;
  
  __n = strlen(param_1);
  __s1 = (char *)*param_2;
  if (__s1 == (char *)0x0) {
    lVar5 = -1;
  }
  else {
    bVar6 = false;
    lVar1 = 0;
    lVar5 = -1;
    do {
      while (lVar4 = lVar1, iVar2 = strncmp(__s1,param_1,__n), iVar2 != 0) {
LAB_00110924:
        __s1 = (char *)param_2[lVar4 + 1];
        lVar1 = lVar4 + 1;
        if (__s1 == (char *)0x0) goto LAB_00110970;
      }
      sVar3 = strlen(__s1);
      if (__n == sVar3) {
        return lVar4;
      }
      if (lVar5 != -1) {
        if (*(int *)(param_3 + lVar4 * 4) != *(int *)(param_3 + lVar5 * 4)) {
          bVar6 = true;
        }
        goto LAB_00110924;
      }
      __s1 = (char *)param_2[lVar4 + 1];
      lVar1 = lVar4 + 1;
      lVar5 = lVar4;
    } while (__s1 != (char *)0x0);
LAB_00110970:
    if (bVar6) {
      lVar5 = -2;
    }
  }
  return lVar5;
}

