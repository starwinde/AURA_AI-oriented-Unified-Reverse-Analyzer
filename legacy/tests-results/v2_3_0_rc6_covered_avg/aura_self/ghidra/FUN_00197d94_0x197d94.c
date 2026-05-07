
undefined8 FUN_00197d94(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar1 = param_2 >> 5 & 1 | (param_2 & 0xf) << 1;
  if (((int)uVar4 == 0xf || uVar2 == 0xf) || uVar1 == 0x1f) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
    if (uVar1 + 1 == 0x20) {
      return 0;
    }
    uVar5 = 1;
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    uVar5 = 3;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
  }
  param_2 = param_2 >> 0x1c;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 + 1) * 2));
  if (param_2 != 0xf) {
    iVar3 = FUN_0018ffb0(param_1);
    if (iVar3 == 0xc4f) {
      if (param_2 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,param_2);
    }
    else {
      FUN_00190140(param_1,param_2);
      if (param_2 == 0xe) {
        FUN_00190100(param_1,0);
        return uVar5;
      }
    }
    FUN_00190100(param_1,3);
    return uVar5;
  }
  return 0;
}

