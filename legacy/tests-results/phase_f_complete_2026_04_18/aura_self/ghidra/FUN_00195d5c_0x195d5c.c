
undefined8 FUN_00195d5c(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if ((param_2 & 0xc00) != 0) {
    uVar1 = param_2 & 0x7f | 0x80;
    uVar2 = param_2 >> 7 & 0x1f;
    MCOperand_CreateImm0(param_1,uVar1 >> uVar2 | uVar1 << 0x20 - uVar2);
    return 3;
  }
  uVar1 = param_2 >> 8;
  param_2 = param_2 & 0xff;
  if (uVar1 == 2) {
    MCOperand_CreateImm0(param_1,param_2 * 0x1000100);
    return 3;
  }
  if (uVar1 == 3) {
    MCOperand_CreateImm0(param_1,param_2 * 0x1010101);
    return 3;
  }
  if (uVar1 != 1) {
    MCOperand_CreateImm0(param_1,param_2);
    return 3;
  }
  MCOperand_CreateImm0(param_1,param_2 * 0x10001);
  return 3;
}

