
void cJSON_CreateNumber(double param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(*(code *)global_hooks)(0x40);
  if (puVar1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *(undefined4 *)(puVar1 + 3) = 8;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    puVar1[6] = param_1;
    if (2147483647.0 <= param_1) {
      *(undefined4 *)(puVar1 + 5) = 0x7fffffff;
      return;
    }
    if (param_1 <= -2147483648.0) {
      *(undefined4 *)(puVar1 + 5) = 0x80000000;
      return;
    }
    *(int *)(puVar1 + 5) = (int)param_1;
  }
  return;
}

