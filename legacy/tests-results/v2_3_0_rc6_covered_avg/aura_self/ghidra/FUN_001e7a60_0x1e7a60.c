
undefined * FUN_001e7a60(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e2a0,4,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fad50 + (ulong)*(uint *)(&DAT_0056e2a4 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

