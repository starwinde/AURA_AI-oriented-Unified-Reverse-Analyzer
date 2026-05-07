
undefined1 * FUN_001e441c(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_15,0xc,param_1);
  if (uVar1 != 0xffffffff) {
    return DBsList + (ulong)*(uint *)(Index_15 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

