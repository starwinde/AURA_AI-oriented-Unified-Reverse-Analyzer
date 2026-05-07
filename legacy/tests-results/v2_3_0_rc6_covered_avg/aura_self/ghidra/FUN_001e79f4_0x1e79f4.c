
undefined * FUN_001e79f4(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e280,3,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fad20 + (ulong)*(uint *)(&DAT_0056e284 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

