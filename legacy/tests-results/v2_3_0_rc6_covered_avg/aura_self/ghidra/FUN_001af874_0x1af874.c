
uint FUN_001af874(undefined4 param_1,long param_2)

{
  uint uVar1;
  
  switch(param_1) {
  case 2:
  case 5:
  case 6:
  case 0xe:
    uVar1 = *(uint *)(param_2 + 4) >> 6 & 1;
    if ((*(uint *)(param_2 + 4) & 0x10) != 0) {
      uVar1 = 0;
    }
    return uVar1;
  default:
    return (*(uint *)(param_2 + 4) ^ 0x10) >> 4 & 1;
  case 4:
    return (uint)((*(uint *)(param_2 + 4) & 0x50) == 0);
  case 0x15:
  case 0x16:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x2c:
  case 0x3c:
  case 0x3d:
  case 0x3e:
  case 0x3f:
  case 0x40:
  case 0x41:
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x49:
    return 1;
  case 0x17:
  case 0x18:
  case 0x46:
  case 0x47:
  case 0x48:
  case 0x4a:
  case 0x4b:
    return *(uint *)(param_2 + 4) >> 6 & 1;
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x24:
  case 0x26:
  case 0x28:
  case 0x29:
  case 0x2b:
  case 0x2d:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x36:
  case 0x37:
  case 0x38:
    return *(uint *)(param_2 + 4) >> 4 & 1;
  case 0x21:
  case 0x23:
  case 0x2e:
  case 0x2f:
  case 0x39:
    return (uint)((*(uint *)(param_2 + 4) & 0x50) == 0x50);
  case 0x22:
  case 0x25:
  case 0x27:
  case 0x2a:
    uVar1 = (*(uint *)(param_2 + 4) ^ 0x20) >> 5 & 1;
    if ((*(uint *)(param_2 + 4) & 0x10) == 0) {
      uVar1 = 0;
    }
    break;
  case 0x35:
    return (uint)((*(uint *)(param_2 + 4) & 0x30) == 0x30);
  case 0x3a:
    uVar1 = (*(uint *)(param_2 + 4) ^ 0x40) >> 6 & 1;
    if ((*(uint *)(param_2 + 4) & 0x10) == 0) {
      uVar1 = 0;
    }
    return uVar1;
  case 0x3b:
    uVar1 = *(uint *)(param_2 + 4) >> 4 & 1;
    if ((*(uint *)(param_2 + 4) & 0x40) != 0) {
      uVar1 = 0;
    }
    return uVar1;
  }
  return uVar1;
}

