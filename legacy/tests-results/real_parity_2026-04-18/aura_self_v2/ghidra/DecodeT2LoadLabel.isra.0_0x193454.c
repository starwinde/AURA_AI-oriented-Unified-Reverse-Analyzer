
undefined8 DecodeT2LoadLabel_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar2 = (uint)((param_2 & 0xffffffff) >> 0xc) & 0xf;
  uVar1 = (uint)param_2 & 0xfff;
  if (uVar2 == 0xf) {
    uVar4 = MCInst_getOpcode();
    if (uVar4 == 0xb32) {
      MCInst_setOpcode(param_1,0xb72);
    }
    else if (uVar4 < 0xb33) {
      if ((uVar4 == 0xb1d) || (uVar4 == 0xb2b)) {
        MCInst_setOpcode(param_1,0xb6e);
      }
    }
    else if (uVar4 == 0xb39) {
      return 0;
    }
  }
  iVar3 = MCInst_getOpcode(param_1);
  if ((iVar3 - 0xb6eU & 0xfffffffb) != 0) {
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar2 * 2));
  }
  uVar5 = (ulong)uVar1;
  if ((((uint)param_2 >> 0x17 & 1) == 0) && (uVar5 = (ulong)(int)-uVar1, (param_2 & 0xfff) == 0)) {
    uVar5 = 0xffffffff80000000;
  }
  MCOperand_CreateImm0(param_1,uVar5);
  return 3;
}

