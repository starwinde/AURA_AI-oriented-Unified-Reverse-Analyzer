
undefined8 FUN_0019c290(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  ulong uVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  
  uVar10 = param_2 & 0xffffffff;
  uVar11 = (uint)(uVar10 >> 10) & 3;
  if (uVar11 == 1) {
    bVar7 = (param_2 & 0x20) == 0;
    iVar9 = 6;
    if (bVar7) {
      iVar9 = 3;
    }
    uVar12 = (ulong)(((uint)(uVar10 >> 4) & 1) << 3);
    uVar13 = uVar10 >> 6 & 3;
    iVar8 = 2;
    if (!bVar7) {
      uVar11 = 2;
      iVar8 = 4;
    }
  }
  else if (uVar11 == 2) {
    uVar12 = uVar10 >> 4 & 3;
    if ((int)uVar12 != 0) {
      if ((int)uVar12 == 3) {
        return 0;
      }
      uVar12 = (ulong)(uint)(4 << uVar12);
    }
    bVar7 = (param_2 & 0x40) == 0;
    iVar8 = 4;
    if (bVar7) {
      iVar8 = 2;
      uVar11 = 1;
    }
    uVar13 = uVar10 >> 7 & 1;
    iVar9 = 6;
    if (bVar7) {
      iVar9 = 3;
    }
  }
  else {
    if ((uVar10 >> 10 & 3) != 0) {
      return 0;
    }
    uVar13 = uVar10 >> 5 & 7;
    iVar9 = 3;
    uVar12 = (ulong)(((uint)(uVar10 >> 4) & 1) << 2);
    uVar11 = 1;
    iVar8 = 2;
  }
  uVar6 = (uint)(uVar10 >> 0xc) & 0xf | ((uint)param_2 & 0x400000) >> 0x12;
  uVar1 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar6 * 2);
  FUN_00190100(param_1,uVar1);
  if (uVar6 + uVar11 < 0x20) {
    uVar2 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar6 + uVar11) * 2);
    FUN_00190100(param_1,uVar2);
    if (uVar6 + iVar8 < 0x20) {
      uVar3 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar6 + iVar8) * 2);
      FUN_00190100(param_1,uVar3);
      if (uVar6 + iVar9 < 0x20) {
        uVar4 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar6 + iVar9) * 2);
        uVar10 = uVar10 >> 0x10 & 0xf;
        uVar11 = (uint)param_2 & 0xf;
        FUN_00190100(param_1,uVar4);
        if (uVar11 == 0xf) {
          FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar10 * 2));
          FUN_00190140(param_1,uVar12);
        }
        else {
          uVar5 = *(undefined2 *)(&DAT_0022f720 + uVar10 * 2);
          FUN_00190100(param_1,uVar5);
          FUN_00190100(param_1,uVar5);
          FUN_00190140(param_1,uVar12);
          if (uVar11 == 0xd) {
            FUN_00190100(param_1,0);
          }
          else {
            FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar11 * 2));
          }
        }
        FUN_00190100(param_1,uVar1);
        FUN_00190100(param_1,uVar2);
        FUN_00190100(param_1,uVar3);
        FUN_00190100(param_1,uVar4);
        FUN_00190140(param_1,uVar13);
        return 3;
      }
    }
  }
  return 0;
}

