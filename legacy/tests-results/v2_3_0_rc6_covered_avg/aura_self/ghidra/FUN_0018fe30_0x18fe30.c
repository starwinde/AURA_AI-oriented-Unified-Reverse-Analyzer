
undefined8
FUN_0018fe30(long param_1,int *param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
            undefined8 param_6)

{
  if (param_1 == 0) {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 0x60) != 0) {
    if (*param_2 == 0) {
      *(undefined4 *)(param_1 + 0x50) = 0xb;
      return 0xb;
    }
    if (*(long *)(param_2 + 0x3c) != 0) {
      if (*(code **)(param_1 + 0xa8) != (code *)0x0) {
        (**(code **)(param_1 + 0xa8))(param_2,param_3,param_4,param_5,param_6);
        return 0;
      }
      *(undefined4 *)(param_1 + 0x50) = 2;
      return 2;
    }
  }
  *(undefined4 *)(param_1 + 0x50) = 7;
  return 7;
}

