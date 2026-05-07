
undefined8 DecodeVLD4LN_isra_0(undefined8 param_1,ulong param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  ulong uVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  
  uVar10 = param_2 & 0xffffffff;
  uVar11 = (uint)(uVar10 >> 10) & 3;
  if (uVar11 == 1) {
    bVar7 = (param_2 & 0x20) == 0;
    iVar9 = 6;
    if (bVar7) {
      iVar9 = 3;
    }
    uVar12 = (ulong)(((uint)(uVar10 >> 4) & 1) << 3);
    uVar13 = uVar10 >> 6 & 3;
    iVar8 = 2;
    if (!bVar7) {
      uVar11 = 2;
      iVar8 = 4;
    }
  }
  else if (uVar11 == 2) {
    uVar12 = uVar10 >> 4 & 3;
    if ((int)uVar12 != 0) {
      if ((int)uVar12 == 3) {
        return 0;
      }
      uVar12 = (ulong)(uint)(4 << uVar12);
    }
    bVar7 = (param_2 & 0x40) == 0;
    iVar8 = 4;
    if (bVar7) {
      iVar8 = 2;
      uVar11 = 1;
    }
    uVar13 = uVar10 >> 7 & 1;
    iVar9 = 6;
    if (bVar7) {
      iVar9 = 3;
    }
  }
  else {
    if ((uVar10 >> 10 & 3) != 0) {
      return 0;
    }
    uVar13 = uVar10 >> 5 & 7;
    iVar9 = 3;
    uVar12 = (ulong)(((uint)(uVar10 >> 4) & 1) << 2);
    uVar11 = 1;
    iVar8 = 2;
  }
  uVar6 = (uint)(uVar10 >> 0xc) & 0xf | ((uint)param_2 & 0x400000) >> 0x12;
  uVar1 = *(undefined2 *)(DPR + (ulong)uVar6 * 2);
  MCOperand_CreateReg0(param_1,uVar1);
  if (uVar6 + uVar11 < 0x20) {
    uVar2 = *(undefined2 *)(DPR + (ulong)(uVar6 + uVar11) * 2);
    MCOperand_CreateReg0(param_1,uVar2);
    if (uVar6 + iVar8 < 0x20) {
      uVar3 = *(undefined2 *)(DPR + (ulong)(uVar6 + iVar8) * 2);
      MCOperand_CreateReg0(param_1,uVar3);
      if (uVar6 + iVar9 < 0x20) {
        uVar4 = *(undefined2 *)(DPR + (ulong)(uVar6 + iVar9) * 2);
        uVar10 = uVar10 >> 0x10 & 0xf;
        uVar11 = (uint)param_2 & 0xf;
        MCOperand_CreateReg0(param_1,uVar4);
        if (uVar11 == 0xf) {
          MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar10 * 2));
          MCOperand_CreateImm0(param_1,uVar12);
        }
        else {
          uVar5 = *(undefined2 *)(GPR + uVar10 * 2);
          MCOperand_CreateReg0(param_1,uVar5);
          MCOperand_CreateReg0(param_1,uVar5);
          MCOperand_CreateImm0(param_1,uVar12);
          if (uVar11 == 0xd) {
            MCOperand_CreateReg0(param_1,0);
          }
          else {
            MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar11 * 2));
          }
        }
        MCOperand_CreateReg0(param_1,uVar1);
        MCOperand_CreateReg0(param_1,uVar2);
        MCOperand_CreateReg0(param_1,uVar3);
        MCOperand_CreateReg0(param_1,uVar4);
        MCOperand_CreateImm0(param_1,uVar13);
        return 3;
      }
    }
  }
  return 0;
}

