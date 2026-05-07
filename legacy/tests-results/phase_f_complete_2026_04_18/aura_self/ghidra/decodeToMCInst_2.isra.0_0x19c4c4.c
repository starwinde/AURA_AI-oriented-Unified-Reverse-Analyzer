
/* WARNING: Type propagation algorithm not settling */

undefined4 decodeToMCInst_2_isra_0(undefined4 param_1,undefined4 param_2,uint param_3,long param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined2 uVar10;
  
  uVar1 = param_3 & 0xffff;
  uVar7 = (ulong)uVar1;
  switch(param_2) {
  case 1:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegImmOperand_isra_0(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      MCOperand_CreateReg0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 2:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegRegOperand_isra_0
                      (param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      MCOperand_CreateReg0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 3:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegRegOperand_isra_0
                      (param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a0cc8:
        MCOperand_CreateReg0(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a0cc8;
    }
    goto switchD_0019c568_caseD_9;
  case 4:
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 5:
    uVar10 = *(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 6:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 7:
    iVar4 = DecodeAddrMode3Instruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 8:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    break;
  case 9:
    goto switchD_0019c568_caseD_9;
  case 10:
    MCOperand_CreateImm0(param_4,uVar1 >> 9 & 1);
    break;
  case 0xb:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0xc:
    iVar4 = DecodeQADDInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xd:
    iVar4 = DecodeSMLAInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xe:
    iVar4 = DecodeSwap_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xf:
    MCOperand_CreateImm0(param_4,param_3 & 0xf | (uVar1 >> 8) << 4);
    break;
  case 0x10:
    iVar4 = DecodeTSTInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x11:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegImmOperand_isra_0(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x12:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegRegOperand_isra_0
                      (param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x13:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      uVar10 = 0xb;
      iVar4 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      iVar4 = 3;
      uVar10 = *(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2);
      MCOperand_CreateReg0(param_4,uVar10);
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    if ((int)uVar7 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,uVar10);
    uVar3 = 1;
    if (iVar4 != 1) {
      uVar3 = param_1;
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    param_1 = uVar3;
    goto joined_r0x001a29a4;
  case 0x14:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x16:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x17:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x18:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x19:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodeBankedReg_isra_0(param_4,(uVar1 >> 8 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1a:
    iVar4 = DecodeMSRMask_isra_0(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1b:
    uVar7 = (ulong)(uVar1 >> 8) & 1;
    lVar5 = lookupBankedRegByEncoding((int)uVar7 << 4);
    if (lVar5 != 0) {
      MCOperand_CreateImm0(param_4,uVar7 << 4);
      if ((param_3 & 0xf) == 0xf) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xb);
      }
      else {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
      }
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1c:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x1d:
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x1e:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x1f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x20:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 3) {
      uVar3 = 0x45;
    }
    else if (uVar1 < 4) {
      uVar3 = 0x43;
      if ((uVar1 != 1) && (uVar3 = 0x44, uVar1 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar1 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar1 != 0xc) goto switchD_0019c568_caseD_9;
      uVar3 = 0x4e;
    }
    MCOperand_CreateReg0(param_4,uVar3);
    uVar1 = param_3 & 0xf;
    if (uVar1 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc) == 0) {
      uVar3 = 0x43;
      if ((uVar1 != 1) && (uVar3 = 0x44, uVar1 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar1 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar1 != 0xc) goto switchD_0019c568_caseD_9;
      uVar3 = 0x4e;
    }
    MCOperand_CreateReg0(param_4,uVar3);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateReg0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x21:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = DecodeSORegImmOperand_isra_0(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      MCOperand_CreateReg0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x22:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    break;
  case 0x23:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x24:
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x25:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodeSORegRegOperand_isra_0
                      (param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a2478:
        MCOperand_CreateReg0(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a2478;
    }
    goto switchD_0019c568_caseD_9;
  case 0x26:
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x27:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x28:
    uVar10 = *(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x29:
    iVar4 = DecodeDoubleRegStore_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2a:
    iVar4 = DecodeDoubleRegLoad_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2b:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
      param_1 = 1;
      MCOperand_CreateImm0(param_4,0);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
      MCOperand_CreateImm0(param_4,0);
    }
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x2c:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,param_3 & 0xf | (uVar1 >> 8 & 0xf) << 4);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x2d:
    iVar4 = DecodeLDR_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,param_3 & 0xf | (uVar1 >> 8 & 0xf) << 4);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x2f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x30:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x31:
    iVar4 = DecodeArmMOVTWInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x32:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x33:
    goto LAB_0019c63c;
  case 0x34:
    iVar4 = DecodeHINTInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x35:
    iVar4 = DecodeMSRMask_isra_0(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x36:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x37:
    iVar4 = DecodeAddrMode2IdxInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x38:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = -(param_3 & 0xfff);
    if (iVar4 == 0) {
      iVar4 = -0x80000000;
    }
    MCOperand_CreateImm0(param_4,iVar4);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x39:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = -(param_3 & 0xfff);
    if (iVar4 == 0) {
      iVar4 = -0x80000000;
    }
    MCOperand_CreateImm0(param_4,iVar4);
    break;
  case 0x3a:
    iVar4 = DecodeSTRPreImm_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x3b:
    iVar4 = DecodeLDRPreImm_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x3c:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodeAddrModeImm12Operand_isra_0(param_4,param_3 & 0xfff);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x3d:
  case 0x3e:
  case 0x114:
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    break;
  case 0x3f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = DecodeSORegMemOperand_isra_0(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x40:
    iVar4 = DecodeSORegMemOperand_isra_0(param_4,param_3 & 0xfef);
    goto joined_r0x001a29a4;
  case 0x41:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x42:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 7 & 0x1f);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x43:
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x44:
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    if (iVar4 == 1) {
      return 1;
    }
    goto joined_r0x0019c998;
  case 0x45:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x46:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 10 & 3);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x47:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 10 & 3);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x48:
    iVar4 = DecodeSTRPreReg_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x49:
    iVar4 = DecodeLDRPreReg_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x4a:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateImm0(param_4,0);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 7 & 0x1f | (uVar1 >> 6 & 1) << 5);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4b:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateImm0(param_4,0);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4c:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 7 & 0x1f);
    MCOperand_CreateImm0(param_4,0);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4d:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = DecodeSORegMemOperand_isra_0(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x4e:
    uVar10 = *(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    if ((param_3 & 0xf80) == 0) {
      MCOperand_CreateImm0(param_4,0xfffffffe);
    }
    else {
      param_1 = 1;
      MCOperand_CreateImm0(param_4,0xfffffffe);
    }
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x4f:
    if (uVar1 >> 0xc == 0xf) {
      MCOperand_CreateReg0(param_4,0xb);
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      uVar10 = *(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2);
      MCOperand_CreateReg0(param_4,uVar10);
      MCOperand_CreateReg0(param_4,uVar10);
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    iVar4 = DecodeBitfieldMaskOperand_isra_0(param_4,uVar1 >> 7 & 0x1f);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x50:
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    iVar4 = DecodeRegListOperand_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x51:
  case 0x113:
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0x52:
    iVar4 = DecodeMemMultipleWritebackInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x53:
    MCOperand_CreateImm0(param_4,uVar7 & 0x1f);
    break;
  case 0x54:
    iVar4 = DecodeBranchImmInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x55:
    MCOperand_CreateImm0(param_4,(uVar7 & 0x7fff) << 1);
    break;
  case 0x56:
    iVar4 = DecoderForMRRC2AndMCRR2_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x57:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,uVar1 >> 4 & 0xf);
      if (uVar1 >> 0xc == 0xf) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xb);
      }
      else {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
      }
      MCOperand_CreateReg0(param_4,0x42);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x58:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeCoprocessor_isra_0(param_4,uVar1 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 4 & 0xf);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x59:
    MCOperand_CreateImm0(param_4,uVar7);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x5a:
    iVar4 = DecodeCopMemInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x5b:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar1 >> 0xc);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5c:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar1 >> 0xc);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5d:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5e:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      MCInst_getOpcode(param_4);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateReg0(param_4,3);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5f:
    if (uVar1 >> 0xc == 0xf) {
      MCOperand_CreateReg0(param_4,2);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x60:
    if (uVar1 >> 0xc == 0xf) {
      MCOperand_CreateReg0(param_4,2);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,0);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 7);
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x61:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x62:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          param_1 = uVar3;
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 99:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 100:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x65:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x66:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
        }
        else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x67:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
    if ((param_3 & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x68:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x69:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          if ((param_3 & 1) == 0) {
            iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
            goto joined_r0x001a29a4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6b:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a2c00:
        MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a2c00;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a5280:
              MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a5280;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a52e8:
              MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a52e8;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a0da4:
          MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a0da4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x70:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 7);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a349c:
          MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a349c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x71:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a3330:
        MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a3330;
    }
    goto switchD_0019c568_caseD_9;
  case 0x72:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a51e4:
              MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a51e4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x73:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a52a4:
              MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a52a4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x74:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x75:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a31e4:
          MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a31e4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x76:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a32b4:
          MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a32b4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x77:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 10 & 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x78:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 9 & 3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x79:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,uVar1 >> 8 & 7);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x7a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a33ac:
            MCOperand_CreateImm0(param_4,uVar1 >> 0xb & 1);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a33ac;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a2b20:
            MCOperand_CreateImm0(param_4,uVar1 >> 10 & 3);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a2b20;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_0019ee60:
            MCOperand_CreateImm0(param_4,uVar1 >> 9 & 7);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_0019ee60;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_0019ede4:
            MCOperand_CreateImm0(param_4,uVar1 >> 8 & 0xf);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_0019ede4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    break;
  case 0x7f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x80:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    uVar2 = param_3 & 0xf | (uVar1 >> 5 & 1) << 4;
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)uVar2 * 2));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,uVar1 >> 0xc);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,uVar2);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x81:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) &&
         (uVar2 = param_3 & 0xf | (uVar1 >> 5 & 1) << 4, (param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar2);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar2);
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x82:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x83:
    iVar4 = DecodeVSHLMaxInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x84:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x85:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        if (iVar4 == 1) {
          uVar3 = 1;
        }
        else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          param_1 = uVar3;
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x86:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x87:
    iVar4 = DecodeTBLInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x88:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x89:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x8a:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x8b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,8);
    break;
  case 0x8f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0x10);
    break;
  case 0x90:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0x20);
    break;
  case 0x91:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,8);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x92:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0x10);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x93:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0x20);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x94:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x95:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x96:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x97:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x98:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x99:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x9a:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateImm0(param_4,8);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9b:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateImm0(param_4,0x10);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9c:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateImm0(param_4,0x20);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9e:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0
                  (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2)
                  );
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa0:
    iVar4 = DecodeVCVTD_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xa1:
    iVar4 = DecodeNEONModImmInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xa2:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0x40);
    break;
  case 0xa3:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0x40);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0xa4:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0xa5:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0xa6:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a352c:
          MCOperand_CreateImm0(param_4,8);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a352c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa7:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2944:
          MCOperand_CreateImm0(param_4,0x10);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2944;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa8:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2aa4:
          MCOperand_CreateImm0(param_4,0x20);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2aa4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa9:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4f28:
            MCOperand_CreateImm0(param_4,8);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4f28;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xaa:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4ed4:
            MCOperand_CreateImm0(param_4,0x10);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4ed4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xab:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4d48:
            MCOperand_CreateImm0(param_4,0x20);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4d48;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xac:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a1aa8:
          MCOperand_CreateImm0(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a1aa8;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xad:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4be8:
            MCOperand_CreateImm0(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4be8;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xae:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2d74:
          MCOperand_CreateImm0(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2d74;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xaf:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4f7c:
            MCOperand_CreateImm0(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4f7c;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb0:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a28e4:
          MCOperand_CreateImm0(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a28e4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb1:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4da0:
            MCOperand_CreateImm0(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4da0;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb2:
    iVar4 = DecodeVCVTQ_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xb3:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_0019f3bc:
          MCOperand_CreateImm0(param_4,0x40);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_0019f3bc;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb4:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4e88:
            MCOperand_CreateImm0(param_4,0x40);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4e88;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb5:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_0019f328:
          MCOperand_CreateImm0(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_0019f328;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb6:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4e50:
            MCOperand_CreateImm0(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4e50;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb7:
    uVar10 = *(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,0);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0xb8:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    MCOperand_CreateImm0(param_4,0);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0xb9:
    uVar10 = *(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 1);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0xba:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 1);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0xbb:
    uVar10 = *(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,uVar1 >> 5 & 3);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0xbc:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    MCOperand_CreateImm0(param_4,uVar1 >> 5 & 3);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0xbd:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0xbe:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0xbf:
    if ((param_3 & 0xc0) != 0xc0) {
      iVar4 = DecodeVSTInstruction_isra_0(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xc0:
    iVar4 = DecodeVST1LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc1:
    iVar4 = DecodeVLD1LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc2:
    iVar4 = DecodeVST2LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc3:
    iVar4 = DecodeVLD2LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc4:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((uVar2 == 6) || (uVar2 == 7)) {
      if ((uVar1 >> 5 & 1) == 0) goto LAB_0019cc70;
    }
    else if ((uVar1 >> 4 & 3) != 3 || uVar2 != 10) {
LAB_0019cc70:
      iVar4 = DecodeVSTInstruction_isra_0(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xc5:
    iVar4 = DecodeVST3LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc6:
    iVar4 = DecodeVLD3LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 199:
    if (((param_3 & 0xc0) != 0xc0) &&
       (uVar1 = uVar1 >> 8 & 0xf, (param_3 & 0x30) != 0x30 || uVar1 != 8 && uVar1 != 9)) {
      iVar4 = DecodeVSTInstruction_isra_0(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 200:
    iVar4 = DecodeVST4LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc9:
    iVar4 = DecodeVLD4LN_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xca:
    if (((param_3 & 0xc0) != 0xc0) && ((uVar1 >> 5 & 1) == 0)) {
      iVar4 = DecodeVSTInstruction_isra_0(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xcb:
    iVar4 = DecodeVLD1DupInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcc:
    iVar4 = DecodeVLD2DupInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcd:
    iVar4 = DecodeVLD3DupInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xce:
    iVar4 = DecodeVLD4DupInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcf:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    break;
  case 0xd0:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    break;
  case 0xd1:
    iVar4 = DecodeThumbAddSPReg_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xd2:
    uVar10 = *(undefined2 *)(GPR + (ulong)(param_3 & 7 | (uVar1 >> 7 & 1) << 3) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd3:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 7 | (uVar1 >> 7 & 1) << 3) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd4:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd5:
    uVar1 = uVar1 >> 3 & 0xf;
    if (uVar1 != 0xf) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
      return param_1;
    }
    goto LAB_001a35e8;
  case 0xd6:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2));
    MCOperand_CreateImm0(param_4,(uVar7 & 0xff) << 2);
    break;
  case 0xd7:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (((ulong)(uVar1 >> 3) & 0x3f) >> 3) * 2));
    break;
  case 0xd8:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateImm0(param_4,((ulong)(uVar1 >> 3) & 0xff) >> 3);
    break;
  case 0xd9:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2));
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    break;
  case 0xda:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2));
    iVar4 = MCInst_getOpcode(param_4);
    if (iVar4 == 0xc3e) {
      MCOperand_CreateReg0(param_4,0xc);
    }
    else if (iVar4 != 0xc42) goto switchD_0019c568_caseD_9;
  case 0xe2:
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    break;
  case 0xdb:
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateReg0(param_4,0xc);
    MCOperand_CreateImm0(param_4,uVar7 & 0x7f);
    break;
  case 0xdc:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateImm0(param_4,(ulong)(uVar1 >> 3 & 0x1f | (uVar1 >> 9 & 1) << 5) << 1);
    break;
  case 0xdd:
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0xff | (uVar1 >> 8 & 1) << 0xe);
    goto joined_r0x001a29a4;
  case 0xde:
    MCOperand_CreateImm0(param_4,uVar1 >> 3 & 1);
    break;
  case 0xdf:
    MCOperand_CreateImm0(param_4,uVar1 >> 4 & 1 | 2);
    MCOperand_CreateImm0(param_4,uVar7 & 7);
    break;
  case 0xe0:
    MCOperand_CreateImm0(param_4,uVar7 & 0x3f);
    break;
  case 0xe1:
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0xff | (uVar1 >> 8 & 1) << 0xf);
    goto joined_r0x001a29a4;
  case 0xe3:
    MCOperand_CreateImm0(param_4,uVar1 >> 4 & 0xf);
    break;
  case 0xe4:
    uVar10 = *(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xe5:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2));
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xe6:
    uVar2 = uVar1 >> 8 & 0xf;
    MCOperand_CreateImm0
              (param_4,(long)(int)(-(uVar1 >> 7 & 1) & 0xfffffe00 | (param_3 & 0xff) << 1));
    if (uVar2 != 0xf) {
      iVar4 = MCInst_getOpcode(param_4);
      if (iVar4 != 0xc4f) {
        MCOperand_CreateImm0(param_4,uVar2);
        if (uVar2 == 0xe) {
          MCOperand_CreateReg0(param_4,0);
          return param_1;
        }
LAB_001a1d2c:
        MCOperand_CreateReg0(param_4,3);
        return param_1;
      }
      if (uVar2 != 0xe) {
        MCOperand_CreateImm0(param_4,uVar2);
        goto LAB_001a1d2c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xe7:
    MCOperand_CreateImm0
              (param_4,-((ulong)(uVar1 >> 10) & 1) & 0xfffffffffffff000 | (uVar7 & 0x7ff) << 1);
    break;
  case 0xe8:
    MCOperand_CreateImm0(param_4,(param_3 & 0x7fe) << 1 | 0xc00000);
    break;
  case 0xe9:
    MCOperand_CreateImm0(param_4,(uVar7 & 0x7ff) << 1 | 0xc00000);
    break;
  case 0xea:
    uVar1 = uVar1 >> 4 & 0xf;
    if (uVar1 == 0xf) {
      if ((param_3 & 0xf) != 0) {
        MCOperand_CreateImm0(param_4,0xe);
        MCOperand_CreateImm0(param_4,param_3 & 0xf);
        return 1;
      }
    }
    else if ((param_3 & 0xf) != 0) {
      MCOperand_CreateImm0(param_4,uVar1);
      MCOperand_CreateImm0(param_4,param_3 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0xeb:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0x5fff);
    goto joined_r0x001a29a4;
  case 0xec:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeRegListOperand_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xed:
    param_3 = param_3 & 0xf;
    MCOperand_CreateReg0(param_4,0x42);
    if (param_3 != 0xd) {
      if (param_3 != 0xf) {
LAB_001a1be0:
        MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
        return param_1;
      }
      goto LAB_001a35e8;
    }
    if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a1be0;
    goto LAB_001a3b78;
  case 0xee:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 0xef:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3658;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c9c4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c9c4;
      }
LAB_001a3658:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0xf0:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3700;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c804:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c804;
      }
LAB_001a3700:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0xf1:
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0xf2:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0xf3:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeRegListOperand_isra_0(param_4,param_3 & 0x5fff);
    goto joined_r0x001a29a4;
  case 0xf4:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeRegListOperand_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xf5:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3974;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c878:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c878;
      }
LAB_001a3974:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0xf6:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37ac;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c8ac:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c8ac;
      }
LAB_001a37ac:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a443c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c8d0:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c8d0;
      }
LAB_001a443c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    iVar4 = DecodeT2AddrModeImm0_1020s4_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xf7:
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36e4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c70c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c70c;
      }
