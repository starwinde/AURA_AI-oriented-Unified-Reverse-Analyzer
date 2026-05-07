
undefined8 DecodeNEONComplexLane64Instruction_isra_0(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar3 = param_2 >> 0x10 & 0xf | (param_2 & 0x80) >> 3;
  if ((param_2 >> 6 & 1) == 0) {
    uVar1 = *(undefined2 *)(DPR + (ulong)uVar2 * 2);
    MCOperand_CreateReg0(param_1,uVar1);
    MCOperand_CreateReg0(param_1,uVar1);
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar3 * 2));
LAB_00198328:
    MCOperand_CreateReg0
              (param_1,*(undefined2 *)(DPR + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_1,0);
    MCOperand_CreateImm0(param_1,param_2 >> 0x14 & 3);
    return 3;
  }
  if ((param_2 >> 0xc & 1) == 0) {
    uVar1 = *(undefined2 *)(QPR + (ulong)(uVar2 >> 1) * 2);
    MCOperand_CreateReg0(param_1,uVar1);
    MCOperand_CreateReg0(param_1,uVar1);
    if ((param_2 >> 0x10 & 1) == 0) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(QPR + (ulong)(uVar3 >> 1) * 2));
      goto LAB_00198328;
    }
  }
  return 0;
}

