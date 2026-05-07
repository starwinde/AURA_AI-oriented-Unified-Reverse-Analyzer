
undefined1  [16] FUN_00118040(ulong param_1)

{
  undefined1 auVar1 [16];
  int iVar2;
  ulong uVar3;
  undefined1 auVar4 [16];
  
  if (param_1 == 0) {
    return ZEXT816(0);
  }
  iVar2 = (int)LZCOUNT(param_1);
  uVar3 = (ulong)(0x403eU - iVar2 & 0x7fff);
  if (0x406f - (long)(int)(0x403eU - iVar2) < 0x40) {
    auVar4._8_8_ = param_1 >> ((ulong)(0xf - iVar2) & 0x3f) & 0xffffffffffff | uVar3 << 0x30;
    auVar4._0_8_ = param_1 << ((ulong)(iVar2 + 0x31) & 0x3f);
    return auVar4;
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = param_1 << ((ulong)(iVar2 - 0xf) & 0x3f) & 0xffffffffffff | uVar3 << 0x30;
  return auVar1 << 0x40;
}

