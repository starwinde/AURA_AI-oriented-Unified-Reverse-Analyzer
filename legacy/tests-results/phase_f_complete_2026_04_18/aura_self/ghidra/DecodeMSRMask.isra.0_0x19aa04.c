
undefined8 DecodeMSRMask_isra_0(long param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  if ((*(uint *)(*(long *)(param_1 + 800) + 4) >> 5 & 1) == 0) {
    if (param_2 == 0) {
      return 0;
    }
  }
  else {
    uVar1 = param_2 & 0xff;
    if (uVar1 < 0x15) {
      uVar3 = 0x1f0fefL >> ((ulong)uVar1 & 0x3f);
    }
    else {
      if (0x10 < uVar1 - 0x88) {
        return 1;
      }
      uVar3 = 0x11b0fL >> ((ulong)(uVar1 - 0x88) & 0x3f);
    }
    if ((uVar3 & 1) == 0) {
      return 1;
    }
    iVar2 = MCInst_getOpcode(param_1);
    if (iVar2 == 0xb5b) {
      uVar4 = 1;
      if ((param_2 >> 10 == 0) || ((param_2 & 0xfc) != 0 && param_2 >> 10 != 2)) goto LAB_0019aa34;
    }
  }
  uVar4 = 3;
LAB_0019aa34:
  MCOperand_CreateImm0(param_1,param_2);
  return uVar4;
}

