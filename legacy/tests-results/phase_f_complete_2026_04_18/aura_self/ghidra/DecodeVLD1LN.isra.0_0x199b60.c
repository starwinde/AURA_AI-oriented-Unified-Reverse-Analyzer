
ulong DecodeVLD1LN_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  
  uVar5 = param_2 >> 10 & 3;
  iVar4 = (int)uVar5;
  uVar6 = (uint)param_2;
  if (iVar4 == 1) {
    if ((uVar6 >> 5 & 1) == 0) {
      uVar5 = param_2 >> 6 & 3;
      lVar7 = (param_2 >> 4 & 1) << 1;
      goto LAB_00199bf8;
    }
  }
  else if (iVar4 == 2) {
    if ((uVar6 >> 6 & 1) == 0) {
      uVar5 = param_2 >> 7 & 1;
      if ((param_2 >> 4 & 3) == 0) {
        lVar7 = 0;
      }
      else {
        if (((uint)(param_2 >> 4) & 3) != 3) {
          return (ulong)(uVar6 & 0x40);
        }
        lVar7 = 4;
      }
      goto LAB_00199bf8;
    }
  }
  else if (iVar4 == 0) {
    if ((uVar6 >> 4 & 1) != 0) {
      return uVar5;
    }
    uVar5 = param_2 >> 5 & 7;
    lVar7 = 0;
LAB_00199bf8:
    uVar1 = uVar6 & 0xf;
    uVar8 = param_2 >> 0x10 & 0xf;
    uVar2 = *(undefined2 *)
             (DPR + (ulong)((uint)(param_2 >> 0xc) & 0xf | (uVar6 & 0x400000) >> 0x12) * 2);
    MCOperand_CreateReg0(param_1,uVar2);
    if (uVar1 == 0xf) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar8 * 2));
      MCOperand_CreateImm0(param_1,lVar7);
    }
    else {
      uVar3 = *(undefined2 *)(GPR + uVar8 * 2);
      MCOperand_CreateReg0(param_1,uVar3);
      MCOperand_CreateReg0(param_1,uVar3);
      MCOperand_CreateImm0(param_1,lVar7);
      if (uVar1 == 0xd) {
        MCOperand_CreateReg0(param_1,0);
      }
      else {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
      }
    }
    MCOperand_CreateReg0(param_1,uVar2);
    MCOperand_CreateImm0(param_1,uVar5);
    return 3;
  }
  return 0;
}

