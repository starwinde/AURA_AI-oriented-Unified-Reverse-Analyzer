
int fixupReg(long param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar4;
  uint uVar3;
  
  bVar1 = *param_2;
  if (8 < bVar1) {
    if (bVar1 != 0x10) {
      return -1;
    }
    bVar1 = *(byte *)(param_1 + 0x98);
    if (param_2[1] - 2 < 0x1b) {
      uVar2 = (uint)bVar1;
      uVar3 = (uint)bVar1;
      switch((uint)param_2[1]) {
      case 2:
        uVar3 = uVar3 & 0x1f;
        if ((*(char *)(param_1 + 5) != '\0') && ((uVar3 - 4 & 0xff) < 4)) {
          uVar3 = uVar3 + 0xc;
        }
        *(uint *)(param_1 + 0x98) = uVar3;
        return ((bVar1 ^ 0x10) >> 4 & 1) - 1;
      case 3:
        uVar3 = (uVar3 & 0x1f) + 0x14;
        if ((bVar1 >> 4 & 1) != 0) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      case 4:
        uVar3 = (uVar3 & 0x1f) + 0x24;
        if ((bVar1 >> 4 & 1) != 0) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      case 5:
        uVar3 = (uVar3 & 0x1f) + 0x34;
        if ((bVar1 >> 4 & 1) != 0) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      default:
        goto switchD_001dbf34_caseD_6;
      case 0xc:
      case 0x14:
        *(uint *)(param_1 + 0x98) = uVar3 + 0x4c;
        return 0;
      case 0xd:
      case 0x15:
        *(uint *)(param_1 + 0x98) = uVar3 + 0x6c;
        return 0;
      case 0xe:
      case 0x16:
        *(uint *)(param_1 + 0x98) = uVar3 + 0x8c;
        return 0;
      case 0x13:
        *(uint *)(param_1 + 0x98) = (uVar2 & 7) + 0x44;
        return 0;
      case 0x17:
        uVar3 = (uVar2 & 0xf) - 0x54 & 0xff;
        if ((bVar1 >> 3 & 1) != 0) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      case 0x18:
        uVar3 = (uVar2 & 7) - 0x4c & 0xff;
        if (5 < (uVar2 & 7)) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      case 0x19:
        *(uint *)(param_1 + 0x98) = uVar2 + 0xba;
        return 0;
      case 0x1a:
        *(uint *)(param_1 + 0x98) = uVar2 + 0xca;
        return 0;
      case 0x1b:
        uVar3 = uVar2 + 0xda;
        if (3 < uVar2) {
          *(uint *)(param_1 + 0x98) = uVar3;
          return -1;
        }
        break;
      case 0x1c:
        uVar3 = uVar2 + *(int *)(param_1 + 0xc0) & 0xffff;
      }
      *(uint *)(param_1 + 0x98) = uVar3;
      return 0;
    }
switchD_001dbf34_caseD_6:
    *(undefined4 *)(param_1 + 0x98) = 0;
    return -1;
  }
  if (1 < bVar1) {
    uVar3 = *(uint *)(param_1 + 0xbc);
    if (*(uint *)(param_1 + 0xc4) < uVar3) {
      return 0;
    }
    uVar4 = *(uint *)(param_1 + 0xc4) - uVar3;
    uVar2 = uVar4 & 0xff;
    switch(param_2[1]) {
    case 2:
      uVar4 = uVar4 & 0xf;
      if ((*(char *)(param_1 + 5) != '\0') && ((uVar4 - 4 & 0xff) < 4)) {
        *(uint *)(param_1 + 0xc4) = uVar4 + 0x3d;
        return 0;
      }
      *(uint *)(param_1 + 0xc4) = uVar4 + 0x31;
      return 0;
    case 3:
      *(uint *)(param_1 + 0xc4) = (uVar4 & 0xf) + 0x45;
      return 0;
    case 4:
      *(uint *)(param_1 + 0xc4) = (uVar4 & 0xf) + 0x55;
      return 0;
    case 5:
      *(uint *)(param_1 + 0xc4) = (uVar4 & 0xf) + 0x65;
      return 0;
    default:
      *(undefined4 *)(param_1 + 0xc4) = 0;
      return -1;
    case 0xc:
    case 0x14:
      *(uint *)(param_1 + 0xc4) = uVar2 + 0x7d;
      return 0;
    case 0xd:
    case 0x15:
      *(uint *)(param_1 + 0xc4) = uVar2 + 0x9d;
      return 0;
    case 0xe:
    case 0x16:
      *(uint *)(param_1 + 0xc4) = uVar2 + 0xbd;
      return 0;
    case 0x13:
      *(uint *)(param_1 + 0xc4) = (uVar4 & 7) + 0x75;
      return 0;
    case 0x17:
      uVar3 = (uVar4 & 0xf) - 0x23 & 0xff;
      if ((uVar2 >> 3 & 1) != 0) {
        *(uint *)(param_1 + 0xc4) = uVar3;
        return -1;
      }
      break;
    case 0x18:
      uVar3 = (uVar4 & 7) - 0x1b & 0xff;
      if (5 < (uVar4 & 7)) {
LAB_001dc234:
        *(uint *)(param_1 + 0xc4) = uVar3;
        return -1;
      }
      break;
    case 0x19:
      *(uint *)(param_1 + 0xc4) = uVar2 + 0xeb;
      return 0;
    case 0x1a:
      *(uint *)(param_1 + 0xc4) = uVar2 + 0xfb;
      return 0;
    case 0x1b:
      uVar3 = uVar2 + 0x10b;
      if (3 < uVar2) goto LAB_001dc234;
      break;
    case 0x1c:
      *(uint *)(param_1 + 0xc4) = uVar2 + uVar3 & 0xffff;
      return 0;
    }
    *(uint *)(param_1 + 0xc4) = uVar3;
    return 0;
  }
  if (bVar1 != 1) {
    return -1;
  }
  uVar3 = *(int *)(param_1 + 0xcc) - *(int *)(param_1 + 0xc0);
  uVar2 = uVar3 & 0xff;
  switch(param_2[1]) {
  case 2:
    uVar3 = uVar3 & 0x1f;
    if ((*(char *)(param_1 + 5) != '\0') && ((uVar3 - 4 & 0xff) < 4)) {
      uVar3 = uVar3 + 0xc;
    }
    *(uint *)(param_1 + 0xcc) = uVar3;
    return ((uVar2 ^ 0x10) >> 4 & 1) - 1;
  case 3:
    uVar4 = (uVar3 & 0x1f) + 0x14;
    if ((uVar2 >> 4 & 1) != 0) {
      *(uint *)(param_1 + 0xcc) = uVar4;
      return -1;
    }
    goto LAB_001dc098;
  case 4:
    uVar4 = (uVar3 & 0x1f) + 0x24;
    if ((uVar2 >> 4 & 1) != 0) {
      *(uint *)(param_1 + 0xcc) = uVar4;
      return -1;
    }
    goto LAB_001dc098;
  case 5:
    uVar4 = (uVar3 & 0x1f) + 0x34;
    if ((uVar2 >> 4 & 1) != 0) {
LAB_001dc080:
      *(uint *)(param_1 + 0xcc) = uVar4;
      return -1;
    }
    goto LAB_001dc098;
  default:
    *(undefined4 *)(param_1 + 0xcc) = 0;
    return -1;
  case 0xc:
  case 0x14:
    *(uint *)(param_1 + 0xcc) = uVar2 + 0x4c;
    break;
  case 0xd:
  case 0x15:
    *(uint *)(param_1 + 0xcc) = uVar2 + 0x6c;
    break;
  case 0xe:
  case 0x16:
    *(uint *)(param_1 + 0xcc) = uVar2 + 0x8c;
    break;
  case 0x13:
    *(uint *)(param_1 + 0xcc) = (uVar3 & 7) + 0x44;
    break;
  case 0x17:
    uVar4 = (uVar3 & 0xf) - 0x54 & 0xff;
    if ((uVar2 >> 3 & 1) != 0) {
      *(uint *)(param_1 + 0xcc) = uVar4;
      return -1;
    }
    goto LAB_001dc098;
  case 0x18:
    uVar4 = (uVar3 & 7) - 0x4c & 0xff;
    if (5 < (uVar3 & 7)) {
      *(uint *)(param_1 + 0xcc) = uVar4;
      return -1;
    }
    goto LAB_001dc098;
  case 0x19:
    *(uint *)(param_1 + 0xcc) = uVar2 + 0xba;
    break;
  case 0x1a:
    *(uint *)(param_1 + 0xcc) = uVar2 + 0xca;
    break;
  case 0x1b:
    uVar4 = uVar2 + 0xda;
    if (3 < uVar2) goto LAB_001dc080;
LAB_001dc098:
    *(uint *)(param_1 + 0xcc) = uVar4;
    break;
  case 0x1c:
    *(uint *)(param_1 + 0xcc) = uVar2 + *(int *)(param_1 + 0xc0) & 0xffff;
  }
  return 0;
}

