
undefined8 FUN_0019391c(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  ulong uVar5;
  
  uVar5 = param_2 & 0xffffffff;
  uVar3 = (uint)(uVar5 >> 0x10) & 0xf;
  uVar1 = (uint)(uVar5 >> 0xc) & 0xf;
  if (uVar3 == 0xf) {
    uVar3 = MCInst_getOpcode();
    if (uVar3 == 0xb37) {
      MCInst_setOpcode(param_1,0xb39);
    }
    else if (uVar3 < 0xb38) {
      if (uVar3 == 0xb29) {
        MCInst_setOpcode(param_1,0xb2b);
      }
      else if (uVar3 == 0xb30) {
        MCInst_setOpcode(param_1,0xb32);
      }
      else {
        if (uVar3 != 0xb1b) {
          return 0;
        }
        MCInst_setOpcode(param_1,0xb1d);
      }
    }
    else if (uVar3 == 0xb6c) {
      MCInst_setOpcode(param_1,0xb6e);
    }
    else if (uVar3 == 0xb70) {
      MCInst_setOpcode(param_1,0xb72);
    }
    else {
      if (uVar3 != 0xb3e) {
        return 0;
      }
      MCInst_setOpcode(param_1,0xb40);
    }
    uVar4 = DecodeT2LoadLabel_isra_0(param_1,uVar5);
    return uVar4;
  }
  if (uVar1 == 0xf) {
    iVar2 = MCInst_getOpcode();
    if (iVar2 == 0xb30) {
      MCInst_setOpcode(param_1,0xb70);
    }
    else {
      if (iVar2 == 0xb37) {
        return 0;
      }
      if (iVar2 == 0xb29) {
        MCInst_setOpcode(param_1,0xb69);
      }
    }
  }
  iVar2 = MCInst_getOpcode(param_1);
  if ((7 < iVar2 - 0xb69U) || ((0x89UL >> ((ulong)(iVar2 - 0xb69U) & 0x3f) & 1) == 0)) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar1 * 2));
  }
  iVar2 = MCInst_getOpcode(param_1);
  if (((iVar2 - 0xbe9U < 0x14) && ((0x82001UL >> ((ulong)(iVar2 - 0xbe9U) & 0x3f) & 1) != 0)) &&
     (uVar3 == 0xf)) {
    return 0;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar3 * 2));
  MCOperand_CreateImm0(param_1,(uint)param_2 & 0xfff);
  return 3;
}

