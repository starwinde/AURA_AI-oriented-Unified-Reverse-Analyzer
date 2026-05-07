
long FUN_00107110(ulong param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar2 = param_1 >> 3 | param_1 << 0x3d;
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = uVar2 / param_2;
  }
  return uVar2 - uVar1 * param_2;
}

