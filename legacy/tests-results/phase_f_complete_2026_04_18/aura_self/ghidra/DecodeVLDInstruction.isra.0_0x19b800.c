
undefined8 DecodeVLDInstruction_isra_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar3 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar1 = MCInst_getOpcode();
  if (uVar1 < 0x5e7) {
    if (uVar1 < 0x5de) {
      if ((0x1b < uVar1 - 0x596) || ((0xc3870e1UL >> ((ulong)(uVar1 - 0x596) & 0x3f) & 1) == 0))
      goto LAB_0019b8e0;
LAB_0019b854:
      if (uVar3 == 0x1f) {
        return 0;
      }
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPair + (ulong)uVar3 * 2));
      goto LAB_0019b8fc;
    }
    if (0x1d < uVar3) {
      return 0;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPairSpc + (ulong)uVar3 * 2));
    uVar1 = MCInst_getOpcode(param_1);
    if (0x646 < uVar1) goto LAB_0019b8a8;
LAB_0019b90c:
    if (0x62d < uVar1) {
      uVar1 = uVar1 - 0x62e;
joined_r0x0019b8c8:
      uVar4 = 1L << ((ulong)uVar1 & 0x3f);
      if ((uVar4 & 0x14a5000) == 0) {
        if ((uVar4 & 0x999) == 0) goto LAB_0019b958;
        iVar2 = 1;
      }
      else {
        iVar2 = 2;
      }
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)(uVar3 + iVar2) & 0x1f) * 2));
    }
  }
  else {
    if (uVar1 - 0x5e7 < 9) goto LAB_0019b854;
LAB_0019b8e0:
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar3 * 2));
LAB_0019b8fc:
    uVar1 = MCInst_getOpcode(param_1);
    if (uVar1 < 0x647) goto LAB_0019b90c;
LAB_0019b8a8:
    uVar1 = uVar1 - 0x675;
    if (uVar1 < 0x19) goto joined_r0x0019b8c8;
  }
LAB_0019b958:
  uVar1 = MCInst_getOpcode(param_1);
  if (uVar1 < 0x647) {
    if (0x62d < uVar1) {
      uVar4 = 1L << ((ulong)(uVar1 - 0x62e) & 0x3f);
      if ((uVar4 & 0x14a5000) == 0) goto LAB_0019b98c;
LAB_0019bb00:
      uVar1 = uVar3 + 4;
LAB_0019b99c:
      MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)uVar1 & 0x1f) * 2));
    }
  }
  else if (uVar1 - 0x675 < 0x19) {
    uVar4 = 1L << ((ulong)(uVar1 - 0x675) & 0x3f);
    if ((uVar4 & 0x14a5000) != 0) goto LAB_0019bb00;
LAB_0019b98c:
    if ((uVar4 & 0x999) != 0) {
      uVar1 = uVar3 + 2;
      goto LAB_0019b99c;
    }
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (iVar2 - 0x675U < 0x19) {
    uVar4 = 1L << ((ulong)(iVar2 - 0x675U) & 0x3f);
    if ((uVar4 & 0x14a5000) == 0) {
      uVar3 = uVar3 + 3;
      if ((uVar4 & 0x999) == 0) goto LAB_0019ba08;
    }
    else {
      uVar3 = uVar3 + 6;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)uVar3 & 0x1f) * 2));
  }
LAB_0019ba08:
  uVar4 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0x647) {
    if (0x630 < uVar3) {
      if ((0x210911UL >> ((ulong)(uVar3 - 0x631) & 0x3f) & 1) != 0) goto LAB_0019bb24;
      goto LAB_0019ba60;
    }
    if (uVar3 < 0x5b2) {
      if (0x573 < uVar3) {
        uVar5 = 0x3060c183cc7860f3 >> ((ulong)(uVar3 - 0x574) & 0x3f);
        goto joined_r0x0019bc30;
      }
      if (uVar3 < 0x56b) {
        if (uVar3 < 0x569) goto LAB_0019ba60;
        goto LAB_0019ba50;
      }
      if (uVar3 - 0x56d < 4) goto LAB_0019ba50;
    }
    else {
      if (0x22 < uVar3 - 0x5df) goto LAB_0019ba60;
      uVar5 = 0x61861b6db >> ((ulong)(uVar3 - 0x5df) & 0x3f);
joined_r0x0019bc30:
      if ((uVar5 & 1) != 0) {
LAB_0019ba50:
        MCOperand_CreateImm0(param_1,0);
      }
    }
LAB_0019ba60:
    uVar5 = (ulong)(param_2 >> 4) & 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    if ((int)uVar5 == 0) goto LAB_0019ba7c;
LAB_0019bb58:
    uVar4 = (ulong)(param_2 & 0xf);
    MCOperand_CreateImm0(param_1,(long)(4 << uVar5));
    uVar3 = MCInst_getOpcode(param_1);
    if (0x5b1 < uVar3) goto LAB_0019bb80;
LAB_0019ba9c:
    if (uVar3 < 0x574) {
      if (7 < uVar3 - 0x569) goto LAB_0019bba0;
      uVar5 = 0xd1L >> ((ulong)(uVar3 - 0x569) & 0x3f);
    }
    else {
      uVar5 = 0x3060c183446820d1 >> ((ulong)(uVar3 - 0x574) & 0x3f);
    }
    if ((uVar5 & 1) != 0) goto LAB_0019bac0;
  }
  else {
    if ((0x15 < uVar3 - 0x678) || ((0x210911UL >> ((ulong)(uVar3 - 0x678) & 0x3f) & 1) == 0))
    goto LAB_0019ba60;
LAB_0019bb24:
    uVar5 = (ulong)(param_2 >> 4) & 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
    if ((int)uVar5 != 0) goto LAB_0019bb58;
LAB_0019ba7c:
    MCOperand_CreateImm0(param_1,0);
    uVar4 = (ulong)(param_2 & 0xf);
    uVar3 = MCInst_getOpcode(param_1);
    if (uVar3 < 0x5b2) goto LAB_0019ba9c;
LAB_0019bb80:
    if ((uVar3 - 0x5df < 0x22) && ((0x208209249U >> ((ulong)(uVar3 - 0x5df) & 0x3f) & 1) != 0)) {
      return 3;
    }
  }
LAB_0019bba0:
  if ((int)uVar4 == 0xd) {
    MCOperand_CreateReg0(param_1,0);
    return 3;
  }
LAB_0019bac0:
  if ((param_2 & 0xd) != 0xd) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar4 * 2));
  }
  return 3;
}

