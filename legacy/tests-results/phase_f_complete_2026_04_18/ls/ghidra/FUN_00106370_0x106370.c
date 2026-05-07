
int FUN_00106370(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  iVar1 = ((uint)((long)param_1[0x11] < (long)param_2[0x11]) -
          (uint)((long)param_2[0x11] < (long)param_1[0x11])) +
          ((uint)((long)param_1[0x10] < (long)param_2[0x10]) -
          (uint)((long)param_2[0x10] < (long)param_1[0x10])) * 2;
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_1,(char *)*param_2);
    return iVar1;
  }
  return iVar1;
}

