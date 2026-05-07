
ulong binsearch_IndexTypeEncoding(ushort *param_1,long param_2,ushort param_3)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = param_2 - 1;
  if ((*param_1 <= param_3) && (param_3 <= param_1[uVar2 * 4])) {
    uVar4 = 0;
    do {
      uVar3 = uVar4 + uVar2 >> 1;
      uVar1 = param_1[uVar3 * 4];
      while( true ) {
        if (uVar1 == param_3) {
          return uVar3 & 0xffffffff;
        }
        if (param_3 <= uVar1) break;
        uVar4 = uVar3 + 1;
        if (uVar2 < uVar4) {
          return 0xffffffff;
        }
        uVar3 = uVar4 + uVar2 >> 1;
        uVar1 = param_1[uVar3 * 4];
      }
      uVar2 = uVar3 - 1;
    } while (uVar4 <= uVar2);
  }
  return 0xffffffff;
}

