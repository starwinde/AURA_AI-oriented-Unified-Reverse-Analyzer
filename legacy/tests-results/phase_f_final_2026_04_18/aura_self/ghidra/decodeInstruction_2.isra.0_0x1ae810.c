
undefined8 decodeInstruction_2_isra_0(byte *param_1,long param_2,uint param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  ulong uVar4;
  bool bVar5;
  long lVar6;
  ulong uVar7;
  undefined8 uVar8;
  ulong uVar9;
  byte *pbVar10;
  byte *pbVar11;
  long lVar13;
  int iVar14;
  byte *pbVar15;
  ulong uVar16;
  byte *extraout_x8;
  undefined4 uVar17;
  byte *pbVar12;
  
  uVar16 = 0;
  uVar17 = 3;
  param_3 = param_3 & 0xffff;
  do {
    while( true ) {
      bVar2 = *param_1;
      bVar5 = bVar2 == 4;
      pbVar10 = param_1;
      if (!bVar5) break;
LAB_001ae890:
      uVar9 = 0;
      lVar6 = 0;
      pbVar10 = param_1 + 1;
      do {
        pbVar15 = pbVar10;
        uVar7 = uVar9 & 0x3f;
        uVar9 = (ulong)((int)uVar9 + 7);
        lVar6 = lVar6 + (((ulong)*pbVar15 & 0x7f) << uVar7);
        pbVar10 = pbVar15 + 1;
      } while ((char)*pbVar15 < '\0');
      uVar9 = (ulong)(uint)((int)pbVar15 - (int)param_1);
      pbVar10 = param_1 + 1 + uVar9;
      param_1 = pbVar10 + 3;
      uVar7 = checkDecoderPredicate_isra_0(lVar6,*(undefined8 *)(param_2 + 800));
      if ((uVar7 & 1) == 0) {
        bVar2 = pbVar10[2];
        bVar3 = pbVar10[1];
        pbVar10 = extraout_x8;
LAB_001aeb6c:
        param_1 = param_1 + ((uint)bVar2 << 0x10 | (uint)bVar3 << 8 | (uint)pbVar10[uVar9]);
      }
    }
LAB_001ae840:
    iVar14 = (int)pbVar10;
    if (bVar2 < 4 || bVar5) {
      if (bVar2 == 2) {
        pbVar10 = pbVar10 + 1;
        uVar9 = 0;
        lVar6 = 0;
        pbVar15 = pbVar10;
        do {
          pbVar12 = pbVar15;
          uVar7 = uVar9 & 0x3f;
          uVar9 = (ulong)((int)uVar9 + 7);
          lVar6 = lVar6 + (((ulong)*pbVar12 & 0x7f) << uVar7);
          pbVar15 = pbVar12 + 1;
        } while ((char)*pbVar12 < '\0');
        uVar9 = (ulong)(uint)((int)pbVar12 - iVar14);
        param_1 = pbVar10 + uVar9 + 3;
        if ((uint)uVar16 != ((uint)lVar6 & 0xffff)) {
          bVar2 = pbVar10[uVar9 + 2];
          bVar3 = pbVar10[uVar9 + 1];
          goto LAB_001aeb6c;
        }
      }
      else {
        if (bVar2 != 3) break;
        pbVar15 = pbVar10 + 3;
        uVar9 = 0;
        lVar6 = 0;
        uVar1 = param_3 & (1 << (ulong)(pbVar10[2] & 0x1f)) + -1 << (ulong)(pbVar10[1] & 0x1f);
        if (pbVar10[2] == 0x10) {
          uVar1 = param_3;
        }
        pbVar12 = pbVar15;
        do {
          pbVar11 = pbVar12 + 1;
          bVar2 = *pbVar12;
          uVar7 = uVar9 & 0x3f;
          uVar9 = (ulong)((int)uVar9 + 7);
          lVar6 = lVar6 + (((ulong)bVar2 & 0x7f) << uVar7);
          pbVar12 = pbVar11;
        } while ((char)bVar2 < '\0');
        uVar9 = (ulong)(uint)((int)pbVar11 - (int)pbVar15);
        param_1 = pbVar15 + uVar9 + 3;
        if ((int)uVar1 >> (pbVar10[1] & 0x1f) != (int)lVar6) {
          param_1 = param_1 + ((uint)pbVar15[uVar9 + 2] << 0x10 | (uint)pbVar15[uVar9 + 1] << 8 |
                              (uint)pbVar15[uVar9]);
        }
      }
    }
    else {
      if (bVar2 == 6) {
        uVar16 = 0;
        lVar6 = 0;
        pbVar15 = pbVar10 + 1;
        do {
          pbVar12 = pbVar15;
          uVar9 = uVar16 & 0x3f;
          uVar16 = (ulong)((int)uVar16 + 7);
          lVar6 = lVar6 + (((ulong)*pbVar12 & 0x7f) << uVar9);
          pbVar15 = pbVar12 + 1;
        } while ((char)*pbVar12 < '\0');
        uVar9 = 0;
        uVar16 = 0;
        pbVar10 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar14);
        do {
          bVar2 = *pbVar10;
          uVar7 = uVar9 & 0x3f;
          uVar9 = (ulong)((int)uVar9 + 7);
          uVar16 = uVar16 + (((ulong)bVar2 & 0x7f) << uVar7);
          pbVar10 = pbVar10 + 1;
        } while ((char)bVar2 < '\0');
        MCInst_setOpcode(param_2,lVar6);
        uVar8 = decodeToMCInst_2_isra_0(uVar17,uVar16 & 0xffffffff,param_3,param_2);
        return uVar8;
      }
      if (bVar2 != 7) {
        if (bVar2 != 5) {
          return 0;
        }
        uVar9 = 0;
        uVar16 = 0;
        pbVar15 = pbVar10 + 1;
        do {
          pbVar12 = pbVar15;
          uVar7 = uVar9 & 0x3f;
          uVar9 = (ulong)((int)uVar9 + 7);
          uVar16 = uVar16 + (((ulong)*pbVar12 & 0x7f) << uVar7);
          pbVar15 = pbVar12 + 1;
        } while ((char)*pbVar12 < '\0');
        uVar7 = 0;
        uVar9 = 0;
        pbVar10 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar14);
        do {
          bVar2 = *pbVar10;
          uVar4 = uVar7 & 0x3f;
          uVar7 = (ulong)((int)uVar7 + 7);
          uVar9 = uVar9 + (((ulong)bVar2 & 0x7f) << uVar4);
          pbVar10 = pbVar10 + 1;
        } while ((char)bVar2 < '\0');
        MCInst_clear(param_2);
        MCInst_setOpcode(param_2,uVar16 & 0xffffffff);
        uVar8 = decodeToMCInst_2_isra_0(uVar17,uVar9 & 0xffffffff,param_3,param_2);
        return uVar8;
      }
      uVar9 = 0;
      lVar6 = 0;
      pbVar15 = pbVar10 + 1;
      do {
        pbVar12 = pbVar15;
        uVar7 = uVar9 & 0x3f;
        uVar9 = (ulong)((int)uVar9 + 7);
        lVar6 = lVar6 + (((ulong)*pbVar12 & 0x7f) << uVar7);
        pbVar15 = pbVar12 + 1;
      } while ((char)*pbVar12 < '\0');
      param_1 = pbVar10 + 1 + (uint)((int)pbVar12 - iVar14);
      uVar9 = 0;
      lVar13 = 0;
      pbVar10 = param_1;
      do {
        pbVar15 = pbVar10 + 1;
        bVar2 = *pbVar10;
        uVar7 = uVar9 & 0x3f;
        uVar9 = (ulong)((int)uVar9 + 7);
        lVar13 = lVar13 + (((ulong)bVar2 & 0x7f) << uVar7);
        pbVar10 = pbVar15;
      } while ((char)bVar2 < '\0');
      param_1 = param_1 + (uint)((int)pbVar15 - (int)param_1);
      if ((param_3 & (uint)lVar6 & 0xffff) == 0) {
        if (((uint)lVar13 & 0xffff & (param_3 ^ 0xffffffff)) != 0) {
          uVar17 = 1;
        }
      }
      else {
        uVar17 = 1;
      }
    }
  } while( true );
  if (bVar2 != 1) {
    return 0;
  }
  param_1 = pbVar10 + 3;
  uVar1 = param_3 & (1 << (ulong)(pbVar10[2] & 0x1f)) + -1 << (ulong)(pbVar10[1] & 0x1f);
  if (pbVar10[2] == 0x10) {
    uVar1 = param_3;
  }
  uVar16 = (ulong)(uint)((int)uVar1 >> (pbVar10[1] & 0x1f));
  bVar2 = *param_1;
  bVar5 = false;
  pbVar10 = param_1;
  if (bVar2 == 4) goto LAB_001ae890;
  goto LAB_001ae840;
}

