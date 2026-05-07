
ulong FUN_00109030(long param_1,long param_2)

{
  int iVar1;
  bool bVar2;
  ulong uVar3;
  uint uVar4;
  
  iVar1 = *(int *)(param_1 + 0x98);
  if (*(int *)(param_2 + 0x98) == 3 || *(int *)(param_2 + 0x98) == 9) {
    uVar4 = 1;
    if (iVar1 == 9 || iVar1 == 3) goto LAB_0010909c;
LAB_001090a8:
    uVar4 = uVar4 - ((*(uint *)(param_1 + 0x9c) & 0xf000) == 0x4000);
  }
  else {
    bVar2 = (*(uint *)(param_2 + 0x9c) & 0xf000) == 0x4000;
    uVar4 = (uint)bVar2;
    if (iVar1 != 9 && iVar1 != 3) goto LAB_001090a8;
    uVar4 = bVar2 - 1;
  }
  if (uVar4 != 0) {
    return (ulong)uVar4;
  }
LAB_0010909c:
  uVar3 = FUN_00108fb4();
  return uVar3;
}

