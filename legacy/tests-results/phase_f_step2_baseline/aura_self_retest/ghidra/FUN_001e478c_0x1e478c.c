
undefined1 * FUN_001e478c(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_5,8,param_1);
  if (uVar1 != 0xffffffff) {
    return PStatesList + (ulong)*(uint *)(Index_5 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

