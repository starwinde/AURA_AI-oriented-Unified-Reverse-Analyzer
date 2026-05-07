
undefined1 * lookupSVEPRFMByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_11,0xc,param_1);
  if (uVar1 != 0xffffffff) {
    return SVEPRFMsList + (ulong)*(uint *)(Index_11 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

