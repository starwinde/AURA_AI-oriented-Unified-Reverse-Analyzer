
long FUN_00102e84(void)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  int *piVar4;
  undefined8 uVar5;
  long lVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined1 auVar13 [16];
  
  piVar4 = __errno_location();
  puVar3 = PTR_stdout_0011ffd0;
  iVar2 = *piVar4;
  fflush_unlocked(*(FILE **)PTR_stdout_0011ffd0);
  __fpurge(*(undefined8 *)puVar3);
  clearerr_unlocked(*(FILE **)puVar3);
  uVar5 = dcgettext(0,"write error",5);
  auVar13 = error(1,iVar2,uVar5);
  lVar6 = dcgettext(0,auVar13._0_8_,5);
  if (auVar13._0_8_ == lVar6) {
    pbVar7 = (byte *)nl_langinfo(0xe);
    if (pbVar7 == (byte *)0x0) {
      pbVar7 = &UNK_001051d8;
    }
    else if (*pbVar7 == 0) {
      pbVar7 = &UNK_001051d8;
    }
    else if (pbVar7 == &DAT_001051e0) {
      return auVar13._8_8_;
    }
    pbVar8 = &DAT_001051e0;
    do {
      uVar10 = (uint)*pbVar7;
      uVar11 = (uint)*pbVar8;
      uVar12 = (uint)*pbVar8;
      if (uVar10 - 0x41 < 0x1a) {
        uVar10 = uVar10 + 0x20;
        uVar1 = uVar12 + 0x20;
        uVar9 = uVar10 & 0xff;
        if (uVar12 - 0x41 < 0x1a) {
          uVar12 = uVar1 & 0xff;
          uVar11 = uVar1;
        }
      }
      else {
        if (uVar12 - 0x41 < 0x1a) {
          uVar11 = uVar12 + 0x20;
        }
        uVar12 = uVar11 & 0xff;
        uVar9 = uVar10;
        if (uVar10 == 0) break;
      }
      pbVar7 = pbVar7 + 1;
      pbVar8 = pbVar8 + 1;
    } while (uVar9 == uVar12);
    if (uVar10 == uVar11) {
      lVar6 = auVar13._8_8_;
    }
  }
  return lVar6;
}

