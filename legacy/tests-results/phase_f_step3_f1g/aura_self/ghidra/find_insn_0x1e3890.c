
uint find_insn(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0x3b22;
  if (param_1 - 0x92 < 0x3b23) {
    uVar2 = 0x3b22;
    uVar1 = 0x1e23;
    uVar4 = 0;
    while( true ) {
      uVar2 = uVar2 >> 1;
      if (param_1 == uVar1) break;
      if (param_1 < uVar1) {
        uVar3 = uVar2 - 1;
        if (uVar3 < uVar4) goto LAB_001e38f8;
      }
      else {
        uVar4 = uVar2 + 1;
        if (uVar3 < uVar4) goto LAB_001e38f8;
      }
      uVar2 = uVar3 + uVar4;
      uVar1 = (uint)*(ushort *)(insns + (ulong)(uVar2 >> 1) * 0x50);
    }
  }
  else {
LAB_001e38f8:
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

