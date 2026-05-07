
char * FUN_0015a9d0(undefined4 param_1)

{
  switch(param_1) {
  case 2:
    return "+";
  case 3:
    return "-";
  case 4:
    return "*";
  case 5:
    return "/";
  case 6:
    return "&";
  case 7:
    return "|";
  case 8:
    return "^";
  case 9:
    return "<<";
  case 10:
    return ">>";
  case 0xb:
    return "==";
  case 0xc:
    return "!=";
  case 0xd:
  case 0xf:
    return "<";
  case 0xe:
  case 0x10:
    return "<=";
  case 0x11:
  case 0x13:
    return ">";
  case 0x12:
  case 0x14:
    return ">=";
  default:
    return "?";
  }
}

