
undefined8 ZydisValidateRexType(long param_1,uint param_2,char param_3)

{
  char cVar1;
  int iVar2;
  
  if (param_2 < 0x25) {
    if (8 < param_2) {
      if (*(int *)(param_1 + 0x30) == 0) {
        *(undefined4 *)(param_1 + 0x30) = 1;
        return 1;
      }
      if (*(int *)(param_1 + 0x30) != 2) {
        return 1;
      }
      return 0;
    }
    if (param_2 < 5) {
      if (param_2 != 0) {
        return 1;
      }
    }
    else if (param_2 - 5 < 4) {
      if (*(int *)(param_1 + 0x30) == 0) {
        *(undefined4 *)(param_1 + 0x30) = 2;
        return 1;
      }
      if (*(int *)(param_1 + 0x30) != 1) {
        return 1;
      }
      return 0;
    }
  }
  cVar1 = ZydisRegisterGetId(param_2);
  if (('\a' < cVar1) || ((param_3 == '\0' && (iVar2 = ZydisRegisterGetClass(param_2), iVar2 == 4))))
  {
    if (*(int *)(param_1 + 0x30) == 0) {
      *(undefined4 *)(param_1 + 0x30) = 1;
    }
    else if (*(int *)(param_1 + 0x30) == 2) {
      return 0;
    }
  }
  return 1;
}

