
void FUN_001957c0(undefined8 param_1,ulong param_2)

{
  byte bVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  uint uVar6;
  short *psVar7;
  short *psVar8;
  
  uVar3 = FUN_0018ffb0();
  psVar7 = (short *)(&PTR_DAT_005e0b78)[(uVar3 & 0xffffffff) * 2];
  uVar3 = FUN_0018ffb0(param_1);
  bVar1 = (&DAT_005e0b70)[(uVar3 & 0xffffffff) * 0x10];
  if (bVar1 == 0) {
LAB_00195884:
    uVar6 = 0;
  }
  else {
    uVar6 = 0;
    psVar8 = psVar7;
    do {
      uVar2 = FUN_0018ffe0(param_1);
      if (uVar2 == uVar6) break;
      uVar3 = FUN_001902f0(psVar8);
      if (((uVar3 & 1) != 0) && (*psVar8 == 0xe)) {
        if (uVar6 == 0) goto LAB_00195884;
        uVar3 = FUN_001902e0(psVar7 + (ulong)(uVar6 - 1) * 4);
        if ((uVar3 & 1) == 0) break;
      }
      uVar6 = uVar6 + 1;
      psVar8 = psVar8 + 4;
    } while (uVar6 != bVar1);
  }
  uVar5 = 3;
  if ((param_2 & 1) != 0) {
    uVar5 = 0;
  }
  uVar4 = FUN_001900e0(param_1,uVar5);
  FUN_0018ff10(param_1,uVar6,uVar4);
  return;
}

