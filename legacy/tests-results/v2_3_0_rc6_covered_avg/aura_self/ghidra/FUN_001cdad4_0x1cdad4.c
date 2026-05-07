
void FUN_001cdad4(undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = FUN_001e7ac4(param_3);
  lVar3 = FUN_001e7ac4(param_4);
  FUN_0018ffd0(param_1,3);
  iVar1 = FUN_001900a0();
  if (iVar1 != 0) {
    FUN_00190370(param_2,*(undefined8 *)(lVar3 + 0x10));
    return;
  }
  FUN_00190370(param_2,*(undefined8 *)(lVar2 + 0x10));
  return;
}

