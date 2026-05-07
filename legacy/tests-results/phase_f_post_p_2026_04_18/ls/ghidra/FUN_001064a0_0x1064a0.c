
int FUN_001064a0(undefined8 *param_1,undefined8 *param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x13);
  if (*(int *)(param_2 + 0x13) == 3 || *(int *)(param_2 + 0x13) == 9) {
    uVar3 = 1;
    if (iVar2 == 3 || iVar2 == 9) goto LAB_00106510;
LAB_00106558:
    iVar2 = uVar3 - ((*(uint *)((long)param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar1 = (*(uint *)((long)param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar3 = (uint)bVar1;
    if (iVar2 != 3 && iVar2 != 9) goto LAB_00106558;
    iVar2 = bVar1 - 1;
  }
  if (iVar2 != 0) {
    return iVar2;
  }
LAB_00106510:
  iVar2 = ((uint)((long)param_2[0x11] < (long)param_1[0x11]) -
          (uint)((long)param_1[0x11] < (long)param_2[0x11])) +
          ((uint)((long)param_2[0x10] < (long)param_1[0x10]) -
          (uint)((long)param_1[0x10] < (long)param_2[0x10])) * 2;
  if (iVar2 != 0) {
    return iVar2;
  }
  iVar2 = strcmp((char *)*param_2,(char *)*param_1);
  return iVar2;
}

