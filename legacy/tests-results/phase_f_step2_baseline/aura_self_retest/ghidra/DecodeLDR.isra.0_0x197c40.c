
undefined4 DecodeLDR_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  
  uVar1 = param_2 >> 0xc & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar6 = 1;
  uVar4 = uVar6;
  if ((param_2 & 0xf00) == 0 && uVar2 != uVar1) {
    uVar4 = 3;
  }
  if (uVar1 == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
    if (uVar2 != 0xf) goto LAB_00197c9c;
LAB_00197d6c:
    uVar6 = 1;
    uVar5 = 0xb;
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    uVar6 = uVar4;
    if (uVar2 == 0xf) goto LAB_00197d6c;
LAB_00197c9c:
    uVar5 = *(undefined2 *)(GPR + (ulong)uVar2 * 2);
    MCOperand_CreateReg0(param_1,uVar5);
  }
  MCOperand_CreateReg0(param_1,uVar5);
  uVar1 = (param_2 & 0x800000) >> 0x17;
  if ((param_2 & 0xf) == 0xf) {
    MCOperand_CreateReg0(param_1,0xb);
    uVar6 = 1;
    MCOperand_CreateImm0(param_1,uVar1);
  }
  else {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(param_2 & 0xf) * 2));
    MCOperand_CreateImm0(param_1,uVar1);
  }
  param_2 = param_2 >> 0x1c;
  if (param_2 == 0xf) {
LAB_00197da4:
    uVar6 = 0;
  }
  else {
    iVar3 = MCInst_getOpcode(param_1);
    if (iVar3 == 0xc4f) {
      if (param_2 == 0xe) goto LAB_00197da4;
      MCOperand_CreateImm0(param_1,param_2);
    }
    else {
      MCOperand_CreateImm0(param_1,param_2);
      if (param_2 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return uVar6;
      }
    }
    MCOperand_CreateReg0(param_1,3);
  }
  return uVar6;
}

