
/* WARNING: Type propagation algorithm not settling */

ulong cs_op_index(uint *param_1,int *param_2,int param_3,ulong param_4)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  ulong uVar10;
  
  if (param_1 == (uint *)0x0) {
    return 0xffffffff;
  }
  if (param_1[0x18] == 0) {
    param_1[0x14] = 7;
    return 0xffffffff;
  }
  if (*param_2 == 0) {
    param_1[0x14] = 0xb;
    return 0xffffffff;
  }
  lVar6 = *(long *)(param_2 + 0x3c);
  if (lVar6 == 0) {
    param_1[0x14] = 7;
    return 0xffffffff;
  }
  uVar4 = *param_1;
  param_1[0x14] = 0;
  uVar8 = (uint)param_4;
  switch(uVar4) {
  case 0:
    piVar7 = (int *)(lVar6 + 0x94);
    uVar2 = uVar4;
    if (*(byte *)(lVar6 + 0x80) != 0) {
      do {
        if (*piVar7 == param_3) {
          uVar4 = uVar4 + 1;
        }
        if (uVar4 == uVar8) {
          return (ulong)uVar2;
        }
        uVar2 = uVar2 + 1;
        piVar7 = piVar7 + 0xc;
      } while (*(byte *)(lVar6 + 0x80) != uVar2);
    }
    break;
  case 1:
    bVar1 = *(byte *)(lVar6 + 0x67);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    if (*(int *)(lVar6 + 0x7c) == param_3) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      uVar5 = uVar4;
      if (param_3 == *(int *)(lVar6 + 0xb4)) goto LAB_0018e2e4;
      if (uVar2 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0xec);
    }
    else {
      if (uVar8 == 0) {
        return 0;
      }
      if (uVar2 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0xb4)) {
        uVar5 = 0;
LAB_0018e2e4:
        uVar5 = uVar5 + 1;
        if (uVar5 == uVar8) {
LAB_0018d240:
          return (ulong)uVar4;
        }
        if (uVar2 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xec);
      }
      else {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xec);
        uVar5 = 0;
      }
    }
    if ((iVar9 == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
      return 2;
    }
    uVar4 = (uint)bVar1;
    if (3 < bVar1) {
      if ((*(int *)(lVar6 + 0x124) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
        return 3;
      }
      if (uVar4 != 4) {
        if ((*(int *)(lVar6 + 0x15c) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
          return 4;
        }
        if (uVar4 != 5) {
          if ((*(int *)(lVar6 + 0x194) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
            return 5;
          }
          if (uVar4 != 6) {
            if ((*(int *)(lVar6 + 0x1cc) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
              return 6;
            }
            if (uVar4 != 7) {
              if ((*(int *)(lVar6 + 0x204) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
                return 7;
              }
              if (uVar4 != 8) {
                if ((param_3 == *(int *)(lVar6 + 0x23c)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
                  return 8;
                }
                if (uVar4 != 9) {
                  piVar7 = (int *)(lVar6 + 0x274);
                  uVar3 = 9;
                  do {
                    if (*piVar7 == param_3) {
                      uVar5 = uVar5 + 1;
                    }
                    if (uVar5 == uVar8) {
                      return (ulong)uVar3;
                    }
                    uVar3 = uVar3 + 1;
                    piVar7 = piVar7 + 0xe;
                  } while (uVar3 <= uVar4 && uVar2 != uVar3);
                }
              }
            }
          }
        }
      }
    }
    break;
  case 2:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x80)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
        uVar5 = 1;
        goto joined_r0x0018dd78;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x80)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
        uVar5 = 0;
        goto joined_r0x0018dd78;
      }
      iVar9 = 0;
    }
    uVar5 = iVar9 + 1;
    if (uVar8 == uVar5) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x98);
joined_r0x0018dd78:
    if ((param_3 == iVar9) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return (ulong)uVar4;
    }
    if (uVar2 < 4) {
      return 0xffffffff;
    }
    if ((*(int *)(lVar6 + 0xb0) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
      return 3;
    }
    if (bVar1 == 4) {
      return 0xffffffff;
    }
    if ((*(int *)(lVar6 + 200) == param_3) && (uVar5 = uVar5 + 1, uVar5 == uVar8)) {
      return 4;
    }
    if (bVar1 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe0)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 5;
    }
    if (bVar1 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xf8)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 6;
    }
    if (bVar1 == 7) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x110)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 7;
    }
    if (bVar1 == 8) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x128)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 8;
    }
    if (bVar1 == 9) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x140)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 9;
    }
    if (bVar1 == 10) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x158)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 10;
    }
    if (uVar2 == 0xb) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0x170);
    uVar4 = 0xb;
    while( true ) {
      if (*piVar7 == param_3) {
        uVar5 = uVar5 + 1;
      }
      if (uVar5 == uVar8) break;
      uVar4 = uVar4 + 1;
      piVar7 = piVar7 + 6;
      if (uVar2 <= uVar4) {
        return 0xffffffff;
      }
    }
    return (ulong)uVar4;
  case 3:
    bVar1 = *(byte *)(lVar6 + 0xa0);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0xa8)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0xd8)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x108);
        uVar2 = 1;
        goto joined_r0x0018dca0;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0xd8)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x108);
        uVar2 = 0;
        goto joined_r0x0018dca0;
      }
      iVar9 = 0;
    }
    uVar2 = iVar9 + 1;
    if (uVar8 == uVar2) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x108);
