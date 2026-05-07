
undefined1 * lookupPRFMByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_10,0x12,param_1);
  if (uVar1 != 0xffffffff) {
    return PRFMsList + (ulong)*(uint *)(Index_10 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

