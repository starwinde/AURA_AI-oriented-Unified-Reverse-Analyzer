
undefined1 * FUN_001bb90c(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(Index_9,0x25,param_1);
  if (uVar1 != 0xffffffff) {
    return MClassSysRegsList + (ulong)*(uint *)(Index_9 + (ulong)uVar1 * 8 + 4) * 0x20;
  }
  return (undefined1 *)0x0;
}

