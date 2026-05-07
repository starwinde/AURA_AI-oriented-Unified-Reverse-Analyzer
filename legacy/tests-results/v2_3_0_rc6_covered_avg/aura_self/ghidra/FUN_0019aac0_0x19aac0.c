
undefined8 FUN_0019aac0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  uVar5 = param_2 >> 0x1c & 0xf;
  uVar3 = (param_2 & 0xffffffff) >> 0xc & 0xf;
  iVar4 = (int)uVar5;
  if (iVar4 == 0xf) {
    uVar6 = FUN_00196224();
    return uVar6;
  }
  if ((int)uVar3 == 0xf) {
    uVar6 = 1;
    FUN_00190100(param_1,0xb);
  }
  else {
    uVar6 = 3;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar3 * 2));
  }
  uVar1 = (uint)param_2 & 0xf;
  if (uVar1 == 0xf) {
    uVar6 = 1;
    FUN_00190100(param_1,0xb);
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  }
  uVar1 = (uint)((param_2 & 0xffffffff) >> 0x10) & 0xf;
  if (uVar1 == 0xf) {
    uVar6 = 1;
    FUN_00190100(param_1,0xb);
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
  }
  iVar2 = FUN_0018ffb0(param_1);
  if (iVar2 == 0xc4f) {
    if (iVar4 == 0xe) {
      return 0;
    }
    FUN_00190140(param_1,uVar5);
  }
  else {
    FUN_00190140(param_1,uVar5);
    if (iVar4 == 0xe) {
      FUN_00190100(param_1,0);
      return uVar6;
    }
  }
  FUN_00190100(param_1,3);
  return uVar6;
}

