
undefined ** FUN_001bb9e0(undefined1 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00190910(&DAT_00244640,0x21,param_1);
  if (uVar1 != 0xffffffff) {
    return &PTR_s_r8_usr_005ed480 + (ulong)*(uint *)(&DAT_00244644 + (ulong)uVar1 * 8) * 2;
  }
  return (undefined **)0x0;
}

