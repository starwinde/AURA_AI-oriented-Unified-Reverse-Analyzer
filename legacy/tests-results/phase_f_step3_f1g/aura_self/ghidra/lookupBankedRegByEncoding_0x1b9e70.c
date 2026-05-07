
undefined ** lookupBankedRegByEncoding(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_7,0x21,param_1);
  if (uVar1 != 0xffffffff) {
    return &BankedRegsList + (ulong)*(uint *)(Index_7 + (ulong)uVar1 * 8 + 4) * 2;
  }
  return (undefined **)0x0;
}

