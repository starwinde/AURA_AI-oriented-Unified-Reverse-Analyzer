
/* WARNING: Type propagation algorithm not settling */

undefined4 decodeToMCInst_4_isra_0(undefined4 param_1,undefined4 param_2,ulong param_3,long param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  ulong uVar5;
  undefined1 *puVar6;
  uint uVar7;
  ulong uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  undefined2 uVar12;
  ulong uVar13;
  undefined2 uVar14;
  
  uVar8 = param_3 & 0xffffffff;
  uVar7 = (uint)param_3;
  uVar1 = (uint)(uVar8 >> 8);
  uVar10 = (uint)(uVar8 >> 0x10);
  switch(param_2) {
  case 1:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = DecodeSORegImmOperand_isra_0(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    if (uVar10 == 0xe) {
      MCOperand_CreateReg0(param_4,0);
    }
    else {
      MCOperand_CreateReg0(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 2:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = DecodeSORegRegOperand_isra_0(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    if (uVar10 == 0xe) {
      MCOperand_CreateReg0(param_4,0);
    }
    else {
      MCOperand_CreateReg0(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 3:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeSORegRegOperand_isra_0(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 4:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 5:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar14 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar14);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar14);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 != 0xc4f) goto LAB_001a5fa4;
joined_r0x001a9ee8:
    if (uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7 >> 0x1c);
    goto LAB_001a46bc;
  case 6:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 8 & 0xff0000000000000f;
    goto LAB_001a4388;
  case 7:
    iVar2 = DecodeAddrMode3Instruction_isra_0(param_4,uVar8);
    break;
  case 8:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) != 0xf) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
      return param_1;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    return 1;
  case 9:
    iVar2 = DecodeCPSInstruction_isra_0(param_4,uVar8);
    break;
  case 10:
    MCOperand_CreateImm0(param_4,uVar8 >> 9 & 1);
    goto switchD_001a440c_caseD_33;
  case 0xb:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0xc:
    iVar2 = DecodeQADDInstruction_isra_0(param_4,uVar8);
    break;
  case 0xd:
    iVar2 = DecodeSMLAInstruction_isra_0(param_4,uVar8);
    break;
  case 0xe:
    iVar2 = DecodeSwap_isra_0(param_4,uVar8);
    break;
  case 0xf:
    MCOperand_CreateImm0(param_4,uVar7 & 0xf | (uVar7 & 0xfff00) >> 4);
    goto switchD_001a440c_caseD_33;
  case 0x10:
    iVar2 = DecodeTSTInstruction_isra_0(param_4,uVar8);
    break;
  case 0x11:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = DecodeSORegImmOperand_isra_0(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x12:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeSORegRegOperand_isra_0(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x13:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      uVar12 = 0xb;
      iVar2 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      iVar2 = 3;
      uVar12 = *(undefined2 *)(GPR + (ulong)uVar1 * 2);
      MCOperand_CreateReg0(param_4,uVar12);
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      uVar14 = 0xb;
      iVar11 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      iVar11 = 3;
      uVar14 = *(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2);
      MCOperand_CreateReg0(param_4,uVar14);
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    MCOperand_CreateReg0(param_4,uVar12);
    uVar3 = 1;
    if (iVar2 != 1) {
      uVar3 = param_1;
    }
    MCOperand_CreateReg0(param_4,uVar14);
    param_1 = 1;
    if (iVar11 != 1) {
      param_1 = uVar3;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x14:
    uVar8 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a495c;
  case 0x15:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x16:
    uVar5 = uVar8;
    goto LAB_001a9cac;
  case 0x17:
    uVar5 = uVar8 >> 0xc;
LAB_001a9cac:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar5 & 0xf) * 2));
    param_3 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a47b8;
  case 0x18:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a47b8;
  case 0x19:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    iVar2 = DecodeBankedReg_isra_0
                      (param_4,(uVar7 >> 0x16 & 1) << 5 | (uVar7 & 0x100) >> 4 | uVar10 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x1a:
    iVar2 = DecodeMSRMask_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x1b:
    uVar10 = (uVar7 >> 0x16 & 1) << 5 | (uVar7 & 0x100) >> 4 | uVar10 & 0xf;
    lVar4 = lookupBankedRegByEncoding(uVar10);
    if (lVar4 == 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x1c:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    goto joined_r0x001a4694;
  case 0x1d:
    goto switchD_001a440c_caseD_1d;
  case 0x1e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 8 & 0xf;
    goto LAB_001a47b8;
  case 0x1f:
    uVar5 = uVar8 >> 0xc & 0xfff000000000000f;
    goto LAB_001a4378;
  case 0x20:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc000) == 0) {
      uVar3 = 0x43;
      if ((uVar10 != 1) && (uVar3 = 0x44, uVar10 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar10 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar10 != 0xc) {
        return 0;
      }
      uVar3 = 0x4e;
    }
    MCOperand_CreateReg0(param_4,uVar3);
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc) == 0) {
      uVar3 = 0x43;
      if ((uVar10 != 1) && (uVar3 = 0x44, uVar10 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar10 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar10 != 0xc) {
        return 0;
      }
      uVar3 = 0x4e;
    }
    MCOperand_CreateReg0(param_4,uVar3);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x21:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = DecodeSORegImmOperand_isra_0(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    if (uVar10 == 0xe) {
      MCOperand_CreateReg0(param_4,0);
    }
    else {
      MCOperand_CreateReg0(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x22:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x23:
    uVar8 = uVar8 >> 0xc & 0xf;
    goto LAB_001a495c;
  case 0x24:
    param_3 = param_3 & 0xf;
    goto LAB_001a4684;
  case 0x25:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    iVar2 = DecodeSORegRegOperand_isra_0(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 0x100000) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x26:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    if ((int)uVar5 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    uVar8 = uVar8 >> 0xc & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x27:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 0xf) * 2));
    param_3 = uVar8 >> 0xc & 0xf;
    goto LAB_001a47b8;
  case 0x28:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar14 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar14);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar14);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a4768:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a4768;
      MCOperand_CreateReg0(param_4,0);
    }
    goto LAB_001a43d0;
  case 0x29:
    iVar2 = DecodeDoubleRegStore_isra_0(param_4,uVar8);
    break;
  case 0x2a:
    iVar2 = DecodeDoubleRegLoad_isra_0(param_4,uVar8);
    break;
  case 0x2b:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar12);
    uVar8 = uVar8 >> 0x17 & 1;
    if ((uVar7 & 0xf) == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
      param_1 = 1;
      MCOperand_CreateImm0(param_4,uVar8);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
      MCOperand_CreateImm0(param_4,uVar8);
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x2c:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateImm0(param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf00) >> 4 | uVar7 & 0xf);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) goto joined_r0x001a9ee8;
    goto LAB_001a5fa4;
  case 0x2d:
    iVar2 = DecodeLDR_isra_0(param_4,uVar8);
    break;
  case 0x2e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateImm0(param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf00) >> 4 | uVar7 & 0xf);
    goto joined_r0x001aabbc;
  case 0x2f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    goto LAB_001a5ff8;
  case 0x30:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff | (uVar7 & 0xc00000) >> 10);
