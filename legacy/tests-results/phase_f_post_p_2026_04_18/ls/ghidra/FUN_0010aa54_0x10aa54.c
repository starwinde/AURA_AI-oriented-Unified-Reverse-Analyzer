
uint FUN_0010aa54(void)

{
  uint uVar1;
  uint uVar2;
  
  if ((DAT_00140f30 & 1) == 0) {
    uVar2 = -(uint)DAT_00140f28 & 0x400 | 2;
  }
  else {
    uVar2 = -(uint)DAT_00140f28 & 0x400 | 0x102;
  }
  if (DAT_00140f2c == 0) {
    if (((DAT_001400ca & 1) == 0) && ((DAT_00140f38 & 1) == 0)) {
      uVar2 = uVar2 | *(uint *)(&DAT_00118460 + (ulong)DAT_00140f34 * 4) | 0x204;
    }
    else {
      uVar2 = uVar2 | *(uint *)(&DAT_00118460 + (ulong)DAT_00140f34 * 4) | 0x20c;
    }
    uVar2 = -(uint)DAT_001400cb & 0x10 | uVar2;
  }
  if (DAT_00140f3c != 4) {
    if (DAT_00140f3c < 5) {
      uVar1 = uVar2 | 0x200;
      if (DAT_00140f3c != 3) {
        uVar1 = uVar2;
      }
      return uVar1;
    }
    if (DAT_00140f3c == 5) {
      uVar2 = uVar2 | *(uint *)(&DAT_00118460 + (ulong)DAT_00140f34 * 4);
    }
  }
  return uVar2;
}

