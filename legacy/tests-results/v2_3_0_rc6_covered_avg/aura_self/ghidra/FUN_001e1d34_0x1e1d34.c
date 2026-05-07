
void FUN_001e1d34(long param_1,undefined4 param_2,undefined8 param_3)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 6) == '\x10') &&
     ((iVar1 = FUN_0018ffb0(), iVar1 == 0x2c9 || (iVar1 == 0x68b)))) {
    FUN_00190370(param_3,"xmmword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    FUN_001e1630(param_1,param_2,param_3);
    return;
  }
  FUN_00190370(param_3,"qword ptr ");
  *(undefined1 *)(param_1 + 0x328) = 8;
  FUN_001e1630(param_1,param_2,param_3);
  return;
}

