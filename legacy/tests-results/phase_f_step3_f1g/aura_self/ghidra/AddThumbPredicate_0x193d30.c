
undefined8 AddThumbPredicate(long param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  char cVar9;
  undefined8 uVar10;
  
  uVar2 = MCInst_getOpcode(param_2);
  if (uVar2 == 0xaf7) {
    MCInst_getOperand(param_2,0);
    lVar8 = MCOperand_getImm();
    if (lVar8 == 0x10) {
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar10 = 1;
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar10 = 3;
    }
LAB_00193ec4:
    if (uVar2 != 0) goto LAB_00193dac;
    uVar4 = MCInst_getOpcode(param_2);
    cVar9 = '\x0e';
    lVar8 = *(long *)(ARMInsts + (uVar4 & 0xffffffff) * 0x10 + 8);
    uVar4 = MCInst_getOpcode(param_2);
    uVar2 = (uint)(byte)ARMInsts[(uVar4 & 0xffffffff) * 0x10];
    if (uVar2 != 0) goto LAB_00193df8;
    uVar7 = 1;
    uVar5 = MCOperand_CreateImm1(param_2,0xe);
    MCInst_insert0(param_2,0,uVar5);
  }
  else {
    if (0xaf7 < uVar2) {
      if (uVar2 < 0xc0c) {
        if (0xc09 < uVar2) goto LAB_00193f90;
      }
      else if (uVar2 - 0xc46 < 0x36) {
        uVar4 = 1L << ((ulong)(uVar2 - 0xc46) & 0x3f);
        if ((uVar4 & 0x20004000010e00) != 0) goto LAB_00193d98;
        if ((uVar4 & 1) != 0) goto LAB_00193f90;
      }
LAB_00193eb8:
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar10 = 3;
      goto LAB_00193ec4;
    }
    if (uVar2 == 0xad3) {
LAB_00193f90:
      uVar2 = *(uint *)(param_1 + 0x5c);
      if (uVar2 < 2) {
        uVar10 = 3;
        goto LAB_00193ec4;
      }
    }
    else {
      if ((uVar2 < 0xad3) || ((uVar2 != 0xada && (2 < uVar2 - 0xae5)))) goto LAB_00193eb8;
LAB_00193d98:
      uVar2 = *(uint *)(param_1 + 0x5c);
      if (uVar2 == 0) {
        return 3;
      }
    }
    uVar10 = 1;
LAB_00193dac:
    cVar9 = *(char *)(param_1 + 0x54 + (ulong)(uVar2 - 1));
    if (cVar9 == '\x0f') {
      cVar9 = '\x0e';
    }
    *(uint *)(param_1 + 0x5c) = uVar2 - 1;
    uVar4 = MCInst_getOpcode(param_2);
    lVar8 = *(long *)(ARMInsts + (uVar4 & 0xffffffff) * 0x10 + 8);
    uVar4 = MCInst_getOpcode(param_2);
    uVar2 = (uint)(byte)ARMInsts[(uVar4 & 0xffffffff) * 0x10];
    if (ARMInsts[(uVar4 & 0xffffffff) * 0x10] == 0) {
      uVar3 = 0;
      uVar1 = 1;
    }
    else {
LAB_00193df8:
      uVar7 = 0;
      do {
        uVar6 = uVar7;
        uVar3 = MCInst_getNumOperands(param_2);
        uVar7 = uVar6 + 1;
        uVar1 = uVar7;
        if (uVar3 == uVar6) goto LAB_00193e38;
        uVar4 = MCOperandInfo_isPredicate(lVar8);
        if ((uVar4 & 1) != 0) {
          uVar5 = MCOperand_CreateImm1(param_2,cVar9);
          MCInst_insert0(param_2,uVar6,uVar5);
          if (cVar9 != '\x0e') goto LAB_00193e5c;
          uVar5 = 0;
          goto LAB_00193e60;
        }
        lVar8 = lVar8 + 8;
      } while (uVar7 < uVar2);
      uVar1 = uVar6 + 2;
      uVar3 = uVar7;
    }
LAB_00193e38:
    uVar7 = uVar1;
    uVar5 = MCOperand_CreateImm1(param_2,cVar9);
    MCInst_insert0(param_2,uVar3,uVar5);
    if (cVar9 != '\x0e') {
LAB_00193e5c:
      uVar5 = 3;
      goto LAB_00193e60;
    }
  }
  uVar5 = 0;
LAB_00193e60:
  uVar5 = MCOperand_CreateReg1(param_2,uVar5);
  MCInst_insert0(param_2,uVar7,uVar5);
  return uVar10;
}

