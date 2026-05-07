
ulong FUN_00109c24(long param_1,long param_2)

{
  int iVar1;
  bool bVar2;
  ulong uVar3;
  uint uVar4;
  
  iVar1 = *(int *)(param_1 + 0x98);
  if (*(int *)(param_2 + 0x98) == 3 || *(int *)(param_2 + 0x98) == 9) {
    uVar4 = 1;
    if (iVar1 == 9 || iVar1 == 3) goto LAB_00109c90;
LAB_00109c9c:
    uVar4 = uVar4 - ((*(uint *)(param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar2 = (*(uint *)(param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar4 = (uint)bVar2;
    if (iVar1 != 9 && iVar1 != 3) goto LAB_00109c9c;
    uVar4 = bVar2 - 1;
  }
  if (uVar4 != 0) {
    return (ulong)uVar4;
  }
LAB_00109c90:
  uVar3 = FUN_00109b80();
  return uVar3;
}

