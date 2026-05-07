
undefined4 FUN_00198284(undefined8 param_1,uint param_2)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  uVar4 = param_2 & 0xfff;
  uVar5 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar6 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar1 = param_2 >> 0x1c;
  uVar7 = 3;
  if ((int)uVar6 == 0xf || (int)uVar6 == (int)uVar5) {
    uVar7 = 1;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
  if (((param_2 >> 0x17 & 1) == 0) && (bVar2 = uVar4 == 0, uVar4 = -uVar4, bVar2)) {
    uVar4 = 0x80000000;
  }
  FUN_00190140(param_1,uVar4);
  if (uVar1 != 0xf) {
    iVar3 = FUN_0018ffb0(param_1);
    if (iVar3 == 0xc4f) {
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