LAB_001a36e4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44b8;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019c730:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019c730;
      }
LAB_001a44b8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0xf8:
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a39b0;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a199c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a199c;
      }
LAB_001a39b0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a469c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a19c0:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a19c0;
      }
LAB_001a469c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,uVar1 >> 8 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0xf9:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37e4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a1968:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a1968;
      }
LAB_001a37e4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0xfa:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3638;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e21c:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e21c;
      }
LAB_001a3638:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    break;
  case 0xfb:
    iVar4 = DecodeThumbTableBranch_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xfc:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a361c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a0f20:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a0f20;
      }
LAB_001a361c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44d4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a0f44:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a0f44;
      }
LAB_001a44d4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0xfd:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3958;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a0eb8:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a0eb8;
      }
LAB_001a3958:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a43c4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_001a0edc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_001a0edc;
      }
LAB_001a43c4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    iVar4 = DecodeT2AddrModeImm8s4_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xfe:
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(param_3 & 0xf) * 2));
    }
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0xff:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3994;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e25c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e25c;
      }
LAB_001a3994:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4624;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e280:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e280;
      }
LAB_001a4624:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x100:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3674;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e050:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e050;
      }
LAB_001a3674:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a48f0;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e074:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e074;
      }
LAB_001a48f0:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x101:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38ac;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dfe4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dfe4;
      }
