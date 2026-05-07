
undefined8 DecodeAddrModeImm12Operand_isra_0(undefined8 param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  
  uVar2 = param_2 & 0xfff;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 >> 0xd) * 2));
  if (((param_2 >> 0xc & 1) == 0) && (bVar1 = uVar2 == 0, uVar2 = -uVar2, bVar1)) {
    uVar2 = 0x80000000;
  }
  MCOperand_CreateImm0(param_1,uVar2);
  return 3;
}

