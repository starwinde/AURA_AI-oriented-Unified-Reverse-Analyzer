
ulong FUN_00196c70(undefined8 param_1,uint param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar1 = (param_2 >> 9 & 1) << 8 | (int)uVar2 << 9 | param_2 & 0xff;
  uVar3 = (ulong)(param_2 >> 0xc) & 0xf;
  if ((int)uVar2 != 0xf) {
    if ((param_2 >> 0x14 & 1) == 0) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar2 * 2));
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar3 * 2));
      uVar1 = FUN_00195ee0(param_1,uVar1);
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar3 * 2));
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar2 * 2));
      uVar1 = FUN_00195ee0(param_1,uVar1);
    }
    if (3 < uVar1) {
      return 0;
    }
    if ((uVar1 & 1) == 0) {
      return 0;
    }
    return (ulong)*(uint *)(&DAT_0022e300 + (ulong)uVar1 * 4);
  }
  uVar1 = FUN_0018ffb0();
  if (uVar1 < 0xb30) {
    if (0xb2d < uVar1) {
      if ((int)uVar3 == 0xf) {
        FUN_0018ff90(param_1,0xb72);
      }
      else {
        FUN_0018ff90(param_1,0xb32);
      }
      goto LAB_00196db0;
    }
    if (uVar1 < 0xb1b) {
      if (0xb18 < uVar1) {
        FUN_0018ff90(param_1,0xb1d);
        goto LAB_00196db0;
      }
    }
    else if (uVar1 - 0xb27 < 2) {
      FUN_0018ff90(param_1,0xb2b);
      goto LAB_00196db0;
    }
  }
  else if (uVar1 < 0xb37) {
    if (0xb34 < uVar1) {
      FUN_0018ff90(param_1,0xb39);
      goto LAB_00196db0;
    }
  }
  else if (uVar1 - 0xb3c < 2) {
    FUN_0018ff90(param_1,0xb40);
LAB_00196db0:
    uVar2 = FUN_00196b84(param_1,param_2);
    return uVar2;
  }
  return 0;
}

