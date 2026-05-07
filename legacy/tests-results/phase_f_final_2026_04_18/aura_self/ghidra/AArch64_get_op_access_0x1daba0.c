
int AArch64_get_op_access(long param_1,undefined4 param_2)

{
  ushort uVar1;
  
  uVar1 = insn_find(insns,0x1517,param_2,param_1 + 0x70);
  if (uVar1 != 0) {
    return (uint)uVar1 * 0xc + 0x2d4754;
  }
  return 0;
}

