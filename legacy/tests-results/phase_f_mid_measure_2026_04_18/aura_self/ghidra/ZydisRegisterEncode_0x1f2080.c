
int ZydisRegisterEncode(uint param_1,byte param_2)

{
  int iVar1;
  
  if (((param_1 == 0) || (param_1 == 0xb)) || (param_1 == 0xc)) {
    iVar1 = 0;
  }
  else if (param_1 < 0x14) {
    if ((uint)(*(int *)(REG_CLASS_LOOKUP + (ulong)param_1 * 0xc + 4) -
              *(int *)(REG_CLASS_LOOKUP + (ulong)param_1 * 0xc)) < (uint)param_2) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(REG_CLASS_LOOKUP + (ulong)param_1 * 0xc) + (uint)param_2;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

