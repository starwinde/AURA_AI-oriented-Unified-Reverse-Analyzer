
undefined8 FUN_0019c0b0(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  uint uVar5;
  bool bVar6;
  uint uVar7;
  ulong uVar8;
  uint uVar9;
  ulong uVar10;
  int iVar11;
  
  uVar8 = param_2 & 0xffffffff;
  uVar9 = (uint)(uVar8 >> 10) & 3;
  uVar7 = (uint)param_2;
  if (uVar9 == 1) {
    if ((uVar7 >> 4 & 1) != 0) {
      return 0;
    }
    bVar6 = (param_2 & 0x20) != 0;
    uVar10 = uVar8 >> 6 & 3;
    if (bVar6) {
      uVar9 = 2;
    }
    iVar11 = 4;
    if (!bVar6) {
      iVar11 = 2;
    }
  }
  else if (uVar9 == 2) {
    if ((param_2 & 0x30) != 0) {
      return 0;
    }
    uVar10 = uVar8 >> 7 & 1;
    iVar11 = 4;
    if ((param_2 & 0x40) == 0) {
      uVar9 = 1;
      iVar11 = 2;
    }
  }
  else {
    if ((uVar8 >> 10 & 3) != 0) {
      return 0;
    }
    if ((uVar7 >> 4 & 1) != 0) {
      return 0;
    }
    uVar9 = 1;
    uVar10 = uVar8 >> 5 & 7;
    iVar11 = 2;
  }
  uVar5 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
  uVar1 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar5 * 2);
  FUN_00190100(param_1,uVar1);
  if (uVar5 + uVar9 < 0x20) {
    uVar2 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar5 + uVar9) * 2);
    FUN_00190100(param_1,uVar2);
    if (uVar5 + iVar11 < 0x20) {
      uVar3 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar5 + iVar11) * 2);
      uVar8 = uVar8 >> 0x10 & 0xf;
      uVar7 = uVar7 & 0xf;
      FUN_00190100(param_1,uVar3);
      if (uVar7 == 0xf) {
        FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
        FUN_00190140(param_1,0);
      }
      else {
        uVar4 = *(undefined2 *)(&DAT_0022f720 + uVar8 * 2);
        FUN_00190100(param_1,uVar4);
        FUN_00190100(param_1,uVar4);
        FUN_00190140(param_1,0);
        if (uVar7 == 0xd) {
          FUN_00190100(param_1,0);
        }
        else {
          FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
        }
      }
      FUN_00190100(param_1,uVar1);
      FUN_00190100(param_1,uVar2);
      FUN_00190100(param_1,uVar3);
      FUN_00190140(param_1,uVar10);
      return 3;
    }
  }
  return 0;
}

