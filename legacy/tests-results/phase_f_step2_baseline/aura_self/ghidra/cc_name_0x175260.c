
char * cc_name(uint param_1)

{
  char *pcVar1;
  
  if (param_1 == 4) {
    return "SysV AMD64";
  }
  if (4 < param_1) {
    if (param_1 == 6) {
      return "ARM EABI";
    }
    if (param_1 != 7) {
      pcVar1 = "unknown";
      if (param_1 == 5) {
        pcVar1 = "MS x64";
      }
      return pcVar1;
    }
    return "AArch64";
  }
  if (param_1 == 2) {
    return "stdcall";
  }
  if (param_1 != 3) {
    pcVar1 = "unknown";
    if (param_1 == 1) {
      pcVar1 = "cdecl";
    }
    return pcVar1;
  }
  return "fastcall";
}

