
undefined4 DecodeT2LDRDPreInstruction_isra_0(long param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  undefined4 uVar8;
  int iVar9;
  ulong uVar10;
  
  uVar5 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar7 = (ulong)(param_2 >> 8) & 0xf;
  uVar10 = (ulong)(param_2 >> 0x10) & 0xf;
  uVar8 = 3;
  iVar4 = (int)uVar5;
  iVar6 = (int)uVar7;
  iVar9 = (int)uVar10;
  if (((~(param_2 >> 0x18) & 1) != 0 || (param_2 >> 0x15 & 1) != 0) &&
     (uVar8 = 3, iVar4 == iVar9 || iVar6 == iVar9)) {
    uVar8 = 1;
  }
  if (iVar4 == iVar6) {
    uVar8 = 1;
  }
  if (iVar4 == 0xd) {
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) == 0) {
      MCOperand_CreateReg0(param_1,0xc);
      goto LAB_0019a7c0;
    }
LAB_0019a754:
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
    if (iVar6 != 0xd) goto LAB_0019a774;
LAB_0019a7d0:
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) goto LAB_0019a77c;
    uVar8 = 1;
    MCOperand_CreateReg0(param_1,0xc);
  }
  else {
    if (iVar4 != 0xf) goto LAB_0019a754;
    MCOperand_CreateReg0(param_1,0xb);
LAB_0019a7c0:
    uVar8 = 1;
    if (iVar6 == 0xd) goto LAB_0019a7d0;
LAB_0019a774:
    if (iVar6 == 0xf) {
      uVar8 = 1;
      MCOperand_CreateReg0(param_1,0xb);
    }
    else {
LAB_0019a77c:
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar7 * 2));
    }
  }
  if (iVar9 == 0xd) {
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) == 0) {
      uVar8 = 1;
      MCOperand_CreateReg0(param_1,0xc);
      goto LAB_0019a840;
    }
  }
  else if (iVar9 == 0xf) {
    uVar8 = 1;
    MCOperand_CreateReg0(param_1,0xb);
    goto LAB_0019a840;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar10 * 2));
LAB_0019a840:
  uVar1 = param_2 & 0xff;
  uVar3 = param_2 >> 0x17 & 1;
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar10 * 2));
  if (uVar3 == 0 && uVar1 == 0) {
    MCOperand_CreateImm0(param_1,0xffffffff80000000);
  }
  else {
    uVar2 = -uVar1;
    if (uVar3 != 0) {
      uVar2 = uVar1;
    }
    MCOperand_CreateImm0(param_1,(long)(int)(uVar2 << 2));
  }
  return uVar8;
}

