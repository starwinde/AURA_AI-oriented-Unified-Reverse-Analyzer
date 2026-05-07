
/* WARNING: Type propagation algorithm not settling */

uint DecodeAddrMode3Instruction_isra_0(long param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  ulong uVar9;
  undefined2 uVar10;
  int iVar11;
  ulong uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  uint uVar17;
  ulong uVar18;
  uint local_20;
  uint local_10;
  
  uVar4 = param_2 >> 0x15;
  uVar2 = (uint)(param_2 >> 0x18) & 1 ^ 1;
  uVar16 = param_2 >> 0xc & 0xf;
  uVar18 = param_2 >> 0x10 & 0xf;
  local_10 = (uint)uVar4 & 0x7ff;
  uVar15 = (uint)uVar16;
  local_20 = (uint)(param_2 >> 8) & 0xf;
  uVar13 = ((uint)((param_2 ^ 0x800000) >> 0x17) & 1) << 8;
  uVar12 = param_2 >> 0x1c & 0xf;
  uVar1 = (uint)param_2 & 0xf;
  uVar3 = param_2 >> 0x16;
  uVar7 = (uint)uVar3 & 1;
  uVar5 = MCInst_getOpcode();
  uVar17 = (uint)uVar18;
  iVar11 = (int)uVar12;
  if (uVar5 < 0x288) {
    if (0x284 < uVar5) goto LAB_00197ed0;
LAB_00197dc0:
    uVar5 = 3;
    uVar6 = MCInst_getOpcode(param_1);
    if (0x29a < uVar6) goto LAB_00197ef0;
LAB_00197dd0:
    if (uVar6 < 0x285) goto LAB_00197e28;
    uVar9 = 1L << ((ulong)(uVar6 - 0x285) & 0x3f);
    uVar14 = 1;
    uVar6 = uVar5;
    if ((uVar9 & 0x339000) != 0) {
      if ((uVar7 & uVar17 == 0xf) != 0) {
LAB_001981a8:
        if (uVar15 != 0xf) goto LAB_00197e28;
        goto LAB_00197e2c;
      }
      if ((uVar3 & 1) == 0) {
        if (uVar15 == 0xf || uVar1 == 0xf) {
          uVar6 = uVar14;
        }
        if ((uVar4 & 1) == 0 && uVar2 == 0) goto LAB_00197e30;
        if ((uVar17 == 0xf) != 0 || uVar15 == uVar17) {
          uVar6 = 1;
        }
      }
      else {
        if (uVar15 == 0xf) goto LAB_00197e2c;
        uVar6 = uVar14;
        if ((uVar4 & 1) == 0 && uVar2 == 0 || uVar15 != uVar17) goto LAB_00197e28;
      }
      goto LAB_00197f70;
    }
    if ((uVar9 & 0xc80) != 0) {
      if ((uVar7 & uVar17 == 0xf) != 0) goto LAB_001981a8;
      if (uVar15 == 0xf) {
        uVar5 = uVar14;
      }
      if (((uint)(uVar1 == 0xf) & (uVar7 ^ 1)) != 0) {
        uVar5 = 1;
      }
      uVar14 = uVar5;
      if ((((uVar7 ^ 1) & ((uint)uVar4 & 0x7ff | uVar2)) != 0) &&
         ((uVar17 == 0xf) != 0 || uVar15 == uVar17)) {
        uVar14 = 1;
      }
      goto LAB_00197e2c;
    }
    if ((uVar9 & 7) == 0) goto LAB_00197e28;
    if ((uVar7 & uVar17 == 0xf) != 0) {
      if (uVar15 == 0xe) goto LAB_00197e2c;
      goto LAB_00197e28;
    }
    if ((local_10 & uVar2) != 0) {
      uVar6 = local_10 & uVar2;
    }
    if ((uVar3 & 1) == 0) {
      if ((uVar15 + 1 != 0xf && uVar1 != 0xf) && (uVar15 != uVar1 && uVar1 != uVar15 + 1)) {
        uVar14 = uVar6;
      }
      uVar6 = uVar14;
      if (((uVar4 & 1) != 0 || uVar2 != 0) && (uVar17 == 0xf) != 0) goto LAB_001982b8;
    }
    if ((uVar4 & 1) != 0 || uVar2 != 0) {
      if (uVar15 == uVar17 || uVar17 == uVar15 + 1) {
        uVar6 = 1;
      }
      goto LAB_00197f70;
    }
LAB_00197e30:
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar16 * 2));
    uVar7 = MCInst_getOpcode(param_1);
    if (uVar7 < 0x288) {
      if (0x284 < uVar7) {
LAB_00198034:
        if (uVar15 + 1 == 0x10) {
          return 0;
        }
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)(uVar15 + 1) * 2));
        if ((uVar4 & 1) != 0 || uVar2 != 0) goto LAB_00197fe4;
        uVar10 = *(undefined2 *)(GPR + uVar18 * 2);
        goto LAB_00198060;
      }
    }
    else if (uVar7 - 0x360 < 3) goto LAB_00198034;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar18 * 2));
  }
  else {
    if (2 < uVar5 - 0x360) goto LAB_00197dc0;
LAB_00197ed0:
    uVar5 = (uint)(param_2 >> 0xc) & 1;
    if ((param_2 >> 0xc & 1) == 0) {
      uVar5 = 3;
    }
    uVar6 = MCInst_getOpcode(param_1);
    if (uVar6 < 0x29b) goto LAB_00197dd0;
LAB_00197ef0:
    if (uVar6 == 0x367) {
LAB_0019817c:
      uVar6 = uVar5;
      if (uVar15 == 0xf) {
        uVar6 = 1;
      }
      uVar7 = (uint)(uVar1 == 0xf) & (uVar7 ^ 1);
      if ((uVar4 & 1) != 0 || uVar2 != 0) {
        if (uVar17 == 0xf || uVar15 == uVar17) {
LAB_001982b8:
          uVar6 = 1;
        }
        else if (uVar7 != 0) {
          uVar6 = 1;
        }
        goto LAB_00197f70;
      }
      if (uVar7 != 0) {
        uVar6 = 1;
      }
      goto LAB_00197e30;
    }
    if (uVar6 < 0x368) {
      if (uVar6 - 0x360 < 3) {
        uVar6 = local_10 & uVar2;
        if ((local_10 & uVar2) == 0) {
          uVar6 = uVar5;
        }
        if ((uVar4 & 1) != 0 || uVar2 != 0) {
          if (uVar17 == 0xf || uVar15 == uVar17) {
            uVar6 = 1;
          }
          else if (uVar17 == uVar15 + 1) goto LAB_001982b8;
        }
        if ((uVar7 & uVar1 == 0xf) != 0) {
          uVar6 = 1;
        }
        if (uVar15 == 0xe) {
          uVar6 = 1;
        }
        if (((uint)((param_2 & 0xf00) != 0) & (uVar7 ^ 1)) != 0) {
          uVar6 = 1;
        }
        if ((uVar4 & 1) != 0 || uVar2 != 0) goto LAB_00197f70;
        goto LAB_00197e30;
      }
    }
    else if (uVar6 - 0x36a < 2) goto LAB_0019817c;
LAB_00197e28:
    uVar14 = uVar5;
LAB_00197e2c:
    uVar6 = uVar14;
    if ((uVar4 & 1) == 0 && uVar2 == 0) goto LAB_00197e30;
LAB_00197f70:
    uVar7 = uVar13 | 0x200;
    *(undefined1 *)(param_1 + 0x335) = 1;
    uVar13 = uVar13 | 0x400;
    if ((param_2 & 0x1000000) != 0) {
      uVar13 = uVar7;
    }
    iVar8 = MCInst_getOpcode(param_1);
    if ((0xb < iVar8 - 0x360U) || ((0xc87UL >> ((ulong)(iVar8 - 0x360U) & 0x3f) & 1) == 0)) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar16 * 2));
      uVar7 = MCInst_getOpcode(param_1);
      if (uVar7 < 0x288) {
        if (uVar7 < 0x285) goto LAB_00197fe4;
      }
      else {
joined_r0x001982c8:
        if (2 < uVar7 - 0x360) goto LAB_00197fe4;
      }
      goto LAB_00198034;
    }
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar18 * 2));
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar16 * 2));
    uVar7 = MCInst_getOpcode(param_1);
    if (0x287 < uVar7) goto joined_r0x001982c8;
    if (0x284 < uVar7) goto LAB_00198034;
