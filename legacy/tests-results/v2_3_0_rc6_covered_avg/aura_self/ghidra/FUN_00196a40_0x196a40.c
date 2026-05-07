
undefined8 FUN_00196a40(undefined8 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0xf) {
    return 0;
  }
  iVar1 = FUN_0018ffb0();
  if (iVar1 == 0xc4f) {
    if (param_2 == 0xe) {
      return 0;
    }
    FUN_00190140(param_1,param_2);
  }
  else {
    FUN_00190140(param_1,param_2);
    if (param_2 == 0xe) {
      FUN_00190100(param_1,0);
      return 3;
    }
  }
  FUN_00190100(param_1,3);
  return 3;
}

