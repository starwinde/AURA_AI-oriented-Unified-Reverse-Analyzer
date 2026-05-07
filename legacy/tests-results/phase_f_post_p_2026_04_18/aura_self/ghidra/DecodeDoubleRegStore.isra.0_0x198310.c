
/* WARNING: Type propagation algorithm not settling */

uint DecodeDoubleRegStore_isra_0(undefined8 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar3 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar2 = (uint)uVar3;
  if (uVar2 == 0xf) {
    uVar5 = (ulong)(param_2 >> 0x10) & 0xf;
    MCOperand_CreateReg0(param_1,0xb);
    uVar4 = 1;
    uVar3 = (ulong)(param_2 & 0xf);
    if ((int)uVar5 == 0xf || (param_2 & 0xf) == 0xf) goto LAB_00198368;
  }
  else {
    uVar5 = (ulong)(param_2 >> 0x10) & 0xf;
    uVar4 = 3;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar3 * 2));
    uVar3 = (ulong)(param_2 & 0xf);
    if (((uint)uVar5 == 0xf || uVar2 == (uint)uVar5) || uVar2 == (param_2 & 0xf)) {
LAB_00198368:
      uVar4 = 1;
      goto LAB_0019836c;
    }
  }
  if (uVar2 == (int)uVar3 + 1U) {
    uVar4 = 1;
  }
LAB_0019836c:
  if ((uint)uVar3 < 0xe) {
    uVar2 = param_2 & 1;
    if ((param_2 & 1) == 0) {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPRPair + (uVar3 & 0xfffffffffffffffe)));
      uVar2 = uVar4;
    }
    else {
      MCOperand_CreateReg0(param_1,*(undefined2 *)(GPRPair + (uVar3 & 0xfffffffffffffffe)));
    }
    param_2 = param_2 >> 0x1c;
    MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + uVar5 * 2));
    if (param_2 != 0xf) {
      iVar1 = MCInst_getOpcode(param_1);
      if (iVar1 == 0xc4f) {
        if (param_2 == 0xe) {
          return 0;
        }
        MCOperand_CreateImm0(param_1,param_2);
      }
      else {
        MCOperand_CreateImm0(param_1,param_2);
        if (param_2 == 0xe) {
          MCOperand_CreateReg0(param_1,0);
          return uVar2;
        }
      }
      MCOperand_CreateReg0(param_1,3);
      return uVar2;
    }
  }
  return 0;
}

