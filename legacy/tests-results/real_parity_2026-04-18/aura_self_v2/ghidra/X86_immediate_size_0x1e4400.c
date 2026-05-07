
undefined1 X86_immediate_size(uint param_1,undefined1 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (0x3b08 < param_1 - 0x93) {
    return 0;
  }
  uVar3 = 0x135;
  uVar2 = 0x135;
  uVar5 = 0x8bf;
  uVar4 = 0;
  while( true ) {
    uVar1 = uVar2 >> 1;
    if (uVar5 == param_1) {
      if (param_2 != (undefined1 *)0x0) {
        *param_2 = x86_imm_size[(ulong)uVar1 * 4];
      }
      return x86_imm_size[(ulong)uVar1 * 4 + 1];
    }
    if (uVar5 < param_1) {
      uVar4 = uVar1 + 1;
    }
    else {
      uVar3 = uVar1 - 1;
      if (uVar2 < 2) {
        return 0;
      }
    }
    uVar2 = uVar3 + uVar4;
    if (uVar3 < uVar4) break;
    uVar5 = (uint)*(ushort *)(x86_imm_size + (ulong)(uVar2 >> 1) * 4 + 2);
  }
  return 0;
}