joined_r0x0018dca0:
    if ((iVar9 == param_3) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x138)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return (ulong)uVar4;
    }
    if (bVar1 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x168)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 4;
    }
    if (bVar1 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x198)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 5;
    }
    if (bVar1 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x1c8)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 6;
    }
    if (bVar1 == 7) {
      return 0xffffffff;
    }
    if (*(int *)(lVar6 + 0x1f8) == param_3) {
      if (uVar8 == uVar2 + 1) {
        return 7;
      }
      return 0xffffffff;
    }
    return 0xffffffff;
  case 4:
    bVar1 = *(byte *)(lVar6 + 0x69);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0x70)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x88)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa0);
        uVar2 = 1;
        goto joined_r0x0018de08;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x88)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa0);
        uVar2 = 0;
        goto joined_r0x0018de08;
      }
      iVar9 = 0;
    }
    uVar2 = iVar9 + 1;
    if (uVar8 == uVar2) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0xa0);
joined_r0x0018de08:
    if ((param_3 == iVar9) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 2;
    }
    uVar5 = (uint)bVar1;
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xb8)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 3;
    }
    if (uVar5 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xd0)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return (ulong)uVar4;
    }
    if (uVar5 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe8)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 5;
    }
    if (uVar5 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x100)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 6;
    }
    if (uVar5 == 7) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x118)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 7;
    }
    if (uVar5 == 8) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x130)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 8;
    }
    if (uVar5 == 9) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0x148);
    uVar4 = 9;
    while( true ) {
      if (*piVar7 == param_3) {
        uVar2 = uVar2 + 1;
      }
      if (uVar2 == uVar8) break;
      uVar4 = uVar4 + 1;
      piVar7 = piVar7 + 6;
      if (uVar5 <= uVar4) {
        return 0xffffffff;
      }
    }
    return (ulong)uVar4;
  case 5:
    bVar1 = *(byte *)(lVar6 + 0x68);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    uVar4 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 0x70)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 1;
LAB_0018e2b0:
        uVar5 = iVar9 + 1;
        if (uVar8 == uVar5) {
          return 1;
        }
        if (uVar2 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x90);
      }
      else {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x90);
        uVar5 = 1;
      }
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (uVar2 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 0;
        goto LAB_0018e2b0;
      }
      if (uVar2 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0x90);
      uVar5 = 0;
    }
    if ((iVar9 == param_3) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 2;
    }
    if (3 < uVar4) {
      if ((param_3 == *(int *)(lVar6 + 0xa0)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
        return 3;
      }
      if (uVar4 != 4) {
        if ((param_3 == *(int *)(lVar6 + 0xb0)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
          return 4;
        }
        if (uVar4 != 5) {
          param_4 = 5;
          do {
            if (*(int *)(lVar6 + 0x70 + param_4 * 0x10) == param_3) {
              uVar5 = uVar5 + 1;
            }
            if (uVar5 == uVar8) {
              param_4 = param_4 & 0xffffffff;
              goto LAB_0018cfe0;
            }
            param_4 = param_4 + 1;
          } while ((uint)param_4 <= uVar4 && uVar2 != (uint)param_4);
        }
      }
    }
    break;
  case 6:
    bVar1 = *(byte *)(lVar6 + 100);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x88)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa8);
        uVar2 = 1;
        goto joined_r0x0018e048;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x88)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa8);
        uVar2 = 0;
        goto joined_r0x0018e048;
      }
      iVar9 = 0;
    }
    uVar2 = iVar9 + 1;
    if (uVar8 == uVar2) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0xa8);
