
void FUN_001cde24(undefined8 param_1,int param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  
  FUN_0018ffd0();
  iVar1 = FUN_001900a0();
  FUN_0018ffd0(param_1,param_2 + 1);
  uVar2 = FUN_001900a0();
  if (iVar1 != 0) {
    FUN_00190540(param_3,iVar1 << (ulong)(uVar2 & 0x1f));
    return;
  }
  if ((uVar2 & 0x3f) == 0) {
    FUN_00190540(param_3,0 << (ulong)(uVar2 & 0x1f));
    return;
  }
  FUN_001906d0(param_3,0);
  FUN_001cdbe4(param_1,param_2 + 1,param_3);
  return;
}

