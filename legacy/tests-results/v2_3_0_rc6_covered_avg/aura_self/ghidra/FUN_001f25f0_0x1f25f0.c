
undefined1 FUN_001f25f0(uint param_1,undefined8 *param_2)

{
  uint uVar1;
  undefined1 uStack_6;
  
  if ((param_1 == 0) || (0x75d < param_1)) {
    *param_2 = 0;
    uStack_6 = 0;
  }
  else {
    uVar1 = *(uint *)(&DAT_005715d0 + (ulong)param_1 * 4);
    *param_2 = &UNK_00573348 + (long)(int)(uVar1 & 0xffff) * 10;
    uStack_6 = (undefined1)(uVar1 >> 0x10);
  }
  return uStack_6;
}

