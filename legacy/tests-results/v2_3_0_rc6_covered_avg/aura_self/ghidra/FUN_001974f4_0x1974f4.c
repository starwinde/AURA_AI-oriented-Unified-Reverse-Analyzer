
undefined4 FUN_001974f4(long param_1,ulong param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (uint)param_2 & 0xf;
  uVar2 = (uint)param_2 >> 7;
  if (uVar4 == 0xd) {
    uVar5 = 3;
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 3;
    if (uVar4 == 0xf) {
      uVar5 = 1;
    }
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar4 * 2));
  uVar3 = ((uint)(param_2 >> 5) & 3) - 1;
  uVar4 = 2;
  uVar1 = *(undefined4 *)(&DAT_0022e300 + (ulong)uVar5 * 4);
  if ((uVar3 < 3) && (uVar4 = *(uint *)(&DAT_0022bbf0 + (ulong)uVar3 * 4), uVar2 == 0 && uVar4 == 4)
     ) {
    uVar4 = 5;
  }
  FUN_00190140(param_1,uVar4 | uVar2 << 3);
  return uVar1;
}

