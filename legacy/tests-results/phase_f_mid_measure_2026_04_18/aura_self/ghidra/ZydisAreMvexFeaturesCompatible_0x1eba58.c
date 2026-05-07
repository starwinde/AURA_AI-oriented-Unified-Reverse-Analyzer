
/* WARNING: Removing unreachable block (ram,0x001ebaec) */

undefined8 ZydisAreMvexFeaturesCompatible(long param_1,long param_2)

{
  uint uVar1;
  ulong uVar2;
  
  if ((*(byte *)(*(long *)(param_1 + 8) + 6) & 7) != 5) {
    return 1;
  }
  if ((*(byte *)(*(long *)(param_1 + 8) + 5) >> 6 == 3) && (*(char *)(param_2 + 0x18d) != '\0')) {
    return 0;
  }
  uVar2 = (ulong)(*(ushort *)(*(long *)(param_1 + 0x10) + 0xc) >> 8) & 0x1f;
  uVar1 = (uint)uVar2;
  if (uVar1 < 0x12) {
    switch(uVar2) {
    case 0:
    case 1:
    case 4:
    case 5:
    case 6:
    case 7:
      goto switchD_001ebb7c_caseD_0;
    case 2:
      if ((((*(int *)(param_2 + 0x17c) != 0) || (*(int *)(param_2 + 0x180) != 0)) ||
          (*(int *)(param_2 + 0x188) != 0)) || (*(char *)(param_2 + 0x18d) != '\0')) {
        return 0;
      }
      break;
    case 3:
      if (((*(int *)(param_2 + 0x17c) != 0) || (*(int *)(param_2 + 0x180) != 0)) ||
         ((*(int *)(param_2 + 0x184) != 0 ||
          ((*(int *)(param_2 + 0x188) != 0 || (*(char *)(param_2 + 0x18d) != '\0')))))) {
        return 0;
      }
      break;
    case 8:
    case 9:
      if ((((*(int *)(param_2 + 0x17c) != 0) || (*(int *)(param_2 + 0x180) != 0)) ||
          (*(int *)(param_2 + 0x184) != 0)) || (*(char *)(param_2 + 0x18c) != '\0')) {
        return 0;
      }
      break;
    case 10:
      if (((*(int *)(param_2 + 0x184) != 0) || (*(int *)(param_2 + 0x188) != 0)) ||
         (*(char *)(param_2 + 0x18c) != '\0')) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x17c) != 4)) &&
         (*(int *)(param_2 + 0x17c) != 0xb)) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x180) != 0) && (*(int *)(param_2 + 0x180) != 1)) &&
         ((*(int *)(param_2 + 0x180) != 3 &&
          ((*(int *)(param_2 + 0x180) != 5 && (*(int *)(param_2 + 0x180) != 4)))))) {
        return 0;
      }
      if ((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x180) != 0)) {
        return 0;
      }
      break;
    case 0xb:
    case 0xf:
      if ((((*(int *)(param_2 + 0x180) != 0) || (*(int *)(param_2 + 0x184) != 0)) ||
          (*(int *)(param_2 + 0x188) != 0)) || (*(char *)(param_2 + 0x18c) != '\0')) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x17c) != 4)) &&
         (*(int *)(param_2 + 0x17c) != 0xb)) {
        return 0;
      }
      break;
    case 0xc:
    case 0x10:
      if (((*(int *)(param_2 + 0x180) != 0) || (*(int *)(param_2 + 0x184) != 0)) ||
         ((*(int *)(param_2 + 0x188) != 0 || (*(char *)(param_2 + 0x18c) != '\0')))) {
        return 0;
      }
      if ((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x17c) != 0xb)) {
        return 0;
      }
      break;
    case 0xd:
    case 0x11:
      if ((((*(int *)(param_2 + 0x180) != 0) || (*(int *)(param_2 + 0x184) != 0)) ||
          (*(int *)(param_2 + 0x188) != 0)) || (*(char *)(param_2 + 0x18c) != '\0')) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x17c) != 3)) &&
         (*(int *)(param_2 + 0x17c) != 10)) {
        return 0;
      }
      break;
    case 0xe:
      if (((*(int *)(param_2 + 0x184) != 0) || (*(int *)(param_2 + 0x188) != 0)) ||
         (*(char *)(param_2 + 0x18c) != '\0')) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x17c) != 4)) &&
         (*(int *)(param_2 + 0x17c) != 0xb)) {
        return 0;
      }
      if (((*(int *)(param_2 + 0x180) != 0) && (*(int *)(param_2 + 0x180) != 3)) &&
         ((*(int *)(param_2 + 0x180) != 2 &&
          ((*(int *)(param_2 + 0x180) != 5 && (*(int *)(param_2 + 0x180) != 4)))))) {
        return 0;
      }
      if ((*(int *)(param_2 + 0x17c) != 0) && (*(int *)(param_2 + 0x180) != 0)) {
        return 0;
      }
      break;
    default:
      goto switchD_001ebb7c_default;
    }
  }
  else {
    if ((0x19 < uVar1) || (uVar1 < 0x12)) {
switchD_001ebb7c_default:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xa87,
                    "ZydisAreMvexFeaturesCompatible");
    }
    uVar2 = 1L << uVar2;
    if ((uVar2 & 0x2a80000) == 0) {
      if ((uVar2 & 0x1100000) != 0) {
        if ((((*(int *)(param_2 + 0x17c) != 0) || (*(int *)(param_2 + 0x184) != 0)) ||
            (*(int *)(param_2 + 0x188) != 0)) || (*(char *)(param_2 + 0x18c) != '\0')) {
          return 0;
        }
        if (*(int *)(param_2 + 0x180) == 0) {
          return 1;
        }
        if (*(int *)(param_2 + 0x180) == 3) {
          return 1;
        }
        if (*(int *)(param_2 + 0x180) == 2) {
          return 1;
        }
        if (*(int *)(param_2 + 0x180) == 5) {
          return 1;
        }
        if (*(int *)(param_2 + 0x180) == 4) {
          return 1;
        }
        return 0;
      }
      if ((uVar2 & 0x440000) != 0) {
        if (((*(int *)(param_2 + 0x17c) == 0) && (*(int *)(param_2 + 0x184) == 0)) &&
           ((*(int *)(param_2 + 0x188) == 0 && (*(char *)(param_2 + 0x18c) == '\0')))) {
          return 1;
        }
        return 0;
      }
      goto switchD_001ebb7c_default;
    }
switchD_001ebb7c_caseD_0:
    if (((*(int *)(param_2 + 0x17c) != 0) || (*(int *)(param_2 + 0x180) != 0)) ||
       ((*(int *)(param_2 + 0x184) != 0 ||
        ((*(int *)(param_2 + 0x188) != 0 || (*(char *)(param_2 + 0x18c) != '\0')))))) {
      return 0;
    }
  }
  return 1;
}

