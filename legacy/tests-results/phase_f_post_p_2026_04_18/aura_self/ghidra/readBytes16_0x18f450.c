
ushort readBytes16(long param_1,ushort *param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = *param_2;
  uVar1 = uVar2 >> 8 | uVar2 << 8;
  if (-1 < *(int *)(*(long *)(param_1 + 800) + 4)) {
    uVar1 = uVar2;
  }
  return uVar1;
}

