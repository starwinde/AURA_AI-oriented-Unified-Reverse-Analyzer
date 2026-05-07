
uint DecodeCPSInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar2 = (uint)param_2;
  if ((param_2 & 0x10020) != 0) {
    return 0;
  }
  uVar4 = param_2 >> 0x12 & 3;
  iVar3 = (int)uVar4;
  if ((uVar2 & 0xff00000) != 0x1000000 || iVar3 == 1) {
    return uVar2 & 0x10020;
  }
  uVar5 = param_2 >> 6 & 7;
  uVar1 = uVar2 & 0x1f;
  if ((iVar3 != 0) == 0 || (param_2 >> 0x11 & 1) == 0) {
    if (((uint)(iVar3 != 0) & (uVar2 >> 0x11 ^ 0xffffffff)) == 0) {
      if (iVar3 == 0 && (param_2 >> 0x11 & 1) != 0) {
        MCInst_setOpcode(param_1,0x23f);
        MCOperand_CreateImm0(param_1,uVar1);
        if ((int)uVar5 == 0) goto LAB_00194d60;
      }
      else {
        MCInst_setOpcode(param_1,0x23f);
        MCOperand_CreateImm0(param_1,uVar1);
      }
    }
    else {
      MCInst_setOpcode(param_1,0x240);
      MCOperand_CreateImm0(param_1,uVar4);
      MCOperand_CreateImm0(param_1,uVar5);
      if ((param_2 & 0x1f) == 0) goto LAB_00194d60;
    }
    uVar2 = 1;
  }
  else {
    MCInst_setOpcode(param_1,0x241);
    MCOperand_CreateImm0(param_1,uVar4);
    MCOperand_CreateImm0(param_1,uVar5);
    MCOperand_CreateImm0(param_1,uVar1);
LAB_00194d60:
    uVar2 = 3;
  }
  return uVar2;
}

