
undefined4 FUN_00198150(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  uVar5 = param_2 & 0xfff;
  uVar6 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar2 = param_2 >> 0xc & 0xf;
  uVar7 = 3;
  if ((uint)uVar6 == 0xf || (uint)uVar6 == uVar2) {
    uVar7 = 1;
  }
  uVar1 = param_2 >> 0x1c;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
  if (((param_2 >> 0x17 & 1) == 0) && (bVar3 = uVar5 == 0, uVar5 = -uVar5, bVar3)) {
    uVar5 = 0x80000000;
  }
  FUN_00190140(param_1,uVar5);
  if (uVar1 != 0xf) {
    iVar4 = FUN_0018ffb0(param_1);
    if (iVar4 == 0xc4f) {
      if (uVar1 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,uVar1);
    }
    else {
      FUN_00190140(param_1,uVar1);
      if (uVar1 == 0xe) {
        FUN_00190100(param_1,0);
        return uVar7;
      }
    }
    FUN_00190100(param_1,3);
    return uVar7;
  }
  return 0;
}

