
void FUN_001b3770(long param_1,undefined4 param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0xf0);
  bVar2 = *(byte *)(lVar3 + 0x80);
  lVar1 = lVar3 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
  *(undefined4 *)(lVar1 + 0x94) = 2;
  *(undefined4 *)(lVar1 + 0x98) = param_2;
  *(byte *)(lVar3 + 0x80) = bVar2 + 1;
  return;
}

