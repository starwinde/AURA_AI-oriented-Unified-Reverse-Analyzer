
undefined8 id2name(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  
  if (0 < param_2) {
    piVar1 = param_1 + (long)param_2 * 4;
    do {
      if (*param_1 == param_3) {
        return *(undefined8 *)(param_1 + 2);
      }
      param_1 = param_1 + 4;
    } while (param_1 != piVar1);
  }
  return 0;
}

