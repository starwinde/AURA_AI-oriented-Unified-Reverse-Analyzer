
void FUN_001e524c(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  
  FUN_0018ffd0();
  uVar1 = FUN_001900a0();
  uVar1 = uVar1 & 3;
  if (uVar1 == 2) {
    FUN_00190370(param_3,"{ru-sae}");
    FUN_001e6884(param_1);
    FUN_001e6830(param_1,3);
    return;
  }
  if (uVar1 != 3) {
    if (uVar1 != 1) {
      FUN_00190370(param_3,"{rn-sae}");
      FUN_001e6884(param_1);
      FUN_001e6830(param_1,1);
      return;
    }
    FUN_00190370(param_3,"{rd-sae}");
    FUN_001e6884(param_1);
    FUN_001e6830(param_1,2);
    return;
  }
  FUN_00190370(param_3,"{rz-sae}");
  FUN_001e6884(param_1);
  FUN_001e6830(param_1,4);
  return;
}

