
bool FUN_0010aca0(ulong param_1)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  byte *pbVar4;
  
  lVar3 = (&DAT_001400f0)[(param_1 & 0xffffffff) * 2];
  bVar1 = false;
  if (lVar3 != 0) {
    pbVar4 = (&PTR_DAT_001400f8)[(param_1 & 0xffffffff) * 2];
    if (lVar3 == 1) {
      return *pbVar4 != 0x30;
    }
    bVar1 = true;
    if (lVar3 == 2) {
      iVar2 = *pbVar4 - 0x30;
      if (iVar2 == 0) {
        iVar2 = pbVar4[1] - 0x30;
      }
      bVar1 = iVar2 != 0;
    }
  }
  return bVar1;
}

