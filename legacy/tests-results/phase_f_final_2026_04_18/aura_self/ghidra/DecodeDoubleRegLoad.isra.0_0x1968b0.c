
uint DecodeDoubleRegLoad_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  param_2 = param_2 & 0xffffffff;
  uVar2 = (uint)(param_2 >> 0x10) & 0xf;
  uVar5 = 3;
  if (uVar2 == 0xf) {
    uVar5 = 1;
  }
  if (((uint)(param_2 >> 0xc) & 0xf) < 0xe) {
    uVar1 = (uint)(param_2 >> 0xc) & 1;
    if ((param_2 >> 0xc & 1) == 0) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPRPair + (param_2 >> 0xc & 0xe)));
      uVar1 = uVar5;
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPRPair + (param_2 >> 0xc & 0xe)));
    }
    param_2 = param_2 >> 0x1c;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    iVar4 = (int)param_2;
    if (iVar4 != 0xf) {
      iVar3 = MCInst_getOpcode(param_1);
      if (iVar3 == 0xc4f) {
        if (iVar4 == 0xe) {
          return 0;
        }
        MCOperand_CreateImm0(param_1,param_2);
      }
      else {
        MCOperand_CreateImm0(param_1,param_2);
        if (iVar4 == 0xe) {
          MCOperand_CreateReg0(param_1,0);
          return uVar1;
        }
      }
      MCOperand_CreateReg0(param_1,3);
      return uVar1;
    }
  }
  return 0;
}