joined_r0x001aabbc:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    goto joined_r0x001a4694;
  case 0x31:
    iVar2 = DecodeArmMOVTWInstruction_isra_0(param_4,uVar8);
    break;
  case 0x32:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    param_3 = param_3 & 0xfff;
    goto LAB_001a4684;
  case 0x33:
    goto switchD_001a440c_caseD_33;
  case 0x34:
    iVar2 = DecodeHINTInstruction_isra_0(param_4,uVar8);
    break;
  case 0x35:
    iVar2 = DecodeMSRMask_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    MCOperand_CreateImm0(param_4,param_3 & 0xfff);
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x36:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2);
LAB_001a5ff8:
    MCOperand_CreateReg0(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar10;
    MCOperand_CreateImm0(param_4,param_3 & 0xfff);
    goto joined_r0x001a6010;
  case 0x37:
    iVar2 = DecodeAddrMode2IdxInstruction_isra_0(param_4,uVar8);
    break;
  case 0x38:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar10 = uVar7 & 0xfff;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if (((uVar7 >> 0x17 & 1) == 0) && (uVar10 = -uVar10, (param_3 & 0xfff) == 0)) {
      uVar10 = 0x80000000;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
LAB_001a5fa4:
    uVar7 = uVar7 >> 0x1c;
    MCOperand_CreateImm0(param_4,uVar7);
    goto joined_r0x001a5994;
  case 0x39:
    uVar10 = uVar7 & 0xfff;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if (((uVar7 >> 0x17 & 1) == 0) && (uVar10 = -uVar10, (param_3 & 0xfff) == 0)) {
      uVar10 = 0x80000000;
    }
    MCOperand_CreateImm0(param_4,uVar10);
    goto switchD_001a440c_caseD_33;
  case 0x3a:
    iVar2 = DecodeSTRPreImm_isra_0(param_4,uVar8);
    break;
  case 0x3b:
    iVar2 = DecodeLDRPreImm_isra_0(param_4,uVar8);
    break;
  case 0x3c:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    iVar2 = DecodeAddrModeImm12Operand_isra_0
                      (param_4,(uVar7 >> 0x17 & 1) << 0xc | (uVar7 & 0xf0000) >> 3 | uVar7 & 0xfff);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x3d:
  case 0x3e:
  case 0x114:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0x3f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = DecodeSORegMemOperand_isra_0
                      (param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                               uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0x40:
    iVar2 = DecodeSORegMemOperand_isra_0
                      (param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                               uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    break;
  case 0x41:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x42:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 7 & 0x1f);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x43:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x44:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    if ((int)uVar5 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x45:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar8 = uVar8 >> 0x10 & 0xf;
LAB_001a495c:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    param_3 = param_3 & 0xf;
LAB_001a47b8:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + param_3 * 2));
joined_r0x001a4694:
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if ((int)uVar8 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar8);
    }
    else {
LAB_001a5984:
      MCOperand_CreateImm0(param_4,uVar8);
      uVar7 = (uint)uVar8;
joined_r0x001a5994:
      if (uVar7 == 0xe) {
LAB_001a43d4:
        MCOperand_CreateReg0(param_4,0);
        goto switchD_001a440c_caseD_33;
      }
    }
LAB_001a46bc:
    MCOperand_CreateReg0(param_4,3);
    goto switchD_001a440c_caseD_33;
  case 0x46:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 10 & 3);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x47:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 10 & 3);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x48:
    iVar2 = DecodeSTRPreReg_isra_0(param_4,uVar8);
    break;
  case 0x49:
    iVar2 = DecodeLDRPreReg_isra_0(param_4,uVar8);
    break;
  case 0x4a:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 7) & 0x1f | (uVar7 & 0x40) >> 1);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x4b:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x4c:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 7 & 0x1f);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x4d:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    iVar2 = DecodeSORegMemOperand_isra_0
                      (param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                               uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x4e:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar1 = (uint)(uVar8 >> 7) & 0x1f;
    uVar10 = (uVar7 & 0x1f0000) >> 0x10;
    if (uVar10 < uVar1) {
      param_1 = 1;
      MCOperand_CreateImm0
                (param_4,(1 << (ulong)(uVar10 + 1 & 0x1f)) - 1U ^
                         (1 << (ulong)uVar10) - 1U ^ 0xffffffff);
    }
    else if (uVar10 == 0x1f) {
      MCOperand_CreateImm0(param_4,(1 << (ulong)uVar1) + -1);
    }
    else {
      MCOperand_CreateImm0
                (param_4,(1 << (ulong)(uVar10 + 1 & 0x1f)) - 1U ^
                         (1 << (ulong)uVar1) - 1U ^ 0xffffffff);
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x4f:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      uVar12 = *(undefined2 *)(GPR + (ulong)uVar10 * 2);
      MCOperand_CreateReg0(param_4,uVar12);
      MCOperand_CreateReg0(param_4,uVar12);
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    iVar2 = DecodeBitfieldMaskOperand_isra_0
                      (param_4,(uint)(uVar8 >> 7) & 0x1f | (uVar7 & 0x1f0000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x50:
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a5380:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a5380;
      MCOperand_CreateReg0(param_4,0);
    }
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0xffff);
    break;
  case 0x51:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x52:
    iVar2 = DecodeMemMultipleWritebackInstruction_isra_0(param_4,uVar8);
    break;
  case 0x53:
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    goto switchD_001a440c_caseD_33;
  case 0x54:
    iVar2 = DecodeBranchImmInstruction_isra_0(param_4,uVar8);
    break;
  case 0x55:
    MCOperand_CreateImm0(param_4,(uVar7 & 0xffffff) << 1 | (uint)(uVar8 >> 0x18) & 1);
    goto switchD_001a440c_caseD_33;
  case 0x56:
    iVar2 = DecoderForMRRC2AndMCRR2_isra_0(param_4,uVar8);
    break;
  case 0x57:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 0xf);
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a6df4;
  case 0x58:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeCoprocessor_isra_0(param_4,uVar8 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x59:
    param_3 = param_3 & 0xffffff;
LAB_001a4684:
    MCOperand_CreateImm0(param_4,param_3);
switchD_001a440c_caseD_1d:
joined_r0x001a4694:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    goto joined_r0x001a4694;
  case 0x5a:
    iVar2 = DecodeCopMemInstruction_isra_0(param_4,uVar8);
    break;
  case 0x5b:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x14 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 0xc & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x5c:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x14 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 0xc & 0xf);
    goto LAB_001a5940;
  case 0x5d:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x15 & 7);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x5e:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x15 & 7);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
