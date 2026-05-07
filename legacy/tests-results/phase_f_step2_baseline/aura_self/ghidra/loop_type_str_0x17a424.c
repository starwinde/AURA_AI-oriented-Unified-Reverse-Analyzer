
char * loop_type_str(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 2) {
    return "do-while";
  }
  if (param_1 != 3) {
    pcVar1 = "while";
    if (param_1 != 1) {
      pcVar1 = "unknown";
    }
    return pcVar1;
  }
  return "for";
}

