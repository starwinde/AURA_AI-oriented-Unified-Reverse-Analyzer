
undefined8 ZydisIsValidAddressingClass(undefined8 *param_1,uint param_2,undefined4 param_3)

{
  bool bVar1;
  char cVar2;
  undefined8 uVar3;
  
  bVar1 = *(int *)*param_1 == 0;
  if (param_2 < 5) {
    if (param_2 < 3) {
      if (param_2 == 0) {
        return 1;
      }
      if (param_2 != 2) goto LAB_001e6654;
      bVar1 = !bVar1;
    }
    else {
      cVar2 = ZydisRegisterGetId(param_3);
      if ((bVar1) && ('\x0f' < cVar2)) {
        if ((*(byte *)(param_1[1] + 6) & 7) == 0) {
          bVar1 = (*(byte *)(param_1[1] + 8) & 0x18) != 0;
        }
        else if ((*(byte *)(param_1[1] + 6) & 7) != 4) {
          bVar1 = false;
        }
      }
      if (param_2 == 3) {
        bVar1 = (bool)(cVar2 < '\b' | bVar1);
      }
    }
    if ((bVar1) && (cVar2 = ZydisValidateRexType(param_1,param_3,1), cVar2 != '\0')) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
LAB_001e6654:
    uVar3 = 0;
  }
  return uVar3;
}

