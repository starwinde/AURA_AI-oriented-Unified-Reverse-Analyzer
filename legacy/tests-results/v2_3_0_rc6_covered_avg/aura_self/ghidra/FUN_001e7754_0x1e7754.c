
undefined * FUN_001e7754(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e0f0,0x12,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005faa10 + (ulong)*(uint *)(&DAT_0056e0f4 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

