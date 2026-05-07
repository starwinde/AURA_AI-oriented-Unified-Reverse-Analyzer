
void MCInst_Init(undefined4 *param_1)

{
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined1 *)((long)param_1 + 6) = 0;
  param_1[2] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  *(undefined1 *)((long)param_1 + 0x335) = 0;
  *(undefined2 *)((long)param_1 + 0x366) = 0;
  *(undefined1 *)(param_1 + 0xda) = 0;
  param_1[0xe4] = 0;
  *(undefined1 *)(param_1 + 0xee) = 0;
  *(undefined8 *)((long)param_1 + 0x33e) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_1 + 0x336) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_1 + 0x34e) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_1 + 0x346) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_1 + 0x35e) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_1 + 0x356) = 0xffffffffffffffff;
  return;
}

