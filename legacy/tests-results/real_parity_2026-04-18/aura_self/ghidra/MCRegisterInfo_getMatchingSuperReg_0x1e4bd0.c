
uint MCRegisterInfo_getMatchingSuperReg(long *param_1,uint param_2,uint param_3,long param_4)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  ushort *puVar10;
  long lVar11;
  
  if (param_2 < *(uint *)(param_1 + 1)) {
    lVar11 = param_1[6];
    lVar4 = (ulong)*(uint *)(*param_1 + (ulong)param_2 * 0x18 + 8) * 2;
    puVar10 = (ushort *)(lVar11 + lVar4);
    if ((puVar10 != (ushort *)0x0) && (uVar3 = (uint)*(ushort *)(lVar11 + lVar4), uVar3 != 0)) {
      uVar3 = uVar3 + param_2;
      do {
        uVar3 = uVar3 & 0xffff;
        puVar10 = puVar10 + 1;
        if (param_4 != 0) {
          while( true ) {
            if ((uVar3 >> 3 < (uint)*(ushort *)(param_4 + 0x10)) &&
               (((int)(uint)*(byte *)(*(long *)(param_4 + 8) + (ulong)(uVar3 >> 3)) >> (uVar3 & 7) &
                1U) != 0)) break;
            uVar2 = *puVar10;
            puVar10 = puVar10 + 1;
            uVar3 = uVar3 + uVar2 & 0xffff;
            if (uVar2 == 0) {
              return 0;
            }
          }
          lVar9 = *param_1 + (ulong)uVar3 * 0x18;
          lVar6 = (ulong)*(uint *)(lVar9 + 4) * 2;
          lVar4 = lVar11 + lVar6;
          if (lVar4 == 0) {
LAB_001e4cc0:
            uVar5 = 0;
          }
          else {
            uVar5 = 0;
            uVar7 = (uint)*(ushort *)(lVar11 + lVar6);
            if (uVar7 != 0) {
              uVar7 = uVar3 + uVar7;
              lVar6 = 0;
              do {
                uVar5 = uVar7 & 0xffff;
                puVar1 = (ushort *)(param_1[8] + (ulong)*(uint *)(lVar9 + 0xc) * 2 + lVar6);
                lVar6 = lVar6 + 2;
                if (param_3 == *puVar1) goto LAB_001e4cc4;
                uVar8 = (uint)*(ushort *)(lVar4 + lVar6);
                uVar7 = uVar8 + uVar5;
              } while (uVar8 != 0);
              goto LAB_001e4cc0;
            }
          }
LAB_001e4cc4:
          if (param_2 == uVar5) {
            return uVar3;
          }
        }
        uVar3 = uVar3 + *puVar10;
        if (*puVar10 == 0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

