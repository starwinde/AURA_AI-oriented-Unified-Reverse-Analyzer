
uint FUN_0018d7a0(uint *param_1,int *param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  int *piVar4;
  int *piVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  byte bVar21;
  int *piVar5;
  int *piVar6;
  
  if (param_1 != (uint *)0x0) {
    if (param_1[0x18] != 0) {
      if (*param_2 == 0) {
        param_1[0x14] = 0xb;
        return 0xffffffff;
      }
      lVar8 = *(long *)(param_2 + 0x3c);
      if (lVar8 != 0) {
        uVar13 = *param_1;
        param_1[0x14] = 0;
        switch(uVar13) {
        case 0:
          bVar2 = *(byte *)(lVar8 + 0x80);
          if (bVar2 == 0) {
            return 0;
          }
          uVar11 = (uint)bVar2;
          uVar12 = uVar13;
          if (3 < bVar2 - 1) {
            iVar20 = 0;
            iVar17 = 0;
            iVar18 = 0;
            iVar19 = 0;
            piVar7 = (int *)(lVar8 + 0x94);
            do {
              piVar4 = piVar7 + 0x30;
              iVar20 = iVar20 + (uint)(*piVar7 == param_3);
              iVar17 = iVar17 + (uint)(piVar7[0xc] == param_3);
              iVar18 = iVar18 + (uint)(piVar7[0x18] == param_3);
              iVar19 = iVar19 + (uint)(piVar7[0x24] == param_3);
              piVar7 = piVar4;
            } while (piVar4 != (int *)(lVar8 + 0x94) + (ulong)(bVar2 >> 2) * 0x30);
            uVar13 = iVar20 + iVar17 + iVar18 + iVar19;
            uVar12 = uVar11 & 0xfffffffc;
            if ((bVar2 & 3) == 0) {
              return uVar13;
            }
          }
          if (*(int *)(lVar8 + ((ulong)uVar12 * 2 + (ulong)uVar12) * 0x10 + 0x94) == param_3) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 + 1 < uVar11) {
            if (param_3 == *(int *)(lVar8 + (ulong)(uVar12 + 1) * 0x30 + 0x94)) {
              uVar13 = uVar13 + 1;
            }
            if (uVar12 + 2 < uVar11) {
              if (param_3 == *(int *)(lVar8 + (ulong)(uVar12 + 2) * 0x30 + 0x94)) {
                uVar13 = uVar13 + 1;
              }
              if ((uVar12 + 3 < uVar11) &&
                 (param_3 == *(int *)(lVar8 + (ulong)(uVar12 + 3) * 0x30 + 0x94))) {
                uVar13 = uVar13 + 1;
              }
            }
          }
          return uVar13;
        case 1:
          bVar2 = *(byte *)(lVar8 + 0x67);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x7c) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0xb4)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xec)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (*(int *)(lVar8 + 0x124) == param_3) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x15c)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          if (*(int *)(lVar8 + 0x194) == param_3) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 6) {
            return uVar13;
          }
          if (*(int *)(lVar8 + 0x1cc) == param_3) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 7) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x204)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 8) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x23c)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 9) {
            return uVar13;
          }
          uVar11 = 9;
          piVar7 = (int *)(lVar8 + 0x274);
          do {
            uVar11 = uVar11 + 1;
            if (*piVar7 == param_3) {
              uVar13 = uVar13 + 1;
            }
            piVar7 = piVar7 + 0xe;
          } while (uVar11 < uVar12);
          return uVar13;
        case 2:
          goto switchD_0018d7f0_caseD_2;
        case 3:
          cVar1 = *(char *)(lVar8 + 0xa0);
          if (cVar1 == '\0') {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0xa8) == param_3;
          if (cVar1 == '\x01') {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0xd8)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x02') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x108)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x03') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x138)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x04') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x168)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x05') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x198)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x06') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x1c8)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\a') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x1f8)) {
            uVar13 = uVar13 + 1;
          }
          return uVar13;
        case 4:
          bVar2 = *(byte *)(lVar8 + 0x69);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x70) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x88)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xb8)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xd0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xe8)) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 6) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x100)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 7) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x118)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 8) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x130)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 9) {
            return uVar13;
          }
          uVar11 = 9;
          piVar7 = (int *)(lVar8 + 0x148);
          do {
            uVar11 = uVar11 + 1;
            if (param_3 == *piVar7) {
              uVar13 = uVar13 + 1;
            }
            piVar7 = piVar7 + 6;
          } while (uVar11 < uVar12);
          return uVar13;
        case 5:
          bVar2 = *(byte *)(lVar8 + 0x68);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x70) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x80)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x90)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xb0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          lVar9 = 5;
          do {
            lVar10 = lVar9 * 0x10;
            lVar9 = lVar9 + 1;
            if (param_3 == *(int *)(lVar8 + 0x70 + lVar10)) {
              uVar13 = uVar13 + 1;
            }
          } while ((uint)lVar9 < (uint)bVar2);
          return uVar13;
        case 6:
          bVar2 = *(byte *)(lVar8 + 100);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x68) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x88)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa8)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 200)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xe8)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x108)) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 6) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x128)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 7) {
            return uVar13;
          }
          lVar9 = 7;
          do {
            lVar10 = lVar9 * 0x20;
            lVar9 = lVar9 + 1;
            if (param_3 == *(int *)(lVar8 + 0x68 + lVar10)) {
              uVar13 = uVar13 + 1;
            }
          } while ((uint)lVar9 < uVar12);
          return uVar13;
        case 7:
          bVar2 = *(byte *)(lVar8 + 0x60);
          if (bVar2 == 0) {
            return 0;
          }
          uVar13 = bVar2 - 1;
          if (uVar13 < 4) {
            uVar13 = 0;
            uVar12 = 0;
          }
          else {
            uVar12 = uVar13 >> 2;
            bVar21 = -(param_3 == *(int *)(lVar8 + 0x94));
            uVar11 = (uint)(-(param_3 == *(int *)(lVar8 + 100)) & 1);
            uVar14 = (uint)(-(param_3 == *(int *)(lVar8 + 0x74)) & 1);
            uVar15 = (uint)(-(param_3 == *(int *)(lVar8 + 0x84)) & 1);
            uVar16 = (ulong)(CONCAT14(bVar21,uVar15) & 0x1ffffffff);
            if (uVar12 != 1) {
              piVar7 = (int *)(lVar8 + 0xe4);
              uVar11 = uVar11 + (param_3 == *(int *)(lVar8 + 0xa4));
              uVar14 = uVar14 + (param_3 == *(int *)(lVar8 + 0xb4));
              uVar16 = CONCAT44((uint)(bVar21 & 1) + (uint)(param_3 == *(int *)(lVar8 + 0xd4)),
                                uVar15 + (param_3 == *(int *)(lVar8 + 0xc4)));
              if (uVar12 != 2) {
                uVar15 = 2;
                do {
                  iVar20 = *piVar7;
                  piVar4 = piVar7 + 4;
                  piVar5 = piVar7 + 8;
                  piVar6 = piVar7 + 0xc;
                  piVar7 = piVar7 + 0x10;
                  uVar15 = uVar15 + 1;
                  uVar11 = uVar11 + (iVar20 == param_3);
                  uVar14 = uVar14 + (*piVar4 == param_3);
                  uVar16 = CONCAT44((int)(uVar16 >> 0x20) + (uint)(*piVar6 == param_3),
                                    (int)uVar16 + (uint)(*piVar5 == param_3));
                } while (uVar12 != uVar15);
              }
            }
            uVar12 = uVar11 + uVar14 + (int)uVar16 + (int)(uVar16 >> 0x20);
            uVar13 = uVar13 & 0xfffffffc;
          }
          if (param_3 == *(int *)(lVar8 + (ulong)uVar13 * 0x10 + 100)) {
            uVar12 = uVar12 + 1;
          }
          if ((uint)bVar2 <= uVar13 + 1) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + (ulong)(uVar13 + 1) * 0x10 + 100)) {
            uVar12 = uVar12 + 1;
          }
          if ((uint)bVar2 <= uVar13 + 2) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + (ulong)(uVar13 + 2) * 0x10 + 100)) {
            uVar12 = uVar12 + 1;
          }
          if ((uint)bVar2 <= uVar13 + 3) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + (ulong)(uVar13 + 3) * 0x10 + 100)) {
            uVar12 = uVar12 + 1;
          }
          return uVar12;
        case 8:
          cVar1 = *(char *)(lVar8 + 0x148);
          if (cVar1 == '\0') {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x90) == param_3;
          if (cVar1 == '\x01') {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 200)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x02') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x100)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x03') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x138)) {
            uVar13 = uVar13 + 1;
          }
          return uVar13;
        case 9:
          cVar1 = *(char *)(lVar8 + 0x60);
          if (cVar1 == '\0') {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 100) == param_3;
          if (cVar1 == '\x01') {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x84)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x02') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x03') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xc4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x04') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xe4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x05') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x104)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x06') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x124)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\a') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x144)) {
            uVar13 = uVar13 + 1;
          }
          return uVar13;
        case 10:
          bVar2 = *(byte *)(lVar8 + 0x61);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 100) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar12 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x7c)) {
            uVar12 = uVar12 + 1;
          }
          if (bVar2 == 2) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0x94)) {
            uVar12 = uVar12 + 1;
          }
          if (bVar2 == 3) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0xac)) {
            uVar12 = uVar12 + 1;
          }
          if (bVar2 == 4) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0xc4)) {
            uVar12 = uVar12 + 1;
          }
          if (bVar2 == 5) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0xdc)) {
            uVar12 = uVar12 + 1;
          }
          uVar11 = (uint)bVar2;
          if (uVar11 == 6) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0xf4)) {
            uVar12 = uVar12 + 1;
          }
          if (uVar11 == 7) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0x10c)) {
            uVar12 = uVar12 + 1;
          }
          if (uVar11 == 8) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0x124)) {
            uVar12 = uVar12 + 1;
          }
          if (uVar11 == 9) {
            return uVar12;
          }
          if (param_3 == *(int *)(lVar8 + 0x13c)) {
            uVar12 = uVar12 + 1;
          }
          if (uVar11 == 10) {
            return uVar12;
          }
          piVar7 = (int *)(lVar8 + 0x154);
          do {
            uVar13 = uVar13 + 1;
            if (param_3 == *piVar7) {
              uVar12 = uVar12 + 1;
            }
            piVar7 = piVar7 + 6;
          } while (uVar13 < uVar11);
          return uVar12;
        case 0xb:
          return 0;
        case 0xc:
          bVar2 = *(byte *)(lVar8 + 0x65);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x68) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x70)) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x78)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x80)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 4) {
            return uVar13;
          }
          lVar9 = 4;
          do {
            lVar10 = lVar9 * 8;
            lVar9 = lVar9 + 1;
            if (param_3 == *(int *)(lVar8 + 0x68 + lVar10)) {
              uVar13 = uVar13 + 1;
            }
          } while ((uint)lVar9 <= uVar12 && (uint)bVar2 != (uint)lVar9);
          return uVar13;
        case 0xd:
          bVar2 = *(byte *)(lVar8 + 0x60);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x68) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x88)) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa8)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 3) {
            return uVar13;
          }
          lVar9 = 3;
          do {
            lVar10 = lVar9 * 0x20;
            lVar9 = lVar9 + 1;
            if (param_3 == *(int *)(lVar8 + 0x68 + lVar10)) {
              uVar13 = uVar13 + 1;
            }
          } while ((uint)lVar9 < uVar12);
          return uVar13;
        case 0xe:
          bVar2 = *(byte *)(lVar8 + 0x60);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x68) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x80)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x98)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xb0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 200)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          uVar12 = 5;
          piVar7 = (int *)(lVar8 + 0xe0);
          do {
            uVar12 = uVar12 + 1;
            if (param_3 == *piVar7) {
              uVar13 = uVar13 + 1;
            }
            piVar7 = piVar7 + 6;
          } while (uVar12 < bVar2);
          return uVar13;
        case 0xf:
          bVar2 = *(byte *)(lVar8 + 0x61);
          if (bVar2 == 0) {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 0x68) == param_3;
          if (bVar2 == 1) {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x80)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 2) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x98)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 3) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xb0)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 4) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 200)) {
            uVar13 = uVar13 + 1;
          }
          if (bVar2 == 5) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xe0)) {
            uVar13 = uVar13 + 1;
          }
          uVar12 = (uint)bVar2;
          if (uVar12 == 6) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xf8)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 7) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x110)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 8) {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x128)) {
            uVar13 = uVar13 + 1;
          }
          if (uVar12 == 9) {
            return uVar13;
          }
          uVar11 = 9;
          piVar7 = (int *)(lVar8 + 0x140);
          do {
            uVar11 = uVar11 + 1;
            if (param_3 == *piVar7) {
              uVar13 = uVar13 + 1;
            }
            piVar7 = piVar7 + 6;
          } while (uVar11 < uVar12);
          return uVar13;
        default:
          param_1[0x14] = 3;
          return 0xffffffff;
        case 0x11:
          cVar1 = *(char *)(lVar8 + 0x60);
          if (cVar1 == '\0') {
            return 0;
          }
          bVar3 = *(int *)(lVar8 + 100) == param_3;
          if (cVar1 == '\x01') {
            return (uint)bVar3;
          }
          uVar13 = (uint)bVar3;
          if (param_3 == *(int *)(lVar8 + 0x74)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x02') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x84)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x03') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0x94)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x04') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xa4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x05') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xb4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\x06') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xc4)) {
            uVar13 = uVar13 + 1;
          }
          if (cVar1 == '\a') {
            return uVar13;
          }
          if (param_3 == *(int *)(lVar8 + 0xd4)) {
            uVar13 = uVar13 + 1;
          }
          return uVar13;
        }
      }
    }
    param_1[0x14] = 7;
  }
  return 0xffffffff;
