
void _obstack_begin_1(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                     undefined8 param_5,undefined8 param_6)

{
  *(undefined8 *)(param_1 + 0x38) = param_4;
  *(undefined8 *)(param_1 + 0x40) = param_5;
  *(undefined8 *)(param_1 + 0x48) = param_6;
  *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) | 1;
  FUN_00107250();
  return;
}

