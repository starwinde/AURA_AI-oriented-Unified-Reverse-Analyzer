
undefined8 DecodeThumb2BCCInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = param_2 & 0xffffffff;
  uVar3 = uVar2 >> 0x16 & 0xf;
  if ((int)uVar3 - 0xeU < 2) {
    iVar1 = (int)(uVar2 >> 4);
    if (iVar1 == 0xf3bf8f5) {
      MCInst_setOpcode(param_1,0xaf2);
    }
    else if (iVar1 == 0xf3bf8f6) {
      MCInst_setOpcode(param_1,0xaf9);
    }
    else {
      if (iVar1 != 0xf3bf8f4) {
        return 0;
      }
      MCInst_setOpcode(param_1,0xaf3);
    }
    MCOperand_CreateImm0(param_1,param_2 & 0xf);
  }
  else {
    MCOperand_CreateImm0
              (param_1,(long)((ulong)(((uint)(uVar2 >> 0xb) & 1) << 0x13 |
                                      ((uint)(uVar2 >> 0xd) & 1) << 0x12 |
                                      ((uint)(uVar2 >> 0x1a) & 1) << 0x14 |
                                      ((uint)param_2 & 0x3f0000) >> 4 | ((uint)param_2 & 0x7ff) << 1
                                     ) << 0x2b) >> 0x2b);
    MCInst_getOpcode(param_1);
    MCOperand_CreateImm0(param_1,uVar3);
    MCOperand_CreateReg0(param_1,3);
  }
  return 3;
}

