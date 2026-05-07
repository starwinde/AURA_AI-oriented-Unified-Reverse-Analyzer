
undefined8 FUN_00199f54(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = param_2 >> 4 & 1;
  if ((uVar3 & (param_2 >> 6 & 3) == 0) != 0) {
    return 0;
  }
  uVar2 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  iVar4 = FUN_0018ffb0();
  if (iVar4 - 0x551U < 9) {
    if (uVar2 == 0x1f) {
      return 0;
    }
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f230 + (ulong)uVar2 * 2));
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar2 * 2));
  }
  iVar4 = uVar3 << (ulong)(param_2 >> 6 & 3);
  uVar1 = *(undefined2 *)(&DAT_0022f720 + ((ulong)(param_2 >> 0x10) & 0xf) * 2);
  if ((param_2 & 0xf) == 0xf) {
    FUN_00190100(param_1,uVar1);
    FUN_00190140(param_1,iVar4);
  }
  else {
    FUN_00190100(param_1,uVar1);
    FUN_00190100(param_1,uVar1);
    FUN_00190140(param_1,iVar4);
    if ((param_2 & 0xd) != 0xd) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 & 0xf) * 2));
    }
  }
  return 3;
}

