
ulong FUN_001e6dc4(ulong param_1,long param_2)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  short sVar4;
  long lVar5;
  
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (lVar5 != 0) {
    param_1 = FUN_0018ffb0();
    param_2 = param_2 + (param_1 & 0xffffffff) * 0x5e;
    sVar4 = *(short *)(param_2 + 4);
    if (sVar4 != 0) {
      bVar1 = *(byte *)(lVar5 + 0x28);
      param_1 = 0;
      bVar3 = bVar1;
      do {
        if (0x13 < bVar3) {
          uVar2 = puts("ERROR: Too many implicit read register defined in instruction mapping.");
          return (ulong)uVar2;
        }
        *(byte *)(lVar5 + 0x28) = bVar3 + 1;
        *(short *)(lVar5 + (ulong)bVar1 * 2 + param_1) = sVar4;
        param_1 = param_1 + 2;
        sVar4 = *(short *)(param_2 + 4 + param_1);
        bVar3 = bVar3 + 1;
      } while (sVar4 != 0);
    }
  }
  return param_1;
}

