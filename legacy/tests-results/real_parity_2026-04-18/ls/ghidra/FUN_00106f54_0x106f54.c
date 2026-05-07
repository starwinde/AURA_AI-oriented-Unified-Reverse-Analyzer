
int FUN_00106f54(undefined8 *param_1,undefined8 *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x13);
  if (*(int *)(param_2 + 0x13) == 3 || *(int *)(param_2 + 0x13) == 9) {
    uVar2 = 1;
    if (iVar3 == 9 || iVar3 == 3) goto LAB_00106fc0;
LAB_00106fd4:
    iVar3 = uVar2 - ((*(uint *)((long)param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar1 = (*(uint *)((long)param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar2 = (uint)bVar1;
    if (iVar3 != 9 && iVar3 != 3) goto LAB_00106fd4;
    iVar3 = bVar1 - 1;
  }
  if (iVar3 != 0) {
    return iVar3;
  }
LAB_00106fc0:
  iVar3 = strcmp((char *)*param_1,(char *)*param_2);
  return iVar3;
}

