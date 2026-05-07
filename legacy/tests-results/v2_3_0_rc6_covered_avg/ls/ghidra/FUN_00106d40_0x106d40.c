
int FUN_00106d40(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  iVar1 = (uint)((long)param_1[9] < (long)param_2[9]) - (uint)((long)param_2[9] < (long)param_1[9]);
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_1,(char *)*param_2);
    return iVar1;
  }
  return iVar1;
}

