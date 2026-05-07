
undefined4 FUN_001175d0(undefined1 param_1 [16],undefined1 param_2 [16])

{
  undefined4 uVar1;
  undefined8 uVar2;
  ulong uVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  
  uVar12 = param_2._8_8_;
  uVar11 = param_2._0_8_;
  uVar10 = param_1._8_8_;
  uVar9 = param_1._0_8_;
  uVar2 = fpcr;
  uVar7 = uVar10 >> 0x30 & 0x7fff;
  uVar3 = uVar10 & 0xffffffffffff;
  lVar6 = -((long)uVar10 >> 0x3f);
  uVar10 = uVar12 & 0xffffffffffff;
  uVar8 = uVar12 >> 0x30 & 0x7fff;
  lVar5 = -((long)uVar12 >> 0x3f);
  if (uVar7 == 0x7fff) {
    if (uVar3 != 0 || uVar9 != 0) {
code_r0x001176f4:
      FUN_001180e0(1);
      return 2;
    }
    if (uVar8 != 0x7fff) goto LAB_00117658;
    if (uVar10 != 0 || uVar11 != 0) goto code_r0x001176f4;
    if (lVar6 != lVar5) goto LAB_00117658;
    bVar4 = true;
  }
  else {
    if (uVar8 == 0x7fff) {
      if (uVar10 != 0 || uVar11 != 0) goto code_r0x001176f4;
      if ((uVar7 == 0) && (uVar3 == 0 && uVar9 == 0)) goto LAB_0011762c;
LAB_00117650:
      if (lVar6 != lVar5) goto LAB_00117658;
      goto LAB_001176d8;
    }
    if (uVar7 == 0) {
      if (uVar8 != 0) {
        if (uVar3 == 0 && uVar9 == 0) {
LAB_0011762c:
          uVar1 = 1;
          if (lVar5 == 0) {
            uVar1 = 0xffffffff;
          }
          return uVar1;
        }
        goto LAB_00117650;
      }
      if (uVar10 == 0 && uVar11 == 0) {
        if (uVar3 == 0 && uVar9 == 0) {
          return 0;
        }
        goto LAB_00117658;
      }
      if (uVar3 == 0 && uVar9 == 0) goto LAB_0011762c;
      if (lVar6 != lVar5) goto LAB_00117658;
    }
    else {
      if (((uVar8 == 0) || (lVar6 != lVar5)) || (uVar8 < uVar7)) goto LAB_00117658;
      if (uVar7 < uVar8) goto LAB_001176d8;
    }
    bVar4 = uVar3 == uVar10;
    if ((uVar10 <= uVar3 && !bVar4) || ((bVar4 && uVar11 <= uVar9) && (!bVar4 || uVar9 != uVar11)))
    {
LAB_00117658:
      uVar1 = 0xffffffff;
      if (lVar6 == 0) {
        uVar1 = 1;
      }
      return uVar1;
    }
  }
  if ((uVar10 <= uVar3) && (!bVar4 || uVar11 <= uVar9)) {
    return 0;
  }
LAB_001176d8:
  uVar1 = 1;
  if (lVar6 == 0) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

