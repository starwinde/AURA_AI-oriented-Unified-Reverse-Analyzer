
undefined8 DecodeT2AddrModeImm8_isra_0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = param_2 >> 9 & 0x7fffff;
  iVar2 = MCInst_getOpcode();
  if (((iVar2 - 0xbe6U < 0x18) && ((0x8a2011UL >> ((ulong)(iVar2 - 0xbe6U) & 0x3f) & 1) != 0)) &&
     ((int)uVar5 == 0xf)) {
    return 0;
  }
  uVar1 = (uint)param_2 & 0xff;
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 < 0xb3c) {
    if (0xb17 < uVar3) {
      uVar4 = 0x810204001 >> ((ulong)(uVar3 - 0xb18) & 0x3f);
joined_r0x00192878:
      if ((uVar4 & 1) != 0) {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
        uVar5 = (ulong)uVar1;
        goto LAB_00192844;
      }
    }
  }
  else if (uVar3 - 0xbe6 < 0x14) {
    uVar4 = 0x82001L >> ((ulong)(uVar3 - 0xbe6) & 0x3f);
    goto joined_r0x00192878;
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
  uVar5 = 0xffffffff80000000;
  if (((param_2 & 0x1ff) != 0) && (uVar5 = (long)(int)-uVar1, (param_2 & 0x100) != 0)) {
    uVar5 = (ulong)uVar1;
  }
LAB_00192844:
  MCOperand_CreateImm0(param_1,uVar5);
  return 3;
}

