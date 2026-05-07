
long FUN_00105ee0(ulong *param_1,ulong param_2)

{
  ulong uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = *param_1 / param_2;
  }
  return *param_1 - uVar1 * param_2;
}

