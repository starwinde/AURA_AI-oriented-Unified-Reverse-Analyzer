
undefined8 FUN_0019635c(undefined8 param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  if ((param_2 & 0xf) == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
    uVar2 = 1;
  }
  else {
    uVar2 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 & 0xf) * 2));
  }
  if (param_2 >> 8 == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
    uVar2 = 1;
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 >> 8) * 2));
  }
  uVar1 = (param_2 >> 5 & 3) - 1;
  if (2 < uVar1) {
    MCOperand_CreateImm0(param_1,2);
    return uVar2;
  }
  MCOperand_CreateImm0(param_1,*(undefined4 *)(CSWTCH_1048 + (ulong)uVar1 * 4));
  return uVar2;
}

