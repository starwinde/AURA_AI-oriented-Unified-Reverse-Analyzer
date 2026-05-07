
undefined4 FUN_001e5b80(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (0x99 < param_1) {
    if (0x3b96 < param_1) {
      return 0;
    }
    uVar4 = 0x56;
    uVar3 = 0;
    do {
      uVar1 = uVar4 + uVar3;
      uVar2 = uVar1 >> 1;
      uVar5 = (uint)*(ushort *)(&DAT_00409670 + (ulong)uVar2 * 0xc);
      if (param_1 < uVar5 || param_1 == uVar5) {
        uVar4 = uVar2 - 1;
        if (param_1 == uVar5) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = *(undefined4 *)(&DAT_00409678 + ((ulong)(uVar2 << 1) + (long)(int)uVar2) * 4)
            ;
          }
          return *(undefined4 *)(&DAT_00409674 + (long)(int)uVar2 * 0xc);
        }
        if (uVar1 < 2) break;
      }
      else {
        uVar3 = uVar2 + 1;
      }
    } while (uVar3 <= uVar4);
    if (0x3b72 < param_1) {
      return 0;
    }
  }
  uVar4 = 0x11;
  uVar3 = 0;
  do {
    uVar1 = uVar3 + uVar4;
    uVar2 = uVar1 >> 1;
    uVar5 = (uint)*(ushort *)(&DAT_00409a88 + (ulong)uVar2 * 0xc);
    if (param_1 < uVar5 || param_1 == uVar5) {
      uVar4 = uVar2 - 1;
      if (param_1 == uVar5) {
        if (param_2 != (undefined4 *)0x0) {
          *param_2 = *(undefined4 *)(&DAT_00409a90 + ((ulong)(uVar2 << 1) + (long)(int)uVar2) * 4);
        }
        return *(undefined4 *)(&DAT_00409a8c + (long)(int)uVar2 * 0xc);
      }
      if (uVar1 < 2) {
        return 0;
      }
    }
    else {
      uVar3 = uVar2 + 1;
    }
    if (uVar4 < uVar3) {
      return 0;
    }
  } while( true );
}

