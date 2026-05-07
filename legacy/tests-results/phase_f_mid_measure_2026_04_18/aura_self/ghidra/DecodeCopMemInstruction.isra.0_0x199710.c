
undefined8 DecodeCopMemInstruction_isra_0(long param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  
  uVar3 = param_2 & 0xff;
  uVar1 = param_2 >> 0x17 & 1;
  uVar6 = param_2 >> 8 & 0xf;
  uVar2 = MCInst_getOpcode();
  if (uVar2 < 0xb14) {
    if (0xb0b < uVar2) goto joined_r0x0019983c;
    if (uVar2 < 0x275) {
      if (0x26c < uVar2) goto joined_r0x0019983c;
    }
    else if (uVar2 - 0x341 < 8) goto joined_r0x0019983c;
  }
  else {
    if (7 < uVar2 - 0xbd3) goto LAB_00199768;
joined_r0x0019983c:
    if (uVar6 - 10 < 2) {
      return 0;
    }
  }
LAB_00199768:
  if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) != 0 && uVar6 != 0xe) {
    return 0;
  }
  MCOperand_CreateImm0(param_1,uVar6);
  MCOperand_CreateImm0(param_1,param_2 >> 0xc & 0xf);
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + ((ulong)(param_2 >> 0x10) & 0xf) * 2));
  uVar2 = MCInst_getOpcode(param_1);
  if (uVar2 < 0xb14) {
    if (0xb03 < uVar2) {
      uVar5 = 1L << ((ulong)(uVar2 - 0xb04) & 0x3f);
      if ((uVar5 & 0x9999) == 0) {
        if ((uVar5 & 0x4444) != 0) {
          uVar3 = uVar3 | uVar1 << 8;
        }
        goto LAB_001997fc;
      }
LAB_001998e8:
      MCOperand_CreateImm0(param_1,uVar1 << 8 ^ 0x100 | uVar3);
      goto LAB_00199808;
    }
    if (uVar2 < 0x275) {
      if (0x264 < uVar2) {
        uVar2 = uVar2 - 0x265;
LAB_001997d8:
        uVar5 = 1L << ((ulong)uVar2 & 0x3f);
        if ((uVar5 & 0x9999) == 0) goto LAB_001997ec;
        goto LAB_001998e8;
      }
    }
    else {
      uVar2 = uVar2 - 0x339;
      if (uVar2 < 0x10) goto LAB_001997d8;
    }
  }
  else {
    if (0xf < uVar2 - 0xbcb) goto LAB_001997fc;
    uVar5 = 1L << ((ulong)(uVar2 - 0xbcb) & 0x3f);
    if ((uVar5 & 0x9999) != 0) goto LAB_001998e8;
LAB_001997ec:
    if ((uVar5 & 0x4444) != 0) {
      uVar3 = uVar3 | uVar1 << 8;
    }
  }
LAB_001997fc:
  MCOperand_CreateImm0(param_1,uVar3);
LAB_00199808:
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0x275) {
    if (uVar3 < 0x26d) {
      return 3;
    }
  }
  else if (7 < uVar3 - 0x341) {
    return 3;
  }
  param_2 = param_2 >> 0x1c;
  if (param_2 != 0xf) {
    iVar4 = MCInst_getOpcode(param_1);
    if (iVar4 == 0xc4f) {
      if (param_2 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,param_2);
    }
    else {
      MCOperand_CreateImm0(param_1,param_2);
      if (param_2 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return 3;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return 3;
  }
  return 0;
}

