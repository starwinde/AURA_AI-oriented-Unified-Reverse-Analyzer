
void FUN_00170860(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    free((void *)param_1[2]);
    *param_1 = 0;
    *(undefined4 *)(param_1 + 1) = 0;
    param_1[2] = 0;
    return;
  }
  return;
}