LAB_001a5940:
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    uVar8 = uVar8 >> 5 & 7;
LAB_001a595c:
    MCOperand_CreateImm0(param_4,uVar8);
    goto joined_r0x001a734c;
  case 0x5f:
    uVar7 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar7 == 0xf) {
      MCOperand_CreateReg0(param_4,2);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x15 & 7);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x60:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      MCOperand_CreateReg0(param_4,2);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x15 & 7);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 7);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0x61:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x62:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 99:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 100:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x65:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    break;
  case 0x66:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x67:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    if ((uVar8 >> 0x10 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x68:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto joined_r0x001a6df4;
  case 0x69:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x6a:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto joined_r0x001a6df4;
  case 0x6b:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6c:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6d:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6e:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar9;
  case 0x70:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x71:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x72:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x73:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x74:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x75:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar9;
  case 0x76:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x77:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 10 & 1);
    return uVar3;
  case 0x78:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 9 & 3);
    return uVar3;
  case 0x79:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 8 & 7);
    return uVar3;
  case 0x7a:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0xb & 1);
    return uVar9;
  case 0x7b:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 10 & 3);
    return uVar9;
  case 0x7c:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 9 & 7);
    return uVar9;
  case 0x7d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 8 & 0xf);
    return uVar9;
  case 0x7e:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x7f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x80:
    uVar8 = (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + uVar8 * 2));
    uVar5 = (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + uVar5 * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar8);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar5);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x81:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 & 0xf | (uVar7 & 0x20) >> 1;
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7);
    goto joined_r0x001a6df4;
  case 0x82:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x83:
    iVar2 = DecodeVSHLMaxInstruction_isra_0(param_4,uVar8);
    break;
  case 0x84:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x85:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x86:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    return uVar3;
  case 0x87:
    iVar2 = DecodeTBLInstruction_isra_0(param_4,uVar8);
    break;
  case 0x88:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x13 & 1);
    goto switchD_001a440c_caseD_33;
  case 0x89:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x12 & 3);
    goto switchD_001a440c_caseD_33;
  case 0x8a:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x11 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x8b:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x13 & 1);
    return uVar3;
  case 0x8c:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x12 & 3);
    return uVar3;
  case 0x8d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x11 & 7);
    return uVar3;
  case 0x8e:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,8 - (uVar10 & 7));
    goto switchD_001a440c_caseD_33;
  case 0x8f:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,0x10 - (uVar10 & 0xf));
    goto switchD_001a440c_caseD_33;
  case 0x90:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,0x20 - (uVar10 & 0x1f));
    goto switchD_001a440c_caseD_33;
  case 0x91:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0x92:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0x93:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0x94:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x95:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0x96:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0x97:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0x98:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    goto switchD_001a440c_caseD_33;
  case 0x99:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0x9a:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0x9b:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0x9c:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0x9d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0x9e:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0x9f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0xa0:
    iVar2 = DecodeVCVTD_isra_0(param_4,uVar8);
    break;
  case 0xa1:
    iVar2 = DecodeNEONModImmInstruction_isra_0(param_4,uVar8);
    break;
  case 0xa2:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,0x40 - (uVar10 & 0x3f));
    goto switchD_001a440c_caseD_33;
  case 0xa3:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x40 - (uVar10 & 0x3f));
    return uVar3;
  case 0xa4:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x3f);
    goto switchD_001a440c_caseD_33;
  case 0xa5:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar3;
  case 0xa6:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0xa7:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0xa8:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0xa9:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,8 - (uVar10 & 7));
    return uVar9;
  case 0xaa:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x10 - (uVar10 & 0xf));
    return uVar9;
  case 0xab:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x20 - (uVar10 & 0x1f));
    return uVar9;
  case 0xac:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0xad:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 7);
    return uVar9;
  case 0xae:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0xaf:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    return uVar9;
  case 0xb0:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0xb1:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar9;
  case 0xb2:
    iVar2 = DecodeVCVTQ_isra_0(param_4,uVar8);
    break;
  case 0xb3:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x40 - (uVar10 & 0x3f));
    return uVar3;
  case 0xb4:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,0x40 - (uVar10 & 0x3f));
    return uVar9;
  case 0xb5:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar3;
  case 0xb6:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar9;
  case 0xb7:
    uVar12 = *(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 0x15 & 1);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0xb8:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    uVar8 = uVar8 >> 0x15 & 1;
    goto LAB_001a595c;
  case 0xb9:
    uVar12 = *(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 6) & 1 | (uVar7 & 0x200000) >> 0x14);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0xba:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 6) & 1 | (uVar7 & 0x200000) >> 0x14);
    goto joined_r0x001a734c;
  case 0xbb:
    uVar12 = *(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 5) & 3 | (uVar7 & 0x200000) >> 0x13);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0xbc:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 5) & 3 | (uVar7 & 0x200000) >> 0x13);
    goto joined_r0x001a734c;
  case 0xbd:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
