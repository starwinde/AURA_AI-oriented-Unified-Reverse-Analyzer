
undefined4 DecodeSORegImmOperand_isra_0(long param_1,ulong param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (uint)param_2 & 0xf;
  uVar2 = (uint)param_2 >> 7;
  if (uVar4 == 0xd) {
    uVar5 = 3;
    if ((*(uint *)(*(long *)(param_1 + 800) + 4) & 0x40) == 0) {
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 3;
    if (uVar4 == 0xf) {
      uVar5 = 1;
    }
  }
  MCOperand_CreateReg0(param_1,*(undefined2 *)(GPR + (ulong)uVar4 * 2));
  uVar3 = ((uint)(param_2 >> 5) & 3) - 1;
  uVar4 = 2;
  uVar1 = *(undefined4 *)(CSWTCH_1083 + (ulong)uVar5 * 4);
  if ((uVar3 < 3) && (uVar4 = *(uint *)(CSWTCH_1048 + (ulong)uVar3 * 4), uVar2 == 0 && uVar4 == 4))
  {
    uVar4 = 5;
  }
  MCOperand_CreateImm0(param_1,uVar4 | uVar2 << 3);
  return uVar1;
}

