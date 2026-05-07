
void FUN_00190140(long param_1,undefined8 param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 4);
  *(byte *)(param_1 + 4) = bVar1 + 1;
  param_1 = param_1 + (ulong)bVar1 * 0x10;
  *(undefined4 *)(param_1 + 0x10) = 2;
  *(undefined1 *)(param_1 + 0x14) = 2;
  *(undefined8 *)(param_1 + 0x18) = param_2;
  return;
}

