
long PPC_get_detail_op(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (lVar1 != 0) {
    lVar1 = lVar1 + (long)(int)((uint)*(byte *)(lVar1 + 0x69) + param_2) * 0x18 + 0x70;
  }
  return lVar1;
}

