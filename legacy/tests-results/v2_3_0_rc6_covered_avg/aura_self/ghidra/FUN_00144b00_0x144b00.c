
char * FUN_00144b00(uint param_1)

{
  char *pcVar1;
  
  if (param_1 == 3) {
    return "ARM";
  }
  if (param_1 < 4) {
    if (param_1 != 1) {
      pcVar1 = "unknown";
      if (param_1 == 2) {
        pcVar1 = "x86_64";
      }
      return pcVar1;
    }
    return "x86";
  }
  pcVar1 = "unknown";
  if (param_1 == 4) {
    pcVar1 = "AArch64";
  }
  return pcVar1;
}

