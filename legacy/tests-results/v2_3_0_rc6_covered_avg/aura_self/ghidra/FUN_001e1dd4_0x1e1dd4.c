
void FUN_001e1dd4(long param_1,undefined4 param_2,undefined8 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0018ffb0();
  if ((iVar1 != 0x39b) && (iVar1 != 0x3b2)) {
    FUN_00190370(param_3,"dword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 4;
    FUN_001e1630(param_1,param_2,param_3);
    return;
  }
  iVar1 = *(int *)(*(long *)(param_1 + 800) + 4);
  if ((iVar1 - 4U & 0xfffffffb) == 0) {
    *(undefined1 *)(param_1 + 0x328) = 0x1c;
    FUN_001e1630(param_1,param_2,param_3);
    return;
  }
  if (iVar1 != 2) {
    FUN_001e1630(param_1,param_2,param_3);
    return;
  }
  *(undefined1 *)(param_1 + 0x328) = 0xe;
  FUN_001e1630(param_1,param_2,param_3);
  return;
}

