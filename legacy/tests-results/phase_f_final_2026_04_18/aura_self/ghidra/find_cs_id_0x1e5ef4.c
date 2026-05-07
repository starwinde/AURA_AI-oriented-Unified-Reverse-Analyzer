
ulong find_cs_id(uint param_1,ushort *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_3 - 1;
  if ((*param_2 <= param_1) && (param_1 <= param_2[(ulong)uVar2 * 0x2f])) {
    uVar3 = 0;
    do {
      while( true ) {
        uVar1 = uVar3 + uVar2 >> 1;
        if (param_2[(ulong)uVar1 * 0x2f] == param_1) {
          return (ulong)uVar1;
        }
        if (param_2[(ulong)uVar1 * 0x2f] <= param_1) break;
        uVar2 = uVar1 - 1;
        if (uVar2 < uVar3) {
          return 0xffffffff;
        }
      }
      uVar3 = uVar1 + 1;
    } while (uVar3 <= uVar2);
  }
  return 0xffffffff;
}

