
undefined8 DecodeT2MOVTWInstruction_isra_0(long param_1,ulong param_2)

{
  int iVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  uVar3 = (uint)param_2;
  uVar5 = param_2 >> 8 & 0xf;
  uVar3 = (uVar3 >> 0x10 & 0xf) << 0xc | (uVar3 & 0x7000) >> 4 |
          uVar3 & 0xff | (uVar3 & 0x4000000) >> 0xf;
  iVar1 = MCInst_getOpcode();
  iVar4 = (int)uVar5;
  if (iVar1 == 0xb4c) {
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) {
        MCOperand_CreateReg0(param_1,0xc);
        goto LAB_00199234;
      }
      uVar6 = 1;
      MCOperand_CreateReg0(param_1,0xc);
      goto LAB_00199238;
    }
    if (iVar4 != 0xf) {
      uVar6 = 3;
      uVar2 = *(undefined2 *)(GPR + uVar5 * 2);
      MCOperand_CreateReg0(param_1);
      goto LAB_001991b8;
    }
    MCOperand_CreateReg0(param_1,0xb);
  }
  else {
    if (iVar4 == 0xd) {
LAB_00199234:
      uVar6 = 3;
LAB_00199238:
      uVar2 = 0xc;
      if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 6 & 1) != 0) {
LAB_001991b8:
        MCOperand_CreateReg0(param_1,uVar2);
        MCOperand_CreateImm0(param_1,uVar3);
        return uVar6;
      }
      MCOperand_CreateReg0(param_1,0xc);
      goto LAB_00199208;
    }
    if (iVar4 != 0xf) {
      uVar6 = 3;
      uVar2 = *(undefined2 *)(GPR + uVar5 * 2);
      goto LAB_001991b8;
    }
  }
  MCOperand_CreateReg0(param_1,0xb);
LAB_00199208:
  MCOperand_CreateImm0(param_1,uVar3);
  return 1;
}

