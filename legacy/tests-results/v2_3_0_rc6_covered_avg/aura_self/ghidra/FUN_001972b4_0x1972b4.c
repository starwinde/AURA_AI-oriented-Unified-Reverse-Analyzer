
undefined8 FUN_001972b4(undefined8 param_1,ulong param_2)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  
  uVar3 = param_2 >> 0x1c & 0xf;
  FUN_00190140(param_1,param_2 & 0xff);
  iVar2 = (int)uVar3;
  if (iVar2 == 0xf) {
    return 0;
  }
  iVar1 = FUN_0018ffb0(param_1);
  if (iVar1 == 0xc4f) {
    if (iVar2 == 0xe) {
      return 0;
    }
    FUN_00190140(param_1,uVar3);
  }
  else {
    FUN_00190140(param_1,uVar3);
    if (iVar2 == 0xe) {
      FUN_00190100(param_1,0);
      return 3;
    }
  }
  FUN_00190100(param_1,3);
  if (((uint)param_2 & 0xff) != 0x10) {
    return 3;
  }
  return 1;
}

