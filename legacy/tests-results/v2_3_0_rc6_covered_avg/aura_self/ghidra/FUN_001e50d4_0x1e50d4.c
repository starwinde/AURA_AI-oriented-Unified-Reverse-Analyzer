
void FUN_001e50d4(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  FUN_0018ffd0();
  lVar1 = FUN_001900a0();
  if (lVar1 == 4) {
    FUN_00190370(param_3,&DAT_001fe140);
    FUN_001e67d0(param_1,5);
    return;
  }
  if (lVar1 < 5) {
    if (lVar1 == 2) {
      FUN_00190370(param_3,&DAT_001fe190);
      FUN_001e67d0(param_1,3);
      return;
    }
    if (lVar1 == 3) {
      FUN_00190370(param_3,"ge");
      FUN_001e67d0(param_1,4);
      return;
    }
    if (lVar1 == 1) {
      FUN_00190370(param_3,"le");
      FUN_001e67d0(param_1,2);
      return;
    }
  }
  else {
    if (lVar1 == 6) {
      FUN_00190370(param_3,"false");
      FUN_001e67d0(param_1,7);
      return;
    }
    if (lVar1 == 7) {
      FUN_00190370(param_3,&DAT_00203a90);
      FUN_001e67d0(param_1,8);
      return;
    }
    if (lVar1 == 5) {
      FUN_00190370(param_3,&DAT_00203a58);
      FUN_001e67d0(param_1,6);
      return;
    }
  }
  FUN_00190370(param_3,&DAT_001fe188);
  FUN_001e67d0(param_1,1);
  return;
}