joined_r0x0018e048:
    if ((param_3 == iVar9) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 2;
    }
    uVar5 = (uint)bVar1;
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 200)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 3;
    }
    if (uVar5 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe8)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 4;
    }
    if (uVar5 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x108)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 5;
    }
    if (uVar5 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x128)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return (ulong)uVar4;
    }
    if (uVar5 == 7) {
      return 0xffffffff;
    }
    uVar10 = 7;
    while( true ) {
      if (*(int *)(lVar6 + 0x68 + uVar10 * 0x20) == param_3) {
        uVar2 = uVar2 + 1;
      }
      if (uVar2 == uVar8) break;
      uVar10 = uVar10 + 1;
      if (uVar5 <= (uint)uVar10) {
        return 0xffffffff;
      }
    }
    return uVar10 & 0xffffffff;
  case 7:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 100)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x74)) {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x84);
        uVar5 = 1;
        goto joined_r0x0018de98;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (uVar2 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x74)) {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x84);
        uVar5 = 0;
        goto joined_r0x0018de98;
      }
      iVar9 = 0;
    }
    uVar5 = iVar9 + 1;
    if (uVar8 == uVar5) {
      return 1;
    }
    if (uVar2 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x84);
joined_r0x0018de98:
    if ((param_3 == iVar9) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 2;
    }
    uVar3 = (uint)bVar1;
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x94)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 3;
    }
    if (uVar3 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xa4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 4;
    }
    if (uVar3 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xb4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 5;
    }
    if (uVar3 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xc4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 6;
    }
    if (uVar3 == 7) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xd4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return (ulong)uVar4;
    }
    if (uVar3 == 8) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 8;
    }
    if (uVar3 == 9) {
      return 0xffffffff;
    }
    uVar10 = 9;
    while( true ) {
      if (*(int *)(lVar6 + 100 + uVar10 * 0x10) == param_3) {
        uVar5 = uVar5 + 1;
      }
      if (uVar5 == uVar8) break;
      uVar10 = uVar10 + 1;
      if (uVar3 < (uint)uVar10 || uVar2 == (uint)uVar10) {
        return 0xffffffff;
      }
    }
    return uVar10 & 0xffffffff;
  case 8:
    bVar1 = *(byte *)(lVar6 + 0x148);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0x90)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 200)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x100);
        uVar4 = 1;
        goto joined_r0x0018dc54;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 200)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x100);
        uVar4 = 0;
        goto joined_r0x0018dc54;
      }
      iVar9 = 0;
    }
    uVar4 = iVar9 + 1;
    if (uVar8 == uVar4) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x100);
joined_r0x0018dc54:
    if ((param_3 == iVar9) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if (*(int *)(lVar6 + 0x138) == param_3) {
      if (uVar8 == uVar4 + 1) {
        return 3;
      }
      return 0xffffffff;
    }
    return 0xffffffff;
  case 9:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 100)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x84)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa4);
        uVar4 = 1;
        goto joined_r0x0018ddc0;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x84)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa4);
        uVar4 = 0;
        goto joined_r0x0018ddc0;
      }
      iVar9 = 0;
    }
    uVar4 = iVar9 + 1;
    if (uVar8 == uVar4) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0xa4);
joined_r0x0018ddc0:
    if ((iVar9 == param_3) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xc4)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 3;
    }
    if (bVar1 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe4)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 4;
    }
    if (bVar1 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x104)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 5;
    }
    if (bVar1 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x124)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 6;
    }
    if (bVar1 == 7) {
      return 0xffffffff;
    }
    if (*(int *)(lVar6 + 0x144) != param_3) {
      return 0xffffffff;
    }
    if (uVar8 != uVar4 + 1) {
      return 0xffffffff;
    }
    return 7;
  case 10:
    bVar1 = *(byte *)(lVar6 + 0x61);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 100)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x7c)) {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x94);
        uVar5 = 1;
        goto joined_r0x0018dee0;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (uVar2 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x7c)) {
        if (uVar2 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x94);
        uVar5 = 0;
        goto joined_r0x0018dee0;
      }
      iVar9 = 0;
    }
    uVar5 = iVar9 + 1;
    if (uVar8 == uVar5) {
      return 1;
    }
    if (uVar2 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x94);