joined_r0x001a734c:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    uVar8 = (ulong)(uVar7 >> 0x1c);
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    goto LAB_001a5984;
  case 0xbe:
    if ((uVar8 >> 0x10 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    if (uVar7 != 0xe) {
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    MCOperand_CreateReg0(param_4,0);
    return uVar3;
  case 0xbf:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = DecodeVSTInstruction_isra_0(param_4,uVar8);
    }
    else {
      iVar2 = DecodeVLDInstruction_isra_0();
    }
    break;
  case 0xc0:
    iVar2 = DecodeVST1LN_isra_0(param_4,uVar8);
    break;
  case 0xc1:
    iVar2 = DecodeVLD1LN_isra_0(param_4,uVar8);
    break;
  case 0xc2:
    iVar2 = DecodeVST2LN_isra_0(param_4,uVar8);
    break;
  case 0xc3:
    iVar2 = DecodeVLD2LN_isra_0(param_4,uVar8);
    break;
  case 0xc4:
    uVar1 = uVar1 & 0xf;
    if ((uVar1 == 6) || (uVar1 == 7)) {
      if ((uVar7 >> 5 & 1) != 0) {
        return 0;
      }
    }
    else if ((uVar7 >> 4 & 3) == 3 && uVar1 == 10) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = DecodeVSTInstruction_isra_0(param_4,uVar8);
    }
    else {
      iVar2 = DecodeVLDInstruction_isra_0();
    }
    break;
  case 0xc5:
    iVar2 = DecodeVST3LN_isra_0(param_4,uVar8);
    break;
  case 0xc6:
    iVar2 = DecodeVLD3LN_isra_0(param_4,uVar8);
    break;
  case 199:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 & 0x30) == 0x30 && ((uVar1 & 0xf) == 8 || (uVar1 & 0xf) == 9)) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = DecodeVSTInstruction_isra_0(param_4,uVar8);
    }
    else {
      iVar2 = DecodeVLDInstruction_isra_0();
    }
    break;
  case 200:
    iVar2 = DecodeVST4LN_isra_0(param_4,uVar8);
    break;
  case 0xc9:
    iVar2 = DecodeVLD4LN_isra_0(param_4,uVar8);
    break;
  case 0xca:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 >> 5 & 1) != 0) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = DecodeVSTInstruction_isra_0(param_4,uVar8);
    }
    else {
      iVar2 = DecodeVLDInstruction_isra_0();
    }
    break;
  case 0xcb:
    iVar2 = DecodeVLD1DupInstruction_isra_0(param_4,uVar8);
    break;
  case 0xcc:
    iVar2 = DecodeVLD2DupInstruction_isra_0(param_4,uVar8);
    break;
  case 0xcd:
    iVar2 = DecodeVLD3DupInstruction_isra_0(param_4,uVar8);
    break;
  case 0xce:
    iVar2 = DecodeVLD4DupInstruction_isra_0(param_4,uVar8);
    break;
  case 0xcf:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd0:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2));
    MCOperand_CreateImm0(param_4,param_3 & 0xff);
    goto switchD_001a440c_caseD_33;
  case 0xd1:
    iVar2 = DecodeThumbAddSPReg_isra_0(param_4,uVar8);
    break;
  case 0xd2:
    uVar12 = *(undefined2 *)(GPR + (ulong)(uVar7 & 7 | (uVar7 & 0x80) >> 4) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd3:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 7 | (uVar7 & 0x80) >> 4) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd4:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd5:
    uVar7 = (uint)(uVar8 >> 3) & 0xf;
    if (uVar7 == 0xf) goto LAB_001aba50;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd6:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2));
    MCOperand_CreateImm0(param_4,(param_3 & 0xff) << 2);
    goto switchD_001a440c_caseD_33;
  case 0xd7:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 6 & 7) * 2));
    goto switchD_001a440c_caseD_33;
  case 0xd8:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 6 & 0x1f);
    goto switchD_001a440c_caseD_33;
  case 0xd9:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2));
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateImm0(param_4,param_3 & 0xff);
    goto switchD_001a440c_caseD_33;
  case 0xda:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2));
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc3e) {
      MCOperand_CreateReg0(param_4,0xc);
    }
    else if (iVar2 != 0xc42) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    goto switchD_001a440c_caseD_33;
  case 0xdb:
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateImm0(param_4,param_3 & 0x7f);
    goto switchD_001a440c_caseD_33;
  case 0xdc:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateImm0(param_4,(ulong)((uint)(uVar8 >> 3) & 0x1f | (uVar7 & 0x200) >> 4) << 1);
    goto switchD_001a440c_caseD_33;
  case 0xdd:
    iVar2 = DecodeRegListOperand_isra_0(param_4,(uVar7 >> 8 & 1) << 0xe | uVar7 & 0xff);
    break;
  case 0xde:
    MCOperand_CreateImm0(param_4,uVar8 >> 3 & 1);
    goto switchD_001a440c_caseD_33;
  case 0xdf:
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 1 | 2);
    MCOperand_CreateImm0(param_4,uVar7 & 7);
    goto switchD_001a440c_caseD_33;
  case 0xe0:
    MCOperand_CreateImm0(param_4,param_3 & 0x3f);
    goto switchD_001a440c_caseD_33;
  case 0xe1:
    iVar2 = DecodeRegListOperand_isra_0(param_4,(uVar7 >> 8 & 1) << 0xf | uVar7 & 0xff);
    break;
  case 0xe2:
    MCOperand_CreateImm0(param_4,param_3 & 0xff);
    goto switchD_001a440c_caseD_33;
  case 0xe3:
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0xe4:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0xff);
    break;
  case 0xe5:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2));
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0xff);
    break;
  case 0xe6:
    uVar8 = uVar8 >> 8 & 0xf;
    MCOperand_CreateImm0(param_4,(long)(int)(-(uVar7 >> 7 & 1) & 0xfffffe00 | (uVar7 & 0xff) << 1));
    uVar7 = (uint)uVar8;
    goto joined_r0x001a4694;
  case 0xe7:
    MCOperand_CreateImm0(param_4,-(uVar8 >> 10 & 1) & 0xfffffffffffff000 | (param_3 & 0x7ff) << 1);
    goto switchD_001a440c_caseD_33;
  case 0xe8:
    uVar10 = uVar7 & 0x4000000;
    MCOperand_CreateImm0
              (param_4,-(ulong)(uVar10 >> 0x1a) & 0xfffffffffe000000 |
                       (ulong)((uint)((uVar7 >> 0xb & 1) == uVar10 >> 0x1a) << 0x15 |
                               (uint)((uVar7 >> 0xd & 1) == uVar10 >> 0x1a) << 0x16 |
                              uVar7 & 0x7fe | (uVar7 & 0x3ff0000) >> 5 | uVar10 >> 3) << 1);
    goto switchD_001a440c_caseD_33;
  case 0xe9:
    uVar10 = uVar7 >> 0x1a;
    MCOperand_CreateImm0
              (param_4,-(ulong)(uVar10 & 1) & 0xfffffffffe000000 |
                       (ulong)((uint)((uVar7 >> 0xb & 1) == (uVar10 & 1)) << 0x15 |
                               (uint)((uVar7 >> 0xd & 1) == (uVar10 & 1)) << 0x16 |
                              (uVar10 & 1) << 0x17 | (uVar7 & 0x3ff0000) >> 5 | uVar7 & 0x7ff) << 1)
    ;
    goto switchD_001a440c_caseD_33;
  case 0xea:
    uVar8 = uVar8 >> 4 & 0xf;
    if ((int)uVar8 == 0xf) {
      if ((param_3 & 0xf) == 0) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,0xe);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      return 1;
    }
    if ((param_3 & 0xf) == 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8);
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0xeb:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0x5fff);
    break;
  case 0xec:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0xffff);
    break;
  case 0xed:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    goto joined_r0x001a6df4;
  case 0xee:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    goto joined_r0x001a6df4;
  case 0xef:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab318;
      }
LAB_001abeac:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abeac;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab318:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab33c;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab33c:
      param_1 = 1;
      goto LAB_001ab340;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001ab340:
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0xf0:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a99d0;
      }
LAB_001abec8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abec8;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a99d0:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a99f4;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a99f4:
      param_1 = 1;
      goto LAB_001a99f8;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001a99f8:
    iVar2 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0xf1:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0xf2:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0xf3:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0x5fff);
    break;
  case 0xf4:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeRegListOperand_isra_0(param_4,uVar7 & 0xffff);
    break;
  case 0xf5:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a6a10;
      }
LAB_001abe8c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abe8c;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a6a10:
      param_1 = 1;
    }
    if ((uVar10 & 0xf) != 0xf) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
      return param_1;
    }
LAB_001aba50:
    MCOperand_CreateReg0(param_4,0xb);
    return 1;
  case 0xf6:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab138;
      }
LAB_001abbb4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abbb4;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab138:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab15c;
      }
