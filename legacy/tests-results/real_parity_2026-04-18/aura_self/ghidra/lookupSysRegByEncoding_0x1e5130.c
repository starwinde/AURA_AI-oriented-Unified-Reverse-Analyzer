
undefined1 * lookupSysRegByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_6,0x3eb,param_1);
  if (uVar1 != 0xffffffff) {
    return SysRegsList + (ulong)*(uint *)(Index_6 + (ulong)uVar1 * 8 + 4) * 0x10;
  }
  return (undefined1 *)0x0;
}

