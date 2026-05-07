
char * FUN_001755d0(undefined4 param_1)

{
  switch(param_1) {
  case 1:
    return "ABS64";
  case 2:
    return "ABS32";
  case 3:
    return "GLOB_DAT";
  case 4:
    return "JUMP_SLOT";
  case 5:
    return "RELATIVE";
  case 6:
    return "PC32";
  case 7:
    return "PLT32";
  case 8:
    return "COPY";
  case 9:
    return "TPOFF";
  case 10:
    return "IRELATIVE";
  case 0xb:
    return "PE_HIGH";
  case 0xc:
    return "PE_LOW";
  default:
    return "UNKNOWN";
  }
}

