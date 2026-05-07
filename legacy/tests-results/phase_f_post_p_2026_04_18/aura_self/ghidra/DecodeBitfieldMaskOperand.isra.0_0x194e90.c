
undefined8 DecodeBitfieldMaskOperand_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  
  uVar2 = param_2 & 0x1f;
  param_2 = param_2 >> 5;
  if (param_2 < uVar2) {
    uVar3 = 1;
    uVar2 = param_2;
  }
  else {
    uVar3 = 3;
    uVar1 = 0xffffffff;
    if (param_2 == 0x1f) goto LAB_00194ec4;
  }
  uVar1 = (1 << (ulong)(param_2 + 1 & 0x1f)) - 1;
LAB_00194ec4:
  MCOperand_CreateImm0(param_1,(1 << (ulong)(uVar2 & 0x1f)) - 1U ^ uVar1 ^ 0xffffffff);
  return uVar3;
}

