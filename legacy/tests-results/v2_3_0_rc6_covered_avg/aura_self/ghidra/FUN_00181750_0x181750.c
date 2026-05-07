
char * FUN_00181750(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return "SEQ";
  case 1:
    return "IF";
  case 2:
    return "WHILE";
  case 3:
    return "DO_WHILE";
  case 4:
    return "FOR";
  case 5:
    return "SWITCH";
  case 6:
    return "GOTO";
  case 7:
    return "LABEL";
  case 8:
    return "BREAK";
  case 9:
    return "CONTINUE";
  case 10:
    return "ASSIGN";
  case 0xb:
    return "RETURN";
  case 0xc:
    return "CALL_STMT";
  case 0xd:
    return "VAR";
  case 0xe:
    return "CONST";
  case 0xf:
    return "BINOP";
  case 0x10:
    return "UNOP";
  case 0x11:
    return "CALL";
  case 0x12:
    return "CAST";
  case 0x13:
    return "FIELD_ACCESS";
  case 0x14:
    return "ARRAY_INDEX";
  case 0x15:
    return "TERNARY";
  default:
    return "UNKNOWN";
  }
}

