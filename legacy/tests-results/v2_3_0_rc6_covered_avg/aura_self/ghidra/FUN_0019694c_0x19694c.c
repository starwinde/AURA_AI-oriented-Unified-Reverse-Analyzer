
undefined8 FUN_0019694c(undefined8 param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  if ((param_2 & 0xf) == 0xf) {
    FUN_00190100(param_1,0xb);
    uVar2 = 1;
  }
  else {
    uVar2 = 3;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 & 0xf) * 2));
  }
  if (param_2 >> 8 == 0xf) {
    FUN_00190100(param_1,0xb);
    uVar2 = 1;
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 >> 8) * 2));
  }
  uVar1 = (param_2 >> 5 & 3) - 1;
  if (2 < uVar1) {
    FUN_00190140(param_1,2);
    return uVar2;
  }
  FUN_00190140(param_1,*(undefined4 *)(&DAT_0022bbf0 + (ulong)uVar1 * 4));
  return uVar2;
}

