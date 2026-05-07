
ulong FUN_001977b0(undefined8 param_1,ulong param_2)

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
    if (uVar3 == 0xb3a) {
      FUN_0018ff90(param_1,0xb39);
    }
    else if (uVar3 < 0xb3b) {
      if (uVar3 == 0xb2c) {
        FUN_0018ff90(param_1,0xb2b);
      }
      else if (uVar3 == 0xb33) {
        FUN_0018ff90(param_1,0xb32);
      }
      else {
        if (uVar3 != 0xb1e) {
          return 0;
        }
        FUN_0018ff90(param_1,0xb1d);
      }
    }
    else if (uVar3 == 0xb6f) {
      FUN_0018ff90(param_1,0xb6e);
    }
    else if (uVar3 == 0xb73) {
      FUN_0018ff90(param_1,0xb72);
    }
    else {
      if (uVar3 != 0xb41) {
        return 0;
      }
      FUN_0018ff90(param_1,0xb40);
    }
    uVar4 = FUN_00196b84(param_1,uVar4);
    return uVar4;
  }
  if (uVar1 == 0xf) {
    iVar2 = FUN_0018ffb0();
    if (iVar2 == 0xb33) {
      FUN_0018ff90(param_1,0xb73);
    }
    else {
      if (iVar2 == 0xb3a) {
        return 0;
      }
      if (iVar2 == 0xb2c) {
        FUN_0018ff90(param_1,0xb6b);
      }
    }
  }
  iVar2 = FUN_0018ffb0(param_1);
  if ((8 < iVar2 - 0xb6bU) || ((0x111UL >> ((ulong)(iVar2 - 0xb6bU) & 0x3f) & 1) == 0)) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  }
  uVar3 = FUN_001976d0(param_1,(uint)(uVar4 >> 4) & 3 | ((uint)param_2 & 0xf) << 2 | uVar3 << 6);
  if ((uVar3 < 4) && ((uVar3 & 1) != 0)) {
    return (ulong)*(uint *)(&DAT_0022e300 + (ulong)uVar3 * 4);
  }
  return 0;
}