LAB_001a38ac:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    break;
  case 0x102:
    MCOperand_CreateReg0(param_4,0x42);
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a373c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019df7c:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019df7c;
      }
LAB_001a373c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4a60;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dfa0:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dfa0;
      }
LAB_001a4a60:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xff) == 0) {
      MCOperand_CreateImm0(param_4,0xffffffff80000000);
    }
    else {
      DecodeT2Imm8S4_part_0(param_4,param_3 & 0xff);
    }
    break;
  case 0x103:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a393c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019defc:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019defc;
      }
LAB_001a393c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44f4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019df20:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019df20;
      }
LAB_001a44f4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    if ((param_3 & 0xff) == 0) {
      MCOperand_CreateImm0(param_4,0xffffffff80000000);
    }
    else {
      DecodeT2Imm8S4_part_0(param_4,param_3 & 0xff);
    }
    break;
  case 0x104:
    iVar4 = DecodeT2STRDPreInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x105:
    iVar4 = DecodeT2LDRDPreInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x106:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3790;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019db50:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019db50;
      }
LAB_001a3790:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    iVar4 = DecodeSORegImmOperand_isra_0
                      (param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x107:
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeT2SOImm_isra_0(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    goto joined_r0x001a29a4;
  case 0x108:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37c8;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019de5c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019de5c;
      }
LAB_001a37c8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeT2SOImm_isra_0(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x109:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3600;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019de00:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019de00;
      }
LAB_001a3600:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    iVar4 = DecodeT2SOImm_isra_0(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x10a:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeT2SOImm_isra_0(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateReg0(param_4,0);
    break;
  case 0x10b:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      MCOperand_CreateReg0(param_4,0xb);
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    break;
  case 0x10c:
    MCOperand_CreateImm0(param_4,param_3 & 0xff | (param_3 & 0x7000) >> 4);
    break;
  case 0x10d:
    iVar4 = DecodeT2MOVTWInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x10e:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a371c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e12c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e12c;
      }
LAB_001a371c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar6 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0x10f:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38e4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d92c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d92c;
      }
LAB_001a38e4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar6 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar7 & 0x1f);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    break;
  case 0x110:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a39cc;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dd58:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dd58;
      }
