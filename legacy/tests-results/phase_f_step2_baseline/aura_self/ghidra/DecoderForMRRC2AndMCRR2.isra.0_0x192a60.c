
undefined4 DecoderForMRRC2AndMCRR2_isra_0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  int iVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  
  uVar2 = param_2 & 0xffffffff;
  uVar3 = 0;
  uVar5 = uVar2 >> 0xc & 0xf;
  uVar7 = uVar2 >> 0x10 & 0xf;
  if (((uint)(param_2 >> 8) & 0xe) != 10) {
    iVar4 = (int)uVar5;
    iVar6 = (int)uVar7;
    uVar3 = 1;
    if (iVar4 != iVar6) {
      uVar3 = 3;
    }
    iVar1 = MCInst_getOpcode();
    if (iVar1 == 0x2b5) {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_1,0xb);
        uVar3 = 1;
      }
      else {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
      }
      if (iVar6 == 0xf) {
        uVar3 = 1;
        MCOperand_CreateReg0(param_1,0xb);
      }
      else {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar7 * 2));
      }
    }
    MCOperand_CreateImm0(param_1,param_2 >> 8 & 0xf);
    MCOperand_CreateImm0(param_1,uVar2 >> 4 & 0xf);
    iVar1 = MCInst_getOpcode(param_1);
    if (iVar1 == 0x2a7) {
      if (iVar4 == 0xf) {
        uVar3 = 1;
        MCOperand_CreateReg0(param_1,0xb);
      }
      else {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
      }
      if (iVar6 == 0xf) {
        uVar3 = 1;
        MCOperand_CreateReg0(param_1,0xb);
      }
      else {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar7 * 2));
      }
    }
    MCOperand_CreateImm0(param_1,param_2 & 0xf);
  }
  return uVar3;
}

