
byte FUN_00190164(byte *param_1)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  long lVar5;
  
  bVar2 = *param_1;
  lVar4 = *(long *)(param_1 + 8);
  if (bVar2 != 0) {
    lVar5 = lVar4;
    do {
      lVar1 = lVar5 + 8;
      bVar3 = FUN_001902e0(lVar5);
      if ((bVar3 & 1) != 0) {
        return bVar3;
      }
      lVar5 = lVar1;
    } while (lVar1 != lVar4 + 8 + (ulong)(bVar2 - 1) * 8);
  }
  return 0;
}

