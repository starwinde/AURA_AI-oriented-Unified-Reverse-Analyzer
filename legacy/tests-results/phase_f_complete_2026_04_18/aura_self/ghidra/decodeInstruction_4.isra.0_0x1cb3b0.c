
undefined8 decodeInstruction_4_isra_0(byte *param_1,undefined8 param_2,uint param_3)

{
  uint uVar1;
  byte bVar2;
  ulong uVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 uVar7;
  ulong uVar8;
  long lVar9;
  byte *pbVar10;
  byte *pbVar11;
  int iVar13;
  byte *pbVar14;
  long lVar15;
  uint uVar16;
  undefined4 uVar17;
  byte *pbVar12;
  
  uVar16 = 0;
  uVar17 = 3;
LAB_001cb3d4:
  do {
    while( true ) {
      bVar2 = *param_1;
      bVar4 = bVar2 == 4;
      pbVar10 = param_1;
      if (!bVar4) break;
LAB_001cb430:
      pbVar10 = param_1 + 1;
      do {
        pbVar14 = pbVar10;
        pbVar10 = pbVar14 + 1;
      } while ((char)*pbVar14 < '\0');
      param_1 = param_1 + 1 + (ulong)(uint)((int)pbVar14 - (int)param_1) + 3;
    }
LAB_001cb3e0:
    iVar13 = (int)pbVar10;
    if (bVar2 < 4 || bVar4) {
      if (bVar2 == 2) {
        pbVar10 = pbVar10 + 1;
        uVar8 = 0;
        lVar15 = 0;
        pbVar14 = pbVar10;
        do {
          pbVar12 = pbVar14;
          uVar5 = uVar8 & 0x3f;
          uVar8 = (ulong)((int)uVar8 + 7);
          lVar15 = lVar15 + (((ulong)*pbVar12 & 0x7f) << uVar5);
          pbVar14 = pbVar12 + 1;
        } while ((char)*pbVar12 < '\0');
        uVar8 = (ulong)(uint)((int)pbVar12 - iVar13);
        param_1 = pbVar10 + uVar8 + 3;
        if (uVar16 != (uint)lVar15) {
          param_1 = param_1 + ((uint)pbVar10[uVar8 + 2] << 0x10 | (uint)pbVar10[uVar8 + 1] << 8 |
                              (uint)pbVar10[uVar8]);
        }
      }
      else {
        if (bVar2 != 3) {
          if (bVar2 != 1) {
            return 0;
          }
          param_1 = pbVar10 + 3;
          uVar16 = (1 << (ulong)(pbVar10[2] & 0x1f)) + -1 << (ulong)(pbVar10[1] & 0x1f) & param_3;
          if (pbVar10[2] == 0x20) {
            uVar16 = param_3;
          }
          uVar16 = uVar16 >> (ulong)(pbVar10[1] & 0x1f);
          bVar2 = *param_1;
          bVar4 = false;
          pbVar10 = param_1;
          if (bVar2 == 4) goto LAB_001cb430;
          goto LAB_001cb3e0;
        }
        pbVar14 = pbVar10 + 3;
        uVar8 = 0;
        lVar15 = 0;
        uVar1 = (1 << (ulong)(pbVar10[2] & 0x1f)) + -1 << (ulong)(pbVar10[1] & 0x1f) & param_3;
        if (pbVar10[2] == 0x20) {
          uVar1 = param_3;
        }
        pbVar12 = pbVar14;
        do {
          pbVar11 = pbVar12 + 1;
          bVar2 = *pbVar12;
          uVar5 = uVar8 & 0x3f;
          uVar8 = (ulong)((int)uVar8 + 7);
          lVar15 = lVar15 + (((ulong)bVar2 & 0x7f) << uVar5);
          pbVar12 = pbVar11;
        } while ((char)bVar2 < '\0');
        uVar8 = (ulong)(uint)((int)pbVar11 - (int)pbVar14);
        param_1 = pbVar14 + uVar8 + 3;
        if (uVar1 >> (ulong)(pbVar10[1] & 0x1f) != (uint)lVar15) {
          param_1 = param_1 + ((uint)pbVar14[uVar8 + 2] << 0x10 | (uint)pbVar14[uVar8 + 1] << 8 |
                              (uint)pbVar14[uVar8]);
        }
      }
      goto LAB_001cb3d4;
    }
    if (bVar2 == 6) {
      uVar8 = 0;
      lVar15 = 0;
      pbVar14 = pbVar10 + 1;
      do {
        pbVar12 = pbVar14;
        uVar5 = uVar8 & 0x3f;
        uVar8 = (ulong)((int)uVar8 + 7);
        lVar15 = lVar15 + (((ulong)*pbVar12 & 0x7f) << uVar5);
        pbVar14 = pbVar12 + 1;
      } while ((char)*pbVar12 < '\0');
      uVar5 = 0;
      uVar8 = 0;
      pbVar10 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar13);
      do {
        bVar2 = *pbVar10;
        uVar6 = uVar5 & 0x3f;
        uVar5 = (ulong)((int)uVar5 + 7);
        uVar8 = uVar8 + (((ulong)bVar2 & 0x7f) << uVar6);
        pbVar10 = pbVar10 + 1;
      } while ((char)bVar2 < '\0');
      MCInst_setOpcode(param_2,lVar15);
      uVar7 = decodeToMCInst_4_constprop_0_isra_0(uVar17,uVar8 & 0xffffffff,param_3,param_2);
      return uVar7;
    }
    if (bVar2 != 7) {
      if (bVar2 != 5) {
        return 0;
      }
      uVar5 = 0;
      uVar8 = 0;
      pbVar14 = pbVar10 + 1;
      do {
        pbVar12 = pbVar14;
        uVar6 = uVar5 & 0x3f;
        uVar5 = (ulong)((int)uVar5 + 7);
        uVar8 = uVar8 + (((ulong)*pbVar12 & 0x7f) << uVar6);
        pbVar14 = pbVar12 + 1;
      } while ((char)*pbVar12 < '\0');
      uVar6 = 0;
      uVar5 = 0;
      pbVar10 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar13);
      do {
        bVar2 = *pbVar10;
        uVar3 = uVar6 & 0x3f;
        uVar6 = (ulong)((int)uVar6 + 7);
        uVar5 = uVar5 + (((ulong)bVar2 & 0x7f) << uVar3);
        pbVar10 = pbVar10 + 1;
      } while ((char)bVar2 < '\0');
      MCInst_clear(param_2);
      MCInst_setOpcode(param_2,uVar8 & 0xffffffff);
      uVar7 = decodeToMCInst_4_constprop_0_isra_0(uVar17,uVar5 & 0xffffffff,param_3,param_2);
      return uVar7;
    }
    uVar8 = 0;
    lVar15 = 0;
    pbVar14 = pbVar10 + 1;
    do {
      pbVar12 = pbVar14;
      uVar5 = uVar8 & 0x3f;
      uVar8 = (ulong)((int)uVar8 + 7);
      lVar15 = lVar15 + (((ulong)*pbVar12 & 0x7f) << uVar5);
      pbVar14 = pbVar12 + 1;
    } while ((char)*pbVar12 < '\0');
    uVar8 = 0;
    param_1 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar13);
    lVar9 = 0;
    pbVar10 = param_1;
    do {
      pbVar14 = pbVar10 + 1;
      bVar2 = *pbVar10;
      uVar5 = uVar8 & 0x3f;
      uVar8 = (ulong)((int)uVar8 + 7);
      lVar9 = lVar9 + (((ulong)bVar2 & 0x7f) << uVar5);
      pbVar10 = pbVar14;
    } while ((char)bVar2 < '\0');
    param_1 = param_1 + (uint)((int)pbVar14 - (int)param_1);
    if ((((uint)lVar15 ^ (uint)lVar9) & param_3) != (uint)lVar9) {
      uVar17 = 1;
    }
  } while( true );
}

