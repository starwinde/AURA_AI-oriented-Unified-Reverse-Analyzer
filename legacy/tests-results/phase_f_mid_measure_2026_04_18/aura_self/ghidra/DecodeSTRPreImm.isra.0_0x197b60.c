
undefined4 DecodeSTRPreImm_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  uVar5 = param_2 & 0xfff;
  uVar6 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar2 = param_2 >> 0xc & 0xf;
  uVar7 = 3;
  if ((uint)uVar6 == 0xf || (uint)uVar6 == uVar2) {
    uVar7 = 1;
  }
  uVar1 = param_2 >> 0x1c;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar6 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar6 * 2));
  if (((param_2 >> 0x17 & 1) == 0) && (bVar3 = uVar5 == 0, uVar5 = -uVar5, bVar3)) {
    uVar5 = 0x80000000;
  }
  MCOperand_CreateImm0(param_1,uVar5);
  if (uVar1 != 0xf) {
    iVar4 = MCInst_getOpcode(param_1);
    if (iVar4 == 0xc4f) {
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

