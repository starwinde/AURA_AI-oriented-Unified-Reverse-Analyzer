
undefined4 FUN_00197440(long param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar1 = (uint)param_2 & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar3 = 3;
  if ((int)uVar2 == 0xc) {
    uVar3 = 1;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar2 * 2));
  if (uVar1 == 0xd) {
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) == 0) {
      FUN_00190100(param_1,0xc);
      return 1;
    }
  }
  else if (uVar1 == 0xf) {
    FUN_00190100(param_1,0xb);
    return 1;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  return uVar3;
}

