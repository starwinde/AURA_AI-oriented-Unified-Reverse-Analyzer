
int FUN_00106a74(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  iVar1 = ((uint)((long)param_2[0xf] < (long)param_1[0xf]) -
          (uint)((long)param_1[0xf] < (long)param_2[0xf])) +
          ((uint)((long)param_2[0xe] < (long)param_1[0xe]) -
          (uint)((long)param_1[0xe] < (long)param_2[0xe])) * 2;
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_2,(char *)*param_1);
    return iVar1;
  }
  return iVar1;
}

