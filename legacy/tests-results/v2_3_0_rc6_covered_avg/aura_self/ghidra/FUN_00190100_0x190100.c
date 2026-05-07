
void FUN_00190100(long param_1,undefined4 param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 4);
  *(byte *)(param_1 + 4) = bVar1 + 1;
  param_1 = param_1 + (ulong)bVar1 * 0x10;
  *(undefined4 *)(param_1 + 0x10) = 1;
  *(undefined1 *)(param_1 + 0x14) = 1;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  return;
}

