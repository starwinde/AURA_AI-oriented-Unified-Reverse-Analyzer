
undefined1 * lookupSVEPREDPATByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_4,0x11,param_1);
  if (uVar1 != 0xffffffff) {
    return SVEPREDPATsList + (ulong)*(uint *)(Index_4 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

