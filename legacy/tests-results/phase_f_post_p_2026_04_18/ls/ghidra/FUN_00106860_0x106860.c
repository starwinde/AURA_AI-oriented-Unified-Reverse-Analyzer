
int FUN_00106860(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  iVar1 = ((uint)((long)param_2[0xd] < (long)param_1[0xd]) -
          (uint)((long)param_1[0xd] < (long)param_2[0xd])) +
          ((uint)((long)param_2[0xc] < (long)param_1[0xc]) -
          (uint)((long)param_1[0xc] < (long)param_2[0xc])) * 2;
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_2,(char *)*param_1);
    return iVar1;
  }
  return iVar1;
}

