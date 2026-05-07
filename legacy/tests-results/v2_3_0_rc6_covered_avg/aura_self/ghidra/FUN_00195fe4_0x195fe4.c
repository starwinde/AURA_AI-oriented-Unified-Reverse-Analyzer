
undefined8 FUN_00195fe4(undefined8 param_1,uint param_2)

{
  if (param_2 >> 8 != 0xf) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 >> 8) * 2));
    FUN_00190140(param_1,param_2 & 0xff);
    return 3;
  }
  FUN_00190100(param_1,0xb);
  FUN_00190140(param_1,param_2 & 0xff);
  return 1;
}

