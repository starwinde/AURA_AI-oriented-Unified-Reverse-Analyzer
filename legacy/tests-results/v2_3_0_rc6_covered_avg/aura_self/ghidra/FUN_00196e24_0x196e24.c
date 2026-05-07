
undefined8 FUN_00196e24(long param_1,int param_2)

{
  if (param_2 - 10U < 2) {
    return 0;
  }
  if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) {
    if (1 < param_2 - 0xeU) {
      return 0;
    }
  }
  FUN_00190140(param_1,param_2);
  return 3;
}

