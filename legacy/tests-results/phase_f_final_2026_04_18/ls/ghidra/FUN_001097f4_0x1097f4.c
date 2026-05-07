
int FUN_001097f4(undefined8 *param_1,undefined8 *param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  char *__s1;
  char *__s2;
  
  iVar2 = *(int *)(param_1 + 0x13);
  if (*(int *)(param_2 + 0x13) == 3 || *(int *)(param_2 + 0x13) == 9) {
    uVar4 = 1;
    if (iVar2 == 9 || iVar2 == 3) goto LAB_00109850;
LAB_001098a8:
    iVar2 = uVar4 - ((*(uint *)((long)param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar1 = (*(uint *)((long)param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar4 = (uint)bVar1;
    if (iVar2 != 9 && iVar2 != 3) goto LAB_001098a8;
    iVar2 = bVar1 - 1;
  }
  if (iVar2 != 0) {
    return iVar2;
  }
LAB_00109850:
  iVar2 = (uint)((long)param_1[9] < (long)param_2[9]) - (uint)((long)param_2[9] < (long)param_1[9]);
  if (iVar2 != 0) {
    return iVar2;
  }
  __s2 = (char *)*param_2;
  __s1 = (char *)*param_1;
  piVar3 = __errno_location();
  *piVar3 = 0;
  iVar2 = strcoll(__s1,__s2);
  return iVar2;
}

