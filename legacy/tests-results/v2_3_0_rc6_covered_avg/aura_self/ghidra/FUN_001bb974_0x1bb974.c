
undefined ** FUN_001bb974(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_00244750,0x25,param_1);
  if (uVar1 != 0xffffffff) {
    return &PTR_s_apsr_g_005ed690 + (ulong)*(uint *)(&DAT_00244754 + (ulong)uVar1 * 8) * 4;
  }
  return (undefined **)0x0;
}