joined_r0x0018dee0:
    if ((iVar9 == param_3) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xac)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 3;
    }
    if (bVar1 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xc4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 4;
    }
    if (bVar1 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xdc)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 5;
    }
    if (bVar1 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xf4)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 6;
    }
    if (bVar1 == 7) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x10c)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 7;
    }
    if (bVar1 == 8) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x124)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 8;
    }
    if (bVar1 == 9) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x13c)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 9;
    }
    if (bVar1 == 10) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0x154);
    while( true ) {
      if (*piVar7 == param_3) {
        uVar5 = uVar5 + 1;
      }
      if (uVar5 == uVar8) break;
      uVar4 = uVar4 + 1;
      piVar7 = piVar7 + 6;
      if (uVar2 <= uVar4) {
        return 0xffffffff;
      }
    }
    return (ulong)uVar4;
  case 0xb:
    break;
  case 0xc:
    bVar1 = *(byte *)(lVar6 + 0x65);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar4 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x70)) {
        iVar9 = 1;
LAB_0018e40c:
        uVar2 = iVar9 + 1;
        if (uVar8 == uVar2) {
          return 1;
        }
        if (bVar1 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x78);
      }
      else {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x78);
        uVar2 = 1;
      }
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x70)) {
        iVar9 = 0;
        goto LAB_0018e40c;
      }
      if (bVar1 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0x78);
      uVar2 = 0;
    }
    if ((param_3 == iVar9) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 2;
    }
    if (uVar4 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x80)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 3;
    }
    if (uVar4 == 4) {
      return 0xffffffff;
    }
    param_4 = 4;
    while( true ) {
      if (*(int *)(lVar6 + 0x68 + param_4 * 8) == param_3) {
        uVar2 = uVar2 + 1;
      }
      if (uVar2 == uVar8) break;
      param_4 = param_4 + 1;
      if (uVar4 <= (uint)param_4) {
        return 0xffffffff;
      }
    }
    param_4 = param_4 & 0xffffffff;
LAB_0018cfe0:
    return param_4 & 0xffffffff;
  case 0xd:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x88)) {
        iVar9 = 1;
LAB_0018e4ac:
        uVar4 = iVar9 + 1;
        if (uVar8 == uVar4) {
          return 1;
        }
        if (bVar1 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa8);
      }
      else {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xa8);
        uVar4 = 1;
      }
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x88)) {
        iVar9 = 0;
        goto LAB_0018e4ac;
      }
      if (bVar1 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0xa8);
      uVar4 = 0;
    }
    if ((param_3 == iVar9) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    param_4 = 3;
    while( true ) {
      if (*(int *)(lVar6 + 0x68 + param_4 * 0x20) == param_3) {
        uVar4 = uVar4 + 1;
      }
      if (uVar4 == uVar8) break;
      param_4 = param_4 + 1;
      if ((uint)bVar1 <= (uint)param_4) {
        return 0xffffffff;
      }
    }
    param_4 = param_4 & 0xffffffff;
    goto LAB_0018cfe0;
  case 0xe:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar4 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 1;
LAB_0018e4fc:
        uVar2 = iVar9 + 1;
        if (uVar8 == uVar2) {
          return 1;
        }
        if (bVar1 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
      }
      else {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
        uVar2 = 1;
      }
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 0;
        goto LAB_0018e4fc;
      }
      if (bVar1 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0x98);
      uVar2 = 0;
    }
    if ((param_3 == iVar9) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 2;
    }
    if (uVar4 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xb0)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 3;
    }
    if (uVar4 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 200)) && (uVar2 = uVar2 + 1, uVar8 == uVar2)) {
      return 4;
    }
    if (uVar4 == 5) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0xe0);
    uVar5 = 5;
    while( true ) {
      if (*piVar7 == param_3) {
        uVar2 = uVar2 + 1;
      }
      if (uVar2 == uVar8) break;
      uVar5 = uVar5 + 1;
      piVar7 = piVar7 + 6;
      if (uVar4 <= uVar5) {
        return 0xffffffff;
      }
    }
    param_4 = (ulong)uVar5;
    goto LAB_0018cfe0;
  case 0xf:
    bVar1 = *(byte *)(lVar6 + 0x61);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 1;
