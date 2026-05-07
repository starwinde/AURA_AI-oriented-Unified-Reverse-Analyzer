
undefined4 DecodeLDRPreImm_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  uVar4 = param_2 & 0xfff;
  uVar5 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar6 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar1 = param_2 >> 0x1c;
  uVar7 = 3;
  if ((int)uVar6 == 0xf || (int)uVar6 == (int)uVar5) {
    uVar7 = 1;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar6 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar6 * 2));
  if (((param_2 >> 0x17 & 1) == 0) && (bVar2 = uVar4 == 0, uVar4 = -uVar4, bVar2)) {
    uVar4 = 0x80000000;
  }
  MCOperand_CreateImm0(param_1,uVar4);
  if (uVar1 != 0xf) {
    iVar3 = MCInst_getOpcode(param_1);
    if (iVar3 == 0xc4f) {
      if (uVar1 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,uVar1);
    }
    else {
      MCOperand_CreateImm0(param_1,uVar1);
      if (uVar1 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return uVar7;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return uVar7;
  }
  return 0;
}