LAB_001a39cc:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar6 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    MCOperand_CreateImm0(param_4,uVar7 & 0x1f);
    break;
  case 0x111:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xc);
      }
      else {
        MCOperand_CreateReg0(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) {
        uVar10 = 0xc;
        goto LAB_001a4080;
      }
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dd04:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dd04;
      }
      uVar10 = *(undefined2 *)(GPR + uVar7 * 2);
      MCOperand_CreateReg0(param_4,uVar10);
LAB_001a4080:
      MCOperand_CreateReg0(param_4,uVar10);
    }
    iVar4 = DecodeBitfieldMaskOperand_isra_0
                      (param_4,uVar1 >> 6 & 3 | (param_3 & 0x1f) << 5 | (uVar1 >> 0xc & 7) << 2);
    goto joined_r0x001a29a4;
  case 0x112:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        MCOperand_CreateReg0(param_4,0xc);
      }
      else {
        MCOperand_CreateReg0(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) {
        uVar10 = 0xc;
        goto LAB_001a4050;
      }
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019e0cc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019e0cc;
      }
      uVar10 = *(undefined2 *)(GPR + uVar7 * 2);
      MCOperand_CreateReg0(param_4,uVar10);
LAB_001a4050:
      MCOperand_CreateReg0(param_4,uVar10);
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecodeBitfieldMaskOperand_isra_0
                      (param_4,uVar1 >> 6 & 3 | (param_3 & 0x1f) << 5 | (uVar1 >> 0xc & 7) << 2);
    goto joined_r0x001a29a4;
  case 0x115:
    iVar4 = DecodeT2CPSInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x116:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    break;
  case 0x117:
    iVar4 = DecodeMSRMask_isra_0(param_4,uVar1 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateReg0(param_4,0x42);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x118:
    uVar1 = uVar1 >> 8 & 0xf | (uVar1 >> 4 & 1) << 4;
    lVar5 = lookupBankedRegByEncoding(uVar1);
    if (lVar5 != 0) {
      MCOperand_CreateImm0(param_4,uVar1);
      MCOperand_CreateReg0(param_4,0x42);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x119:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3920;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019da7c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019da7c;
      }
LAB_001a3920:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 4) & 1;
    lVar5 = lookupBankedRegByEncoding((int)uVar7 << 4);
    if (lVar5 != 0) {
      MCOperand_CreateImm0(param_4,uVar7 << 4);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x11a:
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    break;
  case 0x11b:
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x11c:
    iVar4 = DecodeMSRMask_isra_0(param_4,param_3 & 0xcff);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateReg0(param_4,0x42);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x11d:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a381c;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dbdc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dbdc;
      }
