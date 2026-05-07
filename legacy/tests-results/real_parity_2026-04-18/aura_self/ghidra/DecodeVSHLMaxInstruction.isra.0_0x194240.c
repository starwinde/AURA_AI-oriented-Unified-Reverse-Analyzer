
undefined8 DecodeVSHLMaxInstruction_isra_0(undefined8 param_1,uint param_2)

{
  if ((param_2 >> 0xc & 1) != 0) {
    return 0;
  }
  MCOperand_CreateReg0
            (param_1,*(undefined2 *)
                      (QPR + (ulong)((param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) >> 1) * 2
                      ));
  MCOperand_CreateReg0
            (param_1,*(undefined2 *)(DPR + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
  MCOperand_CreateImm0(param_1,(long)(8 << ((ulong)(param_2 >> 0x12) & 3)));
  return 3;
}

