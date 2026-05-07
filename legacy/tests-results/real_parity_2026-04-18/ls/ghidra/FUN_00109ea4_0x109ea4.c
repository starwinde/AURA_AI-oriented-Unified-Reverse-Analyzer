
ulong FUN_00109ea4(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  ulong uVar4;
  char *__s1;
  char *__s2;
  
  iVar1 = *(int *)(param_1 + 0x13);
  if (*(int *)(param_2 + 0x13) == 3 || *(int *)(param_2 + 0x13) == 9) {
    uVar3 = 1;
    if (iVar1 == 3 || iVar1 == 9) goto code_r0x00109f04;
LAB_00109f40:
    uVar3 = uVar3 - ((*(uint *)((long)param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar2 = (*(uint *)((long)param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar3 = (uint)bVar2;
    if (iVar1 != 3 && iVar1 != 9) goto LAB_00109f40;
    uVar3 = bVar2 - 1;
  }
  if (uVar3 != 0) {
    return (ulong)uVar3;
  }
code_r0x00109f04:
  __s2 = (char *)*param_2;
  __s1 = (char *)*param_1;
  uVar4 = FUN_001110a0(__s1,__s2);
  if ((int)uVar4 == 0) {
    uVar3 = strcmp(__s1,__s2);
    return (ulong)uVar3;
  }
  return uVar4;
}

