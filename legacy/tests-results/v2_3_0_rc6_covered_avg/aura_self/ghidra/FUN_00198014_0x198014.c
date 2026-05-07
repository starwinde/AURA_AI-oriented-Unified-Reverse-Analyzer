
undefined4 FUN_00198014(undefined8 param_1,uint param_2)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  ulong uVar5;
  
  uVar2 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar5 = (ulong)(param_2 >> 0x10) & 0xf;
  iVar1 = (int)uVar5;
  uVar3 = 1;
  if (iVar1 != 0xf && iVar1 != (int)uVar2) {
    uVar3 = 3;
  }
  if ((param_2 & 0xf) == 0xf) {
    uVar3 = 1;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar2 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
  iVar1 = FUN_00196350(param_1,(param_2 >> 0x17 & 1) << 0xc | iVar1 << 0xd | param_2 & 0xfff);
  uVar4 = 1;
  if (((iVar1 == 1) || (uVar4 = uVar3, iVar1 == 3)) && (param_2 = param_2 >> 0x1c, param_2 != 0xf))
  {
    iVar1 = FUN_0018ffb0(param_1);
    if (iVar1 == 0xc4f) {
      if (param_2 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,param_2);
    }
    else {
      FUN_00190140(param_1,param_2);
      if (param_2 == 0xe) {
        FUN_00190100(param_1,0);
        return uVar4;
      }
    }
    FUN_00190100(param_1,3);
    return uVar4;
  }
  return 0;
}

