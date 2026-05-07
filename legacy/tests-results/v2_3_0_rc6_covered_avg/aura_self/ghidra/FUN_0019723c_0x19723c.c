
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0019723c(long param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_2 != 0xd) {
    uVar1 = 3;
    if (param_2 == 0xf) {
      uVar1 = 1;
    }
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)param_2 * 2));
    return uVar1;
  }
  uVar1 = 3;
  if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
    uVar1 = 1;
  }
  FUN_00190100(param_1,_UNK_0022f73a);
  return uVar1;
}

