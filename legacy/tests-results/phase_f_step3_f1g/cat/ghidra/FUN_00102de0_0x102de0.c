
void FUN_00102de0(void)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined *puVar3;
  
  puVar3 = PTR_DAT_001200a0;
  pbVar2 = &DAT_00120021;
  do {
    if (*pbVar2 < 0x39) {
      *pbVar2 = *pbVar2 + 1;
      return;
    }
    pbVar1 = pbVar2 + -1;
    *pbVar2 = 0x30;
    pbVar2 = pbVar1;
  } while (puVar3 <= pbVar1);
  if (puVar3 < (undefined *)0x120011) {
    DAT_00120010 = 0x3e;
  }
  else {
    PTR_DAT_001200a0 = puVar3 + -1;
    puVar3[-1] = 0x31;
    puVar3 = puVar3 + -1;
  }
  if (DAT_001200a8 <= puVar3) {
    return;
  }
  DAT_001200a8 = DAT_001200a8 + -1;
  return;
}

