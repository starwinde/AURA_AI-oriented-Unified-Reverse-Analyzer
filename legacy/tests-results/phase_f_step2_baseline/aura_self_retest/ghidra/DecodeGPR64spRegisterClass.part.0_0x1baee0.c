
undefined8 DecodeGPR64spRegisterClass_part_0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(GPR64DecoderTable + (param_2 & 0xffffffff) * 4);
  if (iVar1 == 9) {
    iVar1 = 5;
  }
  MCOperand_CreateReg0(param_1,iVar1);
  return 3;
}

