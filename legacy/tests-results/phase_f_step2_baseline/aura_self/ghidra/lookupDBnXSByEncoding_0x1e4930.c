
undefined1 * lookupDBnXSByEncoding(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_1,4,param_1);
  if (uVar1 != 0xffffffff) {
    return DBnXSsList + (ulong)*(uint *)(Index_1 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

