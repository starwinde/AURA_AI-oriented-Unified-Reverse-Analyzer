
undefined1 * lookupTLBIByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_12,0xa4,param_1);
  if (uVar1 != 0xffffffff) {
    return TLBIsList + (ulong)*(uint *)(Index_12 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