LAB_001a381c:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    iVar4 = DecodeMSRMask_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0x11e:
    iVar4 = DecodeThumb2BCCInstruction_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x11f:
    MCOperand_CreateImm0
              (param_4,(((uint)((uVar7 ^ 0x800) >> 0xb) & 1) << 0x15 |
                        ((uint)((uVar7 ^ 0x2000) >> 0xd) & 1) << 0x16 | param_3 & 0x7ff) << 1);
    break;
  case 0x120:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3758;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019dc84:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019dc84;
      }
LAB_001a3758:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    iVar4 = DecodeT2AddrModeSOReg_isra_0(param_4,uVar1 >> 4 & 3 | (param_3 & 0xf) << 2);
    goto joined_r0x001a29a4;
  case 0x121:
    iVar4 = DecodeT2LdStPre_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x122:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3838;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d7e0:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d7e0;
      }
LAB_001a3838:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    iVar4 = DecodeT2AddrModeImm8_isra_0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0x123:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3890;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d790:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d790;
      }
LAB_001a3890:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    iVar4 = DecodeT2AddrModeImm8_isra_0(param_4,param_3 & 0xff | (uVar1 >> 9 & 1) << 8);
    goto joined_r0x001a29a4;
  case 0x124:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3870;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d748:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d748;
      }
