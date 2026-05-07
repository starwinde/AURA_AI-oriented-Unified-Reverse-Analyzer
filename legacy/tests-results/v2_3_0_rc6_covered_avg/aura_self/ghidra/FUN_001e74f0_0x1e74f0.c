
undefined ** FUN_001e74f0(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_0056d9a0,0xe,param_1);
  if (uVar1 != 0xffffffff) {
    return &PTR_s_s12e0r_005f9b80 + (ulong)*(uint *)(&DAT_0056d9a4 + (ulong)uVar1 * 8) * 2;
  }
  return (undefined **)0x0;
}

