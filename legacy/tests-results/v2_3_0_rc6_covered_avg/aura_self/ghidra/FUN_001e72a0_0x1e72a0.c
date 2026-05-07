
long FUN_001e72a0(long param_1,int param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  lVar2 = 0;
  if (lVar1 != 0) {
    lVar2 = lVar1 + (long)(int)((uint)*(byte *)(lVar1 + 0x60) + param_2) * 0x10 + 100;
  }
  return lVar2;
}

