
long X86_get_op_access(undefined8 param_1,uint param_2,undefined8 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0x3b22;
  if (0x3b22 < param_2 - 0x92) {
    return 0;
  }
  uVar2 = 0x3b22;
  uVar1 = 0x1e23;
  uVar4 = 0;
  do {
    uVar2 = uVar2 >> 1;
    if (param_2 == uVar1) {
      *param_3 = *(undefined8 *)(insn_ops + (ulong)uVar2 * 0x10);
      return (ulong)uVar2 * 0x10 + 0x40aa50;
    }
    if (param_2 < uVar1) {
      uVar3 = uVar2 - 1;
      if (uVar3 < uVar4) {
        return 0;
      }
    }
    else {
      uVar4 = uVar2 + 1;
      if (uVar3 < uVar4) {
        return 0;
      }
    }
    uVar2 = uVar4 + uVar3;
    uVar1 = (uint)*(ushort *)(insns + (ulong)(uVar2 >> 1) * 0x50);
  } while( true );
}

