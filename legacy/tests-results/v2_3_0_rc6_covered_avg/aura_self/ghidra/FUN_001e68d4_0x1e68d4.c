
undefined * FUN_001e68d4(undefined8 param_1,uint param_2,undefined8 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0x3b22;
  if (0x3b22 < param_2 - 0x92) {
    return (undefined *)0x0;
  }
  uVar2 = 0x3b22;
  uVar1 = 0x1e23;
  uVar4 = 0;
  do {
    uVar2 = uVar2 >> 1;
    if (param_2 == uVar1) {
      *param_3 = *(undefined8 *)(&UNK_0040aa28 + (ulong)uVar2 * 0x10);
      return &UNK_0040aa30 + (ulong)uVar2 * 0x10;
    }
    if (param_2 < uVar1) {
      uVar3 = uVar2 - 1;
      if (uVar3 < uVar4) {
        return (undefined *)0x0;
      }
    }
    else {
      uVar4 = uVar2 + 1;
      if (uVar3 < uVar4) {
        return (undefined *)0x0;
      }
    }
    uVar2 = uVar4 + uVar3;
    uVar1 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar2 >> 1) * 0x50);
  } while( true );
}

