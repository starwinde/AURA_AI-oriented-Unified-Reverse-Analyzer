
undefined1 * lookupATByEncoding(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = binsearch_IndexTypeEncoding(&Index_16,0xe,param_1);
  if (uVar1 != 0xffffffff) {
    return &ATsList + (ulong)*(uint *)(&DAT_0056bde4 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined1 *)0x0;
}

