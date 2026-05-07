
uint MCRegisterClass_contains(long param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  
  if (param_1 != 0) {
    uVar2 = param_2 >> 3 & 0x1fffffff;
    uVar1 = 0;
    if ((uint)uVar2 < (uint)*(ushort *)(param_1 + 0x10)) {
      uVar1 = (int)(uint)*(byte *)(*(long *)(param_1 + 8) + uVar2) >> ((uint)param_2 & 7) & 1;
    }
    return uVar1;
  }
  return 0;
}

