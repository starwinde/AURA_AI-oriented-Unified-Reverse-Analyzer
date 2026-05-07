
undefined1  [16] FUN_00117ec0(uint param_1)

{
  undefined1 auVar1 [16];
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = (int)LZCOUNT((ulong)param_1);
    auVar1._8_8_ = 0;
    auVar1._0_8_ = (ulong)param_1 << ((ulong)(iVar2 - 0xf) & 0x3f) & 0xffffffffffff |
                   (ulong)(0x403eU - iVar2 & 0x7fff) << 0x30;
    return auVar1 << 0x40;
  }
  return ZEXT816(0) << 0x40;
}

