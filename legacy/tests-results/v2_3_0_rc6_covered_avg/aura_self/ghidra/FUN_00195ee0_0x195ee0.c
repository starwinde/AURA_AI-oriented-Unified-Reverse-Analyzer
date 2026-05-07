
undefined8 FUN_00195ee0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = param_2 >> 9 & 0x7fffff;
  iVar2 = FUN_0018ffb0();
  if (((iVar2 - 0xbe6U < 0x18) && ((0x8a2011UL >> ((ulong)(iVar2 - 0xbe6U) & 0x3f) & 1) != 0)) &&
     ((int)uVar5 == 0xf)) {
    return 0;
  }
  uVar1 = (uint)param_2 & 0xff;
  uVar3 = FUN_0018ffb0(param_1);
  if (uVar3 < 0xb3c) {
    if (0xb17 < uVar3) {
      uVar4 = 0x810204001 >> ((ulong)(uVar3 - 0xb18) & 0x3f);
joined_r0x00195fa8:
      if ((uVar4 & 1) != 0) {
        FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
        uVar5 = (ulong)uVar1;
        goto LAB_00195f74;
      }
    }
  }
  else if (uVar3 - 0xbe6 < 0x14) {
    uVar4 = 0x82001L >> ((ulong)(uVar3 - 0xbe6) & 0x3f);
    goto joined_r0x00195fa8;
  }
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
  uVar5 = 0xffffffff80000000;
  if (((param_2 & 0x1ff) != 0) && (uVar5 = (long)(int)-uVar1, (param_2 & 0x100) != 0)) {
    uVar5 = (ulong)uVar1;
  }
LAB_00195f74:
  FUN_00190140(param_1,uVar5);
  return 3;
}

