
void FUN_00190614(undefined8 param_1,int param_2)

{
  if (param_2 < 0) {
    if (param_2 < -9) {
      if (param_2 != -0x80000000) {
        param_2 = -param_2;
      }
      FUN_001903f0(param_1,"#-0x%x",param_2);
      return;
    }
    FUN_001903f0(param_1,&DAT_001fdd80,-param_2);
    return;
  }
  if (9 < param_2) {
    FUN_001903f0(param_1,"#0x%x");
    return;
  }
  FUN_001903f0(param_1,&DAT_001fdd78);
  return;
}

