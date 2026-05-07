
uint readBytes32(long param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_2;
  uVar2 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
  uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
  if (-1 < *(int *)(*(long *)(param_1 + 800) + 4)) {
    uVar2 = uVar1;
  }
  return uVar2;
}

