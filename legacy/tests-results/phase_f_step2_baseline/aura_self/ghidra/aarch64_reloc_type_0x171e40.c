
int aarch64_reloc_type(uint param_1)

{
  int iVar1;
  
  if (param_1 == 0x402) {
    return 4;
  }
  if (param_1 < 0x403) {
    iVar1 = 8;
    if (((param_1 != 0x400) && (iVar1 = 3, param_1 != 0x401)) && (iVar1 = 1, param_1 != 0x101)) {
      iVar1 = (uint)(param_1 == 0x102) << 1;
    }
  }
  else {
    iVar1 = 9;
    if ((param_1 != 0x406) && (iVar1 = 10, param_1 != 0x408)) {
      iVar1 = 5;
      if (param_1 != 0x403) {
        iVar1 = 0;
      }
      return iVar1;
    }
  }
  return iVar1;
}

