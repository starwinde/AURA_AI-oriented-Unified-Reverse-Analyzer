
undefined1 * lookupICByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_13,3,param_1);
  if (uVar1 != 0xffffffff) {
    return ICsList + (ulong)*(uint *)(Index_13 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

