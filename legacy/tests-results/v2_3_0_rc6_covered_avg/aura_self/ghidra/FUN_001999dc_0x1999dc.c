
undefined8 FUN_001999dc(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  
  uVar5 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar5 >> 10) & 3;
  uVar4 = (uint)param_2;
  if (uVar3 == 1) {
    uVar7 = uVar5 >> 6 & 3;
    if ((param_2 & 0x20) != 0) {
      uVar3 = 2;
    }
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 2;
  }
  else if (uVar3 == 2) {
    if ((uVar4 >> 5 & 1) != 0) {
      return 0;
    }
    if ((param_2 & 0x40) == 0) {
      uVar3 = 1;
    }
    uVar7 = uVar5 >> 7 & 1;
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 3;
  }
  else {
    if ((uVar5 >> 10 & 3) != 0) {
      return 0;
    }
    uVar7 = uVar5 >> 5 & 7;
    uVar3 = 1;
    iVar6 = ((uint)(uVar5 >> 4) & 1) << 1;
  }
  uVar1 = uVar4 & 0xf;
  uVar2 = *(undefined2 *)(&DAT_0022f720 + (uVar5 >> 0x10 & 0xf) * 2);
  if (uVar1 == 0xf) {
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,iVar6);
  }
  else {
    FUN_00190100(param_1,uVar2);
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,iVar6);
    if (uVar1 == 0xd) {
      FUN_00190100(param_1,0);
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
  }
  uVar4 = (uint)(uVar5 >> 0xc) & 0xf | (uVar4 & 0x400000) >> 0x12;
  uVar3 = uVar4 + uVar3;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar4 * 2));
  if (0x1f < uVar3) {
    return 0;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar3 * 2));
  FUN_00190140(param_1,uVar7);
  return 3;
}

