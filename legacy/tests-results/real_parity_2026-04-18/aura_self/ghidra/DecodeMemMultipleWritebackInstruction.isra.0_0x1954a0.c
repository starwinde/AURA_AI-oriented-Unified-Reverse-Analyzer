
undefined8 DecodeMemMultipleWritebackInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  
  uVar9 = param_2 >> 0x1c & 0xf;
  uVar7 = (param_2 & 0xffffffff) >> 0x10 & 0xf;
  iVar8 = (int)uVar9;
  uVar6 = (uint)param_2;
  if (iVar8 == 0xf) {
    uVar3 = MCInst_getOpcode();
    if (uVar3 == 0x350) {
      MCInst_setOpcode(param_1,0x32c);
    }
    else if (uVar3 < 0x351) {
      if (uVar3 == 0x279) {
        MCInst_setOpcode(param_1,0x2df);
      }
      else if (uVar3 < 0x27a) {
        if (uVar3 == 0x277) {
          MCInst_setOpcode(param_1,0x2dd);
        }
        else if (uVar3 == 0x278) {
          MCInst_setOpcode(param_1,0x2de);
        }
        else if (uVar3 == 0x275) {
          MCInst_setOpcode(param_1,0x2db);
        }
        else {
          if (uVar3 != 0x276) {
            return 0;
          }
          MCInst_setOpcode(param_1,0x2dc);
        }
      }
      else if (uVar3 == 0x27b) {
        MCInst_setOpcode(param_1,0x2e1);
      }
      else if (uVar3 == 0x27c) {
        MCInst_setOpcode(param_1,0x2e2);
      }
      else {
        if (uVar3 != 0x27a) {
          return 0;
        }
        MCInst_setOpcode(param_1,0x2e0);
      }
    }
    else if (uVar3 == 0x354) {
      MCInst_setOpcode(param_1,0x330);
    }
    else if (uVar3 < 0x355) {
      if (uVar3 == 0x352) {
        MCInst_setOpcode(param_1,0x32e);
      }
      else if (uVar3 == 0x353) {
        MCInst_setOpcode(param_1,0x32f);
      }
      else {
        MCInst_setOpcode(param_1,0x32d);
      }
    }
    else if (uVar3 == 0x356) {
      MCInst_setOpcode(param_1,0x332);
    }
    else if (uVar3 == 0x357) {
      MCInst_setOpcode(param_1,0x333);
    }
    else {
      if (uVar3 != 0x355) {
        return 0;
      }
      MCInst_setOpcode(param_1,0x331);
    }
    if ((uVar6 >> 0x14 & 1) == 0) {
      if ((uVar6 >> 0x16 & 1) == 0) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,param_2 & 0xf);
      return 3;
    }
    uVar5 = 3;
    uVar6 = ((uint)((param_2 & 0xffffffff) >> 0x17) & 3) - 1;
    if (uVar6 < 3) {
      uVar5 = *(undefined4 *)(CSWTCH_1050 + (ulong)uVar6 * 4);
    }
    MCOperand_CreateImm0(param_1,uVar5);
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar7 * 2));
    return 3;
  }
  uVar1 = *(undefined2 *)(GPR + uVar7 * 2);
  MCOperand_CreateReg0(param_1,uVar1);
  MCOperand_CreateReg0(param_1,uVar1);
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 == 0xc4f) {
    if (iVar8 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_1,uVar9);
  }
  else {
    MCOperand_CreateImm0(param_1,uVar9);
    if (iVar8 == 0xe) {
      MCOperand_CreateReg0(param_1,0);
      goto LAB_00195540;
    }
  }
  MCOperand_CreateReg0(param_1,3);
LAB_00195540:
  uVar4 = DecodeRegListOperand_isra_0(param_1,uVar6 & 0xffff);
  if ((int)uVar4 == 1) {
    return uVar4;
  }
  if ((int)uVar4 != 3) {
    return 0;
  }
  return 3;
}

