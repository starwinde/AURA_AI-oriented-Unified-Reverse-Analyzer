
undefined4 FUN_00197b14(long param_1,ulong param_2)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  int iVar4;
  ulong uVar5;
  
  uVar2 = param_2 & 0xffffffff;
  uVar5 = param_2 >> 0x1c & 0xf;
  iVar4 = (int)uVar5;
  if (iVar4 != 0xf) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (uVar2 >> 0x10 & 0xf) * 2));
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)((uint)param_2 & 0xf) * 2));
    iVar1 = FUN_0018ffb0(param_1);
    if (iVar1 == 0xc4f) {
      if (iVar4 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,uVar5);
    }
    else {
      FUN_00190140(param_1,uVar5);
      if (iVar4 == 0xe) {
        FUN_00190100(param_1,0);
        return 3;
      }
    }
    FUN_00190100(param_1,3);
    return 3;
  }
  if ((((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) && ((int)(uVar2 >> 0x14) == 0xf11))
     && ((param_2 & 0xf0) == 0)) {
    uVar3 = 3;
    if ((param_2 & 0xffc0f) != 0) {
      uVar3 = 1;
    }
    FUN_0018ff90(param_1,0x2f6,(uint)param_2 & 0xffc0f);
    FUN_00190140(param_1,uVar2 >> 9 & 1);
    return uVar3;
  }
  return 0;
}

