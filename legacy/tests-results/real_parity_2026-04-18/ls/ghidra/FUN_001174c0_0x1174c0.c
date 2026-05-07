
bool FUN_001174c0(undefined1 param_1 [16],undefined1 param_2 [16])

{
  undefined8 uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  int iVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  
  lVar9 = param_2._0_8_;
  lVar8 = param_1._0_8_;
  uVar1 = fpcr;
  uVar7 = param_1._8_8_ >> 0x30 & 0x7fff;
  uVar2 = param_1._8_8_ & 0xffffffffffff;
  uVar3 = param_2._8_8_ & 0xffffffffffff;
  uVar4 = param_2._8_8_ >> 0x30 & 0x7fff;
  iVar5 = -(param_2._12_4_ >> 0x1f);
  iVar6 = -(param_1._12_4_ >> 0x1f);
  if (uVar7 == 0x7fff) {
    if (uVar2 == 0 && lVar8 == 0) {
      if (uVar4 != 0x7fff) {
        return true;
      }
      if (uVar3 == 0 && lVar9 == 0) {
        return iVar6 != iVar5;
      }
    }
    else {
      if (uVar2 < 0x800000000000) goto code_r0x00117560;
      if (uVar4 != 0x7fff) {
        return true;
      }
    }
  }
  else {
    if (uVar4 != 0x7fff) {
      if (uVar7 != uVar4) {
        return true;
      }
      if (uVar2 != uVar3 || lVar8 != lVar9) {
        return true;
      }
      if (iVar6 == iVar5) {
        return false;
      }
      if (uVar7 != 0) {
        return true;
      }
      return uVar2 != 0 || lVar8 != 0;
    }
    if (uVar3 == 0 && lVar9 == 0) {
      return true;
    }
  }
  if (uVar3 == 0 && lVar9 == 0 || 0x7fffffffffff < uVar3) {
    return true;
  }
code_r0x00117560:
  FUN_001180e0(1);
  return true;
}

