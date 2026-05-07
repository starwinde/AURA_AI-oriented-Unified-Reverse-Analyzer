
undefined1 * lookupDCByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_14,0x1c,param_1);
  if (uVar1 != 0xffffffff) {
    return DCsList + (ulong)*(uint *)(Index_14 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

