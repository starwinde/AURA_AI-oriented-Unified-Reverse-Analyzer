
long FUN_00190124(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x308) = param_2;
  *(undefined4 *)(param_1 + 0x300) = 2;
  *(undefined1 *)(param_1 + 0x304) = 2;
  return param_1 + 0x300;
}