switchD_0018d7f0_caseD_2:
  bVar2 = *(byte *)(lVar8 + 0x60);
  if (bVar2 == 0) {
    return 0;
  }
  bVar3 = *(int *)(lVar8 + 0x68) == param_3;
  if (bVar2 == 1) {
    return (uint)bVar3;
  }
  uVar13 = (uint)bVar3;
  if (param_3 == *(int *)(lVar8 + 0x80)) {
    uVar13 = uVar13 + 1;
  }
  if (bVar2 == 2) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0x98)) {
    uVar13 = uVar13 + 1;
  }
  if (bVar2 == 3) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0xb0)) {
    uVar13 = uVar13 + 1;
  }
  if (bVar2 == 4) {
    return uVar13;
  }
  if (*(int *)(lVar8 + 200) == param_3) {
    uVar13 = uVar13 + 1;
  }
  if (bVar2 == 5) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0xe0)) {
    uVar13 = uVar13 + 1;
  }
  uVar12 = (uint)bVar2;
  if (uVar12 == 6) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0xf8)) {
    uVar13 = uVar13 + 1;
  }
  if (uVar12 == 7) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0x110)) {
    uVar13 = uVar13 + 1;
  }
  if (uVar12 == 8) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0x128)) {
    uVar13 = uVar13 + 1;
  }
  if (uVar12 == 9) {
    return uVar13;
  }
  if (param_3 == *(int *)(lVar8 + 0x140)) {
    uVar13 = uVar13 + 1;
  }
  if (uVar12 == 10) {
    return uVar13;
  }
  if (*(int *)(lVar8 + 0x158) == param_3) {
    uVar13 = uVar13 + 1;
  }
  if (uVar12 == 0xb) {
    return uVar13;
  }
  uVar11 = 0xb;
  piVar7 = (int *)(lVar8 + 0x170);
  do {
    uVar11 = uVar11 + 1;
    if (*piVar7 == param_3) {
      uVar13 = uVar13 + 1;
    }
    piVar7 = piVar7 + 6;
  } while (uVar11 < uVar12);
  return uVar13;
}

