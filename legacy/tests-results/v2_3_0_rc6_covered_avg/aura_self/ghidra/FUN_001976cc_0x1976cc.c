
undefined4 FUN_001976cc(long param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  undefined4 uVar5;
  
  uVar4 = param_2 >> 6 & 0x3ffffff;
  uVar3 = param_2 >> 2 & 0xf;
  iVar1 = FUN_0018ffb0();
  if (((0x13 < iVar1 - 0xbebU) || ((0x82001UL >> ((ulong)(iVar1 - 0xbebU) & 0x3f) & 1) == 0)) ||
     (uVar5 = 0, (int)uVar4 != 0xf)) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
    iVar1 = (int)uVar3;
    if (iVar1 == 0xd) {
      uVar2 = 3;
      if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 3;
      if (iVar1 == 0xf) {
        uVar2 = 1;
      }
    }
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar3 * 2));
    uVar5 = *(undefined4 *)(&DAT_0022e300 + (ulong)uVar2 * 4);
    FUN_00190140(param_1,(uint)param_2 & 3);
  }
  return uVar5;
}