LAB_001acab0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acab0;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab15c:
      param_1 = 1;
    }
    iVar2 = DecodeT2AddrModeImm0_1020s4_isra_0(param_4,uVar7 & 0xff | (uVar7 & 0xf0000) >> 8);
    goto joined_r0x001a6df4;
  case 0xf7:
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab0d0;
      }
LAB_001abe38:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001abe38;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab0d0:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab0f8;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab0f8:
      param_1 = 1;
      goto LAB_001ab0fc;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001ab0fc:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xf8:
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab04c;
      }
LAB_001abe54:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001abe54;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab04c:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab070;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab070:
      param_1 = 1;
      goto LAB_001ab074;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001ab074:
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 8 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xf9:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab008;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab008:
      param_1 = 1;
      goto LAB_001ab010;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001ab010:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xfa:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aba04;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aba04:
      param_1 = 1;
      goto LAB_001aba08;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001aba08:
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    if (uVar10 != 0xf) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
      MCOperand_CreateImm0(param_4,uVar7 & 0xff);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0xb);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    return 1;
  case 0xfb:
    iVar2 = DecodeThumbTableBranch_isra_0(param_4,uVar8);
    break;
  case 0xfc:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aaf78;
      }
LAB_001abd04:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abd04;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aaf78:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aafa0;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aafa0:
      param_1 = 1;
      goto LAB_001aafa4;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001aafa4:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xfd:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aaef4;
      }
LAB_001abdfc:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abdfc;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aaef4:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aaf18;
      }
LAB_001ad454:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad454;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aaf18:
      param_1 = 1;
    }
    iVar2 = DecodeT2AddrModeImm8s4_isra_0
                      (param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf0000) >> 7 | uVar7 & 0xff);
    goto joined_r0x001a6df4;
  case 0xfe:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar7 & 0xf) * 2));
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0xff:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a951c;
      }
LAB_001abc78:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abc78;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a951c:
      param_1 = 1;
    }
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a9540;
      }
    }
    else if (uVar10 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a9540:
      param_1 = 1;
      goto LAB_001a9544;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
LAB_001a9544:
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x100:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab920;
      }
LAB_001abbec:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abbec;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab920:
      param_1 = 1;
    }
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab944;
      }
    }
    else if (uVar10 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab944:
      param_1 = 1;
      goto LAB_001ab948;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
LAB_001ab948:
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x101:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a949c;
      }
LAB_001abee4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abee4;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a949c:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a94c0;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a94c0:
      param_1 = 1;
      goto LAB_001a94c4;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001a94c4:
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    return param_1;
  case 0x102:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a9428;
      }
LAB_001abd90:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abd90;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a9428:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a944c;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a944c:
      param_1 = 1;
      goto LAB_001a9450;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001a9450:
    MCOperand_CreateReg0(param_4,uVar12);
    if ((param_3 & 0xff) != 0 || (param_3 & 0x800000) != 0) {
      DecodeT2Imm8S4_part_0();
      return param_1;
    }
    MCOperand_CreateImm0(param_4,0xffffffff80000000);
    return param_1;
  case 0x103:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a9378;
      }
LAB_001abccc:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abccc;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a9378:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a93a0;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a93a0:
      param_1 = 1;
      goto LAB_001a93a4;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001a93a4:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    if ((param_3 & 0xff) != 0 || (param_3 & 0x800000) != 0) {
      DecodeT2Imm8S4_part_0();
      return param_1;
    }
    MCOperand_CreateImm0(param_4,0xffffffff80000000);
    return param_1;
  case 0x104:
    iVar2 = DecodeT2STRDPreInstruction_isra_0(param_4,uVar8);
    break;
  case 0x105:
    iVar2 = DecodeT2LDRDPreInstruction_isra_0(param_4,uVar8);
    break;
  case 0x106:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa37c;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa37c:
      param_1 = 1;
      goto LAB_001aa380;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001aa380:
    iVar2 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x107:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeT2SOImm_isra_0
                      (param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    goto joined_r0x001a6df4;
  case 0x108:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa2f0;
      }
LAB_001abf1c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abf1c;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa2f0:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa314;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa314:
      param_1 = 1;
      goto LAB_001aa318;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001aa318:
    iVar2 = DecodeT2SOImm_isra_0
                      (param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x109:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa228;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa228:
      param_1 = 1;
      goto LAB_001aa22c;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001aa22c:
    iVar2 = DecodeT2SOImm_isra_0
                      (param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x10a:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodeT2SOImm_isra_0
                      (param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    MCOperand_CreateReg0(param_4,0);
    return param_1;
  case 0x10b:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 & 0xf) * 2));
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateImm0(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    return param_1;
  case 0x10c:
    uVar10 = (uint)(uVar8 >> 0x15) & 1;
    if (uVar10 != ((uint)(uVar8 >> 0x17) & 1)) {
      return 0;
    }
    MCOperand_CreateImm0
              (param_4,(long)((ulong)((uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 |
                                     uVar7 & 0xff | uVar10 << 0xc) << 0x33) >> 0x33);
    goto switchD_001a440c_caseD_33;
  case 0x10d:
    iVar2 = DecodeT2MOVTWInstruction_isra_0(param_4,uVar8);
    break;
  case 0x10e:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa4d0;
      }
LAB_001abbd0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abbd0;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa4d0:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
LAB_001ad5e8:
        MCOperand_CreateReg0(param_4,0xc);
        return 1;
      }
LAB_001aa4f4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
      return param_1;
    }
    if (iVar2 != 0xf) goto LAB_001aa4f4;
    goto LAB_001aba50;
  case 0x10f:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa44c;
      }
LAB_001abc08:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abc08;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa44c:
      param_1 = 1;
    }
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa47c;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa47c:
      param_1 = 1;
      goto LAB_001aa480;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001aa480:
    uVar7 = (uVar7 >> 0x15 & 1) << 5 | (uVar7 & 0x7000) >> 10 | (uint)(uVar8 >> 6) & 3;
    if (uVar7 == 0x20) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    return param_1;
  case 0x110:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab994;
      }
