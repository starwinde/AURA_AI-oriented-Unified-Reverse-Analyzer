
undefined * FUN_001e7860(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e2e0,0x3eb,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fadf0 + (ulong)*(uint *)(&DAT_0056e2e4 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

