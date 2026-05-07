
undefined4 FUN_00198900(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  undefined4 uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  
  uVar5 = param_2 & 0xffffffff;
  uVar6 = (uint)(param_2 >> 0x18) & 0xff;
  uVar8 = uVar5 >> 0x10 & 0xf;
  uVar9 = uVar5 >> 0xc & 0xf;
  uVar10 = (uint)(uVar5 >> 0x18) & 1;
  uVar11 = (uint)(param_2 >> 0x15) & 0x7ff;
  uVar2 = FUN_0018ffb0();
  if (uVar2 < 0x35c) {
    if (0x357 < uVar2) {
LAB_001989c8:
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
  }
  else if (uVar2 - 0x36c < 4) goto LAB_001989c8;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar9 * 2));
  uVar3 = FUN_0018ffb0(param_1);
  uVar2 = (uint)param_2;
  if (uVar3 < 0x281) {
    if (uVar3 < 0x27d) goto LAB_00198980;
LAB_001989f0:
    uVar1 = *(undefined2 *)(&DAT_0022f720 + uVar8 * 2);
    FUN_00190100(param_1,uVar1);
    FUN_00190100(param_1,uVar1);
    uVar3 = (uint)(uVar5 >> 0x17) & 1;
    uVar11 = uVar10 ^ 1 | uVar11;
    if ((uVar6 & uVar11 & 1) != 0) goto LAB_00198a24;
LAB_001989a8:
    if ((param_2 & 0x1000000) == 0) {
      uVar10 = 0x20000;
    }
    else {
      uVar10 = 0;
      uVar6 = 0;
      uVar7 = 3;
      if ((uVar11 & 1) == 0) goto joined_r0x00198a3c;
    }
  }
  else {
    if (uVar3 - 0x29b < 4) goto LAB_001989f0;
LAB_00198980:
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    uVar3 = (uint)(uVar5 >> 0x17) & 1;
    uVar11 = uVar10 ^ 1 | uVar11;
    if ((uVar6 & uVar11 & 1) == 0) goto LAB_001989a8;
LAB_00198a24:
    uVar10 = 0x10000;
  }
  uVar7 = 3;
  uVar6 = uVar10;
  if ((int)uVar8 == 0xf || (int)uVar8 == (int)uVar9) {
    uVar7 = 1;
  }
joined_r0x00198a3c:
  if ((uVar2 >> 0x19 & 1) == 0) {
    FUN_00190100(param_1,0);
    FUN_00190140(param_1,uVar2 & 0xfff | uVar6 | uVar3 << 0xc ^ 0x5000);
  }
  else {
    if ((uVar2 & 0xf) == 0xf) {
      uVar7 = 1;
      FUN_00190100(param_1,0xb);
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar2 & 0xf) * 2));
    }
    uVar10 = ((uint)(uVar5 >> 5) & 3) - 1;
    uVar11 = 0x4000;
    if ((uVar10 < 3) &&
       (uVar11 = *(int *)(&DAT_0022bbf0 + (ulong)uVar10 * 4) << 0xd,
       (param_2 & 0xf80) == 0 && *(int *)(&DAT_0022bbf0 + (ulong)uVar10 * 4) == 4)) {
      uVar11 = 0xa000;
    }
    FUN_00190140(param_1,uVar11 | uVar6 | (uint)(uVar5 >> 7) & 0x1f | uVar3 << 0xc ^ 0x1000);
  }
  if (uVar2 >> 0x1c == 0xf) {
    return 0;
  }
  uVar2 = uVar2 >> 0x1c;
  iVar4 = FUN_0018ffb0(param_1);
  if (iVar4 == 0xc4f) {
    if (uVar2 == 0xe) {
      return 0;
    }
    FUN_00190140(param_1,uVar2);
  }
  else {
    FUN_00190140(param_1,uVar2);
    if (uVar2 == 0xe) {
      FUN_00190100(param_1,0);
      return uVar7;
    }
  }
  FUN_00190100(param_1,3);
  return uVar7;
}

