
ulong FUN_001983c0(long param_1,ulong param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = param_2 & 0xffffffff;
  uVar2 = (uint)(uVar4 >> 0x10) & 0xf;
  if (uVar2 == 0xf) {
    uVar2 = FUN_0018ffb0();
    if (uVar2 == 0xb2d) {
      FUN_0018ff90(param_1,0xb32);
    }
    else if (uVar2 < 0xb2e) {
      if (uVar2 == 0xb18) {
        FUN_0018ff90(param_1,0xb1d);
      }
      else {
        if (uVar2 != 0xb26) {
          return 0;
        }
        FUN_0018ff90(param_1,0xb2b);
      }
    }
    else if (uVar2 == 0xb34) {
      FUN_0018ff90(param_1,0xb39);
    }
    else {
      if (uVar2 != 0xb3b) {
        return 0;
      }
      FUN_0018ff90(param_1,0xb40);
    }
    uVar4 = FUN_00196b84(param_1,uVar4);
    return uVar4;
  }
  uVar4 = uVar4 >> 0xc & 0xf;
  iVar1 = (int)uVar4;
  if (iVar1 == 0xd) {
    uVar3 = 3;
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 3;
    if (iVar1 == 0xf) {
      uVar3 = 1;
    }
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar4 * 2));
  uVar3 = *(uint *)(&DAT_0022e300 + (ulong)uVar3 * 4);
  uVar4 = FUN_00195ee0(param_1,(uint)param_2 & 0xff | uVar2 << 9);
  if ((int)uVar4 != 1) {
    if ((int)uVar4 != 3) {
      return 0;
    }
    return (ulong)uVar3;
  }
  return uVar4;
}

