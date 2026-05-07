
undefined * FUN_001e76f0(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056e090,0xc,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005fa950 + (ulong)*(uint *)(&DAT_0056e094 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

