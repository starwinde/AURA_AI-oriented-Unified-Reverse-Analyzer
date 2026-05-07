
undefined4 FUN_001e5d60(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (0x40a < param_1) {
    if (0x3b6d < param_1) {
      return 0;
    }
    uVar4 = 0x59;
    uVar3 = 0;
    do {
      uVar1 = uVar4 + uVar3;
      uVar2 = uVar1 >> 1;
      uVar5 = (uint)*(ushort *)(&DAT_00409c00 + (ulong)uVar2 * 0xc);
      if (param_1 < uVar5 || param_1 == uVar5) {
        uVar4 = uVar2 - 1;
        if (param_1 == uVar5) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = *(undefined4 *)(&DAT_00409c08 + ((ulong)(uVar2 << 1) + (long)(int)uVar2) * 4)
            ;
          }
          return *(undefined4 *)(&DAT_00409c04 + (long)(int)uVar2 * 0xc);
        }
        if (uVar1 < 2) break;
      }
      else {
        uVar3 = uVar2 + 1;
      }
    } while (uVar3 <= uVar4);
    if (0x1f80 < param_1) {
      return 0;
    }
  }
  uVar4 = 0xe;
  uVar3 = 0;
  do {
    uVar1 = uVar3 + uVar4;
    uVar2 = uVar1 >> 1;
    uVar5 = (uint)*(ushort *)(&DAT_0040a038 + (ulong)uVar2 * 0xc);
    if (param_1 < uVar5 || param_1 == uVar5) {
      uVar4 = uVar2 - 1;
      if (param_1 == uVar5) {
        if (param_2 != (undefined4 *)0x0) {
          *param_2 = *(undefined4 *)(&DAT_0040a040 + ((ulong)(uVar2 << 1) + (long)(int)uVar2) * 4);
        }
        return *(undefined4 *)(&DAT_0040a03c + (long)(int)uVar2 * 0xc);
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

