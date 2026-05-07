
int FUN_001099d0(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  int *piVar2;
  char *__s1;
  char *__s2;
  
  __s1 = (char *)*param_2;
  __s2 = (char *)*param_1;
  piVar2 = __errno_location();
  *piVar2 = 0;
  iVar1 = strcoll(__s1,__s2);
  return iVar1;
}

