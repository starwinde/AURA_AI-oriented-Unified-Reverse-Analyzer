
ulong FUN_00108c30(long param_1,long param_2)

{
  int iVar1;
  bool bVar2;
  ulong uVar3;
  uint uVar4;
  
  iVar1 = *(int *)(param_1 + 0x98);
  if (*(int *)(param_2 + 0x98) == 3 || *(int *)(param_2 + 0x98) == 9) {
    uVar4 = 1;
    if (iVar1 == 9 || iVar1 == 3) goto LAB_00108c9c;
LAB_00108cb0:
    uVar4 = uVar4 - ((*(uint *)(param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar2 = (*(uint *)(param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar4 = (uint)bVar2;
    if (iVar1 != 9 && iVar1 != 3) goto LAB_00108cb0;
    uVar4 = bVar2 - 1;
  }
  if (uVar4 != 0) {
    return (ulong)uVar4;
  }
LAB_00108c9c:
  uVar3 = FUN_00108b40(param_1,param_2,PTR_strcmp_0013ffd8);
  return uVar3;
}

