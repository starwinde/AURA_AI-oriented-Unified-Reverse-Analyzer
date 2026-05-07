
undefined8 FUN_00196350(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (param_2 >> 5 & 3) - 1;
  uVar1 = param_2 >> 7 & 0x1f;
  uVar3 = 0x4000;
  if ((uVar2 < 3) &&
     (uVar3 = *(int *)(&DAT_0022bbf0 + (ulong)uVar2 * 4) << 0xd,
     uVar1 == 0 && *(int *)(&DAT_0022bbf0 + (ulong)uVar2 * 4) == 4)) {
    uVar3 = 0xa000;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 >> 0xd) * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 & 0xf) * 2));
  uVar1 = uVar1 | uVar3;
  uVar3 = uVar1 | 0x1000;
  if ((param_2 & 0x1000) != 0) {
    uVar3 = uVar1;
  }
  FUN_00190140(param_1,uVar3);
  return 3;
}

