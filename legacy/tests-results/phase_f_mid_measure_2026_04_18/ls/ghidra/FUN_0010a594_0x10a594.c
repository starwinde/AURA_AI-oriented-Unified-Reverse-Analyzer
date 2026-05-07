
int FUN_0010a594(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  long lVar4;
  char *__s1;
  char *__s2;
  
  lVar4 = param_2[0x17];
  if (lVar4 == 0) {
    lVar4 = FUN_0010a130(*param_2,DAT_00140f20,*(undefined4 *)((long)param_2 + 0xb4));
  }
  lVar2 = param_1[0x17];
  if (lVar2 == 0) {
    lVar2 = FUN_0010a130(*param_1,DAT_00140f20,*(undefined4 *)((long)param_1 + 0xb4));
  }
  iVar1 = (int)lVar4 - (int)lVar2;
  if (iVar1 == 0) {
    piVar3 = __errno_location();
    __s1 = (char *)*param_2;
    __s2 = (char *)*param_1;
    *piVar3 = 0;
    iVar1 = strcoll(__s1,__s2);
    return iVar1;
  }
  return iVar1;
}

