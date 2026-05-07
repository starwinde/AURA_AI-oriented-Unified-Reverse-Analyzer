
undefined * FUN_001e75b4(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056da70,0x1c,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005f9d20 + (ulong)*(uint *)(&DAT_0056da74 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