LAB_001a3870:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
    }
    MCInst_getOpcode(param_4);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    break;
  case 0x125:
    iVar4 = DecodeT2LoadShift_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x126:
    iVar4 = DecodeT2LoadImm8_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x127:
    iVar4 = DecodeT2LoadT_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x128:
    iVar4 = DecodeT2LoadImm12_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x129:
    iVar4 = DecodeT2LoadLabel_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x12a:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3774;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d8d8:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d8d8;
      }
LAB_001a3774:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 299:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3904;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d880:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d880;
      }
LAB_001a3904:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a43a4;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d8a4:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d8a4;
      }
LAB_001a43a4:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    MCOperand_CreateImm0(param_4,uVar1 >> 4 & 3);
    break;
  case 300:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38c8;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019da1c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019da1c;
      }
LAB_001a38c8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    MCOperand_CreateImm0(param_4,uVar1 >> 4 & 3);
    break;
  case 0x12d:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36ac;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d828:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d828;
      }
LAB_001a36ac:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4910;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d84c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d84c;
      }
LAB_001a4910:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    break;
  case 0x12e:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3690;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d9c8:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d9c8;
      }
LAB_001a3690:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
LAB_001a3b78:
        MCOperand_CreateReg0(param_4,0xc);
        return 1;
      }
    }
    else if (param_3 == 0xf) {
LAB_001a35e8:
      MCOperand_CreateReg0(param_4,0xb);
      return 1;
    }
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)param_3 * 2));
    break;
  case 0x12f:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3800;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d5a4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d5a4;
      }
