
ulong FUN_00199b60(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  
  uVar5 = param_2 >> 10 & 3;
  iVar4 = (int)uVar5;
  uVar6 = (uint)param_2;
  if (iVar4 == 1) {
    if ((uVar6 >> 5 & 1) == 0) {
      uVar5 = param_2 >> 6 & 3;
      lVar7 = (param_2 >> 4 & 1) << 1;
      goto LAB_00199bf8;
    }
  }
  else if (iVar4 == 2) {
    if ((uVar6 >> 6 & 1) == 0) {
      uVar5 = param_2 >> 7 & 1;
      if ((param_2 >> 4 & 3) == 0) {
        lVar7 = 0;
      }
      else {
        if (((uint)(param_2 >> 4) & 3) != 3) {
          return (ulong)(uVar6 & 0x40);
        }
        lVar7 = 4;
      }
      goto LAB_00199bf8;
    }
  }
  else if (iVar4 == 0) {
    if ((uVar6 >> 4 & 1) != 0) {
      return uVar5;
    }
    uVar5 = param_2 >> 5 & 7;
    lVar7 = 0;
LAB_00199bf8:
    uVar1 = uVar6 & 0xf;
    uVar8 = param_2 >> 0x10 & 0xf;
    uVar2 = *(undefined2 *)
             (&DAT_0022f4e0 + (ulong)((uint)(param_2 >> 0xc) & 0xf | (uVar6 & 0x400000) >> 0x12) * 2
             );
    FUN_00190100(param_1,uVar2);
    if (uVar1 == 0xf) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
      FUN_00190140(param_1,lVar7);
    }
    else {
      uVar3 = *(undefined2 *)(&DAT_0022f720 + uVar8 * 2);
      FUN_00190100(param_1,uVar3);
      FUN_00190100(param_1,uVar3);
      FUN_00190140(param_1,lVar7);
      if (uVar1 == 0xd) {
        FUN_00190100(param_1,0);
      }
      else {
        FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
      }
    }
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,uVar5);
    return 3;
  }
  return 0;
}

