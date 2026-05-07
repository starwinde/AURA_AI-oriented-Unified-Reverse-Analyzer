
ulong FUN_00117f30(undefined1 param_1 [16])

{
  undefined8 uVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar5 = param_1._8_8_;
  uVar6 = param_1._0_8_;
  uVar1 = fpcr;
  uVar3 = uVar5 >> 0x30 & 0x7fff;
  if (uVar3 < 0x3fff) {
    if ((uVar3 != 0) || (uVar4 = 0, uVar6 != 0 || (uVar5 & 0xffffffffffff) != 0)) {
      uVar4 = 0;
      FUN_001180e0(0x10);
    }
  }
  else if ((long)uVar5 < 0) {
    uVar4 = 0;
    FUN_001180e0(1);
  }
  else if (uVar3 < 0x403f) {
    uVar5 = uVar5 & 0xffffffffffff | 0x1000000000000;
    iVar2 = (int)uVar3;
    if ((long)(0x406f - uVar3) < 0x40) {
      uVar4 = uVar6 >> ((ulong)(0x406f - iVar2) & 0x3f) | uVar5 << ((ulong)(iVar2 - 0x402f) & 0x3f);
      uVar5 = uVar6 << ((ulong)(iVar2 - 0x402f) & 0x3f);
    }
    else {
      uVar4 = uVar5 >> ((ulong)(0x402f - iVar2) & 0x3f);
      uVar5 = uVar6 | uVar5 << ((ulong)(iVar2 - 0x3fef) & 0x3f);
      if (0x406f - uVar3 == 0x40) {
        uVar5 = uVar6;
      }
    }
    if (uVar5 != 0) {
      FUN_001180e0(0x10);
    }
  }
  else {
    uVar4 = 0xffffffffffffffff;
    FUN_001180e0(1);
  }
  return uVar4;
}