LAB_001a3800:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecoderGPRRegisterClass_isra_0(param_4,uVar1 >> 0xc);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x130:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36c8;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d530:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d530;
      }
LAB_001a36c8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4514;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d554:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d554;
      }
LAB_001a4514:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 0x131:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    break;
  case 0x132:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = DecodeT2AddrModeSOReg_isra_0(param_4,uVar1 >> 4 & 3 | (param_3 & 0xf) << 2);
    goto joined_r0x001a29a4;
  case 0x133:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = DecodeT2AddrModeImm8_isra_0(param_4,param_3 & 0xff | (uVar1 >> 9 & 1) << 8);
    goto joined_r0x001a29a4;
  case 0x134:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xfff);
    break;
  case 0x135:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3854;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d3b0:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d3b0;
      }
LAB_001a3854:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    if ((int)uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a47e8;
      MCOperand_CreateReg0(param_4,0xc);
LAB_0019d3d4:
      param_1 = 1;
    }
    else {
      if ((int)uVar7 == 0xf) {
        MCOperand_CreateReg0(param_4,0xb);
        goto LAB_0019d3d4;
      }
LAB_001a47e8:
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + uVar7 * 2));
    }
    MCOperand_CreateReg0(param_4,0x42);
    iVar4 = DecoderGPRRegisterClass_isra_0(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecoderGPRRegisterClass_isra_0(param_4,uVar2);
      if (iVar4 == 1) {
        uVar3 = 1;
      }
      else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
      iVar4 = DecoderGPRRegisterClass_isra_0(param_4,uVar7);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x136:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,uVar1 >> 4 & 0xf);
      MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
      MCOperand_CreateReg0(param_4,0x42);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x137:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      MCOperand_CreateImm0(param_4,uVar2);
      MCOperand_CreateImm0(param_4,uVar1 >> 4 & 0xf);
      MCOperand_CreateImm0(param_4,uVar7 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x138:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 0x1f);
    break;
  case 0x139:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 6) & 7) * 2));
    break;
  case 0x13a:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 7) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateImm0(param_4,uVar1 >> 6 & 7);
    break;
  case 0x13b:
    uVar10 = *(undefined2 *)(GPR + ((ulong)(uVar1 >> 8) & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff);
    break;
  case 0x13c:
    uVar10 = *(undefined2 *)(GPR + (uVar7 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    break;
  case 0x13d:
    uVar10 = *(undefined2 *)(GPR + (uVar7 & 7) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + ((ulong)(uVar1 >> 3) & 7) * 2));
    MCOperand_CreateReg0(param_4,uVar10);
    break;
  case 0x13e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff | 0x100);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x13f:
    uVar10 = *(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x140:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x141:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x142:
    iVar4 = DecodeVMOVSRR_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x143:
    MCOperand_CreateReg0(param_4,0x42);
    uVar2 = param_3 & 0xff;
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    uVar1 = ((uVar1 >> 0xc) << 9) >> 8;
    if ((param_3 & 0xff) == 0) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
      return 1;
    }
    if (uVar1 + uVar2 < 0x21) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
      uVar9 = uVar2 - 1;
      iVar4 = 3;
      if (uVar2 == 1) {
        return param_1;
      }
    }
    else {
      uVar9 = 0x1f - uVar1;
      iVar4 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
    }
    uVar7 = (ulong)(uVar1 + 2);
    do {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(&DAT_0022f7be + uVar7 * 2));
      if (uVar9 <= ((int)uVar7 - uVar1) - 1) {
joined_r0x001a5108:
        if (iVar4 == 1) {
          return 1;
        }
        return param_1;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 != (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1));
    goto switchD_0019c568_caseD_9;
  case 0x144:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff | 0x100);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x145:
    uVar10 = *(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x146:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x147:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x148:
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x149:
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    iVar4 = DecodeDPRRegListOperand_isra_0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x14a:
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    iVar4 = DecodeDPRRegListOperand_isra_0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x14b:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateImm0(param_4,uVar7 & 0xff | 0x100);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x14c:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      if (iVar4 == 1) {
        uVar3 = 1;
      }
      else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x14d:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodePredicateOperand_isra_0(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x14e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x14f:
    iVar4 = DecodeVMOVRRS_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x150:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x151:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x152:
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x153:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    uVar2 = param_3 & 0xff;
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    uVar1 = ((uVar1 >> 0xc) << 9) >> 8;
    if ((param_3 & 0xff) == 0) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
      return 1;
    }
    if (uVar1 + uVar2 < 0x21) {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
      uVar9 = uVar2 - 1;
      iVar4 = 3;
      if (uVar2 == 1) {
        return param_1;
      }
    }
    else {
      uVar9 = 0x1f - uVar1;
      iVar4 = 1;
      MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)uVar1 * 2));
    }
    uVar7 = (ulong)(uVar1 + 2);
    do {
      MCOperand_CreateReg0(param_4,*(undefined2 *)(&DAT_0022f7be + uVar7 * 2));
      if (uVar9 <= ((int)uVar7 - uVar1) - 1) goto joined_r0x001a5108;
      uVar7 = uVar7 + 1;
    } while (uVar7 != (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1));
    goto switchD_0019c568_caseD_9;
  case 0x154:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    iVar4 = DecodeDPRRegListOperand_isra_0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x155:
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,0x42);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    iVar4 = DecodeDPRRegListOperand_isra_0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x156:
    iVar4 = DecodeForVMRSandVMSR_isra_0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x157:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x158:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x159:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15a:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15b:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15c:
    uVar10 = *(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1 | (param_3 & 0xf) << 1);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15d:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x15f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x160:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x161:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateImm0(param_4,uVar7 & 0xf);
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x162:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x163:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x164:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    break;
  case 0x165:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1 | (param_3 & 0xf) << 1);
    iVar4 = DecodePredicateOperand_isra_0(param_4,0);
    goto joined_r0x001a29a4;
  case 0x166:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(DPR + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      MCOperand_CreateImm0(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x167:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a02c0:
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a02c0;
    }
    goto switchD_0019c568_caseD_9;
  case 0x168:
    uVar10 = *(undefined2 *)(DPR + (ulong)(uVar1 >> 0xc) * 2);
    MCOperand_CreateReg0(param_4,uVar10);
    MCOperand_CreateReg0(param_4,uVar10);
    iVar4 = DecodeDPRRegisterClass_isra_0(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a0230:
        MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
        MCOperand_CreateImm0(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a0230;
    }
    goto switchD_0019c568_caseD_9;
  case 0x169:
    iVar4 = DecodeNEONComplexLane64Instruction_isra_0(param_4,uVar7);
joined_r0x001a29a4:
    if (iVar4 == 1) {
      return 1;
    }
joined_r0x0019c998:
    if (iVar4 == 3) {
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x16a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        MCOperand_CreateReg0(param_4,*(undefined2 *)(QPR + ((ulong)(uVar1 >> 7) & 1) * 0x10));
        if ((param_3 & 1) == 0) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a03b4:
            MCOperand_CreateImm0(param_4,0);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a03b4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x16b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if (((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) && ((param_3 & 1) == 0)) {
            iVar4 = DecodeQPRRegisterClass_part_0(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a51c4:
              MCOperand_CreateImm0(param_4,0);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a51c4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x16c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = DecodeQPRRegisterClass_part_0(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = DecodeQPRRegisterClass_part_0(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = DecodeDPRRegisterClass_isra_0(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a535c:
              MCOperand_CreateImm0(param_4,uVar1 >> 5 & 1);
              MCOperand_CreateImm0(param_4,0);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a535c;
          }
        }
      }
    }
switchD_0019c568_caseD_9:
    param_1 = 0;
    break;
  case 0x16d:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x16e:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x16f:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x170:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + ((ulong)(uVar1 >> 7) & 1) * 2));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x171:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(HPR + (ulong)(uVar1 >> 0xc) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined2 *)(DPR + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    break;
  default:
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (ulong)(uVar1 >> 0xc) * 2));
    MCOperand_CreateReg0(param_4,0x42);
    MCOperand_CreateReg0(param_4,*(undefined2 *)(GPR + (uVar7 & 0xf) * 2));
    MCInst_getOpcode(param_4);
    MCOperand_CreateImm0(param_4,0);
    MCOperand_CreateReg0(param_4,3);
    MCOperand_CreateReg0(param_4,0);
    goto LAB_0019c63c;
  }
  return param_1;
LAB_0019c63c:
  return param_1;
}

