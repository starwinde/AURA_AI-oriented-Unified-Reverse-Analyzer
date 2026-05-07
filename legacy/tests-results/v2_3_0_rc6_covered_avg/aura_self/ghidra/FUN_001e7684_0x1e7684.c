
undefined * FUN_001e7684(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056db70,0xa4,param_1);
  if (uVar1 != 0xffffffff) {
    return &UNK_005f9f10 + (ulong)*(uint *)(&DAT_0056db74 + (ulong)uVar1 * 8) * 0x10;
  }
  return (undefined *)0x0;
}

