
void AArch64_post_printer(long param_1,long param_2,undefined8 param_3,long param_4)

{
  uint uVar1;
  ulong uVar2;
  
  if ((*(int *)(param_1 + 0x60) != 3) || (*(int *)(*(long *)(param_4 + 800) + 0x60) == 0)) {
    return;
  }
  uVar1 = MCInst_getOpcode(param_4);
  if (uVar1 < 0xd77) {
    if (uVar1 < 0xd39) {
      if (uVar1 < 0xc91) {
        if (uVar1 < 0xc52) {
          if (uVar1 < 0xc11) {
            if (uVar1 < 0xbd2) {
              if (uVar1 < 0xb7f) {
                if (uVar1 < 0xb70) {
                  return;
                }
                uVar2 = 0x5555L >> ((ulong)(uVar1 - 0xb70) & 0x3f);
                goto joined_r0x001db7a8;
              }
              if (0x3e < uVar1 - 0xb86) {
                return;
              }
              uVar2 = 0x5555000000005555U >> ((ulong)(uVar1 - 0xb86) & 0x3f) & 1;
            }
            else {
              uVar2 = 0x5015400055555555U >> ((ulong)(uVar1 - 0xbd2) & 0x3f) & 1;
            }
          }
          else {
            if (0x3e < uVar1 - 0xc12) {
              return;
            }
            uVar2 = 0x5555540551555555U >> ((ulong)(uVar1 - 0xc12) & 0x3f) & 1;
          }
        }
        else {
          uVar2 = 0x5515554555415455U >> ((ulong)(uVar1 - 0xc52) & 0x3f) & 1;
        }
      }
      else {
        if (0x1b < uVar1 - 0xd19) {
          return;
        }
        uVar2 = 1L << ((ulong)(uVar1 - 0xd19) & 0x3f);
        if ((uVar2 & 0x8552492) != 0) goto LAB_001db7d4;
        uVar2 = uVar2 & 0x4209249;
      }
    }
    else {
      uVar2 = 1L << ((ulong)(uVar1 - 0xd39) & 0x3f);
      if ((uVar2 & 0x2082082108420842) != 0) goto LAB_001db7d4;
      uVar2 = uVar2 & 0x1041041084210421;
    }
  }
  else {
    if (uVar1 < 0x1494) {
      if (uVar1 < 0x147b) {
        if (uVar1 < 0x140e) {
          if (0x13cf < uVar1) {
            if ((1L << ((ulong)(uVar1 - 0x13d0) & 0x3f) & 0x2a8aaa8415400055U) == 0) {
              if (uVar1 != 0x13f3) {
                return;
              }
              goto LAB_001db7d4;
            }
            goto LAB_001db740;
          }
          if (0x3c < uVar1 - 0x1392) {
            return;
          }
          uVar2 = 0x1555555555405555 >> ((ulong)(uVar1 - 0x1392) & 0x3f);
joined_r0x001db7a8:
          uVar2 = uVar2 & 1;
          goto joined_r0x001db7a8;
        }
        if (0x3e < uVar1 - 0x1415) {
          return;
        }
        uVar2 = 1L << ((ulong)(uVar1 - 0x1415) & 0x3f);
        if ((uVar2 & 0x1815415550551555) != 0) goto LAB_001db740;
        uVar2 = uVar2 & 0x6000000000000000;
      }
      else {
        uVar2 = 1L << ((ulong)(uVar1 - 0x147b) & 0x3f);
        if ((uVar2 & 0x1085249) != 0) goto LAB_001db740;
        uVar2 = uVar2 & 0x10a492;
      }
      if (uVar2 == 0) {
        return;
      }
LAB_001db7d4:
      *(undefined1 *)(*(long *)(param_2 + 0xf0) + 0x65) = 1;
      return;
    }
    if (0x3e < uVar1 - 0x1494) {
      return;
    }
    uVar2 = 1L << ((ulong)(uVar1 - 0x1494) & 0x3f);
    if ((uVar2 & 0x4400000042108421) != 0) goto LAB_001db7d4;
    uVar2 = uVar2 & 0x2200000021084210;
  }
joined_r0x001db7a8:
  if (uVar2 == 0) {
    return;
  }
LAB_001db740:
  *(undefined2 *)(*(long *)(param_2 + 0xf0) + 0x65) = 0x101;
  return;
}

