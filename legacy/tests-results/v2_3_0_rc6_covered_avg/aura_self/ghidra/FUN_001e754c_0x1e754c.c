
undefined * FUN_001e754c(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056da10,0xc,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005f9c60 + (ulong)*(uint *)(&DAT_0056da14 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

