
int FUN_00109a10(undefined8 *param_1,undefined8 *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  char *__s1;
  char *__s2;
  
  iVar3 = *(int *)(param_1 + 0x13);
  if (*(int *)(param_2 + 0x13) == 3 || *(int *)(param_2 + 0x13) == 9) {
    uVar2 = 1;
    if (iVar3 == 3 || iVar3 == 9) goto code_r0x00109a70;
LAB_00109aa8:
    iVar3 = uVar2 - ((*(uint *)((long)param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar1 = (*(uint *)((long)param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar2 = (uint)bVar1;
    if (iVar3 != 3 && iVar3 != 9) goto LAB_00109aa8;
    iVar3 = bVar1 - 1;
  }
  if (iVar3 != 0) {
    return iVar3;
  }
code_r0x00109a70:
  __s1 = (char *)*param_1;
  __s2 = (char *)*param_2;
  piVar4 = __errno_location();
  *piVar4 = 0;
  iVar3 = strcoll(__s1,__s2);
  return iVar3;
}

