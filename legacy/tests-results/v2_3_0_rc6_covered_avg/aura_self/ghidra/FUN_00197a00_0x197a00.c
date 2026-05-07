
uint FUN_00197a00(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  param_2 = param_2 & 0xffffffff;
  uVar2 = (uint)(param_2 >> 0x10) & 0xf;
  uVar5 = 3;
  if (uVar2 == 0xf) {
    uVar5 = 1;
  }
  if (((uint)(param_2 >> 0xc) & 0xf) < 0xe) {
    uVar1 = (uint)(param_2 >> 0xc) & 1;
    if ((param_2 >> 0xc & 1) == 0) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f478 + (param_2 >> 0xc & 0xe)));
      uVar1 = uVar5;
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f478 + (param_2 >> 0xc & 0xe)));
    }
    param_2 = param_2 >> 0x1c;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    iVar4 = (int)param_2;
    if (iVar4 != 0xf) {
      iVar3 = FUN_0018ffb0(param_1);
      if (iVar3 == 0xc4f) {
        if (iVar4 == 0xe) {
          return 0;
        }
        FUN_00190140(param_1,param_2);
      }
      else {
        FUN_00190140(param_1,param_2);
        if (iVar4 == 0xe) {
          FUN_00190100(param_1,0);
          return uVar1;
        }
      }
      FUN_00190100(param_1,3);
      return uVar1;
    }
  }
  return 0;
}

