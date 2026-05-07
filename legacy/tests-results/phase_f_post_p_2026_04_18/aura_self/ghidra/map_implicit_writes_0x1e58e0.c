
ulong map_implicit_writes(ulong param_1,long param_2)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  short sVar4;
  long lVar5;
  
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (lVar5 != 0) {
    param_1 = MCInst_getOpcode();
    param_2 = param_2 + (param_1 & 0xffffffff) * 0x5e;
    sVar4 = *(short *)(param_2 + 0x2c);
    if (sVar4 != 0) {
      uVar3 = (ulong)*(byte *)(lVar5 + 0x52);
      param_1 = 0;
      lVar1 = uVar3 * 2;
      do {
        uVar2 = (uint)uVar3 + 1;
        if (0x13 < (uint)uVar3) {
          uVar2 = puts("ERROR: Too many implicit write register defined in instruction mapping.");
          return (ulong)uVar2;
        }
        uVar3 = (ulong)(uVar2 & 0xff);
        *(char *)(lVar5 + 0x52) = (char)uVar2;
        *(short *)(lVar5 + lVar1 + 0x2a + param_1) = sVar4;
        param_1 = param_1 + 2;
        sVar4 = *(short *)(param_2 + 0x2c + param_1);
      } while (sVar4 != 0);
    }
  }
  return param_1;
}

