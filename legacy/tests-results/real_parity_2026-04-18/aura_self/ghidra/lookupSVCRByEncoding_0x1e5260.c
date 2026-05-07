
undefined1 * lookupSVCRByEncoding(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_3,3,param_1);
  if (uVar1 != 0xffffffff) {
    return SVCRsList + (ulong)*(uint *)(Index_3 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

