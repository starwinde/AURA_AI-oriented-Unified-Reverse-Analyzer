
char * FUN_00178be4(uint param_1)

{
  char *pcVar1;
  
  if (param_1 == 2) {
    return "arg";
  }
  if (2 < param_1) {
    if (param_1 != 3) {
      pcVar1 = "padding";
      if (param_1 != 4) {
        pcVar1 = "unknown";
      }
      return pcVar1;
    }
    return "retaddr";
  }
  pcVar1 = "local";
  if (param_1 != 0) {
    pcVar1 = "saved_reg";
  }
  return pcVar1;
}

