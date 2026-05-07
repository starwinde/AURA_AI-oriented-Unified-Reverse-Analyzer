
ulong FUN_0010e040(uint param_1)

{
  ulong uVar1;
  bool bVar2;
  byte *pbVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  byte *pbVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  
  uVar1 = DAT_001412a8;
  uVar12 = DAT_001412a0;
  uVar11 = DAT_00140ee0;
  pbVar3 = DAT_001412b0;
  if (DAT_001412a0 == 0) {
    if (DAT_00140ee0 <= DAT_001412a8) {
LAB_0010e260:
      if (DAT_00140ee0 == 0) {
        return 0;
      }
      goto LAB_0010e158;
    }
LAB_0010e0b8:
    uVar12 = DAT_00140ee0 << 1;
    pbVar3 = (byte *)reallocarray(DAT_001412b0,DAT_00140ee0,0x30);
  }
  else {
    if (DAT_001412a0 < DAT_00140ee0) {
      uVar11 = DAT_001412a0;
      if (DAT_001412a0 <= DAT_001412a8) goto LAB_0010e158;
    }
    else {
      if (DAT_00140ee0 <= DAT_001412a8) goto LAB_0010e260;
      if (DAT_00140ee0 < DAT_001412a0 >> 1) goto LAB_0010e0b8;
    }
    pbVar3 = (byte *)reallocarray(DAT_001412b0,DAT_001412a0,0x18);
  }
  if (pbVar3 != (byte *)0x0) {
    uVar6 = uVar1 + 1;
    uVar4 = uVar12 - uVar1;
    uVar7 = uVar4 * (uVar12 + uVar6);
    DAT_001412b0 = pbVar3;
    if (!CARRY8(uVar12,uVar6)) {
      uVar10 = 0;
      if (uVar4 != 0) {
        uVar10 = uVar7 / uVar4;
      }
      if ((uVar12 + uVar6 == uVar10) && (lVar5 = reallocarray(0,uVar7 >> 1,8), lVar5 != 0)) {
        DAT_001412a8 = uVar12;
        if (uVar1 < uVar12) {
          lVar8 = uVar6 * 8;
          pbVar9 = pbVar3 + uVar1 * 0x18;
          do {
            *(long *)(pbVar9 + 0x10) = lVar5;
            lVar5 = lVar5 + lVar8;
            lVar8 = lVar8 + 8;
            pbVar9 = pbVar9 + 0x18;
          } while ((uVar12 + 1) * 8 - lVar8 != 0);
        }
LAB_0010e158:
        lVar5 = 3;
        uVar12 = 0;
        do {
          lVar8 = *(long *)(pbVar3 + 0x10);
          uVar1 = uVar12 + 1;
          uVar6 = 0;
          *pbVar3 = 1;
          *(long *)(pbVar3 + 8) = lVar5;
          do {
            *(undefined8 *)(lVar8 + uVar6 * 8) = 3;
            bVar2 = uVar12 != uVar6;
            uVar6 = uVar6 + 1;
          } while (bVar2);
          pbVar3 = pbVar3 + 0x18;
          lVar5 = lVar5 + 3;
          uVar12 = uVar1;
        } while (uVar1 != uVar11);
        if (DAT_00140ee0 != 0) {
          uVar12 = 0;
          do {
            lVar5 = FUN_0010c730(*(undefined8 *)(DAT_00140ee8 + uVar12 * 8));
            uVar1 = DAT_00141020;
            uVar6 = 0;
            pbVar3 = DAT_001412b0;
            do {
              uVar4 = uVar6 + 1;
              if ((*pbVar3 & 1) != 0) {
                if ((param_1 & 1) == 0) {
                  uVar7 = 0;
                  if (uVar4 != 0) {
                    uVar7 = uVar12 / uVar4;
                  }
                  uVar10 = uVar12 - uVar7 * uVar4;
                }
                else {
                  uVar7 = 0;
                  if (uVar4 != 0) {
                    uVar7 = (uVar6 + DAT_00140ee0) / uVar4;
                  }
                  uVar10 = 0;
                  if (uVar7 != 0) {
                    uVar10 = uVar12 / uVar7;
                  }
                }
                uVar7 = *(ulong *)(*(long *)(pbVar3 + 0x10) + uVar10 * 8);
                uVar6 = lVar5 + (ulong)(uVar10 != uVar6) * 2;
                if (uVar7 < uVar6) {
                  *(ulong *)(pbVar3 + 8) = *(long *)(pbVar3 + 8) + (uVar6 - uVar7);
                  *(ulong *)(*(long *)(pbVar3 + 0x10) + uVar10 * 8) = uVar6;
                  *pbVar3 = *(ulong *)(pbVar3 + 8) < uVar1;
                }
              }
              pbVar3 = pbVar3 + 0x18;
              uVar6 = uVar4;
            } while (uVar11 != uVar4);
            uVar12 = uVar12 + 1;
          } while (uVar12 < DAT_00140ee0);
        }
        if (uVar11 != 1) {
          pbVar3 = DAT_001412b0 + uVar11 * 0x18;
          do {
            if ((pbVar3[-0x18] & 1) != 0) {
              return uVar11;
            }
            uVar11 = uVar11 - 1;
            pbVar3 = pbVar3 + -0x18;
          } while (uVar11 != 1);
        }
        return 1;
      }
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

