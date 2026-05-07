
undefined * FUN_001e7924(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e1d0,0x11,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fabe0 + (ulong)*(uint *)(&DAT_0056e1d4 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

