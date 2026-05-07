
undefined8 FUN_0019a190(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  wchar16 wVar5;
  
  uVar4 = (uint)param_2;
  uVar2 = param_2 >> 0xc;
  uVar3 = ((uint)(param_2 >> 0x18) & 1) << 7 | (uVar4 & 0x70000) >> 0xc |
          uVar4 & 0xf00 | ((uint)(param_2 >> 5) & 1) << 0xc | uVar4 & 0xf;
  uVar1 = (uint)uVar2 & 0xf | (uVar4 & 0x400000) >> 0x12;
  if ((uVar4 >> 6 & 1) == 0) {
    wVar5 = *(wchar16 *)(&DAT_0022f4e0 + (ulong)uVar1 * 2);
    FUN_00190100(param_1,wVar5);
    FUN_00190140(param_1,uVar3);
    uVar3 = FUN_0018ffb0(param_1);
    if (uVar3 < 0x777) {
      if (0x774 < uVar3) goto LAB_0019a250;
      if (uVar3 < 0x40e) {
        if (uVar3 < 0x40c) {
          return 3;
        }
        goto LAB_0019a250;
      }
      uVar3 = uVar3 - 0x40e;
    }
    else {
      uVar3 = uVar3 - 0x777;
    }
    if (1 < uVar3) {
      return 3;
    }
    if ((uVar2 & 1) != 0) {
      return 0;
    }
    wVar5 = L"23456789:;<=>?@A"[uVar1 >> 1];
    goto LAB_0019a250;
  }
  if ((uVar2 & 1) != 0) {
    return 0;
  }
  wVar5 = L"23456789:;<=>?@A"[uVar1 >> 1];
  FUN_00190100(param_1,wVar5);
  FUN_00190140(param_1,uVar3);
  uVar3 = FUN_0018ffb0(param_1);
  if (uVar3 < 0x777) {
    if (uVar3 < 0x775) {
      if (0x40d < uVar3) {
        uVar3 = uVar3 - 0x40e;
        goto joined_r0x0019a2ec;
      }
      if (uVar3 < 0x40c) {
        return 3;
      }
    }
    wVar5 = *(wchar16 *)(&DAT_0022f4e0 + (ulong)uVar1 * 2);
  }
  else {
    uVar3 = uVar3 - 0x777;
joined_r0x0019a2ec:
    if (1 < uVar3) {
      return 3;
    }
  }
LAB_0019a250:
  FUN_00190100(param_1,wVar5);
  return 3;
}

