
bool FUN_00105f04(long *param_1,long *param_2)

{
  if (*param_1 != *param_2) {
    return false;
  }
  return param_1[1] == param_2[1];
}

