
undefined8 FUN_0010d080(long *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  long *plVar3;
  long lVar4;
  char *__s1;
  char *__s2;
  
  __s2 = *(char **)(param_2 + 0x30);
  if ((__s2 != (char *)0x0) && ((__s2 < param_2 || (param_2 + 0x38 <= __s2)))) {
    __s1 = (char *)((long)param_1 + 9);
    if (*__s2 == '\0') {
      *(char **)(param_2 + 0x30) = "";
    }
    else {
      while (iVar1 = strcmp(__s1,__s2), iVar1 != 0) {
        while( true ) {
          if ((*__s1 == '\0') &&
             ((__s1 != (char *)((long)param_1 + 9) || ((char)param_1[1] == '\0')))) {
            sVar2 = strlen(__s2);
            sVar2 = sVar2 + 1;
            if ((long)sVar2 < (long)param_1 + (0x80 - (long)__s1)) {
              memcpy(__s1,__s2,sVar2);
              __s1[sVar2] = '\0';
            }
            else {
              lVar4 = FUN_00107ec0(__s2);
              *param_1 = lVar4;
              if (lVar4 == 0) {
                return 0;
              }
              *(undefined1 *)(lVar4 + 8) = 0;
              __s1 = (char *)(lVar4 + 9);
            }
            goto LAB_0010d140;
          }
          sVar2 = strlen(__s1);
          __s1 = __s1 + sVar2 + 1;
          if ((*__s1 != '\0') || (plVar3 = (long *)*param_1, plVar3 == (long *)0x0)) break;
          __s1 = (char *)((long)plVar3 + 9);
          iVar1 = strcmp(__s1,__s2);
          param_1 = plVar3;
          if (iVar1 == 0) goto LAB_0010d140;
        }
      }
LAB_0010d140:
      *(char **)(param_2 + 0x30) = __s1;
    }
  }
  return 1;
}

