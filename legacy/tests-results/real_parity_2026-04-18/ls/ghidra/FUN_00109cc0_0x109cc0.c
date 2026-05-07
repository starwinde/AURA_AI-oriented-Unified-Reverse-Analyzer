
int FUN_00109cc0(undefined8 *param_1,undefined8 *param_2)

{
  char *__s1;
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  int *piVar4;
  char *__s;
  char *__s_00;
  
  __s = (char *)*param_2;
  pcVar2 = strrchr(__s,0x2e);
  __s_00 = (char *)*param_1;
  pcVar3 = strrchr(__s_00,0x2e);
  __s1 = "";
  if (pcVar2 != (char *)0x0) {
    __s1 = pcVar2;
  }
  pcVar2 = "";
  if (pcVar3 != (char *)0x0) {
    pcVar2 = pcVar3;
  }
  piVar4 = __errno_location();
  *piVar4 = 0;
  iVar1 = strcoll(__s1,pcVar2);
  if (iVar1 == 0) {
    iVar1 = strcoll(__s,__s_00);
    return iVar1;
  }
  return iVar1;
}

