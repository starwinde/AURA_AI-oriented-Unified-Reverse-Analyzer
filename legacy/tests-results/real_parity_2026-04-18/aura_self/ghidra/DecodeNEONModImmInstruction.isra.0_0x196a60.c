
undefined8 DecodeNEONModImmInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  undefined2 uVar5;
  
  uVar4 = (uint)param_2;
  uVar2 = param_2 >> 0xc;
  uVar3 = ((uint)(param_2 >> 0x18) & 1) << 7 | (uVar4 & 0x70000) >> 0xc |
          uVar4 & 0xf00 | ((uint)(param_2 >> 5) & 1) << 0xc | uVar4 & 0xf;
  uVar1 = (uint)uVar2 & 0xf | (uVar4 & 0x400000) >> 0x12;
  if ((uVar4 >> 6 & 1) == 0) {
    uVar5 = *(undefined2 *)(DPR + (ulong)uVar1 * 2);
    MCOperand_CreateReg0(param_1,uVar5);
    MCOperand_CreateImm0(param_1,uVar3);
    uVar3 = MCInst_getOpcode(param_1);
    if (uVar3 < 0x777) {
      if (0x774 < uVar3) goto LAB_00196b20;
      if (uVar3 < 0x40e) {
        if (uVar3 < 0x40c) {
          return 3;
        }
        goto LAB_00196b20;
      }
      uVar3 = uVar3 - 0x40e;
    }
    else {
      uVar3 = uVar3 - 0x777;
    }
    if (1 < uVar3) {
      return 3;
    }
    if ((uVar2 & 1) != 0) {
      return 0;
    }
    uVar5 = *(undefined2 *)(QPR + (ulong)(uVar1 >> 1) * 2);
    goto LAB_00196b20;
  }
  if ((uVar2 & 1) != 0) {
    return 0;
  }
  uVar5 = *(undefined2 *)(QPR + (ulong)(uVar1 >> 1) * 2);
  MCOperand_CreateReg0(param_1,uVar5);
  MCOperand_CreateImm0(param_1,uVar3);
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0x777) {
    if (uVar3 < 0x775) {
      if (0x40d < uVar3) {
        uVar3 = uVar3 - 0x40e;
        goto joined_r0x00196bbc;
      }
      if (uVar3 < 0x40c) {
        return 3;
      }
    }
    uVar5 = *(undefined2 *)(DPR + (ulong)uVar1 * 2);
  }
  else {
    uVar3 = uVar3 - 0x777;
joined_r0x00196bbc:
    if (1 < uVar3) {
      return 3;
    }
  }
LAB_00196b20:
  MCOperand_CreateReg0(param_1,uVar5);
  return 3;
}

