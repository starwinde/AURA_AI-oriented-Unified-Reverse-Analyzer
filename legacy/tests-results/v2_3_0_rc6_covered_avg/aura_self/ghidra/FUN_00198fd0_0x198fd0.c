
undefined8 FUN_00198fd0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar1 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar4 = (ulong)uVar1;
  iVar2 = FUN_0018ffb0();
  if (iVar2 - 0x5b2U < 0x12) {
    uVar3 = 1L << ((ulong)(iVar2 - 0x5b2U) & 0x3f);
    if ((uVar3 & 0x38e38) != 0) {
      if (0x1d < uVar1) {
        return 0;
      }
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f330 + uVar4 * 2));
      goto LAB_0019905c;
    }
    if ((uVar3 & 0x71c7) != 0) {
      if (uVar1 == 0x1f) {
        return 0;
      }
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f230 + uVar4 * 2));
      goto LAB_0019905c;
    }
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + uVar4 * 2));
LAB_0019905c:
  uVar4 = (ulong)(param_2 >> 0x10) & 0xf;
  iVar2 = ((param_2 >> 4 & 1) << ((ulong)(param_2 >> 6) & 3)) << 1;
  if ((param_2 & 0xf) == 0xf) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
    FUN_00190140(param_1,iVar2);
  }
  else {
    FUN_00190140(param_1,0);
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
    FUN_00190140(param_1,iVar2);
    if ((param_2 & 0xd) != 0xd) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 & 0xf) * 2));
    }
  }
  return 3;
}

