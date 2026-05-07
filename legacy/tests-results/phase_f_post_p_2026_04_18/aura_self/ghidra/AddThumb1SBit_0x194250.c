
void AddThumb1SBit(undefined8 param_1,ulong param_2)

{
  byte bVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  uint uVar6;
  short *psVar7;
  short *psVar8;
  
  uVar3 = MCInst_getOpcode();
  psVar7 = *(short **)(ARMInsts + (uVar3 & 0xffffffff) * 0x10 + 8);
  uVar3 = MCInst_getOpcode(param_1);
  bVar1 = ARMInsts[(uVar3 & 0xffffffff) * 0x10];
  if (bVar1 == 0) {
LAB_00194314:
    uVar6 = 0;
  }
  else {
    uVar6 = 0;
    psVar8 = psVar7;
    do {
      uVar2 = MCInst_getNumOperands(param_1);
      if (uVar2 == uVar6) break;
      uVar3 = MCOperandInfo_isOptionalDef(psVar8);
      if (((uVar3 & 1) != 0) && (*psVar8 == 0xe)) {
        if (uVar6 == 0) goto LAB_00194314;
        uVar3 = MCOperandInfo_isPredicate(psVar7 + (ulong)(uVar6 - 1) * 4);
        if ((uVar3 & 1) == 0) break;
      }
      uVar6 = uVar6 + 1;
      psVar8 = psVar8 + 4;
    } while (uVar6 != bVar1);
  }
  uVar5 = 3;
  if ((param_2 & 1) != 0) {
    uVar5 = 0;
  }
  uVar4 = MCOperand_CreateReg1(param_1,uVar5);
  MCInst_insert0(param_1,uVar6,uVar4);
  return;
}

