
bool ARM_getFeatureBits(uint param_1,int param_2)

{
  bool bVar1;
  
  if (((((param_1 >> 6 & 1) != 0) ||
       (bVar1 = false, 1 < param_2 - 0x71U && (param_2 != 0x74 && param_2 != 0x75))) &&
      (bVar1 = false, param_2 != 99)) && (((param_1 >> 5 & 1) != 0 || (param_2 != 0x3e)))) {
    if ((param_1 >> 4 & 1) != 0) {
      return param_2 != 0x29;
    }
    bVar1 = false;
    if ((param_2 != 0x5b && param_2 != 0x79) && param_2 != 0x29) {
      bVar1 = param_2 != 0x3e || (param_1 & 0x20) != 0;
    }
  }
  return bVar1;
}

