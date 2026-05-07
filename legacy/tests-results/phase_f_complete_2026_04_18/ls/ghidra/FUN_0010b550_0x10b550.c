
uint FUN_0010b550(long param_1,long param_2,long param_3,long param_4)

{
  byte *pbVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  lVar4 = 0;
  lVar3 = 0;
LAB_0010b56c:
  if (param_2 <= lVar3 && param_4 <= lVar4) {
    return 0;
  }
  if (param_2 <= lVar3) goto LAB_0010b5ec;
LAB_0010b580:
  uVar7 = (uint)*(byte *)(param_1 + lVar3);
  if (*(byte *)(param_1 + lVar3) - 0x30 < 10) goto LAB_0010b5ec;
  do {
    if (uVar7 < 0x5b) {
      if (0x40 < uVar7) goto LAB_0010b6f0;
LAB_0010b5a0:
      uVar6 = uVar7 + 0x100;
      if (lVar4 == param_4) {
        return uVar7 + 0x101;
      }
      bVar2 = *(byte *)(param_3 + lVar4);
      uVar5 = (uint)bVar2;
      if (bVar2 - 0x30 < 10) {
        return uVar6;
      }
      uVar7 = uVar6;
      if (0x5a < bVar2) goto LAB_0010b8a0;
      if (0x40 < bVar2) {
LAB_0010b764:
        return uVar6 - uVar5;
      }
    }
    else {
      if (0x19 < (uVar7 - 0x61 & 0xff)) {
        if (uVar7 == 0x7e) {
          if (lVar4 == param_4) {
            return 0xffffffff;
          }
          bVar2 = *(byte *)(param_3 + lVar4);
          uVar7 = (uint)bVar2;
          if (9 < bVar2 - 0x30) {
            uVar6 = (uint)bVar2;
            if (bVar2 < 0x5b) {
              if (bVar2 < 0x41) {
                uVar7 = bVar2 + 0x100;
              }
            }
            else if (0x19 < (uVar6 - 0x61 & 0xff)) {
              if (uVar6 == 0x7e) goto LAB_0010b5dc;
              uVar7 = uVar6 + 0x100;
            }
            return -uVar7 - 2;
          }
          return 0xfffffffe;
        }
        goto LAB_0010b5a0;
      }
LAB_0010b6f0:
      if (lVar4 == param_4) {
        return uVar7 + 1;
      }
      uVar5 = (uint)*(byte *)(param_3 + lVar4);
      if (uVar5 - 0x30 < 10) {
        return uVar7;
      }
      if (uVar5 < 0x5b) {
        uVar6 = uVar7;
        if (0x40 < uVar5) goto LAB_0010b5d4;
      }
      else {
LAB_0010b8a0:
        uVar6 = uVar7;
        if ((uVar5 - 0x61 & 0xff) < 0x1a) goto LAB_0010b5d4;
        if (uVar5 == 0x7e) {
LAB_0010b898:
          return uVar7 + 2;
        }
      }
    }
    while( true ) {
      while( true ) {
        uVar5 = uVar5 + 0x100;
        uVar6 = uVar7;
LAB_0010b5d4:
        if (uVar6 != uVar5) goto LAB_0010b764;
LAB_0010b5dc:
        lVar3 = lVar3 + 1;
        lVar4 = lVar4 + 1;
        if (lVar3 < param_2) goto LAB_0010b580;
LAB_0010b5ec:
        if ((param_4 <= lVar4) || (uVar5 = (uint)*(byte *)(param_3 + lVar4), uVar5 - 0x30 < 10)) {
          if (lVar3 < param_2) goto LAB_0010b61c;
          if (param_4 <= lVar4) goto LAB_0010b56c;
          goto LAB_0010b640;
        }
        if (lVar3 != param_2) break;
        if (0x5a < uVar5) {
          if (0x19 < (uVar5 - 0x61 & 0xff)) {
            if (uVar5 == 0x7e) {
              uVar7 = 0xffffffff;
              goto LAB_0010b898;
            }
            uVar5 = uVar5 + 0x100;
          }
          return -uVar5 - 1;
        }
        uVar7 = 0xffffffff;
        if (0x40 < uVar5) {
          return -uVar5 - 1;
        }
      }
      uVar7 = (uint)*(byte *)(param_1 + lVar3);
      if (9 < uVar7 - 0x30) break;
      if (0x5a < uVar5) {
        if ((uVar5 - 0x61 & 0xff) < 0x1a) {
LAB_0010b760:
          uVar6 = 0;
          goto LAB_0010b764;
        }
        if (uVar5 == 0x7e) {
          uVar7 = 0;
          goto LAB_0010b898;
        }
        uVar5 = uVar5 + 0x100;
        uVar6 = 0;
        goto LAB_0010b764;
      }
      if (0x40 < uVar5) goto LAB_0010b760;
      uVar7 = 0;
    }
  } while( true );
  while (lVar3 = lVar3 + 1, param_2 != lVar3) {
LAB_0010b61c:
    if (*(char *)(param_1 + lVar3) != '0') break;
  }
  if (lVar4 < param_4) {
LAB_0010b640:
    do {
      if (*(char *)(param_3 + lVar4) != '0') {
        uVar7 = 0;
        if (param_4 <= lVar4 || param_2 <= lVar3) goto LAB_0010b6a0;
        goto LAB_0010b65c;
      }
      lVar4 = lVar4 + 1;
    } while (param_4 != lVar4);
    uVar7 = 0;
    goto LAB_0010b6a0;
  }
  uVar7 = 0;
  if (param_2 <= lVar3) goto LAB_0010b56c;
  goto LAB_0010b6a8;
  while( true ) {
    if (9 < *(byte *)(param_3 + lVar4) - 0x30) {
      if (lVar3 < param_2) {
        return 1;
      }
      goto LAB_0010b6b8;
    }
    lVar3 = lVar3 + 1;
    uVar6 = (uint)*pbVar1 - (uint)*(byte *)(param_3 + lVar4);
    if (uVar7 != 0) {
      uVar6 = uVar7;
    }
    lVar4 = lVar4 + 1;
    uVar7 = uVar6;
    if (param_2 <= lVar3 || param_4 <= lVar4) break;
LAB_0010b65c:
    pbVar1 = (byte *)(param_1 + lVar3);
    if (9 < *pbVar1 - 0x30) break;
  }
LAB_0010b6a0:
  if (param_2 <= lVar3) goto LAB_0010b6b8;
LAB_0010b6a8:
  if (*(byte *)(param_1 + lVar3) - 0x30 < 10) {
    return 1;
  }
LAB_0010b6b8:
  if ((lVar4 < param_4) && (*(byte *)(param_3 + lVar4) - 0x30 < 10)) {
    return 0xffffffff;
  }
  if (uVar7 != 0) {
    return uVar7;
  }
  goto LAB_0010b56c;
}

