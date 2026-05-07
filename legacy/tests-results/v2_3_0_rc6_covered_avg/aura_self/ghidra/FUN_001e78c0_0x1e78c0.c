
undefined * FUN_001e78c0(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e190,8,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fab60 + (ulong)*(uint *)(&DAT_0056e194 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

