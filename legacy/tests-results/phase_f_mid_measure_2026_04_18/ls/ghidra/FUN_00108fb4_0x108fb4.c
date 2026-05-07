
int FUN_00108fb4(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  int *piVar2;
  char *__s1;
  char *__s2;
  
  iVar1 = ((uint)((long)param_2[0x11] < (long)param_1[0x11]) -
          (uint)((long)param_1[0x11] < (long)param_2[0x11])) +
          ((uint)((long)param_2[0x10] < (long)param_1[0x10]) -
          (uint)((long)param_1[0x10] < (long)param_2[0x10])) * 2;
  if (iVar1 == 0) {
    __s1 = (char *)*param_2;
    __s2 = (char *)*param_1;
    piVar2 = __errno_location();
    *piVar2 = 0;
    iVar1 = strcoll(__s1,__s2);
    return iVar1;
  }
  return iVar1;
}

