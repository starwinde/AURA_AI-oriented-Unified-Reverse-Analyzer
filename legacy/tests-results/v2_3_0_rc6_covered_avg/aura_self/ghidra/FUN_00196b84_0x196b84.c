
undefined8 FUN_00196b84(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar2 = (uint)((param_2 & 0xffffffff) >> 0xc) & 0xf;
  uVar1 = (uint)param_2 & 0xfff;
  if (uVar2 == 0xf) {
    uVar4 = FUN_0018ffb0();
    if (uVar4 == 0xb32) {
      FUN_0018ff90(param_1,0xb72);
    }
    else if (uVar4 < 0xb33) {
      if ((uVar4 == 0xb1d) || (uVar4 == 0xb2b)) {
        FUN_0018ff90(param_1,0xb6e);
      }
    }
    else if (uVar4 == 0xb39) {
      return 0;
    }
  }
  iVar3 = FUN_0018ffb0(param_1);
  if ((iVar3 - 0xb6eU & 0xfffffffb) != 0) {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
  }
  uVar5 = (ulong)uVar1;
  if ((((uint)param_2 >> 0x17 & 1) == 0) && (uVar5 = (ulong)(int)-uVar1, (param_2 & 0xfff) == 0)) {
    uVar5 = 0xffffffff80000000;
  }
  FUN_00190140(param_1,uVar5);
  return 3;
}

