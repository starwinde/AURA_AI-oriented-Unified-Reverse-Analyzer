
bool FUN_001071b4(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  
  if (param_1[1] != param_2[1]) {
    return false;
  }
  if (param_1[2] != param_2[2]) {
    return false;
  }
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  return iVar1 == 0;
}

