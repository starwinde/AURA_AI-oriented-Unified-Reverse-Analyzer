
int aura_detect_format(char *param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  
  if (param_1 != (char *)0x0 && 3 < param_2) {
    cVar3 = *param_1;
    cVar4 = param_1[1];
    cVar5 = param_1[2];
    cVar6 = param_1[3];
    if (cVar3 == '\x7f' && cVar4 == 'E') {
      if (cVar5 == 'L' && cVar6 == 'F') {
        return 1;
      }
    }
    else if (cVar3 == -2 && cVar4 == -0x13) {
      if (cVar5 != -6) {
        return 4;
      }
      if ((byte)(cVar6 + 0x32U) < 2) {
        return 3;
      }
    }
    else {
      if ((cVar6 == -2 && cVar5 == -0x13) && cVar4 == -6) {
        return (1 < (byte)(cVar3 + 0x32U)) + 3;
      }
      if (cVar3 == -0x36 && cVar4 == -2) {
        return 4 - (uint)(cVar5 == -0x46 && cVar6 == -0x42);
      }
      if (cVar3 == 'd' && cVar4 == 'e') {
        return (cVar5 == 'x' && cVar6 == '\n') + 4;
      }
    }
    if ((cVar3 == 'M' && cVar4 == 'Z') && 0x177 < param_2) {
      uVar2 = *(uint *)(param_1 + 0x3c);
      iVar7 = 2;
      if ((((uVar2 + 0xe8 <= param_2) && (param_1[uVar2] == 'P')) && (param_1[uVar2 + 1] == 'E')) &&
         ((param_1[uVar2 + 2] == '\0' && (param_1[uVar2 + 3] == '\0')))) {
        uVar1 = uVar2 + 0xf8;
        if (CONCAT11(param_1[uVar2 + 0x19],param_1[uVar2 + 0x18]) != 0x20b) {
          uVar1 = uVar2 + 0xe8;
        }
        if ((uVar1 + 8 <= param_2) &&
           (iVar7 = 6,
           (param_1[uVar1 + 2] == '\0' && param_1[uVar1 + 1] == '\0') &&
           (param_1[uVar1] == '\0' && param_1[uVar1 + 3] == '\0'))) {
          iVar7 = 2;
        }
      }
      return iVar7;
    }
  }
  return 4;
}

