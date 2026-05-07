
undefined8 FUN_00151b10(char *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  *param_2 = 0;
  if (*param_1 == '\0') {
    return 0xb;
  }
  if (((*param_1 == 'e') && (param_1[1] == 'q')) && (param_1[2] == '\0')) {
    return 0xb;
  }
  cVar1 = *param_1;
  if (((cVar1 != 'n') || (param_1[1] != 'e')) || (uVar2 = 0xc, param_1[2] != '\0')) {
    if (cVar1 == 'l') {
      if ((param_1[1] == 't') && (param_1[2] == '\0')) {
        return 0xd;
      }
      if ((param_1[1] == 'e') && (param_1[2] == '\0')) {
        return 0xe;
      }
    }
    if (cVar1 == 'g') {
      if ((param_1[1] == 't') && (param_1[2] == '\0')) {
        return 0x11;
      }
      if ((param_1[1] == 'e') && (param_1[2] == '\0')) {
        return 0x12;
      }
    }
    if (((cVar1 == 'c') && (param_1[1] == 's')) && (param_1[2] == '\0')) {
      return 0x14;
    }
    if (((((((cVar1 != 'h') || (param_1[1] != 's')) || (uVar2 = 0x14, param_1[2] != '\0')) &&
          (((cVar1 != 'c' || (param_1[1] != 'c')) || (uVar2 = 0xf, param_1[2] != '\0')))) &&
         (((cVar1 != 'l' || (param_1[1] != 'o')) || (uVar2 = 0xf, param_1[2] != '\0')))) &&
        (((cVar1 != 'h' || (param_1[1] != 'i')) || (uVar2 = 0x13, param_1[2] != '\0')))) &&
       (((cVar1 != 'l' || (param_1[1] != 's')) || (uVar2 = 0x10, param_1[2] != '\0')))) {
      return 0xc;
    }
  }
  return uVar2;
}

