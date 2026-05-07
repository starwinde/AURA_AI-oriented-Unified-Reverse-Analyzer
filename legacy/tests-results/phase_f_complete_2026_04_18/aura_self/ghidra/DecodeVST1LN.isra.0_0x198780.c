
uint DecodeVST1LN_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  long lVar4;
  
  uVar3 = param_2 >> 10 & 3;
  if (uVar3 == 1) {
    if ((param_2 >> 5 & 1) != 0) {
      return 0;
    }
    lVar4 = ((ulong)(param_2 >> 4) & 1) << 1;
    uVar3 = param_2 >> 6 & 3;
  }
  else if (uVar3 == 2) {
    if ((param_2 >> 6 & 1) != 0) {
      return 0;
    }
    uVar3 = param_2 >> 7 & 1;
    if ((param_2 >> 4 & 3) == 0) {
      lVar4 = 0;
    }
    else {
      if ((param_2 >> 4 & 3) != 3) {
        return param_2 & 0x40;
      }
      lVar4 = 4;
    }
  }
  else {
    if (uVar3 != 0) {
      return 0;
    }
    if ((param_2 >> 4 & 1) != 0) {
      return 0;
    }
    uVar3 = param_2 >> 5 & 7;
    lVar4 = 0;
  }
  uVar1 = param_2 & 0xf;
  uVar2 = *(undefined2 *)(GPR + ((ulong)(param_2 >> 0x10) & 0xf) * 2);
  if (uVar1 == 0xf) {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,lVar4);
  }
  else {
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,lVar4);
    if (uVar1 == 0xd) {
      MCOperand_CreateReg0(param_1,0);
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
  }
  MCOperand_CreateReg0
            (param_1,*(undefined2 *)
                      (DPR + (ulong)(param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) * 2));
  MCOperand_CreateImm0(param_1,uVar3);
  return 3;
}

