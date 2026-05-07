
ulong FUN_00196e7c(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar4 >> 0x10) & 0xf;
  uVar1 = (uint)(uVar4 >> 0xc) & 0xf;
  if (uVar3 == 0xf) {
    uVar3 = FUN_0018ffb0();
    if (uVar3 == 0xb38) {
      FUN_0018ff90(param_1,0xb39);
    }
    else if (uVar3 < 0xb39) {
      if (uVar3 == 0xb2a) {
        FUN_0018ff90(param_1,0xb2b);
      }
      else if (uVar3 == 0xb31) {
        FUN_0018ff90(param_1,0xb32);
      }
      else {
        if (uVar3 != 0xb1c) {
          return 0;
        }
        FUN_0018ff90(param_1,0xb1d);
      }
    }
    else if (uVar3 == 0xb6d) {
      FUN_0018ff90(param_1,0xb6e);
    }
    else if (uVar3 == 0xb71) {
      FUN_0018ff90(param_1,0xb72);
    }
    else {
      if (uVar3 != 0xb3f) {
        return 0;
      }
      FUN_0018ff90(param_1,0xb40);
    }
    uVar4 = FUN_00196b84(param_1,uVar4);
    return uVar4;
  }
  if (uVar1 == 0xf) {
    iVar2 = FUN_0018ffb0();
    if (iVar2 == 0xb31) {
      FUN_0018ff90(param_1,0xb71);
    }
    else {
      if (iVar2 == 0xb38) {
        return 0;
      }
      if ((iVar2 == 0xb2a) && ((uVar4 >> 9 & 1) == 0)) {
        FUN_0018ff90(param_1,0xb6a);
      }
    }
  }
  iVar2 = FUN_0018ffb0(param_1);
  if ((7 < iVar2 - 0xb6aU) || ((0x89UL >> ((ulong)(iVar2 - 0xb6aU) & 0x3f) & 1) == 0)) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  }
  uVar3 = FUN_00195ee0(param_1,uVar3 << 9 | ((uint)(uVar4 >> 9) & 1) << 8 | (uint)param_2 & 0xff);
  if ((uVar3 < 4) && ((uVar3 & 1) != 0)) {
    return (ulong)*(uint *)(&DAT_0022e300 + (ulong)uVar3 * 4);
  }
  return 0;
}

