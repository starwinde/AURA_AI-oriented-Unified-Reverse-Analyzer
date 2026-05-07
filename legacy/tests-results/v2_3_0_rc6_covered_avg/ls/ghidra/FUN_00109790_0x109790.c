
int FUN_00109790(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  int *piVar2;
  char *__s1;
  char *__s2;
  
  iVar1 = (uint)((long)param_2[9] < (long)param_1[9]) - (uint)((long)param_1[9] < (long)param_2[9]);
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

