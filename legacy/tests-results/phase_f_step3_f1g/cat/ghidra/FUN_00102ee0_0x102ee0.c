
long FUN_00102ee0(long param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  lVar2 = dcgettext(0,param_1,5);
  if (param_1 == lVar2) {
    pbVar3 = (byte *)nl_langinfo(0xe);
    if (pbVar3 == (byte *)0x0) {
      pbVar3 = &UNK_001051d8;
    }
    else if (*pbVar3 == 0) {
      pbVar3 = &UNK_001051d8;
    }
    else if (pbVar3 == &DAT_001051e0) {
      return param_2;
    }
    pbVar4 = &DAT_001051e0;
    do {
      uVar6 = (uint)*pbVar3;
      uVar7 = (uint)*pbVar4;
      uVar8 = (uint)*pbVar4;
      if (uVar6 - 0x41 < 0x1a) {
        uVar6 = uVar6 + 0x20;
        uVar1 = uVar8 + 0x20;
        uVar5 = uVar6 & 0xff;
        if (uVar8 - 0x41 < 0x1a) {
          uVar8 = uVar1 & 0xff;
          uVar7 = uVar1;
        }
      }
      else {
        if (uVar8 - 0x41 < 0x1a) {
          uVar7 = uVar8 + 0x20;
        }
        uVar8 = uVar7 & 0xff;
        uVar5 = uVar6;
        if (uVar6 == 0) break;
      }
      pbVar3 = pbVar3 + 1;
      pbVar4 = pbVar4 + 1;
    } while (uVar5 == uVar8);
    if (uVar6 == uVar7) {
      lVar2 = param_2;
    }
  }
  return lVar2;
}