LAB_0018e3bc:
        uVar4 = iVar9 + 1;
        if (uVar8 == uVar4) {
          return 1;
        }
        if (bVar1 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
      }
      else {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x98);
        uVar4 = 1;
      }
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0x80)) {
        iVar9 = 0;
        goto LAB_0018e3bc;
      }
      if (bVar1 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0x98);
      uVar4 = 0;
    }
    if ((param_3 == iVar9) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 2;
    }
    uVar2 = (uint)bVar1;
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xb0)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 3;
    }
    if (uVar2 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 200)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 4;
    }
    if (uVar2 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xe0)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 5;
    }
    if (uVar2 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xf8)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 6;
    }
    if (uVar2 == 7) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x110)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 7;
    }
    if (uVar2 == 8) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x128)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 8;
    }
    if (uVar2 == 9) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0x140);
    uVar5 = 9;
    while( true ) {
      if (*piVar7 == param_3) {
        uVar4 = uVar4 + 1;
      }
      if (uVar4 == uVar8) break;
      uVar5 = uVar5 + 1;
      piVar7 = piVar7 + 6;
      if (uVar2 <= uVar5) {
        return 0xffffffff;
      }
    }
    param_4 = (ulong)uVar5;
    goto LAB_0018cfe0;
  case 0x10:
    bVar1 = *(byte *)(lVar6 + 0x65);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    uVar2 = (uint)bVar1;
    if (param_3 == *(int *)(lVar6 + 0x68)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0xa0)) {
        iVar9 = 1;
        goto LAB_0018e484;
      }
      if (bVar1 == 2) {
        return 0xffffffff;
      }
      iVar9 = *(int *)(lVar6 + 0xd8);
      uVar5 = 1;
    }
    else {
      if (uVar8 == 0) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 == *(int *)(lVar6 + 0xa0)) {
        iVar9 = 0;
LAB_0018e484:
        uVar5 = iVar9 + 1;
        if (uVar8 == uVar5) {
          return 1;
        }
        if (bVar1 < 3) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xd8);
      }
      else {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0xd8);
        uVar5 = 0;
      }
    }
    if ((param_3 == iVar9) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 2;
    }
    if (uVar2 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x110)) && (uVar5 = uVar5 + 1, uVar8 == uVar5)) {
      return 3;
    }
    if (uVar2 == 4) {
      return 0xffffffff;
    }
    piVar7 = (int *)(lVar6 + 0x148);
    uVar4 = 4;
    while( true ) {
      if (*piVar7 == param_3) {
        uVar5 = uVar5 + 1;
      }
      if (uVar5 == uVar8) break;
      uVar4 = uVar4 + 1;
      piVar7 = piVar7 + 0xe;
      if (uVar2 <= uVar4) {
        return 0xffffffff;
      }
    }
    goto LAB_0018d240;
  case 0x11:
    bVar1 = *(byte *)(lVar6 + 0x60);
    if (bVar1 == 0) {
      return 0xffffffff;
    }
    if (param_3 == *(int *)(lVar6 + 100)) {
      if (uVar8 == 1) {
        return 0;
      }
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x74)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x84);
        uVar4 = 1;
        goto joined_r0x0018de50;
      }
      iVar9 = 1;
    }
    else {
      if (uVar8 == 0) goto LAB_0018cfe0;
      if (bVar1 == 1) {
        return 0xffffffff;
      }
      if (param_3 != *(int *)(lVar6 + 0x74)) {
        if (bVar1 == 2) {
          return 0xffffffff;
        }
        iVar9 = *(int *)(lVar6 + 0x84);
        uVar4 = 0;
        goto joined_r0x0018de50;
      }
      iVar9 = 0;
    }
    uVar4 = iVar9 + 1;
    if (uVar8 == uVar4) {
      return 1;
    }
    if (bVar1 < 3) {
      return 0xffffffff;
    }
    iVar9 = *(int *)(lVar6 + 0x84);
joined_r0x0018de50:
    if ((param_3 == iVar9) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 2;
    }
    if (bVar1 < 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0x94)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 3;
    }
    if (bVar1 == 4) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xa4)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 4;
    }
    if (bVar1 == 5) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xb4)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 5;
    }
    if (bVar1 == 6) {
      return 0xffffffff;
    }
    if ((param_3 == *(int *)(lVar6 + 0xc4)) && (uVar4 = uVar4 + 1, uVar8 == uVar4)) {
      return 6;
    }
    if (bVar1 == 7) {
      return 0xffffffff;
    }
    if (*(int *)(lVar6 + 0xd4) == param_3) {
      if (uVar4 + 1 == uVar8) {
        return 7;
      }
      return 0xffffffff;
    }
    return 0xffffffff;
  default:
    param_1[0x14] = 3;
  }
  return 0xffffffff;
}