LAB_001abce8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abce8;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab994:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab9b8;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab9b8:
      param_1 = 1;
      goto LAB_001ab9bc;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001ab9bc:
    MCOperand_CreateImm0(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    return param_1;
  case 0x111:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xc);
      }
      else {
        MCOperand_CreateReg0(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa3f4;
      }
      uVar12 = 0xc;
LAB_001ac560:
      MCOperand_CreateReg0(param_4,uVar12);
    }
    else {
      if (iVar2 != 0xf) {
        uVar12 = *(undefined2 *)(GPR + uVar5 * 2);
        MCOperand_CreateReg0(param_4,uVar12);
        goto LAB_001ac560;
      }
      MCOperand_CreateReg0(param_4,0xb);
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa3f4:
      param_1 = 1;
    }
    iVar2 = DecodeBitfieldMaskOperand_isra_0
                      (param_4,(uVar7 & 0x1f) << 5 | (uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10
                      );
    goto joined_r0x001a6df4;
  case 0x112:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xc);
      }
      else {
        MCOperand_CreateReg0(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab5f4;
      }
      uVar12 = 0xc;
LAB_001ac530:
      MCOperand_CreateReg0(param_4,uVar12);
    }
    else {
      if (iVar2 != 0xf) {
        uVar12 = *(undefined2 *)(GPR + uVar5 * 2);
        MCOperand_CreateReg0(param_4,uVar12);
        goto LAB_001ac530;
      }
      MCOperand_CreateReg0(param_4,0xb);
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab5f4:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 0x10 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecodeBitfieldMaskOperand_isra_0
                      (param_4,(uVar7 & 0x1f) << 5 | (uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10
                      );
    goto joined_r0x001a6df4;
  case 0x113:
    if ((uVar10 & 0xf) == 0xf) goto LAB_001aba50;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x115:
    iVar2 = DecodeT2CPSInstruction_isra_0(param_4,uVar8);
    break;
  case 0x116:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x117:
    iVar2 = DecodeMSRMask_isra_0(param_4,uVar1 & 0xf | (uVar7 & 0x100000) >> 0x10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 != 0xd) {
      if (iVar2 == 0xf) goto LAB_001aba50;
LAB_001a7b8c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
      return uVar3;
    }
    if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a7b8c;
    goto LAB_001ad5e8;
  case 0x118:
    uVar7 = uVar7 & 0x10 | (uVar7 & 0x100000) >> 0xf | uVar1 & 0xf;
    lVar4 = lookupBankedRegByEncoding(uVar7);
    if (lVar4 == 0) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    MCOperand_CreateImm0(param_4,uVar7);
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) goto LAB_001ad5e8;
    }
    else if (iVar2 == 0xf) goto LAB_001aba50;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    goto switchD_001a440c_caseD_33;
  case 0x119:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a7ab8;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a7ab8:
      param_1 = 1;
      goto LAB_001a7abc;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001a7abc:
    uVar7 = uVar7 & 0x10 | (uVar7 & 0x100000) >> 0xf | uVar10 & 0xf;
    lVar4 = lookupBankedRegByEncoding(uVar7);
    if (lVar4 == 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    return param_1;
  case 0x11a:
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff | (uVar7 & 0xf0000) >> 4);
    goto switchD_001a440c_caseD_33;
  case 0x11b:
    MCOperand_CreateImm0(param_4,uVar8 >> 0x10 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0x11c:
    iVar2 = DecodeMSRMask_isra_0(param_4,uVar7 & 0xcff);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) goto LAB_001ad5e8;
    }
    else if (iVar2 == 0xf) goto LAB_001aba50;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    return uVar3;
  case 0x11d:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab22c;
      }
LAB_001abde0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abde0;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab22c:
      param_1 = 1;
    }
    iVar2 = DecodeMSRMask_isra_0(param_4,uVar7 & 0xff);
    goto joined_r0x001a6df4;
  case 0x11e:
    iVar2 = DecodeThumb2BCCInstruction_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x11f:
    uVar10 = (uint)(uVar8 >> 0x1a) & 1;
    MCOperand_CreateImm0
              (param_4,-(ulong)uVar10 & 0xfffffffffe000000 |
                       (ulong)((uint)(((uint)(uVar8 >> 0xb) & 1) == uVar10) << 0x15 |
                               (uint)(((uint)(uVar8 >> 0xd) & 1) == uVar10) << 0x16 |
                               (uVar7 >> 0x10 & 0x3ff) << 0xb | uVar10 << 0x17 | uVar7 & 0x7ff) << 1
              );
    goto switchD_001a440c_caseD_33;
  case 0x120:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab51c;
      }
LAB_001abf00:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abf00;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab51c:
      param_1 = 1;
    }
    iVar2 = DecodeT2AddrModeSOReg_isra_0
                      (param_4,(uVar7 & 0xf) << 2 | (uint)(uVar8 >> 4) & 3 | (uVar7 & 0xf0000) >> 10
                      );
    goto joined_r0x001a6df4;
  case 0x121:
    iVar2 = DecodeT2LdStPre_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x122:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab4cc;
      }
LAB_001abdc4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abdc4;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab4cc:
      param_1 = 1;
    }
    iVar2 = DecodeT2AddrModeImm8_isra_0(param_4,uVar7 & 0xff | (uVar7 & 0xf0000) >> 7);
    goto joined_r0x001a6df4;
  case 0x123:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a9810;
      }
LAB_001abe70:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abe70;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a9810:
      param_1 = 1;
    }
    iVar2 = DecodeT2AddrModeImm8_isra_0
                      (param_4,(uVar7 >> 0x10 & 0xf) << 9 | (uVar7 & 0x200) >> 1 | uVar7 & 0xff);
    goto joined_r0x001a6df4;
  case 0x124:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a9788;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a9788:
      param_1 = 1;
      goto LAB_001a978c;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
LAB_001a978c:
    iVar2 = MCInst_getOpcode(param_4);
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    if (((iVar2 - 0xbe9U < 0x14) && ((0x82001UL >> ((ulong)(iVar2 - 0xbe9U) & 0x3f) & 1) != 0)) &&
       (uVar10 == 0xf)) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    return param_1;
  case 0x125:
    iVar2 = DecodeT2LoadShift_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x126:
    iVar2 = DecodeT2LoadImm8_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x127:
    iVar2 = DecodeT2LoadT_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x128:
    iVar2 = DecodeT2LoadImm12_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x129:
    iVar2 = DecodeT2LoadLabel_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x12a:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa648;
      }
LAB_001abd3c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abd3c;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa648:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001aa66c;
      }
LAB_001acfec:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acfec;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001aa66c:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    goto joined_r0x001a6df4;
  case 299:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a77a4;
      }
LAB_001abc94:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abc94;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a77a4:
      param_1 = 1;
    }
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a77c8;
      }
    }
    else if (uVar7 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a77c8:
      param_1 = 1;
      goto LAB_001a77cc;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
LAB_001a77cc:
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 3);
    return param_1;
  case 300:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a7730;
      }
LAB_001abd74:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abd74;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a7730:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a7754;
      }
    }
    else if (iVar2 == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a7754:
      param_1 = 1;
      goto LAB_001a7758;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
LAB_001a7758:
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 3);
    return param_1;
  case 0x12d:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab460;
      }
LAB_001abc24:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abc24;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab460:
      param_1 = 1;
    }
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001ab484;
      }
LAB_001aca90:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001aca90;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001ab484:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 0x10 & 0xf);
    goto joined_r0x001a6df4;
  case 0x12e:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a76d4;
      }
