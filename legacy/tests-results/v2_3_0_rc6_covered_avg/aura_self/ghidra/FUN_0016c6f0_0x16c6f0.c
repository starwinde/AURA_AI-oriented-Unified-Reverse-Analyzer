
char * FUN_0016c6f0(uint param_1)

{
  char *pcVar1;
  
  if (param_1 == 6) {
    return "ZIP";
  }
  if (6 < param_1) {
    if (param_1 == 9) {
      return "RIFF";
    }
    if (param_1 < 10) {
      pcVar1 = "ELF";
      if (param_1 != 7) {
        pcVar1 = "PE";
      }
      return pcVar1;
    }
    pcVar1 = "Unknown";
    if (param_1 == 10) {
      pcVar1 = "OGG";
    }
    return pcVar1;
  }
  if (param_1 == 3) {
    return "GIF";
  }
  if (param_1 < 4) {
    if (param_1 != 1) {
      pcVar1 = "Unknown";
      if (param_1 == 2) {
        pcVar1 = "PNG";
      }
      return pcVar1;
    }
    return "JPEG";
  }
  pcVar1 = "BMP";
  if (param_1 != 4) {
    pcVar1 = "PDF";
  }
  return pcVar1;
}

