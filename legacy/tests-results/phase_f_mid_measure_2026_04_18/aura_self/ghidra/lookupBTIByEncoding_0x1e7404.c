
undefined1 * lookupBTIByEncoding(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_2,3,param_1);
  if (uVar1 != 0xffffffff) {
    return BTIsList + (ulong)*(uint *)(Index_2 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