LAB_001abda8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abda8;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a76d4:
      param_1 = 1;
    }
    uVar7 = (uVar7 | uVar7 >> 0x10) & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a76f0;
      goto LAB_001ad5e8;
    }
    if (uVar7 != 0xf) {
LAB_001a76f0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar7 * 2));
      return param_1;
    }
    goto LAB_001aba50;
  case 0x12f:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a764c;
      }
LAB_001abd58:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abd58;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a764c:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a7670;
      }
LAB_001ad054:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad054;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a7670:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 0xc & 0xf);
    goto joined_r0x001a6df4;
  case 0x130:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a75c4;
      }
LAB_001abb98:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001abb98;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a75c4:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a75e8;
      }
LAB_001ad260:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad260;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a75e8:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 0x10 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    goto joined_r0x001a6df4;
  case 0x131:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 8 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x132:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = DecodeT2AddrModeSOReg_isra_0
                      (param_4,(uVar7 & 0xf) << 2 | (uint)(uVar8 >> 4) & 3 | (uVar7 & 0xf0000) >> 10
                      );
    break;
  case 0x133:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = DecodeT2AddrModeImm8_isra_0
                      (param_4,(uVar7 >> 0x10 & 0xf) << 9 | (uVar7 & 0x200) >> 1 | uVar7 & 0xff);
    break;
  case 0x134:
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = MCInst_getOpcode(param_4);
    if (((iVar2 - 0xbe9U < 0x14) && ((0x82001UL >> ((ulong)(iVar2 - 0xbe9U) & 0x3f) & 1) != 0)) &&
       (uVar10 == 0xf)) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar10 * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    goto switchD_001a440c_caseD_33;
  case 0x135:
    uVar5 = uVar8 >> 0xc & 0xf;
    if ((int)uVar5 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a73f8;
      }
LAB_001abd20:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar5 * 2));
    }
    else {
      if ((int)uVar5 != 0xf) goto LAB_001abd20;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a73f8:
      param_1 = 1;
    }
    uVar13 = uVar8 >> 8 & 0xf;
    if ((int)uVar13 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        MCOperand_CreateReg0(param_4,0xc);
        goto LAB_001a741c;
      }
LAB_001ad490:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar13 * 2));
    }
    else {
      if ((int)uVar13 != 0xf) goto LAB_001ad490;
      MCOperand_CreateReg0(param_4,0xb);
LAB_001a741c:
      param_1 = 1;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar8 >> 0x10 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar5);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecoderGPRRegisterClass_isra_0(param_4,uVar13);
    goto joined_r0x001a6df4;
  case 0x136:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0x137:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar5);
    MCOperand_CreateImm0(param_4,uVar8 >> 4 & 0xf);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    goto switchD_001a440c_caseD_33;
  case 0x138:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 6 & 0x1f);
    goto switchD_001a440c_caseD_33;
  case 0x139:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 6 & 7) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x13a:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar8 >> 6 & 7);
    goto switchD_001a440c_caseD_33;
  case 0x13b:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 8 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateImm0(param_4,param_3 & 0xff);
    goto switchD_001a440c_caseD_33;
  case 0x13c:
    uVar12 = *(undefined2 *)(GPR + (param_3 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x13d:
    uVar12 = *(undefined2 *)(GPR + (param_3 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 3 & 7) * 2));
    MCOperand_CreateReg0(param_4,uVar12);
    goto switchD_001a440c_caseD_33;
  case 0x13e:
  case 0x144:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if ((uVar7 >> 0x17 & 1) == 0) {
      MCOperand_CreateImm0(param_4,uVar7 & 0xff | 0x100);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    }
    goto joined_r0x001a8948;
  case 0x13f:
    uVar12 = *(undefined2 *)(HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2)
    ;
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 != 0xc4f) goto LAB_001abf54;
joined_r0x001a89d8:
    if (uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7 >> 0x1c);
    goto LAB_001a4478;
  case 0x140:
  case 0x146:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    uVar10 = (uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf;
    goto LAB_001a4428;
  case 0x141:
  case 0x147:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    goto joined_r0x001a4534;
  case 0x142:
    iVar2 = DecodeVMOVSRR_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x143:
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a4edc:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a4edc;
      MCOperand_CreateReg0(param_4,0);
    }
    uVar10 = uVar7 & 0xff;
    uVar7 = (uVar7 >> 0x16 & 1) << 8 | (uVar7 & 0xf000) >> 3;
    uVar1 = uVar7 >> 8;
    uVar12 = *(undefined2 *)(HPR + (ulong)(uVar7 >> 8) * 2);
    if ((param_3 & 0xff) != 0) {
      if (uVar1 + uVar10 < 0x21) {
        MCOperand_CreateReg0(param_4,uVar12);
        if (uVar10 == 1) goto switchD_001a440c_caseD_33;
        if (uVar1 == 0x1f) {
          return 0;
        }
        uVar10 = uVar10 - 1;
        iVar2 = 3;
      }
      else {
        MCOperand_CreateReg0(param_4,uVar12);
        iVar2 = 1;
        uVar10 = 0x1f - uVar1;
        if (uVar1 == 0x1f) {
          return 1;
        }
      }
      uVar8 = (ulong)(uVar1 + 2);
      while (MCOperand_CreateReg0(param_4,*(undefined2 *)(&DAT_0022e5fe + uVar8 * 2)),
            ((int)uVar8 - uVar1) - 1 < uVar10) {
        uVar8 = uVar8 + 1;
        if (uVar8 == (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1)) {
          return 0;
        }
      }
      if (iVar2 == 1) {
        return 1;
      }
      goto switchD_001a440c_caseD_33;
    }
    MCOperand_CreateReg0(param_4,uVar12);
    goto LAB_001a4f20;
  case 0x145:
    uVar12 = *(undefined2 *)(HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2)
    ;
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) goto joined_r0x001a89d8;
LAB_001abf54:
    MCOperand_CreateImm0(param_4,uVar7 >> 0x1c);
    if (uVar7 >> 0x1c != 0xe) goto LAB_001a4478;
    goto LAB_001a460c;
  case 0x148:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    goto joined_r0x001a8948;
  case 0x149:
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a91b4:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a91b4;
      MCOperand_CreateReg0(param_4,0);
    }
    iVar2 = DecodeDPRRegListOperand_isra_0
                      (param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4 | (uVar7 & 0x400000) >> 10);
    break;
  case 0x14a:
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a69b8:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a69b8;
      MCOperand_CreateReg0(param_4,0);
    }
    iVar2 = DecodeDPRRegListOperand_isra_0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4);
    break;
  case 0x14b:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if ((uVar7 >> 0x17 & 1) == 0) {
      MCOperand_CreateImm0(param_4,uVar7 & 0xff | 0x100);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0x14c:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x14d:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a6df4;
  case 0x14e:
  case 0x150:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar10 = (uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf;
    goto LAB_001a44c4;
  case 0x14f:
    iVar2 = DecodeVMOVRRS_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x151:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    goto LAB_001a4c4c;
  case 0x152:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
joined_r0x001a6df4:
    if (iVar2 != 1) {
      if (iVar2 == 3) {
        return param_1;
      }
      return 0;
    }
    goto LAB_001a4f20;
  case 0x153:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a8e24:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a8e24;
      MCOperand_CreateReg0(param_4,0);
    }
    uVar10 = uVar7 & 0xff;
    uVar7 = (uVar7 >> 0x16 & 1) << 8 | (uVar7 & 0xf000) >> 3;
    uVar1 = uVar7 >> 8;
    uVar12 = *(undefined2 *)(HPR + (ulong)(uVar7 >> 8) * 2);
    if ((param_3 & 0xff) == 0) {
      MCOperand_CreateReg0(param_4,uVar12);
      return 1;
    }
    if (uVar1 + uVar10 < 0x21) {
      MCOperand_CreateReg0(param_4,uVar12);
      if (uVar10 == 1) goto switchD_001a440c_caseD_33;
      if (uVar1 == 0x1f) {
        return 0;
      }
      uVar10 = uVar10 - 1;
      iVar2 = 3;
    }
    else {
      MCOperand_CreateReg0(param_4,uVar12);
      iVar2 = 1;
      uVar10 = 0x1f - uVar1;
      if (uVar1 == 0x1f) {
        return 1;
      }
    }
    uVar8 = (ulong)(uVar1 + 2);
    while (MCOperand_CreateReg0(param_4,*(undefined2 *)(&DAT_0022e5fe + uVar8 * 2)),
          ((int)uVar8 - uVar1) - 1 < uVar10) {
      uVar8 = uVar8 + 1;
      if (uVar8 == (ulong)(0x1e - uVar1) + (ulong)(uVar1 + 3)) {
        return 0;
      }
    }
    if (iVar2 == 1) {
      return 1;
    }
    goto switchD_001a440c_caseD_33;
  case 0x154:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a8d88:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a8d88;
      MCOperand_CreateReg0(param_4,0);
    }
    iVar2 = DecodeDPRRegListOperand_isra_0
                      (param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4 | (uVar7 & 0x400000) >> 10);
    break;
  case 0x155:
    uVar12 = *(undefined2 *)(GPR + (uVar8 >> 0x10 & 0xf) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    MCOperand_CreateReg0(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar10);
LAB_001a8880:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a8880;
      MCOperand_CreateReg0(param_4,0);
    }
    iVar2 = DecodeDPRRegListOperand_isra_0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4);
    break;
  case 0x156:
    iVar2 = DecodeForVMRSandVMSR_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x157:
  case 0x15e:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xf | (uVar7 & 0xf0000) >> 0xc);
    goto joined_r0x001a4534;
  case 0x158:
  case 0x15a:
  case 0x15b:
  case 0x15d:
    uVar10 = (uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb;
LAB_001a4428:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar10 * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    goto joined_r0x001a4534;
  case 0x159:
  case 0x15f:
    uVar10 = (uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb;
LAB_001a44c4:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar10 * 2));
    goto joined_r0x001a4534;
  case 0x15c:
    uVar12 = *(undefined2 *)(HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2)
    ;
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateImm0(param_4,(uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
joined_r0x001a4534:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar7 >> 0x1c == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar7 >> 0x1c);
    }
    else {
LAB_001a45f8:
      MCOperand_CreateImm0(param_4,uVar7 >> 0x1c);
      if (uVar7 >> 0x1c == 0xe) {
LAB_001a460c:
        MCOperand_CreateReg0(param_4,0);
        goto switchD_001a440c_caseD_33;
      }
    }
