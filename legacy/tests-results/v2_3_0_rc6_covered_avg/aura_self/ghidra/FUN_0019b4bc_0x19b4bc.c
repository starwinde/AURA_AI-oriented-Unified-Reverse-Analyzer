
undefined8 FUN_0019b4bc(undefined8 param_1,uint param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  long lVar8;
  
  uVar5 = param_2 >> 10 & 3;
  if (uVar5 == 1) {
    uVar7 = param_2 >> 6 & 3;
    if ((param_2 & 0x20) != 0) {
      uVar5 = 2;
    }
    lVar8 = ((ulong)(param_2 >> 4) & 1) << 3;
  }
  else if (uVar5 == 2) {
    uVar6 = (ulong)(param_2 >> 4) & 3;
    iVar4 = (int)uVar6;
    if (iVar4 == 0) {
      lVar8 = 0;
    }
    else {
      if (iVar4 == 3) {
        return 0;
      }
      lVar8 = (long)(4 << uVar6);
    }
    uVar7 = param_2 >> 7 & 1;
    if ((param_2 & 0x40) == 0) {
      uVar5 = 1;
    }
  }
  else {
    if (uVar5 != 0) {
      return 0;
    }
    uVar7 = param_2 >> 5 & 7;
    uVar5 = 1;
    lVar8 = ((ulong)(param_2 >> 4) & 1) << 2;
  }
  uVar1 = param_2 & 0xf;
  uVar2 = *(undefined2 *)(&DAT_0022f720 + ((ulong)(param_2 >> 0x10) & 0xf) * 2);
  if (uVar1 == 0xf) {
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,lVar8);
  }
  else {
    FUN_00190100(param_1,uVar2);
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,lVar8);
    if (uVar1 == 0xd) {
      FUN_00190100(param_1,0);
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
  }
  uVar3 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar1 = uVar3 + uVar5;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar3 * 2));
  if (uVar1 < 0x20) {
    uVar3 = uVar5 + uVar1;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar1 * 2));
    if (uVar3 < 0x20) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar3 * 2));
      if (uVar5 + uVar3 < 0x20) {
        FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar5 + uVar3) * 2));
        FUN_00190140(param_1,uVar7);
        return 3;
      }
    }
  }
  return 0;
}

