
undefined1 * lookupMClassSysRegByM1Encoding12(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_8,0x25,param_1);
  if (uVar1 != 0xffffffff) {
    return MClassSysRegsList + (ulong)*(uint *)(Index_8 + (ulong)uVar1 * 8 + 4) * 0x20;
  }
  return (undefined1 *)0x0;
}

