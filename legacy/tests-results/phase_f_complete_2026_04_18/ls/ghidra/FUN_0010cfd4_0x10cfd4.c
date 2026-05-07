
int FUN_0010cfd4(int param_1,undefined8 *param_2)

{
  int iVar1;
  int *piVar2;
  char *__s1;
  
  if (param_1 == 0) {
    piVar2 = __errno_location();
    param_1 = -1;
    *piVar2 = 0x5f;
  }
  else if (param_1 == 10) {
    __s1 = (char *)*param_2;
    iVar1 = strcmp(__s1,"unlabeled");
    if (iVar1 != 0) {
      return 10;
    }
    freecon(__s1);
    *param_2 = 0;
    param_1 = -1;
    piVar2 = __errno_location();
    *piVar2 = 0x3d;
  }
  return param_1;
}