LAB_001a4478:
    MCOperand_CreateReg0(param_4,3);
    goto switchD_001a440c_caseD_33;
  case 0x160:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    uVar8 = (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
    puVar6 = HPR;
    goto LAB_001a4c64;
  case 0x161:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateImm0(param_4,uVar7 & 0xf | (uVar7 & 0xf0000) >> 0xc);
    goto joined_r0x001a8948;
  case 0x162:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0x163:
    uVar12 = *(undefined2 *)(HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2)
    ;
LAB_001a4c4c:
    MCOperand_CreateReg0(param_4,uVar12);
    puVar6 = DPR;
    uVar8 = (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto LAB_001a4c64;
  case 0x164:
    puVar6 = DPR;
    uVar8 = (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
LAB_001a4c64:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(puVar6 + uVar8 * 2));
joined_r0x001a8948:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    goto LAB_001a45f8;
  case 0x165:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateImm0(param_4,(uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
    iVar2 = DecodePredicateOperand_isra_0(param_4,uVar7 >> 0x1c);
    break;
  case 0x166:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
              );
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x18 & 1);
    return uVar3;
  case 0x167:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x17 & 3);
    return uVar3;
  case 0x168:
    uVar12 = *(undefined2 *)
              (DPR + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_4,uVar12);
    MCOperand_CreateReg0(param_4,uVar12);
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x14 & 3);
    return uVar3;
  case 0x169:
    iVar2 = DecodeNEONComplexLane64Instruction_isra_0(param_4,param_3 & 0xffffffff);
    break;
  case 0x16a:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0
                      (param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x18 & 1);
    return uVar9;
  case 0x16b:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 0x17 & 3);
    return uVar3;
  case 0x16c:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = DecodeQPRRegisterClass_part_0(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = DecodeDPRRegisterClass_isra_0(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar8 >> 5 & 1);
    MCOperand_CreateImm0(param_4,uVar8 >> 0x14 & 3);
    return uVar3;
  case 0x16d:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x16e:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x16f:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x170:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2));
    goto switchD_001a440c_caseD_33;
  case 0x171:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)
                        (HPR + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    goto switchD_001a440c_caseD_33;
  default:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar8 >> 0xc & 0xf) * 2));
    uVar5 = uVar8 >> 0x10;
LAB_001a4378:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar5 & 0xf) * 2));
LAB_001a4388:
    uVar8 = uVar8 >> 0x1c;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (param_3 & 0xf) * 2));
    uVar10 = (uint)uVar8;
joined_r0x001a6010:
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = MCInst_getOpcode(param_4);
    if (iVar2 == 0xc4f) {
      if ((int)uVar8 == 0xe) {
        return 0;
      }
      MCOperand_CreateImm0(param_4,uVar8);
LAB_001a43c4:
      MCOperand_CreateReg0(param_4,3);
    }
    else {
      MCOperand_CreateImm0(param_4,uVar8);
      if ((int)uVar8 != 0xe) goto LAB_001a43c4;
      MCOperand_CreateReg0(param_4,0);
    }
LAB_001a43d0:
    if ((uVar7 >> 0x14 & 1) == 0) goto LAB_001a43d4;
    goto LAB_001a46bc;
  }
  if (iVar2 == 1) {
LAB_001a4f20:
    param_1 = 1;
  }
  else {
    if (iVar2 != 3) {
      return 0;
    }
switchD_001a440c_caseD_33:
  }
  return param_1;
}

