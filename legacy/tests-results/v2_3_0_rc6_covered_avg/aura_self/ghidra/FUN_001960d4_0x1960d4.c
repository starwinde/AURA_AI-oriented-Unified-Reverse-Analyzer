
undefined8 FUN_001960d4(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar3 = param_2 >> 9 & 3;
  uVar4 = param_2 >> 5 & 7;
  iVar2 = (int)uVar3;
  if (iVar2 == 1) {
    return 0;
  }
  uVar1 = (uint)param_2 & 0x1f;
  if ((iVar2 != 0) == 0 || (param_2 >> 8 & 1) == 0) {
    if (((uint)(iVar2 != 0) & ((uint)(param_2 >> 8) & 0xffffff ^ 0xffffffff)) == 0) {
      if (iVar2 == 0 && (param_2 >> 8 & 1) != 0) {
        FUN_0018ff90(param_1,0xae5);
        FUN_00190140(param_1,uVar1);
        if ((int)uVar4 != 0) {
          return 1;
        }
      }
      else {
        uVar1 = (uint)param_2 & 0xff;
        if (4 < uVar1) {
          return 0;
        }
        FUN_0018ff90(param_1,0xaf7);
        FUN_00190140(param_1,uVar1);
      }
    }
    else {
      FUN_0018ff90(param_1,0xae6);
      FUN_00190140(param_1,uVar3);
      FUN_00190140(param_1,uVar4);
      if ((param_2 & 0x1f) != 0) {
        return 1;
      }
    }
  }
  else {
    FUN_0018ff90(param_1,0xae7);
    FUN_00190140(param_1,uVar3);
    FUN_00190140(param_1,uVar4);
    FUN_00190140(param_1,uVar1);
  }
  return 3;
}

