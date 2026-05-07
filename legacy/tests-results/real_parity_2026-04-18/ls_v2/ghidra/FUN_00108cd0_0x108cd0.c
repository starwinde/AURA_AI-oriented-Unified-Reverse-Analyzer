
ulong FUN_00108cd0(long param_1,long param_2)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  ulong uVar4;
  
  iVar1 = *(int *)(param_1 + 0x98);
  if (*(int *)(param_2 + 0x98) == 3 || *(int *)(param_2 + 0x98) == 9) {
    uVar3 = 1;
    if (iVar1 == 9 || iVar1 == 3) goto LAB_00108d40;
LAB_00108d5c:
    uVar3 = uVar3 - ((*(uint *)(param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar2 = (*(uint *)(param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar3 = (uint)bVar2;
    if (iVar1 != 9 && iVar1 != 3) goto LAB_00108d5c;
    uVar3 = bVar2 - 1;
  }
  if (uVar3 != 0) {
    return (ulong)uVar3;
  }
LAB_00108d40:
  uVar4 = FUN_00108b40(param_2,param_1,PTR_strcmp_0013ffd8);
  return uVar4;
}

