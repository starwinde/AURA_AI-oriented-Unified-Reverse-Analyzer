
undefined4 FUN_0010af10(ulong param_1,uint param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  if ((param_1 & 1) == 0) {
    uVar2 = 0;
    if (((((param_3 != 5) && (uVar2 = 0x2f, param_3 != 3 && param_3 != 9)) &&
         (uVar2 = 0, DAT_00140f80 != 1)) &&
        ((uVar2 = 0x40, param_3 != 6 && (uVar2 = 0x7c, param_3 != 1)))) &&
       (uVar2 = 0x3d, param_3 != 7)) {
      uVar2 = 0;
    }
  }
  else {
    uVar1 = param_2 & 0xf000;
    if (uVar1 == 0x8000) {
      uVar2 = 0;
      if ((DAT_00140f80 == 3) && (uVar2 = 0x2a, (param_2 & 0x49) == 0)) {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0x2f;
      if (((uVar1 != 0x4000) && (uVar2 = 0, DAT_00140f80 != 1)) &&
         ((uVar2 = 0x40, uVar1 != 0xa000 &&
          ((uVar2 = 0x7c, uVar1 != 0x1000 && (uVar2 = 0x3d, uVar1 != 0xc000)))))) {
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