LAB_00197fe4:
    iVar8 = MCInst_getOpcode(param_1);
    if ((iVar8 - 0x285U < 0x16) && ((0x33de87UL >> ((ulong)(iVar8 - 0x285U) & 0x3f) & 1) != 0)) {
      uVar10 = *(undefined2 *)(GPR + uVar18 * 2);
      MCOperand_CreateReg0(param_1);
    }
    else {
      uVar10 = *(undefined2 *)(GPR + uVar18 * 2);
    }
LAB_00198060:
    MCOperand_CreateReg0(param_1,uVar10);
  }
  if ((uVar3 & 1) == 0) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    MCOperand_CreateImm0(param_1,uVar13);
  }
  else {
    MCOperand_CreateReg0(param_1,0);
    MCOperand_CreateImm0(param_1,uVar1 | local_20 << 4 | uVar13);
  }
  if (iVar11 != 0xf) {
    iVar8 = MCInst_getOpcode(param_1);
    if (iVar8 == 0xc4f) {
      if (iVar11 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_1,uVar12);
    }
    else {
      MCOperand_CreateImm0(param_1,uVar12);
      if (iVar11 == 0xe) {
        MCOperand_CreateReg0(param_1,0);
        return uVar6;
      }
    }
    MCOperand_CreateReg0(param_1,3);
    return uVar6;
  }
  return 0;
}

