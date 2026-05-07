
uint ctx32_isra_0(long param_1,int param_2,long param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + param_3);
  uVar2 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
  uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
  if (param_2 == 0) {
    uVar2 = uVar1;
  }
  return uVar2;
}

