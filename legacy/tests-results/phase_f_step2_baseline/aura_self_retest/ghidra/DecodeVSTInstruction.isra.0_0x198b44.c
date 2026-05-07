
undefined8 DecodeVSTInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  uint uVar7;
  
  uVar7 = (uint)param_2;
  uVar1 = uVar7 & 0xf;
  uVar3 = (uint)((param_2 & 0xffffffff) >> 0x10) & 0xf;
  uVar2 = MCInst_getOpcode();
  if (uVar2 < 0xa03) {
    if (0x9c3 < uVar2) {
      uVar5 = 1L << ((ulong)(uVar2 - 0x9c4) & 0x3f);
      if ((uVar5 & 0x61861b6db) != 0) goto LAB_00198bb0;
      uVar5 = uVar5 & 0x4400000000000000;
      goto joined_r0x00198cb8;
    }
    if (uVar2 < 0x9af) {
      if (uVar2 < 0x971) {
        if (uVar2 < 0x968) {
          if (0x965 < uVar2) goto LAB_00198bb0;
        }
        else if (uVar2 - 0x96a < 4) {
LAB_00198bb0:
          if (uVar1 == 0xf) {
            return 0;
          }
          MCOperand_CreateImm0(param_1,0);
        }
      }
      else if ((0x3060c183cc7860f3U >> ((ulong)(uVar2 - 0x971) & 0x3f) & 1) != 0) goto LAB_00198bb0;
    }
  }
  else {
    if (0x3c < uVar2 - 0xa06) goto LAB_00198bc8;
    uVar5 = 0x1084888000002109U >> ((ulong)(uVar2 - 0xa06) & 0x3f) & 1;
joined_r0x00198cb8:
    if (uVar5 != 0) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar3 * 2));
    }
  }
LAB_00198bc8:
  uVar2 = (uVar7 & 0x30) >> 4;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar3 * 2));
  if (uVar2 == 0) {
    MCOperand_CreateImm0(param_1,0);
    uVar3 = MCInst_getOpcode(param_1);
    if (0x9a6 < uVar3) goto LAB_00198ce4;
LAB_00198c00:
    if (0x969 < uVar3) {
      uVar5 = 0x102040a214102885 >> ((ulong)(uVar3 - 0x96a) & 0x3f);
      goto joined_r0x00198d04;
    }
    if (uVar3 == 0x966) goto LAB_00198c24;
    if (uVar1 != 0xd) goto LAB_00198d10;
LAB_00198f70:
    MCOperand_CreateReg0(param_1,0);
  }
  else {
    MCOperand_CreateImm0(param_1,(long)(4 << (ulong)uVar2));
    uVar3 = MCInst_getOpcode(param_1);
    if (uVar3 < 0x9a7) goto LAB_00198c00;
LAB_00198ce4:
    if (uVar3 - 0x9ad < 0x39) {
      uVar5 = 0x104104924800001 >> ((ulong)(uVar3 - 0x9ad) & 0x3f);
joined_r0x00198d04:
      if ((uVar5 & 1) == 0) goto LAB_00198d08;
    }
    else {
LAB_00198d08:
      if (uVar1 == 0xd) goto LAB_00198f70;
LAB_00198d10:
      if (uVar1 != 0xf) {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
      }
    }
  }
LAB_00198c24:
  uVar1 = (uint)((param_2 & 0xffffffff) >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
  iVar4 = MCInst_getOpcode(param_1);
  if (iVar4 == 0x993) {
LAB_00198d7c:
    if (uVar1 == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPair + (ulong)uVar1 * 2));
  }
  else if (iVar4 - 0x998U < 0x3d) {
    uVar5 = 1L << ((ulong)(iVar4 - 0x998U) & 0x3f);
    if ((uVar5 & 0x1ff000000061c387) != 0) goto LAB_00198d7c;
    if ((uVar5 & 0xff80000000000) == 0) goto LAB_00198da0;
    if (0x1d < uVar1) {
      return 0;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPairSpc + (ulong)uVar1 * 2));
  }
  else {
LAB_00198da0:
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (ulong)uVar1 * 2));
  }
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0xa04) {
    if ((0x9fa < uVar3) && ((0x199UL >> ((ulong)(uVar3 - 0x9fb) & 0x3f) & 1) != 0)) {
      uVar5 = (ulong)(uVar1 + 1);
      goto LAB_00198df0;
    }
  }
  else if (uVar3 - 0xa06 < 0x3d) {
    uVar6 = 1L << ((ulong)(uVar3 - 0xa06) & 0x3f);
    uVar5 = (ulong)(uVar1 + 2);
    if ((uVar6 & 0x14a500000000294a) == 0) {
      if ((uVar6 & 0x999000000001) == 0) goto LAB_00198e08;
      uVar5 = (ulong)(uVar1 + 1);
    }
LAB_00198df0:
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (uVar5 & 0x1f) * 2));
  }
LAB_00198e08:
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0xa04) {
    if ((uVar3 < 0x9fb) || ((0x199UL >> ((ulong)(uVar3 - 0x9fb) & 0x3f) & 1) == 0))
    goto LAB_00198e58;
    uVar5 = (ulong)(uVar1 + 2);
  }
  else {
    if (0x3c < uVar3 - 0xa06) goto LAB_00198e58;
    uVar6 = 1L << ((ulong)(uVar3 - 0xa06) & 0x3f);
    uVar5 = (ulong)(uVar1 + 4);
    if ((uVar6 & 0x14a500000000294a) == 0) {
      if ((uVar6 & 0x999000000001) == 0) goto LAB_00198e58;
      uVar5 = (ulong)(uVar1 + 2);
    }
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + (uVar5 & 0x1f) * 2));
LAB_00198e58:
  iVar4 = MCInst_getOpcode(param_1);
  if (iVar4 - 0xa2aU < 0x19) {
    uVar5 = 1L << ((ulong)(iVar4 - 0xa2aU) & 0x3f);
    if ((uVar5 & 0x14a5000) == 0) {
      uVar1 = uVar1 + 3;
      if ((uVar5 & 0x999) == 0) {
        return 3;
      }
    }
    else {
      uVar1 = uVar1 + 6;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + ((ulong)uVar1 & 0x1f) * 2));
  }
  return 3;
}

