
ulong read_encoded_ptr_constprop_0
                (long param_1,ulong param_2,ulong *param_3,byte param_4,long param_5)

{
  ulong uVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined1 uVar6;
  byte bVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  
  if (param_4 == 0xff) {
    return 0;
  }
  bVar3 = param_4 & 0xf;
  uVar12 = *param_3;
  if (bVar3 != 4) {
    if (bVar3 < 5) {
      if (bVar3 == 2) {
        if (uVar12 + 2 <= param_2) {
          uVar6 = *(undefined1 *)(param_1 + uVar12);
          uVar2 = *(undefined1 *)(param_1 + uVar12 + 1);
          *param_3 = uVar12 + 2;
          uVar9 = (ulong)CONCAT11(uVar2,uVar6);
          goto joined_r0x00187df4;
        }
        goto LAB_00187ec0;
      }
      if (bVar3 == 3) {
        if (param_2 < uVar12 + 4) goto LAB_00187ec0;
        lVar8 = param_1 + uVar12;
        bVar7 = *(byte *)(param_1 + uVar12);
        bVar3 = *(byte *)(lVar8 + 2);
        bVar4 = *(byte *)(lVar8 + 3);
        bVar5 = *(byte *)(lVar8 + 1);
        *param_3 = uVar12 + 4;
        uVar9 = (ulong)((uint)bVar3 << 0x10 | (uint)bVar5 << 8 | (uint)bVar7 | (uint)bVar4 << 0x18);
        goto joined_r0x00187df4;
      }
      if (bVar3 != 0) {
        if (uVar12 < param_2) {
          uVar10 = uVar12 + 1;
          *param_3 = uVar10;
          uVar9 = (ulong)*(byte *)(param_1 + uVar12) & 0x7f;
          if (((char)*(byte *)(param_1 + uVar12) < '\0') && (uVar10 < param_2)) {
            uVar11 = uVar12 + 2;
            *param_3 = uVar11;
            uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar10) & 0x7f) << 7;
            if (((char)*(byte *)(param_1 + uVar10) < '\0') && (uVar11 < param_2)) {
              uVar10 = uVar12 + 3;
              *param_3 = uVar10;
              uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar11) & 0x7f) << 0xe;
              if (((char)*(byte *)(param_1 + uVar11) < '\0') && (uVar10 < param_2)) {
                uVar11 = uVar12 + 4;
                *param_3 = uVar11;
                uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar10) & 0x7f) << 0x15;
                if (((char)*(byte *)(param_1 + uVar10) < '\0') && (uVar11 < param_2)) {
                  uVar10 = uVar12 + 5;
                  *param_3 = uVar10;
                  uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar11) & 0x7f) << 0x1c;
                  if (((char)*(byte *)(param_1 + uVar11) < '\0') && (uVar10 < param_2)) {
                    uVar11 = uVar12 + 6;
                    *param_3 = uVar11;
                    uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar10) & 0x7f) << 0x23;
                    if (((char)*(byte *)(param_1 + uVar10) < '\0') && (uVar11 < param_2)) {
                      uVar10 = uVar12 + 7;
                      *param_3 = uVar10;
                      uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar11) & 0x7f) << 0x2a;
                      if (((char)*(byte *)(param_1 + uVar11) < '\0') && (uVar10 < param_2)) {
                        uVar11 = uVar12 + 8;
                        *param_3 = uVar11;
                        uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar10) & 0x7f) << 0x31;
                        if (((char)*(byte *)(param_1 + uVar10) < '\0') && (uVar11 < param_2)) {
                          uVar10 = uVar12 + 9;
                          *param_3 = uVar10;
                          uVar9 = uVar9 | ((ulong)*(byte *)(param_1 + uVar11) & 0x7f) << 0x38;
                          if (((char)*(byte *)(param_1 + uVar11) < '\0') && (uVar10 < param_2)) {
                            *param_3 = uVar12 + 10;
                            uVar9 = uVar9 | (ulong)*(byte *)(param_1 + uVar10) << 0x3f;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else {
          uVar9 = 0;
        }
        goto joined_r0x00187df4;
      }
    }
    else {
      if (bVar3 == 0xb) {
        if (param_2 < uVar12 + 4) goto LAB_00187ec0;
        lVar8 = param_1 + uVar12;
        bVar7 = *(byte *)(param_1 + uVar12);
        bVar3 = *(byte *)(lVar8 + 2);
        bVar4 = *(byte *)(lVar8 + 3);
        bVar5 = *(byte *)(lVar8 + 1);
        *param_3 = uVar12 + 4;
        uVar9 = (long)(int)((uint)bVar3 << 0x10 | (uint)bVar5 << 8 |
                           (uint)bVar7 | (uint)bVar4 << 0x18);
        goto joined_r0x00187df4;
      }
      if (bVar3 < 0xc) {
        if (bVar3 == 9) {
          if (param_2 <= uVar12) {
            return 0;
          }
          uVar9 = uVar12 + 1;
          *param_3 = uVar9;
          uVar11 = (ulong)*(byte *)(param_1 + uVar12);
          uVar10 = uVar11 & 0x7f;
          if (((char)*(byte *)(param_1 + uVar12) < '\0') && (uVar9 < param_2)) {
            uVar1 = uVar12 + 2;
            *param_3 = uVar1;
            uVar11 = (ulong)*(byte *)(param_1 + uVar9);
            uVar10 = uVar10 | (uVar11 & 0x7f) << 7;
            if (((char)*(byte *)(param_1 + uVar9) < '\0') && (uVar1 < param_2)) {
              uVar9 = uVar12 + 3;
              *param_3 = uVar9;
              uVar11 = (ulong)*(byte *)(param_1 + uVar1);
              uVar10 = uVar10 | (uVar11 & 0x7f) << 0xe;
              if (((char)*(byte *)(param_1 + uVar1) < '\0') && (uVar9 < param_2)) {
                uVar1 = uVar12 + 4;
                *param_3 = uVar1;
                uVar11 = (ulong)*(byte *)(param_1 + uVar9);
                uVar10 = uVar10 | (uVar11 & 0x7f) << 0x15;
                if (((char)*(byte *)(param_1 + uVar9) < '\0') && (uVar1 < param_2)) {
                  uVar9 = uVar12 + 5;
                  *param_3 = uVar9;
                  uVar11 = (ulong)*(byte *)(param_1 + uVar1);
                  uVar10 = uVar10 | (uVar11 & 0x7f) << 0x1c;
                  if (((char)*(byte *)(param_1 + uVar1) < '\0') && (uVar9 < param_2)) {
                    uVar1 = uVar12 + 6;
                    *param_3 = uVar1;
                    uVar11 = (ulong)*(byte *)(param_1 + uVar9);
                    uVar10 = uVar10 | (uVar11 & 0x7f) << 0x23;
                    if (((char)*(byte *)(param_1 + uVar9) < '\0') && (uVar1 < param_2)) {
                      uVar9 = uVar12 + 7;
                      *param_3 = uVar9;
                      uVar11 = (ulong)*(byte *)(param_1 + uVar1);
                      uVar10 = uVar10 | (uVar11 & 0x7f) << 0x2a;
                      if (((char)*(byte *)(param_1 + uVar1) < '\0') && (uVar9 < param_2)) {
                        uVar1 = uVar12 + 8;
                        *param_3 = uVar1;
                        uVar11 = (ulong)*(byte *)(param_1 + uVar9);
                        uVar10 = uVar10 | (uVar11 & 0x7f) << 0x31;
                        if (((char)*(byte *)(param_1 + uVar9) < '\0') && (uVar1 < param_2)) {
                          uVar9 = uVar12 + 9;
                          *param_3 = uVar9;
                          uVar11 = (ulong)*(byte *)(param_1 + uVar1);
                          uVar10 = uVar10 | (uVar11 & 0x7f) << 0x38;
                          if (((char)*(byte *)(param_1 + uVar1) < '\0') && (uVar9 < param_2)) {
                            *param_3 = uVar12 + 10;
                            uVar9 = uVar10 | (ulong)*(byte *)(param_1 + uVar9) << 0x3f;
                            goto joined_r0x00187df4;
                          }
                          lVar8 = 0x3f;
                        }
                        else {
                          lVar8 = 0x38;
                        }
                      }
                      else {
                        lVar8 = 0x31;
                      }
                    }
                    else {
                      lVar8 = 0x2a;
                    }
                  }
                  else {
                    lVar8 = 0x23;
                  }
                }
                else {
                  lVar8 = 0x1c;
                }
              }
              else {
                lVar8 = 0x15;
              }
            }
            else {
              lVar8 = 0xe;
            }
          }
          else {
            lVar8 = 7;
          }
          uVar9 = uVar10 | -1L << lVar8;
          if ((uVar11 & 0x40) == 0) {
            uVar9 = uVar10;
          }
        }
        else {
          if (bVar3 != 10) {
            return 0;
          }
          if (param_2 < uVar12 + 2) goto LAB_00187ec0;
          uVar6 = *(undefined1 *)(param_1 + uVar12);
          uVar2 = *(undefined1 *)(param_1 + uVar12 + 1);
          *param_3 = uVar12 + 2;
          uVar9 = (long)CONCAT11(uVar2,uVar6);
        }
        goto joined_r0x00187df4;
      }
      if (bVar3 != 0xc) {
        return 0;
      }
    }
  }
  if (param_2 < uVar12 + 8) {
LAB_00187ec0:
    *param_3 = param_2;
    return 0;
  }
  uVar10 = uVar12 + 8;
  uVar9 = uVar12 + 4;
  if (param_2 < uVar9) {
    uVar10 = param_2 + 4;
    *param_3 = param_2;
    if (param_2 < uVar10) {
      return 0;
    }
    uVar11 = 0;
  }
  else {
    lVar8 = param_1 + uVar12;
    bVar7 = *(byte *)(param_1 + uVar12);
    bVar3 = *(byte *)(lVar8 + 2);
    bVar4 = *(byte *)(lVar8 + 1);
    bVar5 = *(byte *)(lVar8 + 3);
    *param_3 = uVar9;
    uVar11 = (ulong)((uint)bVar3 << 0x10 | (uint)bVar4 << 8 | (uint)bVar7 | (uint)bVar5 << 0x18);
    param_2 = uVar9;
  }
  lVar8 = param_1 + param_2;
  bVar7 = *(byte *)(param_1 + param_2);
  bVar3 = *(byte *)(lVar8 + 2);
  bVar4 = *(byte *)(lVar8 + 3);
  bVar5 = *(byte *)(lVar8 + 1);
  *param_3 = uVar10;
  uVar9 = uVar11 | (ulong)((uint)bVar3 << 0x10 | (uint)bVar5 << 8 |
                          (uint)bVar7 | (uint)bVar4 << 0x18) << 0x20;
joined_r0x00187df4:
  if (uVar9 == 0) {
    return 0;
  }
  if ((param_4 & 0xf0) == 0x10) {
    uVar12 = uVar9 + uVar12 + param_5;
  }
  else {
    uVar12 = uVar9 + param_5;
    if ((param_4 & 0xf0) != 0x30) {
      uVar12 = uVar9;
    }
  }
  return uVar12;
}

