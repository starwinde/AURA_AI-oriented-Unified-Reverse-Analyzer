
uint FUN_00198780(undefined8 param_1,uint param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  long lVar4;
  
  uVar3 = param_2 >> 10 & 3;
  if (uVar3 == 1) {
    if ((param_2 >> 5 & 1) != 0) {
      return 0;
    }
    lVar4 = ((ulong)(param_2 >> 4) & 1) << 1;
    uVar3 = param_2 >> 6 & 3;
  }
  else if (uVar3 == 2) {
    if ((param_2 >> 6 & 1) != 0) {
      return 0;
    }
    uVar3 = param_2 >> 7 & 1;
    if ((param_2 >> 4 & 3) == 0) {
      lVar4 = 0;
    }
    else {
      if ((param_2 >> 4 & 3) != 3) {
        return param_2 & 0x40;
      }
      lVar4 = 4;
    }
  }
  else {
    if (uVar3 != 0) {
      return 0;
    }
    if ((param_2 >> 4 & 1) != 0) {
      return 0;
    }
    uVar3 = param_2 >> 5 & 7;
    lVar4 = 0;
  }
  uVar1 = param_2 & 0xf;
  uVar2 = *(undefined2 *)(&DAT_0022f720 + ((ulong)(param_2 >> 0x10) & 0xf) * 2);
  if (uVar1 == 0xf) {
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,lVar4);
  }
  else {
    FUN_00190100(param_1,uVar2);
    FUN_00190100(param_1,uVar2);
    FUN_00190140(param_1,lVar4);
    if (uVar1 == 0xd) {
      FUN_00190100(param_1,0);
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
  }
  FUN_00190100(param_1,*(undefined2 *)
                        (&DAT_0022f4e0 +
                        (ulong)(param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) * 2));
  FUN_00190140(param_1,uVar3);
  return 3;
}

