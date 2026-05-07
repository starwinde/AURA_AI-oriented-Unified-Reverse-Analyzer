
undefined4 FUN_00197ef0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar4 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar3 = (uint)uVar4;
  uVar1 = param_2 >> 0xc & 0xf;
  uVar5 = 3;
  if (uVar3 == 0xf || uVar3 == uVar1) {
    uVar5 = 1;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  iVar2 = FUN_00196350(param_1,(param_2 >> 0x17 & 1) << 0xc | uVar3 << 0xd | param_2 & 0xfff);
  uVar6 = 1;
  if (((iVar2 == 1) || (uVar6 = uVar5, iVar2 == 3)) && (param_2 = param_2 >> 0x1c, param_2 != 0xf))
  {
    iVar2 = FUN_0018ffb0(param_1);
    if (iVar2 == 0xc4f) {
      if (param_2 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,param_2);
    }
    else {
      FUN_00190140(param_1,param_2);
      if (param_2 == 0xe) {
        FUN_00190100(param_1,0);
        return uVar6;
      }
    }
    FUN_00190100(param_1,3);
    return uVar6;
  }
  return 0;
}

