
int FUN_00106ce4(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  iVar1 = (uint)((long)param_2[9] < (long)param_1[9]) - (uint)((long)param_1[9] < (long)param_2[9]);
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_2,(char *)*param_1);
    return iVar1;
  }
  return iVar1;
}

