
undefined8 FUN_0019791c(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined2 uVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (ulong)(param_2 >> 0xc) & 0xf;
  iVar2 = MCInst_getOpcode();
  if (iVar2 == 0x2ab) {
    if ((int)uVar4 != 0xf) {
      uVar3 = *(undefined2 *)(GPR + uVar4 * 2);
      MCOperand_CreateReg0(param_1,uVar3);
      goto LAB_00197960;
    }
    MCOperand_CreateReg0(param_1,0xb);
  }
  else if ((int)uVar4 != 0xf) {
    uVar3 = *(undefined2 *)(GPR + uVar4 * 2);
LAB_00197960:
    uVar5 = 3;
    MCOperand_CreateReg0(param_1,uVar3);
    goto LAB_00197970;
  }
  uVar5 = 1;
  MCOperand_CreateReg0(param_1,0xb);
LAB_00197970:
  uVar1 = param_2 >> 0x1c;
  MCOperand_CreateImm0(param_1,param_2 & 0xfff | (param_2 & 0xf0000) >> 4);
  if (uVar1 == 0xf) {
    return 0;
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 == 0xc4f) {
    if (uVar1 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,uVar1);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar1);
    if (uVar1 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      return uVar5;
    }
  }
  MCOperand_CreateReg0(param_1,3);
  return uVar5;
}

